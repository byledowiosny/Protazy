#include "hvmm.hpp"

int readFile (const string filename)
{
  const int LINE_LENGTH = 60;  //with some free places to live
	const char * inFile = filename.c_str();  //convert string to char*
  FILE *stvFile = fopen(inFile,"r");  //needs char*, not string
  int Hours;
  float Tick, Volume;
  float TVolume;
  int line_nb = 0;
  char line[LINE_LENGTH];
  int first = 0;
  int pass = 0;
  vector <float> dynValues(0); //dynamic array
  string fileDate = filename.substr (0,7);
  string outFile = fileDate+"-HVMM.dat";
  fstream newFile;
  newFile.open(outFile, ios::out | ios::app);  //line by line
  while (fgets(line, LINE_LENGTH, stvFile) != NULL)  //stdin with "<" is possible too
    {
      sscanf(&line[0],"%d,%f,%f",&Hours,&Tick,&Volume);  //from c: simple and effective
      if (line_nb == 0)
        {
          first = pass = Hours;
        }
      if (Hours > pass)
        {
          //===============
          //To do: implement a buffer to facilitate adding and deleting of columns,
          //and add rows number to output filename.
        	newFile << fixed;
          newFile << pass - first;
          newFile << " ";
          newFile << setprecision(2);
          newFile << TVolume; //AskVolume and BidVolume
          newFile << " ";
          newFile << setprecision(4);
          float* values = dynValues.data();
          mode(values, values + sizeof(values)/sizeof(float),
               std::ostream_iterator<float>(newFile, " "));
          newFile << endl;
          //===============
          pass = Hours;
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
  newFile << pass - first;
  newFile << " ";
  newFile << setprecision(2);
  newFile << TVolume; //AskVolume and BidVolume
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

int main (int argc, char* argv[])
{
  const string filename = argv[1];
  readFile(filename);
  return 0;
}
