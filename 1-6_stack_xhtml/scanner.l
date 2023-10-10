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
%x INCOMMENT ANCHOR HTMLTAG


/* regular definitions */

delim		[ \t\r\n]
tagdelim	[ \t\r\n\>]
whitespace	{delim}+
digit		[0-9]
alpha		[a-zA-Z]
nota		[b-zB-Z]
alphanum	[a-zA-Z0-9]
pathchars       [-~a-zA-Z0-9_/\\.]
number		{digit}+(\.{digit}+)?
quote           \"
apostrophe      [']
tagfill		.|{delim}
%%

{whitespace}		{}

<INITIAL>\<!--		{savedState = YY_START; BEGIN(INCOMMENT);}
<INITIAL>\<[aA][^a-zA-Z]		{BEGIN(ANCHOR);}

<INITIAL>\<{nota}{alphanum}*[^\>]*\>  {lexeme = yytext; return TAG;}
<INITIAL>\<[aA]{alphanum}+[^\>]*\>  {lexeme = yytext; return TAG;}
<INITIAL>\<[/]{alphanum}+[^\>]*\>  {lexeme = yytext; return TAG;}
<INITIAL>{alpha}+	{LEXEME; return WORD;}


<INCOMMENT>--\>	{BEGIN(savedState);}

<ANCHOR>[Nn][Aa][Mm][Ee]  {hrefMode = NAME;}
<ANCHOR>[Hh][Rr][Ee][Ff]  {hrefMode = LINK;}
<ANCHOR>\"[^\"]*\"		{LEXEME;
                         return hrefMode;}
<ANCHOR>\'[^\']*\'		{LEXEME;
                         return hrefMode;}
<ANCHOR>\>		{BEGIN(INITIAL);}

<<EOF>>			{return ENDOFFILE;}
.			{}

%%






