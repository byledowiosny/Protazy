#include <stdio.h>
#include <stdlib.h>

#include "tv.hpp"

using namespace std;

int make_mode_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile1;
  string outFile2;
  string inFile;
  string command1, command2;
  switch(id) {
  case 1:
    outFile1 = dateFile+"-SMHL.dat";
    outFile2 = dateFile+"-sM.dat";
  	inFile = dateFile+"-SVHLMM.dat";
    break;
  case 2:
    outFile1 = dateFile+"-MMHL.dat";
    outFile2 = dateFile+"-mM.dat";
  	inFile = dateFile+"-MVHLMM.dat";
    break;
  case 3:
    outFile1 = dateFile+"-HMHL.dat";
    outFile2 = dateFile+"-hM.dat";
  	inFile = dateFile+"-HVHLMM.dat";
    break;
  case 4:
    outFile1 = dateFile+"-DMHL.dat";
    outFile2 = dateFile+"-dM.dat";
  	inFile = dateFile+"-DVHLMM.dat";
    break;
  case 5:
    outFile1 = dateFile+"-TMHL.dat";
    outFile2 = dateFile+"-tM.dat";
  	inFile = dateFile+"-TVHLMM.dat";
    break;
      }

  command1 = "choose -c1,5,3,4 -o "+outFile1+" "+inFile;
  const char * command1_char = command1.c_str();  //convert string to char*
  system(command1_char);

  command2 = "choose -c5 -o "+outFile2+" "+inFile;
  const char * command2_char = command2.c_str();  //convert string to char*
  system(command2_char);

  return 0;
}
