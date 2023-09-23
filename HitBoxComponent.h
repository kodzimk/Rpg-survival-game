#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H


class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitBoxComponent(sf::Sprite&sprite,float offeset_x,float offset_y,float width,float height);
	virtual ~HitBoxComponent();

	//Accessors
	const sf::Vector2f& getPosition()const;
	const sf::FloatRect& getNextPosition(sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x,const float y);

	//Functions
	bool intersect(const sf::FloatRect& frect);
	const sf::FloatRect getGlobalBounds() const;

	void update();
	void render(sf::RenderTarget& target);
};
#endif
