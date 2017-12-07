#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "tv.hpp"

using namespace std;

int make_volume_mode_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile;
  string inFile;
  switch(id) {
  case 1:
    outFile = dateFile+"-SVMM.dat";
  	inFile = dateFile+"-STV.dat";
    break;
  case 2:
    outFile = dateFile+"-MVMM.dat";
  	inFile = dateFile+"-MTV.dat";
    break;
  case 3:
    outFile = dateFile+"-HVMM.dat";
  	inFile = dateFile+"-HTV.dat";
    break;
  case 4:
    outFile = dateFile+"-DVMM.dat";
  	inFile = dateFile+"-DTV.dat";
    break;
  case 5:
    outFile = dateFile+"-TVMM.dat";
  	inFile = dateFile+"-TTV.dat";
    break;
      }
  const char * file = inFile.c_str();  //convert string to char*
  FILE *stvFile = fopen(file,"r");  //needs char*, not string

  fstream newFile;
  newFile.open(outFile, ios::out | ios::app);  //line by line

  float Tick, Volume, TVolume;
  int line_nb = 0;
  int first, pass, Epoch;
  vector <float> dynValues(0); //dynamic array

  const int LINE_LENGTH = 60;  //with some free places to live
  char line[LINE_LENGTH];

  while (fgets(line, LINE_LENGTH, stvFile) != NULL)  //stdin with "<" is possible too
    {
      sscanf(&line[0],"%d,%f,%f",&Epoch,&Tick,&Volume);  //from c: simple and effective
      if (line_nb == 0)
        {
          first = pass = Epoch;
        }
      if (Epoch > pass)
        {
          //===============
        	newFile << fixed;
          //time (epoch) absolute
          newFile << pass;
          //or time (epoch) relative to first in month
          //newFile << pass - first;
          newFile << " ";
          newFile << setprecision(2);
          newFile << TVolume;
          newFile << " ";
          newFile << setprecision(4);
          float* values = dynValues.data();
          mode(values, values + sizeof(values)/sizeof(float),
               std::ostream_iterator<float>(newFile, " "));
          newFile << endl;
          //===============
          pass = Epoch;
          TVolume = 0;
          dynValues.clear();
        }
      dynValues.push_back(Tick);
      TVolume += Volume;
      line_nb++;
    }
  //============================
  //This is for the last pass.
  newFile << fixed;
  newFile << pass;
  //newFile << pass - first;
  newFile << " ";
  newFile << setprecision(2);
  newFile << TVolume;
  newFile << " ";
  newFile << setprecision(4);
  float* values = dynValues.data();
  mode(values, values + sizeof(values)/sizeof(float),
       std::ostream_iterator<float>(newFile, " "));
  newFile << endl;
  //============================
  //close the files
  fclose(stvFile);
  newFile.close();
  return 0;
}
