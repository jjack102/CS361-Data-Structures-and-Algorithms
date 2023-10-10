#include "csv.h"

using namespace std;

/**
 *  Parse a string as a row of CSV (comma-separated-values) fields.
 * 
 * @param line a line representing a single row in CSV format.
 * @return a vector of string field values obtained from the line
 */
std::vector<std::string> parseCSV(const std::string &line)
{
    enum States
    {
        atStartofField,
        accumulatingCharacters,
        insideQuotedString
    };
    vector<string> fields;
    string current;
    States state = atStartofField;
    for (string::size_type i = 0; i < line.size(); ++i)
    {
        char c = line[i];
        switch (state)
        {
        case atStartofField:
        {
            if (c == '"')
            {
                state = insideQuotedString;
            }
            else if (c == ',')
            {
                fields.push_back(current);
                current = "";
            }
            else
            {
                current += c;
                state = accumulatingCharacters;
            }
        }
        break;

        case accumulatingCharacters:
        {
            if (c == ',')
            {
                fields.push_back(current);
                current = "";
                state = atStartofField;
            }
            else
            {
                current += c;
                state = accumulatingCharacters;
            }
        }
        break;

        case insideQuotedString:
        {
            if (c == '"')
            {
                if (i == line.size() || line[i + 1] != '"')
                {
                    state = accumulatingCharacters;
                }
                else
                {
                    current += c;
                    i++;
                    state = insideQuotedString;
                }
            }
            else
            {
                current += c;
                state = insideQuotedString;
            }
        }
        break;
        }
    }
    fields.push_back(current);
    return fields;
}
