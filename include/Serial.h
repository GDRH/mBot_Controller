#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <stdio.h>

class Serial
{
    public:
        Serial();
        virtual ~Serial();

        bool init( std::string filePath );
        bool sendBytes ( char * buffer, unsigned int size );

    protected:

    private:
        FILE * filestream;
};

#endif // SERIAL_H
