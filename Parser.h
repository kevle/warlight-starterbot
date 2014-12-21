#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

//stl
#include <stdio.h>
#include <string>
#include <vector>

class Bot;

class Parser
{
public:
	Parser(Bot* bot);
	virtual ~Parser();

	void parseInput();

private:
	Bot* theBot;

    void parseSetupMap();
    void parseStartingRegions();
    void parseSettings();
    void parseUpdateMap();
    void parseOpponentMoves();
    void parseGo();
    void parseSuperRegions();
    void parseRegions();
    void parseNeighbors();
    void parseWastelands();
    void parseAllStartingRegions();
    void parseOpponentStartingRegions();

    std::vector<std::string> splitString(const std::string& string, const char& delimiter);
};

#endif // PARSER_H_INCLUDED
