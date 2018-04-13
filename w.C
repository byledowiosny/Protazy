#include <stdio.h>
#include <stdlib.h>

#include <scythestat/matrix.h>

#include "tv.hpp"

using namespace std;
using namespace scythe;

int make_weight_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile;
  string inFile;
  string command;
  switch(id) {
  case 1:
    outFile = dateFile+"-WeightSecond.dat";
  	inFile = dateFile+"-SVHLMM.dat";
    break;
  case 2:
    outFile = dateFile+"-WeightMinute.dat";
  	inFile = dateFile+"-MVHLMM.dat";
    break;
  case 3:
    outFile = dateFile+"-WeightHour.dat";
  	inFile = dateFile+"-HVHLMM.dat";
    break;
  case 4:
    outFile = dateFile+"-WeightDay.dat";
  	inFile = dateFile+"-DVHLMM.dat";
    break;
  case 5:
    outFile = dateFile+"-WeightMonth.dat";
  	Matrix<> W(1, 1);
    W = 1.000000e+00;
    W.save(outFile);
    break;
      }
  if(id != 5) {
    command = "rescale -c2 -o "+outFile+" "+inFile;
    const char * command_char = command.c_str();  //convert string to char*
    system(command_char);
  }
  return 0;
}
