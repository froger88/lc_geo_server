/* 
 * File:   thread_connect.h
 * Author: froger
 *
 * Created on 31 sierpień 2009, 23:57
 */

#ifndef _THREAD_CONNECT_H
#define	_THREAD_CONNECT_H
#define _REENTRANT

#include <pthread.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <mysql/mysql.h>
#include <unistd.h>

#include "main.h"
#include "inttostr.h"
#include "strtoint.h"
#include "ciprange.h"
#include "clocation.h"

void* threadConnect(void *arg);

#endif	/* _THREAD_CONNECT_H */

