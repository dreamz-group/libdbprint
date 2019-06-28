/*
    This file is part of libdbgprint.

    MIT License
    Copyright (c) 2019 dreamz-group

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


#ifndef __DBGPRINT_H__
#define __DBGPRINT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _printlevel 
{
    DBG_PRINT_EVERYTHING,
    DBG_PRINT_VERBOSE,
    DBG_PRINT_INFO,
    DBG_PRINT_WARNING,
    DBG_PRINT_ERROR,
    DBG_PRINT_OFF
} printlevel;

typedef enum _printgrp 
{
  DBG_GRP_GENERAL,  
  DBG_GRP_NETWORK,  
  DBG_GRP_STARTUP,  
  DBG_GRP_DEVELOP,  
  DBG_GRP_DEBUGING, 
  DBG_GRP_DBGPRINT, 
  DBG_GRP_MQTT,
  DBG_GRP_ALL,  // Keep this 2nd last...
  DBG_GRP_ERR    // Keep this last
} printgrp;

typedef struct
{
    printgrp index;  // To make sure its the same as printgrp;
    const char *name;
    const char *spaces;  // Silly way to prettify printouts...
    int level; 
}print_levels;


void dbgmsg(printgrp grp, printlevel lvl, const char* format, ... );
// Can be used to get all data on the same line without level prefix.
void dbgmsg_ex(printgrp grp, printlevel lvl, const char* format, ... );
void dbgmsg_init(const char *name);
void dbgmsg_set(printgrp grp, printlevel lvl);
printgrp dbgmsg_name_to_grpid(const char *name);

#ifdef __cplusplus
} //extern "C"
#endif

#endif

