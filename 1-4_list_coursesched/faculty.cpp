#include <cassert>
#include "faculty.h"

using namespace std;


/**
   * Construct a Faculty object with empty name and no course sections.
   */
Faculty::Faculty()
: name(), numberOfSections(0), sections()
{
}

/**
   * Construct a faculty member with the given name and no course sections.
   * 
   * @param theName  name to give to this faculty member
   */
Faculty::Faculty(std::string theName)
: name(theName), numberOfSections(0), sections()
{
}


Faculty::Faculty(std::string theName, std::initializer_list<Section> sections)
: name(theName), numberOfSections(0), sections()
{
   for(auto it = sections.begin(); it != sections.end(); ++it)
   {
        add(*it);
   }

}


/**
   *  Add a section to the list for this faculty member. Sections are kept ordered
   *  by course number and CRN.
   * 
   * @param sect a course section
   */
void Faculty::add(const Section &sect)
{
    sections.push_back(sect);
    ++numberOfSections;
    sections.sort();
}


/**
   * Allow access to the "beginning" of the section with a const_iterator
   */
Faculty::const_iterator Faculty::begin() const
{
    return sections.begin();
}

/**
   * Allow access to the "end" of the section with a const_iterator
   */
Faculty::const_iterator Faculty::end() const
{
    return sections.end();
}

/**
   * Return the size of the faculty, the number of sections
   */
size_t Faculty::size() const 
{
    return sections.size();
}


/**
   * Overloading operator<
   */
bool Faculty::operator<(const Faculty& right) const
{
    if(name != right.getName())
        return name < right.getName();
    if(numberOfSections != right.numSections())
        return numberOfSections < right.numSections();
    
    list<Section>::const_iterator it_right = right.sections.begin();
    for(auto it = sections.begin(); it != sections.end(); ++it)
    {
        if(!(*it == *it_right))
        {
            return *it < *it_right;
        }
        ++it;
    }

   return false;
}


/**
   * Overloading operator==
   */
bool Faculty::operator==(const Faculty& right) const
{
    
    if(name != right.getName() || numberOfSections != right.numSections())
        return false;
    
     list<Section>::const_iterator it_right = right.sections.begin();
    for(auto it = sections.begin(); it != sections.end(); ++it)
    {
        if(!(*it == *it_right))
        {
            return false;
        }
        ++it;
    }

    return true;
}


/**
 *  Print a faculty member name, followed, one per line, by the sections associated
 *  with this faculty member;
 */
std::ostream& operator<< (std::ostream& out, const Faculty& fac)
{
    out << fac.getName() << "\n";

    for(auto it = fac.begin(); it != fac.end(); ++it)
    {
        out << "    " << *it << endl;
    }

    return out;
}