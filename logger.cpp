
#include <iostream>
#include <fstream>
#include <time.h>

#include "logger.h"

std::streambuf *psbuf, *backup;
std::ofstream filestr;



void initLogger(){
	
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );

	time ( &rawtime );
    timeinfo = localtime ( &rawtime );

	filestr.open ("cout_log.txt", std::fstream::in | std::fstream::ate);

	backup = std::cout.rdbuf();     // back up cout's streambuf

	psbuf = filestr.rdbuf();   // get file's streambuf
	std::cout.rdbuf(psbuf);         // assign streambuf to cout

	std::cout << "Logging started: " << asctime(timeinfo)<< std::endl;
  
	
}

void closeLogger(){
	std::cout.rdbuf(backup);        // restore cout's original streambuf

	filestr.close();
}