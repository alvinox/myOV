#include "Util.h"

std::string Indent(unsigned lv) {
  std::string indent;
  for (unsigned i = 0; i < lv; i++) {
    indent += "  ";
  }
  return indent;
}