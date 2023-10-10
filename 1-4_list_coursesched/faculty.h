#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <list>
#include <string>
#include "section.h"

class Faculty {
private:

  //** You must not change the private data members of this class, nor
  //** may you add additional data members.
  //**
  //** You may add private functions if you wish.


  std::string name;      //!< The name of the faculty member
  unsigned numberOfSections;  //!< Number of course sections being taught by this faculty member
  std::list<Section> sections;     //!< List of sections being taught by this faculty member

public:
  //** You may alter the public interface but it must continue to
  //** compile with the existing, unaltered application code and
  //** test code.

  typedef std::list<Section>::const_iterator iterator;              // standard iterator
  
  typedef std::list<Section>::const_iterator const_iterator;  // standard const_iterator

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

  template <typename Iterator>
  Faculty(std::string theName, Iterator start, Iterator stop);

  Faculty(std::string theName, std::initializer_list<Section> sections);

  Faculty(const Faculty& fac) = default;

  ~Faculty() = default;

  Faculty& operator=(const Faculty& fac) = default;
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
   * Allow access to the "beginning" of the section with a const_iterator
   */
  const_iterator begin() const;

  /**
   * Allow access to the "end" of the section with a const_iterator
   */
  const_iterator end() const;

  /**
   * Return the size of the faculty, the number of sections
   */
  size_t size() const;
  
  /**
   * Overloading operator<
   */
  bool operator<(const Faculty& right) const;

   /**
   * Overloading operator==
   */
  bool operator==(const Faculty& right) const;
  
  /**
   * Used by the instructor for testing purposes.
   */
  bool sanityCheck() const;
};

/**
 *  Print a faculty member name, followed, one per line, by the sections associated
 *  with this faculty member;
 */
std::ostream& operator<< (std::ostream& out, const Faculty& a);

template <typename Iterator>
Faculty::Faculty(std::string theName, Iterator start, Iterator stop)
: name(theName), numberOfSections(0), sections()
{
    for(auto it = start; it != stop; ++it)
    {
        add(*it);
    }

}
#endif
