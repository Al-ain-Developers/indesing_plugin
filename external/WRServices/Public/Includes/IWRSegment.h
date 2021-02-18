//========================================================================================
//  
//  File: IWRSegment.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRSEGMENT__
#define __IWRSEGMENT__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRExtensionAttributeList.h"
#include "WROptycaStage.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Interface to access segments
/**
This interface exposes the segment objects to the outside, especially external modules
A segment is a section of the strike array which is managed by an external module. 
A segment is always in a definite "stage", which accounts for the degree of processing 
already completed.
The x-position is the start position of the segment at the time individual positions of the
segment strikes were computed. When the segment is moved, the delta is propagarted to all strikes
in the segment.
The segment also knows how meny chars and how many corresponding strikes it contains.
Another intersting aspect of the segment is its ability to store in a IWRExtensionAttributeList
the private attributes (actually any data) the external module needs to associate to the segment.
@sa OptycaSegment, SegmentBuffer, IWRSegmentBuffer, IWRExtensionAttributeList
**/

class WRSERVICES_DECL IWRSegment
{
public:
#ifndef WR_WIN_ENV
	virtual	~IWRSegment(); // gcc needs it even in abstract classes
#endif

	virtual OptycaStage GetStage(void) const = 0;	///< get the processing stage
	virtual void SetStage(OptycaStage s) = 0;		///< set the processing stage
	virtual WRFloat GetXPosition(void) const = 0;	///< get the horizontal start position
	virtual void SetXPosition(WRFloat p) = 0;		///< set the horizontal start position
	virtual WRFloat GetWidth(void) const  = 0;		///< get the segment width
	virtual void SetWidth(WRFloat w)  = 0;			///< set the segment width
	virtual WRInt32 GetCharStart(void) const = 0;	///< get the segment char count
	virtual void SetCharStart(WRInt32 c) = 0;		///< set the segment char count
	virtual WRInt32 GetCharCount(void) const = 0;	///< get the segment char count
	virtual void SetCharCount(WRInt32 c) = 0;		///< set the segment char count
	virtual WRInt32 GetGlyphCount(void) const = 0;	///< get the segment strike count
	virtual void SetGlyphCount(WRInt32 c) = 0;		///< set the segment strike count
	/// append text to the end of a segment
	/** 
	this method is used by external shapers to increase the char and strike counts, as well as the graphical width.
	It doesn't update the segment index in the strike records
	@param cc a WRInt32, char count
	@param gc a WRInt32, strike count
	@param w a WRFlat, width of the added strikes
	**/
	virtual void Append(WRInt32 cc, WRInt32 gc, WRFloat w) = 0;
	virtual IWRExtensionAttributeList* GetExtensionAttributeList(void) = 0; ///< get a pointer to the attributes belonging to the external module
protected:
};


#endif
