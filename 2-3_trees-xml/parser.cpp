#include "parser.h"
#include "parseState.h"
#include "node.h"
#include "FlexLexer.h"
#include "scanner.h"


using namespace std;

Node* Parser::parse(std::istream& input) const
{
    ParseState pstate;
    yyFlexLexer scanner (&input);
    int tokenKind = scanner.yylex();
    Node* root = nullptr;
    while (tokenKind != ENDOFFILE)
    {
        if (tokenKind == TAG)
        {
            root = pstate.tag(lexeme);
        } else if (tokenKind == TEXT)
        {
            pstate.text(lexeme);
        } else if (tokenKind == ERROR) {
            return nullptr;
        }
        tokenKind = scanner.yylex();
    }
    return root;
}