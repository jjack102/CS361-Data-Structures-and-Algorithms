#include <algorithm>
#include <fstream>
#include <stack>
#include <list>

#include "balancer.h"
#include "FlexLexer.h"
#include "scanner.h"


using namespace std;


std::string lowercase(std::string s)
{
	using namespace std;
	for (string::size_type i = 0; i < s.size(); ++i)
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
			s[i] = s[i] + 'a' - 'A';
	return s;
}




string location;




bool checkStatus(const Balancer& bal, const string& lastTag)
{
	if (bal.status() < 0)
	{
		cout << "Mismatched tags detected at tag " << lastTag << endl;
		return true;
	}
	else
		return false;
}



void collectFromFile (const string& fileName)
{
	ifstream inFile (fileName);

	Balancer balancer;

	if (!inFile)
	{
		cout << "Could not open '" << fileName << "'" << endl;
		return;
	}

	yyFlexLexer scanner (&inFile);

	cerr << "Checking " << fileName << endl;

	location = fileName;

	bool done = false;

	while (!done)
	{
		int tokenKind = scanner.yylex();
		// cerr << "lex: " << tokenKind << " '" << lexeme << "'" << endl;


		switch (tokenKind) {
		case WORD:
		{
			break;
		}

		case NAME:
		case LINK:
		case TAG:
		{
			// A tag has been detected.

			//cerr << "Encountered tag " << lexeme << endl;

			balancer.tag(lexeme);
			break;
		}

		case ENDOFFILE:
		{
			done = true;
		}
		}

		if (done) break;
		done = checkStatus(balancer, lexeme);
	}
	if (balancer.status() == 0)
	{
		cout << "Unclosed tags detected at end of file."<< endl;
	}
	else if (balancer.status() == 1)
		cout << "OK" << endl;

}





int main (int argc, char** argv)
{
	if (argc != 2 )
	{
		cerr << "usage:\n   collector htmlfilename" << endl;
		return 1;
	}


	string fileName = argv[1];

	collectFromFile (fileName);

	return 0;
}


