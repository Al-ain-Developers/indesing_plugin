//========================================================================================
//  
//  File: IWRSegmentBuffer.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __ISegmentBuffer__
#define __ISegmentBuffer__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRSegment.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Interface to a segment buffer
/**
This class exposes optyca's segment buffer object. 
@sa IWRSegment, OptycaSegment, SegmentBuffer
**/

class WRSERVICES_DECL IWRSegmentBuffer
{
public:
#ifndef WR_WIN_ENV
	virtual				~IWRSegmentBuffer() {} // gcc needs it even in abstract classes
#endif
	virtual IWRSegment&	GetSegment(WRInt32 i) = 0; ///< get the i-th segment
	virtual WRInt32		Size(void) const = 0; ///< number of segments
	virtual void		Remove(WRInt32 start, WRInt32 count = 1) = 0; ///< update a segment after strike removal
	virtual WRError		Insert(IWRSegment* item, WRInt32 start, WRInt32 count = 1) = 0; ///< update a segment after strike add
	virtual IWRSegment* AppendNew(WRInt32& index) = 0; ///< create a new segment at the end of the buffer
};

#endif
