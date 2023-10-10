#include <cassert>
#include <string>

#include "department.h"

using namespace std;


Department::Department()
  : nFaculty(0)
{
}


Faculty& Department::findFaculty (const string& facName)
{
  int k = 0;
  while (k < nFaculty && facName > faculty[k].getName())
  {
    ++k;
  }
  if (k < nFaculty && facName == faculty[k].getName())
  {
    return faculty[k];
  }
  else
  {
    assert (nFaculty < MAXFACULTY);
    faculty[nFaculty] = Faculty(facName, {});
    ++nFaculty;
    k = nFaculty-1;
    while (k > 0 && faculty[k] < faculty[k-1]) 
    {
      swap(faculty[k], faculty[k-1]);
      --k;
    }
    return faculty[k];
  }  
}


