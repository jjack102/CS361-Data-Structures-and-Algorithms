#include <algorithm>
#include <fstream>
#include <stack>
#include <list>

#include "node.h"
#include "parser.h"
#include "extraction.h"

using namespace std;

string formatted(string text)
{
	// normalize whitespace
	string result;
	char lastChar = ' ';
	for (char c : text)
	{
		if (c == ' ' || c == '\r' || c == '\n' || c == '\t')
		{
			if (lastChar != ' ')
			{
				result += ' ';
				lastChar = ' ';
			}
		}
		else
		{
			result += c;
			lastChar = c;
		}
	}
	if (result.size() > 0 && lastChar == ' ')
	{
		result.erase(result.end() - 1);
	}
	// Break lines that would exceeed 80 characters
	string::size_type lineLength = 0;
	string::size_type pos = 0;
	string::size_type lastBlankPos = string::npos;
	while (pos < result.size())
	{
		if (lineLength > 80 && lastBlankPos != string::npos)
		{
			result[lastBlankPos] = '\n';
			lineLength = pos - lastBlankPos + 1;
			lastBlankPos = string::npos;
		}
		else if (result[pos] == ' ')
		{
			lastBlankPos = pos;
			++lineLength;
			++pos;
		}
		else
		{
			++lineLength;
			++pos;
		}
	}
	if (lineLength > 80 && lastBlankPos != string::npos)
	{
		result[lastBlankPos] = '\n';
	}
	return result;
}

/**
 * Run this as:
 *    xmlextract xmlFile xpath
 */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cerr << "usage:\n   " << argv[0] << " xmlfile xpath" << endl;
		return 1;
	}

	string fileName = argv[1];
	string xpath = argv[2];

	ifstream xmlInput(fileName);
	Node *root = Parser().parse(xmlInput);
	xmlInput.close();

	if (root == nullptr)
	{
		cout << fileName << " could not be parsed as XML." << endl;
		return 1;
	}

	Node *selected = selectByPath(root, xpath);
	if (selected == nullptr)
	{
		cout << xpath << " did not find a node in " << fileName << endl;
		return 2;
	}

	string text = extractText(selected);
	cout << formatted(text) << endl;
	return 0;
}
