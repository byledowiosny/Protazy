#include <iostream>
#include <sstream> //this is for ToString function
#include <vector>  //this is for dynamic arrays
#include <cstdlib>
#include <TString.h>
#include <TSystem.h>
#include <TTreeReader.h>
#include <TChain.h>
#include <TInterpreter.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TROOT.h>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>

using namespace std;

TString ToString(int num);
Int_t CreateRootTicksFile(TString file);

int main(int argc, char* argv[])
{
  cout << "Enter the data file name to proceed: ";
  TString datafile;
  cin >> datafile;
  size_t position = datafile.find(".");
  string suffix = datafile.substr (position);  //from "." to the end
  string filetype;
  filetype = datafile.substr (0,4);  //"Ticks"
  if(filetype == "Ticks")
    {
      if(suffix != "root") CreateRootTicksFile(datafile);
      //open the root file and do some useful things
      return 0;
    }
  filetype = datafile.substr (8,12);  //"HMSVT" or "MMSVT"
  if(filetype == "HMSVT") ModesHourly(datafile);
  if(filetype == "MMSVT") ModesMinutely(datafile);
  filetype = datafile.substr (8,11);  //"HCHL" or "MCHL"
  if(filetype == "HCHL") CHLHourly(datafile);
  if(filetype == "MCHL") CHLMinutely(datafile);
  filetype = datafile.substr (8,9);  //"HC", "MC" ...
  if(filetype == "HC") CloseHourly(datafile);
  if(filetype == "HH") HighHourly(datafile);
  if(filetype == "HL") LowHourly(datafile);
  if(filetype == "HM") ModeHourly(datafile);
  if(filetype == "MC") CloseMinutely(datafile);
  if(filetype == "MH") HighMinutely(datafile);
  if(filetype == "ML") LowMinutely(datafile);
  if(filetype == "MM") ModeMinutely(datafile);
  return 0;
}

Int_t CreateRootTicksFile(TString datafile)
{
	const int LINE_LENGTH = 60;
	FILE *fp = fopen(datafile,"r");
  size_t position = datafile.find(".");
  TString inbase = (string::npos == position)? datafile : datafile.substr(0, position);
  TString filename = inbase+".root";
  TFile *hfile = 0;
  hfile = TFile::Open(filename,"RECREATE");
  //The root file is created in the directory where program is running.
  Int_t Year, Month, Day, Hour, Minute, Second, Millisecond;
  Float_t Ask, Bid, AskVolume, BidVolume;
  TString treename = "ticks";
  TTree* tree = new TTree(treename, treename);
  tree->Branch("Year",&Year,"Year/I");
  tree->Branch("Month",&Month,"Month/I");
  tree->Branch("Day",&Day,"Day/I");
  tree->Branch("Hour",&Hour,"Hour/I");
  tree->Branch("Minute",&Minute,"Minute/I");
  tree->Branch("Second",&Second,"Second/I");
  tree->Branch("Millisecond",&Millisecond,"Millisecond/I");
  tree->Branch("Ask",&Ask,"Ask/F");
  tree->Branch("Bid",&Bid,"Bid/F");
  tree->Branch("AskVolume",&AskVolume,"AskVolume/F");
  tree->Branch("BidVolume",&BidVolume,"BidVolume/F");
  int nlines = 0;
	char line[LINE_LENGTH];
  while (fgets(line, LINE_LENGTH, fp) != NULL)
    {
      sscanf(&line[0],"%d-%d-%d %d:%d:%d.%d,%f,%f,%f,%f",
             &Year,&Month,&Day,&Hour,&Minute,&Second,&Millisecond,
             &Ask,&Bid,&AskVolume,&BidVolume);
      if (nlines > 0) {tree -> Fill();}
      nlines++;
    }
  tree -> Write();
  fclose(fp);
  delete hfile;
	return 0;
}

TString ToString(int num)
{
  ostringstream start;
  start << num;
  TString start1 = start.str();
  return start1;
}
