#include "unittest.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>
#include "section.h"

using namespace std;


UnitTest(testSectionDefaultConstructor) {
	Section s;
	assertThat (s.getCredits(), isEqualTo(0));
	assertThat (s.getCRN(), isEqualTo(0));
	assertThat (s.getDays(), isEqualTo(""));
	assertThat (s.getName(), isEqualTo(""));
	assertThat (s.getTime(), isEqualTo(""));
	assertThat (s.getTitle(), isEqualTo(""));
	assertThat (s, isEqualTo(Section()));
	assertFalse(s < Section());

	ostringstream out;
	out << s;
	string outs = out.str();
}

void stripBlanks(string& s)
{
	string result;
	for (unsigned i = 0;  i < s.size(); ++i)
	    if (s[i] != ' ')
		   result += s[i];
	s = result;
}

UnitTest(testSectionConstructor) {
	int crn = 12345;
	string name = "CS350";
	string title = "Software Engineering";
	int credits = 3;
	string time = "1:00-1:50PM";
	string days = "MWF";
	Section s(crn, name, title, credits, days, time);
	assertThat (s.getCredits(), isEqualTo(credits));
	assertThat (s.getCRN(), isEqualTo(crn));
	assertThat (s.getDays(), isEqualTo(days));
	assertThat (s.getName(), isEqualTo(name));
	assertThat (s.getTime(), isEqualTo(time));
	assertThat (s.getTitle(), isEqualTo(title));
	assertThat (s, not(isEqualTo(Section())));
	assertThat(Section(), isLessThan(s));

	ostringstream out;
	out << s;
	string output = out.str();
	assertThat (output, contains(to_string(crn)));
	assertThat (output, contains(name));
	assertThat (output, contains(days));
	assertThat (output, contains(time));
	assertThat (output, contains(title));

	stripBlanks(output);
	string title2 = title;
	stripBlanks(title2);
	assertThat (output, isEqualTo("12345" + name + title2 + "3" + days + time));
	

	Section s2(crn+1, name, title, credits, days, time);
	assertThat (s, isLessThan(s2));
	assertThat (s, not(isEqualTo(s2)));

	Section s3(crn+1, "CS150", title, credits, days, time);
	assertThat (s3, isLessThan(s));
	assertThat (s, not(isEqualTo(s3)));

	Section s4(crn, name, "", credits+1, "TR", "4:20-5:35PM");
	assertThat (s, isEqualTo(s4));
	
}


