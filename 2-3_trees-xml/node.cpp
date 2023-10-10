#include "node.h"

using namespace std;

/**
     * Create a node containing either an element (with no children) 
     * or a leaf with the given tag name/leaf content.
     * 
     * @param elementq true iff this is to be an element
     * @param content the tag name or leaf content
     */
Node::Node(bool elementq, std::string content)
    : isAnElement(elementq), label(content)
{
}

Node::~Node()
{
    for (Node *child : children)
    {
        delete child;
    }
}
