//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkCaptionActionComponent.cpp $
//  
//  Owner: lance bushore
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

// Interfaces:
#include "IActionStateList.h"
#include "ILinksUIUtils.h"
#include "IGenerateCaptionCmdData.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IApplication.h"
#include "IFrameType.h"
#include "ISelectionUtils.h"
#include "ILinkUtils.h"
#include "IDocument.h"
#include "IActiveContext.h"
#include "ILink.h"
#include "IPageItemTypeUtils.h"
#include "IMediaUtils.h"
#include "ICaptionSelectionSuite.h"
#include "ITextEditSuite.h"
#include "ITableUtils.h"

// Includes:
#include "CActionComponent.h"
#include "LinksUIID.h"
#include "Utils.h"
#include "UIDList.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "LinksUIResDefs.h"
#include "RsrcSpec.h"
#include "ErrorUtils.h"
#include "CAlert.h"
#include "ActionStateList.h"
#include "TextEditorActionID.h"
#include "MovieID.h"

class LinkCaptionActionComponent : public CActionComponent
{
public:
	LinkCaptionActionComponent(IPMUnknown *boss) : CActionComponent(boss)
		{}
	
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

private:
	void InvokeGenerateCaptionPrefsDialog() const;
	void GenerateCaptionForPageItems(const UIDList& pageItems, bool makeLiveCaption) const;

};

CREATE_PMINTERFACE(LinkCaptionActionComponent, kLinkCaptionActionComponentImpl)

static UIDList GetLinkedPageItemsForCaptionsFromLinksPanelSelection(IPMUnknown* widget)
{
	UIDList linksSelectedInPanel = Utils<ILinksUIUtils>()->GetLinksForMenuAction(widget);
	IDataBase* docDB = linksSelectedInPanel.GetDataBase();
	UIDList targetPageItems(docDB);
	for(int i = linksSelectedInPanel.Length() -1; i >= 0; --i)
	{
		InterfacePtr<const ILink> link(linksSelectedInPanel.GetRef(i),UseDefaultIID());
		UIDRef linkedObject(docDB,link->GetObject());

		if(!Utils<IPageItemTypeUtils>()->IsInline(linkedObject) && !Utils<ITableUtils>()->IsTableCellContent(linkedObject))
		{
			if(Utils<IPageItemTypeUtils>()->IsGraphic(linkedObject) || Utils<IMediaUtils>()->IsMediaItem( kMoviePageItemBoss, linkedObject.GetUID(),  docDB ))
				targetPageItems.push_back(link->GetObject());
		}
	}
	return targetPageItems;
}

static bool CanGenerateStaticCaption(const UIDList& items)
{
	for(int i = items.Length() -1; i >= 0; --i)
	{
		if(Utils<ILinkUtils>()->FindLink(items.GetRef(i)) != kInvalidUID)
			return true;
	}
	return false;
}


void LinkCaptionActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(mousePoint)

	InterfacePtr<const ICaptionSelectionSuite> captionSuite (ac->GetContextSelection(), UseDefaultIID());
	UIDList selectedGraphicFrames;
	if(captionSuite)
		selectedGraphicFrames =	captionSuite->GetUIDsSuitableForCaptioning();

	//
	// If any of the selected item is a graphic cell page item, then block caption generation
	//
	bool16 allowCaption = kTrue;

	for(int32 i = 0; i <selectedGraphicFrames.Length(); ++i)
	{
		if(Utils<ITableUtils>()->IsTableCellContent(selectedGraphicFrames.GetRef(i)))
		{
			allowCaption = kFalse;
			break;
		}
	}
	
	const int32 nCount = listToUpdate->Length();

	for (int32 i = 0; i < nCount; i++)
	{
		ActionID nAction = listToUpdate->GetNthAction(i);

		switch (nAction.Get())
		{
			case kGenerateLiveCaptionForLinkSelectionActionID:
			{
				if(allowCaption && selectedGraphicFrames.size())
					listToUpdate->SetNthActionState(i, kEnabledAction);
			}
			break;
			case kGenerateStaticCaptionForLinkSelectionActionID:
			{
				if(allowCaption && CanGenerateStaticCaption(selectedGraphicFrames))
					listToUpdate->SetNthActionState(i, kEnabledAction);
			}
			break;

			case kGenerateLiveCaptionForLinkActionID:
			case kGenerateStaticCaptionForLinkActionID:
			{
				// need at least one link selected which has a valid link object which is not an inline.
				UIDList captionablePI = GetLinkedPageItemsForCaptionsFromLinksPanelSelection(widget);
				if(captionablePI.size())
					listToUpdate->SetNthActionState(i, kEnabledAction);
			}
			break;
			case kConvertLiveCaptionToTextActionID:
			{
				InterfacePtr<const ITextEditSuite> editSuite (ac->GetContextSelection(), UseDefaultIID());
				if(editSuite)
				{
					listToUpdate->SetNthActionState(i, editSuite->CanConvertVariable(kLinkMetadataVariableBoss) ? kEnabledAction : kDisabled_Unselected);
				}
				else if(captionSuite && allowCaption)
				{
					listToUpdate->SetNthActionState(i, captionSuite->CanConvertCaptionVariablesInTextFrame() ? kEnabledAction : kDisabled_Unselected);
				}
			}
			break;
			default:
				ASSERT_FAIL("asked to update action I don't know about!");
				break;
		}
	}
}


void LinkCaptionActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{	
#pragma unused(mousePoint)					
	
	switch (actionID.Get()) 
	{
		case kGenerateLiveCaptionForLinkSelectionActionID:
		case kGenerateStaticCaptionForLinkSelectionActionID:
		{
			InterfacePtr<const ICaptionSelectionSuite> captionSuite (ac->GetContextSelection(), UseDefaultIID());
			UIDList selectedGraphicFrames =	captionSuite->GetUIDsSuitableForCaptioning();
			ASSERT_MSG(selectedGraphicFrames.size() > 0,"kGenerateCaptionForLinkSelectionActionID shouldn't be enabled unless there's one or more selected graphic frame in layout");
			GenerateCaptionForPageItems(selectedGraphicFrames, actionID == kGenerateLiveCaptionForLinkSelectionActionID);
		}
		break;

		case kGenerateLiveCaptionForLinkActionID:
		case kGenerateStaticCaptionForLinkActionID:
		{
			UIDList captionablePI = GetLinkedPageItemsForCaptionsFromLinksPanelSelection(widget);
			GenerateCaptionForPageItems(captionablePI,actionID == kGenerateLiveCaptionForLinkActionID);
		}
		break;
		case kGenerateCaptionPrefsDialogActionID:
		{
			InvokeGenerateCaptionPrefsDialog();
		}
		break;
		case kConvertLiveCaptionToTextActionID:
		{
			InterfacePtr<ITextEditSuite>	textEditSuite(ac->GetContextSelection(), UseDefaultIID());
			if (textEditSuite)
				textEditSuite->ConvertVariableToText(kLinkMetadataVariableBoss);
			else
			{
				InterfacePtr<ICaptionSelectionSuite> captionSuite (ac->GetContextSelection(), UseDefaultIID());
				if(captionSuite)
					captionSuite->ConvertCaptionVariablesInTextFrameToText();
			}
			
		}
		break;
		default: 
			ASSERT_FAIL("LinkCaptionActionComponent - unknown menu id");
			break;
	}
}


void LinkCaptionActionComponent::GenerateCaptionForPageItems(const UIDList& pageItems, bool makeLiveCaption) const
{
	ASSERT_MSG(pageItems.size() >= 1,"Should only be enabled with selected frames");
	
	InterfacePtr<ICommand> generateCaptionCmd ( CmdUtils::CreateCommand( kGenerateLinkCaptionCmdBoss ) );
	generateCaptionCmd->SetItemList(pageItems) ;
	InterfacePtr<IGenerateCaptionCmdData> liveData(generateCaptionCmd,UseDefaultIID());
	liveData->Set(makeLiveCaption,kTrue);
	ErrorCode cmdErr = CmdUtils::ProcessCommand( generateCaptionCmd ) ;
	if(cmdErr != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(kSuccess);
		if(cmdErr == (ErrorCode)kCaptionLayerLockedError)
			CAlert::ErrorAlert("#CaptionLayerLockedError");
		else if(cmdErr == (ErrorCode)kCaptionCantCreateGroupError)
			CAlert::ErrorAlert("#CaptionGroupFailureError");
		else
			CAlert::ErrorAlert("#ErrorGeneratingCaption");
	}

}

void LinkCaptionActionComponent::InvokeGenerateCaptionPrefsDialog() const
{	
	InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());

	IDialog* captionDialog = dialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(),kLinksUIPluginID, kViewRsrcType, kGenerateLinkCaptionDialogResID), IDialog::kMovableModal);
	if(captionDialog)
	{
		captionDialog->Open();
	}

}
