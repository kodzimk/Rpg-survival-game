#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H


#include "Item.h"


class MeleeWeapon :
    public Item
{
private:

protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapon_texture;

    int damageMin;
    int damageMax;

public:
    MeleeWeapon();
    virtual ~MeleeWeapon();

    virtual void update(const sf::Vector2f mousePosView,const sf::Vector2f center)= 0;
    virtual void render(sf::RenderTarget& target) = 0;

};
#endif

