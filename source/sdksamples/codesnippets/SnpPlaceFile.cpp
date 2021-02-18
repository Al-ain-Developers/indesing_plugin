//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPlaceFile.cpp $
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
#include "IActiveContext.h"
#include "IDocument.h"
#include "IControlView.h"
#include "ILayoutControlData.h"
#include "IDataBase.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"

// General includes:
#include "Utils.h"
#include "PMRect.h"

// SDK includes:
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	How to place a file in a frame. 
	
	This snippet code illustrates how to place various files (Importable Files)
	into InDesign document. By calling SDKLayoutHelper::PlaceFileInFrame(), the
	details of import process are encapsulated. This sample will bring up 
	a dialog that allows you to choose a file to Import, such as text, incopy file,
	snippet, images, and InDesign documents.


  	@ingroup sdk_snippet

	@see SDKLayoutHelper
 */
class SnpPlaceFile 
{
	public:

		/** Constructor.
		 */
		SnpPlaceFile() {}

		/** Destructor.
		 */
		virtual			~SnpPlaceFile() {}

		/** Allow the user to choose a file using a place file browse dialog,
			then place the file in a frame.
			@param layoutControlData
			@param selectedItemRef TODO enhance snippet so that if there is a selection the placed file
					will replace the selected item.
			@return kSuccess on success, kCancel on cancel, other ErrorCode otherwise.
		 */
		ErrorCode	PlaceViaHelper(ILayoutControlData* layoutControlData, const UIDRef& selectedItemRef);

	
};


/*
*/
ErrorCode SnpPlaceFile::PlaceViaHelper(ILayoutControlData* layoutControlData, const UIDRef& selectedItemRef)
{
	ErrorCode result = kCancel;
	SDKLayoutHelper layoutHelper;
	do {

		// Choose a file to be placed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		SDKFilePlaceChooser fileChooser; //change to ISnipRunParameterUtils once it supports IDFile parameters
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}

		// Assume we failed till we know we succeeded.
		result = kFailure;

		// Parent the frame on the active spread layer.
		InterfacePtr<IHierarchy> activeSpreadLayerHierarchy(layoutControlData->QueryActiveLayer());
		ASSERT(activeSpreadLayerHierarchy != nil);
		if (activeSpreadLayerHierarchy == nil) {
			break;
		}
		UIDRef parentUIDRef = ::GetUIDRef(activeSpreadLayerHierarchy);

		// Transform the bounds of the frame from page co-ordinates
		// into the parent co-ordinates, i.e. the spread.
		ASSERT(layoutControlData->GetPage() != kInvalidUID);
		if (layoutControlData->GetPage() == kInvalidUID) {
			break;
		}
		UIDRef pageUIDRef(parentUIDRef.GetDataBase(), layoutControlData->GetPage());
		PMRect boundsInPageCoords(0,0,100,100); // hard wire for now.
		PMRect boundsInParentCoords = layoutHelper.PageToSpread(pageUIDRef, boundsInPageCoords);

		// Place the file in a frame.
		UIFlags uiFlags = K2::kMinimalUI;
		if (fileChooser.GetShowFilterPrefs()) {
			uiFlags = K2::kFullUI;
		}
		UIDRef frameRef = layoutHelper.PlaceFileInFrame(fileChooser.GetIDFile(),
						parentUIDRef,
						boundsInParentCoords,
						uiFlags, 
						fileChooser.GetRetainFormat(),
						fileChooser.GetConvertQuotes(), 
						fileChooser.GetApplyCJKGrid());

		// TODO add code that looks at SDKFilePlaceChooser::GetReplaceSelectedItem
		// and replaces the content of the frame indicated by selectedItemRef.

		result = kSuccess;
	} while(false);
	return result;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerPlaceFile : public SnpRunnable
{

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerPlaceFile();

		/** Destructor.
		 */
		virtual			~_SnpRunnerPlaceFile();

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


/* Constructor.
*/
_SnpRunnerPlaceFile::_SnpRunnerPlaceFile() : SnpRunnable("PlaceFile")
{
	this->SetDescription("Places a file in a new frame in the active document");
	this->SetPreconditions("layout view");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerPlaceFile::~_SnpRunnerPlaceFile()
{
}

/*
*/
bool16	_SnpRunnerPlaceFile::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (!layoutControlData) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode _SnpRunnerPlaceFile::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpPlaceFile instance;
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (!layoutControlData) {
			break;
		}

		// If a single item is selected pass a reference to it to PlaceViaHelper.
		UIDRef selectedItemRef = UIDRef::gNull;
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget) {
			UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
			if (itemList.Length() == 1) {
				selectedItemRef = itemList.GetRef(0);
			}
		}

		status = instance.PlaceViaHelper(layoutControlData, selectedItemRef);
		if (status == kCancel) {
			SNIPLOG("The place operation was cancelled");
			status = kSuccess;
		}

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPlaceFile instance_SnpRunnerPlaceFile;
DEFINE_SNIPPET(_SnpRunnerPlaceFile) 	

// End, SnpPlaceFile.cpp

