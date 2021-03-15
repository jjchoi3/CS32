//
//  Flatulan.h
//  Project 1
//
//  Created by Junho Choi on 1/8/21.
//

class City;

#ifndef Flatulan_h
#define Flatulan_h
class Flatulan {
  public:
        // Constructor
    Flatulan(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool possiblyGetConverted();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};


#endif /* Flatulan_h */
