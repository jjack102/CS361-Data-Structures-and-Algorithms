#include "unittest.h"
#include "department.h"
#include <array>
#include <algorithm>

using namespace std;


UnitTest(testDeptAddFacultyBeginning) {
    Faculty f1 ("A");
    Faculty f2 ("B");
    Faculty f3 ("C");
    Faculty f4 ("D");

    Faculty expected[] = {f1, f2, f3, f4};

    Department dept;

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(expected[3-i].getName());
        assertThat (f, isEqualTo(expected[3-i]));
        assertThat (dept.numFaculty(), isEqualTo(i+1));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(expected[i].getName());
        assertThat (f, isEqualTo(expected[i]));
        assertThat (dept.numFaculty(), isEqualTo(4));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.get(i);
        assertThat (f, isEqualTo(expected[i]));
    }
}

UnitTest(testDeptAddFacultyEnd) {
    Faculty f1 ("A");
    Faculty f2 ("B");
    Faculty f3 ("C");
    Faculty f4 ("D");

    Faculty expected[] = {f1, f2, f3, f4};

    Department dept;

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(expected[i].getName());
        assertThat (f, isEqualTo(expected[i]));
        assertThat (dept.numFaculty(), isEqualTo(i+1));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(expected[i].getName());
        assertThat (f, isEqualTo(expected[i]));
        assertThat (dept.numFaculty(), isEqualTo(4));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.get(i);
        assertThat (f, isEqualTo(expected[i]));
    }
}

UnitTest(testDeptAddFacultyMixed) {
    Faculty f1 ("A");
    Faculty f2 ("B");
    Faculty f3 ("C");
    Faculty f4 ("D");

    Faculty insertion[] = {f4, f1, f3, f2}; 
    Faculty expected[] = {f1, f2, f3, f4};

    Department dept;

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(insertion[i].getName());
        assertThat (f, isEqualTo(insertion[i]));
        assertThat (dept.numFaculty(), isEqualTo(i+1));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.findFaculty(expected[i].getName());
        assertThat (f, isEqualTo(expected[i]));
        assertThat (dept.numFaculty(), isEqualTo(4));
    }

    for (int i = 0; i < 4; ++i)
    {
        Faculty& f = dept.get(i);
        assertThat (f, isEqualTo(expected[i]));
    }
}
