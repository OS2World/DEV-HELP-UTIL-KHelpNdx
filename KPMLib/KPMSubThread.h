/*
    KPMLib, C++ encapsulation class library for OS/2 PM
    Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

#ifndef KPM_SUB_THREAD_H
#define KPM_SUB_THREAD_H

#define INCL_WIN
#include <os2.h>

#include "KPMThread.h"

class KPMSubThread : protected KPMThread
{
public :
    KPMSubThread() : KPMThread() {}
    virtual ~KPMSubThread() {}

    virtual bool BeginThread( void *arg = 0, int cbStackSize = 1024 * 1024 );
    virtual bool WaitThread( bool fWait = true ) const;

protected :
    virtual int  Run() { return 0; }
    virtual void ThreadMain( void* arg ) { return; }

private :
    static void ThreadStart( void* arg );

    void PMThreadStart( void* arg );
};
#endif
