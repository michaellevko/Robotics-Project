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

	double scans[5];
	//pp.SetSpeed(0.5, 0);
	pp.SetOdometry(-6.009, 2.481, dtor(-194.220));

	for (int i=0; i<5; i++)
	{
		scans[i] = 100;
	}

	while (true) {
		pc.Read();

		std::cout << "array: [";
		for(int i=0; i<5;  i++)
		{
			std::cout << scans[i] << ', ' ;
		}

		std::cout << " ] " << endl;


		for (int i=0; i<5; i++)
		{
			scans[i] = sp[i];
		}
			if (scans[1] < 0.3 || scans[3] < 0.3)
			{
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
				else if (scans[3] < 0.3)
				{
					std::cout << " went for going  right" << endl;
					pp.SetSpeed(0, -0.6);
				}
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
	}

}
