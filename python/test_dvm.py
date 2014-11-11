import struct
import bz2
import Image, ImageDraw
from odv_utils import Buffer

def hexdump(src, length=16):
    FILTER = ''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)])
    lines = []
    for c in xrange(0, len(src), length):
        chars = src[c:c+length]
        hex = ' '.join(["%02x" % ord(x) for x in chars])
        printable = ''.join(["%s" % ((ord(x) <= 127 and FILTER[ord(x)]) or '.') for x in chars])
        lines.append("%04x  %-*s  %s\n" % (c, length*3, hex, printable))
    return ''.join(lines).rstrip('\n')

b = Buffer(open("Level_01.dvm", "rb").read())
width = b.GetWord()
height = b.GetWord()
print "[+] width = %04X" % width
print "[+] height = %04X" % height
type_picture = b.GetDword()
print "[+] type_picture = %08X" % type_picture
length = b.GetDword()
print "[+] length = %08X" % length
data = b.GetBufferSize(length)
data_u = bz2.decompress(data)
print "[+] length_u = %08X" % len(data_u)
print hexdump(data_u[:0x200])
b_u = Buffer(data_u)

#unsigned char red = (buf & 0xf800) >> 11;
#unsigned char green = (buf & 0x07e0) >> 5;
#unsigned char blue = buf & 0x001f;

img = Image.new('RGB', (height, width), "black")
pixels = img.load() # create the pixel map
for i in range(img.size[0]):
    for j in range(img.size[1]):
        color = struct.unpack("<H", data_u[((j + (i * img.size[1])) * 2):((j + (i * img.size[1])) * 2) + 2])[0]
        r = (color >> 11 << 8) / 32
        g = (((color >> 5) & 0x3F) << 8) / 64
        b = ((color & 0x1F) << 8) / 32
        pixels[i, j] = (r, g, b)

#coord = [(645, 862), (576, 915), (92, 690), (300, 534), (162, 458), (218, 424), (276, 446), (306, 423), (246, 390), (347, 305), (523, 384)]
#y = [(y, x) for x, y in coord]
#draw = ImageDraw.Draw(img)
#for i in zip(y, y[1:]):
#    draw.rectangle(i, outline=(255, 0, 220), fill=(255, 0, 220))
    #draw.rectangle([(x - 4, y - 4), (x + 4, y + 4)], outline=(255, 0, 220), fill=(255, 0, 220))
    #print i

#coord = [(442, 369), (498, 290), (413, 247), (581, 120), (808, 233), (1173, 759), (964, 931), (534, 718)]
#y = [(y, x) for x, y in coord]
#draw = ImageDraw.Draw(img)
#for i in zip(y, y[1:]):
#    draw.rectangle(i, outline=(255, 0, 220), fill=(255, 0, 220))

#draw = ImageDraw.Draw(img)
#draw.rectangle(coord, outline=(255, 0, 220), fill=(255, 0, 220))
#for y, x in coord:
    #draw.rectangle([(x - 4, y - 4), (x + 4, y + 4)], outline=(255, 0, 220), fill=(255, 0, 220))

coord = [(528, 347), (487, 322), (511, 296), (480, 280), (460, 302), (404, 275), (481, 200), (608, 266)]
coord = [(442, 369), (498, 290), (413, 247), (581, 120), (808, 233), (1173, 759), (964, 931), (534, 718)]
coord = [(920, 806), (900, 826), (922, 842), (883, 872), (846, 809), (882, 785)]
for y, x in coord:
    #draw.rectangle([(x - 4, y - 4), (x + 4, y + 4)], outline=(255, 0, 220), fill=(255, 0, 220))
    
    for i in xrange(0, 7):
        pixels[x - i, y - i] = (255, 0, 220)
        pixels[x, y - i] = (255, 0, 220)
        pixels[x - i, y] = (255, 0, 220)
        pixels[x, y] = (255, 0, 220)
        pixels[x + 1, y + i] = (255, 0, 220)
        pixels[x, y + i] = (255, 0, 220)
        pixels[x + i, y] = (255, 0, 220)
        
#        red = ((struct.unpack("<H", data_u[i + (j * img.size[1]): i + (j * img.size[1]) + 2])[0] >> 0x0B) << 0x08) / 0x20
#        #green = 0
#        #blue = 0
#        green = (((struct.unpack("<H", data_u[i + (j * img.size[1]): i + (j * img.size[1]) + 2])[0] >> 0x5) & 0x3F) << 8) / 0x40
#        blue = ((struct.unpack("<H", data_u[i + (j * img.size[1]): i + (j * img.size[1]) + 2])[0] & 0x001F) << 8) / 0x20
#        pixels[i, j] = (red, green, blue)
img = img.transpose(Image.FLIP_LEFT_RIGHT)
img = img.rotate(90, expand=True)
img.save("test_dvm.jpg", "JPEG")
