import sys
import os
import struct
import bz2
import Image, ImageDraw
from odv_utils import Buffer

def draw_crosshair(pixels, coord):
    for y, x in coord:
        for i in xrange(0, 7):
            pixels[x - i, y - i] = (255, 0, 220)
            pixels[x, y - i] = (255, 0, 220)
            pixels[x - i, y] = (255, 0, 220)
            pixels[x, y] = (255, 0, 220)
            pixels[x + 1, y + i] = (255, 0, 220)
            pixels[x, y + i] = (255, 0, 220)
            pixels[x + i, y] = (255, 0, 220)

def handle_dvm(filename):
    b = Buffer(open(filename, "rb").read())
    width = b.GetWord()
    height = b.GetWord()
    type_picture = b.GetDword()
    length = b.GetDword()
    data = b.GetBufferSize(length)
    data_u = bz2.decompress(data)
    print "[+] width        = 0x%04X" % width
    print "[+] height       = 0x%04X" % height
    print "[+] type_picture = 0x%08X" % type_picture
    print "[+] length       = 0x%08X" % length
    print "[+] length_u     = 0x%08X" % len(data_u)
    img = Image.new('RGB', (height, width), "black")
    pixels = img.load()
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            color = struct.unpack("<H", data_u[((j + (i * img.size[1])) * 2):((j + (i * img.size[1])) * 2) + 2])[0]
            red = (color >> 11 << 8) / 32
            green = (((color >> 5) & 0x3F) << 8) / 64
            blue = ((color & 0x1F) << 8) / 32
            pixels[i, j] = (red, green, blue)

    #coord = [(920, 806), (900, 826), (922, 842), (883, 872), (846, 809), (882, 785)]
    #draw_crosshair(pixels, coord)

    img = img.transpose(Image.FLIP_LEFT_RIGHT)
    img = img.rotate(90, expand=True)
    img.save("test_dvm.jpg", "JPEG")

def main():
    if len(sys.argv) < 2:
        sys.stderr.write("Usage: %s <*.dvm>" % sys.argv[0])
        return 1
    if not os.path.exists(sys.argv[1]):
        sys.stderr.write("[-] %s wat not found" % sys.argv[1])
        return 1
    handle_dvm(sys.argv[1])

if __name__ == "__main__":
    sys.exit(main())