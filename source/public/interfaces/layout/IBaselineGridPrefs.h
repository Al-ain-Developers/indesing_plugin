//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBaselineGridPrefs.h $
//  
//  Owner: psorrick
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
#ifndef __IBaselineGridPrefs__
#define __IBaselineGridPrefs__

#define kMinBaselineStart		0
#define kMaxBaselineStart		1000 
#define kMinBaselineDivision	1
#define kMaxBaselineDivision	8640
#define kMinBaselineViewLimit	5
#define kMaxBaselineViewLimit	4000

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "SpreadID.h"

class IBaselineGridPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IBASELINEGRIDPREFERENCES };

	////
	//// BaselineGrid Preferences
	////
	
	typedef enum { kRelativeToTopOfPage, kRelativeToTopOfMargin } BaselineGridRelativeOption;

	// Is BaselineGrid shown or hidden by default
	virtual void SetBaselineGridShown(bool16 bShown) = 0;
	virtual bool16 GetBaselineGridShown() const = 0;

	// BaselineGrid division
	virtual void SetBaselineGridDivision(const PMReal& division) = 0;
	virtual PMReal GetBaselineGridDivision() const = 0;

	// BaselineGrid start (offset from top of page)
	virtual void SetBaselineGridStart(const PMReal& start) = 0;
	virtual PMReal GetBaselineGridStart() const = 0;

	// BaselineGrid relative to options
	virtual void SetBaselineGridRelativeOption(const IBaselineGridPrefs::BaselineGridRelativeOption& relativeOption) = 0;
	virtual IBaselineGridPrefs::BaselineGridRelativeOption GetBaselineGridRelativeOption() const = 0;

	// BaselineGrid view percentage limit
	virtual void SetBaselineGridViewLimit(const PMReal& limit) = 0;
	virtual PMReal GetBaselineGridViewLimit() const = 0;
	
	virtual void SetBaselineGridColor(UID uiColorUID) = 0;
	virtual UIDRef GetBaselineGridColor() const = 0;

	/** Internal  method used to convert baseline grid show setting. Please do not call!
	*/
	virtual bool16 GetBaselineGridShown_DURING_CONVERSION_ONLY() const = 0;

	/** Internal  method used to convert baseline grid color setting. Please do not call!
	*/
	virtual int32 GetBaselineGridColorIndex_DURING_CONVERSION_ONLY() const = 0;
};
#endif

#endif
