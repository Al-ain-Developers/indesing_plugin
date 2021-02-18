//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextInset.h $
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
//  
//  Sets the inset of a drawable pageitem.
//  See TextInset.cpp, SetTextInsetCmd.cpp, SpreadOverlapManager.cpp
//  
//========================================================================================

#pragma once
#ifndef __ITextInset__
#define __ITextInset__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "StandOffID.h"

class IGeometry;
class IStandOff;
class PMRect;

/** 
	@ingroup text_wrap
*/
class ITextInset : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTINSET };

	enum InsetFlags
	{
		kLeft	= 1,
		kTop	= 2,
		kRight	= 4,
		kBottom	= 8
	};

	/**
	nInset specifies the distance between this pageitem and the textframe that is a child of this pageitem.
	*/
	virtual void 			SetInset(PMReal nInset) = 0;

	/**
	returns the inset value. Notice that QueryInsetGeometry() and GetInset()
	are independent. You could get an inset geometry even if the inset value
	was 0.0.
	*/
	virtual PMReal 			GetInset() const = 0;

	/**
	*/
	virtual bool16 			SetRectInset(const PMRect &insetRect) = 0;

	/**
	*/
	virtual PMRect			GetRectInset() const = 0;

	/**
	Returns the effective inset given the rectangle/non-rectangle shape of
	the Spline. If a rectangle, returns GetRectInset(), otherwise returns
	GetInset() for all sides.
	*/
	virtual PMRect			GetEffectiveInset() const = 0;

	/**
	expects the UID of the standoff pageitem. This is called by TextInset::DoRecalcInset().
	*/
	virtual void			SetInsetGeometry(UID nInsetGeo) = 0;

	/**
	returns nil or the inset geometry. Notice that QueryInsetGeometry() and GetInset()/GetInsetGeometry() are independent.
	You could get an inset geometry even if the inset value was 0.0.		
	*/
	virtual IGeometry *		QueryInsetGeometry() const = 0;

	/**
	Updates the InsetGeometry
	recalculates the inset geometry.
	@param bDynamic ignored/obsolete
	@return kTrue (always)
	*/
	virtual bool16			UpdateInsetGeometry(bool16 bDynamic = kFalse) = 0;		
	/**
	returns the UID of the inset. Notice that QueryInsetGeometry() and GetInsetGeometry() are independend.
	QueryInsetGeometry() returns nil if the pageitem is a rectangle and the inset values are 0.
	TextInset::Do() calls GetInsetGeometry() to see whether an inset item needs to be created.
	*/
	virtual UID				GetInsetGeometry() const = 0;

};

#endif
