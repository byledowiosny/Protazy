#include <stdio.h>
#include <stdlib.h>

#include "tv.hpp"

using namespace std;

int make_mode_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile;
  string inFile;
  string command;
  switch(id) {
  case 1:
    outFile = dateFile+"-SM.dat";
  	inFile = dateFile+"-SVMM.dat";
    break;
  case 2:
    outFile = dateFile+"-MM.dat";
  	inFile = dateFile+"-MVMM.dat";
    break;
  case 3:
    outFile = dateFile+"-HM.dat";
  	inFile = dateFile+"-HVMM.dat";
    break;
  case 4:
    outFile = dateFile+"-DM.dat";
  	inFile = dateFile+"-DVMM.dat";
    break;
  case 5:
    outFile = dateFile+"-TM.dat";
  	inFile = dateFile+"-TVMM.dat";
    break;
      }

  command = "rescale -c3 -o "+outFile+" "+inFile;

  const char * command_char = command.c_str();  //convert string to char*

  system(command_char);

  return 0;
}
