#include "unittest.h"
#include "csv.h"
#include <array>
#include <algorithm>

using namespace std;


UnitTest(testParseCSVSimple) {
    string in = "abc,123,def";
    array<string,3> expected = {"abc", "123", "def"};

    auto fields = parseCSV(in);
    assertThat (fields.size(), isEqualTo(expected.size()));

    assertTrue(equal(fields.begin(), fields.end(), expected.begin(), expected.end()));
}

UnitTest(testParseCSVQuoted) {
    string in = "abc,\"1,2\"\"3\",def";
    array<string,3> expected = {"abc", "1,2\"3", "def"};

    auto fields = parseCSV(in);
    assertThat (fields.size(), isEqualTo(expected.size()));

    assertTrue(equal(fields.begin(), fields.end(), expected.begin(), expected.end()));
}

UnitTest(testParseCSVEmpty) {
    string in = ",\"1,23\",";
    array<string,3> expected = {"", "1,23", ""};

    auto fields = parseCSV(in);
    assertThat (fields.size(), isEqualTo(expected.size()));

    assertTrue(equal(fields.begin(), fields.end(), expected.begin(), expected.end()));
}

