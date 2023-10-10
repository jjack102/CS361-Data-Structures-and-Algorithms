#include <string>

#include "department.h"

using namespace std;

/**
   * @brief Construct a new Department object with no faculty
   *    or course sections.
*/
Department::Department()
: facultyMembers(), facultyCourses()
{

}

/**
   * Add a new faculty member with the indicated
   * name. Duplicates are ignored.
   * 
   * @param facName name of the faculty member to find or add
*/
void Department::addFaculty (const string& facName) {
    facultyMembers.insert(facName);
}

/**
   * number of faculty in the dept. 
   */
int Department::numFaculty() const {
    return facultyMembers.size();
}

// Provide access to faculty names (in alphabetical order)
Department::const_iterator Department::begin() const {
    return facultyMembers.begin();
}
Department::const_iterator Department::end() const {
    return facultyMembers.end();
}

/**
   * Record the information that this faculty member is teaching a course section.
   * In general, faculty may teach many different sections. If the faculty member is
   * unknown, ignore this call.
*/
void Department::teaches (std::string facultyName, const  Section& section) {
    if(facultyMembers.find(facultyName) == facultyMembers.end()){
        return;
    }

    facultyCourses.insert(std::make_pair(facultyName, section));
}

/**
   * Return the set of courses taught by the indicated faculty member.
   * 
   * @param facultyName name of the faculty member.
   * @returns the set of sections taught by that faculty member. Return an empty
   *          set if the faculty name is unknown.
*/
std::set<Section> Department::taughtBy (std::string facultyName) {
    std::set<Section> courses;

    auto pos = facultyCourses.equal_range(facultyName);
    for (auto it = pos.first; it != pos.second; ++it){
        courses.insert(it->second);
    }

    return courses;
}

