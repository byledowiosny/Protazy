#include "tv.hpp"

using namespace std;

int main (int argc, char* argv[])
{
	const string filename = argv[1];
	for (int i = 1; i < 6; i++ ) {make_tick_volume_file(filename, i);}
  for (int i = 1; i < 6; i++ ) {make_volume_mode_file(filename, i);}
  for (int i = 1; i < 6; i++ ) {make_weight_file(filename, i);}
  for (int i = 1; i < 6; i++ ) {make_mode_file(filename, i);}
  return 0;
}
