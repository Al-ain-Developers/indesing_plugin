//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MSystemUtils.h $
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
#ifndef __MSystemUtils__
#define __MSystemUtils__

#include "MSysType.h"
#include "ISession.h"
#include "WorkspaceID.h"

#define MTOOLBOX
#define QUICKDRAW
#define QUARTZ
#define HITOOLBOX

inline bool _CheckResultFunc(const char* caller, intptr_t result, intptr_t okResult, const char* codeString, const char* fileStr, int32 lineNo)
{
#pragma unused (caller, codeString, fileStr, lineNo)
	ASSERT_MSG(result == okResult, FORMAT_ARGS("%s: %s returned error: %p, called from file: %s at line %d \n", caller, codeString, result, fileStr, lineNo));
	return result == okResult;
}

#define MAC_CHECKERROR(err, routinename) ASSERT_MSG(err == noErr, FORMAT_ARGS("%s returned error: %d\n", #routinename, err))
//#define MAC_CHECKRESULT(code) {OSStatus err = code; ASSERT_MSG(err == noErr, FORMAT_ARGS("%s returned error: %d\n", #code, err));}
#define MAC_CHECKRESULT(code) _CheckResultFunc("MAC_CHECKRESULT", (int32) code, (int32) noErr, #code,__FILE__,__LINE__)


// The following macros allow use as l-values
#define	SysPointH( point ) (point).x
#define	SysPointV( point ) (point).y

inline SysCoord SysRectLeft(const SysRect& sysRect)
	{ return sysRect.origin.x; }
inline SysCoord SysRectTop(const SysRect& sysRect)
	{ return sysRect.origin.y; }
inline SysCoord SysRectRight(const SysRect& sysRect)
	{ return (sysRect.origin.x + sysRect.size.width); }
inline SysCoord SysRectBottom(const SysRect& sysRect)
	{ return (sysRect.origin.y + sysRect.size.height); }
inline SysCoord SysRectWidth(const SysRect& sysRect)
	{ return sysRect.size.width; }
inline SysCoord SysRectHeight(const SysRect& sysRect )
	{ return sysRect.size.height; }
inline SysCoord SysRectCenterH(const SysRect& sysRect)
	{ return int32(sysRect.origin.x + sysRect.size.width/2.); }		
inline SysCoord SysRectCenterV(const SysRect& sysRect )
	{ return int32(sysRect.origin.y + sysRect.size.height/2.); }
	
// These should not be inlined, since, the new coordinate(s) often contains some combination of existing coordinates.
//	Also note that thes functions are design for compatibility with rectangles that based on (top,left,bottom,right)
//	Thus SetSysRectLeft changes both origin.x and size.width of the underlying HIRect...(Beware)
#ifdef PUBLIC_BUILD
#pragma export on
#endif
PUBLIC_DECL void SetSysRectLeft(SysRect& sysRect, SysCoord left);
PUBLIC_DECL void SetSysRectTop(SysRect& sysRect, SysCoord top);
PUBLIC_DECL void SetSysRectRight(SysRect& sysRect, SysCoord right);
PUBLIC_DECL void SetSysRectBottom(SysRect& sysRect, SysCoord bottom);
PUBLIC_DECL void SetSysRectWidth(SysRect& sysRect, SysCoord width);
PUBLIC_DECL void SetSysRectHeight(SysRect& sysRect, SysCoord height);
PUBLIC_DECL void SetSysRect(SysRect& rect, SysCoord left, SysCoord top, SysCoord right, SysCoord bottom);
PUBLIC_DECL void SetSysRectLTRB(SysRect& rect, SysCoord left, SysCoord top, SysCoord right, SysCoord bottom);
PUBLIC_DECL void SetSysRectLTWH(SysRect& rect, SysCoord left, SysCoord top, SysCoord width, SysCoord height);
#ifdef PUBLIC_BUILD
#pragma export off
#endif

inline void SetSysPoint(SysPoint& pt, SysCoord x, SysCoord y)
{
	pt.x = x; pt.y = y;
}


#define SysRgnBBOX( rgn ) GetRegionRect(rgn)
inline SysRect GetRegionRect( ConstSysRgn rgn )
{
	SysRect aRect;
	MTOOLBOX::HIShapeGetBounds(rgn,&aRect);
	return aRect;
}

#ifdef PUBLIC_BUILD
#pragma export on
#endif
PUBLIC_DECL void GetRegionRectData( ConstSysRgn rgn, std::vector<SysRect>& rectsVec );
#ifdef PUBLIC_BUILD
#pragma export off
#endif

inline bool16 SysPointInSysRect( const SysPoint& p, const SysRect& r )
	{ return (MTOOLBOX::CGRectContainsPoint( r, p ) == true); }

inline bool16 EmptySysRect( const SysRect& r )
	{ return (MTOOLBOX::CGRectIsEmpty( r ) == true); }

inline bool16 IntersectSysRect(const SysRect& src1, const SysRect& src2, SysRect& dst)
{	
	dst = MTOOLBOX::CGRectIntersection(src1, src2); 
	if(MTOOLBOX::CGRectIsNull(dst))
		dst = MTOOLBOX::CGRectMake(0,0,0,0);
	
	return (MTOOLBOX::CGRectIsEmpty(dst) != true);
}

inline void UnionSysRect(const SysRect& src1, const SysRect& src2, SysRect& dst)
	{ dst = MTOOLBOX::CGRectUnion(src1, src2); }

inline void InsetSysRect(SysRect& rt, SysCoord deltaX, SysCoord deltaY)
	{ rt = MTOOLBOX::CGRectInset(rt, deltaX, deltaY); }

inline void OffsetSysRect(SysRect& rt, SysCoord deltaX, SysCoord deltaY)
	{ rt = MTOOLBOX::CGRectOffset(rt, deltaX, deltaY); }

inline void SysRectMakeZeroOrigin(SysRect& rt)
	{ rt = MTOOLBOX::CGRectOffset(rt, -rt.origin.x, -rt.origin.y); }


//===    SysRgn     ========================

inline SysRgn CreateSysRgn()
	{ return MTOOLBOX::HIShapeCreateMutable(); }

inline void DeleteSysRgn(ConstSysRgn sysRgn)
	{ MTOOLBOX::CFRelease (sysRgn); }
	
inline SysRgn CopySysRgn(ConstSysRgn sysRgn)
	{ return MTOOLBOX::HIShapeCreateMutableCopy(sysRgn); }

inline void CopySysRgn(ConstSysRgn srcRgn, SysRgn dstRgn)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeSetWithShape(dstRgn, srcRgn);;
	ASSERT_MSG(err == noErr, "HIShapeSetWithShape failed!");
}

inline SysRgn CreateRectSysRgn (const SysRect& sysRect)
	{ return MTOOLBOX::HIShapeCreateMutableWithRect(&sysRect); }

inline bool16 SysPointInSysRgn( const SysPoint& p, ConstSysRgn rgn)
{ 
	if(rgn)
		return MTOOLBOX::HIShapeContainsPoint(rgn, &p);
	else
		return kFalse;
}

inline bool16 SysRectIntersectsSysRgn(ConstSysRgn rgn, const SysRect *rect)
{
	if(rgn)
	{
		return MTOOLBOX::HIShapeIntersectsRect(rgn, rect);
	}
	else
		return kFalse;
}

#define RectInSysRgn(rgn, rect)		SysRectIntersectsSysRgn(rgn, rect)

inline bool16 EqualSysRgn(ConstSysRgn rgn1, ConstSysRgn rgn2)
{
	if (MTOOLBOX::HIShapeIsEmpty(rgn1))
	{
		if (MTOOLBOX::HIShapeIsEmpty(rgn2))
			return kTrue;
		else
			return kFalse;
	}
	else if (MTOOLBOX::HIShapeIsEmpty(rgn2))
	{
		return kFalse;
	}
	
	
	HIShapeRef diffShape = MTOOLBOX::HIShapeCreateDifference(rgn1, rgn2);
	bool16 result = MTOOLBOX::HIShapeIsEmpty(diffShape);
	MTOOLBOX::CFRelease(diffShape);
	return result;  	 
}

inline void UnionSysRgn(ConstSysRgn srcRgn1, ConstSysRgn srcRgn2, SysRgn destRgn)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeUnion(srcRgn1, srcRgn2, destRgn);
	ASSERT_MSG(err == noErr, "HIShapeUnion failed!");
}
	
inline void DiffSysRgn(ConstSysRgn srcRgn, ConstSysRgn removeRgn, SysRgn destRgn)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeDifference(srcRgn, removeRgn, destRgn); 
	ASSERT_MSG(err == noErr, "HIShapeDifference failed!");
}
	
inline void IntersectSysRgn(ConstSysRgn srcRgn1, ConstSysRgn srcRgn2, SysRgn destRgn)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeIntersect (srcRgn1, srcRgn2, destRgn); 
	ASSERT_MSG(err == noErr, "HIShapeIntersect failed!");
}
	
inline bool16 EmptySysRgn(ConstSysRgn theRgn)
	{ return (MTOOLBOX::HIShapeIsEmpty(theRgn) == true); }

inline void XorSysRgn(ConstSysRgn srcRgn1, ConstSysRgn srcRgn2, SysRgn destRgn)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeXor(srcRgn1, srcRgn2, destRgn); 
	ASSERT_MSG(err == noErr, "HIShapeXor failed!");
}

inline void OffsetSysRgn(SysRgn rgn, SysCoord deltaX, SysCoord deltaY)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeOffset (rgn, deltaX, deltaY); 
	ASSERT_MSG(err == noErr, "HIShapeOffset failed!");
}

inline void InsetSysRgn(SysRgn rgn, SysCoord deltaX, SysCoord deltaY)
{
#if defined(ID_ENABLE_DEBUGGING)
	OSStatus err = 
#endif
	MTOOLBOX::HIShapeInset (rgn, deltaX, deltaY); 
	ASSERT_MSG(err == noErr, "HIShapeInset failed!");
}

//===    SysWireframe     ========================
inline SysRect GetRegionRect( SysWireframe rgn )
	{ return ::GetRegionRect((ConstSysRgn) rgn); }
inline SysWireframe CreateSysWireframe()
	{ return ::CreateSysRgn(); }

inline SysWireframe CreateRectSysWireframe (SysRect sysRect)
	{ return ::CreateRectSysRgn(sysRect); }

inline void DeleteSysWireframe(SysWireframe sysRgn)
	{ ::DeleteSysRgn(sysRgn); }

inline SysWireframe CopySysWireframe(SysWireframe sysRgn)
	{ return ::CopySysRgn(sysRgn); }

inline void CopySysWireframe(SysWireframe srcRgn, SysWireframe dstRgn)
	{ ::CopySysRgn(srcRgn, dstRgn); }

inline void OffsetSysWireframe(SysWireframe rgn, int32 deltaX, int32 deltaY)
	{ ::OffsetSysRgn(rgn, deltaX, deltaY); }

inline void InsetSysWireframe(SysWireframe rgn, int32 deltaX, int32 deltaY)
	{ ::InsetSysRgn(rgn, deltaX, deltaY); }

inline void UnionSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
	{ ::UnionSysRgn(srcRgn1, srcRgn2, destRgn); }
	
inline void DiffSysWireframe(SysWireframe srcRgn, SysWireframe removeRgn, SysWireframe destRgn)
	{ ::DiffSysRgn(srcRgn, removeRgn, destRgn); }
	
inline void IntersectSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
	{ ::IntersectSysRgn(srcRgn1, srcRgn2, destRgn); }
	
inline void XorSysWireframe(SysWireframe srcRgn1, SysWireframe srcRgn2, SysWireframe destRgn)
	{ ::XorSysRgn(srcRgn1, srcRgn2, destRgn); }

//===    MISC     ========================

PUBLIC_DECL SysPoint GetMousePosition();

inline SysRect operator-(const SysRect& rt1, const SysRect& rt2)
{
	SysRect result;
	
	result.origin.x = rt1.origin.x - rt2.origin.x;
	result.origin.y = rt1.origin.y - rt2.origin.y;
	result.size.width = rt1.size.width - rt2.size.width;
	result.size.height = rt1.size.height - rt2.size.height;
	
	return result;
}

inline SysRect operator+(const SysRect& rt1, const SysRect& rt2)
{
	SysRect result;
	
	result.origin.x = rt1.origin.x + rt2.origin.x;
	result.origin.y = rt1.origin.y + rt2.origin.y;
	result.size.width = rt1.size.width + rt2.size.width;
	result.size.height = rt1.size.height + rt2.size.height;
	
	return result;
}



//PUBLIC_DECL void EraseSysRect(SysPort port, const SysRect *theRect);
//PUBLIC_DECL void EraseSysRgn(SysPort port, const SysRgn theRgn);

//PUBLIC_DECL QDRgn	GetAvailableWindowPositioningRegion(void);
		
PUBLIC_DECL Boolean	IsFrontProcess(void);

	
inline uint32 GetCaretTime()
{
	// GetCaretTime is not supported in 64 bit applications and is obsolete in regular 32 bit os x. Replacing with it's default
	// return value of 34. There is still a windows version we use in WSystemUtils.h.
	return 34;
}

namespace SystemUtils
{
    PUBLIC_DECL uint32 TickCount();
    PUBLIC_DECL uint64 Milliseconds();
    PUBLIC_DECL uint64 Microseconds(); 
}

#endif
		// __MSystemUtils__
