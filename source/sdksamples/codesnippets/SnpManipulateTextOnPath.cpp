//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextOnPath.cpp $
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
#include "ILayoutTarget.h"
#include "ITextModel.h"
#include "IMainItemTOPData.h"
#include "ITOPSplineData.h"
#include "IPathGeometry.h"
#include "ITOPSplineData.h"
#include "IBoolData.h"
#include "ITextModelCmds.h"
#include "ITOPFrameData.h"
#include "IPageItemTypeUtils.h"
#include "ITextFrameColumn.h"

// General includes:
#include "TextOnPathID.h"
#include "Utils.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "PersistUtils.h"
#include "UIDRef.h"
#include "LocaleSetting.h"

// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpTextModelHelper.h"

/** \li How to add text on a path to a spline,
	\li how to remove text on a path from a spline,
	\li how to find the story associated with text on a path
		and insert text into it.

  	@ingroup sdk_snippet
	@ingroup sdk_text

*/
class SnpManipulateTextOnPath 
{
public:
	/** Constructor.
	*/
	SnpManipulateTextOnPath() {}

	/** Destructor
	*/
	virtual ~SnpManipulateTextOnPath() {}
	/** Return kTrue if text on a path can be associated with the spline, kFalse otherwise.
		@return kTrue if text on a path can be associated with the spline, kFalse otherwise.
		*/
 	bool16 CanAddTextOnPath(const UIDRef& splineUIDRef);
 	
 	/** Adds text on a path to the spline.
 		@return kSuccess on success, kFailure otherwise.
 		*/
	ErrorCode AddTextOnPath(const UIDRef& splineUIDRef);
	
	/** Return kTrue if the spline has text on a path associated and it can be deleted.
		@return kTrue if the spline has text on a path associated and it can be deleted.
		*/
 	bool16 CanDeleteTextOnPath(const UIDRef& splineUIDRef);

 	/** Remove text on a path from the spline.
 		@return kSuccess on success, kFailure otherwise.
 		*/ 		
	ErrorCode DeleteTextOnPath(const UIDRef& splineUIDRef);
	
	/** Insert the given data string into the story associated with the 
		text on a path that is associated with the given spline.
		*/
	ErrorCode InsertTextIntoTextOnPath(const UIDRef& splineUIDRef, const boost::shared_ptr<WideString>& data);

};

/*
*/
bool16 SnpManipulateTextOnPath::CanAddTextOnPath(const UIDRef& splineUIDRef)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<IMainItemTOPData> mainItemTOPData(splineUIDRef, UseDefaultIID());
		if (!mainItemTOPData) {
			break;
		}
		if (mainItemTOPData->GetTOPSplineItemUID() != kInvalidUID) {
			// This spline already has text on path associated.
			break;
		}

		// There are some constraints to the kind of path
		// text on a path can be applied to. Check them.
		InterfacePtr<IPathGeometry> pathGeometry(mainItemTOPData, UseDefaultIID());
		if (!pathGeometry) {
			break;
		}
		if (pathGeometry->GetNumPaths() != 1) {
			// Can't add text on a path to a compound path or empty path.
			break;
		}
		if (pathGeometry->GetNumSegments(0) == 0) {
			// Can't add text on a path to a single point path.
			break;
		}
		Utils<IPageItemTypeUtils> pageItemTypeUtils;
		if (pageItemTypeUtils->IsInline(pathGeometry)) {
			// Can't add text on a path to inlines.
			break;
		}

		// If we get here text on a path can be added.
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextOnPath::AddTextOnPath(const UIDRef& splineUIDRef)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ICommand> addTextOnPathCmd(CmdUtils::CreateCommand(kAddTextOnPathCmdBoss));
		ASSERT(addTextOnPathCmd);
		if (!addTextOnPathCmd) {
			break;
		}
		InterfacePtr<IBoolData> defaultCreation(addTextOnPathCmd, UseDefaultIID());
		ASSERT(defaultCreation);
		if (!defaultCreation) {
			break;
		}
		defaultCreation->Set(kTrue);
		addTextOnPathCmd->SetItemList(UIDList(splineUIDRef));
		result = CmdUtils::ProcessCommand(addTextOnPathCmd);
		ASSERT_MSG(result == kSuccess, "kAddTextOnPathCmdBoss failed");
	} while(false);
	return result;
}

/*
*/
bool16 SnpManipulateTextOnPath::CanDeleteTextOnPath(const UIDRef& splineUIDRef)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<IMainItemTOPData> mainItemTOPData(splineUIDRef, UseDefaultIID());
		if (!mainItemTOPData) {
			break;
		}
		if (mainItemTOPData->GetTOPSplineItemUID() == kInvalidUID) {
			// This spline does not have any text on path associated.
			break;
		}

		// If we get here text on a path can be deleted.
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextOnPath::DeleteTextOnPath(const UIDRef& splineUIDRef)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<ICommand> topDeleteCmd(CmdUtils::CreateCommand(kTOPDeleteCmdBoss));
		if (! topDeleteCmd) {
			break;
		}
		topDeleteCmd->SetItemList(UIDList(splineUIDRef));
		result = CmdUtils::ProcessCommand(topDeleteCmd) ;
		ASSERT_MSG(result == kSuccess, "kTOPDeleteCmdBoss failed");
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpManipulateTextOnPath::InsertTextIntoTextOnPath(const UIDRef& splineUIDRef, const boost::shared_ptr<WideString>& data)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<IMainItemTOPData> mainItemTOPData(splineUIDRef, UseDefaultIID());
		if (!mainItemTOPData) {
			break;
		}
		if (mainItemTOPData->GetTOPSplineItemUID() == kInvalidUID) {
			// This spline does not have text on path associated.
			break;
		}
		InterfacePtr<ITOPFrameData> topFrameData(mainItemTOPData->QueryTOPFrameData());
		if (!topFrameData) {
			break;
		}
		InterfacePtr<ITextFrameColumn> textFrameColumn(topFrameData, UseDefaultIID());
		if (!textFrameColumn) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textFrameColumn->QueryTextModel());
		if (!textModel) {
			break;
		}
		SnpTextModelHelper	textCmdHelper;
		result = textCmdHelper.InsertText(textModel, 0, data);
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerManipulateTextOnPath : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		_SnpRunnerManipulateTextOnPath();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateTextOnPath();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if a document is open, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/**	Don't present this snippet in the framework's UI if the
			product we are running under is InCopy. 
			@return kTrue if the snippet can be loaded, kFalse otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}
};
/* Constructor
*/
_SnpRunnerManipulateTextOnPath::_SnpRunnerManipulateTextOnPath() : SnpRunnable("ManipulateTextOnPath")
{
	this->SetDescription("manipulates text on a path");
	this->SetPreconditions("layout selection of a spline");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
_SnpRunnerManipulateTextOnPath::~_SnpRunnerManipulateTextOnPath()
{
}

/*
*/
bool16 _SnpRunnerManipulateTextOnPath::CanRun(ISnpRunnableContext* runnableContext)
{
	bool result = kFalse;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}	
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/* 
*/
ErrorCode _SnpRunnerManipulateTextOnPath::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextOnPath instance;
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}	
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			SNIPLOG("Please select a frame");
			break;
		}
		UIDRef splineUIDRef = itemList.GetRef(0);
		
		// Ask which operation is wanted.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Add text on path"));
		choices.push_back(PMString("Delete text on path"));

		enum {kAddTextOnPath, kDeleteTextOnPath};
		int32 choice  = parameterUtils->GetChoice("operation?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Perform the operation.
		switch (choice) 
		{		
		case kAddTextOnPath:
			{
				if (instance.CanAddTextOnPath(splineUIDRef) == kFalse) {
					SNIPLOG("Can't add text on path to this frame");
					break;
				}
				status = instance.AddTextOnPath(splineUIDRef);
				if (status != kSuccess) {
					break;
				}
				boost::shared_ptr<WideString> data(new WideString("Text on a path"));
				status = instance.InsertTextIntoTextOnPath(splineUIDRef, data);
				break;
			}

		case kDeleteTextOnPath:
			{
				if (instance.CanDeleteTextOnPath(splineUIDRef) == kFalse) {
					SNIPLOG("Please choose a spline that has text on a path associated");
					break;
				}
				status = instance.DeleteTextOnPath(splineUIDRef);
				break;
			}
		default:
			{
				break;
			}
		}
	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerManipulateTextOnPath::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		// Text on a path can be applied to page items under InCopy
		// but we don't load this snippet because there's no pointer tool 
		// to select a page item with. If we loaded the Go button for the
		// snippet would pretty much always be disabled and we couldn't test it.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTextOnPath instance_SnpRunnerManipulateTextOnPath;
DEFINE_SNIPPET(_SnpRunnerManipulateTextOnPath) 	

//End, SnpManipulateTextOnPath.cpp
