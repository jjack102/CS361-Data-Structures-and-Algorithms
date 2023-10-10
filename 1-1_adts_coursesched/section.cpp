#include "section.h"
#include <iomanip>

using namespace std;

/**
   * Create a course section with all string members empty and all
   * integer members zero.
   */
Section::Section()
: name(), title(), crn(0), credits(0), days(), time()
{
}

/**
   * Create a course section
   * @param sectionCRN the section identifier
   * @param courseName the short name of the course (e.g., MATH162)
   * @param courseTitle the long name of the course
   * @param courseCredits # of credits for this course
   * @param courseDays days on which the course is offered (may be empty)
   * @param courseTime time at which the course is offered (may be empty)
   */
Section::Section(int sectionCRN, const std::string &courseName, const std::string &courseTitle,
                 int courseCredits, const std::string &courseDays, const std::string &courseTime)
: name(courseName), title(courseTitle), crn(sectionCRN), credits(courseCredits), 
  days(courseDays), time(courseTime)
{
}

bool Section::operator<(const Section & right) const
{
    if (name < right.name)
        return true;
    else if (name == right.name)
        return crn < right.crn;
    else
        return false;    
}

bool Section::operator==(const Section & right) const
{
    return (crn == right.crn) && (name == right.name);
}

// Print the section
std::ostream &operator<<(std::ostream &out, const Section &sect)
{
    std::ios_base::fmtflags savedFlags( out.flags() );
    out << setw(5) << sect.getCRN() << " ";
    out << setw(9) << sect.getName().substr(0, 9) << " ";
    out << setw(32) << left << sect.getTitle().substr(0, 32) << " ";
    out << setw(2) << right << sect.getCredits() << " ";
    out << setw(7) << right << sect.getDays().substr(0, 7) << " ";
    out << setw(12) << left << sect.getTime().substr(0, 12) << " ";
    out.flags(savedFlags);
    return out;
}

