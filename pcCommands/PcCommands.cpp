#include <iostream>
#include "SerialClass.h"

int main()
{
    
    	Serial* SP = new Serial("\\\\.\\COM6");    // adjust as needed
	
	/* it tells us if the robot is connected to the PC */
	if (SP->IsConnected())
		std::cout << "Arduino connected" << std::endl;
	
	/* we define sendbuffer matrice */
	char sendbuffer[] = { 1, 2, 3, 4 };

	/* sends data to the robot */
	if (SP->IsConnected()){
        	SP->WriteData(sendbuffer,4);
        	std::cout << "Data sent!" << std::endl;
	}

    return 0;
}
