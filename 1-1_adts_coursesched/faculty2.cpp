#include <cassert>
#include "faculty.h"

using namespace std;




bool Faculty::sanityCheck() const
{
    const unsigned& n = numberOfSections;
    using Array = const Section*;
    const Array& sects = sections;
    if (n > 1)
    {
        for (unsigned i = 0; i < n-1; ++i)
        {
            if (sects[i+1] < sects[i])
                return false;
        }
    }
    return true;
}

