#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <scythestat/matrix.h>
#include <scythestat/la.h>

#include "bind.hpp"

using namespace std;
using namespace scythe;

int make_bind_file (const string filename, const int id)
{
	string dateFile = filename.substr (0,7);
  string outFile;
  string inFile1;
  string inFile2;
  switch(id) {
  case 1:
    outFile = dateFile+"-SWM.dat";
  	inFile1 = dateFile+"-SVM.dat";
    inFile2 = dateFile+"-SW.dat";
    break;
  case 2:
    outFile = dateFile+"-MWM.dat";
  	inFile1 = dateFile+"-MVM.dat";
    inFile2 = dateFile+"-MW.dat";
    break;
  case 3:
    outFile = dateFile+"-HWM.dat";
  	inFile1 = dateFile+"-HVM.dat";
    inFile2 = dateFile+"-HW.dat";
    break;
  case 4:
    outFile = dateFile+"-DWM.dat";
  	inFile1 = dateFile+"-DVM.dat";
    inFile2 = dateFile+"-DW.dat";
    break;
  case 5:
    outFile = dateFile+"-TWM.dat";
  	inFile1 = dateFile+"-TVM.dat";
    inFile2 = dateFile+"-TW.dat";
    break;
      }

  Matrix<> M(inFile1);
  Matrix<> Weight(inFile2);
  Matrix<> Epoch = M(_, 0);
  Matrix<> Mode  = M(_, 2);

  Matrix<> EW(M.rows(),2);
  Matrix<> EWM(M.rows(),3);
  EW  = cbind(Epoch,Weight);
  EWM = cbind(EW,Mode);

  EWM.save(outFile);

  return 0;
}
