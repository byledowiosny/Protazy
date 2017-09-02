#include <iostream>
#include <sstream> //for ToString function
#include <vector>
#include <TString.h>
#include <TSystem.h>
#include <TTreeReader.h>
#include <TChain.h>
#include <TInterpreter.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
//=====================
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
#include <cstdlib>

#define LINELEN 50

using namespace std;

TString ToString(int num){
  ostringstream start;
  start << num;
  TString start1 = start.str();
  return start1;
}

int main(int argc, char* argv[]){
  Int_t Year, Month, Day, Hour, Minute, Second, Millisecond;
  Float_t Ask, Bid, AskVolume, BidVolume;
  //TString dir = "/home/jerzy/calculus/data";

  //cout << "Enter the asset name: ";
  //TString assetName;
  //cin >> assetName;
  //cout << "Enter the year of data (yyyy): ";
  //TString yearString;
  //cin >> yearString;
  //cout << "Enter the month of data (mm): ";
  //TString monthString;
  //cin >> monthString;
  //cout << "You have entered " << assetName << " " << yearString << " " << monthString << endl;
	//TString dir = "/home/jerzy/calculus/data/"+assetName+"/"+yearString+"/"+monthString+"/";
  //system("cd $dir");

  //dir.Append("/EURUSD/2016/01/");
  //dir.ReplaceAll("/./","/");

  cout << "Enter the data file name to proceed (without suffix): ";
  //TString inbase = "Ticks201601";
  TString inbase;
  cin >> inbase;

  //FILE *fp = fopen(Form("%s"+inbase+".csv",dir.Data()),"r");
  FILE *fp = fopen(inbase+".csv","r");
  TString filename = inbase+".root";

  TFile *hfile = 0;

  hfile = TFile::Open(filename,"RECREATE");

  //the filename is created in the directory where program is running

  int day = 3, hour = 23;

  TString daystr = ToString(day);
  TString hourstr = ToString(hour);
  TString treename = "tree" + daystr + hourstr;
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
	char line[LINELEN];

  while (fgets(line, LINELEN, fp) != NULL) //stdin
    {
      sscanf(&line[0],"%d-%d-%d %d:%d:%d.%d,%f,%f,%f,%f",
             &Year,&Month,&Day,&Hour,&Minute,&Second,&Millisecond,
             &Ask,&Bid,&AskVolume,&BidVolume);
      if (nlines > 0 && Day == day && Hour == hour)
        {
          printf("%s", line);
          tree -> Fill();
        }
      nlines += 1;
    }

  tree -> Write();

  /*TFile file(filename);
  TTreeReader reader(treename, &file);
  TTreeReaderValue<int> year(reader, "Year");    // template type must match datatype
  TTreeReaderValue<int> month(reader, "Month");  // name must match branchname
  TTreeReaderValue<int> day(reader, "Day");
  TTreeReaderValue<int> hour(reader, "Hour");
  TTreeReaderValue<int> minute(reader, "Minute");
  while (reader.Next()){
    //use *mass, *charge, ...
  }*/

  fclose(fp);
  delete hfile;

	return 0;
}
