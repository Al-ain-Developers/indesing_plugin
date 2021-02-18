//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionalTextOptions.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __IConditionalTextOptions__
#define __IConditionalTextOptions__

#include "IPMUnknown.h"
#include "ConditionalTextID.h"

/**	
	IConditionalTextPrefs is an interface used to set the prefs that control the behavior of conditional text.
*/
class IConditionalTextOptions : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ICONDITIONALTEXTOPTIONS };
	
	/**
	Enum for specifying mode for condition indicators.
	*/
	enum ConditionIndicatorsMode 
	{
		/** Condition indicators show. */
		kShow = 0,
		/** Condition indicators show and print. */
		kShowAndPrint,
		/** Condition indicators hide. */
		kHide,
	};

	/**	
		Set the conditional text indicators show mode.
		@param showIndicatorsMode IN The show mode for conditional text indicators.
	 */
	virtual void SetShowConditionIndicators(ConditionIndicatorsMode showIndicatorsMode) = 0;
	
	/**	
		Get the conditional text indicators show mode.
		@return ConditionIndicatorsMode The show mode for conditional text indicators.
	 */
	virtual ConditionIndicatorsMode GetShowConditionIndicators() const = 0;
	
	/**	
		Set the active condition set. It's preferable to use the method in IConditionalTextFacade::SetActiveTagSet to do this which instead of calling this
		routine directly. The facade will fire the right command and update the UI properly this will do none of that.
		@param conditionSetUID IN UID of condition set to make active, may be kInvalidUID if no set is desired to be active
	 */
	virtual void SetActiveConditionSet(UID conditionSetUID) = 0;
	
	/**	
		Get the active condition set UID. It's preferable to use the method IConditionalTextFacade::GetActiveTagSet instead of calling this routine.
		@return UID of the active condition set, will be kInvalidUID if no set is active
	 */	
	virtual UID GetActiveConditionSet() const = 0;
};

#endif // __IConditionalTextOptions__
