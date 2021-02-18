//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MSysType.h $
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
#ifndef __MSYSTYPE__
#define __MSYSTYPE__

#include "K2TypeTraits.h"
//======================================================================
// Isolate windowing system (Mac OS QuickDraw or Core Graphics) vs. Windows GDI)
//======================================================================

// 32-bit integer coordinate space
struct Int32Rect {						// Use in cases where coords must be integral (but not QD specific). Bitmap bounds, image internal (pixel) bounds, etc.
	int32               top;
	int32               left;
	int32               bottom;
	int32               right;
	
	Int32Rect() {top = 0; left = 0; bottom = 0; right = 0;}
    Int32Rect(const Int32Rect &) = default;
    Int32Rect& operator=(const Int32Rect& r) = default;
};

// Default coordinate space - based on Core Graphics
typedef CGFloat SysCoord;				// Floating point coordinate system (from Core graphics)

struct SysPoint : CGPoint {
	SysPoint(SysCoord h, SysCoord v ) {x = h; y = v;}
	SysPoint(const CGPoint& pt) {x = pt.x; y = pt.y;}
    SysPoint(const SysPoint& pt) {x = pt.x; y = pt.y;}
	SysPoint() {x = 0; y = 0;}
	SysPoint& operator=(const SysPoint& pt)  {x = pt.x; y = pt.y; return *this;}
	SysPoint& operator=(const CGPoint& pt)  {x = pt.x; y = pt.y; return *this;}
};

typedef SysPoint GSysPoint;		// "Global" SysPoint
typedef SysPoint WSysPoint;		// "Window" SysPoint

struct SysSize : CGSize {
	SysSize(SysCoord h, SysCoord w ) {width = h; height = w;}
	SysSize(const CGPoint& pt) {width = pt.x; height = pt.y;}
	SysSize(const CGSize& sz)  {width = sz.width; height = sz.height;}
	SysSize() {width = 0; height = 0;}
	SysSize& operator=(const SysPoint& pt)  {width = pt.x; height = pt.y; return *this;}
	SysSize& operator=(const CGSize& sz)		 {width = sz.width; height = sz.height; return *this;}
};

struct SysRect : CGRect {
	SysRect(SysCoord left, SysCoord top, SysCoord right, SysCoord bottom ) {origin.x = left; origin.y = top; size.width = right - left; size.height = bottom - top;}
	SysRect(const SysPoint& theOrigin, const SysSize& theSize ) {origin = theOrigin; size = theSize;}
	SysRect(const Int32Rect& r) {origin.x = r.left; origin.y = r.top; size.width = r.right - r.left; size.height = r.bottom - r.top;}
	SysRect(const CGRect& r) {origin = r.origin; size = r.size;}
    SysRect(const SysRect& r) {origin = r.origin; size = r.size;}
	SysRect() {origin.x =0; origin.y = 0; size.width = 0; size.height = 0;}
	SysRect& operator=(const SysRect& r)  {origin = r.origin; size = r.size; return *this;}
	SysRect& operator=(const CGRect& r)  {origin = r.origin; size = r.size; return *this;}
//  		bool16 operator==(const SysRect& r) const  {return (origin.x == r.origin.x) && (origin.y == r.origin.y) && (size.width == r.size.width) && (size.height == r.size.height);}
//		bool16 operator!=(const SysRect& r) const  {return !(*this == r);}
	
	operator Int32Rect() const 
	{
		Int32Rect foo; 
		CGRect temp = CGRectIntegral(*this);
		foo.left = (int32) temp.origin.x; foo.top = (int32) temp.origin.y; foo.right = foo.left + (int32) temp.size.width; foo.bottom = foo.top +(int32) temp.size.height;
		return foo;
	}
};

typedef SysRect GSysRect;			// SysRect in "Global" screen or device coordinates
typedef SysRect WSysRect;			// SysRect in "Window" coordinates

typedef HIMutableShapeRef SysRgn;		
typedef HIShapeRef ConstSysRgn;		// Ref counted, const version.

typedef SysRgn SysWireframe;		// Implementation of wireframe feedback  
DECLARE_BASE_TYPE(SysRgn);

typedef SysCoord GSysCoord;	// "Global" coordinate
typedef SysCoord WSysCoord;	// "Window" coordinate
typedef uint16_t SysChar; // UTF16's just like Drover. This will hopefully fix some international languages keyboard shortcut problems.
typedef uint16 SysKeyCode;	// code for key on keyboard
typedef WindowPtr SysWindow;
DECLARE_BASE_TYPE(SysWindow);
	
typedef void* SysControl;

typedef GrafPtr SysPort;
//DECLARE_BASE_TYPE(SysPort); // GrafPtr == WindowPtr
typedef CGContextRef SysPort_NEW;
DECLARE_BASE_TYPE(SysPort_NEW);

typedef GWorldPtr SysBitmap;				// This will become a CGContextRef
typedef CGContextRef SysBitmap_NEW;

typedef int16 SysFileRef;	// open file reference
typedef void* SysEvent;
typedef Handle SysHandle;
// Rather than remove calls to HLock and HUnlock we will simply define them as a no-op. 
#define HLOCK
#define HUNLOCK



typedef int16 MenuID;
typedef int32 PlatformError;
typedef uint32 UserError;
typedef int16 CursorID;

typedef struct FInfo SysFileInfo;

typedef ResType RsrcType;
typedef char *RsrcName;
typedef uint32 RsrcID;

// Connection information for loading & unloading DLLs
typedef CFBundleRef SysConnection;	//BundleRef is nil if plugin bundle/dylib is not loaded
DECLARE_BASE_TYPE(SysConnection);
	
#endif // __SYSTYPE__
