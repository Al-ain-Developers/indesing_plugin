//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/InLineEditController.h $
//  
//  Owner: Matt joss
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
#ifndef __InLineEditController__
#define __InLineEditController__

#include "IInLineEditController.h"
#include "IEvent.h"

class IControlView;
class IEventHandler;

#pragma export on

//----------------------------------------------------------------------------------------
// InLineEditController constructor
//----------------------------------------------------------------------------------------
class WIDGET_DECL InLineEditController : public IInLineEditController
{
public:
	InLineEditController(IPMUnknown *boss);
	~InLineEditController();
	
	virtual bool16 BeginEditing();
	virtual bool16 StopEditing(bool16 syncData, bool16 releaseKeyFocus);
	virtual bool16 IsBeingEdited() const;
	virtual void   SyncFilteringNode();

protected:
	virtual	void SetEditState(bool16 isEditing);
	virtual	void CreateEditingWidget() {}
	virtual	void RemoveEditingWidget() {}
	
	virtual void BeginEditing_SyncToWidget (IControlView * iStaticView, IControlView * iEditView);
	virtual void StopEditing_SyncToWidget (IControlView * iStaticView, IControlView * iEditView);
	virtual ClassID GetInLineEditEventMonitor () const;

	virtual bool16 ForceNotifyTextChangeForNonDropDown() const { return kFalse;  }

private:
	// Private implementation class
	class PrivateImpl;
	PrivateImpl*			Impl() const {return fImpl;}
	PrivateImpl*			fImpl;

DECLARE_HELPER_METHODS()
};


#pragma export off

#endif
