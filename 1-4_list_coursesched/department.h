#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <cassert>
#include <string>

#include "faculty.h"

using namespace std;


class Department {

    static const int MAXFACULTY = 100;
    Faculty faculty[MAXFACULTY];
    int nFaculty;

public: 
   Department();

    /**
     * Search the department for the indicated faculty name. If found, return
     * that faculty member. If not found, add a new faculty member with that
     * name and return the newly added faculty member.
     * 
     * @param facName name of the faculty member to find or add
     * @return the faculty member with that name
     */
   Faculty& findFaculty (const string& facName);

   /**
    * number of faculty in the dept. 
    */
   int numFaculty() const {return nFaculty;}

   /**
    * Retrieve the i_th faculty member
    * 
    * @param i index of faculty member to retrieve
    * @return the faculty member
    * @pre i >= 0 && i < numFaculty()
    */
   Faculty& get (int i) const {return ((Department*)this)->faculty[i];}

};

#endif
