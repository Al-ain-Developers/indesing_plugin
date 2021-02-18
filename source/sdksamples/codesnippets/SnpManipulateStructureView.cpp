//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateStructureView.cpp $
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
#include "IActionManager.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "IDocument.h"
#include "IDocumentPresentation.h"
#include "IPanelControlData.h"
#include "ISelectionUtils.h"
#include "IWidgetParent.h"
#include "IDocumentPresentation.h"
#include "IDocumentUIUtils.h"
#include "IWorkspace.h"
#include "IXMLNodeSelectionSuite.h"


// General includes:
#include "ErrorUtils.h"
#include "SnpRunnable.h"
#include "ISnpRunnableContext.h"
#include "ISnipRunParameterUtils.h"
#include "SnpXMLHelper.h"
#include "SnipRunLog.h"

// Project includes


/** Manipulate the state of the structure-view:
	\li query or set selections in the structure-view 
	\li query visibility and change visibility.

	These methods mainly take IActiveContext, implicitly meaning they are likely to 
	be useful when writing your user interface, that is, client code.

  	@ingroup sdk_snippet
	@ingroup sdk_xmedia
	@see _SnpRunnerManipulateStructureView::Run for driver code

 */
class SnpManipulateStructureView
{
public:

	/**	Show or hide the structure-view
		@param activeContext specifies current active context 
		@param setVisible kTrue to show, kFalse to hide
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ChangeStructureViewState(IActiveContext* activeContext, bool16 setVisible);

	/**	Determine if nodes are selected in the structure-view
		@param activeContext specifies current active context 
		@return bool16 indicating whether there's node(s) selected in structure view
	 */
	bool16 IsStructureViewSelectionNonEmpty(IActiveContext* activeContext);

	/** Determine if structure-view window is showing
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@return kTrue if visible, kFalse if not
	*/
	bool16 IsStructureViewShowing(const UIDRef& documentUIDRef);

	/**	Set a selection in the structure-view explicitly
		@precondition xmlReference should allow IIDXMLElement to be instantiated
		@param activeContext specifies current active context 
		@param xmlReference specifies the element to select
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode SetExplicitStructureViewSelection(IActiveContext* activeContext, const XMLReference& xmlReference);

	/**	Explicitly set the root element in the structure-view to be selected.
		@param activeContext specifies current active context 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode SetExplicitStructureViewRootSelected(IActiveContext* activeContext);

};

/*
*/
bool16 SnpManipulateStructureView::IsStructureViewShowing(const UIDRef& documentUIDRef)
{
	bool16 retval = kFalse;
	do{
		// precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		IDocumentPresentation* docWindow = Utils<IDocumentUIUtils>()->GetFrontmostPresentationForDocument(documentUIDRef.GetDataBase());
		if(!docWindow) {
			// Perhaps we have no windows open onto this document;
			// probably an assert is not required here, just returning false is enough
			break;
		}		
		InterfacePtr<IBoolData>	structureIsShown( docWindow, IID_ISTRUCTUREISSHOWNBOOLDATA );
		ASSERT(structureIsShown);
		if(!structureIsShown) {
			break;
		}
		retval = (structureIsShown->GetBool());
	} while(kFalse);
	return retval;
}
		

/*
*/
ErrorCode SnpManipulateStructureView::ChangeStructureViewState(IActiveContext* activeContext, 
														  bool16 setVisible)
{
	ErrorCode err = kFailure;
	do {
		UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
		bool16 isStructureViewShowing = this->IsStructureViewShowing(documentUIDRef);
		if(isStructureViewShowing == setVisible) { 
			break;
		}
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IActionManager> actionManager(app->QueryActionManager());
		ASSERT(actionManager);
		if(!actionManager) {
			break;
		}
		actionManager->PerformAction(activeContext, kOpenStructureWinActionID);
		// If the action failed, hope someone set the err code
		err = ErrorUtils::PMGetGlobalErrorCode();
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateStructureView::SetExplicitStructureViewSelection(IActiveContext* activeContext, 
														   const XMLReference& xmlReference)
{
	ErrorCode result = kFailure;
	do {
		ASSERT(activeContext);
		if(!activeContext) {
			break;
		}
		
		IControlView* selectionView = activeContext->GetContextView();
		ASSERT(selectionView);
		if(!selectionView) {
			break;
		}
		SnpXMLHelper xmlHelper;
		PMString selectionViewClass = xmlHelper.GetClassFrom(::GetClass(selectionView));
		SNIPLOG("SelectionViewClass = %s\n", selectionViewClass.GetPlatformString().c_str());
		InterfacePtr<IWidgetParent> widgetParent(selectionView, UseDefaultIID());
		ASSERT(widgetParent);
		if(!widgetParent) {
			break;
		}
		InterfacePtr<IDocumentPresentation> docWindow( (IDocumentPresentation*)widgetParent->QueryParentFor(IID_IDOCUMENTPRESENTATION));
		// Could be we're not in a layout view
		if(!docWindow) {
			break;
		}
		PMString docPresentationClass = xmlHelper.GetClassFrom(::GetClass(docWindow));
		SNIPLOG("docPresentationClass = %s\n", docPresentationClass.GetPlatformString().c_str());
		InterfacePtr<IPanelControlData> docPanelData(docWindow, UseDefaultIID());
		if (!docPanelData) {
			break;
		}
	
		this-> ChangeStructureViewState(activeContext, kTrue);
		
	
		IControlView* structureView = docPanelData->FindWidget(kXMLPanelWidgetID);
		if(!structureView) {
			break;
		}
		Utils<ISelectionUtils>()->ActivateView(structureView);
		// This isn't the same as our context selection manager
		InterfacePtr<ISelectionManager>	selectionMgr(
			Utils<ISelectionUtils>()->QueryViewSelectionManager(structureView));
		
		InterfacePtr<IXMLNodeSelectionSuite> 
			xmlNodeSelectionSuite(selectionMgr, UseDefaultIID());
		ASSERT(xmlNodeSelectionSuite);
		if(!xmlNodeSelectionSuite) {
			break;
		}	
		if(kInvalidXMLReference == xmlReference) {
			xmlNodeSelectionSuite->DeselectAll();
		} else {
			xmlNodeSelectionSuite->SelectElement(xmlReference, 
												Selection::kAddTo);
		}
		result = kSuccess;
	} while(kFalse);
	return result;

}

/*
*/
ErrorCode SnpManipulateStructureView::SetExplicitStructureViewRootSelected(IActiveContext* activeContext)
{
	ErrorCode retval = kFailure;
	do {
		SnpXMLHelper xmlHelper;
		XMLReference rootXMLRef  = xmlHelper.GetRootXMLReference(::GetUIDRef(activeContext->GetContextDocument()));
		retval = this->SetExplicitStructureViewSelection(activeContext, rootXMLRef);
	} while(kFalse);
	return retval;
}

/*
*/
bool16 SnpManipulateStructureView::IsStructureViewSelectionNonEmpty(IActiveContext* activeContext)
{
	bool16 hasSelection = kFalse;
	do {
		ISelectionManager *selectionManager = activeContext->GetContextSelection();
		if (!selectionManager) {
			break;
		}
		// Have we an existing selection? If we have then we should be able to
		// get an IXMLNodeSelectionSuite from the selection manager
		InterfacePtr<IXMLNodeSelectionSuite> xmlSelection(selectionManager, UseDefaultIID());
		if(xmlSelection != nil && (!xmlSelection->IsEmpty())) {
			hasSelection = kTrue;
		}
	} while(kFalse);

	return hasSelection;
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateStructureView available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateStructureView : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateStructureView();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateStructureView();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
	
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateStructureView::_SnpRunnerManipulateStructureView() : SnpRunnable("ManipulateStructureView")
{
	this->SetDescription("Manipulate structure view visibility, node selections etc.");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");}

/* Destructor.
*/
_SnpRunnerManipulateStructureView::~_SnpRunnerManipulateStructureView()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateStructureView::CanRun(ISnpRunnableContext* runnableContext)
{
		bool16 result = kFalse;
	do {
		ASSERT(runnableContext->GetActiveContext()); 
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		return document != nil;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateStructureView::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode err = kCancel;
	IActiveContext* activeContext = runnableContext->GetActiveContext();
	UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
	SnpManipulateStructureView instance;
	SnpXMLHelper xmlHelper;
	XMLReference rootXMLRef = xmlHelper.GetRootXMLReference(documentUIDRef);
	

	do {

		K2Vector<PMString> choices;
		choices.push_back(PMString("ChangeStructureViewState (toggle)")); //0
		choices.push_back(PMString("SetExplicitStructureViewSelection (root)")); //1
	
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		switch(choice) {
			case 0:
			{
				SNIPLOG("ChangeStructureViewState (toggle)");
				bool16 showing = instance.IsStructureViewShowing(documentUIDRef);
				instance.ChangeStructureViewState(activeContext, !showing);
			} 
			break;


			case 1:
			{
				SNIPLOG("SetExplicitStructureViewSelection (root)");
				instance.ChangeStructureViewState(activeContext, kTrue);
				instance.SetExplicitStructureViewSelection(activeContext, rootXMLRef);
			}
			break;

		} // end of switch
		 
	} while(kFalse);

	return kSuccess;
}


/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateStructureView instance_SnpRunnerManipulateStructureView;
DEFINE_SNIPPET(_SnpRunnerManipulateStructureView) 	
