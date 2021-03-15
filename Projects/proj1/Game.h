//
//  Game.h
//  Project 1
//
//  Created by Junho Choi on 1/8/21.
//

class City;
#ifndef Game_h
#define Game_h
class Game {
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
        // Mutators
    void play();

  private:
    City* m_city;
};

#endif /* Game_h */
