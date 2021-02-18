//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpFillTextFrame.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "IPageItemTypeUtils.h"
#include "ITextMiscellanySuite.h"
#include "ISelectionUtils.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

class SnpFillTextFrame : public SnpRunnable
{
	public:
		ErrorCode	FillTextFrame( const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager, int32 script);
		bool16		IsTextFrame(const UIDRef& graphicFrameUIDRef);

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		SnpFillTextFrame();

		/** Destructor
		*/
		virtual ~SnpFillTextFrame();

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

		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}

};

ErrorCode SnpFillTextFrame::FillTextFrame( const UIDRef& graphicFrameUIDRef, ISelectionManager* selectionManager, int32 script)
{
	ErrorCode status = kFailure;
	do {
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}
		if (selectionManager == nil) {
			break;
		}
		
		
		InterfacePtr<ITextMiscellanySuite> textMiscellanySuite(selectionManager, UseDefaultIID());
		if (!textMiscellanySuite) {
			// The selection manager does not support text selection. Might
			// be the selection manager for a structure view for example.
			break;
		}

		status = textMiscellanySuite->FillWithPlaceHolderText(script);

	} while(false);
	return status;	
}

bool16 SnpFillTextFrame::IsTextFrame(const UIDRef& graphicFrameUIDRef)
{
	bool16 result = kFalse;
	Utils<IPageItemTypeUtils> pageItemTypeUtils;
	if (pageItemTypeUtils && pageItemTypeUtils->IsTextFrame(graphicFrameUIDRef)) {
		result = kTrue;
	}
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor
*/
SnpFillTextFrame::SnpFillTextFrame() : SnpRunnable("FillTextFrame")
{
	this->SetDescription("Fill text frame with text");
	this->SetPreconditions("Frame selected");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
SnpFillTextFrame::~SnpFillTextFrame()
{
}

/*
*/
bool16 SnpFillTextFrame::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			break;
		}
		if (this->IsTextFrame(itemList.GetRef(0)) == kFalse) {
			break;
		}

		// If we get here a layout selection exists of a single frame
		// and that frame has text content.
		result = kTrue;
	} while(false);
	return result;
}

/* 
*/
ErrorCode SnpFillTextFrame::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		// Find the selected text frame.
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			SNIPLOG("Please select a text frame");
			break;
		}
		UIDRef graphicFrameUIDRef = itemList.GetRef(0);
		if (this->IsTextFrame(graphicFrameUIDRef) == kFalse) {
			SNIPLOG("Please select a text frame");
			break;
		}

		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> names;
		names.push_back("Roman");
		names.push_back("Cyrillic");
		names.push_back("Greek");
		names.push_back("Arabic");
		names.push_back("Hebrew");
		enum { kArabic, kCyrillic, kRoman, kGreek, kHebrew };
		int32 langue  = parameterUtils->GetChoice("Choose the language of the text you want to fill.", names);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		int32 script;
		switch (langue)
		{
		case 0:
			script = 0; break;
		case 1:
			script = 7; break;
		case 2:
			script = 6; break;
		case 3:
			script = 4; break;
		case 4:
			script = 5; break;
		default:
			script = 0; break;
		}

		status = this->FillTextFrame( graphicFrameUIDRef, runnableContext->GetActiveContext()->GetContextSelection(), script);

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpFillTextFrame instanceSnpFillTextFrame;

//End, SnpFillTextFrame.cpp
