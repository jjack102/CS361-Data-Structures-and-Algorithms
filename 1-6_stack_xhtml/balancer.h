#ifndef BALANCER_H
#define BALANCER_H


#include <list>
#include <stack>
#include <string>
#include <iostream>

/**
 * XHTML Balancer class
 */
class Balancer {
public:
	/**
	 * Create a new balancer.
	 */
	Balancer();

	/**
	 * Process a new tag.
	 *
	 * @param aTag the lexeme (full string text) of a tag.
	 */
	void tag (std::string aTag);

	/**
	 * Inquire as to the balance status of the tags seen so far.
	 *
	 * @return 1 if all opening tags seen so far have been properly matched by
	 *           a closing tag
	 *
	 *         0 if no mismatches have been detected, but at least one opening tag
	 *            seen so far has not been properly matched by a closing tag
	 *
	 *         -1 if we have seen at least one instance of a closing tag that
	 *            did not match the most recently added and unmatched opening tag.
	 *            Note that once a -1 has been returned, all subsequent calls to
	 *            status() must return -1, no matter what additional tags are added.
	 */
	int status () const;

private:
	bool error; ///< true iff a mismatch has been seen since this object was created
	std::stack<std::string, std::list<std::string> > tagStack;
};



#endif
