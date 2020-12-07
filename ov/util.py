import pdb

def readtext(filename):
    with open(filename, "rt") as fin:
        text = fin.read()

    return text