//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStandOff.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IStandOff__
#define __IStandOff__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "StandOffID.h"			// IsStandOff
#include "PMMatrix.h"
#include "CTextEnum.h"
#include "IParcel.h"
#include "ITextFrameColumn.h"
#include "ITextParcelList.h"
#include "ITextStoryThread.h"

class IGeometry;
class ITransform;


//---------------------------------------------------------------
// class IStandOff
//---------------------------------------------------------------

/**
	Holds the standoff information which is used to cause text
	in text frames to wrap around the "standoffs of pageitems".
	@ingroup text_wrap
*/
class IStandOff : public IPMUnknown
{
public:
	/**
	StandOff's default IID.
    */
	enum { kDefaultIID = IID_ISTANDOFF };

	/**
	StandOff mode.
    */
	enum mode
	{
		/** no effect on text */
		kNone			= 0,

		/** text leads past area of strip */
		kBand			= 1,

		/** text continues in next column, aka jump wrap */
		kNextFrame 		= 2,

		/** text on follows the bounding box of the shape (PM) */
		kBoundingBox	= 3,

#ifdef ID_DEPRECATED
		kBothSides 		= kBoundingBox,

		/** text within holes in object */
		kWithinHoles	= 4, 	// Invalid, unimplemented

		/** text follows the shape (implies kBothSides) */
		kAutoContour	= 5,	// Invalid, unimplemented
#endif
		/** text follows the standoff shape	*/
		kManualContour	= 6,

#ifdef ID_DEPRECATED
		/** text wraps only to the left side of the standoff. */
		kLeftContour	= 7,	// Invalid, unimplemented

		/** text wraps only to the right side of the standoff. */
		kRightContour	= 8,	// Invalid, unimplemented

#endif
		/** default StandOff mode */
		kDefaultMode = kNone
	};

	/**
	StandOff form.
    */
	enum form
	{
		/** the shape of the StandOff */
		kRegular,

		/** dintrusions become extrusions */
		kInvert,

		/** default StandOff form */
		kDefaultForm = kRegular
	};

	/**
	StandOff side. Valid with non-kInvert kBoundingBox and kManualContour
	*/
	enum side
	{
		/** both sides of the StandOff */
		kBoth,

		/** left side of the StandOff */
		kLeft,

		/** right side of the StandOff */
		kRight,

		/** side closest to binding */
		kToBinding,

		/** side farthest from binding */
		kAwayBinding,

		/** the largest piece. may not actually be a side */
		kLargest,

		/** default StandOff form */
		kDefaultSide = kBoth

	};

	/** This returns the bounding box of the StandOff's geometry
	@param pRect is assigned to bounding box of the standoff's geometry.
	*/
	virtual void		GetBounds( PBPMRect *pRect ) const = 0;

	/** The StandOff itself has a IGeometry which is different from the pageitem's geometry
	@return the IGeometry interface of the StandOff.
	*/
	virtual IGeometry *QueryStandOffGeometry() const = 0;

/** If the geometry of the pageitem changes then the the StandOff's geometry has to be adapted.
	@return kTrue if StandOff was updated.
	*/
	virtual bool16		UpdateStandOffGeometry() = 0;

	/** called by MainItemObserver on kDeletePageItemCmdBoss, returns always 0
	@return always nil.
	*/
	virtual IGeometry *DeleteStandOff() = 0;

	/** IgnoreUpdateStandOffGeometryCalls provides a mechanism for ignoring updates while doing something such as document conversion.
		Be careful when using this method because it will prevent the composition engine from being notified that
		anything has changed.
		@param bIgnore [IN]: if true, calls to UpdateStandOffGeometry will become noops until this method is called
			with 'false'
	*/
	virtual void IgnoreUpdateStandOffGeometryCalls(bool bIgnore) = 0;
};

DECLARE_BASE_TYPE(IStandOff::form);
DECLARE_BASE_TYPE(IStandOff::mode);
DECLARE_BASE_TYPE(IStandOff::side);

#endif
	//	__IStandOff__

