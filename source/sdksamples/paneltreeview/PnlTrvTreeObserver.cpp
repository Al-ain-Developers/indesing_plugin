//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvTreeObserver.cpp $
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
#include "IPMStream.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "IPnlTrvDataModel.h"
// General includes
#include "CObserver.h"
#include "CAlert.h"
#include "K2Vector.tpp" // For NodeIDList to compile
#include "StreamUtil.h"
#include "PnlTrvUtils.h"
// Project includes
#include "PnlTrvFileNodeID.h"
#include "PnlTrvID.h"
#include "IPnlTrvOptions.h"
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

	@ingroup paneltreeview
	
*/
class PnlTrvTreeObserver : public CObserver
{
public:
	/**
		Constructor for WLBListBoxObserver class.
		@param interface ptr from boss object on which this interface is aggregated.
	*/
	PnlTrvTreeObserver(IPMUnknown* boss);

	/**
		Destructor 
	*/	
	~PnlTrvTreeObserver();

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
	
	/** Updates this plug-in's panel when the plug-in's model changes. For example when this plug-in's preferences
		(IPnlTrvOptions) change. Widgets that react to changes in the plug-in's model are updated by lazy notifications 
		handled by this method.
		@param theSubject [IN] provides a reference to the object which has changed.
		@param protocol [IN] the protocol along which the change occurred.
		@param data [IN] 
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
	void initTree();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvTreeObserver, kPnlTrvTreeObserverImpl)


/* Constructor
*/
PnlTrvTreeObserver::PnlTrvTreeObserver(IPMUnknown* boss)
: CObserver(boss)
{
}


/* Destructor
*/
PnlTrvTreeObserver::~PnlTrvTreeObserver()
{
}


/* AutoAttach
*/
void PnlTrvTreeObserver::AutoAttach()
{
	// Show/refresh tree when widget made visible
	initTree();
	InterfacePtr<ISubject> mySubj(this, UseDefaultIID()); 
	ASSERT(mySubj);
	mySubj->AttachObserver(this, IID_ITREEVIEWCONTROLLER);

	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace()); 
	InterfacePtr<IPnlTrvOptions> ptOptions(ws, UseDefaultIID());
	if (ptOptions)
	{
		InterfacePtr<ISubject> subj(ptOptions, UseDefaultIID());
		if (subj && !subj->IsAttached(ISubject::kLazyAttachment,this, IID_IPNLTRVOPTIONS, IID_IOBSERVER))
		{
			subj->AttachObserver(ISubject::kLazyAttachment,this, IID_IPNLTRVOPTIONS, IID_IOBSERVER);
		}
	}
}


/* AutoDetach
*/
void PnlTrvTreeObserver::AutoDetach()
{
	InterfacePtr<ISubject> mySubj(this, UseDefaultIID()); 
	ASSERT(mySubj);
	mySubj->DetachObserver(this, IID_ITREEVIEWCONTROLLER);

	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace()); 
	InterfacePtr<IPnlTrvOptions> ptOptions(ws, UseDefaultIID());
	if (ptOptions)
	{
		InterfacePtr<ISubject> subj(ptOptions, UseDefaultIID());
		if (subj && subj->IsAttached(ISubject::kLazyAttachment,this, IID_IPNLTRVOPTIONS, IID_IOBSERVER))
		{
			subj->DetachObserver(ISubject::kLazyAttachment,this, IID_IPNLTRVOPTIONS, IID_IOBSERVER);
		}
	}
}


/* Update
*/
void PnlTrvTreeObserver::Update(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy)
{

	switch(theChange.Get())
	{
		case kListSelectionChangedMessage:
			{
				this->handleSelectionChanged();
				break;
			}
		default:
			{
				ASSERT_FAIL (FORMAT_ARGS ("PnlTrvTreeObserver::Update does not support theChange (%x)", theChange.Get()));
				break;
			}
	}
}

/*
*/
void PnlTrvTreeObserver:: LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* )
{
	switch(protocol.Get())
	{
		case IID_IPNLTRVOPTIONS:
			{
				this->initTree();
				break;
			}
		default:
			{
				ASSERT_FAIL (FORMAT_ARGS ("PnlTrvTreeObserver::LazyUpdate does not support this protocal (%x)", protocol.Get ()));
				break;
			}
	}
}

/* initTree
*/
void PnlTrvTreeObserver::initTree()
{
	do
	{
		InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		// Get latest folder from option
		PMString folderRootPath = PnlTrvUtils::GetFolderSelectedPath();
		// Empty folder path is fine, for instance, if we undid setting
		// the path when we just started up, it should be OK to do this
		model->Rebuild(folderRootPath);
		InterfacePtr<ITreeViewMgr>	
			treeViewMgr(this, UseDefaultIID());
		ASSERT(treeViewMgr);
		if(treeViewMgr == nil)
		{
			break;
		}
		treeViewMgr->ClearTree();
		treeViewMgr->ChangeRoot(kTrue);
	} while(kFalse);
}


/* handleSelectionChanged
*/
void PnlTrvTreeObserver::handleSelectionChanged()
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
			TreeNodePtr<PnlTrvFileNodeID> nodeID(selectedItems[0]);
			ASSERT(nodeID);
			if(!nodeID)
			{
				break;
			}
			PMString pstr(nodeID->GetPath());
			this->doPreview(pstr);
		}
	} while(kFalse);
}


/* doPreview
*/
void PnlTrvTreeObserver::doPreview(const PMString& path)
{
	do
	{
		SDKFileHelper fileHelper(path);
		IDFile xFile = fileHelper.GetIDFile();
		InterfacePtr<IWidgetParent> 
			iWidgetParent(this, UseDefaultIID());
		ASSERT(iWidgetParent);
		if(!iWidgetParent)
		{
			break;
		}
		InterfacePtr<IPanelControlData>	iPanelControlData( 
			(IPanelControlData*)iWidgetParent->QueryParentFor(IID_IPANELCONTROLDATA) );
	
		ASSERT(iPanelControlData);
		if(!iPanelControlData)
		{
			break;
		}

		IControlView* iWidgetView = 
			iPanelControlData->FindWidget(kPnlTrvCustomPanelViewWidgetID);
		ASSERT(iWidgetView);
		if(!iWidgetView) {
			break;
		}
		

		// below, if we could find the stream, we'll set this true
		InterfacePtr<IPMStream> 
			iDataFileStream(StreamUtil::CreateFileStreamReadLazy(xFile));
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
		iSysFileData->Set(xFile);


		iWidgetView->Invalidate();
	} while(kFalse);
}

//	end, File: PnlTrvTreeObserver.cpp
