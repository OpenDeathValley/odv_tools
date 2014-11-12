import sys
import os
import struct
import zlib
import Image, ImageDraw
from odv_utils import Buffer

def handle_map(filename):
    b = Buffer(open(filename, "rb").read())
    width = b.GetWord()
    height = b.GetWord()
    type_compression = b.GetDword()
    length = b.GetDword()
    data = b.GetBufferSize(length)
    data_u = zlib.decompress(data)
    print "[+] width            = 0x%04X" % width
    print "[+] height           = 0x%04X" % height
    print "[+] type_compression = 0x%08X" % type_compression
    print "[+] length           = 0x%08X" % length
    print "[+] length_u         = 0x%08X" % len(data_u)
    img = Image.new('RGB', (height, width), "black")
    pixels = img.load()
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            color = struct.unpack("<H", data_u[((j + (i * img.size[1])) * 2):((j + (i * img.size[1])) * 2) + 2])[0]
            red = (color >> 11 << 8) / 32
            green = (((color >> 5) & 0x3F) << 8) / 64
            blue = ((color & 0x1F) << 8) / 32
            pixels[i, j] = (red, green, blue)

    img = img.transpose(Image.FLIP_LEFT_RIGHT)
    img = img.rotate(90, expand=True)
    img.save("test_map.jpg", "JPEG")

def main():
    if len(sys.argv) < 2:
        sys.stderr.write("Usage: %s <*.map>" % sys.argv[0])
        return 1
    if not os.path.exists(sys.argv[1]):
        sys.stderr.write("[-] %s wat not found" % sys.argv[1])
        return 1
    handle_map(sys.argv[1])

if __name__ == "__main__":
    sys.exit(main())
