#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "department.h"
#include "faculty.h"
#include "section.h"
#include "csv.h"

using namespace std;





void readSchedule(Department& dept, istream &input)
{
  string line;
  getline(input, line); // ignore first line (headers)
  while (getline(input, line))
  {
    auto fields = parseCSV(line);
    assert(fields.size() == 8);
    int crn = stoi(fields[0]);
    string name = fields[1] + fields[2];
    string title = fields[3];
    int credits = stoi(fields[4]);
    string time = fields[5];
    string days = fields[6];
    string instructor = fields[7];

    Section section(crn, name, title, credits, days, time);
    Faculty &facultyMember = dept.findFaculty(instructor);
    facultyMember.add(section);
  }
}

void printSchedule (Department& dept, ostream& output)
{
  output << "Schedule" << endl;
  for (int iFac = 0; iFac < dept.numFaculty(); ++iFac)
    {
      const Faculty& fac = dept.get(iFac);
      output << fac.getName() << endl;
      int sectionCount = 0;
      for (const Section& sect: fac)
      {
        output << "    " << sect << endl;
        ++sectionCount;
      }
      output << "  " << sectionCount << " sections" << endl;
    }
}

void doMain (istream& in)
{
  Department dept;
  readSchedule (dept, in);
  printSchedule (dept, cout);
}

int main (int argc, char** argv)
{
  if (argc > 1) 
  {
    ifstream in (argv[1]);
    doMain (in);
  } else {
    doMain (cin);
  }
    
  return 0;
}
