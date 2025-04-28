// gk2.h : main header file for the GK2 application
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

#if !defined(AFX_GK2_H__24728671_3B60_444E_A257_A5833AD82812__INCLUDED_)
#define AFX_GK2_H__24728671_3B60_444E_A257_A5833AD82812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGk2App:
// See gk2.cpp for the implementation of this class
//

class CGk2App : public CWinApp
{
public:
	CGk2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGk2App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGk2App)
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GK2_H__24728671_3B60_444E_A257_A5833AD82812__INCLUDED_)
