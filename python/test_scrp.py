import struct
from odv_utils import Buffer

b = Buffer(open("test_scrp.bin", "rb").read())
sig = b.GetDword()
print hex(sig)
unk_dword_00 = b.GetDword()
print "[+] unk_dword_00 = 0x%08X" % unk_dword_00
version = b.GetDword()
print "[+] version = 0x%08X" % version
nb = b.GetWord()
print "[+] nb = 0x%04X" % nb
for i in xrange(0, nb):
    print "-" * 20
    unk_word_00 = b.GetWord()
    if unk_word_00 == 1:
        print "[+] unk_word_00 = 0x%04X" % unk_word_00
        unk_word_01 = b.GetWord()
        print "[+] unk_word_01 = 0x%04X" % unk_word_01
        unk_word_02 = b.GetWord()
        print "[+] unk_word_02 = 0x%04X" % unk_word_02
        unk_word_03 = b.GetWord()
        print "[+] unk_word_03 = 0x%04X" % unk_word_03
        unk_word_04 = b.GetWord()
        print "[+] unk_word_04 = 0x%04X" % unk_word_04
        unk_byte_00 = b.GetByte()
        print "[+] unk_byte_00 = 0x%02X" % unk_byte_00
        #print "TODO!"
        #sys.exit()
        #pass
    elif unk_word_00 != 2:
        unk_word_01 = unk_word_00
        print "[+] nb coordinate = 0x%04X" % unk_word_00
        tab = []
        for j in xrange(0, unk_word_01):
            unk_word_02 = b.GetWord()
            unk_word_03 = b.GetWord()
            tab.append((unk_word_02, unk_word_03))
            #print "[+] unk_word_02 = 0x%04X" % unk_word_02
            #print "[+] unk_word_03 = 0x%04X" % unk_word_03
        print tab
        unk_word_04 = b.GetWord()
        print "[+] unk_word_04 = 0x%04X" % unk_word_04
        unk_word_05 = b.GetWord()
        print "[+] unk_word_05 = 0x%04X" % unk_word_05
        unk_byte_00 = b.GetByte()
        print "[+] classname present = 0x%02X" % unk_byte_00
        if unk_byte_00 == 1:
            classname = b.GetBuffer()
            print "[+] classname = %s" % classname
    else:
        print "STFU!"
        sys.exit()
    #break
