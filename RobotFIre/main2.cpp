/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <cmath>

using namespace PlayerCc;
using namespace std;

// First Milestone - Robotics Class - Michael lefkovits 204206445 and Alon Bar Tzlil 302276126
int main() {
	PlayerClient pc("localhost", 6665);
	Position2dProxy pp(&pc);
	SonarProxy sp(&pc);

	double scans[5];
	double obstaclePositionsX[5];
	double obstaclePositionsY[5];
	double sensorAngles[5] ={-90 * 3.14 / 180, -25 * 3.14 / 180, 0 , 25 *3.14 / 180, 90 * 3.14/ 180} ;

	//pp.SetSpeed(0.5, 0);
	pp.SetOdometry(-6.009, 2.481, dtor(-194.220));

	// initializing sensor readings with no obstacle values
	for (int i=0; i<5; i++)
	{
		scans[i] = 999;
	}

	// initializing obstacle positions with no obstacle values
	for (int i=0; i<5; i++)
	{
		obstaclePositionsX[i] = 999;
		obstaclePositionsY[i] = 999;
	}

	while (true) {
		pc.Read();


		// printing sensor readings
		std::cout << "array: [";
		for(int i=0; i<5;  i++)
		{
			std::cout << scans[i] << "", "" ;
		}

		std::cout << " ] " << endl;

		// updating sensor readings
		for (int i=0; i<5; i++)
		{
			scans[i] = sp[i];
		}

		// calculating obstacle positions
		for (int i =0; i< 5; i++)
		{
			if (scans[i] < 0.8)
			{
				obstaclePositionsX[i] = pp.GetXPos() + scans[i] * (cos(pp.GetYaw() + sensorAngles[i]));
				obstaclePositionsY[i] = pp.GetYPos() + scans[i] * (sin(pp.GetYaw() + sensorAngles[i]));
			}
			else
			{
				// setting no obstacle value
				obstaclePositionsX[i] = 999;
				obstaclePositionsY[i] = 999;

			}
		}
			// Checking for close obstacles on 25 degree sensors
			if (scans[1] < 0.3 || scans[3] < 0.3)
			{
				// checking if both have close obstacle
				if (scans[3] < 0.3 && scans[1] < 0.3)
				{
					if (scans[0] > scans[4])
					{
						std::cout << " went for going no choice right" << endl;
						pp.SetSpeed(0, -3.14);

					}
					else
					{
						std::cout << " went for going no choice left" << endl;
						pp.SetSpeed(0, 3.14);


					}
				}
				// Checking if only left sensor has obstacle
				else if (scans[3] < 0.3)
				{
					std::cout << " went for going  right" << endl;
					pp.SetSpeed(0, -0.6);
				}
				// Checking if only right sensor has obstacle
				else
				{
					std::cout << " went for going left " << endl;
					pp.SetSpeed(0, 0.6);
				}
			}
			else
			{
				std::cout << " went for going straight" << endl;
					pp.SetSpeed(0.2, 0);
			}



			// Printing obstacle positions
			std::cout << " obstacle positions: [";

			for(int i=0; i<5;  i++)
			{
				std::cout << " ( " << obstaclePositionsX[i] << " , " << obstaclePositionsY[i] << " ) " << " , ";
			}

			std::cout << " ] " << endl;


	}

}
