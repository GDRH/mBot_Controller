#include "Serial.h"

Serial::Serial(){
    filestream = NULL;
}

Serial::~Serial(){
    fclose(filestream);
}

bool Serial::init( std::string filePath ){
	filestream = fopen( filePath.c_str(), "w" );

	if ( filestream ){
		puts("Serial opened!\n");
		return true;
	}
	//else...
    puts("Error : failed to initialize serial!");
    return false;
}

bool Serial::sendBytes ( char * buffer, unsigned int size ){
    if ( !filestream )
        return false;

    for ( unsigned int i = 0; i < size; i++ ){
        fputc( buffer[i], filestream );
    }

	fflush( filestream );
	return true;
}
