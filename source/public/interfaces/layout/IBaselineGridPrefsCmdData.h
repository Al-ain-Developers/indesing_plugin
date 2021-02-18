//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBaselineGridPrefsCmdData.h $
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
//  
//  Data interface for BaselineGrid prefs commands.
//  includes : 	BaselineGrids drawn in front or back, shown or hidden,
//  intervals between each baseline grid line,
//  offset from top of page, and view limit percentage.
//  
//========================================================================================

#pragma once
#ifndef __IBaselineGridPrefsCmdData__
#define __IBaselineGridPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMReal.h"
#include "IBaselineGridPrefs.h"

class IDataBase;




class IBaselineGridPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBASELINEGRIDPREFSCMDDATA };

	virtual void Set(	const	UIDRef&	gridPrefs, 			/* which document or story grid prefs to affect */
								bool16	shown,		 	/* BaselineGrids shown or hidden */
								PMReal	division,		/* Interval between main BaselineGridlines */
								PMReal	start,			/* Offset from top of page */
								PMReal	viewLimit,		/* View percentage limit */
							    UID	colorUID = kInvalidUID) = 0;
	virtual	UIDRef GetDocument() const = 0;
	virtual	UIDRef GetGridPrefs() const = 0;
	virtual bool16 GetBaselineGridShown() const = 0;
	virtual PMReal GetBaselineGridDivision() const = 0;
	virtual PMReal GetBaselineGridStart() const = 0;
	virtual PMReal GetBaselineGridViewLimit() const = 0;
	virtual UID GetBaselineGridColorUID() const = 0;

	virtual void SetBaselineGridRelativeOption(const IBaselineGridPrefs::BaselineGridRelativeOption relativeOption) = 0;
	virtual IBaselineGridPrefs::BaselineGridRelativeOption GetBaselineGridRelativeOption() const = 0;
};


#endif // __IBaselineGridPrefsCmdData__
