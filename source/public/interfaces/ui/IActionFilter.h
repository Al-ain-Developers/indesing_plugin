//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IActionFilter.h $
//  
//  Owner: lance bushore
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
#ifndef __IActionFilter__
#define __IActionFilter__

#include "IPMUnknown.h"
#include "ActionID.h"

/** This Interface allows plugin writers to change behavior of existing actions at the time they are added. Typically this is used to either remove menu items completely(in conjunction with an IMenuFilter)
	or to replace the default implementation of some action(i.e. you have a plugin which wants to do something different when the user chooses File:Open).
	To get your	action filter implementation called, you must put it on a boss that supports kActionFilterService, like so:
	Class
	{
		kXXXActionFilterBoss,
		kInvalidClass,
		{
			IID_IK2SERVICEPROVIDER,		kActionFilterProviderImpl,
			IID_IACTIONFILTER,			kXXXActionFilterImpl,
			IID_IPMPERSIST,				kPMPersistImpl,
		}
	};

*/
class IActionFilter : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IACTIONFILTER };

	/** Any call to IActionManager::AddAction will call all action filters to allow them to change anything about the action being added.
		@param componentClass This is a pointer to the action component class to be used to handle this action. The action filter is free to change this to some other action component class
		@param actionID This is a pointer to the ActionID. The action filter is free to change this to some other ActionID. If it's changed to kInvalidActionID the action will not be added.
		@param actionName This is a pointer to the name of the action. This is the name that appears in the menu or in the shortcut editor describing the action. The action filter is free to change this to a different string.
		@param actionArea This is a pointer to the area of the action. This is the string that appears as the grouping in the shortcut editor. The action filter is free to change this to a different string.
		@param actionType This is a pointer to the type of the action. Usually kNormalAction, but could also be kPreNotify or kPostNotify(see ActionDefs.h). The action filter is free to change this to some other action type.
		@param enablingType This is a pointer to the enabling bitfield for this action(see ActionDefs.h). Often something like (kCustomEnabling|kDisableIfLowMem). The action filter is free to change this bitfield to alter the enabling for this action.
		@param userEditable This is a pointer to the user editable flag. If this flag is true this action will show up in the shortcut editor. The action filter is free to change this boolean.
	*/
		virtual void	FilterAction(ClassID* componentClass, ActionID *actionID,	PMString* actionName,
									 PMString* actionArea, int16* actionType, uint32* enablingType, bool16* userEditable)= 0;		
};

#endif // __IActionFilter__
		