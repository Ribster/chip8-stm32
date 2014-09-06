import Image
import ImageOps

def func(num, pos):
            return (num & (1 << pos)) >> pos

def de_func(num, pos):
            return num ^ (1 << pos)


def encode(in_img):
    img_buf=in_img.load()
    i=0
    j=0
    k=0
    l=0
    s=0
    exit=1
    num=0
    out =[]
    for l in xrange(768):
        j=0+k
        for s in xrange(8):
            if img_buf[i,j]<125:
                num=de_func(num, s)
            j+=1
        i+=1
        out.append(num)
        '''print num'''
        num=0
        if i>=96:
            i=0
            k+=8
            
    return out

def decode(bytes):
    out=Image.new('L', (96,68))
    img_bit =[]
    img_buf=out.load()
    i=0
    j=0
    k=0

    for byte in bytes:
        j=0+k
        for pos in xrange(8):
            bit=func(byte,pos)
            img_bit.append(bit)
            if bit:
                img_buf[i,j] =0
            else:
                img_buf[i,j] =255
            j+=1
        i+=1
        if i>=96:
            i=0
            k+=8
    return out

def get_hex(input_list):
    i=0
    header_file = open('image.h','ab')
    header_file.write('static const unsigned char BAW[] = {\n')
    for b in input_list:
        if i > 10:
            header_file.write('\n')
            i=0
        header_file.write(hex(b)+', ')
        i+=1
    header_file.write('};\n\n\n')

out=Image.open('LLb3NGi.png')
ll =encode(ImageOps.mirror(out.convert("L")))
jj=decode(ll)
jj.show()
print ll
get_hex(ll)
print str(len(ll))

