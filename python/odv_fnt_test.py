import struct
import bz2
import zlib
import Image, ImageDraw
from odv_utils import Buffer
from odv_utils import hexdump
import sys
import glob
import ctypes

# Parse FNT: sub_5D0520

def draw_crosshair(pixels, coord, color=(255, 0, 220)):
    for y, x in coord:
        for i in xrange(0, 7):
            try:
                pixels[x, y - i] = color
                pixels[x - i, y] = color
                pixels[x, y] = color
                pixels[x, y + i] = color
                pixels[x + i, y] = color
            except:
                continue
            
def read_image(b, filename="test_fnt.jpg", pixel_tab=[]):
    width = b.GetWord()
    height = b.GetWord()
    type_compression = b.GetDword()
    size_compressed = b.GetDword()
    print "[+] width = 0x%08X" % width
    print "[+] height = 0x%08X" % height
    data = b.GetBufferSize(size_compressed)
    if type_compression == 2:
        data_u = bz2.decompress(data)
    elif type_compression == 1:
        data_u = zlib.decompress(data)
    else:
        print "[-] unsupported type"
        sys.exit()
    img = Image.new('RGB', (height, width), "black")
    pixels = img.load()
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            color = struct.unpack("<H", data_u[((j + (i * img.size[1])) * 2):((j + (i * img.size[1])) * 2) + 2])[0]
            red = (color >> 11 << 8) / 32
            green = (((color >> 5) & 0x3F) << 8) / 64
            blue = ((color & 0x1F) << 8) / 32
            pixels[i, j] = (red, green, blue)
    draw = ImageDraw.Draw(img)
    for a in pixel_tab:
        print a
        draw.rectangle(a, outline=(76, 255, 0))
    img = img.transpose(Image.FLIP_LEFT_RIGHT)
    img = img.rotate(90)
    img.save(filename, "PNG")
    return b

def parse_fnt(filename="dialog.fnt"):
    print "[+] fnt_filename = %s" % filename
    b = Buffer(open(filename, "rb").read())
    signature = b.GetBufferSize(6)
    if signature != "SBFONT":
        print "[-] wrong signature"
        sys.exit(1)
    unk_b = Buffer(b.GetBufferSize(0x3C))
    unk_dword_00 = unk_b.GetDword()
    print "[+] first_unk_dword_00 = 0x%08X" % unk_dword_00
    name = unk_b.GetBufferSize(36)
    print "[+] name = %s" % name.replace("\x00", "")
    unk_word_00 = unk_b.GetWord()
    unk_word_01 = unk_b.GetWord()
    unk_dword_02 = unk_b.GetDword()
    unk_dword_03 = unk_b.GetDword()
    unk_dword_04 = unk_b.GetDword()
    print "[+] unk_word_00 = %04X (%d)  // TYPE SOMETHING ?" % (unk_word_00, unk_word_00)
    print "[+] unk_word_01 = %04X (%d)" % (unk_word_01, unk_word_01)
    print "[+] unk_dword_02 = %08X (%d)  // HEIGHT ?" % (unk_dword_02, unk_dword_02)
    print "[+] unk_dword_03 = %08X (%d)  // Width square letter" % (unk_dword_03, unk_dword_03)
    print "[+] unk_dword_04 = %08X (%d)  // Max width letter" % (unk_dword_04, unk_dword_04)
    print hexdump(unk_b.buf[unk_b.pos:unk_b.pos + 0x200])
    unk_b.pos = 0x38
    nb_entry = unk_b.GetDword()
    print "[+] nb_entry = 0x%08X" % nb_entry
    if unk_dword_00 >= 0x200:
        unk_dword_05 = b.GetDword()
    else:
        unk_dword_05 = 0
    unk_dword_05 = ctypes.c_long(unk_dword_05).value
    print "[+] unk_dword_05 = %08X (%d)" % (unk_dword_05, unk_dword_05)
    pixel_tab = []
    for i in xrange(0, nb_entry):
        char_value = b.GetWord()
        Y_COORD = b.GetDword()
        WIDTH_LETTER = b.GetDword()
        unk_dword_00 = b.GetDword()
        unk_dword_01 = b.GetDword()
        if char_value < 127:
            print "[+] num = %04X" % i
            print "[+] char_value = 0x%04X (\"%c\")" % (char_value, char_value)
            print "[+] Y_COORD = 0x%08X (%d)" % (Y_COORD, Y_COORD)
            print "[+] WIDTH_LETTER = 0x%08X (%d)" % (WIDTH_LETTER, WIDTH_LETTER)
            print "[+] unk_dword_00 = 0x%08X" % unk_dword_00
            print "[+] unk_dword_01 = 0x%08X" % unk_dword_01
            #WIDTH_LETTER = int((WIDTH_LETTER + unk_dword_05 + unk_dword_00 + unk_dword_01) & 0xffffffff)
            pixel_tab.append([(0, Y_COORD), (unk_dword_02 - 1, Y_COORD + WIDTH_LETTER)])
    print pixel_tab
    b = read_image(b, filename + "1.png", pixel_tab)
    b = read_image(b, filename + "2.png", pixel_tab)
    print "-" * 20

#parse_fnt("buttons_0.fnt")
for fnt_file in glob.glob('./*.fnt'):
    parse_fnt(fnt_file)
