/* 
 * File:   ciprange.cpp
 * Author: froger
 * 
 * Created on 29 sierpień 2009, 20:47
 */

#include "ciprange.h"
#include "clocation.h"

int CIPRange::SIZE = 0;

CIPRange::CIPRange()
{
  CIPRange::SIZE++;
}

CIPRange::CIPRange(const CIPRange& orig)
{
	this->
}

CIPRange::~CIPRange()
{
  this->SIZE--;
}

void CIPRange::setID(int ID)
{
  this->ID = ID;
  return;
}

void CIPRange::setIPEnd(long long int IPEndNum)
{
  this->IPEnd = IPEndNum;
  return;
}

void CIPRange::setIPStart(long long int IPStartNum)
{
  this->IPStart = IPStartNum;
  return;
}

int CIPRange::check(uint32_t IP)
{
  if(IP >= IPStart && IP < IPEnd)
  {
	  Location loc;
	  loc.CityID = CityID;
	  loc.CountryID = CountryID;
	  loc.RegionID = RegionID;
  }
  return -1;
}

int CIPRange::size()
{
  return SIZE;
}

CIPRange& CIPRange::operator =(const CIPRange &x)
{
  this->IPStart = x.IPStart;
  this->IPEnd = x.IPEnd;
  this->ID = x.ID;
  return *this;
}
