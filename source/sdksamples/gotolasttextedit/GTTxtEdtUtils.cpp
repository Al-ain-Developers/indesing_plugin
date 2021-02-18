//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtUtils.cpp $
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
#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IWindow.h"
#include "ITool.h"
#include "ISelectionManager.h"
#include "IToolBoxUtils.h"
#include "ITextSelectionSuite.h"
#include "ITextModel.h"

// General includes:
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "ErrorUtils.h"
#include "RangeData.h"
#include "K2Vector.h"
#include "K2Assert.h"
#include "CPMUnknown.h"
#include "TextChar.h"
#include "TextEditorID.h"	// kIBeamToolBoss


// Project includes:
#include "GTTxtEdtID.h"
#include "IGTTxtEdtUtils.h"

/** Utility functionality for the GoTo plug-in

@ingroup gotolasttextedit
*/
class GTTxtEdtUtils : public CPMUnknown<IGTTxtEdtUtils>
{
public:
	/** Constructor.
	*/
	GTTxtEdtUtils(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~GTTxtEdtUtils();

	/** Activates the nominated story at the specified position. 
	Activating a story will enable the text editor.
	@param pSelectionManager IN the active selection manager.
	@param storyUIDRef IN the story that is to be activated.
	@param storyIndex IN the position the caret is set to.
	*/
	void ActivateStory(ISelectionManager* pSelectionManager, UIDRef storyUIDRef,int32 storyIndex = 0);

};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(GTTxtEdtUtils, kGTTxtEdtUtilsImpl)

/*
*/
GTTxtEdtUtils::GTTxtEdtUtils(IPMUnknown* boss) : CPMUnknown<IGTTxtEdtUtils>(boss)
{
}

/*
*/
GTTxtEdtUtils::~GTTxtEdtUtils()
{
}


/*
*/
void GTTxtEdtUtils::ActivateStory(ISelectionManager* pSelectionManager, UIDRef storyUIDRef, int32 storyIndex)
{
	do {

		InterfacePtr<ITextModel> textModel(storyUIDRef, IID_ITEXTMODEL);
		if (!textModel)
			break;

		int32 length = textModel->TotalLength();
		if (storyIndex>= length)
			storyIndex = length -1; // reset text index if it is out of range



		// Deselect everything.
		pSelectionManager->DeselectAll(nil); // deselect every active CSB


		// select the text edit tool
		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (activeTool->IsTextTool() == kFalse) {
			InterfacePtr<ITool> iBeamTool(Utils<IToolBoxUtils>()->QueryTool(kIBeamToolBoss));
			ASSERT(iBeamTool);
			if (iBeamTool == nil) {
				break;
			}
			if (Utils<IToolBoxUtils>()->SetActiveTool(iBeamTool) == kFalse){
				break;
			}
		}


		// Make a text selection to set the text caret blinking at the start of the story.
		InterfacePtr<ITextSelectionSuite> iTextSelectionSuite(pSelectionManager, UseDefaultIID());
		if (iTextSelectionSuite == nil) {
			break;
		}
		if(iTextSelectionSuite->SetTextSelection(storyUIDRef, RangeData(storyIndex, RangeData::kLeanForward),Selection::kScrollIntoView, nil) == kFalse){
			break;
		}
	}while (kFalse);
}



// End, GTTxtEdtUtils.cpp

