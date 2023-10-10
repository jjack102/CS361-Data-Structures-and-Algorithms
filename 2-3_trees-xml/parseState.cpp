#include "parseState.h"

using namespace std;

ParseState::ParseState()
	: error(false)
{
}

/**
	 * Present a text string to the ParseState.  If the ParseState
	 * is nto inside an HTML element, this is ignored.
	 * Otherwise it is remembered as a child of the current element.
	 *
	 * @param textContent the lexeme of a text string within an HTML element.
	 */
void ParseState::text(std::string textContent)
{
	if (!ParseStateStack.empty())
	{
		Node* n = new Node(false, textContent);
		ParseStateStack.top()->children.push_back(n);
	}
}

Node *ParseState::tag(std::string atag)
{
	if (error)
		return nullptr;
	if (atag[1] == '/')
	{
		// This is a closing tag.
		string::size_type start = atag.find_first_not_of(' ', 2);
		string::size_type stop = atag.find_first_of(" >", start);
		string tagName = atag.substr(start, stop - start);
		if (ParseStateStack.empty() || tagName != ParseStateStack.top()->label)
		{
			error = true;
		}
		else
		{
			Node *n = ParseStateStack.top();
			ParseStateStack.pop();
			if (!ParseStateStack.empty())
			{
				ParseStateStack.top()->children.push_back(n);
			}
			return n;
		}
	}
	else if (atag[atag.size() - 2] != '/')
	{
		// This is an opening tag;
		string::size_type start = atag.find_first_not_of(' ', 1);
		string::size_type stop = atag.find_first_of(" >", start);
		string tagName = atag.substr(start, stop - start);
		ParseStateStack.push(new Node(true, tagName));
	}
	else
	{
		// This is a singleton tag.
		string::size_type start = atag.find_first_not_of(' ', 1);
		string::size_type stop = atag.find_first_of(" />", start);
		string tagName = atag.substr(start, stop - start);
		Node *n = new Node(true, tagName);
		if (!ParseStateStack.empty())
		{
			ParseStateStack.top()->children.push_back(n);
		}
		return n;
	}
	return nullptr;
}

int ParseState::status() const
{
	if (error)
		return -1;
	else if (ParseStateStack.empty())
		return 1;
	else
		return 0;
}
