#include "tv.hpp"

using namespace std;

int make_tick_volume_file (const string filename, const int id)
{
      string dateFile = filename.substr (0,7);
      string outFile;
      switch(id) {
      case 1: outFile = dateFile+"-STV.dat";
        break;
      case 2: outFile = dateFile+"-MTV.dat";
        break;
      case 3: outFile = dateFile+"-HTV.dat";
        break;
      case 4: outFile = dateFile+"-DTV.dat";
        break;
      case 5: outFile = dateFile+"-TTV.dat";
        break;
      }
      fstream timeFile;
      timeFile.open(outFile, ios::out | ios::app);  //line by line

      const char * inFile = filename.c_str();  //convert string to char*
      FILE *dtFile = fopen(inFile,"r");  //needs char*, not string

      time_t rawtime;
      struct tm * timeinfo;
      time(&rawtime);  //rawtime = time(0); get current timeinfo
      timeinfo = localtime(&rawtime);  //convert to struct
      int Year, Month, Day, Hour, Minute, Second, Millisecond;
      float Ask, Bid, AskVolume, BidVolume;
      int line_nb = 0;
      const int LINE_LENGTH = 60;  //with some free places to live
      char line[LINE_LENGTH];

      while (fgets(line, LINE_LENGTH, dtFile) != NULL)
        {
          if (line_nb > 0)
            {
              sscanf(&line[0],"%d-%d-%d %d:%d:%d.%d,%f,%f,%f,%f",
                     &Year,&Month,&Day,&Hour,&Minute,&Second,&Millisecond,
                     &Ask,&Bid,&AskVolume,&BidVolume);
              //modify the timeinfo to the given date:
              switch(id) {
              case 1: timeinfo->tm_year = Year - 1900;  //1900;
                timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
                timeinfo->tm_mday = Day;          //day of the month - [1,31]
                timeinfo->tm_hour = Hour;         //hours since midnight - [0,23]
                timeinfo->tm_min  = Minute;       //minutes after the hour - [0,59]
                timeinfo->tm_sec  = Second;       //seconds after the minute - [0,59]
                break;
              case 2: timeinfo->tm_year = Year - 1900;  //1900;
                timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
                timeinfo->tm_mday = Day;          //day of the month - [1,31]
                timeinfo->tm_hour = Hour;         //hours since midnight - [0,23]
                timeinfo->tm_min  = Minute;       //minutes after the hour - [0,59]
                break;
              case 3: timeinfo->tm_year = Year - 1900;  //1900;
                timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
                timeinfo->tm_mday = Day;          //day of the month - [1,31]
                timeinfo->tm_hour = Hour;         //hours since midnight - [0,23]
                break;
              case 4: timeinfo->tm_year = Year - 1900;  //1900;
                timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
                timeinfo->tm_mday = Day;          //day of the month - [1,31]
                break;
              case 5: timeinfo->tm_year = Year - 1900;  //1900;
                timeinfo->tm_mon  = Month - 1;    //months since January - [0,11]
                break;
              }
              //all lines are uncommented for second precision
              //Unix time stamp, since 1970-01-01, from timeinfo struct;
              //mktime() for localtime, timegm() for UTC/GMT time.
              int epoch = timegm(timeinfo);
              timeFile << fixed;
              timeFile << epoch;
              timeFile << ",";
              timeFile << setprecision(4);
              timeFile << Ask;
              timeFile << ",";
              timeFile << setprecision(2);
              timeFile << AskVolume;
              timeFile << endl;
              timeFile << epoch;
              timeFile << ",";
              timeFile << setprecision(4);
              timeFile << Bid;
              timeFile << ",";
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
