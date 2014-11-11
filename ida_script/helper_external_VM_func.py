from idaapi import *
from idc import *
from idautils import *

# EA of the function that init array of function

init_func_ea = 0x005E3BF0

# EA of function for displaying error / exception message

error_func_ea = 0x005B6E90

def search_func(func_start, func_searched):
 todo = [func_start]
 done = [func_start]
 found_l = []
 while len(todo):
  func_cur = todo.pop()
  done.append(func_cur)
  for x in [x for x in FuncItems(func_cur) if idaapi.is_call_insn(x)]:
   for xref in XrefsFrom(x, idaapi.XREF_FAR):
	if not xref.iscode:
	 continue
	if xref.to not in done:
	 todo.append(xref.to)
	if xref.to == func_searched:
	 found_l.append(xref.frm)
 return found_l

def get_dbg_string(ea):
 nb = 0
 for i in xrange(0, 10):
  ea = PrevHead(ea)
  mnem = GetMnem(ea)
  if mnem == 'push':
   nb = nb + 1
   if nb == 4:
	op1_type = GetOpType(ea, 0)
	if op1_type == o_imm:
	 op1_value = GetOperandValue(ea, 0)
	 return GetString(op1_value)
 return None

f_start = get_func(init_func_ea).startEA
f_end = FindFuncEnd(f_start)
func_l = []
for ea in Heads(f_start, f_end):
 mnem = GetMnem(ea)
 if mnem == 'mov':
  op1_type = GetOpType(ea, 0)
  op2_type = GetOpType(ea, 1)
  if op1_type == o_phrase or op1_type == o_displ and op2_type == o_imm:
   op2_value = GetOperandValue(ea, 1)
   func_l.append(op2_value)
for func in func_l:
 l = search_func(func, error_func_ea)
 print "0x%08X" % func
 for i in l:
  res = get_dbg_string(i)
  if res != None:
   print "0x%08X -> %s" % (i, res)
  break # HAX, only the first one