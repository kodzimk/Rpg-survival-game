#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}

	this->map.clear();
	std::cout << map.size() << "\n";
}

TileMap::TileMap(float gridSize,unsigned width,unsigned height,std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

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

	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "Error::TILEMAP LOAD FROM GRASS" << "\n";
}

TileMap::~TileMap()
{
	this->clear();
}

//Accessors
const sf::Texture* TileMap::getTileSheet()const
{
	return &this->tileSheet;
}


//Functions
void TileMap::addTile(const unsigned x,const unsigned y,const unsigned z,const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSize.x && x >= 0 &&
	    y >= 0 && y < this->maxSize.y &&
	    z < this->layers&& z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF,this->tileSheet,texture_rect,collision,type);
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

void TileMap::saveToFile(const std::string filename)
{
	std::ofstream out_file;

	out_file.open(filename);


	if (out_file.is_open())
	{
		out_file<< this->maxSize.x<<" "<<this->maxSize.y<<"\n"
		 << this->gridSizeU <<"\n"
		 << this->layers<<"\n"
		 <<this->textureFile<<"\n";

		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
			       out_file << x<<" "<<y<<" "<<z<<" "<< this->map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR TILEMAP COULD NOT SAVE TO FILE";
	}

	out_file.close();
	
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);


	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		in_file >> size.x >> size.y >> gridSize >> layers >>texture_file;


		this->gridSizeF = gridSize;
		this->gridSizeU = static_cast<unsigned>(gridSize);
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

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

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "Error::TILEMAP LOAD FROM GRASS" << "\n";

		while (in_file>>x >> y >> z>>trX>>trY>>collision>>type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF,
			this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU,
			this->gridSizeU), collision, type);
		}
	}
	else
	{
		std::cout << "ERROR TILEMAP COULD NOT lLOAD FROM TO FILE";
	}

	in_file.close();
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

