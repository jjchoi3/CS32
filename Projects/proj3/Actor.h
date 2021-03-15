#ifndef ACTOR_H_
#define ACTOR_H_

#include <iostream>
#include <string>
#include "GraphObject.h"
#include "GameConstants.h"

// Class Protoypes
class StudentWorld;

class Actor : public GraphObject {
public:
    // Constructor
    Actor(int imgId, int xCoord, int yCoord, int dxn, double size, int depth, bool colAvoidWorthy, int vertSpeed, int horizSpeed, bool affectedByHolyWater, StudentWorld* sw):
    GraphObject(imgId, xCoord, yCoord, dxn, size, depth),
    _colAvoidWorthy(colAvoidWorthy),
    _isAlive(true),
    _vertSpeed(vertSpeed), _horizSpeed(horizSpeed),
    _studentWorld(sw),
    _affectedByHolyWater(affectedByHolyWater)
    {}
    // Destructor
    virtual ~Actor(){}
    
    // Accessor Member Functions
    bool isColAvoidWorthy() const {return _colAvoidWorthy;}
    bool isAffectedByHolyWater() const {return _affectedByHolyWater;}
    virtual bool isAlive() const {return _isAlive;}
    int getVertSpeed() const {return _vertSpeed;}
    int getHorizSpeed() const {return _horizSpeed;}
    
    
    virtual void hitByHolyWater(){return;};
    
    // Pure Virtual Functions
    virtual void doSomething() = 0;
    
protected:
    // Accessor Member Functions
    StudentWorld* getWorld() const {return _studentWorld;}
    
    bool overlapsWithAisha(const Actor* actor) const;
    
    // Mutator Member functions
    virtual void killActor(){_isAlive = false;}
    virtual void moveActor();
    
    void setVertSpeed(int speed) {_vertSpeed = speed;}
    void setHorizSpeed(int speed) {_horizSpeed = speed;}
    
private:
    StudentWorld* _studentWorld;
    
    bool _colAvoidWorthy;
    bool _isAlive;
    bool _affectedByHolyWater;
    
    int _vertSpeed;
    int _horizSpeed;
};

class HitPointActor : public Actor {
public:
    // Constructor
    HitPointActor(int imgId, int xCoord, int yCoord, int dxn, double size, int depth, int vertSpeed, int horizSpeed, bool affectedByHolyWater, StudentWorld* sw, int healthPoints):
    Actor(imgId, xCoord, yCoord, dxn, size, depth, true, vertSpeed, horizSpeed,affectedByHolyWater, sw),
    _hitPoints(healthPoints){}
    
    // Destructor
    virtual ~HitPointActor(){}
    
    // Accessor Member Functions
    bool isAlive() const {return _hitPoints > 0;}
    int getHealth() const {return _hitPoints;}
    
    // Mutator Member Functions
    void damageActor(int damageBy=1); // Default damage by 1 point
    void killActor();
    
protected:
    // Mutator Member Functions
    void setHitPoints(int points){_hitPoints = points;}

private:
    int _hitPoints;
};

class MovingNPC : public HitPointActor {
public:
    // Constructor
    MovingNPC(int imgId, int xCoord, int yCoord, int dxn, double size, int depth, int vertSpeed, int horizSpeed, StudentWorld*sw, int healthPoints, int movePlanDist):
    HitPointActor(imgId, xCoord, yCoord, dxn, size, depth, vertSpeed, horizSpeed, true, sw, healthPoints),
    _movePlanDistance(movePlanDist){}
    
    // Destructor
    virtual ~MovingNPC(){}
    
protected:
    // Accessor Member Functions
    int getMovePlanDistance() const{return _movePlanDistance;}
    
    // Mutator Member Functions
    virtual void killedByHolyWater(int sound, int scoreAmount);
    void setMovePlanDistance(int dist){_movePlanDistance = dist;}
    void hitByHolyWater(){damageActor();}
    
private:
    int _movePlanDistance = 0;
};

class Goodie : public Actor {
public:
    // Constructor
    Goodie(int imgId, int xCoord, int yCoord, int dxn, double size, int depth, int vertSpeed, int horizSpeed, bool affectedByHolyWater, StudentWorld* sw):
    Actor(imgId, xCoord, yCoord, dxn, size, depth, false, vertSpeed, horizSpeed, affectedByHolyWater, sw){}
    
    // Destructor
    virtual ~Goodie(){}
    
protected:
    // Mutator Member Function
    virtual void hitByHolyWater() {killActor();}
    
    // Mutator Member Function
    virtual void activate(int sound, int scoreAmount);
};

class GhostRacer : public HitPointActor {
public:
    // Constructor
    GhostRacer(int xCoord, int yCoord, StudentWorld* sw):
    HitPointActor(IID_GHOST_RACER, xCoord, yCoord, 90, 4, 0, 0, 0, false, sw, 100),
    _holyWater(10){}
    
    // Accessor Member Functions
    int getSpraysLeft() const{return _holyWater;}
    
    // Mutator Member Functions
    void doSomething();
    void moveActor();
    
    void spinCar();
    void addHolyWater(int amt){ _holyWater += amt;}
    
    void healActor(int amt);
    
private:
    int _holyWater;
    
    // Mutator Member Functions
    void changeDirection();
    void shootHolyWater();
};

class BorderLine : public Actor { // Could be a struct
public:
    // Constructor
    BorderLine(int borderColor, int xCoord, int yCoord, StudentWorld* sw):
    Actor(borderColor, xCoord, yCoord, 0, 2.0, 1, false, -4, 0, false, sw)
    {}
    
    // Destructor
    virtual ~BorderLine(){}
    
    // Mutator Member Functions
    virtual void doSomething();
};

class HumanPedestrian : public MovingNPC {
public:
    // Constructor
    HumanPedestrian(int xCoord, int yCoord, StudentWorld* sw):
    MovingNPC(IID_HUMAN_PED, xCoord, yCoord, 0, 2.0, 0, -4, 0, sw, 2, 0){}
    
    // Destructor
    virtual ~HumanPedestrian(){}
    
    // Mutator Member Function
    void doSomething();
protected:
    // Mutator Member Functions
    void hitByHolyWater();
};

class ZombiePedestrian : public MovingNPC {
public:
    // Constructor
    ZombiePedestrian(int xCoord, int yCoord, StudentWorld* sw):
    MovingNPC(IID_ZOMBIE_PED, xCoord, yCoord, 0, 3.0, 0, -4, 0, sw, 2, 0),
    _ticksUntilGrunt(0){}
    
    // Destructor
    virtual ~ZombiePedestrian(){}

    // Mutator Member Functions
    void doSomething();
    
protected:
    // Mutator Member Functions
    void killedByHolyWater(int sound, int scoreAmount);
    void hitByHolyWater();
    
private:
    int _ticksUntilGrunt;
};

class ZombieCab : public MovingNPC {
public:
    // Constructor
    ZombieCab(int xCoord, int yCoord, int vertSpeed, StudentWorld* sw):
    MovingNPC(IID_ZOMBIE_CAB, xCoord, yCoord, 90, 4.0, 0, vertSpeed, 0, sw, 3, 0),
    _hasDamagedGhostRacer(false){}

    // Destructor
    virtual ~ZombieCab(){}
    
    // Mutator Member Functions
    void doSomething();
    
protected:
    // Mutator Member Functions
    virtual void killedByHolyWater(int sound, int scoreAmount);
    void hitByHolyWater();
    
private:
    bool _hasDamagedGhostRacer;
};

class OilSlick : public Actor {
public:
    // Constructor
    OilSlick(int xCoord, int yCoord, StudentWorld* sw):
    Actor(IID_OIL_SLICK, xCoord, yCoord, 0, randInt(2, 5), 1.0, false, -4, 0, false, sw){}
    
    // Destructor
    ~OilSlick(){}
    
    // Mutator Member Functions
    virtual void doSomething();
};

class HealingGoodie : public Goodie {
public:
    // Public
    HealingGoodie(int xCoord, int yCoord, StudentWorld* sw):
    Goodie(IID_HEAL_GOODIE, xCoord, yCoord, 0, 1.0, 2, -4, 0, true, sw){}
    
    // Destructor
    virtual ~HealingGoodie(){}
    
    // Mutator Member Functions
    virtual void doSomething();
    
protected:
    // Mutator Member Functions
    virtual void activate(int sound, int scoreAmount);
};

class HolyWaterGoodie : public Goodie {
public:
    // Constructor
    HolyWaterGoodie(int xCoord, int yCoord, StudentWorld* sw):
    Goodie(IID_HOLY_WATER_GOODIE, xCoord, yCoord, 90, 2.0, 2, -4, 0, true, sw){}
    
    // Destructor
    virtual ~HolyWaterGoodie(){}
    
    // Mutator Member Functions
    virtual void doSomething();
    
protected:
    // Mutator Member Functions
    virtual void activate(int sound, int scoreAmount);
};

class SoulGoodie : public Goodie {
public:
    // Constructor
    SoulGoodie(int xCoord, int yCoord, StudentWorld* sw):
    Goodie(IID_SOUL_GOODIE, xCoord, yCoord, 0, 4.0, 2, -4, 0, false, sw){}
    
    // Destructor
    virtual ~SoulGoodie(){}
    
    // Mutator Member Functions
    virtual void doSomething();
    
protected:
    // Mutator Member Functions
    virtual void activate(int sound, int scoreAmount);
};

class HolyWaterProjectile : public Actor {
public:
    // Constructor
    HolyWaterProjectile(int xCoord, int yCoord, int dxn, StudentWorld* sw):
    Actor(IID_HOLY_WATER_PROJECTILE, xCoord, yCoord, dxn, 1, 1, false, 0, 0, false, sw),
    _distanceTraveled(0){}
    
    // Mutator Member Functions
    void doSomething();
    
protected:
    void moveActor();
    
private:
    int _distanceTraveled;
    bool _hasActivated;
};
#endif // ACTOR_H_
