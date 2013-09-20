#include "frgr_binary_search.h"

int FRGRBinarySearch(CIPRange *IPRangeArray, int left, int right, long long int value)
{
  int index;

  if(left > right)
  {
    return -1;
  }
  index = (left + right) / 2;
  if(IPRangeArray[index].check(value) >= 0)
  {
    return index;
  }
  else if(value < IPRangeArray[index].IPStart)
  {
    return FRGRBinarySearch(IPRangeArray, left, index - 1, value);
  }
  else
  {
    return FRGRBinarySearch(IPRangeArray, index + 1, right, value);
  }
}

int FRGRBinarySearch(CLocation *LocationArray, int left, int right, long long int value)
{
  int index;

  if(left > right)
  {
    return -1;
  }
  index = (left + right) / 2;
  if(LocationArray[index].check(value) == true)
  {
    return index;
  }
  else if(value < LocationArray[index].ID)
  {
    return FRGRBinarySearch(LocationArray, left, index - 1, value);
  }
  else
  {
    return FRGRBinarySearch(LocationArray, index + 1, right, value);
  }
}

