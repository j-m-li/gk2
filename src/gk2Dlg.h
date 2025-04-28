// gk2Dlg.h : header file
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

#if !defined(AFX_GK2DLG_H__FD8F7FD6_C01A_4925_9EB0_28416EBC763C__INCLUDED_)
#define AFX_GK2DLG_H__FD8F7FD6_C01A_4925_9EB0_28416EBC763C__INCLUDED_

#include "Cactus.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FILEBUFFER_LEN  10000

/////////////////////////////////////////////////////////////////////////////
// CGk2Dlg dialog

class CGk2Dlg : public CDialog
{
// Construction
public:
	static void CALLBACK EXPORT timeout(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
	
	BOOL running;
	void OnIdle();
	CGk2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGk2Dlg)
	enum { IDD = IDD_GK2_DIALOG };
	CString	m_filelist;
	CString	m_txt1;
	CString	m_txt2;
	CString	m_txt3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGk2Dlg)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL proc_set;
	CCactus *proc;
	HICON m_hIcon;
	TCHAR m_filebuffer[FILEBUFFER_LEN];
	// Generated message map functions
	//{{AFX_MSG(CGk2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnButton1();
	virtual void OnOK();
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg void OnStop();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	UINT time;
	int peakl;
	int peakr;
	TCHAR *current_file;
	static CGk2Dlg *self;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GK2DLG_H__FD8F7FD6_C01A_4925_9EB0_28416EBC763C__INCLUDED_)
