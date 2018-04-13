#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>

#include "tv.hpp"

using namespace std;

int make_scale_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile1, outFile2;
  string inFile1, inFile2;
  switch(id) {
  case 1:
    outFile1 = dateFile+"-ScaleSecond.tmp";
    outFile2 = dateFile+"-ModebisSecond.dat";
  	inFile1 = dateFile+"-SVHLMM.dat";
  	inFile2 = dateFile+"-STV.dat";
    break;
  case 2:
    outFile1 = dateFile+"-ScaleMinute.tmp";
    outFile2 = dateFile+"-ModebisMinute.dat";
  	inFile1 = dateFile+"-MVHLMM.dat";
  	inFile2 = dateFile+"-MTV.dat";
    break;
  case 3:
    outFile1 = dateFile+"-ScaleHour.tmp";
    outFile2 = dateFile+"-ModebisHour.dat";
  	inFile1 = dateFile+"-HVHLMM.dat";
  	inFile2 = dateFile+"-HTV.dat";
    break;
  case 4:
    outFile1 = dateFile+"-ScaleDay.tmp";
    outFile2 = dateFile+"-ModebisDay.dat";
  	inFile1 = dateFile+"-DVHLMM.dat";
  	inFile2 = dateFile+"-DTV.dat";
    break;
  case 5:
    outFile1 = dateFile+"-ScaleMonth.tmp";
    outFile2 = dateFile+"-ModebisMonth.dat";
  	inFile1 = dateFile+"-TVHLMM.dat";
  	inFile2 = dateFile+"-TTV.dat";
    break;
      }
  float Tick, modeVolume, tickVolume, High, Low, Mode, Modebis, modeItem;
  int tickLine_nb = 0, i = 0;
  int pass, modeEpoch, tickEpoch;
  vector <float> modeDynValues(0); //dynamic array
  vector <float> modeEpochDynValues(0); //dynamic array
  vector <float> scaleDynValues(0); //dynamic array

  const int LINE_LENGTH = 60;  //with some free places to live
  char modeLine[LINE_LENGTH];
  char tickLine[LINE_LENGTH];

  const char * file1 = inFile1.c_str();  //convert string to char*
  FILE *modeFile = fopen(file1,"r");  //needs char*, not string
  fstream modebisFile;
  modebisFile.open(outFile2, ios::out | ios::app);  //line by line
  while (fgets(modeLine, LINE_LENGTH, modeFile) != NULL)
    {
      sscanf(&modeLine[0],"%d %f %f %f %f %f",&modeEpoch,&modeVolume,&High,&Low,&Mode,&Modebis);
      modebisFile << fixed;
      modebisFile << setprecision(4);
      isnan(Modebis) ? modebisFile << Mode : modebisFile << Modebis;
      modebisFile << endl;
      modeEpochDynValues.push_back(modeEpoch);
      modeDynValues.push_back(Mode);
    }
  fclose(modeFile);
  modebisFile.close();

  const char * file2 = inFile2.c_str();  //convert string to char*
  FILE *tickFile = fopen(file2,"r");  //needs char*, not string
  fstream newFile;
  newFile.open(outFile1, ios::out | ios::app);  //line by line
  while (fgets(tickLine, LINE_LENGTH, tickFile) != NULL)
    {
      sscanf(&tickLine[0],"%d %f %f",&tickEpoch,&Tick,&tickVolume);
      if (tickLine_nb == 0)
        {
          pass = modeEpochDynValues[0];
          modeItem = modeDynValues[0];
        }
      if(id == 5) {scaleDynValues.push_back(abs(Tick-modeItem));}
      else
        {
          if (tickEpoch > pass)
            {
              newFile << fixed;
              newFile << setprecision(4);
              float* values = scaleDynValues.data();
              mode(values, values + sizeof(values)/sizeof(float),
                   std::ostream_iterator<float>(newFile, " "));
              newFile << endl;
              //==============
              scaleDynValues.clear();
              i++;
              modeItem = modeDynValues[i];
              pass = modeEpochDynValues[i];
            }
          scaleDynValues.push_back(abs(Tick-modeItem));
          tickLine_nb++;
        }
    }
  fclose(tickFile);
  //====================================
  //This is for the month and last pass.
  newFile << fixed;
  newFile << setprecision(4);
  float* values = scaleDynValues.data();
  mode(values, values + sizeof(values)/sizeof(float),
       std::ostream_iterator<float>(newFile, " "));
  newFile << endl;
  //====================================
  newFile.close();
  return 0;
}
