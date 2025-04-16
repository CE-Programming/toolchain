
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

if (len(file_data) < 10):
    print("Error: Output is empty")

with open(file_path, "wb") as file:
    file.write(file_data)

print("Finished")
