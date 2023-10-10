#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include "node.h"

class Parser {
public:
    Node* parse(std::istream& input) const;
};


#endif
