//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WSysType.h $
//  
//  Owner: ?
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __WSYSTYPE__
#define __WSYSTYPE__


//======================================================================
// Isolate windowing system (QuickDraw vs. Windows)
//======================================================================

#ifndef __MWERKS__
	#include "BaseType.h"
#endif

#define ON_WIN_USE_GDIPLUS_COORDS	1

	//======================================================================
	// Isolate windowing system Mac OS (QuickDraw or Core Graphics) vs. Windows (GDI or GDI+)
	//======================================================================

#ifdef ON_WIN_USE_GDIPLUS_COORDS
#else
#endif

	// typedef FIXED SysFixed;
	typedef RECT GDIRect;
	typedef POINT GDIPoint;
	typedef SIZE GDISize;
	
	typedef GDIRect SysRect;
	typedef GDIRect GSysRect;			// SysRect in "Global" screen or device coordinates
	typedef GDIRect WSysRect;			// SysRect in "Window" coordinates
	typedef GDIRect Int32Rect;			// Use in cases where coords must be integral. Bitmap bounds, image internal (pixel) bounds, etc.
	typedef GDIPoint SysPoint;
	typedef GDIPoint GSysPoint;		// "Global" SysPoint
	typedef GDIPoint WSysPoint;		// "Window" SysPoint  (result of GlobalToLocal)
	typedef int32 SysCoord;
	typedef SysCoord GSysCoord;	// "Global" coordinate
	typedef SysCoord WSysCoord;	// "Window" coordinate
#ifdef _UNICODE
	//typedef textchar SysChar;		// character code used by platform (UNICODE)
	typedef TCHAR SysChar;		// character code used by platform (UNICODE)
#else
	typedef unsigned char SysChar;	// character code used by platform (ASCII+)
#endif
	typedef uint16 SysKeyCode;	// code for key on keyboard
	typedef HWND SysWindow;
	typedef HWND SysControl;
	typedef HWND SysDialog;
	typedef HRGN SysRgn;
	typedef HRGN SysWireframe;
	typedef HDC SysPort;
	typedef MSG* SysEvent;
	typedef HANDLE SysHandle;
	typedef int16 MenuID;
	typedef uint32 UserError;
	typedef int32 CursorID;
	typedef struct RGBColor{	//copied from MAC
		unsigned short red;
		unsigned short green;
		unsigned short blue;
	}RGBColor;

	typedef int32 Fixed;

	typedef HANDLE ThreadID;
	
	typedef uint32 OSType; 

	typedef uint32 RsrcType; 
	typedef uint32 RsrcID;

	struct FileInfo {
			OSType creator;
			OSType type;
		}; 

	typedef DWORD PlatformError;

typedef struct FileInfo SysFileInfo;

typedef HDC	SysBitmap;
typedef SysBitmap SysBitmap_NEW;
typedef SysPort SysPort_NEW;


typedef int32 SysSocket;

typedef HINSTANCE SysConnection;
	// Connection information for loading & unloading DLLs
	
struct SysSize : GDISize {
		SysSize(SysCoord h, SysCoord w ) {cx = h; cy = w;}
		SysSize(const GDIPoint& pt) {cx = pt.x; cy = pt.y;}
		SysSize(const GDISize& sz)  {cx = sz.cx; cy = sz.cy;}
		SysSize() {cx = 0; cy = 0;}
		SysSize& operator=(const SysPoint& pt)  {cx = pt.x; cy = pt.y; return *this;}
		SysSize& operator=(const GDISize& sz)		 {cx = sz.cx; cy = sz.cy; return *this;}

		operator const GDISize & () const { return *this; }
};


#define kDefaultFPUExceptions	_CW_DEFAULT
	// Default exceptions are Windows default for now. In the future we
	// may want to turn off exception handling for certain floating point
	// errors so we know when they happen. If so, change _CW_DEFAULT to
	// something else (see Windows documention for _controlfp)

#endif // __WSYSTYPE__
