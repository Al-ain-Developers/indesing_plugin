//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlaceBehaviorSignalData.h $
//  
//  Owner: Jonathan W. Brown
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __IPlaceBehaviorSignalData_h__
#define __IPlaceBehaviorSignalData_h__

#include "IPMUnknown.h"

#include "OpenPlaceID.h"

class IPlaceBehavior ;

/**
	Data interface for Place Behaviors to use when signaling responders.
	@see IPlaceBehavior.h
*/
class IPlaceBehaviorSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPLACEBEHAVIORSIGNALDATA } ;

	/** Initialize */
	virtual void			Init( IPlaceBehavior* source, IPlaceBehavior* target, const UIDList& result ) = 0 ;

	/** Get the source */
	virtual IPlaceBehavior*	GetSource() const = 0 ;

	/** Get the target; may be nil (e.g., for a snippet) */
	virtual IPlaceBehavior*	GetTarget() const = 0 ;

	/** Get the result; will be kInvalidUIDRef for a before place signal */
	virtual UIDList			GetResult() const = 0 ;
};

#endif // __IPlaceBehaviorSignalData_h__
