
/**
 *  File:      NXHeader.h
 *
 *  Author:    ����(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   ����ѧϰDX����Ⱦ���
 */

#ifndef		__ZX_HEADER_H__
#define		__ZX_HEADER_H__

#include <shlwapi.h>
#include <windows.h>
#define		_T(queto)	TEXT(queto)


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

#ifndef		UNICODE
#define		TString		string
#define		TFstream	fstream
#else
#define		TString		wstring
#define		TFstream	wfstream
#endif



//������Ϸ����Ĵ�С
#define		MAINFRAME_WIDTH		1024
#define		MAINFRAME_HEIGHT	768




#pragma comment(lib, "Msimg32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "kernel32")
#pragma comment(lib, "shlwapi")


#endif