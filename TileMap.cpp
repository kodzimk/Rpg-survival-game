#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize,unsigned width,unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
		std::cout << "Error::TILEMAP LOAD FROM GRASS" << "\n";
}

TileMap::~TileMap()
{
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}


}


//Functions
void TileMap::addTile(const unsigned x,const unsigned y,const unsigned z,const sf::IntRect& texture_rect)
{
	if (x < this->maxSize.x && x >= 0 &&
	    y >= 0 && y < this->maxSize.y &&
	    z < this->layers&& z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF,this->tileTextureSheet,texture_rect);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 &&
		y >= 0 && y < this->maxSize.y &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if(z != NULL)
				   z->render(target);
			}
		}
	}
}

