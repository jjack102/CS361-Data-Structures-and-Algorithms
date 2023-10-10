%option noyywrap

%{

#include <fstream>
#include "scanner.h"

using namespace std;

  int savedState, hrefMode;
  std::string lexeme;

 
#undef ECHO 
//#define ECHO cerr << yytext << flush;
#define ECHO

#undef LEXEME
#define LEXEME lexeme = yytext; 

int yy_more_offset, yy_prev_more_offset;



%}
%x INCOMMENT HTMLTAG


/* regular definitions */

delim		[ \t\r\n]
tagdelim	[ \t\r\n\>]
whitespace	{delim}+
digit		[0-9]
alpha		[a-zA-Z]
nota		[b-zB-Z]
alphanum	[a-zA-Z0-9]
tagchars	[a-zA-Z0-9:]
pathchars       [-~a-zA-Z0-9_/\\.]
number		{digit}+(\.{digit}+)?
quote           \"
apostrophe      [']
htmltext		[^<>]|[ \t\r\n]
%%

{whitespace}		{}

<INITIAL>\<!--		{savedState = YY_START; BEGIN(INCOMMENT);}

<INITIAL>\<{alpha}{tagchars}*[^\>]*\>  {lexeme = yytext; return TAG;}
<INITIAL>\<{alpha}{tagchars}*[^\>]*/\>  {lexeme = yytext; return TAG;}
<INITIAL>\<[/]{tagchars}+[^\>]*\>  {lexeme = yytext; return TAG;}
<INITIAL>{htmltext}+	{LEXEME; return TEXT;}

<INCOMMENT>.	{}
<INCOMMENT>--\>	{BEGIN(savedState);}


<<EOF>>			{return ENDOFFILE;}
.			{}

%%






