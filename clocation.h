/* 
 * File:   clocation.h
 * Author: froger
 *
 * Created on 31 sierpień 2009, 21:15
 */

#ifndef _CLOCATION_H
#define	_CLOCATION_H

#include <string>
using namespace std;


class CLocation
{
public:
  CLocation();
  CLocation(const CLocation& orig);
  virtual ~CLocation();

  void setID(int ID);
  void setCountry(string country);
  void setCity(string city);
  void setLatitude(string latitude);
  void setLongitude(string longitude);

  bool get(int id, string& Country, string& City, string &Latitude, string &Longitude);
  bool getAllInString(int id, string &All);
  bool check(int id);

  int size();
  CLocation& operator =(const CLocation &x);

  int ID;
private:
  string country;
  string city;
  string latitude;
  string longitude;
  static int SIZE;
};

#endif	/* _CLOCATION_H */

