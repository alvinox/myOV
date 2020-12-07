import sys
import os
import pdb

OVPATH = os.getenv('OVPATH')
sys.path.append(OVPATH + "/thirdparty")

import ply.lex              as lex
import ov
import ov.front_end.logger  as logger
from   ov.util              import *

class Lexer():

    def __init__(self, debug = False):
        self.lexer = None
        self.debug = debug

        self._build(debug = self.debug, debuglog=logger.log)

    keywords = {
        'design' : "DESIGN",
        'func'   : "FUNC",
        'if'     : "IF",
        'const'  : "CONST",
    }

    tokens = [
        'ID',
        'INTEGER',
        'ADD',
        'SUB',
        'MUL',
        'DIV',

        'LT',
        'LE',
        'GT',
        'GE',
        'EQ',
        'NEQ',

        'RAND',
        'ROR',

        'COMMENT',
    ] + list(keywords.values())

    literals = [',', '.', ':', ';', '(', ')', '[', ']', '{', '}']


    t_ADD    = r'\+'
    t_SUB    = r'-'
    t_MUL    = r'\*'
    t_DIV    = r'/'

    t_LT     = r'\<'
    t_LE     = r'\<\='
    t_GT     = r'\>'
    t_GE     = r'\>\='
    t_EQ     = r'\=\='
    t_NEQ    = r'\!\='

    def t_ID(self, t):
        r'[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = Lexer.keywords.get(t.value, 'ID')
        return t

    def t_INTEGER(self, t):
        r'\d+'
        t.value = int(t.value)
        return t

    def t_COMMENT(self, t):
        r'\/\/.*'

    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    t_ignore = ' \t'

    def t_error(self, t):
        print("Illegal character '%s'" % t.value[0])
        t.lexer.skip(1)

    def tokenize(self, filename):
        text = readtext(filename)
        self.lexer.input(text)
        while True:
            tok = self.lexer.token()
            if not tok:
                break

            print(tok)

    def _build(self, **kwargs):
        self.lexer = lex.lex(module = self, **kwargs)
        self.lexer.lineno = 0
