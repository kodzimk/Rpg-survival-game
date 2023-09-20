#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite),textureSheet(texture_sheet),lastAnimation(NULL),priorityAnimation(NULL)
{
	
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animtions)
	{
		delete i.second;
	}
	
}


//Accessors

const bool& AnimationComponent::isDone(const std::string key) 
{
	return this->animtions[key]->isDone();
}


//Functions
void AnimationComponent::addAnimation(const std::string key,   float animation_timer,int start_frame_x,
	int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animtions[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key,const float & dt,const bool priority )
{

	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animtions[key])
		{
			if (this->lastAnimation != this->animtions[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animtions[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animtions[key];
				}
			}

			if (this->animtions[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animtions[key];
		}

		if (this->lastAnimation != this->animtions[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animtions[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animtions[key];
			}
		}

		this->animtions[key]->play(dt);
	}
	return this->animtions[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt,const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animtions[key])
		{
			if (this->lastAnimation != this->animtions[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animtions[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animtions[key];
				}
			}

			if (this->animtions[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animtions[key];
		}

		if (this->lastAnimation != this->animtions[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animtions[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animtions[key];
			}
		}

		this->animtions[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animtions[key]->isDone();
}
