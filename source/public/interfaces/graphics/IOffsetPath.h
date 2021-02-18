//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IOffsetPath.h $
//  
//  Owner: jargast
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
#ifndef __IOffsetPath__
#define __IOffsetPath__

#include "IPMUnknown.h"
#include "GraphicTypes.h"
#include "OffsetPathID.h"

class IPathGeometry;
class IOutlineInfo;
class PMReal;

/** Interface for outsetting (i.e., negative inset) a path
*/
class IOffsetPath : public IPMUnknown
{
public:
	/** default IID for this interface 
	*/
	enum { kDefaultIID = IID_IOFFSETPATH };

	/** Offset strategy
	*/
	enum OffsetStyle
	{
		/** old functionality: closes path and offsets hull
		*/
		kOffsetArea,
		/** offsets stroke, without closing path
		*/
		kOffsetPath
	};
	
	/** Offsets the path by nOffset amount. Will union the paths if bUnionPaths is true
		can specify join type, line cap, and miter limit directly.
		@param pathData - IN: source path
		@param offsetPath - OUT: destination path
		@param amount - IN: non-zero amount to offset
		@param style - IN: offset style
		@param joinType - IN: join type
		@param lineCap - IN: linecap
		@param miterLimit - IN: miter limit
		@param unionPaths - IN: Should paths be unioned
		@return ErrorCode.  kSuccess indicates no error.
	*/
	virtual ErrorCode OffsetPath(
		IPathGeometry const *pathData,		// source
		IOutlineInfo *offsetPath,			// destination
		PMReal const &amount,				// amount to offset (shouldn't be zero)
		OffsetStyle style = kOffsetArea,	// style (see enum above)
		int32 joinType = kPMRoundJoin,		// join type
		int32 lineCap = kPMButtCap,			// linecap
		PMReal const &miterLimit = 1.0,		// miter limit
		bool16 unionPaths = kTrue			// should paths be unioned
	) const = 0;
			
};

#endif
