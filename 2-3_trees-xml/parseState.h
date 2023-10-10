#ifndef ParseState_H
#define ParseState_H


#include <list>
#include <stack>
#include <string>

#include "node.h"

/**
 * XHTML ParseState class
 */
class ParseState {
public:
	/**
	 * Create a new ParseState.
	 */
	ParseState();

	/**
	 * Present a tag to the ParseState.  If this is a closing tag,
	 * return a tree node representing the parsed HTML for the
	 * corresponding element
	 *
	 * @param atag the lexeme (full string text) of a tag.
	 * @return a tree node or null if this is not a closing tag
	 */
	Node* tag (std::string atag);

	/**
	 * Present a text string to the ParseState.  If the ParseState
	 * is nto inside an HTML element, this is ignored.
	 * Otherwise it is remembered as a child of the current element.
	 *
	 * @param textContent the lexeme of a text string within an HTML element.
	 */
	void text (std::string textContent);

	/**
	 * Inquire as to the balance status ofthe tags seen so far.
	 *
	 * @return 1 if all opening tags seen so far have been properly matched by
	 *           a closing tag
	 *
	 *         0 if no mismatches have been detected, but at least one opening tag
	 *            seen so far has not been properly matched by a closing tag
	 *
	 *         -1 if we have seen at least one instance of a closing tag that
	 *            did not match the most recently added and unmatched opening tag.
	 */
	int status () const;

private:
	bool error;
	std::stack<Node*, std::list<Node*> > ParseStateStack;
};



#endif
