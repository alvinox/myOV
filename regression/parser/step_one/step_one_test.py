import sys
import os
import pdb

OVPATH = os.getenv('OVPATH')
import ov
import ov.front_end.lexer    as lexer
import ov.front_end.parser   as parser

#====================== Test Cases =====================================#
def test_parser():
    filename = OVPATH + "/designs/step_one/step_one.ov"

    l = lexer.Lexer()
    p = parser.Parser(start='design_definition')
    result = p.parse(filename, l.lexer)
    pdb.set_trace()

test_parser()