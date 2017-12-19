#include "bind.hpp"

using namespace std;

int main (int argc, char* argv[])
{
	const string filename = argv[1];
	for (int i = 1; i < 6; i++ ) {make_mode_file(filename, i);}
  for (int i = 1; i < 6; i++ ) {make_bind_file(filename, i);}
  return 0;
}
