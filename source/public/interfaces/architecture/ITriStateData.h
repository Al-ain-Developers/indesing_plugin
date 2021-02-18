//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITriStateData.h $
//  
//  Owner: robin briggs
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
#ifndef __ITriStateData__
#define __ITriStateData__

#include "IPMUnknown.h"
#include "ShuksanID.h"

/** 	Data interface for storing a value that can be in one of three states. There is a similar interface used for widgets with
	three possible states. @see ITriStateControlData
	@ingroup arch_coredata 
*/
class ITriStateData : public IPMUnknown
{
	public:
		enum	{ kDefaultIID = IID_ITRISTATEDATA };
		typedef enum { kUnselected, kUnknown, kSelected } TriState;

	/** 	Set the new state */
	virtual void		Set(TriState newState) = 0;

	/** 	Check if the state is currently kSelected */
	virtual bool16		IsSelected() = 0;

	/** 	Check if the state is currently kUnselected */
	virtual bool16		IsDeselected() = 0;

	/** 	Check if the state is currently kUnknown */
	virtual bool16		IsUnknown() = 0;

	/** 	Get the current state */
	virtual TriState	GetState() = 0;
};

#endif