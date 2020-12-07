import sys
import os
import pdb

OVPATH = os.getenv('OVPATH')
import ov
import ov.front_end.lexer    as lexer

#====================== Test Cases =====================================#
def test_lexer():
    filename = OVPATH + "/designs/step_one/step_one.ov"

    l = lexer.Lexer()
    l.tokenize(filename)

test_lexer()