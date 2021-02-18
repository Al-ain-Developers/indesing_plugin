//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CBooleanControlDataObserver.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CBOOLEANCONTROLDATAOBSERVER__
#define __CBOOLEANCONTROLDATAOBSERVER__

#include "CObserver.h"
#include "HelperInterface.h"
#include "ShuksanID.h"

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------

#pragma export on

#ifdef ID_DEPRECATED
/** This class is not used by any internal code, hence it may not work....
*/

class WIDGET_DECL CBooleanControlDataObserver : public CObserver
{
	public:
		CBooleanControlDataObserver(IPMUnknown *boss, PMIID interfaceID = IID_IOBSERVER);
		virtual ~CBooleanControlDataObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) ; 

		virtual void AutoAttach();
			// If the observer knows who to attach itself to, it'll do so with this call
			
		virtual void AutoDetach();
			// If the observer knows who to detach itself from, it'll do so with this call
			
	protected:
		
		// Clients should override DoBooleanUpdate to do the heart of the work when
		// the boolean control changes state.
		virtual void DoBooleanUpdate(bool16 selected);

DECLARE_HELPER_METHODS()
};
#endif

#pragma export off

#endif
