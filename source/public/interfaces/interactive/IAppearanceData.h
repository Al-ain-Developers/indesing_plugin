//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAppearanceData.h $
//  
//  Owner: Tim Wright
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
#ifndef __IAppearanceData__
#define __IAppearanceData__

#include "IPMUnknown.h"
#include "FormFieldID.h"
#include "FormFieldTypes.h"

/** Used as a parameter interface for command bosses that
    take appearance parameters as input or output.
    @see kChangeStateCmdBoss
*/
class IAppearanceData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IAPPEARANCEDATA };
		
		typedef Form::Appearance		ValueType;

	/** Set parameters for the appearance (use kChangeStateCmdBoss, IHierarchy related
		commands to change the child page items for the appearance */
	virtual void Set(const Form::Appearance& inAppearance) = 0;

	/** Get parameters for the appearance (use kChangeStateCmdBoss, IHierarchy related
		commands to get the child page items for the appearance */
	virtual void GetAppearance(Form::Appearance* outAppearance) const = 0;
};



#endif // __IAppearanceData__
