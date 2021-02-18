//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ICommandFactory.h $
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

#ifndef __ICommandFactory_h__
#define __ICommandFactory_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"

class ICommand;

/**
	Creates commands to manipulate behaviors.
	There is a corresponding ICommandFactory implemention for each behavior implementation
	For example, ICommandFactory is an interface on
	kBehaviorDataBoss and kActionFactoryBoss (a service provider)
	@see CommandFactory
*/
class ICommandFactory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMMANDFACTORY };
	
	/** @return A command that will create a particular behavior */
	virtual ICommand*	CreateCreateCommand() const = 0;

	/** @return A command that will edit a particular behavior */
	virtual ICommand*	CreateEditCommand() const = 0;

	/** @return A command that will delete a particular behavior */
	virtual ICommand*	CreateDeleteCommand() const = 0;

	/** @return A command to be executed after the particular behavior is copied.
	
		Such commands are called Fixup*BhvrCmd where * is the name of the behavior
		Examples are FixupShowHideFieldsBhvrCmd, FixupSoundBhvrCmd  If you don't
		reference other UIDs, you can usually just return kNoOpCmdBoss for this.
		
		Fixup commands (or DeferredScrap Commands) generally look at
		IXReferenceUID and edit the behavior so that the UIDs that are
		source refs in IXReferenceUID are changed to the corresponding
		destination refs
		@see IXReferenceUID, FixupSoundBhvrCmd, FixupShowHideFieldsBhvrCmd
		
		 */
	virtual ICommand*	CreateDeferredScrapCommand() const = 0;
};

#endif // __ICommandFactory_h__
