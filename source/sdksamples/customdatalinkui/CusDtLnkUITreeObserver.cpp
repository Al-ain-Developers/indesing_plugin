//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITreeObserver.cpp $
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
#include "IControlView.h"
#include "ITreeViewMgr.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ISysFileData.h"
#include "IBoolData.h"
#include "IPMStream.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "ICusDtLnkUITreeDataModel.h"
#include "ICusDtLnkFacade.h"
#include "IActiveContext.h"
#include "IWorkspace.h"

// General includes
#include "Utils.h"
#include "CusDtLnkUITreeDataNode.h"
#include "CObserver.h"
#include "CAlert.h"
#include "K2Vector.tpp" // For NodeIDList to compile
#include "StreamUtil.h"

// Project includes
#include "CusDtLnkUIFileNodeID.h"
#include "CusDtLnkUIID.h"
//#include "ICusDtLnkUITreeOptions.h"
#include "SDKFileHelper.h"

/** Implements IObserver; initialises the tree when an IObserver::AutoAttach message sent
	and listens for when the node selection changes.
	When the selection changes and there's a non-empty selection list, it takes the first item
	and previews the asset if it can do so (for instance, if it's a GIF, JPEG etc).
	It does this by setting a path on a data interface of the custom-view panel widget and
	invalidating the widget, forcing it to redraw to create a rendering of the new asset.

	 The class is derived from CObserver, and overrides the
	AutoAttach(), AutoDetach(), and Update() methods.
	This class implements the IObserver interface using the CObserver helper class,
	and is listening along the IID_ITREEVIEWCONTROLLER protocol for changes in the tree data model.

	@ingroup customdatalinkui
	
*/
class CusDtLnkUITreeObserver : public CObserver
{
public:
	/**
		Constructor for WLBListBoxObserver class.
		@param interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUITreeObserver(IPMUnknown* boss);

	/**
		Destructor 
	*/	
	~CusDtLnkUITreeObserver();

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
		@param theChange [IN] this is specified by the agent of change; it can be the class ID of the agent,
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

	/** Updates this plug-in's tree view when the plug-in's preferences change.
		@param theSubject [IN] provides a reference to the object which has changed.
		@param protocol [IN] the protocol along which the change occurred.
		@param data [IN] not used by this plug-in currently
	*/
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* );

protected:

	/**	Handles a change in the selection when the end user 
	either clicks on a node or clicks off it
	*/
	void handleSelectionChanged();

	/**	Sets the path on the preview widget and invalidates it
		@param path [IN] specifies the path to the asset in 
		the local file system
	 */
	void doPreview(const PMString& path);

	/**	Populates the tree model. 
	 */
	void initTree(IWorkspace *ws);

	// Handle active context (workspace) change
	void ActiveContextChange(IActiveContext* context);

private:
	/** Cache current workspace
	*/
	IWorkspace *fCurrentWorkspace;

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUITreeObserver, kCusDtLnkUITreeObserverImpl)


/* Constructor
*/
CusDtLnkUITreeObserver::CusDtLnkUITreeObserver(IPMUnknown* boss)
: CObserver(boss), fCurrentWorkspace(nil)
{
}


/* Destructor
*/
CusDtLnkUITreeObserver::~CusDtLnkUITreeObserver()
{
}


/* AutoAttach
*/
void CusDtLnkUITreeObserver::AutoAttach()
{
	
   // Observe the active context.
    IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
    if (context)
    {
        InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
        contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

    // Observe the current document in the active context (if any).
    this->ActiveContextChange(context);

	//Attach to tree view after the tree has been rebuilt
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	ASSERT(subj);
	subj->AttachObserver(this, IID_ITREEVIEWCONTROLLER);


}


/* AutoDetach
*/
void CusDtLnkUITreeObserver::AutoDetach()
{

	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
    if (context)
    {
        InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
        contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
    }

	// Attach from the widget
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	ASSERT(subj);
	subj->DetachObserver(this, IID_ITREEVIEWCONTROLLER);

	// detach from the workspace
	if(fCurrentWorkspace)
	{
		InterfacePtr<ISubject> subject(fCurrentWorkspace, UseDefaultIID());
		if (subject) {
				subject->DetachObserver(ISubject::kLazyAttachment,this, IID_ICUSDTLNKDATABASESASOPTIONS, IID_IOBSERVER);
		}
		fCurrentWorkspace = nil;
	}
}

void CusDtLnkUITreeObserver::ActiveContextChange(IActiveContext* context)
{
	ASSERT(context);
	IWorkspace* theWorkspace = context->GetContextWorkspace();
	if (theWorkspace != fCurrentWorkspace)
	{
		if (fCurrentWorkspace)
		{
			InterfacePtr<ISubject> subject(fCurrentWorkspace, UseDefaultIID());
			if (subject) {
					subject->DetachObserver(ISubject::kLazyAttachment,this, IID_ICUSDTLNKDATABASESASOPTIONS, IID_IOBSERVER);
			}
		}

		if (theWorkspace)
		{
			InterfacePtr<ISubject> subject(theWorkspace, UseDefaultIID());
			if (subject) {
				// We care when databases change
				subject->AttachObserver(ISubject::kLazyAttachment,this, IID_ICUSDTLNKDATABASESASOPTIONS, IID_IOBSERVER);
			}
			fCurrentWorkspace = theWorkspace;
		}
		
		// Show/refresh tree
		initTree(fCurrentWorkspace);

	}

}

/* Update
*/
void CusDtLnkUITreeObserver::Update(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy)
{
	switch(protocol.Get())
	{
		case IID_ITREEVIEWCONTROLLER:
		{
			if (theChange.Get() == kListSelectionChangedMessage)
				this->handleSelectionChanged();
			break;
		}
		case IID_IACTIVECONTEXT:
		{
			IActiveContext::ContextInfo* contextInfo = reinterpret_cast<IActiveContext::ContextInfo*>(changedBy);
			if (contextInfo->Key() == IID_IWORKSPACE)
			{
				InterfacePtr<IActiveContext> context( theSubject, UseDefaultIID() );
				this->ActiveContextChange(context);
			}
			break;
		}
		default:
		{
			ASSERT_FAIL (FORMAT_ARGS ("CusDtLnkUITreeObserver::Update does not support theChange (%x)", theChange.Get()));
			break;
		}
	}
}

/* LazyUpdate
*/
void CusDtLnkUITreeObserver::LazyUpdate(
	ISubject* theSubject, 
	const PMIID &protocol, 
	const LazyNotificationData* )
{
	switch(protocol.Get())
	{
		case IID_ICUSDTLNKDATABASESASOPTIONS:
		{
			// We're only listening for changes in the databases, not other
			// options....
			InterfacePtr<IWorkspace> ws(theSubject, IID_IWORKSPACE);
			this->initTree(ws); // This should be the same as the current workspace
			break;
		}
		default:
		{
			ASSERT_FAIL (FORMAT_ARGS ("CusDtLnkUITreeObserver::LazyUpdate does not support this protocal (%x)", protocol.Get ()));
			break;
		}
	}
}


/* initTree
*/
void CusDtLnkUITreeObserver::initTree(IWorkspace *ws)
{
	do
	{
		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		model->Rebuild(ws);

		InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());
		ASSERT(treeViewMgr);
		if(!treeViewMgr) {
			break;
		}
		treeViewMgr->ClearTree();
		treeViewMgr->ChangeRoot(kTrue);

		//Update preview
		this->handleSelectionChanged();
	
	} while(kFalse);
}


/* handleSelectionChanged
*/
void CusDtLnkUITreeObserver::handleSelectionChanged()
{
	do
	{
		InterfacePtr<ITreeViewController> 
			controller(this, UseDefaultIID());
		ASSERT(controller);
		if(!controller)
		{
			break;
		}

		NodeIDList selectedItems;
		controller->GetSelectedItems(selectedItems);
		// We've got single selection only
		if(selectedItems.size()>0)
		{
			TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(selectedItems[0]);
			ASSERT(nodeID);
			if(!nodeID)
			{
				break;
			}
			PMString uk(nodeID->GetUniqueKey());
			this->doPreview(uk);
		}
		else
		{   // Clear preview area
			PMString clear;
			this->doPreview(clear);

		}
	} while(kFalse);
}


/* doPreview
*/
void CusDtLnkUITreeObserver::doPreview(const PMString& uniqueKey)
{
	do
	{
		InterfacePtr<IWidgetParent> 
			iWidgetParent(this, UseDefaultIID());
		ASSERT(iWidgetParent);
		if(!iWidgetParent)
		{
			break;
		}
		// Look for another widget that's a peer of this one
		// that can do a custom view, looking it up by widgetID
		InterfacePtr<IPanelControlData>	iPanelControlData( 
			(IPanelControlData*)iWidgetParent->QueryParentFor(IID_IPANELCONTROLDATA) );
	
		ASSERT(iPanelControlData);
		if(!iPanelControlData)
		{
			break;
		}

		IControlView* iWidgetView = 
			iPanelControlData->FindWidget(kCusDtLnkUITreeCustomPanelViewWidgetID);
		// We may not have this widget, so don't worry
		if(!iWidgetView) {
			break;
		}

		if (uniqueKey.IsEmpty())
		{
  			InterfacePtr<ISysFileData> iSysFileData(iWidgetView, IID_ISYSFILEDATA);
  			IDFile invalidFile; //This is a file pointing to working directory, can not be previewed.
  			iSysFileData->Set(invalidFile);
			iWidgetView->Invalidate();
			break;
		}

		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		
		CusDtLnkUITreeDataNode* dataNode = model->GetNode(uniqueKey);
		ASSERT(dataNode);
		if(!dataNode) {
			break;
		}
		if(dataNode->GetNodeType() != CusDtLnkUITreeDataNode::eAssetType) {
			break;
		}
		// it's an asset, think about previewing
	
		IDFile absPathIDFile = dataNode->ResolveAssetPath();
		
		SDKFileHelper assHelper(absPathIDFile);
		if(!assHelper.IsExisting()) {
			break;
		}
		// We'll use this somewhat later
		Utils<ICusDtLnkFacade>()->SetCurrentlyChosenUniqueAssetKey(model->GetWorkspace(), uniqueKey);

		InterfacePtr<IPMStream> 
			iDataFileStream(StreamUtil::CreateFileStreamReadLazy(absPathIDFile));
		// If nil, we couldn't have opened this
		if (iDataFileStream == nil)
		{
			break;
		}

		iDataFileStream->Close();

		InterfacePtr<ISysFileData> 
			iSysFileData(iWidgetView, IID_ISYSFILEDATA);
		ASSERT(iSysFileData);
		if(!iSysFileData)
		{
			break;
		}
		iSysFileData->Set(absPathIDFile);

		iWidgetView->Invalidate();
	} while(kFalse);
}

//	end, File: CusDtLnkUITreeObserver.cpp
