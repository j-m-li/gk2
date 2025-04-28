// gk2.cpp : Defines the class behaviors for the application.
//
/******************************************************************************
 *   "$Id:  $"
 *
 *   glitch killer
 *
 *                 Copyright (c) 2002-2003  O'ksi'D
 *
 *   This program is freedom software; you can redistribute it and/or modify
 *   it under the terms of the O'ksi'D Freedom Software License as published by
 *   the O'ksi'D; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the O'ksi'D Freedom Software License
 *   along with this program; if not, ask the person who distribute it.
 *
 *   Author : Jean-Marc Lienher ( http://oksid.ch )
 */

#include "stdafx.h"
#include "gk2.h"
#include "gk2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGk2App

BEGIN_MESSAGE_MAP(CGk2App, CWinApp)
	//{{AFX_MSG_MAP(CGk2App)
	ON_WM_ENTERIDLE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGk2App construction

CGk2App::CGk2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGk2App object

CGk2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CGk2App initialization

BOOL CGk2App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGk2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CGk2App::OnIdle(LONG lCount) 
{
	exit(0);
	// TODO: Add your specialized code here and/or call the base class
	if (CWinApp::OnIdle(lCount)) return TRUE;
	((CGk2Dlg*)m_pMainWnd)->OnIdle();
	return TRUE;
	
}



void CGk2App::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
	//CWnd::OnEnterIdle(nWhy, pWho);
	
	// TODO: Add your message handler code here
	((CGk2Dlg*)m_pMainWnd)->OnIdle();
}
