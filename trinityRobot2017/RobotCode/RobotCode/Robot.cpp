#include "Robot.h"
#include <thread>

using namespace std;


// made using this video: https://www.youtube.com/watch?v=LL8wkskDlbs

Robot::Robot():
	robotPos(gridSize/2, gridSize/2), mazeMapper(), robotAngle(0), drive(), gameState(),
	safeZoneLocation(), colorSensor(), IRsensor(), camera()
{
	// variables are initialized through the constructor for now
}

///////////////////////////

void Robot::start(void) {
	// maybe this can go in the constructor in the future
	// Thread dedicated to looping the lazer scanner until the robot dies.
	thread laserScanInputThread(&MazeMapper::laserScanLoop, mazeMapper);
	laserScanInputThread.detach(); // thread should run freely on its own ( this function doesn't wait for it to finish)

	// Let's start this thing
	robotLoop();
}

///////////////////////////

// I'm not sure when to update these GameState variables..
//bool safeZoneFound;
//bool inRoom;
//bool secondArena;


void Robot::robotLoop(void){
	// initialize to nothing (doesn't really matter)
	MazeMapper::robotOps nextRobotOperation = MazeMapper::robotOps::NOTHING;
	// our path variable
	vector<Point> nextPath;
	bool done = false;
	while (!done) {
		// most important line of the program?
		nextPath = mazeMapper.findNextTarget(gameState, nextRobotOperation);

		// always drive to next location, then do other stuff depending on nextRobotOperation
		robotDrive(nextPath);

		// switch the nextRobotOperation variable and act accordingly
		switch (nextRobotOperation) {
		case MazeMapper::NOTHING:
			// This is here for formality
			break;
		case MazeMapper::CRADLE_FRONT:
			goToSideFromFront();
		case MazeMapper::CRADLE_SIDE:
			getBaby();
			gameState.babyObtained = true;
			break;
		case MazeMapper::SAFEZONE:
			tossBaby();
			gameState.babySaved = true;
			break;
		case MazeMapper::EXTINGUISH:
			blowCandle();
			gameState.numCandlesExtinguished++;
			break;
		//differentiation between scanroom and exitroom occurs when door is target,
		//return scan or exit based on whether or not currently in room.
		case MazeMapper::SCANROOM:
			spinAndScan();
			gameState.inRoom = true;
			break;
		case MazeMapper::EXITROOM:
			leaveRoom(); //doesn't do the spin move enter room has
			gameState.inRoom = false;
			break;
		case MazeMapper::HALLWAY:
			hallwaySweep();
			break;
		case MazeMapper::HALLWAY_SIMPLE:
			hallwaySimple();
			break;
		case MazeMapper::STOP:
			done = true;
			break;
		}
		// annnnd.. repeat
		break; // without break, code will keep on running forever. Remove this when we start serious testing.
	}
}

void Robot::robotDrive(vector<Point> instructions) {
	// Idk how this will work exactly
	//drive.drive(vector<Point> instructions)
	//drive.rotate(int numDegrees)
	//drive.drive(instructions);
}

void Robot::getBaby(void) {
	//get Camera data
	//rotate robot to face the cradle /  move robot to be centered
	//
	//align robot facing cradle and do whatever we need to do to operate the arm, Matt needs to talk to mechanical for that
}
void Robot::tossBaby(void) {
	//align robot facing window and do whatever we need to do to throw the baby out the window
}
void Robot::blowCandle(void) {
	gameState.numCandlesExtinguished++;
	//point robot at candle (can be done via lidar or ir sensor alignment), then activate easy valve
}
void Robot::spinAndScan(void) {
	//MazeMapper.targetPoints[FLAME].push_back(flame_location)
	//robot will be in appropriate position, so just spin around and get flame and camera data,
	//updating the important points vector as necessary
}
void Robot::hallwaySweep(void) {
	/*
	(potentially) : drive down the hallway, using lidar to detect once we have exited the hallway.
	Then turn the robot so camera is facing back where we came from(so it�ll detect the safezone target)
	then drive the robot sideways through each of the side hallways.Theoretically this should guarantee
	that we find the correct window.
	*/
}
