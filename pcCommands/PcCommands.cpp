#include <iostream>
#include "SerialClass.h"

int main()
{
    Serial* SP = new Serial("\\\\.\\COM6");    // adjust as needed
	if (SP->IsConnected())
		std::cout << "Arduino connected" << std::endl;

	char sendbuffer[] = { 1, 2, 3, 4 };

	if (SP->IsConnected()){
        SP->WriteData(sendbuffer,4);
        std::cout << "Data sent!" << std::endl;
	}

    return 0;
}
