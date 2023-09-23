#ifndef TILE_H
#define TILE_H

enum TileTypes{DEFAULT = 0,DAMAGING};

class Tile
{
private:


protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(unsigned x, unsigned y,float gridSizeF,const sf::Texture& texture,
		const sf::IntRect& texture_rect, bool collison = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Functions
	const sf::Vector2f& getPosition()const;
	const bool& getCollision()const;
	const std::string getAsString()const;

	void update();
	void render(sf::RenderTarget& target);
};
#endif
