#ifndef BOT_H
#define BOT_H

// stl
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

// project
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"

class Bot
{

public:
	enum Phase {
		NONE,
		PICK_PREFERRED_REGION,
		FIND_BORDERS,
		PLACE_ARMIES,
		ATTACK_TRANSFER
	};

	Bot();
	virtual ~Bot();

	void playGame();    ///< plays a single game of Warlight

	void makeMoves();   ///< makes moves for a single turn

	void addRegion(const unsigned& noRegion, const unsigned& noSuperRegion);
	void addSuperRegion(const unsigned& noSuperRegion, const int& reward);
	void addNeighbors(const unsigned& noRegion, const unsigned& Neighbors);
    void addWasteland(const unsigned& noRegion);
    void addOpponentStartingRegion(const unsigned &noRegion);

    /// Setters for settings
	void setBotName(const std::string& name);
	void setOpponentBotName(const std::string& name);
	void setArmiesLeft(const int& nbArmies);
    void setTimebank(const int& newTimebank);
    void setTimePerMove(const int& newTimePerMove);
    void setMaxRounds(const int&  newMaxRounds);
    void addStartingRegionSetting(const unsigned& noRegion);

	/**
	 * Adds armies to a region
	 * @param noRegion region to add to
	 * @param nbArmies number of Armies
	 */
	void addArmies(const unsigned& noRegion, const int& nbArmies);
	/**
	 * Moves armies on the map
	 * @param noRegion starting region
	 * @param toRegion target region
	 * @param nbArmies number of Armies
	 */
	void moveArmies(const unsigned& noRegion, const unsigned& toRegion, const int& nbArmies);

    void clearStartingRegions();
	void addStartingRegion(const unsigned& noRegion);

    void opponentPlacement(const unsigned& noRegion, const int& nbArmies);
    void opponentMovement(const unsigned& noRegion, const unsigned& toRegion, const int& nbArmies);

	void startDelay(const int& delay);

	void setPhase(const Phase phase);

	/**
	 * Evaluates the current phase and in turn figures out the proper action for the current move
	 * Hook in your army placements and attack moves here
	 */
	void executeAction();
	/**
	 * Updates the regions from the game engine
	 * @param noRegion region identifier
	 * @param playerName player who owns it
	 * @param nbArmies number of armies he gets
	 */
	void updateRegion(const unsigned& noRegion, const std::string& playerName, const int& nbArmies);

	void resetRegionsOwned();

private:
	std::ifstream in;

	std::vector<Region> regions;
	std::vector<SuperRegion> superRegions;
	std::string botName;
	std::string opponentBotName;
    std::vector<int> startingRegionsReceived; // Starting regions which are available to choose from
    std::vector<int> startingRegions; // Every available starting region
    std::vector<int> opponentStartingRegions;
	std::vector<int> ownedRegions;
    std::vector<int> wastelands;
	int armiesLeft;
    int timebank;
    int timePerMove;
    int maxRounds;
	Parser parser;
	Phase phase;
};

#endif // BOT_H
