#include <cassert>
#include "faculty.h"

using namespace std;


const unsigned Faculty::MAXSECTIONS = 150;
/**
   * Construct a Faculty object with empty name and no course sections.
   */
Faculty::Faculty()
: name(), numberOfSections(0), sections(new Section[MAXSECTIONS])
{
}

/**
   * Construct a faculty member with the given name and no course sections.
   * 
   * @param theName  name to give to this faculty member
   */
Faculty::Faculty(std::string theName)
: name(theName), numberOfSections(0), sections(new Section[MAXSECTIONS])
{
}

/**
   * Copy Constructor 
   */
Faculty::Faculty(const Faculty& src)
: name(src.name), numberOfSections(src.numberOfSections), 
sections(new Section[MAXSECTIONS])
{
    for(int i = 0; (unsigned)i < numberOfSections; ++i)
    {
        sections[i] = src.sections[i];
    } 
}

/**
  * Deconstructor
  */
Faculty::~Faculty()
{
    delete [] sections;
}

/**
   * Retrieve the sectionNum_th section associated with this faculty member
   * 
   * @param sectionNum identifies the section to be retrieved.
   * @return the desired section
   * @pre sectionNum < numSections()  
   */
const Section& Faculty::getSection(unsigned sectionNum) const
{
    assert (sectionNum < numberOfSections);
    return sections[sectionNum];
}


/**
   *  Add a section to the list for this faculty member. Sections are kept ordered
   *  by course number and CRN.
   * 
   * @param sect a course section
   */
void Faculty::add(const Section &sect)
{
    assert (numberOfSections < MAXSECTIONS);

    // Make room for the insertion
    int k = numberOfSections - 1;
    while(k >= 0 && sect < sections[k])
    {
        sections[k+1] = sections[k];
        --k;
    }

    //Insert the new value
    sections[k+1] = sect;
    ++numberOfSections;
}

/**
   * Assignment operator
   */
Faculty& Faculty::operator=(const Faculty& right)
{
    if(this != &right)
    {
        name = right.name;
        numberOfSections = right.numberOfSections;
        delete [] sections;
        sections = new Section[MAXSECTIONS];
        for(int i = 0; (unsigned)i < numberOfSections; ++i)
        {
            sections[i] = right.sections[i];
        }
    }
    return *this;
}

/**
   * Overloading operator<
   */
bool Faculty::operator<(const Faculty& right) const
{
    
    if(name != right.name)
        return name < right.name;
    if(numberOfSections != right.numberOfSections)
        return numberOfSections < right.numberOfSections;
    for(int i = 0; (unsigned)i < numberOfSections; ++i)
    {
        if(!(sections[i] == right.sections[i]))
            return sections < right.sections;
    }
   return false;
}

/**
   * Overloading operator==
   */
bool Faculty::operator==(const Faculty& right) const
{
    if(name != right.name || numberOfSections != right.numberOfSections)
        return false;
    for(int i = 0; (unsigned)i < numberOfSections; ++i)
    {
        if(!(sections[i] == right.sections[i]))
            return false;
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
    for (unsigned i = 0; i < fac.numSections(); ++i)
    {
        const Section& sect = fac.getSection(i);
        out << "    " << sect << endl;
    }
    return out;
}

