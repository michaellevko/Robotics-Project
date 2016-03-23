/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>

using namespace PlayerCc;
using namespace std;

static double avoidDistance = 0.4;

void AvoidObstacles(SonarProxy &sp, Position2dProxy &pp)
{
	//will avoid obstacles closer than 40cm
	avoidDistance = 0.4;

	//will turn away at 60 degrees/sec
	int avoidTurnSpeed = 0.5;

	//left corner is sonar no. 1
	//right corner is sonar no. 3
	if((sp[1] < avoidDistance) || (sp[0] < avoidDistance))
	{
		pp.SetSpeed(0, avoidTurnSpeed);
	}
	else if((sp[3] < avoidDistance) || (sp[4] < avoidDistance))
	{
		pp.SetSpeed(0, (-1)*avoidTurnSpeed);
	}
	else if(sp[2] < avoidDistance)
	{
		pp.SetSpeed(-0.2, avoidTurnSpeed);
	}
}

int CheckAllScanners(SonarProxy &sp)
{
	bool IsClose = 0;
	double Distance = 0.4;
	int ScannerCount = sp.GetCount() -3;

		for (int i=0; i<ScannerCount; i++)
		{
			if(sp[i] < Distance)
			{
				IsClose = 1;
				break;
			}
		}

	return IsClose;
}

int main()
{
	PlayerClient pc;
	SonarProxy sp(&pc);
	Position2dProxy pp(&pc);

	while (true) {
		pc.Read();

		while(CheckAllScanners(sp))
		{
			AvoidObstacles(sp, pp);
		}


		pp.SetSpeed(0.2, 0);

	}
	return 0;
}


