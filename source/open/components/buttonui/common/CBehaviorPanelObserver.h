//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/common/CBehaviorPanelObserver.h $
//  
//  Owner: Dave Stephens
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
#ifndef __CBehaviorPanelObserver__
#define __CBehaviorPanelObserver__

// ----- Implementation Includes -----

#include "CActiveSelectionObserver.h"

class IBehaviorData;
class ISubject;

//========================================================================================
// CLASS GoToURLPanelObserver
//========================================================================================

class CBehaviorPanelObserver : public CActiveSelectionObserver
{
public:
	CBehaviorPanelObserver(IPMUnknown *boss);
	virtual ~CBehaviorPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();

protected:
	virtual void HandleSelectionChanged (const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged (const ISelectionMessage*);
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
		
	virtual void		InitializeFieldsFromActionData(const IBehaviorData* inActionData) {}
	virtual bool		ApplyFieldsToActionData(IBehaviorData* inActionData) {return true;}

	bool	isAttached;
private:
	bool	isInitialized;
};

#endif