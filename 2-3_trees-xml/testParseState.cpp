/*
 * testParseState.cpp
 *
 * Unit tests for ParseState class
 *
 *  Created on: June 4, 2019
 *      Author: zeil
 */

#include "parseState.h"
#include "node.h"
#include "FlexLexer.h"
#include "scanner.h"

#include <vector>
#include <string>
#include <sstream>

#include "unittest.h"


using namespace std;



UnitTest(LexerOneElement)
{
	string inputData = "<data/>";
	istringstream input (inputData);
	yyFlexLexer scanner (&input);
	int tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo(inputData));
}

UnitTest(LexerElementWithText)
{
	string inputData = "<data>hello world</data>";
	istringstream input (inputData);
	yyFlexLexer scanner (&input);
	int tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("<data>"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TEXT));
	assertThat(lexeme, isEqualTo("hello world"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("</data>"));
}

UnitTest(LexerElementWithBrokenText)
{
	string inputData = "<data>hello\nworld</data>";
	istringstream input (inputData);
	yyFlexLexer scanner (&input);
	int tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("<data>"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TEXT));
	assertThat(lexeme, isEqualTo("hello\nworld"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("</data>"));
}

UnitTest(LexerElementWithSingleton)
{
	string inputData = "<data><omitted /></data>";
	istringstream input (inputData);
	yyFlexLexer scanner (&input);
	int tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("<data>"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("<omitted />"));

	tokenKind = scanner.yylex();
	assertThat(tokenKind, isEqualTo(TAG));
	assertThat(lexeme, isEqualTo("</data>"));
}




UnitTest (ParseStateOneSingleton) {
	ParseState ParseState;

	Node* n = ParseState.tag("<img src='foo.png' aligh='right'/>");
	assertThat (n, isNotNull());
	assertTrue(n->isAnElement);
	assertThat (n->label, isEqualTo("img"));
	assertThat (n->children.size(), isEqualTo(0));

	delete n;
}

UnitTest (ParseStateOneOpener) {
	ParseState ParseState;

	Node* n = ParseState.tag("<div class='title'>");
	assertThat (n, isNull());
}

UnitTest (ParseStateOpenerCloser) {
	ParseState ParseState;

	ParseState.tag("<div>");
	Node* n = ParseState.tag("</div>");
	assertTrue(n->isAnElement);
	assertThat (n->label, isEqualTo("div"));
	assertThat (n->children.size(), isEqualTo(0));

	delete n;
}

UnitTest (ParseStateOpenerTextCloser) {
	ParseState ParseState;

	ParseState.tag("<div>");
	ParseState.text("Hello");
	Node* n = ParseState.tag("</div>");
	assertTrue(n->isAnElement);
	assertThat (n->label, isEqualTo("div"));
	assertThat (n->children.size(), isEqualTo(1));

	Node* child = n->children[0];
	assertFalse(child->isAnElement);
	assertThat (child->label, isEqualTo("Hello"));
	assertThat (child->children.size(), isEqualTo(0));

	delete n;
}

