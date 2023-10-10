#include "unittest.h"
#include "faculty.h"
#include <algorithm>
#include <sstream>

using namespace std;


UnitTest(testFacDefaultConstructor)
{
    Faculty fac;
    assertThat (fac.getName(), isEqualTo(""));
    assertThat (fac.numSections(), isEqualTo(0));
    assertThat (fac, isEqualTo(Faculty()));
    assertFalse (fac < Faculty());
    assertFalse (Faculty() < fac);

    assertTrue (fac.sanityCheck());
}

UnitTest(testFacConstructor)
{
    string originalName = "Doe, John";
    Faculty fac (originalName);
    assertThat (fac.getName(), isEqualTo(originalName));
    assertThat (fac.numSections(), isEqualTo(0));
    assertThat (fac, isEqualTo(Faculty(originalName)));
    assertTrue (fac < Faculty() || Faculty() < fac);

    ostringstream out;
    out << fac;
    string facOutput = out.str();
    assertThat (facOutput, contains(originalName));

    assertTrue (fac.sanityCheck());
}

UnitTest(testFacSetName)
{
    string originalName = "Doe, John";
    Faculty fac (originalName);
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    fac.add (s1);

    string newName = "Smith, Jane";

    Faculty fac0 (fac);
    fac.setName(newName);

    assertThat (fac.getName(), isEqualTo(newName));
    assertThat (fac0.getName(), isEqualTo(originalName));

    assertThat (fac.numSections(), isEqualTo(1));
    assertThat (fac, not(isEqualTo(fac0)));
    assertTrue (fac < fac0 || fac0 < fac);

    ostringstream out;
    out << fac;
    string facOutput = out.str();
    assertThat (facOutput, contains(newName));
    assertThat (facOutput, contains(s1.getName()));
    assertThat (facOutput, contains(s1.getTitle()));

    assertTrue (fac.sanityCheck());
}



void testAddingSections (Section* expected, Section* input, int nSections)
{
    Faculty fac ("Doe, John");
    Faculty fac0 = fac;

    for (int i = 0; i < nSections; ++i)
    {
        fac0 = fac;
        fac.add(input[i]);
    }
    assertThat (fac.numSections(), isEqualTo(nSections));
    for (int j = 0; j < nSections; ++j)
    {
        assertThat(fac.getSection(j), isEqualTo(expected[j]));
    }
    assertThat(fac0, not(isEqualTo(fac)));
    assertTrue (fac0 < fac || fac < fac0);
        
    ostringstream out;
    out << fac;
    string facOutput = out.str();

    string::size_type k = facOutput.find(fac.getName());
    assertNotEqual (string::npos, k);

    for (int j = 0; j < nSections; ++j)
    {
        ostringstream out2;
        out2 << expected[j];
        k = facOutput.find(out2.str(), k); 
        assertNotEqual (string::npos, k);
    }

    assertTrue (fac.sanityCheck());
}

UnitTest(testFacAddBeginning) {
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    Section s2 (12346, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s3 (12300, "CS361", "Data Structures and Algorithms", 3, "MW", "4:20-5:35PM");
    Section s4 (12789, "CS690", "Graduate Colloquium", 1, "F", "10:30AM-12:00PM");

    Section expected[] = {s1, s2, s3, s4};
    Section input[] = {s4, s3, s2, s1};

    testAddingSections(expected+3, input, 1);
    testAddingSections(expected+2, input, 2);
    testAddingSections(expected+1, input, 3);
    testAddingSections(expected, input, 4);
}

UnitTest(testFacAddEnd) {
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    Section s2 (12346, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s3 (12300, "CS361", "Data Structures and Algorithms", 3, "MW", "4:20-5:35PM");
    Section s4 (12789, "CS690", "Graduate Colloquium", 1, "F", "10:30AM-12:00PM");

    Section expected[] = {s1, s2, s3, s4};
    Section input[] = {s1, s2, s3, s4};

    testAddingSections(expected, input, 1);
    testAddingSections(expected, input, 2);
    testAddingSections(expected, input, 3);
    testAddingSections(expected, input, 4);
}

UnitTest(testFacAddMixed) {
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    Section s2 (12346, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s3 (12300, "CS361", "Data Structures and Algorithms", 3, "MW", "4:20-5:35PM");
    Section s4 (12789, "CS690", "Graduate Colloquium", 1, "F", "10:30AM-12:00PM");

    Section expected[] = {s1, s2, s3, s4};
    Section input[] = {s1, s4, s3, s2};

    testAddingSections(expected, input, 4);
}

UnitTest (testFacCopy)
{
    Section s1 (12345, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s2 (12340, "CS252", "Intro to Unix", 1, "", "");
   string facName = "Smith, Jane";

    Faculty fac1(facName);
    fac1.add(s1);

    Faculty fac2 (fac1);
    assertThat (fac2, isEqualTo(fac1));
    assertFalse (fac1 < fac2);
    assertFalse (fac2 < fac1);
    assertThat (fac2.getName(), isEqualTo(fac1.getName()));
    assertThat (fac2.numSections(), isEqualTo(fac1.numSections()));
    assertThat (fac2.getSection(0), isEqualTo(s1));

    ostringstream out1;
    out1 << fac1;
    ostringstream out2;
    out2 << fac2;

    assertThat (out2.str(), isEqualTo(out1.str()));
    
    
    fac1.add (s2);
    assertThat (fac2, not(isEqualTo(fac1)));
    assertThat (fac2.getName(), isEqualTo(fac1.getName()));
    assertThat (fac2.numSections(), isEqualTo(fac1.numSections()-1));
    assertThat (fac2.getSection(0), isEqualTo(s1));

    assertTrue (fac1.sanityCheck());
}

UnitTest (testFacAssign)
{
    Section s1 (12345, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s2 (12340, "CS252", "Intro to Unix", 1, "", "");
    string facName = "Smith, Jane";

    Faculty fac1(facName);
    fac1.add(s1);

    Faculty fac2;
    Faculty fac3 (fac2 = fac1);
    assertThat (fac2, isEqualTo(fac1));
    assertThat (fac3, isEqualTo(fac1));
    assertFalse (fac1 < fac2);
    assertFalse (fac2 < fac1);
    assertThat (fac2.getName(), isEqualTo(fac1.getName()));
    assertThat (fac2.numSections(), isEqualTo(fac1.numSections()));
    assertThat (fac2.getSection(0), isEqualTo(s1));

    ostringstream out1;
    out1 << fac1;
    ostringstream out2;
    out2 << fac2;

    assertThat (out2.str(), isEqualTo(out1.str()));
    
    fac1.add (s2);
    assertThat (fac2, not(isEqualTo(fac1)));
    assertThat (fac2.getName(), isEqualTo(fac1.getName()));
    assertThat (fac2.numSections(), isEqualTo(fac1.numSections()-1));
    assertThat (fac2.getSection(0), isEqualTo(s1));

    fac1 = fac1;
    assertThat(fac1.getName(), isEqualTo(facName));
    assertThat(fac1.numSections(), isEqualTo(2));
    assertThat (fac1.getSection(0), isEqualTo(s2));
    assertThat (fac1.getSection(1), isEqualTo(s1));

    assertTrue (fac1.sanityCheck());
}





UnitTest (zzMemoryCheck) {
    assertThat (MemoryChecked::getCurrentCount(), isEqualTo(0));
}

