#include <stdio.h>
#include <stdlib.h>

#include "tv.hpp"

using namespace std;

int make_mode_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile1, outFile3, outFile4, outFile5; //outFile2, outFile6;
  string inFile;
  string command1, command3, command4, command5; //command2, command6;
  switch(id) {
  case 1:
    outFile1 = dateFile+"-EpochSecond.dat";
    //outFile2 = dateFile+"-VolumeSecond.dat";
    outFile3 = dateFile+"-HighSecond.dat";
    outFile4 = dateFile+"-LowSecond.dat";
    outFile5 = dateFile+"-ModeSecond.dat";
    //outFile6 = dateFile+"-ModebisSecond.dat";
  	inFile = dateFile+"-SVHLMM.dat";
    break;
  case 2:
    outFile1 = dateFile+"-EpochMinute.dat";
    //outFile2 = dateFile+"-VolumeMinute.dat";
    outFile3 = dateFile+"-HighMinute.dat";
    outFile4 = dateFile+"-LowMinute.dat";
    outFile5 = dateFile+"-ModeMinute.dat";
    //outFile6 = dateFile+"-ModebisMinute.dat";
  	inFile = dateFile+"-MVHLMM.dat";
    break;
  case 3:
    outFile1 = dateFile+"-EpochHour.dat";
    //outFile2 = dateFile+"-VolumeHour.dat";
    outFile3 = dateFile+"-HighHour.dat";
    outFile4 = dateFile+"-LowHour.dat";
    outFile5 = dateFile+"-ModeHour.dat";
    //outFile6 = dateFile+"-ModebisHour.dat";
  	inFile = dateFile+"-HVHLMM.dat";
    break;
  case 4:
    outFile1 = dateFile+"-EpochDay.dat";
    //outFile2 = dateFile+"-VolumeDay.dat";
    outFile3 = dateFile+"-HighDay.dat";
    outFile4 = dateFile+"-LowDay.dat";
    outFile5 = dateFile+"-ModeDay.dat";
    //outFile6 = dateFile+"-ModebisDay.dat";
  	inFile = dateFile+"-DVHLMM.dat";
    break;
  case 5:
    outFile1 = dateFile+"-EpochMonth.dat";
    //outFile2 = dateFile+"-VolumeMonth.dat";
    outFile3 = dateFile+"-HighMonth.dat";
    outFile4 = dateFile+"-LowMonth.dat";
    outFile5 = dateFile+"-ModeMonth.dat";
    //outFile6 = dateFile+"-ModebisMonth.dat";
  	inFile = dateFile+"-TVHLMM.dat";
    break;
      }

  command1 = "choose -c1 -o "+outFile1+" "+inFile;
  const char * command1_char = command1.c_str();  //convert string to char*
  system(command1_char);

  //command2 = "choose -c2 -o "+outFile2+" "+inFile;
  //const char * command2_char = command2.c_str();  //convert string to char*
  //system(command2_char);

  command3 = "choose -c3 -o "+outFile3+" "+inFile;
  const char * command3_char = command3.c_str();  //convert string to char*
  system(command3_char);

  command4 = "choose -c4 -o "+outFile4+" "+inFile;
  const char * command4_char = command4.c_str();  //convert string to char*
  system(command4_char);

  command5 = "choose -c5 -o "+outFile5+" "+inFile;
  const char * command5_char = command5.c_str();  //convert string to char*
  system(command5_char);

  //command6 = "choose -c6 -o "+outFile6+" "+inFile;
  //const char * command6_char = command6.c_str();  //convert string to char*
  //system(command6_char);

  return 0;
}
