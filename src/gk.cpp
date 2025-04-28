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

#ifndef _WIN32
#include <unistd.h>
#define _write write
#define _read read
#define _open open
#define _close close
#define _lseek lseek
#define _O_RDWR O_RDWR
#define _O_BINARY 0
#define _seek seek
#else
#	include <io.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#define debug1 1

#define u_long unsigned int
#define u_short unsigned char
typedef struct wavhead {
  u_long        main_chunk;     /* 'RIFF' */
  u_long        length;         /* Length of rest of file */
  u_long        chunk_type;     /* 'WAVE' */

  u_long        sub_chunk;      /* 'fmt ' */
  u_long        sc_len;         /* length of sub_chunk, =16 (rest of chunk) */
  u_short       format;         /* should be 1 for PCM-code */
  u_short       modus;          /* 1 Mono, 2 Stereo */
  u_long        sample_fq;      /* frequence of sample */
  u_long        byte_p_sec;
  u_short       byte_p_spl;     /* samplesize; 1 or 2 bytes */
  u_short       bit_p_spl;      /* 8, 12 or 16 bit */

  u_long        data_chunk;     /* 'data' */
  u_long        data_length;    /* samplecount (lenth of rest of block?)*/
} wavhead;
	long l[33000];
	long r[3300];
	
	int nbs = 32;//32768;
int maxi_list[32];
long maxi_seek[32];
int maxi_nb = 0;
inline int gs(int s)
{
	if (s >= nbs) s -= nbs;
	if (s < 0) s = nbs + s;
	if (s > nbs || s< 0) exit(0);
	return s;
}


int main(int argc, char* argv[])
{
	char fi[1024];
	char *fl = NULL;
	printf("--- Glitch killer V1.0 (c) 2002 O'ksi'D ---\n");
	if (argc < 2) {
		//printf("Usage: gk wave_file.wav\n");	
		printf("Wave file: ");
		fscanf(stdin, "%s", fi);
		fl = fi;
	} else {
		fl = argv[1];
	}
	int peak = 14590; // tuned
	int max = 30000;
	int delta = 7000; // tuned
	int flat = 3500;
	int glitch = 9300;
	int fast = 31500;
	int large = 28500;
	int bad = 0;
	printf("starting scanning %s\n", fl);
	int fd = _open(argv[1], _O_RDWR | _O_BINARY);
	if (fd < 1) return 2;
	struct wavhead wavhd;
	int count = read(fd, ((char*)&wavhd), sizeof(wavhd));
	if(count != sizeof(wavhd) || wavhd.format != 1) return 3;
	int len = wavhd.data_length * 2 * 2;
	char buf[1024];
	long off = 0; 
	int rd = 0, left = 0, right = 0;
	rd = _read(fd, buf, 4);

	int rdc = 0, ldc = 0;
	int i;
	for (i = 0; i < nbs; i++) {
		l[i] = 0; r[i] = 0;

	}
	
	int s = 0;
	
	while (rd > 0) {

		
		l[s] = (unsigned) buf[0] + (buf[1] << 8);
		r[s] = (unsigned) buf[2] + (buf[3] << 8);
	

		int a1 = l[gs(s - 2)] - l[gs(s - 3)];
		int a2 = l[gs(s - 4)] - l[gs(s - 3)];
		
		int a3, a4;
		a3 = a1;
		if (a3 < 0) a3 = -a3;
		a4 = a2;
		if (a4 < 0) a4 = -a4;
		int a16 = a4;
		int a17 = a3;
		if (a4 < a3) {
			int t = a3;
			a3 = a4;
			a4 = t;
		}
		int p = l[gs(s - 3)];
		if (p < 0) p = -p;
		int p2 = l[gs(s - 1)];
		if (p2 < 0) p2 = -p2;
	
		
		int a5 = l[s] - l[gs(s - 1)];
		int a9 = a5;
		if (a5 < 0) a5 = -a5;
		int a6 = l[gs(s - 5)] - l[gs(s - 4)];
		int a7 = l[gs(s - 6)] - l[gs(s - 5)];
		if (a7 < 0) a7 = -a7;
		int a8 = l[gs(s - 2)] - l[gs(s - 1)];
		int a19 = a8;
		if (a8 < 0) a8 = -a8;
		int a10 = a6;
		if (a10 < 0) a10 = -a10;
		int a11 = l[gs(s - 7)] - l[gs(s - 6)];
		if (a11 < 0) a11 = -a11;
		int a12 = l[gs(s - 8)] - l[gs(s - 7)];
		if (a12 < 0) a12 = -a12;
		int a13 = l[gs(s - 1)] - l[gs(s - 3)];
		int a14 = l[gs(s - 5)] - l[gs(s - 3)];
		int a15 = 0;
		if (a1 < 0 && a13 < 0 && a14 < 0 && a8 < glitch && a10 < glitch && a7 < large) {
			a15 = -a13;
			if (a14 > a13) a15 = -a14; 
		} else if (a1 > 0 && a13 > 0 && a14 > 0 && a8 < glitch && a10 < glitch && a7 < large) {
			a15 = a13;
			if (a14 < a13) a15 = a14;
		}
		int a18 = l[gs(s - 1)] - l[gs(s - 3)];
		if (a18 < 0) a18 = -a18;
		long rms = 0;
		long dc = 0;
		for (i = 1; i < 18; i++) {
			if (i != 3) {
				rms += l[gs(s - i)] * l[gs(s -i)] / 16;
				dc += l[gs(s -i)] / 16;
			}
		}
		long rm = (long) sqrt(rms);
		rms = p - rm;
		dc -= l[gs(s - 3)];
		if (dc < 0) dc = -dc;

		if  ( /*p > max ||*/ (rm < 4850 && a16 > 22000) ||

			a3 > fast ||
				(a1 > peak && a2 > peak && a7 < flat && a10 < flat && a11 < flat && rm < 12500) ||
				(a1 < -peak && a2 < -peak && a7 < flat && a10 < flat && a11 < flat && rm < 12500) ||
			  (
				(a3 > glitch 
			
				) &&
				(
					(a1 > 0 && a2 > 0) || 
					(a1 < 0 && a2 < 0)
				) &&
				(
					(a1 > 0 && a6 < delta && 
						(a7 < delta || a15 > peak || 
							(rms > glitch && a3 > large)
						)
					) ||
					(a1 < 0 && a6 > -delta && 
						(a7 < delta || a15 > peak || 
							(rms > glitch && a3 > large)
						)
					)
				) &&
				(
					a15 > peak || 
					(
						a16 > fast && a17 > peak

					) ||
					(
						a7 < delta * 2  && 
							(
								a8 < delta ||
								(a1 > 0 && a9 < -delta) ||
								(a1 < 0 && a9 > delta)
							)
							
					) 
				) &&
				(
					(
						a3 > peak && 
						(
							(p > max ) || (p2 > max && p > (max / 2) && a5 > peak) ||
							(a3 > max && a4 > max)
						)
					) ||
					(a5 < flat && a10 < flat && a8 < flat && a7 < flat && a12 < flat && a11 < flat)
				)
			  )

			)
		{
			bad++;
			left++;
			p = 0;
			l[gs(s - 3)] = (l[gs(s - 2)] + l[gs(s - 4)]) / 2;
			
			buf[0] = l[gs(s - 3)] & 0xff;
			buf[1] = (l[gs(s - 3)] >> 8) & 0xff;
#ifndef debug1
			_lseek(fd, -16, SEEK_CUR);
			write(fd,buf, 2);
			_lseek(fd, 14, SEEK_CUR);
#else
			printf ("p %d %d %d %d %d\n", rm, a16 , a17, a3, dc);
			printf("\noiff: %d\n", off);
#endif
		}

		if (p > max && maxi_nb < 32) {
			maxi_list[maxi_nb] = (l[gs(s - 2)] + l[gs(s - 4)]) / 2;
			maxi_seek[maxi_nb] = off - 12 + sizeof(wavhd);
			maxi_nb++;
		}
		

		a1 = r[gs(s - 2)] - r[gs(s - 3)];
		a2 = r[gs(s - 4)] - r[gs(s - 3)];
		a3 = a1;
		if (a3 < 0) a3 = -a3;
		a4 = a2;
		if (a4 < 0) a4 = -a4;
		a16 = a4;
		a17 = a3;
		if (a4 < a3) a3 = a4;
		p = r[gs(s - 3)];
		if (p < 0) p = -p;
		p2 = r[gs(s - 1)];
		if (p2 < 0) p2 = -p2;
		a5 = r[s] - r[gs(s - 1)];
		a9 = a5;
		if (a5 < 0) a5 = -a5;
		a6 = r[gs(s - 5)] - r[gs(s - 4)];
		a10 = a6;
		if (a10 < 0) a10 = -a10;
		a7 = r[gs(s - 6)] - r[gs(s - 5)];
		if (a7 < 0) a7 = -a7;
		a8 = r[gs(s - 2)] - r[gs(s - 1)];
		if (a8 < 0) a8 = -a8;
		a11 = r[gs(s - 7)] - r[gs(s - 6)];
		if (a11 < 0) a11 = -a11;
		a12 = r[gs(s - 8)] - r[gs(s - 7)];
		if (a12 < 0) a12 = -a12;
		a13 = r[gs(s - 1)] - r[gs(s - 3)];
		a14 = r[gs(s - 5)] - r[gs(s - 3)];
		a15 = 0;
		
		if (a1 < 0 && a13 < 0 && a14 < 0 && a8 < glitch && a10 < glitch && a7 < glitch) {
			a15 = -a13;
			if (a14 > a13) a15 = -a14; 
		} else if (a1 > 0 && a13 > 0 && a14 > 0 && a8 < glitch && a10 < glitch && a7 < glitch) {
			a15 = a13;
			if (a14 < a13) a15 = a14;
		}
		rms = 0;
		for (i = 1; i < 18; i++) {
			if (i != 3) rms += r[gs(s - i)] * r[gs(s -i)] / 16;
		}
		rm = (long) sqrt(rms);
		rms = p - rm;
		if  ( (rm < 4850 && a16 > 22000) ||
				a3 > fast ||
				(a1 > peak && a2 > peak && a7 < flat && a10 < flat && a11 < flat && rm < 12500) ||
				(a1 < -peak && a2 < -peak && a7 < flat && a10 < flat && a11 < flat && rm < 12500) ||
			  (
				(a3 > glitch 
			
				) &&
				(
					(a1 > 0 && a2 > 0) || 
					(a1 < 0 && a2 < 0)
				) &&
				(
					(a1 > 0 && a6 < delta && (a7 < delta || a15 > peak || (rms > glitch && a3 > large))) ||
					(a1 < 0 && a6 > -delta && (a7 < delta || a15 > peak || (rms > glitch && a3 > large)))
				) &&
				(
					a15 > peak || 
					(
						a16 > fast && a17 > peak

					) ||
					(
						a7 < delta * 2  && 
							(
								a8 < delta ||
								(a1 > 0 && a9 < -delta) ||
								(a1 < 0 && a9 > delta)
							)
							
					) 
				) &&
				(
					(
						a3 > peak && 
						(
							(p > max ) || (p2 > max && p > (max / 2) && a5 > peak) ||
							(a3 > max && a4 > max)
						)
					) ||
					(a5 < flat && a10 < flat && a8 < flat && a7 < flat && a12 < flat && a11 < flat)
				)
			  )

			)
		{
			right++;
			bad++;
			p = 0;
			
			r[gs(s - 3)] = (r[gs(s - 2)] + r[gs(s - 4)]) / 2;
			buf[0] = r[gs(s - 3)] & 0xff;
			buf[1] = (r[gs(s - 3)] >> 8) & 0xff;
#ifndef debug1
			_lseek(fd, -14, SEEK_CUR);
			write(fd,buf, 2);
			_lseek(fd, 12, SEEK_CUR);
#else
			printf ("right %d %d %d %d %d\n", rm, a16 , a17, a3, dc);
			printf("\noff: %d\n", off);
#endif
		}

		if (p > max && maxi_nb < 32) {
			maxi_list[maxi_nb] = (r[gs(s - 2)] + r[gs(s - 4)]) / 2;
			maxi_seek[maxi_nb] = off - 10 + sizeof(wavhd);
			maxi_nb++;
		}
		
		off += rd;
		if (off % (750000)  == 0) {
			if (bad == 0) {
				printf(".");
			} else {
				printf("#");
			}
			bad = 0;
		}
		rd = _read(fd, buf, 4);
		s++; if (s >= nbs) s = 0;
	}

	if (maxi_nb > 0 && maxi_nb < 32) {
		printf("\nRemoving %d maxi peak", maxi_nb);
		while(maxi_nb > 0) {
			maxi_nb--;
			buf[0] = maxi_list[maxi_nb] & 0xff;
			buf[1] = (maxi_list[maxi_nb] >> 8) & 0xff;
			_lseek(fd, maxi_seek[maxi_nb], SEEK_SET);
			write(fd,buf, 2);
		}
		
	}
	
	printf("\nremoved peak : left %d  right %d\n", left, right);
	_close(fd);
	return 0;
}

