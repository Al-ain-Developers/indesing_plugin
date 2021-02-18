//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITreeNodeObserver.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes
#include "ISubject.h"
#include "ITreeViewMgr.h"
#include "ITreeNodeIDData.h"
#include "CusDtLnkUIFileNodeID.h"
#include "IWidgetParent.h"
#include "ITextControlData.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ICusDtLnkFacade.h"
// General includes:
#include "Utils.h"
#include "CObserver.h"
#include "CAlert.h"
#include "AcquireModalCursor.h"
// Project
#include "CusDtLnkUIID.h"
/**
	Implements IObserver; this is observing changes in the expand/collapse state of 
	the node widgets that have dependents. When there is a change in this state, it's
	displayed in a static text widget.
	
	 The class is derived from CObserver, and overrides the
	AutoAttach(), AutoDetach(), and Update() methods.
	This class implements the IObserver interface using the CObserver helper class,
	and is listening along the IID_ITREEVIEWMGR protocol for changes in the tree-data model.

	
	@ingroup customdatalinkui
*/

class CusDtLnkUITreeNodeObserver : public CObserver
{
public:
	/**
		Constructor 
		@param interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUITreeNodeObserver(IPMUnknown* boss);

	/**
		Destructor
	*/	
	~CusDtLnkUITreeNodeObserver();

	/**
		AutoAttach is only called for registered observers
		of widgets.  This method is called by the application
		core when the widget is shown.
	*/	
	virtual void AutoAttach();

	/**
		AutoDetach is only called for registered observers
		of widgets. Called when widget hidden.
	*/	
	virtual void AutoDetach();

	/**
		Update is called for all registered observers, and is
		the method through which changes are broadcast. 
		@param theChange [IN] is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject [IN] provides a reference to the object which has changed; in this case, the button
		widget boss object that is being observed.
		@param protocol [IN] the protocol along which the change occurred.
		@param changedBy [IN] this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/	
	virtual void Update(
		const ClassID& theChange, 
		ISubject* theSubject, 
		const PMIID &protocol, 
		void* changedBy);

private:
	void handleChange(bool16 isExpanding);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUITreeNodeObserver, kCusDtLnkUITreeNodeObserverImpl)


/* Constructor
*/
CusDtLnkUITreeNodeObserver::CusDtLnkUITreeNodeObserver(IPMUnknown* boss)
: CObserver(boss)
{

}


/* Destructor
*/
CusDtLnkUITreeNodeObserver::~CusDtLnkUITreeNodeObserver()
{

}


/* AutoAttach
*/
void CusDtLnkUITreeNodeObserver::AutoAttach()
{
	do {

		InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
		ASSERT(subj);
		subj->AttachObserver(this, IID_ITREEVIEWMGR);
		
	} while(kFalse);

}


/* AutoDetach
*/
void CusDtLnkUITreeNodeObserver::AutoDetach()
{
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	ASSERT(subj);
	subj->DetachObserver(this, IID_ITREEVIEWMGR);
}


/* Update
*/
void CusDtLnkUITreeNodeObserver::Update(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy)
{
	switch(theChange.Get())
	{
		case kTreeNodeExpandedMsg: 
		{
			AcquireWaitCursor busyCursor;
			this->handleChange(kTrue);
			break;
		}
		case kTreeNodeCollapsedMsg:
		{
			this->handleChange(kFalse);
			break;
		}
	}
}


/* handleChange
*/
void CusDtLnkUITreeNodeObserver::handleChange(bool16 isExpanding)
{
	do
	{
		InterfacePtr<ITreeNodeIDData> 
			nodeData(this, UseDefaultIID());
		ASSERT(nodeData);
		if(!nodeData)
		{
			break;
		}
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(nodeData->Get());
		ASSERT(nodeID);
		if(!nodeID)
		{
			break;
		}
		PMString pstr(nodeID->GetUniqueKey());
	
		InterfacePtr<IWidgetParent> 
			iWidgetParent(this, UseDefaultIID());
		ASSERT(iWidgetParent);
		if(!iWidgetParent)
		{
			break;
		}

		InterfacePtr<ITreeViewMgr>	iTreeViewMgr( 
			(ITreeViewMgr*)iWidgetParent->QueryParentFor(IID_ITREEVIEWMGR) );
		// Be sure we get the right panel control data; we don't want the one on the
		// tree but on it's parent, a panel
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr)
		{
			break;
		}

		InterfacePtr<IWidgetParent> 
			iTreeWidgetParent(iTreeViewMgr, UseDefaultIID());
		ASSERT(iTreeWidgetParent);
		if(!iTreeWidgetParent)
		{
			break;
		}
		// We should now be at the panel that contains the tree _and_ the other widgets
		InterfacePtr<IPanelControlData>	iPanelControlData( 
			(IPanelControlData*)iTreeWidgetParent->QueryParentFor(IID_IPANELCONTROLDATA) );
	
		ASSERT(iPanelControlData);
		if(!iPanelControlData)
		{
			break;
		}

		IControlView* iWidgetView = iPanelControlData->FindWidget(kCusDtLnkUITreeTextMessageWidgetID);
		// fail silently, as we might be on a panel or dlg without this
		if(!iWidgetView) {
			break;
		}
		PMString displayStr = Utils<ICusDtLnkFacade>()->TruncatePath(pstr);
		if(isExpanding)
		{
			displayStr += ":expanding.";
		}
		else
		{
			displayStr += " : collapsing.";
		}
		displayStr.SetTranslatable(kFalse);
	
		InterfacePtr<ITextControlData> 
			textControlData(iWidgetView, UseDefaultIID());
		ASSERT(textControlData);
		if(!textControlData)
		{
			break;
		}
		textControlData->SetString(displayStr);
	} while(kFalse);
}

//	end, File:	CusDtLnkUITreeNodeObserver.cpp
