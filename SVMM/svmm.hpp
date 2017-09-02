#include <iterator>
#include <utility>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>


using namespace std;

//helper struct
template<typename T> struct referring
{
  referring(T const& t): value(t) {}
  template<typename Iter>
  bool operator()(std::pair<Iter, int> const& p) const
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
  typedef typename std::iterator_traits<FwdIterator>::value_type value_type;
  typedef std::list<std::pair<FwdIterator, int> > count_type;
  typedef typename count_type::iterator count_iterator;
  count_type counts;  //count elements
  while (first != last)  //(first, last) is a valid range
    {
      count_iterator element = std::find_if(counts.begin(), counts.end(),
                                            referring<value_type>(*first));
      if (element == counts.end()) counts.push_back(std::make_pair(first, 1));
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