#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <cassert>
#include <string>

#include "section.h"
#include <set>
#include <map>

using namespace std;


class Department {
  // Declare the appropriate data members you need here.
  // You may NOT use arrays, vectors, lists, deques, or other
  // sequential structures. Focus on the associative containers.
private:
  std::set<std::string, std::less<std::string>> facultyMembers;
  
  typedef std::multimap<std::string, Section> FacultyMap;
  FacultyMap facultyCourses; 

public: 
  //** You may alter the public interface but it must continue to
  //** compile with the existing, unaltered application code and
  //** test code.

  // Rewrite the typedef below using an appropriate iterator type.
    //typedef std::string* iterator;
    //typedef std::set<std::string>::const_iterator const_iterator;

  typedef std::set<std::string>::const_iterator iterator;
  typedef std::set<std::string>::const_iterator const_iterator;

   /**
    * @brief Construct a new Department object with no faculty
    *    or course sections.
    */
   Department();

    /**
     * Add a new faculty member with the indicated
     * name. Duplicates are ignored.
     * 
     * @param facName name of the faculty member to find or add
     */
   void addFaculty (const string& facName);

   /**
    * number of faculty in the dept. 
    */
   int numFaculty() const;

   // Provide access to faculty names (in alphabetical order)
   const_iterator begin() const;
   const_iterator end() const;

  /**
   * Record the information that this faculty member is teaching a course section.
   * In general, faculty may teach many different sections. If the faculty member is
   * unknown, ignore this call.
   */
   void teaches (std::string facultyName, const  Section& section);

  /**
   * Return the set of courses taught by the indicated faculty member.
   * 
   * @param facultyName name of the faculty member.
   * @returns the set of sections taught by that faculty member. Return an empty
   *          set if the faculty name is unknown.
   */
   std::set<Section> taughtBy (std::string facultyName);


};

#endif
