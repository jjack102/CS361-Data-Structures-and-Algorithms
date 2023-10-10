#include "balancer.h"

using namespace std;


Balancer::Balancer() 
: error(false), tagStack()
{

}

void Balancer::tag (std::string aTag) {
    if(aTag.empty()) {
        return;
    }

    // Find the first tag in the string
    size_t tagStart = aTag.find('<');
    size_t tagEnd = aTag.find('>', tagStart);

    if(tagStart == string::npos || tagEnd == string::npos) {
        return;
    }

    // Process the tag
    if(aTag.at(tagStart+1) == '/') {        // Closing tag
        
        // Pop the corresponding opening tag from the stack
        string tagName = aTag.substr(tagStart +2, tagEnd - tagStart -2);
        tagName = tagName.substr(0, tagName.find(' '));
        if(!tagStack.empty() && tagStack.top() == tagName) {
            tagStack.pop();  
        }
        else
        {
            error = true;
            return;
        }

    } 
    else if(aTag.at(tagEnd-1) == '/') {     // singleton tag
        // ignore
    }
    else {                                  // opening tag

        // Push the tag onto the stack
        string tagName = aTag.substr(tagStart +1, tagEnd - tagStart -1);
        tagName = tagName.substr(0, tagName.find(' '));
        tagStack.push(tagName);
    }

    // Recursively process the rest of the string after the current tag
    string remaining = aTag.substr(tagEnd + 1);
    tag(remaining);

}

int Balancer::status () const {

    if(error == true) {
        return -1;
    }
    else if(!tagStack.empty()) {
        return 0;
    }
    else {
        return 1;
    }
}
