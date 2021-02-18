//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IIntegratorTarget.h $
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
	#ifndef _IIntegratorTarget_
	#define _IIntegratorTarget_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h"
	
	//.......ID headers...........................................................................
	#include "ShuksanID.h"

//================================================================================================
/**	This is the target interface for integrator suites on the ASB/HTB to use.
*/
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IIntegratorTarget : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IINTEGRATORTARGET };
		typedef K2Vector<InterfacePtr<IPMUnknown> >	TargetSuiteCollection;	

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//________________________________________________________________________________________
		/** Return a list of interfaces from the "concrete selection" or "uniform targeting" bosses.
		
			NOTE:		The caller must call delete() on the returned collection.
			
			@param iid 
			@returns A collection of IPMUnknown*	*/
		//________________________________________________________________________________________
		virtual TargetSuiteCollection* GetTarget (const PMIID& iid) const = 0;
	};

#endif // _IIntegratorTarget_