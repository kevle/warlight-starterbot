//stl
#include <iostream>
#include <stdlib.h>
#include <stdexcept>

// project
#include "Bot.h"
#include "Parser.h"

Parser::Parser(Bot* bot)
	:theBot(bot)
{
}

Parser::~Parser()
{
}

void Parser::parseInput()
{
	std::string inputType;
	while (std::cin >> inputType)
	{
		if (inputType == "setup_map")
			parseSetupMap();
        else if (inputType == "pick_starting_region")
			parseStartingRegions();
		else if (inputType == "settings")
			parseSettings();
		else if (inputType == "update_map")
			parseUpdateMap();
		else if (inputType == "opponent_moves")
			parseOpponentMoves();
		else if (inputType == "go")
			parseGo();
		theBot->executeAction();
	}
}

void Parser::parseSetupMap()
{
	std::string setupType;
	std::cin >> setupType;
	if (setupType == "super_regions")
		parseSuperRegions();
    else if (setupType == "regions")
		parseRegions();
    else if (setupType == "neighbors")
		parseNeighbors();
    else if (setupType == "wastelands")
        parseWastelands();
    else if (setupType == "opponent_starting_regions ")
        parseOpponentStartingRegions();
}
void Parser::parseStartingRegions()
{
	int region;
	int delay;
	std::cin >> delay;
	theBot->startDelay(delay);
    theBot->clearStartingRegions();
	while (std::cin >> region)
	{
		theBot->addStartingRegion(region);
		if (std::cin.peek() == '\n')
			break;
	}
	theBot->setPhase(Bot::PICK_PREFERRED_REGION);
}
void Parser::parseOpponentStartingRegions()
{
    unsigned noRegion;
    while (std::cin >> noRegion)
    {
        theBot->addOpponentStartingRegion(noRegion);
        if (std::cin.peek() == '\n')
            break;
    }
}

void Parser::parseSettings()
{
	std::string settingType;
	std::cin >> settingType;
	if (settingType == "your_bot")
	{
        std::string bot_name;
		std::cin >> bot_name;
		theBot->setBotName(bot_name);
	}
    else if (settingType == "opponent_bot")
	{
        std::string bot_name;
		std::cin >> bot_name;
		theBot->setOpponentBotName(bot_name);
	}
    else if (settingType == "starting_armies")
	{
        int nbArmies;
		std::cin >> nbArmies;
		theBot->setArmiesLeft(nbArmies);
	}
    else if (settingType == "timebank")
    {
        int timebank;
        std::cin >> timebank;
        theBot->setTimebank(timebank);
    }
    else if (settingType == "time_per_move")
    {
        int timePerMove;
        std::cin >> timePerMove;
        theBot->setTimePerMove(timePerMove);
    }
    else if (settingType == "max_rounds")
    {
        int maxRounds;
        std::cin >> maxRounds;
        theBot->setMaxRounds(maxRounds);
    }
    else if (settingType == "starting_regions")
    {
        parseAllStartingRegions();
    }
}
void Parser::parseAllStartingRegions()
{
    unsigned noRegion;
    while (std::cin >> noRegion)
    {
        theBot->addStartingRegionSetting(noRegion);
        if (std::cin.peek() == '\n')
            break;
    }
}

void Parser::parseUpdateMap()
{
	std::string playerName;
    unsigned noRegion;
    int nbArmies;
	theBot->resetRegionsOwned();
	while (std::cin >> noRegion >> playerName >> nbArmies)
	{
		theBot->updateRegion(noRegion, playerName, nbArmies);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseOpponentMoves()
{

	std::string playerName, action;
    unsigned noRegion, toRegion;
    int nbArmies;
	while (std::cin.peek() != '\n' && std::cin >> playerName >> action)
	{
		if (action == "place_armies")
		{
			std::cin >> noRegion >> nbArmies;
            theBot->opponentPlacement(noRegion, nbArmies);
		}
		if (action == "attack/transfer")
		{
			std::cin >> noRegion >> toRegion >> nbArmies;
            theBot->opponentMovement(noRegion, toRegion, nbArmies);
		}
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseGo()
{
	std::string phase;
	int delay;
	std::cin >> phase >> delay;
	theBot->startDelay(delay);
	if(phase ==  "place_armies")
	{
		theBot->setPhase(Bot::PLACE_ARMIES);
		return;
	}
	if(phase ==   "attack/transfer")
	{
		theBot->setPhase(Bot::ATTACK_TRANSFER);
		return;
	}
	if(phase == "find_borders")
	{
		theBot->setPhase(Bot::FIND_BORDERS);
		return;
	}
	if(phase ==  "pick_preferred_region")
	{
		theBot->setPhase(Bot::PICK_PREFERRED_REGION);
		return;
	}
	throw std::invalid_argument("Cannot handle " + phase + "correctly");
}

void Parser::parseSuperRegions()
{
    unsigned super;
    int reward;
	while (std::cin >> super >> reward)
	{
		theBot->addSuperRegion(super, reward);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseRegions()
{
    unsigned super, region;
	while (std::cin >> region >> super)
	{
		theBot->addRegion(region, super);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseNeighbors()
{

    unsigned region;
	std::string neighbors;
	std::vector<std::string> neighbors_flds;
	while (std::cin >> region >> neighbors)
	{
		neighbors_flds = splitString(neighbors, ',');
		for (unsigned i = 0; i < neighbors_flds.size(); i++)
			theBot->addNeighbors(region, atoi(neighbors_flds[i].c_str()));
		if (std::cin.peek() == '\n')
			break;
	}
	neighbors_flds.clear();
	theBot->setPhase(Bot::FIND_BORDERS);
}

void Parser::parseWastelands()
{
    unsigned region;
    while(std::cin >> region)
    {
        theBot->addWasteland(region);
        if (std::cin.peek()== '\n')
            break;
    }
}

std::vector<std::string> Parser::splitString(const std::string& string, const char& delimiter)
{
	std::vector<std::string> fields;
	std::string buf = "";
	for(size_t i = 0; i < string.size(); ++i)
	{
		if (string[i] != delimiter)
			buf += string[i];
		else
		{
			fields.push_back(buf);
			buf = "";
		}
	}
	if (!buf.empty())
		fields.push_back(buf);
	return fields;
}

