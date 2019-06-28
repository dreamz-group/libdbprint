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

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "include/dbgprint.h"
#include <stdarg.h>

//
// NOTE SHOULD BE SAME ORDER AS _printgrp in the .h file
static print_levels print_level[] = {
    {DBG_GRP_GENERAL,  "DBG_GRP_GENERAL", "  : ", DBG_PRINT_WARNING},
    {DBG_GRP_NETWORK,  "DBG_GRP_NETWORK", "  : ", DBG_PRINT_WARNING},
    {DBG_GRP_STARTUP,  "DBG_GRP_STARTUP", "  : ", DBG_PRINT_WARNING},
    {DBG_GRP_DEVELOP,  "DBG_GRP_DEVELOP", "  : ", DBG_PRINT_WARNING},
    {DBG_GRP_DEBUGING, "DBG_GRP_DEBUGING", " : ", DBG_PRINT_WARNING},
    {DBG_GRP_DBGPRINT, "DBG_GRP_DBGPRINT", " : ", DBG_PRINT_WARNING},
    {DBG_GRP_MQTT,     "DBG_GRP_MQTT", "     : ", DBG_PRINT_WARNING},
    {DBG_GRP_ALL,      "DBG_GRP_ALL", "      : ", DBG_PRINT_WARNING},
    {DBG_GRP_ERR,      NULL, NULL, 0} // Keep this last...
};

void dbgmsg_init(const char *name)
{
    // Stupid test to check for inconsistency...
    if (print_level[DBG_GRP_ALL].index == DBG_GRP_ALL)
        return;

    // You should really reed the comments in the dbgprint.h file...
    // If you get here, it probably a good thing to take the rest of the day off :-)
    printf("ERROR: libdbgprint inconsistency found!!!\n");
    exit(-1);
}

printgrp dbgmsg_name_to_grpid(const char *name)
{
    print_levels *rp;
    if (!name)
        return DBG_GRP_ERR;

    // Loop through all...
    for (rp = print_level; rp->index != DBG_GRP_ERR; rp++)
    {
        if (strcmp(name, rp->name) == 0)
        {
            return rp->index;
        }
    }
    printf("Did not find DBG GRP -> (%s)\n", name); 
    return DBG_GRP_ERR;
}

void dbgmsg_set(printgrp grp, printlevel lvl)
{
    int i;
    dbgmsg(DBG_GRP_DBGPRINT, DBG_PRINT_WARNING, "Setting dbgprint level for %s to %d\n", print_level[grp].name, lvl);
    if( DBG_GRP_ALL == grp )
    {
        for( i=0; i < DBG_GRP_ALL; ++i )
        {
            print_level[i].level = lvl;
        }
        return;
    }
    print_level[grp].level = lvl;
}

void dbgmsg_ex(printgrp grp, printlevel lvl, const char *format, ...)
{
    va_list arglist;

    // Check print level...
    if (print_level[grp].level > lvl)
    {
        return;
    }
    // Print actual print...
    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);

}
void dbgmsg(printgrp grp, printlevel lvl, const char *format, ...)
{
    va_list arglist;

    // Check print level...
    if (print_level[grp].level > lvl)
    {
        return;
    }

    if (print_level[DBG_GRP_DBGPRINT].level < DBG_PRINT_WARNING)
    {
        printf("%s%s", print_level[grp].name, print_level[grp].spaces);
    }
    // Print actual print...
    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);

    // NOTE: use vsnprintf and add syslog prints...
}

