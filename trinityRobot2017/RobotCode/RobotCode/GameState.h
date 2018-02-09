#pragma once
#include <vector>
#include "constants.h"

using namespace std;
//right now we don;t have baby as a target type wut
//we need baby to be atarget type
struct GameState {

	GameState(int _levelOfCompetition = 1, int _numCandlesExtinguished = 0, bool _babySaved = false, bool _babyObtained = false, bool _safeZoneFound = false,  bool _inRoom = true, bool _secondArena){
		levelOfCompetition = _levelOfCompetition;
		numCandlesExtinguished = _numCandlesExtinguished;
		babySaved = _babySaved;
		babyObtained = _babyObtained;
		safeZoneFound = _safeZoneFound;
		inRoom = _inRoom;
		secondArena = _secondArena;
	}

	int levelOfCompetition;
	int numCandlesExtinguished;
	bool babySaved;
	bool babyObtained;
	bool safeZoneFound;
	bool inRoom;
	bool secondArena;

	vector<int> getTargetType() {
		//returns what kind of objects (in order or priority) to look for in the important object map before resorting to exploring
		vector<int> targets;
		if (levelOfCompetition != 3 || babySaved) {
			targets.push_back(FLAME);
			targets.push_back(CANDLE);
			targets.push_back(DOOR);
			return targets;
		}

		//level 3, baby not saved
		if (babyObtained) {
			//we have the baby we just need to shove it out the window
			targets.push_back(SAFE_ZONE);
			return targets;
		}
		//we have not found the baby
		else {
			if (!secondArena)
				targets.push_back(HALLWAY);
			else {
				targets.push_back(RED_SIDE_CRADLE);
				targets.push_back(BLUE_SIDE_CRADLE);
				targets.push_back(GREEN_SIDE_CRADLE);
				targets.push_back(DOOR);//no need to differentiate entering and exiting room here, that's done outside
			}
		}
		return targets;
	}
};
