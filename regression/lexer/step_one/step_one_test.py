import sys
import os
import pdb

OVPATH = os.getenv('OVPATH')
sys.path.append(OVPATH + "/thirdparty")

import ply.lex as lex

# pdb.set_trace()
# Build the lexer
# lexer = lex.lex()


#====================== Test Cases =====================================#
def test_aa():
    assert 0 != 1
