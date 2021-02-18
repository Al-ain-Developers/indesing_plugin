//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtSuiteTextCSB.cpp $
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
#include "ITextTarget.h"
#include "ITextModel.h"
#include "IDocumentBroadcastMsg.h"
#include "ICommand.h"

// General includes:
#include "CPMUnknown.h"
#include "SelectionExtTemplates.tpp"
#include "GenericID.h"
#include "UIDList.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtSuite.h"
#include "HidTxtFacade.h"
#include "IHidTxtModel.h"

/**	Implements IHidTxtSuite for the text CSB that gets used when a text
	selection exists.

	
	@ingroup hiddentext
	@see IHidTxtSuite
*/
class HidTxtSuiteTextCSB : public CPMUnknown<IHidTxtSuite>
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtSuiteTextCSB (IPMUnknown *boss);
		/** Desitructor.
		 */
		virtual ~HidTxtSuiteTextCSB (void);

	// IHidTxtSuite methods:
	public:
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanCreateHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		CreateHiddenText(const WideString& text);
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanGetHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual void			GetHiddenText(WideString& text) const;
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanModifyHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		ModifyHiddenText(const WideString& text);
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanDeleteHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		DeleteHiddenText();

	//	Selection extension functions 
	public:
		/** @see ISelectionExtension and SelectionExt template.
		*/
		virtual void				Startup			 					(void);

		/** @see ISelectionExtension and SelectionExt template.
		*/
		virtual void				Shutdown			 				(void);

		/** @see ISelectionExtension and SelectionExt template.
		*/
		virtual void				SelectionChanged 					(SuiteBroadcastData*, const PMIID&, void*);

		/** Posts a suite message, IHidTxtSuite::kDefaultIID, to
			selection observer clients when hidden text changes.
			@see ISelectionExtension and SelectionExt template.
		*/
		virtual void				SelectionAttributeChanged 			(SuiteBroadcastData*, const PMIID&, void*);

		/** @see ISelectionExtension and SelectionExt template.
		*/
		virtual void				HandleIntegratorSuiteMessage		(void*, const ClassID&, ISubject*, const PMIID&, void*);

		/** Adds protocol IHidTxtModel::kDefaultIID, the protocol on which
			commands that change hidden text notify change on the document's
			subject (ISubject).
			@see ISelectionExtension and SelectionExt template.
		*/
		virtual ProtocolCollection*	CreateObserverProtocolCollection 	(void);

	private:
		/** Return the TextIndex to be examined for associated hidden text
			based on the selection's text target (ITextTarget).
			@param leanBackward if kTrue return the TextIndex immediately preceeding
				the start of the selected range of text, otherwise return the TextIndex
				of the start of the selected range of text.				
			@return the TextIndex to be examined for associated hidden text.
		 */
		TextIndex GetAnchorTextIndex(const bool16 leanBackward = kTrue) const;
		
		/** Return reference to the selected story.
			@return reference to the selected story.
		 */
		UIDRef GetAnchorTextModel() const;
		
		/** @return kTrue if the story that has been changed by the given command
				intersects with selection's target (ITextTarget).
		 */	
		bool16 IntersectsTarget(ICommand* cmd);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(HidTxtSuiteTextCSB, kHidTxtSuiteTextCSBImpl)

/*
	Binds the suite onto its selection extension making the 
	selection extension member functions in the suite
	callable by the selection subsystem.
	The parameter to the template is the suite implementation class.
*/
template class SelectionExt<HidTxtSuiteTextCSB>;
CREATE_PMINTERFACE (SelectionExt<HidTxtSuiteTextCSB>, kHidTxtSuiteTextCSBSelectionExtImpl)

/*
*/
HidTxtSuiteTextCSB::HidTxtSuiteTextCSB(IPMUnknown* boss) :
	CPMUnknown<IHidTxtSuite>(boss)
{
}

/*
*/
HidTxtSuiteTextCSB::~HidTxtSuiteTextCSB(void)
{
}

/*
*/
bool16 HidTxtSuiteTextCSB::CanCreateHiddenText() const
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex(kFalse/*don't leanBackward*/));
	return facade.CanCreateHiddenText();
}

/*
*/
ErrorCode HidTxtSuiteTextCSB::CreateHiddenText(const WideString& text)
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex(kFalse/*don't leanBackward*/));
	return facade.CreateHiddenText(text);
}

/*
*/
bool16 HidTxtSuiteTextCSB::CanGetHiddenText() const
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	return facade.CanGetHiddenText();
}

/*
*/
void HidTxtSuiteTextCSB::GetHiddenText(WideString& text) const
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	facade.GetHiddenText(text);
}

/*
*/
bool16 HidTxtSuiteTextCSB::CanModifyHiddenText() const
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	return facade.CanModifyHiddenText();
}


/*
*/
ErrorCode HidTxtSuiteTextCSB::ModifyHiddenText(const WideString& text)
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	return facade.ModifyHiddenText(text);
}

/*
*/
bool16 HidTxtSuiteTextCSB::CanDeleteHiddenText() const
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	return facade.CanDeleteHiddenText();
}

/*
*/
ErrorCode HidTxtSuiteTextCSB::DeleteHiddenText()
{
	HidTxtFacade facade(this->GetAnchorTextModel(), this->GetAnchorTextIndex());
	return facade.DeleteHiddenText();
}

/*
*/
TextIndex HidTxtSuiteTextCSB::GetAnchorTextIndex(const bool16 leanBackward) const
{
	TextIndex result = kInvalidTextIndex;
	InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
	ASSERT(textTarget);
	if (textTarget != nil) {
		result = textTarget->GetRange().Start(nil);
		if (leanBackward && result > 0) {
			result--;
		}
	}
	return result;
}

/*
*/
UIDRef HidTxtSuiteTextCSB::GetAnchorTextModel() const
{
	UIDRef result = UIDRef::gNull;
	InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
	ASSERT(textTarget);
	if (textTarget != nil) {
		result = textTarget->GetTextModel();
	}
	return result;
}

/*
*/
void HidTxtSuiteTextCSB::Startup(void)
{
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::Startup-->In\n");
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::Startup-->Out\n");
}

/*
*/
void HidTxtSuiteTextCSB::Shutdown(void)
{
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::Shutdown-->In\n");
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::Shutdown-->Out\n");
}

/*
*/
void HidTxtSuiteTextCSB::SelectionChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* message)
{
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::SelectionChanged-->In\n");
	TRACEFLOW(kHidTxtPluginName,"HidTxtSuiteTextCSB::SelectionChanged-->Out\n");
}

/*
*/
ProtocolCollection*	HidTxtSuiteTextCSB::CreateObserverProtocolCollection(void)
{
	TRACEFLOW(kHidTxtPluginName, "HidTxtSuiteTextCSB::CreateObserverProtocolCollection-->In\n");
	ProtocolCollection*	protocolList = new ProtocolCollection();
	protocolList->insert(protocolList->begin(), 1, IHidTxtModel::kDefaultIID);
	TRACEFLOW(kHidTxtPluginName, "HidTxtSuiteTextCSB::CreateObserverProtocolCollection-->Out\n");
	return protocolList;
}

/*
*/
void HidTxtSuiteTextCSB::SelectionAttributeChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* message)
{
	TRACEFLOW(kHidTxtPluginName, "HidTxtSuiteTextCSB::SelectionAttributeChanged-->In\n");

	do {
		// Changes to IHidTxtModel are posted inside messages of type IDocumentBroadcastMsg.
		// Check that we have received a message that might be of interest to
		// IHidTxtSuite client code.

		if (messageID != IID_IDOCUMENT_BROADCAST) {
			// Just stop, this is a message we don't handle or tell
			// IHidTxtSuite clients about.
			break;
		}

		// Check message contains a protocol we registered in CreateObserverProtocolCollection.
		IDocumentBroadcastMsg* documentMessage = static_cast<IDocumentBroadcastMsg*>(message);
		if (documentMessage->GetPMIID () != IHidTxtModel::kDefaultIID) {
			// We shouldn't be sent IDocumentBroadcastMsg messages we didn't ask for.
			ASSERT_FAIL("HidTxtSuiteTextCSB::SelectionAttributeChanged called for an unregistered protocol.");
			break;
		}

		// The command that made the change to IHidTxtModel is indicated
		// by the IDocumentBroadcastMsg.
		// Check the state of the command indicates that the 
		// change is complete. 
		ICommand* cmd = static_cast<ICommand*>(documentMessage->GetVoidStar());
		ASSERT(cmd);
		if (!cmd) {
			break;
		}
		if (cmd->GetCommandState() != ICommand::kDone) {
			break;
		}

 		// Check that at least one item whose IHidTxtModel has changed
		// is a selected object.
		if (this->IntersectsTarget(cmd) == kFalse) {
			break;
		}

		// Check we didn't already post a message to client code about
		// change to IHidTxtModel.
		int32 keyLocation = FindLocationInSorted(*broadcastData, static_cast<PMIID>(IHidTxtSuite::kDefaultIID));
		if (keyLocation >= 0){
			// We already posted a message.
			// Note that ::InsertOrReplaceKeyValueInSorted is useful if you 
			// need to replace any message you already posted.
			// See header KeyValuePair.h.
			break;
		}

		// Post a message to clients of IHidTxtSuite about the change.
		// Note that me message is independent of the underlying
		// data model. We don't pass protocol IHidTxtModel::kDefaultIID,
		// we pass the suite's protocol, IHidTxtSuite::kDefaultIID.
		// Client code must be kept decoupled from the model.
		::InsertKeyValueInSorted(*broadcastData, static_cast<PMIID>(IHidTxtSuite::kDefaultIID), boost::shared_ptr<SelectionSuiteData>());

	} while(false);

	TRACEFLOW(kHidTxtPluginName, "HidTxtSuiteTextCSB::SelectionAttributeChanged-->Out\n");
}

/*
*/
void HidTxtSuiteTextCSB::HandleIntegratorSuiteMessage(void* message, const ClassID&, ISubject*, const PMIID&, void*)
{
	ASSERT_FAIL("HidTxtSuiteTextCSB::HandleIntegratorSuiteMessage should never be called");
}

/*
*/
bool16 HidTxtSuiteTextCSB::IntersectsTarget(ICommand* cmd)
{
	bool16 result = kFalse;
	do {
		// Look at the data being targeted by selection.
		UIDRef targetTextModelUIDRef = this->GetAnchorTextModel();

		// Look at the data the command changed.
		const UIDList& itemList = cmd->GetItemListReference();
		if (itemList.GetDataBase() != targetTextModelUIDRef.GetDataBase()) {
			// Different databases so no intersection.
			break;
		}
		// If we get here the database of the command and the selection target intersect.

		// Special handling of hidden text delete.
		if (::GetClass(cmd) == kHidTxtModelDeleteCmdBoss) {
			// TODO: enhance the delete command so that the text model
			// the hidden text has been deleted from can be detected
			// to see if it intersects the selection's target text model. 
			// For now if the we get a 
			// delete of hidden text within the same database then assume
			// intersection.
			result = kTrue;
			break;
		}

		// Check if the text model of the hidden text that has been
		// modified matches the selection's targeted text model.
		for (int32 i = 0 ; i < itemList.Length(); i++) {
			InterfacePtr<IHidTxtModel> hidTxtModel(itemList.GetRef(i), UseDefaultIID());
			if (!hidTxtModel) {
				continue;
			}
			InterfacePtr<ITextModel> changedTextModel(hidTxtModel->QueryTextModel());
			if (!changedTextModel) {
				continue;
			}
			if (::GetUIDRef(changedTextModel) == targetTextModelUIDRef) {
				result = kTrue;
				break;
			}
		}
	} while(false);
	return result;
}	

// End, HidTxtSuiteTextCSB.cpp.

