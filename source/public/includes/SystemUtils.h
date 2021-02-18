//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SystemUtils.h $
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
#ifndef __SystemUtils__
#define __SystemUtils__
 
#ifndef __PMTYPES__
#include "PMTypes.h"
#endif

#ifdef MACINTOSH
#include "MSystemUtils.h"
#endif
 
#ifdef WINDOWS
#include "WSystemUtils.h"
#endif

#pragma export on

PUBLIC_DECL void SetRect(SysRect *r, SysPoint p1, SysPoint p2);
	// Create a rectangle out of two points. Rectangle
	// is "normalized" to reorder the points.	


PUBLIC_DECL void K2ReadWriteSysRect(IPMStream *s, SysRect& rt);

PUBLIC_DECL void SystemBeep(void);

//  ----- Some convenient inlines for double numbers.

#pragma export off

inline bool16 operator==(const SysPoint& pt1, const SysPoint& pt2)
	{ return SysPointH(pt1) == SysPointH(pt2) && SysPointV(pt1) == SysPointV(pt2); }

inline bool16 operator!=(const SysPoint& pt1, const SysPoint& pt2)
	{ return SysPointH(pt1) != SysPointH(pt2) || SysPointV(pt1) != SysPointV(pt2); }

inline SysPoint operator-(const SysPoint& pt1, const SysPoint& pt2)
{
	SysPoint result;
	
	SysPointH(result) = SysPointH(pt1) - SysPointH(pt2);
	SysPointV(result) = SysPointV(pt1) - SysPointV(pt2);
	
	return result;
}

inline SysPoint operator+(const SysPoint& pt1, const SysPoint& pt2)
{
	SysPoint result;
	
	SysPointH(result) = SysPointH(pt1) + SysPointH(pt2);
	SysPointV(result) = SysPointV(pt1) + SysPointV(pt2);
	
	return result;
}

inline void SysRectOffset( SysRect& rect, int32 dx, int32 dy )
{
	::OffsetSysRect(rect, dx, dy);
}

// Stack based utility for managing deletion of SysRgn
class AutoSysRgn
{
	
public:
	AutoSysRgn()
		{
			fSysRgn = NULL;
		}
	
	explicit AutoSysRgn(const SysRgn& value)
		{
			fSysRgn = value;
		}
	
	/// Destructor
	~AutoSysRgn()
		{
			if (fSysRgn)
				::DeleteSysRgn(fSysRgn);
		}
	
	/// Change the object referenced
	void Reset(SysRgn value = NULL)
		{
			if (value != fSysRgn)
			{
				if (fSysRgn)
					::DeleteSysRgn(fSysRgn);
				fSysRgn = value;
			}
		}
	
	/// Return true if no object referenced.
	bool IsNull() const
		{
			return fSysRgn == NULL;
		}
	
	const SysRgn& operator*() const
		{
			return fSysRgn;
		}

	SysRgn& operator*()
		{
			return fSysRgn;
		}

private:
	SysRgn			fSysRgn;
};


#endif
		// __SystemUtils__
