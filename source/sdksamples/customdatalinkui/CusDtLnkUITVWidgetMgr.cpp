//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITVWidgetMgr.cpp $
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

// Interface includes:
#include "IControlView.h"
#include "IImportProvider.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ICusDtLnkFacade.h"
#include "ICusDtLnkUITreeDataModel.h"
#include "IWidgetParent.h"
#include "IObserver.h"
// General includes:
#include "Utils.h"
#include "CTreeViewWidgetMgr.h"
#include "CreateObject.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysControlIds.h"
#include "OpenPlaceID.h"
#include "SDKFileHelper.h"
#include "CusDtLnkUITreeDataNode.h"

// Project includes:
#include "CusDtLnkUIID.h"
#include "CusDtLnkUIFileNodeID.h"
//#include "CusDtLnkUITreeUtils.h"

/**
	Implements ITreeViewWidgetMgr, providing methods to create and describe the widgets for 
	nodes in the tree. This interface is similar to a widget factory in that this is where 
	you will create widgets for the nodes in the tree.
	
	For further reading on ITreeViewWidgetMgr interface, see the Widgets chapter
	of the User Interface technote.

	
	@ingroup customdatalinkui

*/

class CusDtLnkUITreeTVWidgetMgr: public CTreeViewWidgetMgr
{
public:
	/**
		Constructor
		@param boss object on which this interface is being aggregated
	*/	
	CusDtLnkUITreeTVWidgetMgr(IPMUnknown* boss);

	/**
		Destructor
	*/	
	virtual ~CusDtLnkUITreeTVWidgetMgr() {}

	/** Create instance of the widget that represents given node in the tree.
		@param node [IN] specifies node of interest
		@return return reference to a newly instantiated object that is suitable for this node
	*/	
	virtual	IControlView* CreateWidgetForNode(
		const NodeID& node) const;
	/**
		Retrieve ID of a widget that has the right appearance for the node
		that you're trying to display. Here we use the same widget types for all the nodes,
		but vary the appearance by showing or hiding the expander widget depending on the number
		of children associated with a node.
		@param node [IN] specifies node of interest
		@return the ID of a widget that has the correct appearance for the given node type
	*/	
	virtual	WidgetID GetWidgetTypeForNode(const NodeID& node) const;

	/** Determine how to render the given node to the specified control.
		Figure out how you're going to render it based on properties of the node
		such as whether is has children or not (don't show expander if no children, for instance).
		@param node [IN] refers to the node that we're trying to render
		@param widget [IN] the control into which this node's appearance is going to be rendered
		@param message [IN] specifies ???
		@return kTrue if the node has been rendered successfully, kFalse otherwise
	*/	
	virtual	bool16 ApplyNodeIDToWidget(
		const NodeID& node, 
		IControlView* widget, 
		int32 message = 0) const;

	/** Given a particular node, how far should it be indented? This method
		returns a value in pixels that is used to indent the displayed node 
		from the left edge of the tree-view control.
		@param node [IN] specifies node of interest
		@return an indent for this particular node from the left edge of tree-view
	*/
	virtual PMReal GetIndentForNode(const NodeID& node) const;

private:
	bool16 isOnOurSelectableDialog() const;

	void indent(
		const NodeID& node, IControlView* widget, IControlView* staticTextWidget) const;

	void setIconForContent(
		IControlView* widget, const PMString& path) const;

	bool16 canImportThisFile(const PMString& path) const;
	void cacheExtensions();

	std::map<PMString, PMString> fExtensionMap;
};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUITreeTVWidgetMgr, kCusDtLnkUITVWidgetMgrImpl)

/* Constructor
*/
CusDtLnkUITreeTVWidgetMgr::CusDtLnkUITreeTVWidgetMgr(IPMUnknown* boss) :
	CTreeViewWidgetMgr(boss)
{
	this->cacheExtensions();
}


/* CreateWidgetForNode
*/
IControlView* CusDtLnkUITreeTVWidgetMgr::CreateWidgetForNode(
	const NodeID& node) const
{
	IControlView* retval= (IControlView*) ::CreateObject(
		::GetDataBase(this),
		RsrcSpec(LocaleSetting::GetLocale(), 
		kCusDtLnkUIPluginID, 
		kViewRsrcType, 
		kCusDtLnkUITreeNodeWidgetRsrcID),
		IID_ICONTROLVIEW);

	ASSERT(retval);
	return retval;
}



/* GetWidgetTypeForNode
*/
WidgetID CusDtLnkUITreeTVWidgetMgr::GetWidgetTypeForNode(
	const NodeID& node) const
{
	return kCusDtLnkUITreeNodeWidgetId;
}


/* ApplyNodeIDToWidget
*/
bool16 CusDtLnkUITreeTVWidgetMgr::ApplyNodeIDToWidget(
	const NodeID& node, IControlView* widget, int32 message) const
{
	CTreeViewWidgetMgr::ApplyNodeIDToWidget(node, widget);
	do
	{
		// If this node doesn't have any children, don't show expander Widget
		InterfacePtr<IPanelControlData> 
			panelControlData(widget, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData==nil) {
			break;
		}
		// Set expander widget to hidden state if this node has no kids
		IControlView* expanderWidget = panelControlData->FindWidget(kTreeNodeExpanderWidgetID);
		ASSERT(expanderWidget);
		if(expanderWidget == nil) {
			break;
		}
		InterfacePtr<const ITreeViewHierarchyAdapter>
			adapter(this, UseDefaultIID());
		ASSERT(adapter);
		if(adapter == nil) {
			break;
		}
		if (expanderWidget) {
			if (adapter->GetNumChildren(node) <= 0) {
				expanderWidget->HideView();
			}
			else {
				expanderWidget->ShowView();
			}
		}

		IControlView* iconView = 
			panelControlData->FindWidget(kCusDtLnkUITreeIconWidgetId);
		ASSERT(iconView);
		if (iconView == nil) {
			break;
		}

		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(node);
		ASSERT(nodeID);
		if(nodeID == nil) {
			break;
		}	
		PMString uniqueKey =  nodeID->GetUniqueKey();
		this->setIconForContent(iconView, uniqueKey);

		IControlView* displayStringView = 
			panelControlData->FindWidget( kCusDtLnkUITreeNodeNameWidgetID );
		ASSERT(displayStringView);
		if(displayStringView == nil) {
			break;
		}
		InterfacePtr<ITextControlData>
			textControlData( displayStringView, UseDefaultIID() );
		ASSERT(textControlData);
		if(textControlData== nil) {
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
		

		PMString lastPartOfUK(
			Utils<ICusDtLnkFacade>()->TruncatePath(uniqueKey));
		if(lastPartOfUK.empty()) {
			lastPartOfUK="Empty?";	
		}

		PMString stringToDisplay(lastPartOfUK);
		switch(dataNode->GetNodeType()) {
			case CusDtLnkUITreeDataNode::eAssetType:
			{
				stringToDisplay += " ";
				stringToDisplay += dataNode->GetDescription();
			}
			break;


			case  CusDtLnkUITreeDataNode::eDataBaseType:
			{
				// let's see if we're on a selectable dlg
				if(this->isOnOurSelectableDialog()) {
					// Display the FULL path only when on
					// selectable dialog
					stringToDisplay = uniqueKey;
				}
				
			}
			break;

			case CusDtLnkUITreeDataNode::eValueType:
			{
				// Truncate only on /, not other separators, so if 
				// we for instance have 12:23:34 as time field, we don't lose it
				PMString longerTruncatedUK(
					Utils<ICusDtLnkFacade>()->
						TruncatePath(uniqueKey, kFalse, kTextChar_Solidus));

				stringToDisplay = longerTruncatedUK;
		
			}
			break;
			//
		}
	
		stringToDisplay.SetTranslatable( kFalse );
		textControlData->SetString(stringToDisplay);
		// Adjust indenting
		this->indent( node, widget, displayStringView );
		
	} while(kFalse);

	return kTrue;
}


/* GetIndentForNode
*/
PMReal CusDtLnkUITreeTVWidgetMgr::GetIndentForNode(const NodeID& node) const
{
	return 10.0;
}


/* indent
*/
void CusDtLnkUITreeTVWidgetMgr::indent(
	const NodeID& node, 
	IControlView* widget, 
	IControlView* staticTextWidget) const
{	
	do
	{
		ASSERT(widget);
		ASSERT(staticTextWidget);
		if(widget == nil || staticTextWidget == nil) {
			break;
		}
		const PMReal myIndent = this->GetIndent(node);	
		// adjust the size to fit the text 
		PMRect widgetFrame = widget->GetFrame();
		widgetFrame.Left() = myIndent;
		widget->SetFrame( widgetFrame );
		// Call window changed to force FittedStaticText to resize
		staticTextWidget->WindowChanged();
		PMRect staticTextFrame = staticTextWidget->GetFrame();
		staticTextFrame.Right( widgetFrame.Right() );
		// Don't at present take account of scroll bar dimension?
		staticTextWidget->SetFrame( staticTextFrame );
	} while(kFalse);
}


/* setIconForContent
*/
void CusDtLnkUITreeTVWidgetMgr::setIconForContent(
	IControlView* iconView, const PMString& uniqueKey) const
{
	do {

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
		// Since the node widgets are recycled, be sure to explicitly set
		// the icon back to our default
		// kPMRsrcID_None = 0,0
		iconView->SetRsrcPluginID(0);
		iconView->SetRsrcID(0);

		switch(dataNode->GetNodeType()) {
			case CusDtLnkUITreeDataNode::eDataBaseType:  
			{
				SDKFileHelper fileHelper(uniqueKey);
				if(!fileHelper.IsExisting()) 
				{
// TODO					iconView->SetRsrcPluginID(kLinksPanelPluginID);
// TODO					iconView->SetRsrcID(kMissingStatusIconResID);
				}
			}
			break;

			case CusDtLnkUITreeDataNode::eAssetType:  
			{
				URI uri = dataNode->GetURIFromNode();
				if(uri.VerifyURI()) {
					//Check to see if the asset is available. Display missing icon when file/database does not exist
					Utils<ICusDtLnkFacade> facade;
					ASSERT(facade);
					if(!facade) {
						break;
					}
					IDFile	idFile;
					facade->URIToIDFile(uri, idFile);
					SDKFileHelper fileHelper(idFile);
					if(!fileHelper.IsExisting()) 
					{
	// TODO					iconView->SetRsrcPluginID(kLinksPanelPluginID);
	// TODO					iconView->SetRsrcID(kMissingStatusIconResID);
					}
					else if(dataNode->GetAssetState() == CusDtLnkUITreeDataNode::eStateFinal) {
						// TODO use more apt icons
						iconView->SetRsrcPluginID(kCusDtLnkUIPluginID);
						iconView->SetRsrcID(kCusDtLnkUIPenLockedIconRsrcID);
					} else if(dataNode->GetAssetState() == CusDtLnkUITreeDataNode::eStateProvisional){
						iconView->SetRsrcPluginID(kCusDtLnkUIPluginID);
						iconView->SetRsrcID(kCusDtLnkUIPenIconRsrcID);
					} else {
						iconView->SetRsrcPluginID(kCusDtLnkUIPluginID);
						iconView->SetRsrcID(kCusDtLnkUIBlankIconRsrcID);
					}
				}
			}
			break;
				
			case CusDtLnkUITreeDataNode::eValueType:
			{
				iconView->SetRsrcPluginID(kCusDtLnkUIPluginID);
				iconView->SetRsrcID(kCusDtLnkUIBlankIconRsrcID);
			};
			break;
			
		} // Switch on node type

	} while(kFalse);
}

/* cacheExtensions
*/
void CusDtLnkUITreeTVWidgetMgr::cacheExtensions()
{
	do {
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		if(!serviceRegistry) {
			break;
		}
		int	numHandlers = serviceRegistry->GetServiceProviderCount(kImportProviderService);
		for (int32 nHandler = 0; nHandler < numHandlers; nHandler++) {

			InterfacePtr<IK2ServiceProvider> provider(
				serviceRegistry->QueryNthServiceProvider(kImportProviderService, nHandler));
			InterfacePtr<IImportProvider> importProvider(provider, IID_IIMPORTPROVIDER);//UseDefaultIID());
			ASSERT(importProvider);
			if(!importProvider) {
				continue;
			}

			for(int32 nFormat = 0; nFormat <  importProvider->CountFormats(); nFormat++) {
				
				for(int32 nExtension = 0; 
					nExtension < importProvider->CountExtensionsForFormat( nFormat ); 
					nExtension++) {
					
						PMString strExtension = importProvider->GetExtensionForFormat( nFormat, nExtension );
						// These (I think) are stored as uppercase, but to be sure...
						strExtension.ToUpper();
						this->fExtensionMap.insert( 
							std::pair<PMString, PMString>(strExtension, strExtension));
		
				}
			}
		}
	} while(kFalse);
}

/* canImportThisFile
*/
bool16 CusDtLnkUITreeTVWidgetMgr::canImportThisFile(const PMString& path) const
{
	bool16 retval = kFalse;
	do {
		CharCounter lastDot =  path.LastIndexOfWChar(UTF32TextChar('.'));
		if(lastDot < 0 || lastDot >= path.CharCount()) {
			break;
		}
		K2::scoped_ptr<PMString> pExtension(path.Substring(lastDot+1, path.CharCount() - (lastDot+1)));
		ASSERT(pExtension);
		if(!pExtension) {
			break;
		}

		pExtension->ToUpper();
		std::map<PMString, PMString>::const_iterator result = fExtensionMap.find(*pExtension);
		if(result != fExtensionMap.end()){
			// If we  found this extension in the map we computed earlier,
			// then success; there is an existing import provider that 
			// can import this file extension. We're not considering Mac file
			// types for this sample
			retval = kTrue;
		}
	
	} while(kFalse);
	return retval;
}

bool16 CusDtLnkUITreeTVWidgetMgr::isOnOurSelectableDialog() const
{
	bool16 retval = kFalse;
	do {
		InterfacePtr<IWidgetParent> 
		widgetParent(this, UseDefaultIID());
		ASSERT(widgetParent);
		if(!widgetParent) {
			break;
		}
		
		// This interface marks it as our selectable dialog, see the FR file
		InterfacePtr<IObserver> ourObserver(static_cast<IObserver*>(
			widgetParent->QueryParentFor(IID_ICUSDTLNKUIWIDGETOBSERVER)));

		if(ourObserver) {
			retval = kTrue;
			break;
		}
		

	} while(kFalse);
	return retval;
}

//	end, File: CusDtLnkUITreeTVWidgetMgr.cpp
