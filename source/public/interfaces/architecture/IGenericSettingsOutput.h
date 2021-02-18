//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGenericSettingsOutput.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  Allows GenericSettings objects to be visited in different ways.
//  
//========================================================================================

#pragma once
#ifndef __IGenericSettingsOutputStrategy__
#define __IGenericSettingsOutputStrategy__

#include "IPMUnknown.h"
#include "IGenericSettingsGroup.h"
#include "IPMUnknownIterator.h"
#include "GenericSettingsID.h"
class IGenericSettings;

/** Format all the preferences of a preset.
	You implement this interface and pass it to IGenericSetting::WriteTo method.
	See ISummaryUtils::GenerateHumanTextSummary.

	The methods are called in the order the preferences and groups were added to 
	the IGenericSettings interface.
*/
class IGenericSettingsOutputStrategy: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERICSETTINGSOUTPUTSTRATEGY };

public:
	/** Get the formatted results as one big string.
		@return the formatted string.
	*/
	virtual const PMString& GetResult() = 0;

public:
	/** This is called at the beginning.
		@param pSettings is a pointer to the preset settings being formatted.
	*/
	virtual void StartSettings(   IGenericSettings* pSettings )      = 0;

	/** This is called at the end.
		@param pSettings is a pointer to the preset settings being formatted.
	*/
	virtual void FinishSettings(  IGenericSettings* pSettings )      = 0;

	/** This is called at the beginning of a group.
		@param pGroup is a pointer to the group settings being formatted.
	*/
	virtual void StartGroup( IGenericSettingsGroup*  pGroup )        = 0;

	/** This is called at the end of a group.
		@param pGroup is a pointer to the group settings being formatted.
	*/
	virtual void FinishGroup( IGenericSettingsGroup* pGroup )        = 0;

	/** This is called to format one preset.
		@param pAttr is a pointer to the preference to format.
	*/
	virtual void RecordAttribute( IGenericSettingsAttribute* pAttr ) = 0;
};


#endif 
