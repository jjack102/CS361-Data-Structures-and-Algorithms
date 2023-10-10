#ifndef AUTHOR_H
#define AUTHOR_H

#include <iostream>
#include <string>
#include "section.h"


class Faculty {
private:

  //** You must not change the private data members of this class, nor
  //** may you add additional data members.
  //**
  //** You may add private functions if you wish.


  static const unsigned MAXSECTIONS;

  std::string name;      //!< The name of the faculty member
  unsigned numberOfSections;  //!< Number of course sections being taught by this faculty member
  Section* sections;     //!< Array of sections being taught by this faculty member

public:
  //** You may alter the public interface but it must continue to
  //** compile with the existing, unaltered application code and
  //** test code.

  /**
   * Construct a Faculty object with empty name and no course sections.
   */
  Faculty();

  /**
   * Construct a faculty member with the given name and no course sections.
   * 
   * @param theName  name to give to this faculty member
   */
  Faculty(std::string theName);

  /**
   * Copy Constructor 
   */
  Faculty(const Faculty& src);

  /**
   * Deconstructor
   */
  ~Faculty();

  /**
   * Get the name of the faculty member.
   * 
   * @return the name
   */
  std::string getName() const  {return name;}

  /**
   * Set the name of the faculty member.
   * 
   * @param theName the name to give to this faculty member.
   */
  void setName (std::string theName) {name = theName;}

  /**
   * How many sections are associated with this faculty member?
   * 
   * @return number of sections
   */
  unsigned numSections() const { return numberOfSections; }
  
  /**
   *  Add a section to the list for this faculty member. Sections are kept ordered
   *  by course number and CRN.
   * 
   * @param sect a course section
   * @pre numSections() < MAXSECTIONS
   */
  void add (const Section& sect);

  /**
   * Retrieve the sectionNum_th section associated with this faculty member
   * 
   * @param sectionNum identifies the section to be retrieved.
   * @return the desired section
   * @pre sectionNum < numSections()  
   */
  const Section& getSection (unsigned sectionNum) const;

  /**
   * Used by the instructor for testing purposes.
   */
  bool sanityCheck() const;

  /**
   * Assignment Operator
   */
  Faculty& operator=(const Faculty& right);
  
  /**
   * Overloading operator<
   */
  bool operator<(const Faculty& right) const;

   /**
   * Overloading operator==
   */
  bool operator==(const Faculty& right) const;
};


/**
 *  Print a faculty member name, followed, one per line, by the sections associated
 *  with this faculty member;
 */
std::ostream& operator<< (std::ostream& out, const Faculty& a);

#endif
