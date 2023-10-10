/*
 * testExtractor.cpp
 *
 * Unit tests for class Parser
 *
 *      Author: zeil
 */

#include "parser.h"
#include "node.h"

#include <string>
#include <sstream>

#include "unittest.h"


using namespace std;

 

// Render a tree in s-expression format
string sexp(const Node* t)
{
	if (t == nullptr)
	    return "";
	string result = "(" + t->label;
	for (const Node* child: t->children)
	{
		result += sexp(child);
	}
	result += ')';
	return result;
}

UnitTest(ParserSimple)
{
	string inputData = "<html><head><title>T</title></head><body><h1>T</h1><p>Hello</p><br/><p>World!</p></body></html>";
	istringstream input (inputData);
	Parser parser;
	Node* root = parser.parse(input);
	assertNotNull(root);
	assertThat(root->label, isEqualTo("html"));
	assertThat(root->children.size(), isEqualTo(2));
	assertThat(sexp(root), isEqualTo("(html(head(title(T)))(body(h1(T))(p(Hello))(br)(p(World!))))"));
}

UnitTest(ParserIgnoreAtrributes)
{
	string inputData = "<html><head><title>T</title></head><body><h1 class='header'>T</h1><p>Hello</p><br/><p>World!</p><!-- comment --></body></html>";
	istringstream input (inputData);
	Parser parser;
	Node* root = parser.parse(input);
	assertNotNull(root);
	assertThat(root->label, isEqualTo("html"));
	assertThat(root->children.size(), isEqualTo(2));
	Node* n = root->children[1]->children[0]; // h1
	assertThat(n->label, isEqualTo("h1"));
	assertThat(sexp(root), isEqualTo("(html(head(title(T)))(body(h1(T))(p(Hello))(br)(p(World!))))"));
}



UnitTest(ParserIgnoreWS)
{
	string inputData = "<html>\n<head>   <title>T</title>\n</head>\n<body>\n<h1>T</h1>\n<p>Hello</p><br/><p>World!</p>\n</body></html>";
	istringstream input (inputData);
	Parser parser;
	Node* root = parser.parse(input);
	assertNotNull(root);
	assertThat(root->label, isEqualTo("html"));
	assertThat(root->children.size(), isEqualTo(2));
	assertThat(sexp(root), isEqualTo("(html(head(title(T)))(body(h1(T))(p(Hello))(br)(p(World!))))"));
}

UnitTest(ParserIgnoreComments)
{
	string inputData = "<html><head><title>T</title></head><body><!-- comment --><h1>T</h1><p>Hello</p><br/><p>World!</p><!-- comment --></body></html>";
	istringstream input (inputData);
	Parser parser;
	Node* root = parser.parse(input);
	assertNotNull(root);
	assertThat(root->label, isEqualTo("html"));
	assertThat(root->children.size(), isEqualTo(2));
	assertThat(sexp(root), isEqualTo("(html(head(title(T)))(body(h1(T))(p(Hello))(br)(p(World!))))"));
}
