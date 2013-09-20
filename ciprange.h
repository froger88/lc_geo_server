/* 
 * File:   ciprange.h
 * Author: froger
 *
 * Created on 29 sierpień 2009, 20:47
 */

#ifndef _CIPRANGE_H
#define	_CIPRANGE_H

class CIPRange
{
public:
  CIPRange();
  CIPRange(const CIPRange& orig);
  virtual ~CIPRange();

  void setIPStart(long long int IPStartNum);
  void setIPEnd(long long int IPEndNum);
  void setCountryID(int CID);
  void setRegionID(int RID);
  void setCityID(int CID);
  Location check(uint32_t IP);
  int size();
  CIPRange & operator =(const CIPRange &x);

  uint32_t IPStart;
  uint32_t IPEnd;
private:
  int CityID;
  int RegionID;
  int CountryID;
  static int SIZE;
};

#endif	/* _CIPRANGE_H */

