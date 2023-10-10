#ifndef EXTRACTION_H
#define EXTRACTION_H

#include <string>
#include "node.h"

/**
 * Find a node in an XML tree usign a subset of XPATH:
 *   /tag1[k1]/tag2[k2]/.../tagn[kn]
 * Each tagi is an XML tag name. The [ki] give an integer index indicating
 * which child with the given tag name should be selected. The "[ki]"  portion
 * may be omitted when ki==1.
 * 
 * @param root the root of the tree from which the selection should be made
 * @param xpath the path to follow in selectign the desired node.
 * @return the desired node from within the tree, or nullptr if no node matching
 *         the given path can be found.
 */
Node* selectByPath (Node* root, std::string xpath);

/**
 *  Given an XML (sub)tree, extract and concatenate the text leaves from
 *  that tree in the order they would be encountered in an XML listing,
 *  separating text from different leaf nodes by one or more blanks.
 * 
 * @param tree the root of the tree from which the text is to be extracted.
 */
std::string extractText(const Node* tree);

#endif
