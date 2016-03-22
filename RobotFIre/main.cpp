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

int main() {
	PlayerClient pc("localhost", 6665);
	Position2dProxy pp(&pc);
	SonarProxy sp(&pc);

	//pp.SetSpeed(0.5, 0);
	pp.SetOdometry(-6.009, 2.481, dtor(-194.220));

	while (true) {
		pc.Read();
		std::cout << "X: " << pp.GetXPos() << ", Y: " << pp.GetYPos()
				<< ", Yaw: " << pp.GetYaw();

		std::cout << sp << std::endl;

		if (sp[2] < 0.5)
			pp.SetSpeed(0, 0.5);
		else
			pp.SetSpeed(0.5, 0);
	}

}
