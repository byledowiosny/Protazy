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

int make_tick_volume_file (const string filename, const int id);

int make_volume_mode_file (const string filename, const int id);

//helper struct
template<typename T> struct referring
{
  referring(T const& t): value(t) {}
  template<typename Iter>
  bool operator()(pair<Iter, int> const& p) const
  {
    return *p.first == value;
  }
  T const& value;
};

//FwdIterator is a ForwardIterator, its value_type is EqualityComparable,
//convertible to the value_type of OutIterator, an output iterator.
template<typename FwdIterator, typename OutIterator>
void mode(FwdIterator first, FwdIterator last, OutIterator result)
{
  typedef typename iterator_traits<FwdIterator>::value_type value_type;
  typedef list<pair<FwdIterator, int> > count_type;
  typedef typename count_type::iterator count_iterator;
  count_type counts;  //count elements
  while (first != last)  //(first, last) is a valid range
    {
      count_iterator element = find_if(counts.begin(), counts.end(),
                                            referring<value_type>(*first));
      if (element == counts.end()) counts.push_back(make_pair(first, 1));
      else ++element->second;
      ++first;
    }
  int max = 0;  //find maximum
  for (count_iterator i = counts.begin(); i != counts.end(); ++i)
    if (i->second > max) max = i->second;
  //copy corresponding elements to output sequence
  for (count_iterator i = counts.begin(); i != counts.end(); ++i)
    if (i->second == max)
      *result++ = *i->first;  //the mode is wtitten to result
}
