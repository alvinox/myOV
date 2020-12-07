import sys
import os
import pdb

OVPATH = os.getenv('OVPATH')
sys.path.append(OVPATH + "/thirdparty")

import ply.yacc as yacc

import ov
import ov.front_end.lexer   as lexer
import ov.front_end.logger  as logger
from   ov.util              import *

class Node():
    pass

class Module(Node):
    def __init__(self):
        self.statements = []

class DesignDefinition(Node):
    def __init__(self, name):
        self.name = name

class Parser():

    tokens = lexer.Lexer.tokens

    start = 'definition_statements'

    def __init__(self, debug = False, start = None):
        self.parser = None
        self.module = Module()

        self.debug  = debug
        self.start  = Parser.start if start is None else start

        if self.debug:
            self._build(debug = self.debug, debuglog = logger.log, start = self.start)
        else:
            self._build(start = self.start)

    def p_definition_statements(self, p):
        '''
            definition_statements : definition_statement
                                  | definition_statements definition_statement
        '''
        stm = p[1]
        if len(p) == 3:
            stm = p[2]
        self.module.statements.append(stm)

    def p_definition_statement(self, p):
        '''
            definition_statement  : design_definition
        '''
        p[0] = p[1]

    def p_design_definition(self, p):
        '''
            design_definition : DESIGN ID '{' '}'
        '''
        p[0] = DesignDefinition(p[2])

    def _build(self, **kwargs):
        self.parser = yacc.yacc(module = self, **kwargs)
    
    def parse(self, filename, lexer):
        text = readtext(filename)
        root = self.parser.parse(input = text, lexer = lexer, debug = self.debug)
        return root