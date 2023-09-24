#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (size_t k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = NULL;
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}

	this->map.clear();
	std::cout << map.size() << "\n";
}

TileMap::TileMap(float gridSize,int width,int height,std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());

			}
		}
	}

	std::cout << map[0][0].size() << std::endl;
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "Error::TILEMAP LOAD FROM GRASS" << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize,gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
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

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < this->map.size())
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < this->map[x][y].size())
			{
				return  this->map[x][y][layer].size();
			}
		}
	}
	return -1;
}


//Functions
void TileMap::addTile(const int x,const int y,const int z,const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
	    y >= 0 && y < this->maxSizeWorldGrid.y &&
	    z < this->layers&& z >= 0)
	{
		this->map[x][y][z].push_back( new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
		}
	}
}

void TileMap::saveToFile(const std::string filename)
{
	std::ofstream out_file;

	out_file.open(filename);


	if (out_file.is_open())
	{
		out_file<< this->maxSizeWorldGrid.x<<" "<<this->maxSizeWorldGrid.y<<"\n"
		 << this->gridSizeU <<"\n"
		 << this->layers<<"\n"
		 <<this->textureFile<<"\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (size_t k= 0; k < this->map[x][y][z].size(); k++)
					{
						if (!this->map[x][y][z].empty())
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString() << " ";
						}
					}
				
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
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;


		this->gridSizeF = gridSize;
		this->gridSizeU = static_cast<int>(gridSize);
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
					for (int i = 0; i < this->map[x][y][this->layer].size(); i++)
					{
						this->map[x][y][this->layer][i] = NULL;
					}
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "Error::TILEMAP LOAD FROM GRASS" << "\n";

		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF,
				this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU,
					this->gridSizeU), collision, type));
		}
	}
	else
	{
		std::cout << "ERROR TILEMAP COULD NOT lLOAD FROM TO FILE";
	}

	in_file.close();
}

void TileMap::renderDeferred(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		this->deferredRenderStack.top()->render(target);
		this->deferredRenderStack.pop();
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 4;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 5;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 3;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 5;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	this->layer = 0;


	for (int x = this->fromY; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k])
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
					{
						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
						this->map[x][y][this->layer][k]->render(target);

						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			
			}
		}
	
		//for (auto& x : this->map)
		//{
		//	for (auto& y : x)
		//	{
		//		for (auto &z : y)
		//		{
		//			for (auto* k : z)
		//			{
		//				if (k )
		//				{
		//					k->render(target);
		//					if (k->getCollision())
		//					{
		//						this->collisionBox.setPosition(k->getPosition());
		//						target.draw(this->collisionBox);
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	
	
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGloabalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGloabalBounds().width , entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}

	else if (entity->getPosition().y + entity->getGloabalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGloabalBounds().height);
		entity->stopVelocityY();
	}

	this->fromX = entity->getGridPosition(this->gridSizeU).x - 5;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeU).x + 8;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeU).y -5;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeU).y + 8;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	this->layer = 0;


	for (int x = this->fromY; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k])
				{
					sf::FloatRect playerBounds = entity->getGloabalBounds();
					sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
					sf::FloatRect nextPositionBounds = entity->getNextPositionsBounds(dt);

					if (this->map[x][y][this->layer][k]->getCollision() &&
						this->map[x][y][this->layer][k]->intersects(nextPositionBounds))
					{
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left <wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width >wallBounds.left)
						{
							entity->stopVelocity();
							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}
						else  if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left <wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width >wallBounds.left)
						{
							entity->stopVelocity();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}


						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top <wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height >wallBounds.top)
						{
							entity->stopVelocity();
							entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top <wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height >wallBounds.top)
						{
							entity->stopVelocity();
							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}
	}
}

