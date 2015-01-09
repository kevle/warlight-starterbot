#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

//stl
#include <stdio.h>
#include <string>
#include <vector>

// tools
#include "tools/noncopyable.hpp"

class Bot;

class Parser: boost::noncopyable
{
public:
	Parser(Bot* bot);
	virtual ~Parser();

	void parseInput();

private:
	Parser();
	Bot* theBot;

	// helper function for the case we want to handle \r\n in future
	inline bool lineEnds()
	{
		return bool(std::cin.peek() == '\n');
	}

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
	void parseOpponentStartingRegions();
	void parsePickStartingRegion();

	std::vector<std::string> splitString(const std::string& string, const char& delimiter);
};

#endif // PARSER_H_INCLUDED
