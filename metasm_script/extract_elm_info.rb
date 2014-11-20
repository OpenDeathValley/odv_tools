require 'metasm'
include Metasm

def print_block_info(block)
    # print Metasm::InstructionBlock attributes
    print "block at 0x#{block.address.to_s(16)}\n"
    print "\tfrom_normal: ", block.from_normal.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.from_normal
    print "\tto_normal: ", block.to_normal.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.to_normal
    print "\tfrom_subfuncret: ", block.from_subfuncret.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.from_subfuncret
    print "\tto_subfuncret: ", block.to_subfuncret.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.to_subfuncret
    print "\tfrom_indirect: ", block.from_indirect.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.from_indirect
    print "\tto_indirect: ", block.to_indirect.map{|c| '0x%08X' % c}.join(' - '), "\n" if block.to_indirect
end

def print_modrm_info(arg)
    # print Metasm::Ia32::ModRM attributes
    print "arg.b = ", arg.b, "\n"
    print "arg.i = ", arg.i, "\n"
    print "arg.imm = ", arg.imm, "\n"
    print "arg.s = ", arg.s, "\n"
end

def output_disas(dasm)
    # dasm: Metasm::Disassembler
    # print disassembler result
    out = dasm.instructionblocks.sort_by { |block| block.address }.map{ |block|
        ((l = dasm.get_label_at(block.address)) ? "#{l}:\n" : '') + block.list.map{ |instr|
            instr.instruction.to_s
        }.join("\n")
    }.join("\n")
    puts out
end

def output_disas_func(dasm, func_va)
    # dasm: Metasm::Disassembler
    # func_va: Fixnum
    out = dasm.function_blocks(func_va).keys.sort.each { |a| }.map{ |a|
        next if not di = dasm.di_at(a)
        ((l = dasm.get_label_at(di.block.address)) ? "#{l}:\n" : '') + di.block.list.map{ |instr|
            instr.instruction.to_s
        }.join("\n")
    }.join("\n")
    puts out
end

def output_disas_block(dasm, block)
    out = (l = dasm.get_label_at(block.address)) ? "#{l}:\n" : ''
    out += block.list.map{ |instr|
            instr.instruction.to_s
        }.join("\n")
    puts out
end

def is_reg(arg)
    return (arg and arg.kind_of? Ia32::Reg)
end

def is_modrm(arg)
    return (arg and arg.kind_of? Ia32::ModRM)
end

def is_numeric(arg)
    return (arg and arg.kind_of? Expression and arg.reduce_rec.kind_of? Integer)
end

def is_jcc(decoded_instru)
    # test if Metasm::DecodedInstruction is a conditonal jump
    pr = decoded_instru.opcode.props
    if pr[:setip] and not (['ret', 'retn', 'call', 'jmp'] .include? decoded_instru.instruction.opname)
        return true
    end
    return false
end

def get_val_at(dasm, val_va, size=32)
    # decode immediate value at val_va virtual address
    if s = dasm.get_section_at(val_va)
        value = s[0].decode_imm("a#{size}".to_sym, dasm.cpu.endianness)
        return value
    else
        print "[-] get_val_at - dasm.get_section_at(0x#{val_va.to_s(16)}) failed\n"
        exit()
    end
end

# HAX, no stack offset :(
def find_push_before_call(dasm, block, call_va)
    if not call_index = block.list.index{|x| x.address == call_va}
        print "[-] find_push_before_call - call_index not found\n"
        exit()
    end
    for n in (call_index - 1).downto(0) do
        decoded_instru = block.list[n]
        if decoded_instru.instruction.opname == 'push'
            return decoded_instru
        end
    end
    return nil
end

def get_next_dst(dasm, jcc_va)
    # dasm: Metasm::Disassembler
    # jcc_va: Fixnum
    # return a tuple with next address and destination of a conditonal jump
    di = dasm.di_at(jcc_va)
    if not is_jcc(di)
        return nil, nil
    end
    return di.next_addr, (di.block.to_normal - [di.next_addr])[0]
end

def get_vtable_va(dasm, ctor_va)
    dasm.disassemble_fast(ctor_va)
    dasm.function_blocks(ctor_va).keys.sort.each { |a|
        next if not di = dasm.di_at(a)
        di.block.list.each {|decoded_instru|
            # check mov dword ptr[esi]
            if decoded_instru.instruction.opname == 'mov' and
                is_modrm(decoded_instru.instruction.args[0]) and
                decoded_instru.instruction.args[0].b.to_s == "esi" and not decoded_instru.instruction.args[0].imm
                if is_numeric(decoded_instru.instruction.args[1])
                    vtable_va = decoded_instru.instruction.args[1].reduce_rec
                    return vtable_va
                else
                    print "[-] get_vtable_va - arg1 not numeric"
                    exit()
                end
            end
        }
    }
    return nil
end

def print_object_info(object)
    print "ba => block_address\n"
    print "so => size_object\n"
    print "c_va => constructor virtual address\n"
    print "v_va => vtable virtual address\n"
    print "rd => read method virtual address\n"
    print "v => value (type of object)\n"
    object.each {|obj|
        block_address, size_object, constructor_va, vtable_va, read_method, value = obj
        print "v = 0x%08X ; rd: 0x%08X ; ba: 0x%08X ; so: 0x%04X ; c_va: 0x%08X ; v_va: 0x%08X ; \n" % [value, read_method, block_address, size_object, constructor_va, vtable_va]
    }
end

def test_dst(dasm, jcc_va)
    # ...
    nxt, dst = get_next_dst(dasm, jcc_va)
    print "next: 0x#{nxt.to_s(16)}\n"
    print "dst : 0x#{dst.to_s(16)}\n"
    #exit()
end

def get_cond_jcc(dasm, decoded_instru, call_read_type_va, switch_symbolism)
    cond = dasm.cpu.get_jump_condition(decoded_instru)
    back = dasm.backtrace(cond, decoded_instru.address, :log => bt_log = [], :snapshot_addr => call_read_type_va)
    expr =  back[0].bind(switch_symbolism).reduce_rec
    if expr.lexpr.lexpr.rexpr.class != Fixnum
        print "[-] get_cond_jcc - not Fixnum!"
        exit()
    end
    value = -expr.lexpr.lexpr.rexpr
    return value
end

def output_instance_var(obj)
    print obj.instance_variables.map{|var| puts [var, obj.instance_variable_get(var)].join(":")}
    print "\n"
end

def get_index_jmp_table(dasm, jump_table_va, value, decoded_instru)
    print decoded_instru.comment
    nb_index = decoded_instru.comment.length
    if nb_index == 0
        print "[-] get_index_jmp_table - nb_index null\n"
        exit()
    end
    index = -1
    for n in (0..nb_index) do
        block_va = get_val_at(dasm, jump_table_va + n * decoded_instru.instruction.args[0].s)
        if block_va == value
            index = n
            break
        end
    end
    return index
end

def get_backtrace_index_val(dasm, reg, decoded_instru, call_read_type_va, switch_symbolism)
    back = dasm.backtrace(reg, decoded_instru.address, :log => bt_log = [], :snapshot_addr => call_read_type_va)
    expr =  back[0].bind(switch_symbolism).reduce_rec
    if expr.rexpr.class != Fixnum
        print "[-] get_backtrace_index - not Fixnum!"
        exit()
    end
    return -expr.rexpr
end

def get_cond_not_jcc(dasm, block, decoded_instru, call_read_type_va, switch_symbolism)
    if decoded_instru.instruction.opname == 'jmp' and is_modrm(decoded_instru.instruction.args[0])
        # 004ACE7F FF 24 85 F4 DE 4A 00    jmp     ds:off_4ADEF4[eax*4]
        if decoded_instru.instruction.args[0].i.to_s == "eax"
            #print_modrm_info(decoded_instru.instruction.args[0])
            jump_table_va = dasm.normalize(decoded_instru.instruction.args[0].imm)
            print "[+] jump_table_va: 0x#{jump_table_va.to_s(16)}\n"
            index = get_index_jmp_table(dasm, jump_table_va, block.address, decoded_instru)
            if index == -1
                print "[-] get_cond - index not found!"
                exit()
            end
            value = get_backtrace_index_val(dasm, :eax, decoded_instru, call_read_type_va, switch_symbolism) + index
            return value
        # 004AD1AE 8A 90 24 DF 4A 00       mov     dl, ds:byte_4ADF24[eax]
        # 004AD1B4 FF 24 95 10 DF 4A 00    jmp     ds:off_4ADF10[edx*4] ; switch
        elsif decoded_instru.instruction.args[0].i.to_s == "edx"
            jump_table_va = dasm.normalize(decoded_instru.instruction.args[0].imm)
            print "[+] jump_table_va: 0x#{jump_table_va.to_s(16)}\n"
            index = get_index_jmp_table(dasm, jump_table_va, block.address, decoded_instru)
            if index == -1
                print "[-] get_cond - index not found!"
                exit()
            end
            # TODO: hax
            index_table = 0x004ADF24
            real_index = -1
            for n in (0..239) do
                val_index = get_val_at(dasm, index_table + n, 8)
                if val_index == index
                    real_index = n
                end
            end
            if real_index == -1
                print "[-] get_cond - REAL index not found!"
                exit()
            end
            value = get_backtrace_index_val(dasm, :eax, decoded_instru, call_read_type_va, switch_symbolism) + real_index
            print "[+] value = 0x#{value.to_s(16)}\n"
            return value
        else
            print "[-]get_cond_not_jcc - unknow jump talbe"
            exit()
        end
    else
        print "[-] get_cond_not_jcc - not jump table\n"
        exit()
    end
end

def get_cond(dasm, block, call_read_type_va, switch_symbolism)
    if block.from_normal.length != 1
        from_normal = block.from_normal[0]
    else
        from_normal = block.from_normal[0]
    end
    prev_di = dasm.di_at(from_normal)
    prev_block = prev_di.block
    decoded_instru = prev_di.block.list[-1]
    if is_jcc(decoded_instru)
        value = get_cond_jcc(dasm, decoded_instru, call_read_type_va, switch_symbolism)
        return value
    else
        value = get_cond_not_jcc(dasm, block, decoded_instru, call_read_type_va, switch_symbolism)
        return value
    end
end

filename = "game_swick.exe"
start_va = 0x4ACD50             # Parse ELEM Function
new_func_va = 0x0061F14F        # new() C++
new_ignored_va = [0x004ADDBD]
call_read_type_va = 0x004ACE56  # snapshot_addr for backtracking
switch_symbolism = {
    Expression[Indirection[[:esp, :+, 0x1c], 4, nil], :&, 0xFFFF] => :type_object,
}
object = []

bin = AutoExe.decode_file(filename)
dasm = bin.init_disassembler
dasm.disassemble_fast(start_va)

dasm.function_blocks(start_va).keys.sort.each { |a|
    next if not di = dasm.di_at(a)
    block = di.block
    # check if the new() func is called inside the block, and it's not one we ignore
    if block.to_normal and block.to_normal.include? new_func_va and not new_ignored_va.include? block.address
        print "[+] Working on block at 0x#{block.address.to_s(16)}\n"
        call_decoded_instru = block.list.last
        decoded_instru = find_push_before_call(dasm, block, call_decoded_instru.address)
        if not is_numeric(decoded_instru.instruction.args[0])
            print "[-] not an immediate value for push\n"
            exit()
        end

        size_object = decoded_instru.instruction.args[0].reduce_rec
        print "[+] Size_object = 0x#{size_object.to_s(16)}\n"
        next_block_address = call_decoded_instru.next_addr
        next_block = dasm.di_at(next_block_address).block
        print "[+] next_block_address = 0x#{next_block_address.to_s(16)}\n"
        nblock_last_decoded_instru = next_block.list[-1]
        if not is_jcc(nblock_last_decoded_instru)
            print "[-] not a jcc after new()\n"
            exit()
        end

        nxt, dst = get_next_dst(dasm, nblock_last_decoded_instru.address)
        cond = dasm.cpu.get_jump_condition(nblock_last_decoded_instru)
        if cond.op == :+
            nxt_block_addr = nxt
        elsif cond.op == :!
            nxt_block_addr = dst
        else
            print "[-] wtf with cond.op\n"
        end
        print "[+] nxt_block_addr = 0x#{nxt_block_addr.to_s(16)}\n"
        di = dasm.di_at(nxt_block_addr)
        constructor_va = di.block.to_normal[0]
        print "[+] constructor_va: 0x#{constructor_va.to_s(16)}\n"

        vtable_va = get_vtable_va(dasm, constructor_va)
        print "[+] vtable_va: 0x#{vtable_va.to_s(16)}\n"
        read_method_at = vtable_va + 0x40
        read_method_va = get_val_at(dasm, read_method_at, 32)
        print "[+] read_method_va: 0x#{read_method_va.to_s(16)}\n"
        value = get_cond(dasm, block, call_read_type_va, switch_symbolism)
        print "[+] value: 0x#{value.to_s(16)}\n"

        object << [block.address, size_object, constructor_va, vtable_va, read_method_va, value]
        print "-" * 20, "\n"
    end
}

print_object_info(object)