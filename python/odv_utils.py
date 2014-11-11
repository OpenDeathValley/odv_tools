import struct

def hexdump(src, length=16):
    FILTER = ''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)])
    lines = []
    for c in xrange(0, len(src), length):
        chars = src[c:c+length]
        hex = ' '.join(["%02x" % ord(x) for x in chars])
        printable = ''.join(["%s" % ((ord(x) <= 127 and FILTER[ord(x)]) or '.') for x in chars])
        lines.append("%04x  %-*s  %s\n" % (c, length*3, hex, printable))
    return ''.join(lines).rstrip('\n')

class Buffer:
    def __init__(self, buf):
        self.buf = buf
        self.length = len(self.buf)
        self.pos = 0

    def GetByte(self):
        byte = struct.unpack("<B", self.buf[self.pos: self.pos + 1])[0]
        self.pos += 1
        return byte

    def GetWord(self):
        word = struct.unpack("<H", self.buf[self.pos: self.pos + 2])[0]
        self.pos += 2
        return word

    def GetDword(self):
        dword = struct.unpack("<I", self.buf[self.pos: self.pos + 4])[0]
        self.pos += 4
        return dword

    def GetQword(self):
        qword = struct.unpack("<Q", self.buf[self.pos: self.pos + 8])[0]
        self.pos += 8
        return qword

    def GetBuffer(self):
        size = self.GetWord()
        b = self.buf[self.pos:self.pos + size]
        self.pos += size
        return b

    def GetBufferSize(self, size):
        b = self.buf[self.pos:self.pos + size]
        self.pos += size
        return b
