/* 
 * File:   clocation.cpp
 * Author: froger
 * 
 * Created on 31 sierpień 2009, 21:15
 */

#include "clocation.h"

int CLocation::SIZE = 0;

CLocation::CLocation()
{
  SIZE++;
}

CLocation::CLocation(const CLocation& orig)
{
  this->ID = orig.ID;
  this->city = orig.city;
  this->country = orig.country;
  this->latitude = orig.latitude;
  this->longitude = orig.longitude;
}

CLocation::~CLocation()
{
  SIZE --;
}

void CLocation::setID(int ID)
{
  this->ID = ID;
  return;
}

void CLocation::setCity(string city)
{
  this->city = city;
  for(int i=0;i<this->city.length();i++)
  {
    if(this->city[i] == '_')
    {
      this->city[i] = ' ';
    }
  }
  return;
}

void CLocation::setLatitude(string latitude)
{
  this->latitude = latitude;
  return;
}

void CLocation::setLongitude(string longitude)
{
  this->longitude = longitude;
  return;
}

void CLocation::setCountry(string country)
{
  this->country = country;
  for(int i=0;i<this->country.length();i++)
  {
    if(this->country[i] == '_')
    {
      this->country[i] = ' ';
    }
  }
  return;
}

bool CLocation::check(int id)
{
  if(ID == id)
  {
    return true;
  }
  return false;
}

bool CLocation::getAllInString(int id, string& All)
{
  if(ID == id)
  {
    All = "city="+this->city+"&coun="+this->country+"&long="+this->longitude+"&lati="+this->latitude;
    return true;
  }
  return false;
}

bool CLocation::get(int id, string& Country, string& City, string& Latitude, string& Longitude)
{
  if(ID == id)
  {
    Country = this->country;
    City = this->city;
    Latitude = this->latitude;
    Longitude = this->longitude;
    return true;
  }
  return false;
}

int CLocation::size()
{
  return SIZE;
}

CLocation& CLocation::operator =(const CLocation &x)
{
  this->ID = x.ID;
  this->country = x.country;
  this->city = x.city;
  this->latitude = x.latitude;
  this->longitude = x.longitude;
  return *this;
}
