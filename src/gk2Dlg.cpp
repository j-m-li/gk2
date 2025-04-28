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
#include <winbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG	
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGk2Dlg dialog

CGk2Dlg::CGk2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGk2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGk2Dlg)
	m_filelist = _T("");
	m_txt1 = _T("");
	m_txt2 = _T("");
	m_txt3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	self = this;
}

void CGk2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGk2Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_filelist);
	DDX_Text(pDX, IDC_EDIT2, m_txt1);
	DDX_Text(pDX, IDC_EDIT3, m_txt2);
	DDX_Text(pDX, IDC_EDIT4, m_txt3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGk2Dlg, CDialog)
	//{{AFX_MSG_MAP(CGk2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDABOUT, OnAbout)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_ENTERIDLE()
	ON_BN_CLICKED(ID_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_APP + 1, OnIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGk2Dlg message handlers

BOOL CGk2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CButton *b = (CButton*)GetDlgItem(IDC_BUTTON1);
	b->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));

	proc = new CCactus();
	running = FALSE;
	proc_set = FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGk2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGk2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGk2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGk2Dlg::OnAbout() 
{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	
}

void CGk2Dlg::OnButton1() 
{
	
	UpdateData(TRUE);
	LPTSTR p = m_filebuffer, s = m_filelist.GetBuffer(FILEBUFFER_LEN);
	while (s && *s > 0) {
		*(p++) = *(s++);	
	}
	*p = 0;

	CFileDialog fd(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT/*|OFN_ENABLESIZING*/  , _T("Wave Files (*.wav)|*.wav||"), NULL) ;
	fd.m_ofn.lpstrFile = m_filebuffer;
	fd.m_ofn.nMaxFile = FILEBUFFER_LEN;
	m_filebuffer[0] = 0;
	if (fd.DoModal() == IDOK) {
		POSITION pos;
		m_filelist = _T("");
		pos = fd.GetStartPosition();
		if (pos) m_filelist += _T("\"");
		while(pos) {
			m_filelist += fd.GetNextPathName(pos);
			if (pos) {
				m_filelist += _T("\" \"");
			} else {
				m_filelist += _T("\"");
			}
		}
		UpdateData(FALSE);
	}
}

void CGk2Dlg::OnOK() 
{
	// TODO: Add extra validation here
	if (running) return;
	proc_set = FALSE;
	running = 1;
	time = SetTimer(1, 1, timeout);
	OnIdle();
	//CDialog::OnOK();
}

void CGk2Dlg::OnIdle()
{
	
	CProgressCtrl *p = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	
	if (!running || proc->is_finish()) {
		if (proc_set) {
			proc->stop();
			p->SetPos(0);
			//m_txt1 = _T("");
			//m_txt2 = _T("");
			//m_txt3 = _T("");
			//UpdateData(FALSE);
		}
		proc_set = FALSE;
		running = FALSE;
		if (time) KillTimer(time);
		time = 0;
		return;
	}
	
	if (!proc_set) {
		peakl = 0;
		peakr = 0;
		current_file = NULL;

		UpdateData(TRUE);
		LPTSTR pp = m_filebuffer, s = m_filelist.GetBuffer(FILEBUFFER_LEN);
		*pp = 0;
		while (s && *s != 0) {
			*(pp++) = *(s++);	
		}
	
		proc->setup(m_filebuffer);
		proc_set = TRUE;
	
	}

	proc->process();	
	p->SetRange32(0, proc->get_len());
	
	p->SetPos(proc->get_pos());
	if (current_file != proc->get_file()) {
		current_file = proc->get_file();
		m_txt3 = current_file;
		UpdateData(FALSE);
	}
	
	
	if (peakl != proc->get_peakl()) {
		peakl = proc->get_peakl();
		m_txt1.Format(_T("Left peaks : %d"), peakl);
		UpdateData(FALSE);
	}
	if (peakr != proc->get_peakr()) {
		peakr = proc->get_peakr();
		m_txt2.Format(_T("Right peaks : %d"), peakr);
		UpdateData(FALSE);
	}
	
}

LRESULT CGk2Dlg::OnKickIdle(WPARAM, LPARAM lCount) 
{
	
	return TRUE;
}

BOOL CGk2Dlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CGk2Dlg::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}

LRESULT CGk2Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT r = 0;
    DWORD QueueStatus;
    r = CDialog::WindowProc(message, wParam, lParam);
	QueueStatus = GetQueueStatus(QS_ALLINPUT);
	if(HIWORD(QueueStatus) == 0 && running) {
		//PostMessage(WM_APP + 1, wParam + 1, lParam);
	}	
	return r;
}

void CGk2Dlg::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
	CDialog::OnEnterIdle(nWhy, pWho);
	
	// TODO: Add your message handler code here
	//OnIdle();
}

void CGk2Dlg::OnStop() 
{
	// TODO: Add extra cleanup here
	if (!running) return;
	running = FALSE;
	KillTimer(time);
	time = 0;
	OnIdle();
	//CDialog::OnCancel();
}

CGk2Dlg * CGk2Dlg::self = NULL;

void CALLBACK EXPORT CGk2Dlg::timeout(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	self->OnIdle();
}
