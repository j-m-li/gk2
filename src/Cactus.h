// Cactus.h: interface for the CCactus class.
//
//////////////////////////////////////////////////////////////////////
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

#if !defined(AFX_CACTUS_H__E58704BE_4467_43F9_85EC_735B51707633__INCLUDED_)
#define AFX_CACTUS_H__E58704BE_4467_43F9_85EC_735B51707633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCactus  
{
public:
	TCHAR * files;
	long file_len;
	TCHAR * file;
	int get_peakl();
	int get_peakr();
	TCHAR * get_file();
	int is_finish();
	void stop();
	int get_pos();
	int get_len();
	void setup(TCHAR *);
	void process();
	CCactus();
	virtual ~CCactus();

private:
	int main_run();
	int maxi_nb;
	int right;
	int left;
	int fd;
	int files_len;
	long off;
	int state;
};

#endif // !defined(AFX_CACTUS_H__E58704BE_4467_43F9_85EC_735B51707633__INCLUDED_)
