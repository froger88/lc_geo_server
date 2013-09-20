
#include "ciprange.h"


#include <pthread.h>
#include <bits/pthreadtypes.h>

#define _REENTRANT

#include "thread_connect.h"

using namespace std;

extern CIPRange* IPRangeArray;
extern CLocation* LocationArray;

extern pthread_mutex_t ip_array_mutex;
extern pthread_mutex_t location_mutex;
extern pthread_mutex_t strtoint_mutex;

void* threadConnect(void *arg)
{
  long int fd = (long int) arg;
  char *Buffer = new char[20];
  int th_str;
  ///USTAWIENIE TL
  timespec TL;
  TL.tv_sec = 1; //seconds
  TL.tv_nsec = 0; //nano seconds

  timespec *timeout = &TL;

  fd_set readmask;
  FD_ZERO(&readmask);
  FD_SET(fd, &readmask);
  ///KONIEC USTAWIANIA TL

  int PING = 0;

  while(1)
  {
    int nfound = 0;
    while(nfound == 0)
    {
      nfound = 0;
      FD_ZERO(&readmask);
      FD_SET(fd, &readmask);
      memset(Buffer, NULL, 20);
      nfound = pselect(sizeof (readmask)*8, &readmask, NULL, &readmask, timeout, NULL);

      if(nfound == 0)//jezeli TL przekroczony
      {

        if(PING == 3)
        {
          break;
          //exit now!
          pthread_exit(0);
        }
        else
        {
          PING++;
        }
      }
      else
      {
        PING = 0;
        break;
      }
    }

    if(PING < 3)
    {
      th_str = read(fd, Buffer, 20);
    }
    if((th_str == 0) || (th_str == -1) || PING >= 3)
    {
      close(fd);
      pthread_exit(0);
    }
    else
    {
      string ANSWER = "geo=false";
      string DATA_IN = Buffer;
      int error = 0;
      long long int IPNum;

      //zmienne do geo-daty
      string All;

      //zablokuj konwersje za pomoca funkcji strToInt      //konwertuj do int
      pthread_mutex_lock(&strtoint_mutex);
      IPNum = strToInt(DATA_IN, error);
      pthread_mutex_unlock(&strtoint_mutex);

      //ustaw IDLocal
      int IDLocal = -1;
      //znajdz odpowiednie ID
      pthread_mutex_lock(&ip_array_mutex); // tablice IPRangeArray na czas przeszukiwania
      int IPRangeSize = IPRangeArray->size();
      pthread_mutex_unlock(&ip_array_mutex);

      pthread_mutex_lock(&ip_array_mutex);
      IDLocal = FRGRBinarySearch(IPRangeArray, 0, IPRangeSize - 1, IPNum); //znajdz index obiektu w tablicy IPRangeArray
      pthread_mutex_unlock(&ip_array_mutex);

      if(IDLocal >= 0)
      {
        IDLocal = IPRangeArray[IDLocal].check(IPNum);
      }

      //sprawdz wartosc IDLocal, jezeli != -1 , przeszukaj LocationArray
      if(IDLocal != -1)
      {
        pthread_mutex_lock(&location_mutex);
        int LocationArraySize = LocationArray->size();
        int ind = FRGRBinarySearch(LocationArray, 0, LocationArraySize - 1, IDLocal);
        if(ind >= 0)
        {
          LocationArray[ind].getAllInString(IDLocal, All);
          ANSWER = "geo=true&" + All;
        }
        pthread_mutex_unlock(&location_mutex);

      }
      //wyslij odpowiedz
      write(fd, ANSWER.c_str(), ANSWER.size());
      close(fd);
      pthread_exit(0);
    }
  }
}