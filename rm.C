#include <stdio.h>
#include <stdlib.h>

#include "tv.hpp"

using namespace std;

int make_rm_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string File1, File2, File3;
  string command;
  switch(id) {
  case 1:
  	File1 = dateFile+"-STV.dat";
  	File2 = dateFile+"-SVHLMM.dat";
  	File3 = dateFile+"-ScaleSecond.tmp";
    break;
  case 2:
  	File1 = dateFile+"-MTV.dat";
  	File2 = dateFile+"-MVHLMM.dat";
  	File3 = dateFile+"-ScaleMinute.tmp";
    break;
  case 3:
  	File1 = dateFile+"-HTV.dat";
  	File2 = dateFile+"-HVHLMM.dat";
  	File3 = dateFile+"-ScaleHour.tmp";
    break;
  case 4:
  	File1 = dateFile+"-DTV.dat";
  	File2 = dateFile+"-DVHLMM.dat";
  	File3 = dateFile+"-ScaleDay.tmp";
    break;
  case 5:
  	File1 = dateFile+"-TTV.dat";
  	File2 = dateFile+"-TVHLMM.dat";
  	File3 = dateFile+"-ScaleMonth.tmp";
    break;
      }
  command = "rm "+File1+" "+File2+" "+File3;
  const char * command_char = command.c_str();  //convert string to char*
  system(command_char);
  return 0;
}
