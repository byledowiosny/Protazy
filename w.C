#include <stdio.h>
#include <stdlib.h>

#include "tv.hpp"

using namespace std;

int make_weight_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile;
  string inFile;
  string command;
  switch(id) {
  case 1:
    outFile = dateFile+"-SW.dat";
  	inFile = dateFile+"-SVMM.dat";
    break;
  case 2:
    outFile = dateFile+"-MW.dat";
  	inFile = dateFile+"-MVMM.dat";
    break;
  case 3:
    outFile = dateFile+"-HW.dat";
  	inFile = dateFile+"-HVMM.dat";
    break;
  case 4:
    outFile = dateFile+"-DW.dat";
  	inFile = dateFile+"-DVMM.dat";
    break;
  case 5:
    outFile = dateFile+"-TW.dat";
  	inFile = dateFile+"-TVMM.dat";
    break;
      }

  command = "rescale -c2 -o "+outFile+" "+inFile;

  const char * command_char = command.c_str();  //convert string to char*

  system(command_char);

  return 0;
}
