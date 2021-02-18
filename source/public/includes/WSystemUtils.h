//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WSystemUtils.h $
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
#ifndef __WSystemUtils__
#define __WSystemUtils__
 
#include "WSysType.h"

#define WTOOLBOX

inline bool _CheckResultFunc(const char* caller, intptr_t result, intptr_t okResult, const char* codeString, const char* fileStr, int32 lineNo)
{
#pragma unused (caller, codeString, fileStr, lineNo)
	ASSERT_MSG(result == okResult, FORMAT_ARGS("%s: %s returned error: %p, called from file: %s at line %d \n", caller, codeString, result, fileStr, lineNo));
	return result == okResult;
}

#define WIN_CHECKERROR(err, routinename) ASSERT_MSG(err == ERROR_SUCCESS, FORMAT_ARGS("%s returned error: %d\n", #routinename, err))
//#define WIN_CHECKRESULT(code) {code; DWORD err = GetLastError(); ASSERT_MSG(err == ERROR_SUCCESS, FORMAT_ARGS("%s returned error: %d\n", #code, err));}
#define WIN_CHECKRESULT(code) SetLastError(ERROR_SUCCESS); code; _CheckResultFunc("WIN_CHECKRESULT", (int32) GetLastError(), (int32) ERROR_SUCCESS, #code,__FILE__,__LINE__)

#define	SysPointH( point ) (point).x
#define	SysPointV( point ) (point).y

	inline void SetSysPoint(SysPoint& pt, SysCoord x, SysCoord y)
	{
		pt.x = x; pt.y = y;
	}

	inline SysCoord SysRectLeft(const SysRect& sysRect)
		{ return sysRect.left; }
	inline SysCoord SysRectTop(const SysRect& sysRect)
		{ return sysRect.top; }
	inline SysCoord SysRectRight(const SysRect& sysRect)
		{ return sysRect.right; }
	inline SysCoord SysRectBottom(const SysRect& sysRect)
		{ return sysRect.bottom; }
	inline SysCoord SysRectWidth(const SysRect& sysRect)
		{ return sysRect.right - sysRect.left; }		
	inline SysCoord SysRectHeight(const SysRect& sysRect )
		{ return sysRect.bottom - sysRect.top; }
	inline SysCoord SysRectCenterH(const SysRect& sysRect)
		{ return (sysRect.right + sysRect.left)/2; }		
	inline SysCoord SysRectCenterV(const SysRect& sysRect )
		{ return (sysRect.bottom + sysRect.top)/2; }

	inline void SetSysRectLeft(SysRect& sysRect, SysCoord left)
		{ sysRect.left = left; }
	inline void SetSysRectTop(SysRect& sysRect, SysCoord top)
		{ sysRect.top = top; } 		
	inline void SetSysRectRight(SysRect& sysRect, SysCoord right)
		{ sysRect.right = right; } 		
	inline void SetSysRectBottom(SysRect& sysRect, SysCoord bottom)
		{ sysRect.bottom = bottom; }
	PUBLIC_DECL void  SetSysRectWidth(SysRect& sysRect, SysCoord width);
	PUBLIC_DECL void  SetSysRectHeight(SysRect& sysRect, SysCoord height);
	inline void SetSysRect(SysRect& rt, SysCoord left, SysCoord top, SysCoord right, SysCoord bottom)
		{ WTOOLBOX::SetRect(&rt, left, top, right, bottom); }
	PUBLIC_DECL void SetSysRectLTRB(SysRect& rect, SysCoord left, SysCoord top, SysCoord right, SysCoord bottom);
	PUBLIC_DECL void SetSysRectLTWH(SysRect& rect, SysCoord left, SysCoord top, SysCoord width, SysCoord height);

inline SysRect SysRgnBBOX( HRGN rgn )
{
	RECT r; 
	GetRgnBox(rgn, &r); 
	return r; 
}

inline SysRect GetRegionRect( HRGN rgn )
	{ return ::SysRgnBBOX( rgn ); }

	PUBLIC_DECL void GetRegionRectData( SysRgn rgn, std::vector<SysRect>& rectsVec );

inline bool16 SysPointInSysRect( const SysPoint& p, const SysRect& r )
	{ return ::PtInRect( &r, p ); }

inline bool16 EmptySysRect( const SysRect& r )
	{ return IsRectEmpty( &r ); }

inline bool16 IntersectSysRect(const SysRect& src1, const SysRect& src2, SysRect& dst)
	{ return (bool16)::IntersectRect(	&dst, &src1, &src2 ); }

inline void UnionSysRect(const SysRect& src1, const SysRect& src2, SysRect& dst)
	{ ::UnionRect( &dst, &src1, &src2 ); }

inline void InsetSysRect(SysRect& rt, int32 deltaX, int32 deltaY)
	{ ::InflateRect( &rt, -deltaX, -deltaY ); }

inline void OffsetSysRect(SysRect& rt, int32 deltaX, int32 deltaY)
	{ ::OffsetRect( &rt, deltaX, deltaY ); }

	inline void SysRectMakeZeroOrigin(SysRect& rt)
	{ ::OffsetRect( &rt, -rt.left, -rt.top ); }


inline SysPoint GetMousePosition()	
{
	// ----- Returns mouse position in screen/global coordinates
	
	SysPoint pt;
	::GetCursorPos( &pt );	
	return pt;
}

namespace SystemUtils
{
	// ----- Returns a value in 60ths of a second.
	inline uint32 TickCount()
    {
        return (uint32)((double) ::GetTickCount() / 16.6667);
    }

    inline uint64 Milliseconds()
    {
        return static_cast<uint64>(::GetTickCount64());
    }
}
inline uint32 GetCaretTime()
	{ return (uint32)((double) ::GetCaretBlinkTime() / 16.6667); }

inline SysRgn CreateRectSysRgn (SysRect sysRect)
	{	return ::CreateRectRgn (sysRect.left, sysRect.top, sysRect.right, sysRect.bottom); }
	
inline SysRgn CreateSysRgn()
	{ return ::CreateRectRgn(0, 0, 0, 0); }

inline void K2DeleteObject(HGDIOBJ gdiObject)
	{ if (gdiObject != 0) {if (::DeleteObject (gdiObject) == 0) {ASSERT_FAIL (FORMAT_ARGS("The GDI object was not deleted. Error code: %d", ::GetLastError ()));} } }

inline void DeleteSysRgn(SysRgn sysRgn)
	{ K2DeleteObject (sysRgn); }
	
inline SysRgn CopySysRgn(SysRgn sysRgn)
	{ 
		SysRgn copy = ::CreateRectRgn(0, 0, 0, 0);;
	  	::CombineRgn(copy, sysRgn, 0L, RGN_COPY); 
	  	return copy; 
	}
	
inline void CopySysRgn(SysRgn srcRgn, SysRgn dstRgn)
	{ 
	  	::CombineRgn(dstRgn, srcRgn, 0L, RGN_COPY); 
	}

inline bool16 RectInSysRgn(SysRgn rgn, const SysRect *theRect)
{ return ::RectInRegion(rgn, theRect); }

inline bool16 EqualSysRgn(SysRgn rgn1, SysRgn rgn2)
	{ return ::EqualRgn(rgn1, rgn2); }
	
inline void UnionSysRgn(SysRgn srcRgn1, SysRgn srcRgn2, SysRgn destRgn)
	{ ::CombineRgn(destRgn, srcRgn1, srcRgn2, RGN_OR); }
	
inline void DiffSysRgn(SysRgn srcRgn, SysRgn removeRgn, SysRgn destRgn)
	{ ::CombineRgn(destRgn, srcRgn, removeRgn, RGN_DIFF); }
	
inline void IntersectSysRgn(SysRgn srcRgn1, SysRgn srcRgn2, SysRgn destRgn)
	{ ::CombineRgn (destRgn, srcRgn1, srcRgn2, RGN_AND); }
	
inline bool16 EmptySysRgn(SysRgn theRgn)
{
	RECT r; 
	::GetRgnBox(theRgn, &r); 

	return ((r.left == r.right) || (r.top == r.bottom));
}

inline void XorSysRgn(SysRgn srcRgn1, SysRgn srcRgn2, SysRgn destRgn)
	{ ::CombineRgn (destRgn, srcRgn1, srcRgn2, RGN_XOR); }
	
inline void OffsetSysRgn(SysRgn rgn, int32 deltaX, int32 deltaY)
	{ ::OffsetRgn (rgn, deltaX, deltaY); }
	
inline bool16 SysPointInSysRgn( const SysPoint& p, SysRgn rgn )
	{ return ::PtInRegion(rgn, p.x, p.y); }

inline void EraseSysRect(SysPort port, const SysRect *theRect)
{
	HBRUSH hBrush = ::GetSysColorBrush (COLOR_3DFACE);
	::FillRect (port, theRect, hBrush);
	K2DeleteObject (hBrush);
}
inline void EraseSysRgn(SysPort port, const SysRgn theRgn)
{
	HBRUSH hBrush = ::GetSysColorBrush (COLOR_3DFACE);
	::FillRgn (port, theRgn, hBrush);
	K2DeleteObject (hBrush);
}

//===    SysWireframe     ========================

	inline SysWireframe CreateSysWireframe()
		{ return ::CreateSysRgn(); }

	inline SysWireframe CreateRectSysWireframe (SysRect sysRect)
		{ return ::CreateRectSysRgn(sysRect);}

	inline void DeleteSysWireframe(SysWireframe sysRgn)
		{ ::DeleteSysRgn (sysRgn); }
	
	inline SysWireframe CopySysWireframe(SysWireframe sysRgn)
		{ return ::CopySysRgn(sysRgn); }
	
	inline void CopySysWireframe(SysWireframe srcRgn, SysWireframe dstRgn)
		{ ::CopySysRgn(srcRgn, dstRgn); }

	inline void OffsetSysWireframe(SysWireframe rgn, int32 deltaX, int32 deltaY)
		{ ::OffsetSysRgn (rgn, deltaX, deltaY); }

	inline void UnionSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
		{ ::UnionSysRgn(srcRgn1, srcRgn2, destRgn); }
		
	inline void DiffSysWireframe(SysWireframe srcRgn, SysWireframe removeRgn, SysWireframe destRgn)
		{ ::DiffSysRgn(srcRgn, removeRgn, destRgn); }
		
	inline void IntersectSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
		{ ::IntersectSysRgn (srcRgn1, srcRgn2, destRgn); }
		
	inline void XorSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
		{ ::XorSysRgn (srcRgn1, srcRgn2, destRgn); }

#endif // __WSystemUtils__
