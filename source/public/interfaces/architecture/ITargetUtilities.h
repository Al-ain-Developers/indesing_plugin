//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITargetUtilities.h $
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
//========================================================================================

#pragma once
#ifndef __ITargetUtilities__
#define __ITargetUtilities__

//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

	//.......Interface headers....................................................................
	#include "IPMUnknown.h"

	//.......ID headers...........................................................................
	#include "ShuksanID.h"										// ID definition header

	//.......Other headers........................................................................
//________________________________________________________________________________________________
//	Forward Declarations
//________________________________________________________________________________________________
	
//================================================================================================

//________________________________________________________________________________________________
//	NOTE:	This interface is available on the UtilsBoss. Please use the following syntax:
//			Utils<ITargetUtilities>()->SomeMemberFunction( ... );
//________________________________________________________________________________________________

class ITargetUtilities : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITARGETUTILS };
		
		//________________________________________________________________________________________
		/** Creates a Hybrid Target sub-system. The caller is responsible for calling 
			DestroyHybridTargetBoss() with the returned HTB sub-system.
			
			@param target specifier
			@return HTB sub-system	*/
		//________________________________________________________________________________________
		virtual IPMUnknown* 	CreateHybridTargetBoss	(IPMUnknown* iTarget) = 0;

		//________________________________________________________________________________________
		/** Creates a Hybrid Target sub-system for a UIDList. The caller is responsible for calling 
			DestroyHybridTargetBoss() with the returned HTB sub-system.
			
			@param UIDList
			@return HTB sub-system using the IID to choose a suite	*/
		//________________________________________________________________________________________
		virtual IPMUnknown* 	CreateHybridTargetBoss	(const UIDList& items, const PMIID& id = IID_IUNKNOWN) = 0;

};


#endif	// __ITargetUtilities__
