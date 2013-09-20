/* 
 * File:   main.cpp
 * Author: froger
 *
 * Created on 28 sierpień 2009, 22:40
 */
#include "strtoint.h"


#include "inttostr.h"


#include <fstream>

#include "ciprange.h"


#include "main.h"

pthread_mutex_t ip_array_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t location_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t strtoint_mutex = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

CIPRange *IPRangeArray;
CLocation *LocationArray;

string PORT;

int main(int argc, char** argv)
{

  int Port;
  int MaxClients;
  int IPRangeArraySize;
  int LocationArraySize;
  int error;

  pthread_t t_thread, t_threadguard;
  pthread_attr_t tattr_thread, tattr_threadguard;
  long int sockfd, newsockfd[100000];
  size_t client_length;
  char *buffer;
  sockaddr_in server_address;
  sockaddr client_address;
  string IP = "";
  int IPtmp;


  if(argc == 1) //default port, max clients == 300
  {
    Port = 15001;
    PORT = "15001";
    MaxClients = 300;
  }
  else if(argc == 2) //port will be set by parameter, max clients == 300
  {
    int error;
    PORT.assign(argv[1]);
    Port = strToInt(argv[1], error);
    MaxClients = 300;
  }
  else if(argc == 3) //port will be set by parameter1 , max clients will be set by parameter 2
  {
    Port = strToInt(argv[1], error);
    MaxClients = strToInt(argv[2], error);
  }

  //uzupelnij tabele IPRangeArray
  fstream file;
  file.open("/home/froger/geo-data/Blocks", ios::in);
  string x;
  file >> x;
  int err = 0;

  string dane[5];
  IPRangeArraySize = strToInt(x, err);
  if(err == 0 && IPRangeArraySize > 0)
  {
    IPRangeArray = new CIPRange[IPRangeArraySize];
    for(int i = 0; i < IPRangeArraySize; i++)
    {
      try
      {
        file >> dane[0] >> dane[1] >> dane[2];
      }
      catch(...)
      {
        break;
      }
      IPRangeArray[i].setID(strToInt(dane[0], err));
      IPRangeArray[i].setIPStart(strToInt(dane[1], err));
      IPRangeArray[i].setIPEnd(strToInt(dane[2], err));
    }
  }

  file.close();
  //uzupelnij tabele LocationArray
  file.open("/home/froger/geo-data/Location", ios::in);
  x.clear();
  file >> x;
  err = 0;
  LocationArraySize = strToInt(x, err);
  if(err == 0 && LocationArraySize > 0)
  {
    LocationArray = new CLocation[LocationArraySize];
    for(int i = 0; i < LocationArraySize; i++)
    {
      try
      {
      file >> dane[0] >> dane[1] >> dane[2] >> dane[3] >> dane[4];
      }
      catch(...)
      {
       break;
      }
      LocationArray[i].setID(strToInt(dane[0],err));
      LocationArray[i].setCountry(dane[1]);
      LocationArray[i].setCity(dane[2]);
      LocationArray[i].setLongitude(dane[3]);
      LocationArray[i].setLatitude(dane[4]);
    }
  }
  file.close();

  pthread_setconcurrency(MaxClients + 1);
  pthread_attr_init(&tattr_threadguard);
  pthread_attr_setdetachstate(&tattr_threadguard, PTHREAD_CREATE_DETACHED);

  int cpid1 = (int) pthread_create(&t_threadguard, &tattr_threadguard, threadGuard, NULL);
  if(cpid1 != 0)
  {
    return EXIT_FAILURE;
  }

  //-----------CREATE THREAD AND CONNECTION----------

  buffer = new char[20];
  pthread_attr_init(&tattr_thread);
  pthread_attr_setdetachstate(&tattr_thread, PTHREAD_CREATE_DETACHED);

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //tcpsol=0
  if(sockfd < 0)
  {
    //tehre are critical problems. exit
    return EXIT_FAILURE;
  }
  memset(buffer, 0, 20);

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(Port);

  if(bind(sockfd, (sockaddr *) & server_address, sizeof (server_address)) != 0)
  {
    //error while binding, exit
    close(sockfd);
    return EXIT_FAILURE;
  }
  listen(sockfd, 20);
  cout << "Ready! <PORT:" << Port << ">" << endl;
  int count = 0;
  while(1)
  {
    cout << "1";
    if(count >= 100000)
    {
      count = 0;
    }
    memset(buffer, 0, 20);
    client_length = sizeof (client_address);
    newsockfd[count] = accept(sockfd, (sockaddr *) & client_address, (socklen_t*) & client_length);

    IP = "";
    string tmp;
    IPtmp = (int) client_address.sa_data[2];
    if(IPtmp < 0)
    {
      IPtmp += 256;
    }
    tmp = intToStr(IPtmp);
    IP += tmp;
    IP += ".";
    IPtmp = (int) client_address.sa_data[3];
    if(IPtmp < 0)
    {
      IPtmp += 256;
    }
    tmp = intToStr(IPtmp);
    IP += tmp;
    IP += ".";
    IPtmp = (int) client_address.sa_data[4];
    if(IPtmp < 0)
    {
      IPtmp += 256;
    }
    tmp = intToStr(IPtmp);
    IP += tmp;
    IP += ".";
    IPtmp = (int) client_address.sa_data[5];
    if(IPtmp < 0)
    {
      IPtmp += 256;
    }
    tmp = intToStr(IPtmp);
    IP += tmp;

    if(IP != "127.0.0.1")
    {
      //someone from other localization than localhost
      close(newsockfd[count]);
    }

    if(newsockfd[count] < 0)
    {
      //Error while creating new sock filedescriptor (newsockfd)
    }
    else
    {
      int cpid = (int) pthread_create(&t_thread, &tattr_thread, threadConnect, (void*) newsockfd[count]);
      if(cpid != 0)
      {
        close(newsockfd[count]);
        //Error while creating thread
      }
    }
    count++;
  }


  return (EXIT_SUCCESS);
}
