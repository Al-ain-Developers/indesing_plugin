//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IBehaviorData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IBehaviorData_h__
#define __IBehaviorData_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"

/** Base data interface for all behavior bosses
	Each behavior has an interface that inherits from this interface
	that contains methods to access the parameters specific to that behavior
	@see IBehaviorList, IMovieActionData 
*/
class IBehaviorData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIORDATA };

	// ---- Static properties of actions. i.e. They cant' be changed once the action
	//		is created.
	
	/** Get an unique enumeration, a PMID in kBehaviorIDSpace, for this behavior */
	virtual int32		GetAction() const = 0;

	/** Get a human readable name for the behavior  */
	virtual PMString	GetName() const = 0;

	// ---- Dyncamic properties of actions.
	
	/** Get the UID of the boss to which this behavior belongs.
		Typically, a behavior boss belongs to an IBehaviorList interface which
		is an event/behavior list map. IBehaviorLists are interfaces on Form Field
		and Document bosses, for instance.  So this would return the UID of a form
		field or document.
	*/
	virtual UID			GetOwner() const = 0;
	
	/** Set the owner of the boss that this behavior belongs to
		@param owner UID of boss that owns the behavior */
	virtual void		SetOwner(const UID& owner) = 0;
	
	/** Return if this behavior is enabled, that is whether it should be exported
	    in the output PDF */
	virtual bool16		IsEnabled() const = 0;
	
	/** Enable or Disable this behavior, that is whether it should be exported
	    in the output PDF */
	virtual bool16		Enable(const bool16& enable = kTrue) = 0;
	bool16				IsDisabled() const { return !IsEnabled(); }
	bool16				Disable() { return Enable(kFalse); }
	
	/** Copy parameters from one IBehaviorData interface to another.
		@param srcData, this should be an IBehaviorData interface matching this one.
				That is if you call Copy on an IMovieActionData interface, srcData
				should be an IMovieActionData interface as well. */
	virtual void		Copy(IPMUnknown* srcData) = 0;
};

#endif // __IBehaviorData_h__
