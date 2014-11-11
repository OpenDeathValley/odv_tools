import struct
import bz2
import Image
from odv_utils import Buffer

b = Buffer(open("Loading.pak", "rb").read())
z = 0
while b.pos != b.length:
    width = b.GetWord()
    height = b.GetWord()
    type_picture = b.GetDword()
    length = b.GetDword()
    print "[+] width = %04X" % width
    print "[+] height = %04X" % height
    print "[+] type_picture = %04X" % type_picture
    print "[+] length = %04X" % length
    data = b.GetBufferSize(length)
    data_u = bz2.decompress(data)
    print b.length
    print b.pos
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
    img.save("test_pak_%d.jpg" % z, "JPEG")
    z = z + 1
