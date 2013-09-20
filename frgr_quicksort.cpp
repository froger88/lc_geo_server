#include "frgr_quicksort.h"

void FRGRQuickSort(CIPRange * tab, long long int n1, long long int n2)
{
  long long int y = n2;
  long long int x = n1;
  CIPRange tmp;
  if(n2 <= n1)
  {
    return;
  }
  tmp = tab[n1];
  for(x; x < y; x++)
  {
    if(tab[n2].IPStart < tab[x].IPStart)
    {
      for(y; y > x; y--)
      {
        if(tab[n2].IPStart > tab[y].IPStart)
        {
          tmp = tab[x];
          tab[x] = tab[y];
          tab[y] = tmp;
          break;
        }
      }
    }
  }
  tmp = tab[n2];
  tab[n2] = tab[y];
  tab[y] = tmp;
  FRGRQuickSort(tab, n1, y - 1);
  FRGRQuickSort(tab, y + 1, n2);
}

void FRGRQuickSort(CLocation * tab, long long int n1, long long int n2)
{
  long long int y = n2;
  long long int x = n1;
  CLocation tmp;
  if(n2 <= n1)
  {
    return;
  }
  tmp = tab[n1];
  for(x; x < y; x++)
  {
    if(tab[n2].ID < tab[x].ID)
    {
      for(y; y > x; y--)
      {
        if(tab[n2].ID > tab[y].ID)
        {
          tmp = tab[x];
          tab[x] = tab[y];
          tab[y] = tmp;
          break;
        }
      }
    }
  }
  tmp = tab[n2];
  tab[n2] = tab[y];
  tab[y] = tmp;
  FRGRQuickSort(tab, n1, y - 1);
  FRGRQuickSort(tab, y + 1, n2);
}
