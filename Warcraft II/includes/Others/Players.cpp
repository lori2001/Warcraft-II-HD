#include "Players.h"

unsigned int Players::playerrace = 1;
unsigned int Players::playerteam = 1;
unsigned int Players::playercolor = 1;

unsigned int Players::ais = 1;
unsigned int Players::ailimit = 11;
unsigned int Players::aidifficulty[11] = { 1,1,1,1,1,1,1,1,1,1,1 };
unsigned int Players::airace[11] = { 1,1,1,1,1,1,1,1,1,1,1 };
unsigned int Players::aiteam[11] = { 2,3,4,5,6,7,8,9,10,11,12 };
unsigned int Players::aicolor[11] = { 2,3,4,5,6,7,8,9,10,11,12 };

bool Players::relativecolors = false;

bool Players::canStart()
{
	bool canstart = false;
	bool onlyspaces = true;
	
	RW::Settings settings; 

	//checks if there are only spaces in the name
	for (std::string::const_iterator i = settings.getName().begin(); i != settings.getName().end(); ++i)
	{
		if (*i != ' ' && *i != '\t')
		{
			onlyspaces = false;
			break;
		}
	}

	if (settings.getName() == "" || onlyspaces) //if the name contains nothing or has only spaces, return false
		return false;

	for (unsigned int i = 0; i < ais; i++) // if any of the teams are different the game can start
	{
		if (aiteam[i] != playerteam)
		{
			canstart = true;
			break;
		}

		for (unsigned int j = i + 1; j < ais; j++)
		{
			if (aiteam[i] != aiteam[j])
			{
				canstart = true;
				break;
			}
		}
		if (canstart)
			break;
	}

	return canstart;
}
void Players::setColorsTeamRelative()
{
	playercolor = playerteam;
	for (int i = 0; i < 11; i++)
	{
		aicolor[i] = aiteam[i];
	}
}
bool Players::setAiColor(const unsigned int & i, const unsigned int & value)
{
	if (!relativecolors) // doublecheck for relativecolors disabled
	{
		bool usedup = false;

		for (unsigned int j = 0; j < ais; j++)
		{
			if ((i != j && value == aicolor[j]) || value == playercolor)
			{
				usedup = true;
				break;
			}
		}

		if (!usedup)
			aicolor[i] = value;
		else
			return false;
	}
	else
		aicolor[i] = aiteam[i];

	return true;
}
void Players::setAiColorsAfter(const unsigned int & from)
{ 
	unsigned int colors[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	for (int i = from; i < 11; i++) // for every ai after the param
	{
		for (int j = 1; j < 12; j++) // for every existing color
		{
			if (setAiColor(i, j)) //if color setting is succesful
			{
				ais++; // adds the color to the ais pool
				break; // break because no further color setting is needed
			}
		}
	}
}
bool Players::setPlayerColor(const unsigned int & value)
{
	if (!relativecolors) // doublecheck for relativecolors disabled
	{
		bool usedup = false;

		for (unsigned int j = 0; j < ais; j++)
		{
			if (value == aicolor[j])
			{
				usedup = true;
				break;
			}
		}

		if (!usedup)
			playercolor = value;
		else
			return false;
	}
	else
		playercolor = playerteam;

	return true;
}
void Players::resetColors()
{
	playercolor = 1;

	for (int i = 0; i < 11; i++)
	{
		aicolor[i] = i + 2;
	}
}
void Players::resetValues()
{
	playerrace = 1;
	playerteam = 1;
	playercolor = 1;
	relativecolors = false;

	ais = 1;
	for (int i = 0; i < 11; i++)
	{
		aidifficulty[i] = 1;
		airace[i] = 1;
		aiteam[i] = i + 2;
		aicolor[i] = i + 2;
	}
}
