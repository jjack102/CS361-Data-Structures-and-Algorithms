#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>

class Character {
public:
  /**
   * The position of this character.
   */
  int x, y;


  long distanceSq(const Character& p) const;
};

std::ostream& operator<< (std::ostream& out, const Character& p);

bool operator== (const Character& left, const Character& right);




#endif /* POINT_H_ */
