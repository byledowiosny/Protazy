#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>
#include <iterator>
#include <utility>
#include <algorithm>
#include <list>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

int readFile (const string filename)
{
  const int LINE_LENGTH = 60;  //with some free places to live
  string fileDate = filename.substr (0,7);
  string outFile = fileDate+"-HTV.dat";
  fstream timeFile;
  timeFile.open(outFile, ios::out | ios::app);  //line by line
  const char * inFile = filename.c_str();  //convert string to char*
  FILE *dtFile = fopen(inFile,"r");  //needs char*, not string
  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);  //rawtime = time(0); //get current timeinfo
  timeinfo = localtime(&rawtime);  //convert to struct
  int Year, Month, Day, Hour, Minute, Second, Millisecond;
  float Ask, Bid, AskVolume, BidVolume;
  int line_nb = 0;
  char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, dtFile) != NULL)  //stdin
    {
      if (line_nb > 0)
        {
          sscanf(&line[0],"%d-%d-%d %d:%d:%d.%d,%f,%f,%f,%f",
                 &Year,&Month,&Day,&Hour,&Minute,&Second,&Millisecond,
                 &Ask,&Bid,&AskVolume,&BidVolume);
          //modify the timeinfo to the given date:
          timeinfo->tm_year = Year - 1900;  //1900;
          timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
          timeinfo->tm_mday = Day;          //day of the month - [1,31]
          timeinfo->tm_hour = Hour;         //hours since midnight - [0,23]
          timeinfo->tm_min  = Minute;       //minutes after the hour - [0,59]
          timeinfo->tm_sec  = Second;       //seconds after the minute - [0,59]
          //Unix time stamp, since 1970-01-01, from timeinfo struct;
          //mktime() for localtime, timegm() for UTC/GMT time.
          //int seconds = timegm(timeinfo);
          //int minutes = timegm(timeinfo)/60;
          int hours   = timegm(timeinfo)/3600;
          //Close = 0;
          //High = 0;
          //Low = 0;
          timeFile << fixed;
          timeFile << hours;
          timeFile << ",";
          timeFile << setprecision(4);
          timeFile << Ask;
          timeFile << ",";
          timeFile << setprecision(2);
          timeFile << AskVolume; //AskVolume and BidVolume
          timeFile << endl;
          timeFile << hours;
          timeFile << ",";
          timeFile << setprecision(4);
          timeFile << Bid;
          timeFile << ",";
          timeFile << setprecision(2);
          timeFile << BidVolume;
          timeFile << endl;
          //outputFile << Close;
          //outputFile << High;
          //outputFile << Low;
        }
      line_nb++;
    }
  fclose(dtFile);
  timeFile.close();
  return 0;
}

int main (int argc, char* argv[])
{
	const string filename = argv[1];
  readFile(filename);
  return 0;
}
