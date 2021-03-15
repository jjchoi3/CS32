#include "Actor.h"
#include "StudentWorld.h"

#define PI 3.14159265

// Actor Implementation
void Actor::moveActor(){
    // Move border line
    const int vert_speed = getVertSpeed() - getWorld()->getAisha()->getVertSpeed();
    const int horiz_speed = getHorizSpeed();
    
    const int new_y = getY() + vert_speed;
    const int new_x = getX() + horiz_speed;
    moveTo(new_x, new_y);
        
    // If Border Line is out of bounds, kill it
    if(getX() < 0 || getY() < 0  ||
       getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT){
        killActor();
        return;
    }
}
bool Actor::overlapsWithAisha(const Actor *actor) const{return _studentWorld->overlapsWithAisha(actor);}

// MovingNPC Implementation
void MovingNPC::killedByHolyWater(int sound, int scoreAmount){
    killActor();
    getWorld()->playSound(sound);
    getWorld()->increaseScore(scoreAmount);
}

// HitPointActor Implementation
void HitPointActor::damageActor(int damageBy){
    _hitPoints-=damageBy;
    if(!isAlive())
        Actor::killActor();
}
void HitPointActor::killActor(){
    _hitPoints = 0;
    Actor::killActor();
}

// Goodie Implementation
// Same Implementation as MovingNPC::killedByHolyWater but serves very different purpose; should not abstract
void Goodie::activate(int sound, int scoreAmount){
    killActor();
    getWorld()->playSound(sound);
    getWorld()->increaseScore(scoreAmount);
}

// GhostRacer Implementation
void GhostRacer::doSomething(){
    if(!isAlive())
        return;
    
    // If GR Left of Left Boundary
    if(getX() <= ROAD_CENTER - ROAD_WIDTH / 2){
        if(getDirection() > 90)
            damageActor(10);
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        moveActor();
        return;
    }// If GR Right of Right Boundary
    else if(getX() >= ROAD_CENTER + ROAD_WIDTH / 2){
        if(getDirection() < 90)
            damageActor(10);
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        moveActor();
        return;
    }
    // Keystroke Interpretation and Reaction
    changeDirection();
    moveActor();
}
void GhostRacer::moveActor(){
    const double max_shift_per_tick = 4.0;
    const double direction = PI * getDirection() / 180;
    const double delta_x = cos(direction) * max_shift_per_tick;
    const double cur_x = getX();
    const double cur_y = getY();

    moveTo(cur_x + delta_x, cur_y);
}
void GhostRacer::changeDirection(){
    int ch;
    if(Actor::getWorld()->getKey(ch)){
        // User hit a key during this tick
        switch(ch){
            case KEY_PRESS_SPACE:
                if(getSpraysLeft() > 0)
                    shootHolyWater();
                break;
            case KEY_PRESS_LEFT:
                if(getDirection() < 114)
                    setDirection(GraphObject::getDirection() + 8);
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() > 66)
                    setDirection(GraphObject::getDirection() - 8);
                break;
            case KEY_PRESS_UP:
                if(getVertSpeed() < 5)
                    setVertSpeed(getVertSpeed() + 1);
                break;
            case KEY_PRESS_DOWN:
                if(getVertSpeed() > -1)
                    setVertSpeed(getVertSpeed() - 1);
                break;
        }
    }
}
void GhostRacer::shootHolyWater(){
    const double direction = PI * getDirection() / 180;
    const double delta_x = (cos(direction) >= 0) ? cos(direction) * SPRITE_HEIGHT : -cos(direction) * SPRITE_HEIGHT;
    const double delta_y = sin(direction) * SPRITE_HEIGHT;
    const double cur_x = getX();
    const double cur_y = getY();
    
    getWorld()->addHolyWaterProjectile(cur_x + delta_x, cur_y + delta_y, GraphObject::getDirection());
    getWorld()->playSound(SOUND_PLAYER_SPRAY);
    addHolyWater(-1); // Decrement amount of holy water
}
void GhostRacer::spinCar(){
    const int spinAmt = randInt(5, 20);
    const int spinDxn = randInt(0, 1) ? -1 : 1;
    
    const int newDxn = getDirection() + spinAmt * spinDxn;
    if(newDxn < 60)
        setDirection(60);
    else if(newDxn > 120)
        setDirection(120);
    else
        setDirection(newDxn);
}
void GhostRacer::healActor(int amt){
    if(getHealth() + amt > 100)
        setHitPoints(100);
    else
        damageActor(-amt);
}

// BorderLine Implementation
void BorderLine::doSomething(){moveActor();}

// HumanPedestrian Implementation
void HumanPedestrian::doSomething(){
    if(!isAlive())
        return;
    
    if(overlapsWithAisha(this)){
        getWorld()->getAisha()->killActor();
        return;
    }
    
    moveActor();
    setMovePlanDistance(getMovePlanDistance() - 1);
    
    if(getMovePlanDistance() > 0)
        return;
    int new_horiz_speed = 0;
    while(new_horiz_speed == 0)
        new_horiz_speed = randInt(-3, 3);
    setHorizSpeed(new_horiz_speed); // Set Horiz Speed to random number from -3 to 3 not including 0
    setMovePlanDistance(randInt(4, 32));
    if(new_horiz_speed < 0)
        setDirection(180);
    else
        setDirection(0);
}
void HumanPedestrian::hitByHolyWater(){
    // Change Horizontal Speed
    const int new_horiz_speed = -getHorizSpeed();
    setHorizSpeed(new_horiz_speed);
    
    // Change direction
    const int new_dxn = (getDirection() == 0) ? 180 : 0;
    setDirection(new_dxn);
    getWorld()->playSound(SOUND_PED_HURT);
}

// ZombiePedestrian Implementation
void ZombiePedestrian::doSomething(){ // TODO : OTHER CIRCUMSTANCES
    if(!isAlive())
        return;

    // Pointer to GR
    GhostRacer* aisha = getWorld()->getAisha();
    
    if(overlapsWithAisha(this)){
        aisha->damageActor(5);
        damageActor(2);
        return;
    }
    
    // If Zombie Ped's X coord is within 30 px of GR's X coord
    // AND Zombie Ped is in front of GR
    const unsigned int delta_x = (getX() > aisha->getX()) ? getX() - aisha->getX() : aisha->getX() - getX();
    if((delta_x <= 30) && getY() > aisha->getY()){
        setDirection(270);
        
        // If Zombie Ped is left of GR
        if(getX() - aisha->getX() < 0)
            setHorizSpeed(1);
        // If Zombie Ped is left of GR
        else if(getX() - aisha->getX() > 0)
            setHorizSpeed(-1);
        else
            setHorizSpeed(0);
        
        _ticksUntilGrunt--;
        if(_ticksUntilGrunt <= 0){ // If it's time to grunt!
            getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
            _ticksUntilGrunt = 20;
        }
    }
    moveActor();
    if(getMovePlanDistance() > 0){
        setMovePlanDistance(getMovePlanDistance() - 1);
        return;
    }
    
    int new_horiz_speed = 0;
    while(new_horiz_speed == 0)
        new_horiz_speed = randInt(-3, 3);
    
    setHorizSpeed(new_horiz_speed);
    setMovePlanDistance(randInt(4, 32));
    if(new_horiz_speed < 0)
        setDirection(180);
    else
        setDirection(0);
}
void ZombiePedestrian::hitByHolyWater(){
    MovingNPC::hitByHolyWater();
    if(getHealth() <= 0){
        killedByHolyWater(SOUND_PED_DIE, 150);
        return;
    }else{
        getWorld()->playSound(SOUND_PED_HURT);
    }
}
void ZombiePedestrian::killedByHolyWater(int sound, int scoreAmount){
    MovingNPC::killedByHolyWater(sound, scoreAmount);
    if(!overlapsWithAisha(this)){ // If Zombie Ped didn't die from overlapping
        if(randInt(0, 4) == 0) // 1 in 5 chance of spawning HealingGoodie
            getWorld()->addHealingGoodie(getX(), getY());
    }
}

// HealingGoodie Implementation
void HealingGoodie::doSomething(){
    moveActor();
    // Activate if overlaps
    if(overlapsWithAisha(this)){activate(SOUND_GOT_GOODIE, 250);}
}
void HealingGoodie::activate(int sound, int scoreAmount){
    getWorld()->getAisha()->healActor(10);
    Goodie::activate(sound, scoreAmount);
}

// HolyWaterGoodie Implementation
void HolyWaterGoodie::doSomething(){
    moveActor();
    // Activate if overlaps
    if(overlapsWithAisha(this)){activate(SOUND_GOT_GOODIE, 50);}
}
void HolyWaterGoodie::activate(int sound, int scoreAmount){
    getWorld()->getAisha()->addHolyWater(10);
    Goodie::activate(sound, scoreAmount);
}

// SoulGoodie Implementation
void SoulGoodie::doSomething(){
    moveActor();
    if(overlapsWithAisha(this)){activate(SOUND_GOT_SOUL, 100);}
    setDirection(getDirection() - 10);
}
void SoulGoodie::activate(int sound, int scoreAmount){
    getWorld()->incrementSoulsSaved();
    Goodie::activate(sound, scoreAmount);
}

// ZombieCab Implementation
void ZombieCab::doSomething(){
    if(!Actor::isAlive())
        return;
    
    // Pointer to GR
    GhostRacer* aisha = getWorld()->getAisha();
    
    if(overlapsWithAisha(this) && !_hasDamagedGhostRacer){ // Check if overlapping AND hasn't damaged Ghost Racer Already
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        aisha->damageActor(20);
        // If Zombie Cab is left of GR
        if(getX() - aisha->getX() <= 0){
            setHorizSpeed(-5);
            setDirection(120 + randInt(0, 19));
        }// If Zombie Cab is right of GR
        else if(getX() - aisha->getX() > 0){
            setHorizSpeed(5);
            setDirection(60 - randInt(0, 19));
        }
        _hasDamagedGhostRacer = true;
    }
    moveActor();
    if(getVertSpeed() > aisha->getVertSpeed()){
        // If Zombie Cab is is within 96 px of an actor in front in the same lane
        if(getWorld()->closeActorInSameLane(this, 96)){
            setVertSpeed(getVertSpeed() - 0.5);
            return;
        }
    }else if(getVertSpeed() <= aisha->getVertSpeed()){
        // If Zombie Cab is is within 96 px of an actor behind in the same lane
        if(getWorld()->closeActorInSameLane(this, -96)){
            setVertSpeed(getVertSpeed() + 0.5);
            return;
        }
    }
    setMovePlanDistance(getMovePlanDistance() - 1);
    if(getMovePlanDistance() > 0)
        return;
    setMovePlanDistance(randInt(4, 32));
    setVertSpeed(getVertSpeed() + randInt(-2, 2));
}
void ZombieCab::hitByHolyWater(){
    MovingNPC::hitByHolyWater();
    if(getHealth() <= 0){
        killedByHolyWater(SOUND_VEHICLE_DIE, 200);
        return;
    }else{
        getWorld()->playSound(SOUND_VEHICLE_HURT);
    }
}
void ZombieCab::killedByHolyWater(int sound, int scoreAmount){
    MovingNPC::killedByHolyWater(sound, scoreAmount);
    if(randInt(0, 4) == 0) // 1 in 5 chance of spawning OilSlick
        getWorld()->addOilSlick(getX(), getY());
}

// OilSlick Implementation
void OilSlick::doSomething(){
    moveActor();
    // Activate if it overlaps with GR
    if(overlapsWithAisha(this)){
        getWorld()->playSound(SOUND_OIL_SLICK);
        getWorld()->getAisha()->spinCar();
    }
}

// HolyWaterProjectile Implementation
void HolyWaterProjectile::doSomething(){
    if(!isAlive())
        return;
    // Get overlapping actor if one exists
    Actor* overlappingActor = getWorld()->getOverlappingActorAffectedByHolyWater(this);

    if(overlappingActor != nullptr){
        Actor* overlappingActor = getWorld()->getOverlappingActorAffectedByHolyWater(this);
        overlappingActor->hitByHolyWater();
        killActor();
        return;
    }
    moveActor();
}

void HolyWaterProjectile::moveActor(){
    moveForward(SPRITE_HEIGHT);
    _distanceTraveled++;
    if(getX() < 0 || getY() < 0 ||
       getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT){
        killActor();
        return;
    }
    else if(_distanceTraveled >= 160)
        killActor();
}
