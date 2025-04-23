
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

# __iand

file_data = file_data.replace(
    b"\tld\tbc, 255\n\tcall\t__iand\n",
    b"\tld\tbc, 255\n\tinc.s\thl\n\tdec\thl\n\tld\th, b\n"
)


# __land

file_data = file_data.replace(
    b"\tld\tbc, 255\n\txor\ta, a\n\tcall\t__land\n",
    b"\tld\tbc, 255\n\t\n\txor\ta, a\n\tinc.s\thl\n\tdec\thl\n\tld\th, b\n\tld\te, b\n"
)

# __imulu

file_data = file_data.replace(
    b"\tld\tbc, 3\n\tcall\t__imulu\n",
    b"\tpush\thl\n\tpop\tbc\n\tadd\thl, bc\n\tadd\thl, bc\n\tld\tbc, 3\n"
)

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tcall\t__imulu\n",
    b"\tcall\t__set_bc_and_mul_hl_by_240\n"
)

file_data = file_data.replace(
    b"\tld\tbc, -2\n\tcall\t__imulu\n",
    b"\tcall\t__set_bc_and_mul_hl_by_minus2\n"
)

# targetted

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tld\tde, 0\n\tld\te, (ix + 12)\n\tadd\tiy, de\n\tcall\t__imulu\n",
    b"\tld\tde, 0\n\tld\te, (ix + 12)\n\tadd\tiy, de\n\tcall\t__set_bc_and_mul_hl_by_240\n"
)

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tadd\tiy, de\n\tld\thl, (ix - 9)\n\tcall\t__imulu\n",
    b"\tadd\tiy, de\n\tld\thl, (ix - 9)\n\tcall\t__set_bc_and_mul_hl_by_240\n"
)

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tadd\tiy, de\n\tld\thl, (ix - 12)\n\tcall\t__imulu\n",
    b"\tadd\tiy, de\n\tld\thl, (ix - 12)\n\tcall\t__set_bc_and_mul_hl_by_240\n"
)

file_data = file_data.replace(
    b"\tld\tbc, 240\n\tld\ta, e\n\tld\tde, 0\n\tld\te, (ix + 12)\n\tadd\tiy, de\n\tcall\t__imulu\n",
    b"\tld\ta, e\n\tld\tde, 0\n\tld\te, (ix + 12)\n\tadd\tiy, de\n\tcall\t__set_bc_and_mul_hl_by_240\n"
)

file_data = file_data.replace(
    b"\tld\tde, 240\n\tpush\tbc\n\tpop\tiy\n\tpush\thl\n\tpop\tbc\n\tadd\tiy, bc\n\tld\thl, (ix + 9)\n\tpush\tde\n\tpop\tbc\n\tcall\t__imulu\n",
    b"\t\n\tpush\tbc\n\tpop\tiy\n\tpush\thl\n\tpop\tbc\n\tadd\tiy, bc\n\tld\thl, (ix + 9)\n\tcall\t__set_bc_and_mul_hl_by_240\n"
)

# targetted second pass

file_data = file_data.replace(
    b"\tcall\t__set_bc_and_mul_hl_by_240\n\tpush\thl\n\tpop\tde\n\tadd\tiy, de\n\tlea\thl, iy\n",
    b"\tcall\t__set_bc_and_mul_hl_by_240\n\tex\tde, hl\n\tadd\tiy, de\n\tlea\thl, iy\n"
)

file_data = file_data.replace(
    b"\tcall\t__set_bc_and_mul_hl_by_240\n\tpush\thl\n\tpop\tde\n\tlea\thl, iy\n\tadd\thl, de\n",
    b"\tcall\t__set_bc_and_mul_hl_by_240\n\tex\tde, hl\n\tlea\thl, iy\n\tadd\thl, de\n"
)

if (len(file_data) < 10):
    print("Error: Output is empty")


with open(file_path, "wb") as file:
    file.write(file_data)

print("Finished")
