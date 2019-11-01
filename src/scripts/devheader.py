#!/usr/bin/env python3

from pyclibrary import CParser

libraries = ['graphx', 'fileioc', 'keypadc', 'fontlibc']

byte1 = ["char", "signed char", "unsigned char", "uint8_t", "int8_t", "srl_error_t"]
byte2 = ["short", "signed short", "unsigned short", "uint16_t", "int16_t"]
byte3 = ["int", "signed int", "unsigned int", "unsigned", "uint24_t", "int24_t", "gfx_location_t", "fontlib_load_options_t", "usb_error_t", "msd_error_t", "fat_error_t"]
byte4 = ["long", "signed long", "unsigned long", "uint32_t", "int32_t"]
byte8 = ["long long", "signed long long", "unsigned long long", "uint64_t", "int64_t"]
bytefloat = ["float"]
bytedouble = ["double"]

def get_bytes_type(param):
    ret = 0
    if param in byte1:
        ret = 1
    if param in byte2:
        ret = 2
    if param in byte3:
        ret = 3
    if param in byte4:
        ret = 4
    if param in byte8:
        ret = 8
    if param in bytefloat:
        ret = 64
    if param in bytedouble:
        ret = 65
    return ret

def create_dev_file(name):
    path = '../' + name.lower() + '/' + name.lower() + '.h'
    devpath = '../' + name.lower() + '/' + name.lower() + '-dev.asm'
    libpath = '../' + name.lower() + '/' + name.lower() + '.lib'
    funcnames = []

    '''
    Determine order of functions
    '''
    libfile = open(libpath, 'r')
    libfile.readline()
    line = libfile.readline().strip()

    while line:
        columns = line.split()
        funcnames.append(columns[1])
        line = libfile.readline().strip()

    devfile = open(devpath, 'w')
    parser = CParser([path])
    functions = parser.defs['functions']
    devfile.write('lib_%s:\n' % name.lower())
    devfile.write('\tdb "%s",0 ; library name\n' % name.upper())
    devfile.write('\tdb %d ; number of functions\n' % len(funcnames))
    index = 0
    for i in range(len(funcnames)):

        try:
            ret = functions[funcnames[i]][0]
            params = functions[funcnames[i]][1]
        except:
            print('no function prototype: ', funcnames[i])
            ret = []
            params = []

        '''
        Parse return value
        '''
        retvalue = 0
        if len(ret) > 0:
            retvalue = get_bytes_type(ret[0])
        if len(ret) > 1:
            if ret[1] == "*":
                retvalue = 131
        devfile.write('\tdb %d ; return value (%s [%d])\n' % (retvalue, funcnames[i], index))

        '''
        Parse parameters
        '''
        if len(params) == 0 or (len(params) == 1 and str(params[0][1][0]) == "void"):
            devfile.write('\tdb 0 ; num params\n')
            devfile.write('\tdb 0,')
        else:
            devfile.write('\tdb %d ; num params\n' % len(params))
            devfile.write('\tdb ')
            for arg in params:
                if len(arg[1]) > 0:
                    argvalue = get_bytes_type(arg[1][0])
                if len(arg[1]) > 1:
                    if arg[1][1] == "*":
                        argvalue = 131
                devfile.write('%d,' % argvalue)
        for i in range(1, 14 - len(params)):
            devfile.write('0,')
        devfile.write('0\n')

        index += 3

    devfile.close()

for lib in libraries:
    create_dev_file(lib)

'''
Create concatenated library file
Convert with fasmg
'''
def append_dev_file(name):
    devpath = '../' + name.lower() + '/' + name.lower() + '-dev.asm'
    f = open(devpath, "r")
    devlibrary.write(f.read())
    f.close()

devlibrary = open('devlibs.asm', 'w')
devlibrary.write('include \'../include/ez80.inc\'\n')
devlibrary.write('include \'../include/ti84pceg.inc\'\n')
devlibrary.write('include \'../include/tiformat.inc\'\n')
devlibrary.write('format ti archived appvar \'DEVLIBS\'\n')
devlibrary.write('\n')
devlibrary.write('\tdb "DEVLIBS",0\n')
for lib in libraries:
    devlibrary.write('\tdl lib_%s\n' % lib.lower())
for lib in libraries:
    append_dev_file(lib)
devlibrary.write('\tdl 0\n')
devlibrary.close()
