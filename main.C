#include "tv.hpp"

using namespace std;

int main (int argc, char* argv[])
{
	const string filename = argv[1];
  //manage tick files
	//for (int i = 1; i < 6; i++ ) {make_tick_volume_file(filename, i);} //all
	for (int i = 3; i < 6; i++ ) {make_tick_volume_file(filename, i);} //hour, day, month
  //high, low, mode
  //for (int i = 1; i < 6; i++ ) {make_volume_mode_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_volume_mode_file(filename, i);}
  //weighted volume
  //for (int i = 1; i < 6; i++ ) {make_weight_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_weight_file(filename, i);}
  //choose columns
  //for (int i = 1; i < 6; i++ ) {make_mode_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_mode_file(filename, i);}
  //manage scale files
  //for (int i = 1; i < 6; i++ ) {make_scale_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_scale_file(filename, i);}
  //scale, scalebis vector files
  //for (int i = 1; i < 6; i++ ) {make_scalebis_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_scalebis_file(filename, i);}
  //remove tmp files
  //for (int i = 1; i < 6; i++ ) {make_rm_file(filename, i);}
  for (int i = 3; i < 6; i++ ) {make_rm_file(filename, i);}
  return 0;
}
