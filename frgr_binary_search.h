/* 
 * File:   frgr_binary_search.h
 * Author: froger
 *
 * Created on 5 listopad 2009, 18:29
 */

#ifndef _FRGR_BINARY_SEARCH_H
#define	_FRGR_BINARY_SEARCH_H

#include "ciprange.h"
#include "clocation.h"

int FRGRBinarySearch(CIPRange *IPRangeArray, int left, int right, long long int value);
int FRGRBinarySearch(CLocation *LocationArray, int left, int right, long long int value);

#endif	/* _FRGR_BINARY_SEARCH_H */

