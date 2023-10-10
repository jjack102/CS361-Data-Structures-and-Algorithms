#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>

/**
 *  Parse a string as a row of CSV (comma-separated-values) fields.
 * 
 * @param line a line representing a single row in CSV format.
 * @return a vector of string field values obtained from the line
 */
std::vector<std::string> parseCSV (const std::string& line);

#endif
