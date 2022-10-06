#!/usr/bin/python

import random
import sys


with open("generator/fname.txt") as f:
    fnames = f.readlines()

with open("generator/lname.txt") as f:
    lnames = f.readlines()

with open("generator/zip.txt") as f:
    zip = f.readlines()



def generate_name_file(size, output_file):
    with open("data/" + output_file, "w") as f:
        for _ in range(size):
            f.write(random.choice(fnames).strip() + 
            "," + random.choice(lnames).strip() + 
            "," + random.choice(zip).strip() + ";\n")


generate_name_file(int(sys.argv[1]), sys.argv[2])