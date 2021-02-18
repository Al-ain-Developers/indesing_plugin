//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxFlattenerUsage.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IAdornmentFlattenerUsage.h"
#include "IShape.h"

// Project includes:
#include "TranFxID.h"

/** Reports whether given its current settings the adornment
	is or isn't using transparency. In our case if the adornmeent
	is attached to a a page item transparency is present.

	
	@ingroup transparencyeffect
 */
class TranFxFlattenerUsage : public CPMUnknown<IAdornmentFlattenerUsage>
{
public:
	/** Constructor.
		@param boss
	*/
	TranFxFlattenerUsage(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~TranFxFlattenerUsage();    

	/**	Reports whether given its current settings the adornment
		is or isn't using transparency.
		@param iThing page item that owns the adornment.
		@param transform
		@param nFlags
		@return kTrue if adornment is adding transparency, kFalse otherwise.
	*/
	virtual bool32 IsFlattenerRequired_(IPMUnknown* iThing, const PMMatrix*, int32);

};

/*
*/
CREATE_PMINTERFACE(TranFxFlattenerUsage, kTranFxFlattenerUsageImpl)

/*
*/
TranFxFlattenerUsage::TranFxFlattenerUsage(IPMUnknown* boss) : CPMUnknown<IAdornmentFlattenerUsage>(boss)
{
}

/*
*/
TranFxFlattenerUsage::~TranFxFlattenerUsage()	
{
}

/*	If you add/remove the adornment when you add/remove transparency, 
	then returning kTrue works fine. But maybe you have other settings, 
	only certain values of which will cause the transparency effect to be present. 
	In that case your implementation would need to look at those 
	settings to determine whether there really is transparency present.
*/
bool32 TranFxFlattenerUsage::IsFlattenerRequired_(IPMUnknown* iThing, const PMMatrix*, int32)
{
	// Our adornment is owned by a page item (otherwise we would not be called),
	// so assume transparency is present.
	bool32 result = kTrue;
	return result;
}

// End, TranFxFlattenerUsage.cpp.
