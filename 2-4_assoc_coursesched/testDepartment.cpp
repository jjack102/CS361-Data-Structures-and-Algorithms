#include "unittest.h"
#include "department.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


UnitTest(testDeptConstructor) {
    Department dept;
    assertThat (dept.numFaculty(), isEqualTo(0));
    assertThat (dept.taughtBy("anyone").size(), isEqualTo(0));
    assertThat (dept.begin(), isEqualTo(dept.end()));
}

UnitTest(testDeptAddFaculty) {
    string f1 ("A");
    string f2 ("B");
    string f3 ("C");
    string f4 ("D");

    vector<string> insertion = {f4, f1, f3, f2}; 
    vector<string> expected = {f1, f2, f3, f4};

    Department dept;

    for (int i = 0; i < 4; ++i)
    {
        dept.addFaculty(insertion[i]);
        assertThat (dept.numFaculty(), isEqualTo(i+1));
        assertThat (dept.taughtBy(insertion[i]).size(), isEqualTo(0));
    }
    assertThat(contentsOf(dept), matches(contentsOf(expected)));
    assertThat (dept.taughtBy("E").size(), isEqualTo(0));
}


UnitTest(testDeptTeachesBase) {
    string doe = "Doe, John";
    string smith = "Smith, Jane";
    
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    Section s2 (12346, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s3 (12300, "CS361", "Data Structures and Algorithms", 3, "MW", "4:20-5:35PM");
    Section s4 (12789, "CS690", "Graduate Colloquium", 1, "F", "10:30AM-12:00PM");

    Department dept;
    dept.addFaculty(doe);
    dept.addFaculty(smith);
    assertThat (dept.taughtBy(doe).size(), isEqualTo(0));

    dept.teaches(doe, s3);
    assertThat (dept.taughtBy(doe).size(), isEqualTo(1));
    assertThat (dept.taughtBy(smith).size(), isEqualTo(0));
    assertThat (*(dept.taughtBy(doe).begin()), isEqualTo(s3));


    
    dept.teaches(doe, s2);
    vector<Section> expected1 = {s2, s3};
    assertThat (contentsOf(dept.taughtBy(doe)), matches(contentsOf(expected1)));

    dept.teaches(smith, s4);
    dept.teaches(smith, s3);
    dept.teaches(smith, s2);
    dept.teaches(smith, s1);
    vector<Section> expected2 = {s1, s2, s3, s4};
    assertThat (contentsOf(dept.taughtBy(smith)), matches(contentsOf(expected2)));
    
}

UnitTest(testDeptTeachesUnknown) {
    string doe = "Doe, John";
    string smith = "Smith, Jane";
    
    Section s1 (12345, "CS350", "Software Engineering", 3, "", "");
    Section s2 (12346, "CS350", "Software Engineering", 3, "TR", "9:00-10:15AM");
    Section s3 (12300, "CS361", "Data Structures and Algorithms", 3, "MW", "4:20-5:35PM");
    Section s4 (12789, "CS690", "Graduate Colloquium", 1, "F", "10:30AM-12:00PM");

    Department dept;
    dept.addFaculty(doe);
    assertThat (dept.taughtBy(doe).size(), isEqualTo(0));


    dept.teaches(doe, s3);
    assertThat (dept.taughtBy(doe).size(), isEqualTo(1));
    assertThat (dept.taughtBy(smith).size(), isEqualTo(0));
    assertThat (*(dept.taughtBy(doe).begin()), isEqualTo(s3));


    
    dept.teaches(doe, s2);
    vector<Section> expected1 = {s2, s3};
    assertThat (contentsOf(dept.taughtBy(doe)), matches(contentsOf(expected1)));

    dept.teaches(smith, s4);
    dept.teaches(smith, s3);
    dept.teaches(smith, s2);
    dept.teaches(smith, s1);
    vector<Section> expected2 = {};
    assertThat (dept.numFaculty(), isEqualTo(1));
    assertThat (contentsOf(dept.taughtBy(smith)), matches(contentsOf(expected2)));
    
}