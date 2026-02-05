
# use this on the compiled graphy.c.src file

import os
import sys
import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()

print("Input file to strip")

file_path = filedialog.askopenfilename()

print("File Path: " + file_path)

if not file_path.endswith(".c.src"):
    print("Error: File extension must be \'.c.src\'")
    sys.exit()

with open(file_path, "rb") as file:
    file.seek(0, os.SEEK_END)
    file_length = file.tell()
    file.seek(0)
    if (file_length < 10):
        print("Error: File is empty")
        sys.exit()
    file_data = file.read()

file_data = file_data.replace(b"\tassume" , b";\tassume" )
file_data = file_data.replace(b"\textern" , b";\textern" )
file_data = file_data.replace(b"\tident"  , b";\tident"  )
file_data = file_data.replace(b"\tprivate", b";\tprivate")
file_data = file_data.replace(b"\tpublic" , b";\tpublic" )
file_data = file_data.replace(b"\tsection", b";\tsection")

file_data = file_data.replace(b"_gfy_", b"gfy_")
file_data = file_data.replace(b"_GFY_", b"GFY_")
file_data = file_data.replace(b"_lcd_", b"lcd_")

# This is the fun optimization section

# the dangerous one

file_data = file_data.replace(
    b"\n\tjp\t",
    b"\n\tjq\t",
)

# remove p m po pe

file_data = file_data.replace(
    b"\n\tjq\tp,",
    b"\n\tjp\tp,",
)

file_data = file_data.replace(
    b"\n\tjq\tm,",
    b"\n\tjp\tm,",
)

file_data = file_data.replace(
    b"\n\tjq\tpo,",
    b"\n\tjp\tpo,",
)

file_data = file_data.replace(
    b"\n\tjq\tpe,",
    b"\n\tjp\tpe,",
)

# common patterns

file_data = file_data.replace(
    b"\tsbc\ta, a\n\tbit\t0, a\n",
    b"\tsbc\ta, a\n",
)

# duplicate value register loads

file_data = file_data.replace(
    b"\tld\tbc, 0\n\tld\tiy, 0\n",
    b"\tld\tiy, 0\n\tlea\tbc, iy\n",
)

# destructive register loads

file_data = file_data.replace(
    b"\tpush\thl\n\tpop\tde\n\tld\thl,",
    b"\tex\tde, hl\n\tld\thl,",
)

file_data = file_data.replace(
    b"\tpush\thl\n\tpop\tde\n\tlea\thl,",
    b"\tex\tde, hl\n\tlea\thl,",
)

file_data = file_data.replace(
    b"\tld\tiy, 0\n\tlea\thl, iy\n\tld\tiy,",
    b"\tld\thl, 0\n\tld\tiy,",
)

# __ishl

file_data = file_data.replace(
    b"\tld\tc, 1\n\tcall\t__ishl\n",
    b"\tld\tc, 1\n\tadd\thl, hl\n"
)
file_data = file_data.replace(
    b"\tld\tc, 2\n\tcall\t__ishl\n",
    b"\tld\tc, 2\n\tadd\thl, hl\n\tadd\thl, hl\n"
)
file_data = file_data.replace(
    b"\tld\tc, 3\n\tcall\t__ishl\n",
    b"\tld\tc, 3\n\tadd\thl, hl\n\tadd\thl, hl\n\tadd\thl, hl\n"
)
file_data = file_data.replace(
    b"\tld\tc, 4\n\tcall\t__ishl\n",
    b"\tld\tc, 4\n\tadd\thl, hl\n\tadd\thl, hl\n\tadd\thl, hl\n\tadd\thl, hl\n"
)

# pop push __ishl

file_data = file_data.replace(
    b"\tld\tc, 1\n\tpush\tde\n\tpop\thl\n\tcall\t__ishl\n",
    b"\tld\tc, 1\n\tpush\tde\n\tpop\thl\n\tadd\thl, hl\n",
)

file_data = file_data.replace(
    b"\tld\tc, 1\n\tpush\tbc\n\tpop\thl\n\tcall\t__ishl\n",
    b"\tld\tc, 1\n\tpush\tbc\n\tpop\thl\n\tadd\thl, hl\n",
)

# other __ishl

file_data = file_data.replace(
    b"\tld\tc, 1\n\tlea\thl, iy\n\tcall\t__ishl\n",
    b"\tld\tc, 1\n\tlea\thl, iy\n\tadd\thl, hl\n",
)

# __bshl

file_data = file_data.replace(
    b"\tld\tb, 1\n\tcall\t__bshl\n",
    b"\tld\tb, 1\n\tadd\ta, a\n"
)

file_data = file_data.replace(
    b"\tld\tb, 2\n\tcall\t__bshl\n",
    b"\tld\tb, 2\n\tadd\ta, a\n\tadd\ta, a\n"
)

file_data = file_data.replace(
    b"\tld\tb, 3\n\tcall\t__bshl\n",
    b"\tld\tb, 3\n\tadd\ta, a\n\tadd\ta, a\n\tadd\ta, a\n"
)

file_data = file_data.replace(
    b"\tld\tb, 4\n\tcall\t__bshl\n",
    b"\tld\tb, 4\n\tadd\ta, a\n\tadd\ta, a\n\tadd\ta, a\n\tadd\ta, a\n"
)

file_data = file_data.replace(
    b"\tld\tb, 6\n\tcall\t__bshl\n",
    b"\tld\tb, 6\n\trrca\n\trrca\n\tand\ta, 192\n"
)

file_data = file_data.replace(
    b"\tld\tb, 7\n\tcall\t__bshl\n",
    b"\tld\tb, 7\n\trrca\n\tand\ta, 128\n"
)

# __bshru

file_data = file_data.replace(
    b"\tld\tb, 1\n\tcall\t__bshru\n",
    b"\tld\tb, 1\n\tsrl\ta\n"
)

file_data = file_data.replace(
    b"\tld\tb, 2\n\tcall\t__bshru\n",
    b"\tld\tb, 2\n\tsrl\ta\n\tsrl\ta\n"
)

file_data = file_data.replace(
    b"\tld\tb, 6\n\tcall\t__bshru\n",
    b"\tld\tb, 6\n\trlca\n\trlca\n\tand\ta, 3\n"
)

file_data = file_data.replace(
    b"\tld\tb, 7\n\tcall\t__bshru\n",
    b"\tld\tb, 7\n\trlca\n\tand\ta, 1\n"
)

# __bshrs

file_data = file_data.replace(
    b"\tld\tb, 1\n\tcall\t__bshrs\n",
    b"\tld\tb, 1\n\tsra\ta\n"
)

file_data = file_data.replace(
    b"\tld\tb, 2\n\tcall\t__bshrs\n",
    b"\tld\tb, 2\n\tsra\ta\n\tsra\ta\n"
)

file_data = file_data.replace(
    b"\tld\tb, 7\n\tcall\t__bshrs\n",
    b"\tld\tb, 7\n\trlca\n\tsbc\ta, a\n"
)

# __iand

file_data = file_data.replace(
    b"\tld\tbc, 65535\n\tcall\t__iand\n",
    b"\tld\tbc, 65535\n\tinc\thl\n\tdec.s\thl\n"
)

file_data = file_data.replace(
    b"\tld\tbc, 255\n\tcall\t__iand\n",
    b"\tld\tbc, 255\n\tinc\thl\n\tdec.s\thl\n\tld\th, b\n"
)

# __imulu

file_data = file_data.replace(
    b"\tld\tbc, 3\n\tcall\t__imulu\n",
    b"\tpush\thl\n\tpop\tbc\n\tadd\thl, bc\n\tadd\thl, bc\n\tld\tbc, 3\n"
)

# targetted __imulu

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tcall\t__imulu\n",
    b"\tcall\t__set_bc_and_mul_hl_by_240\n"
)

# __imulu cleanup

file_data = file_data.replace(
    b"\tld\tbc, 3\n\tpush\thl\n\tpop\tbc\n",
    b"\tpush\thl\n\tpop\tbc\n",
)

file_data = file_data.replace(
    b"\tpush\tbc\n\tpop\thl\n\tpush\thl\n\tpop\tbc\n",
    b"\tpush\tbc\n\tpop\thl\n",
)

if (len(file_data) < 10):
    print("Error: Output is empty")


with open(file_path, "wb") as file:
    file.write(file_data)

print("Finished")
