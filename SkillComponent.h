#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H


class SkillComponent
{
private:
	class Skill
	{
	private:
		int level;
		int levelCap;
		int exp;
		int expNext;

	public:
		Skill()	
		{
			this->level = 1;
			this->exp = 0;
			this->levelCap = 99;
			this->expNext = 100;
		}
		~Skill(){}

		inline const int& getLevel() const
		{
			return this->level;
		}
		inline const int& getExp() const
		{
			return this->exp;
		}
		inline const int& getExpNext() const
		{
			return this->expNext;
		}

		void setLevel(const int level) { this->level = level; }
		void setLevelCap(const int level) { this->levelCap = level; }

		 void gainExp(const int exp) { 
			this->exp += exp; 
			this->updateLevel(); 
		}

		 void loseExp(const int exp)
		 {
			 this->exp -= exp;
		 }

		void updateLevel(const bool up = true)
		{
			if (up)
			{
				if (this->exp >= this->expNext)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelCap)
						{
							this->level++;
							this->expNext = std::pow(this->level, 2) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->exp < 0)
					{
						if (this->level > 0)
						{
							this->level++;
							this->exp = 0;
							this->expNext = std::pow(this->level, 2) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
		}

		void update()
		{
			
		}
	};

	std::map<std::string, Skill> skills;

public:
	SkillComponent();
	virtual ~SkillComponent();

	const int getSkill(std::string key)const;
};
#endif

