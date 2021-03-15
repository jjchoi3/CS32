#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <list>

using namespace std;

GameWorld* createStudentWorld(string assetPath){
	return new StudentWorld(assetPath);
}

// Constructor
StudentWorld::StudentWorld(string assetPath):
GameWorld(assetPath),
_aisha(nullptr),
_numSoulsSaved(0),
_lastWhiteBorderYCoord(-1),
_bonusPoints(5000){}

// StudentWorld Implementation
// Initialize world with GhostRacer and appropriate boundary lines
int StudentWorld::init(){
    // Instantiate GhostRacer and add to list
    _aisha = new GhostRacer(128, 32, this);
    _actors.push_back(_aisha);
    
    const int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH / 2;
    const int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH / 2;
    
    // Instantiate Yellow Border Lines and add to list
    for(int i = 0; i < VIEW_HEIGHT / SPRITE_HEIGHT; ++i){
        // Left
        _actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, i * SPRITE_HEIGHT, this));
        // Right
        _actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, i * SPRITE_HEIGHT,  this));
    }
    // Instantiate White Border Lines and add to list
    for(int i = 0; i < VIEW_HEIGHT / (4 * SPRITE_HEIGHT); ++i){
        // Left
        _actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH / 3, i * (4 * SPRITE_HEIGHT), this));
        // Right
        _actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH / 3, i * (4 * SPRITE_HEIGHT), this));
        _lastWhiteBorderYCoord = _actors.back()->getY();
    }
    
    // Init Done
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move(){
    for(std::list<Actor*>::iterator it = _actors.begin(); it != _actors.end(); ++it){
        // Actors do something if alive
        if((*it)->isAlive()){
            (*it)->doSomething();
            
            if(!_aisha->isAlive()){
                playSound(SOUND_PLAYER_DIE); // Play dead sound
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            
            if(_numSoulsSaved == GameWorld::getLevel() * 2 + 5){
                increaseScore(_bonusPoints);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    // Update Y Coordinate of Last White Border Line
    updateLastWhiteBorderYCoord(_lastWhiteBorderYCoord);
    
    // Remove all dead actors from list and free memory
    std::list<Actor*>::iterator it = _actors.begin();
    while(it != _actors.end()){
        // Actors die if not alive
        if(!(*it)->isAlive()){
            Actor* deadActor = (*it);
            std::list<Actor*>::iterator temp_it = it; // Temporary iterator to point to next node
            temp_it++;
            _actors.erase(it);
            delete deadActor;
            it = temp_it; // Set it to node after deleted node
        }else
            it++;
    }
    
    // Potentially add new actors
    addRoadMarkers();
    addHumanPedestrian();
    addZombiePedestrian();
    addZombieCab();
    addOilSlick();
    addHolyWaterGoodie();
    addLostSoul();
    
    // Update game status
    updateGameStatsText();
    
    // Subtract 1 Bonus Point per tick
    if(_bonusPoints > 0)
        _bonusPoints--;
    return GWSTATUS_CONTINUE_GAME;
}

// Clean up world and free up all dynamically allocated actors
void StudentWorld::cleanUp(){
    std::list<Actor*>::iterator it = _actors.begin();
    while(it != _actors.end()){
        delete *it;
        it++;
    }
    _aisha = nullptr; // GhostRacer was on list so is now deleted
    _actors.clear();
    
    _numSoulsSaved = 0;
    _lastWhiteBorderYCoord = -1;
    _bonusPoints = 5000;
}

// Methods for StudentWorld to randomly spawn actors
void StudentWorld::addRoadMarkers(){
    const int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
    const int delta_y = new_border_y - _lastWhiteBorderYCoord;
    
    // Instantiate Yellow Border Lines and add to list
    if(delta_y >= SPRITE_HEIGHT){
        // Left
        _actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2, new_border_y, this));
        // Right
        _actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2, new_border_y, this));
    }
    // Instantiate White Border Lines and add to list
    if(delta_y >= 4 * SPRITE_HEIGHT){
        // Left
        _actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3, new_border_y, this));
        
        // Right
        _actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3, new_border_y, this));
        
        _lastWhiteBorderYCoord = _actors.back()->getY();
    }
}
void StudentWorld::addHumanPedestrian(){
    const int chanceHumanPed = max(200 - getLevel() * 10, 30);
    const int xCoord = randInt(0, VIEW_WIDTH);
    const int yCoord = VIEW_HEIGHT;
    if(randInt(0, chanceHumanPed - 1) == 0)
        _actors.push_back(new HumanPedestrian(xCoord, yCoord, this));
}
void StudentWorld::addZombiePedestrian(){
    const int chanceZombiePed = max(100 - GameWorld::getLevel() * 10, 20);
    const int xCoord = randInt(0, VIEW_WIDTH);
    const int yCoord = VIEW_HEIGHT;
    
    if(randInt(0, chanceZombiePed - 1) == 0)
        _actors.push_back(new ZombiePedestrian(xCoord, yCoord, this));
}
void StudentWorld::addZombieCab(){
    const int chanceVehicle = max(100 - getLevel() * 10, 20);
    if(randInt(0, chanceVehicle) == 0){
        // Generate array with lanes in random order
        int lanes[] = {
            ROAD_CENTER - ROAD_WIDTH / 3, // Represents Left Lane
            ROAD_CENTER, // Represents Middle Lane
            ROAD_CENTER + ROAD_WIDTH / 3 // Represents Right Lane
        };
        int randomLanes[3];
        int firstLane = randInt(0, 2), secondLane = firstLane;
        while(secondLane != firstLane)
            secondLane = randInt(0,2);
        randomLanes[0] = lanes[firstLane];
        randomLanes[1] = lanes[secondLane];
        if(firstLane + secondLane == 1)
            randomLanes[2] = lanes[2];
        else if(firstLane + secondLane == 2)
            randomLanes[2] = lanes[1];
        else
            randomLanes[2] = lanes[0];
        
        for(int i = 0; i < 3; ++i){
            int leftBoundary, rightBoundary; // Get left and right boundary of lane
            getActorLaneBoundaries(randomLanes[i], leftBoundary, rightBoundary);
            
            // Check closest collision avoidance-worthy actors to the bottom of lane
            Actor* closestBottomActor = getColAvoidWorthyActorClosestToY(0, leftBoundary, rightBoundary);
            if(closestBottomActor == nullptr ||
               (closestBottomActor != nullptr && closestBottomActor->getY() > VIEW_HEIGHT / 3)){
                const int vertSpeed = getAisha()->getVertSpeed() + randInt(2, 4);
                _actors.push_back(new ZombieCab(randomLanes[i], SPRITE_HEIGHT / 2, vertSpeed, this));
                break;
            }
            
            // Check closest collision avoidance-worthy actors to the top of the lane
            Actor* closestTopActor = getColAvoidWorthyActorClosestToY(VIEW_HEIGHT, leftBoundary, rightBoundary);
            if(closestTopActor == nullptr ||
               (closestTopActor != nullptr && closestTopActor->getY() < VIEW_HEIGHT * 2 / 3)){
                const int vertSpeed = getAisha()->getVertSpeed() - randInt(2, 4);
                _actors.push_back(new ZombieCab(randomLanes[i], VIEW_HEIGHT - SPRITE_HEIGHT / 2, vertSpeed, this));
                break;
            }
        }
    }
}
void StudentWorld::addOilSlick(){
    const int chanceOilSlick = max(150 - getLevel() * 10, 40);
    const int xCoord = randInt(ROAD_CENTER - ROAD_WIDTH / 2, ROAD_CENTER + ROAD_WIDTH / 2);
    const int yCoord = VIEW_HEIGHT;
    
    if(randInt(0, chanceOilSlick - 1) == 0)
        _actors.push_back(new OilSlick(xCoord, yCoord, this));
}
void StudentWorld::addHolyWaterGoodie(){
    const int chanceOfHolyWater = 100 + 10 * getLevel();
    const int xCoord = randInt(ROAD_CENTER - ROAD_WIDTH / 2, ROAD_CENTER + ROAD_WIDTH / 2);
    if(randInt(0, chanceOfHolyWater - 1) == 0)
        _actors.push_back(new HolyWaterGoodie(xCoord, VIEW_HEIGHT, this));
}
void StudentWorld::addLostSoul(){
    const int chanceOfHolyWater = 100;
    const int xCoord = randInt(ROAD_CENTER - ROAD_WIDTH / 2, ROAD_CENTER + ROAD_WIDTH / 2);
    if(randInt(0, chanceOfHolyWater - 1) == 0)
        _actors.push_back(new SoulGoodie(xCoord, VIEW_HEIGHT, this));
}

// Methods for actors to spawn other actors
void StudentWorld::addOilSlick(int xCoord, int yCoord){_actors.push_back(new OilSlick(xCoord, yCoord, this));}
void StudentWorld::addHolyWaterProjectile(int xCoord, int yCoord, int dxn){_actors.push_back(new HolyWaterProjectile(xCoord, yCoord, dxn, this));}
void StudentWorld::addHealingGoodie(int xCoord, int yCoord){_actors.push_back(new HealingGoodie(xCoord, yCoord, this));}

void StudentWorld::updateLastWhiteBorderYCoord(int& yCoord){
    // Move border line
    const int vert_speed = -4 - _aisha->getVertSpeed();
    yCoord = yCoord + vert_speed;
}

// Make and Update Game Stats Text
void StudentWorld::updateGameStatsText(){
    std::string scoreText = "Score: " + std::to_string(getScore());
    std::string levelText = "Lvl: " + std::to_string(getLevel());
    int soulsToSave = getLevel() * 2 + 5 - _numSoulsSaved;
    std::string soulsText = "Souls2Save: " + std::to_string(soulsToSave);
    std::string livesText = "Lives: " + std::to_string(getLives());
    std::string healthText = "Health: " + std::to_string(_aisha->getHealth());
    std::string spraysText = "Sprays: " + std::to_string(_aisha->getSpraysLeft());
    std::string bonusText = "Bonus: " + std::to_string(_bonusPoints);
    std::string gameStatsText = scoreText + "  " +  levelText + "  " + soulsText + "  " + livesText + "  " + healthText + "  " + spraysText + "  " + bonusText;
    GameWorld::setGameStatText(gameStatsText); // Update
}

// Check if actor exists within yDistance (in front or in back, positive or negative yDistance, respectively) in the same lane
bool StudentWorld::closeActorInSameLane(const Actor* actor, int yDistance) const{
    // Get left and right boundaries of lane that actor is in
    int leftBoundary, rightBoundary;
    getActorLaneBoundaries(actor->getX(), leftBoundary, rightBoundary);

    // Get top and bottom boundaries given distance
    int topBoundary = 0, bottomBoundary = 0;
    if(yDistance > 0){ // Depending on sign of given distance, adjust bottom and top boundaries
        topBoundary = actor->getY() + yDistance;
        bottomBoundary = actor->getY();
    }else if(yDistance < 0){
        topBoundary = actor->getY();
        bottomBoundary = actor->getY() + yDistance;
    }
    for(std::list<Actor*>::const_iterator it = _actors.begin(); it != _actors.end(); ++it){
        if(*it == actor) // Don't check overlap between the same actor
            continue;
        // For every living collision avoid worthy actor, check if they are in same lane as passed in actor
        if((*it)->isColAvoidWorthy() &&
           (*it)->getX() >= leftBoundary && (*it)->getX() < rightBoundary){
            // If in same lane, check if within vertical boundary
            if((*it)->getY() > bottomBoundary && (*it)->getY() < topBoundary){
                return true;
            }
        }
    }
    return false;
}

// Returns pointer to actor closest to given Y Coord (default entire width)
Actor* StudentWorld::getColAvoidWorthyActorClosestToY(int yCoord, int leftBound, int rightBound) const {
    Actor* closestActor = nullptr;
    for(std::list<Actor*>::const_iterator it = _actors.begin(); it != _actors.end(); ++it){
        // If actor is collision avoid worthy and within the lane
        if((*it)->isColAvoidWorthy() &&
           (*it)->getX() >= leftBound && (*it)->getX() < rightBound){
            if(closestActor == nullptr)
                closestActor = (*it);
            else{
                // Find lesser distance from given Y coordinate (absolute value)
                const double delta_1 = (closestActor->getY() > yCoord) ? (closestActor->getY() - yCoord) : (yCoord - closestActor->getY());
                const double delta_2 = ((*it)->getY() > yCoord) ? ((*it)->getY() - yCoord) : (yCoord - (*it)->getY());
                if(delta_1 > delta_2)
                    closestActor = (*it);
            }
        }
    }
    return closestActor;
}

// Returns if given actor overlaps with GR
bool StudentWorld::overlapsWithAisha(const Actor* actor) const {return isOverlapping(actor, _aisha);}

// Returns pointer to overlapping actor to given actor
Actor* StudentWorld::getOverlappingActorAffectedByHolyWater(const Actor* actor) const{
    for(std::list<Actor*>::const_iterator it = _actors.begin(); it != _actors.end(); ++it){
        if(*it == actor) // Don't check overlap between the same actor
            continue;
        if(isOverlapping(*it, actor) && (*it)->isAffectedByHolyWater()) // If another actor overlaps and is affected by Holy Water
            return *it; // Return pointer to that actor
    }
    return nullptr; // Otherwise return nullptr
}

// Non-member Functions
bool isOverlapping(const Actor* actor1, const Actor* actor2){
    // Get absolute value of deltas
    const double delta_x = (actor1->getX() > actor2->getX()) ? (actor1->getX() - actor2->getX()) : (actor2->getX() - actor1->getX());
    const double delta_y = (actor1->getY() > actor2->getY()) ? (actor1->getY() - actor2->getY()) : (actor2->getY() - actor1->getY());
    const double radius_sum = actor1->getRadius() + actor2->getRadius();
    
    return (delta_x < radius_sum * 0.25 && delta_y < radius_sum * 0.6);
}

// Updates leftXCoord and rightXCoord to boundaries of lane actorXCoord is in
void getActorLaneBoundaries(int actorXCoord, int& leftXCoord, int& rightXCoord){
    // Constants
    const int YELLOW_LINE_LEFT_X = ROAD_CENTER - ROAD_WIDTH / 2;
    const int YELLOW_LINE_RIGHT_X = ROAD_CENTER + ROAD_WIDTH / 2;
    const int WHITE_LINE_LEFT_X = ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH / 3;
    const int WHITE_LINE_RIGHT_X = ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH / 3;
    
    // Actor is in Left Lane
    if(actorXCoord >= YELLOW_LINE_LEFT_X && actorXCoord < WHITE_LINE_LEFT_X){
        leftXCoord = YELLOW_LINE_LEFT_X;
        rightXCoord = WHITE_LINE_LEFT_X;
    } // Actor is in Mid Lane
    else if(actorXCoord >= WHITE_LINE_LEFT_X && actorXCoord < WHITE_LINE_RIGHT_X){
        leftXCoord = WHITE_LINE_LEFT_X;
        rightXCoord = WHITE_LINE_RIGHT_X;
    } // Actor is in Right Lane
    else if(actorXCoord >= WHITE_LINE_RIGHT_X && actorXCoord < YELLOW_LINE_RIGHT_X){
        leftXCoord = WHITE_LINE_RIGHT_X;
        rightXCoord = YELLOW_LINE_RIGHT_X;
    }
}
