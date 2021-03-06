/*
    khn, invoker the viwer of KwikINF on-line documents
    Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#define INCL_WIN
#include <os2.h>

#include "KPMLib.h"

#include "KHNClient.h"

#include "khn.h"

int KHN::Run()
{
    KHNClient kclient;
    kclient.RegisterClass( GetHAB(), WC_KHN, CS_MOVENOTIFY, sizeof( PVOID ));

    ULONG flFrameFlags;
    flFrameFlags = FCF_SYSMENU | FCF_TITLEBAR | FCF_TASKLIST | FCF_DLGBORDER;

    KFrameWindow kframe;
    kframe.CreateStdWindow( KWND_DESKTOP,           // parent window handle
                            WS_VISIBLE,             // frame window style
                            &flFrameFlags,          // window style
                            KHN_TITLE,              // window title
                            0,                      // default client style
                            0,                      // resource in exe file
                            ID_KHN,                 // frame window id
                            kclient                 // client window handle
                          );

    if( kframe.GetHWND())
    {
        if( !kframe.RestoreWindowPos( KHN_TITLE, KHN_POSITION_KEY ))
        {
            RECTL rcl;

            kclient.CalcClientRect( &rcl );

            kframe.CalcFrameRect( &rcl, FALSE );

            kframe.SetWindowPos( 0, 0, 0,
                                 rcl.xRight - rcl.xLeft,
                                 rcl.yTop - rcl.yBottom,
                                 SWP_MOVE | SWP_SIZE );
        }

        kframe.SetWindowPos( KWND_TOP, 0, 0, 0, 0,
                             SWP_SHOW | SWP_ZORDER | SWP_ACTIVATE |
                             SWP_RESTORE );

        KPMApp::Run();

        kframe.StoreWindowPos( KHN_TITLE, KHN_POSITION_KEY );

        kframe.DestroyWindow();
    }

    return 0;
}

int main( int argc, char *argv[])
{
    KHN khn;

    return khn.Run();
}
