#ifndef SCANNER_H
#define SCANNER_H

#include <string>

extern std::string lexeme;

// token kinds
const int ENDOFFILE = 0;
const int WORD = 1;
const int LINK = 2;
const int NAME = 3;
const int TAG = 4;
const int ERROR = -1;


#endif
