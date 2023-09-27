#ifndef SWORD_H
#define SWORD_H


#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword :
    public MeleeWeapon
{
private:

public:
    Sword();
    virtual ~Sword();

     virtual void update(const sf::Vector2f mousePosView, const sf::Vector2f center) ;
    virtual  void render(sf::RenderTarget& target);
};
#endif

