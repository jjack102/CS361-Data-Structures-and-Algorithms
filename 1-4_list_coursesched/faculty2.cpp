#include <cassert>
#include "faculty.h"
#include <list>

using namespace std;


bool constCheck (const Section&)
{
    return true;
}

bool constCheck (Section&)
{
    return false;
}


bool Faculty::sanityCheck() const
{
    const unsigned& n = numberOfSections;
    const list<Section> sects = sections;
    if (n > 1)
    {
        const_iterator start = begin();
        const_iterator next = start;
        ++next;
        while (next != end())
        {
            if (*next < *start)
                return false;
            start = next;
            next++;
        }
    }
    Faculty& fac = (Faculty&)(*this);
    Faculty::iterator iter = fac.begin();
    Section s;
    decltype(*iter) x = s;
    return constCheck(x);
}

