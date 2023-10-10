/*
 * testExtraction.cpp
 *
 * Unit tests for Extraction Functions
 *
 *      Author: zeil
 */

#include "extraction.h"
#include "parser.h"
#include "node.h"

#include <algorithm>
#include <string>
#include <sstream>

#include "unittest.h"


using namespace std;

Node* root;

void setup()
{
	string inputData = "<html><head><title>T</title></head><body><h1>T</h1><div><p>Hello</p><br/><p>World!</p></div></body></html>";
	istringstream input (inputData);
	Parser parser;
	root = parser.parse(input);
}

void cleanup()
{
	delete root;
}


UnitTest(SelectByPathBasic)
{
	setup();
	Node* n = selectByPath(root, "/html");
	assertThat(n, isEqualTo(n));
	n = selectByPath(root, "/html/body");
	assertThat(n, isEqualTo(root->children[1]));
	n = selectByPath(root, "/html/p");
	assertThat(n, isEqualTo((Node*)nullptr));
	cleanup();
}

UnitTest(SelectByPathIndices)
{
	setup();
	Node* n = selectByPath(root, "/html[1]");
	assertThat(n, isEqualTo(n));
	n = selectByPath(root, "/html[1]/body[1]");
	assertThat(n, isEqualTo(root->children[1]));
	n = selectByPath(root, "/html/body[0]");
	assertThat(n, isEqualTo((Node*)nullptr));
	n = selectByPath(root, "/html/body[2]");
	assertThat(n, isEqualTo((Node*)nullptr));
	n = selectByPath(root, "/html[1]/body[1]/div/p[1]");
	assertThat(n, isEqualTo(root->children[1]->children[1]->children[0]));
	n = selectByPath(root, "/html[1]/body[1]/div/p[2]");
	assertThat(n, isEqualTo(root->children[1]->children[1]->children[2]));
	cleanup();
}


UnitTest(ExtractSingleNodes)
{
	setup();
	const Node* n = root->children[1]->children[1]->children[0]; // first <p>
	string text = extractText(n);
	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	assertThat(text, isEqualTo("Hello"));
	cleanup();
}

UnitTest(ExtractEmpty)
{
	setup();
	Node* n = nullptr;
	string text = extractText(n);
	assertThat(text, isEqualTo(""));
	cleanup();
}


UnitTest(ExtractMultipleNodes)
{
	setup();
	const Node* n = root->children[1]->children[1]; // <div>
	string text = extractText(n);
	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	assertThat(text, isEqualTo("HelloWorld!"));
	cleanup();
}

UnitTest(ExtractMultipleLevels)
{
	setup();
	Node* n = root->children[1]; // <body>
	string text = extractText(n);
	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	assertThat(text, isEqualTo("THelloWorld!"));

	text = extractText(root);
	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	assertThat(text, isEqualTo("TTHelloWorld!"));
	cleanup();
}