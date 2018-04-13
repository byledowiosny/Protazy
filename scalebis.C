#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>

#include "tv.hpp"

using namespace std;

int make_scalebis_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile1, outFile2;
  string inFile;
  switch(id) {
  case 1:
    outFile1 = dateFile+"-ScaleSecond.dat";
    outFile2 = dateFile+"-ScalebisSecond.dat";
    inFile   = dateFile+"-ScaleSecond.tmp";
    break;
  case 2:
    outFile1 = dateFile+"-ScaleMinute.dat";
    outFile2 = dateFile+"-ScalebisMinute.dat";
    inFile   = dateFile+"-ScaleMinute.tmp";
    break;
  case 3:
    outFile1 = dateFile+"-ScaleHour.dat";
    outFile2 = dateFile+"-ScalebisHour.dat";
    inFile   = dateFile+"-ScaleHour.tmp";
    break;
  case 4:
    outFile1 = dateFile+"-ScaleDay.dat";
    outFile2 = dateFile+"-ScalebisDay.dat";
    inFile   = dateFile+"-ScaleDay.tmp";
    break;
  case 5:
    outFile1 = dateFile+"-ScaleMonth.dat";
    outFile2 = dateFile+"-ScalebisMonth.dat";
    inFile   = dateFile+"-ScaleMonth.tmp";
    break;
      }
  float Mode, Modebis;

  const int LINE_LENGTH = 60;  //with some free places to live
  char modeLine[LINE_LENGTH];

  const char * file = inFile.c_str();  //convert string to char*
  FILE *tmpModeFile = fopen(file,"r");  //needs char*, not string

  fstream modeFile;
  modeFile.open(outFile1, ios::out | ios::app);  //line by line
  fstream modebisFile;
  modebisFile.open(outFile2, ios::out | ios::app);  //line by line
  while (fgets(modeLine, LINE_LENGTH, tmpModeFile) != NULL)
    {
      sscanf(&modeLine[0],"%f %f",&Mode,&Modebis);

      modeFile << fixed;
      modeFile << setprecision(4);
      modeFile << Mode;
      modeFile << endl;

      modebisFile << fixed;
      modebisFile << setprecision(4);
      isnan(Modebis) ? modebisFile << Mode : modebisFile << Modebis;
      modebisFile << endl;
    }
  fclose(tmpModeFile);
  modeFile.close();
  modebisFile.close();
  return 0;
}
