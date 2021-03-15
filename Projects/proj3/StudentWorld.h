#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Class Protoypes
class Actor;
class GhostRacer;

class StudentWorld : public GameWorld{
public:
    // Constructor
    StudentWorld(std::string assetPath);
    
    // Destructor
    ~StudentWorld(){cleanUp();}
    
    // Mutator Member Overloaded Functions
    int init();
    int move();
    void cleanUp();
    
    // Accessor Member Functions
    GhostRacer* getAisha() const {return _aisha;}
    
    bool closeActorInSameLane(const Actor* actor, int yDistance) const;
   
    bool overlapsWithAisha(const Actor* actor) const;
    Actor* getOverlappingActorAffectedByHolyWater(const Actor* actor) const;
    
    // Mutator Member Functions
    void addOilSlick(int xCoord, int yCoord);
    void addHolyWaterProjectile(int xCoord, int yCoord, int dxn);
    void addHealingGoodie(int xCoord, int yCoord);
    
    void incrementSoulsSaved(){_numSoulsSaved++;}
    
private:
    // List to hold all actors (including GhostRacer)
    std::list<Actor*> _actors;
    GhostRacer* _aisha;
    
    int _bonusPoints;
    int _numSoulsSaved;
    
    int _lastWhiteBorderYCoord;
    
    // Accessor Member Functions
    Actor* getColAvoidWorthyActorClosestToY(int yCoord, int leftBound, int rightBound) const;
    
    // Mutator Member Functions
    void addRoadMarkers();
    void addHumanPedestrian();
    void addZombiePedestrian();
    void addZombieCab();
    void addOilSlick();
    void addHolyWaterGoodie();
    void addLostSoul();
    
    void updateGameStatsText();
    void updateLastWhiteBorderYCoord(int& yCoord);
};

// Non-Member Functions
bool isOverlapping(const Actor* actor1, const Actor* actor2);
void getActorLaneBoundaries(int actorXCoord, int& leftXCoord, int& rightXCoord);

#endif // STUDENTWORLD_H_
