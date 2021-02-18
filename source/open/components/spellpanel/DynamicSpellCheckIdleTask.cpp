//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DynamicSpellCheckIdleTask.cpp $
//  
//  Owner: Heath Horton
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

#include "IApplication.h"
#include "IComposeScanner.h"
#include "IConcreteSelection.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IGalleyUtils.h"
#include "IGraphicsPort.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutController.h"
#include "IPanelControlData.h"
#include "IRangeData.h"
#include "ISelectionUtils.h"
#include "ISession.h"
#include "ISpellingUtils.h"
#include "IPrivateSpellingUtils.h"
#include "IStoryRefData.h"
#include "ITextFocus.h"
#include "ITextMiscellanySuite.h"
#include "ITextModel.h"
#include "ITextTrackerAccess.h"
#include "IDocumentPresentation.h"
#include "IDocumentUIUtils.h"
#include "IWorkspace.h"

#include "K2SmartPtr.h"
#include "CIdleTask.h"
#include "GraphicsData.h"
#include "keyboarddefs.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "PMTextUtils.h"
#include "ISelectionUtils.h"
#include "SpellPanelID.h"
#include "SystemUtils.h"
#include "TextID.h"
#include "TransformUtils.h"
#include "UnicodeClass.h"
#include "WritingModeUIID2.h"
	
#include "Trace.h"

#if DEBUG
extern bool16 gPaintInvalRect;
#endif

//----------------------------------------------------------------------------------------
// CLASS DynamicSpellCheckTypingIdleTask 
//----------------------------------------------------------------------------------------
class DynamicSpellCheckTypingIdleTask : public CIdleTask
{
public:
	DynamicSpellCheckTypingIdleTask(IPMUnknown *boss);
	~DynamicSpellCheckTypingIdleTask();
	
	virtual uint32 		RunTask(uint32 appFlags, IdleTimer* timeCheck);
	virtual const char* TaskName();

	virtual void InstallTask(uint32 millisecsBeforeFirstRun);
	virtual void UninstallTask();

private:
	void 		DoTask();

	IDocumentPresentation* 	fWindow;
};


CREATE_PMINTERFACE(DynamicSpellCheckTypingIdleTask, kDynamicSpellCheckTypingIdleTaskImpl);


//----------------------------------------------------------------------------------------
// DynamicSpellCheckTypingIdleTask constructor 
//----------------------------------------------------------------------------------------
DynamicSpellCheckTypingIdleTask::DynamicSpellCheckTypingIdleTask(IPMUnknown *boss) :
	CIdleTask(boss),
		fWindow(nil)
{
}

DynamicSpellCheckTypingIdleTask::~DynamicSpellCheckTypingIdleTask()
{
}

void DynamicSpellCheckTypingIdleTask::InstallTask(uint32 millisecsBeforeFirstRun)
{
#ifdef DEBUG
	TRACEFLOW_OBSOLETE("DSC", "DynamicSpellCheckTypingIdleTask::InstallTask -- Disabling the adornment(s)\n");
#endif

	fWindow = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();

	InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<ITextMiscellanySuite> textMiscellanySuite(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, selectionManager)));
	if (textMiscellanySuite)
	{
		InterfacePtr<IIntData> intData(this, UseDefaultIID());
		SysChar c = 0;
		if (intData)
		{
			c = intData->Get();
		}
		textMiscellanySuite->SetWorkSpaceTypingRangeData(c, IID_IDYNAMICSPELLINGRANGEDATA);
	}

	CIdleTask::InstallTask(millisecsBeforeFirstRun);
}

void DynamicSpellCheckTypingIdleTask::UninstallTask()
{
#ifdef DEBUG
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	TRACEFLOW_OBSOLETE("DSC", "DynamicSpellCheckTypingIdleTask::UninstallTask\n");
#endif

	CIdleTask::UninstallTask();
}

//FW:Denali:source:components:ToolBox:PopOutMouseTrackThread.cpp

//----------------------------------------------------------------------------------------
// DynamicSpellCheckTypingIdleTask::DoTask
// This invalidates the region associated with the text range in this idle task
//----------------------------------------------------------------------------------------
void DynamicSpellCheckTypingIdleTask::DoTask()
{
#ifdef DEBUG
	TRACEFLOW_OBSOLETE("DSC", "DynamicSpellCheckTypingIdleTask::DoTask\n");
#endif
			
	InterfacePtr<IWorkspace> ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IRangeData> rangeData(ws, IID_IDYNAMICSPELLINGRANGEDATA);
	
	int32 typingStart = rangeData->GetStart();
	int32 typingEnd = rangeData->GetEnd();

	IDocumentPresentation* window = Utils<IDocumentUIUtils>()->GetActiveDocumentPresentation();

	if (fWindow != window)
	{
#ifdef DEBUG
		TRACEFLOW_OBSOLETE("DSC", "IdleTask installed with different window than runTask\n");
#endif
		window = fWindow; // FIXME_OWL2: Ack!
		return; //fWindow could be bogus (if it closed before the task ran) TODO: set up observer which will remove idle task when window is closed.
	}
	
	/* reset the range so the adornment draws all */
	rangeData->Set(kInvalidTextIndex, kInvalidTextIndex);

	PMRect invalRect;
	ITextModel* textModel = nil;
	IControlView* writingView = nil;
	
	if (window && Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(window))
	{
		InterfacePtr<IPanelControlData> panelData(window, IID_IPANELCONTROLDATA);
		writingView = panelData->FindWidget(kWritingId);
		if (writingView != nil)
		{
			InterfacePtr<IStoryRefData> storyRefData(writingView, IID_ISTORYREFDATA);
			ASSERT(storyRefData != nil);

			InterfacePtr<ITextModel> model(storyRefData->GetStoryRef(), IID_ITEXTMODEL);

			textModel = model;
			ASSERT(textModel != nil);
			textModel->AddRef();
		}
		else
			return;
	}
	else
	{
		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());
		InterfacePtr<ITextTrackerAccess> tta( selMgr, UseDefaultIID());
		if (!tta)
			return;
		InterfacePtr<ITextFocus> focus (tta->QueryTextFocus());
		if (!focus)
			return;
		textModel = focus->QueryModel();
		if (! textModel)
			return;
	}

	if (textModel)
	{
		int32 storyLength = textModel->TotalLength();

		/* It may be possible the model is now shorter than the range set by the idle task */
		if (typingStart >= storyLength)
			typingStart = storyLength - 1;
		if (typingStart < 0)
			typingStart = 0;
		if (typingEnd >= storyLength)
			typingEnd = storyLength - 1;
		if (typingEnd < 0)
			typingEnd = 0;

		Utils<IPrivateSpellingUtils>()->InvalTextRange(nil, textModel, typingStart, typingEnd);
	
		textModel->Release();
		textModel = nil;
	}

}

uint32 DynamicSpellCheckTypingIdleTask::RunTask(uint32 appFlags, IdleTimer* timeCheck)
{
	DoTask();
	
	/* One and done */
	this->UninstallTask();
	
	return 0;
}

const char* DynamicSpellCheckTypingIdleTask::TaskName()
{
	return "DynamicSpellCheckTypingIdleTask";
}
