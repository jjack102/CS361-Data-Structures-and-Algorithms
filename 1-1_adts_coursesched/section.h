#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>
#include "memoryChecked.h"

/**
 * A section of a course offering.  Course offerings (a single course taught by a faculty member)
 * are divided into sections for a variety of administrative purposes. In particular,
 * distance courses are offered simultaneously to different "campuses" but are still considered
 * a single course offering.
 */
class Section {
private:
  std::string name;   //!< Short name of the course, e.g., "CS361"
  std::string title;  //!< full name of the course
  int crn;            //!< Unique identifier of a course section
  int credits;        //!< Number of credits for the course
  std::string days;   //!< Days on which the course is offered.
  std::string time;   //!< Time at which the course is offered.
  MemoryChecked check;  //!< Used to check for memory leaks.
public:

  /**
   * Create a course section with all string members empty and all
   * integer members zero.
   */
  Section();

  /**
   * Create a course section
   * @param sectionCRN the section identifier
   * @param courseName the short name of the course (e.g., MATH162)
   * @param courseTitle the long name of the course
   * @param courseCredits # of credits for this course
   * @param courseDays days on which the course is offered (may be empty)
   * @param courseTime time at which the course is offered (may be empty)
   */
  Section(int sectionCRN, const std::string& courseName, const std::string& courseTitle,
          int courseCredits, const std::string& courseDays, const std::string& courseTime);

  
  /**
   * The section identifier
   */
  int getCRN() const  {return crn;}

  /**
   *  Name of this course
   */
  std::string getName() const {return name;}

 /**
   *  Title of this course
   */
  std::string getTitle() const {return title;}

  /**
   * Number of credits
   */
  int getCredits() const  {return credits;}

 /**
   *  Days on which this section is offered
   */
  std::string getDays() const {return days;}

 /**
   *  Time at which this section is offered
   */
  std::string getTime() const {return time;}


  /**
   *  Ordered by course name, ties broken by CRN
   */
  bool operator< (const Section&) const;
  bool operator== (const Section&) const;
};

// Print the section
std::ostream& operator<< (std::ostream& out, const Section& sect);


#endif
