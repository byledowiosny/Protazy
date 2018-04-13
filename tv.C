#include <TTimeStamp.h>

#include "tv.hpp"

using namespace std;

int make_tick_volume_file (const string filename, const int id)  //tv
{
  const char * inFile = filename.c_str();  //convert string to char*
  FILE *dtFile = fopen(inFile,"r");  //needs char*, not string

  string dateFile = filename.substr (0,7);
  string outFile;
  switch(id) {
  case 1: outFile = dateFile+"-STV.dat";  //epoch (sec)
    break;
  case 2: outFile = dateFile+"-MTV.dat";  //epoch (min)
    break;
  case 3: outFile = dateFile+"-HTV.dat";  //epoch (hour)
    break;
  case 4: outFile = dateFile+"-DTV.dat";  //epoch (day)
    break;
  case 5: outFile = dateFile+"-TTV.dat";  //epoch (month)
    break;
  }
  fstream timeFile;
  timeFile.open(outFile, ios::out | ios::app);  //line by line

  const int LINE_LENGTH = 60;  //with some free places to live
  char line[LINE_LENGTH];
  int line_nb = 0;

  UInt_t year;
  UInt_t month;
  UInt_t day;
  UInt_t hour;
  UInt_t min;
  UInt_t sec;
  UInt_t nsec = 0;
  Bool_t isUTC = kTRUE;
  Int_t  secOffset = 0;
  float  Ask, Bid, AskVolume, BidVolume;
  Int_t  epoch;
  while (fgets(line, LINE_LENGTH, dtFile) != NULL)
    {
      if (line_nb > 0) //no headers
        {
          sscanf(&line[0],"%d-%d-%d %d:%d:%d.%d,%f,%f,%f,%f", &year,&month,&day,&hour,&min,&sec,&nsec,
                 &Ask,&Bid,&AskVolume,&BidVolume);
          switch(id) {
          case 1:
            epoch = TTimeStamp(year, month, day, hour, min, sec, nsec = 0, isUTC, secOffset);
            break;
          case 2:
            epoch = TTimeStamp(year, month, day, hour, min, sec = 0, nsec = 0, isUTC, secOffset);
            break;
          case 3:
            epoch = TTimeStamp(year, month, day, hour, min = 0, sec = 0, nsec = 0,
                               isUTC, secOffset);
            break;
          case 4:
            epoch = TTimeStamp(year, month, day, hour = 0, min = 0, sec = 0, nsec = 0,
                               isUTC, secOffset);
            break;
          case 5:
            epoch = TTimeStamp(year, month, day = 0, hour = 0, min = 0, sec = 0, nsec = 0,
                               isUTC, secOffset);
            break;
          }
          timeFile << fixed;
          timeFile << epoch;
          timeFile << " ";
          timeFile << setprecision(4);
          timeFile << Ask;
          timeFile << " ";
          timeFile << setprecision(2);
          timeFile << AskVolume;
          timeFile << endl;
          timeFile << epoch;
          timeFile << " ";
          timeFile << setprecision(4);
          timeFile << Bid;
          timeFile << " ";
          timeFile << setprecision(2);
          timeFile << BidVolume;
          timeFile << endl;
        }
      line_nb++;
    }
  fclose(dtFile);
  timeFile.close();
  return 0;
}
