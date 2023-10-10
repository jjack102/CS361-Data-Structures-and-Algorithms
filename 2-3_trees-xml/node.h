#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

struct Node {
    /**
     * true if this node represents an HTML element, false if
     * it is a text string (leaf)
     * */
    bool isAnElement;

    /**
     * If isAnElement, contains the tag name of the element.
     * If !isAnEelement, contains the text string of a leaf.
     */
    std::string label; 

    /**
     * If isAnElement, contains pointers to the children of this element.
     * If !isAnEelement, this is empty and unused.
     */
    std::vector<Node*> children; 

    /**
     * Create a node containing either an element (with no children) 
     * or a leaf with the given tag name/leaf content.
     * 
     * @param elementq true iff this is to be an element
     * @param content the tag name or leaf content
     */
    Node(bool elementq, std::string content);

    ~Node();
};

#endif
