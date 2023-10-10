#include "extraction.h"
#include <algorithm>
#include <vector>
#include <string>

#include <iostream>

using namespace std;

/**
 * Examine an xpath step of the form "/tagName[k]" and pull out the tagname
 * and index. The index part may be omitted, in which case it is assumed to
 * be 1.
 * 
 * @param xpathStep the string containing one step in an xpath.
 * @param tagName the tag name that must be matched in the step (output)
 * @param index the index of the desired child with that tagName (output)
 */
void interpretXPathStep(string xpathStep, string &tagName, unsigned &index)
{
    index = 1;
    tagName = xpathStep;
    if (tagName.size() > 0 && tagName[0] == '/') {
      tagName = tagName.substr(1); // discard the '/'
    }
    string::size_type indexStart = xpathStep.find('[');
    if (indexStart != string::npos)
    {
      string::size_type indexStop = xpathStep.find(']');
      index = stoi(xpathStep.substr(indexStart + 1, indexStop - indexStart - 1));
      tagName = tagName.substr(0, indexStart);
    }
}

/**
 * Find a node in an XML tree usign a subset of XPATH:
 *   /tag1[k1]/tag2[k2]/.../tagn[kn]
 * Each tagi is an XML tag name. The [ki] give an integer index indicating
 * which child with the given tag name should be selected. The "[ki]"  portion
 * may be omitted when ki==1.
 * 
 * @param root the root of the tree from which the selection should be made
 * @param xpath the path to follow in selecting the desired node.
 * @return the desired node from within the tree, or nullptr if no node matching
 *         the given path can be found.
 */
Node *selectByPath(Node *root, std::string xpath)
{
  if(xpath.empty() || !root) {
    return nullptr;
  }

  //Divide the path into steps at each '/' 
  // store in a vector
  std::vector<std::string> steps;
  string::size_type start = 0;
  while (start != std::string::npos) {
    string::size_type stop = xpath.find('/', start + 1);
    steps.push_back(xpath.substr(start, stop - start));
    //cout << xpath.substr(start, stop - start) << " ";
    start = stop;
  }  
 
  Node *curr = root;
  bool foundChild = false;
  for(const auto& step : steps) {
    string tagName;
    unsigned index;
    interpretXPathStep(step, tagName, index);
    //cout << step << " " << tagName << " " << index << " ";

    for(Node *child : curr->children) {
      if(child->label == tagName) {
        if(index == 1) {
          curr = child;
          foundChild = true;
          break;
        }
        else {
          --index;
        }

      }
    }

  }

  if(!foundChild) {
    return nullptr;
  }

  return curr;
}

/**
 *  Given an XML (sub)tree, extract and concatenate the text leaves from
 *  that tree in the order they would be encountered in an XML listing,
 *  separating text from different leaf nodes by one or more blanks.
 * 
 * @param tree the root of the tree from which the text is to be extracted.
 */
std::string extractText(const Node *tree)
{
  //*** To be implemented
  string result;

  if(tree == nullptr){
    return result;
  }

  if(!tree->isAnElement) 
  {
    result = tree->label;
  }

  for(Node *child : tree->children)
  {
    result += " " + extractText(child);
  }
  
  return result;
}
