import os
header_file = open('out.h','wb')

def getsubs(dir):
    # get all
    dirs = []
    files = []
    for dirname, dirnames, filenames in os.walk(dir):
        dirs.append(dirname)
        for subdirname in dirnames:
            dirs.append(os.path.join(dirname, subdirname))
        for filename in filenames:
            files.append(os.path.join(dirname, filename))
    return files

def get_hex(file_name):
	'''buffer_hex = []'''
	name_file= file_name.split('/')[1]

	app_file = open(file_name,'rb')
	header_file.write('static const unsigned char '+ name_file+'[] = {\n')
	for b in app_file.read():
		'''buffer_hex.append(int(b.encode('hex'), 16))'''
		header_file.write(hex(int(b.encode('hex'), 16))+', ')
	header_file.write('};\n\n\n')
	
for i in getsubs('.'):
	get_hex(i);
