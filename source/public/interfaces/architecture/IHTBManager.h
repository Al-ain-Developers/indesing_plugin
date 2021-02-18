//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTBManager.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _IHTBManager_
	#define _IHTBManager_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h"
	
	//.......ID headers...........................................................................
	#include "ShuksanID.h"

//================================================================================================
/**	This is the HTB Manger interface. It is analogous to the selection's ASB.
*/
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IHTBManager : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IHTBMANAGER };
		typedef K2Vector<InterfacePtr<IPMUnknown> >	UniformTargetingBossCollection;	

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//________________________________________________________________________________________
		/** Is the interface enbaled, i.e. does it exist on one of the enabled UTBs.
		//
		//	@returns True or False. */
		//________________________________________________________________________________________
		virtual bool16 		IsInterfaceEnabled (const PMIID& interfaceID) const = 0;

		//________________________________________________________________________________________
		/** Startup the htb manager on the hybrid targeting boss.
			
			@param iTargetingBoss */
		//________________________________________________________________________________________
		virtual void 		Startup (IPMUnknown* iTargetingBoss) = 0;
		
		//________________________________________________________________________________________
		/** Return a list of interfaces from the concrete selection bosses. Check for 
			the requested interface on all CSBs or only on the active CSBs.

			NOTE:		The caller must call delete() on the returned collection.

			@returns 	A collection of IPMUnknown*	*/
		//________________________________________________________________________________________
		virtual UniformTargetingBossCollection* QueryUniformTargetingBosses (const PMIID&) const = 0;
	};

#endif // _IHTBManager_