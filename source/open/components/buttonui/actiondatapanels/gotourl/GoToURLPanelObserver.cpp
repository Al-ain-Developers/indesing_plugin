//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotourl/GoToURLPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IActiveContext.h"
#include "ICommandSequence.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IGoToURLBehaviorData.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkFacade.h"
#include "IHyperlinkTable.h"
#include "ILayoutUIUtils.h"
#include "IStringData.h"
#include "IStringListControlData.h"
#include "ITextControlData.h"
#include "ISubject.h"
#include "IUIDData.h"
#include "IUIDListData.h"
#include "IWidgetUtils.h"


// ----- Implementation Includes -----

#include "BehaviorUIDefs.h"
#include "CBehaviorPanelObserver.h"

#include "CmdUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "HyperlinkID.h"
#include "HyperlinkPanelID.h"
#include "widgetid.h"

//========================================================================================
// CLASS GoToURLPanelObserver
//========================================================================================

class GoToURLPanelObserver : public CBehaviorPanelObserver
{
public:
	GoToURLPanelObserver(IPMUnknown *boss);
	virtual ~GoToURLPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	
protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	virtual void	LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* data);
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);
	virtual void	DoPopupChange();

private:
	void			AddHyperlinkDestination();
	UIDRef			GetSelectedObjectsUIDRef(IStringListControlData *destStringListController, int32 selected) const;
	void			ConvertURLNameToDestinationIfPossible(PMString& urlName) const;
	void			LoadURLs();
	bool16			ActiveDocChange();
	void			AttachTo(IDataBase* db);
	void			DetachFrom(IDataBase* db);

	IDataBase *fDB;
	bool	isAttached;
};

//========================================================================================
// METHODS GoToURLPanelObserver
//========================================================================================

CREATE_PMINTERFACE(GoToURLPanelObserver, kGoToURLPanelObserverImpl)

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver constructor 
//----------------------------------------------------------------------------------------

GoToURLPanelObserver::GoToURLPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::~GoToURLPanelObserver
//----------------------------------------------------------------------------------------

GoToURLPanelObserver::~GoToURLPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::AutoAttach()
{
	if ( ! isAttached ) 
	{
		IDocument *doc = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
		fDB = ::GetDataBase(doc);

		if (fDB)
			AttachTo(fDB);

		LoadURLs();

		CBehaviorPanelObserver::AutoAttach();
		
#if 0
		InterfacePtr<IUIDData> behaviorRef(FormFieldUIUtils::QueryActiveBehavior());
		if ( behaviorRef->GetItemUID() != kInvalidUID )
		{
			InterfacePtr<IGoToURLBehaviorData> behaviorData(behaviorRef->GetRef(), UseDefaultIID());
			
			if ( behaviorData )
				SetTextControlData(kGoToURLWidgetID, behaviorData->GetURL());
		}
		else
		{
			SetTextControlData(kGoToURLWidgetID, "");
		}
#endif
		
		AttachToWidget(kGoToURLWidgetID, IID_ITEXTCONTROLDATA);
		AttachToWidget(kGoToURLWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = true;
	}
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kGoToURLWidgetID, IID_ITEXTCONTROLDATA);
		DetachFromWidget(kGoToURLWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		if (fDB)
			DetachFrom(fDB);

		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	
	if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
	{
		if ( inBossClassID == kPopupChangeStateMessage )
		{
			DoPopupChange();
		}
		else if ( inProtocol == IID_ITEXTCONTROLDATA )
		{
			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__) ; 
			AddHyperlinkDestination();
			CBehaviorPanelObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
			CmdUtils::EndCommandSequence(cmdSeq); 
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
		return;
	}

	if (inProtocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
	{
		InterfacePtr<IActiveContext> context( inSubject, UseDefaultIID());
		IActiveContext::ContextInfo *info = (IActiveContext::ContextInfo*)inMessage;

		if (info->Key() == IID_IDOCUMENT)
		{
			ActiveDocChange();
		}
	}

	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//---------------------------------------------------------------------------------------- 
// GoToURLPanelObserver::LazyUpdate: 
//---------------------------------------------------------------------------------------- 

void GoToURLPanelObserver::LazyUpdate(ISubject* theSubject, const PMIID& protocol, const LazyNotificationData* data)
{
	if(protocol == IID_IDESTINATIONCHANGE )
	{
		LoadURLs();
    }
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if ( inActionData )
	{
		InterfacePtr<IGoToURLBehaviorData> behaviorData(inActionData, UseDefaultIID());
		
		if ( behaviorData )
		{
			SetTextControlData(kGoToURLWidgetID, behaviorData->GetURL(), nil, kTrue, kFalse);			
		}

	}
	else
	{
		bool updated = false;
		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
			{
				updated = true;
				InitializeFieldsFromActionData(iBehaviorData);
				LoadURLs();
			}
		}

		if ( !updated )
			SetTextControlData(kGoToURLWidgetID, "$$$/Dialog/Behaviors/GoToView/DefaultURL", nil, kTrue, kFalse);
	}
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::ApplyFieldsToActionData
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::ConvertURLNameToDestinationIfPossible(PMString& urlName) const
{
	// if urlName does not match any defined url hyperlink's name, it returns unmodified.

	InterfacePtr<IHyperlinkTable> docHyperlinkTable(fDB, fDB->GetRootUID(), UseDefaultIID()); 
	const int32 numDestinations(docHyperlinkTable ? docHyperlinkTable->GetHyperlinkDestinationCount() : 0);

	// search the list of hyperlinks on this document
	for (UniqueKeyToUIDMap::const_iterator iter = docHyperlinkTable->GetDestinationKeyToUIDMapBeginIter(); 
		 iter != docHyperlinkTable->GetDestinationKeyToUIDMapEndIter(); ++iter) 
	{
		const UID hlDestUID = iter->second;
		
		InterfacePtr<const IHyperlinkDestination> destination(fDB, hlDestUID, UseDefaultIID());

		ASSERT(destination);
		if(destination)
		{
			const IHyperlinkDestination::DestType type = destination->GetType();

			if(type == IHyperlinkDestination::kURLDestination)
			{
				PMString destName;
				// if the name of the destination matches the url name passed in, 
				// change the url name to this url's destination, and return.
				destination->GetName(&destName);
				if(destName == urlName)
				{
					destination->GetInfo(&urlName);
					break;
				}
			}
		}
	} 
	
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::ApplyFieldsToActionData
//----------------------------------------------------------------------------------------

bool GoToURLPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	if ( inActionData )
	{
		IGoToURLBehaviorData* actionData = static_cast<IGoToURLBehaviorData*>(inActionData);

		PMString url(GetTextControlData(kGoToURLWidgetID));
		if ( url.empty() )
		{
			url = "$$$/Dialog/Behaviors/GoToView/DefaultURL";
			url.Translate();
			SetTextControlData(kGoToURLWidgetID, url);
		}
		else
		{
			ConvertURLNameToDestinationIfPossible(url);
		}

		PMString oldURL = actionData->GetURL();
		oldURL.Translate();
		if ( oldURL != url )
		{
			// The url we got from edit box (kGoToURLWidgetID) has already been translated (See WEditBoxTextControlData::GetString()).
			// However the fURL in actionData has not translated. 
			// Therefore we have the string comparison asserts within SetURL(). See bug #1870360. 
			// So here we set the translatable flag as kFalse for the UI string since I think 
			// all strings entered by user is not key string and therefore should not be translated.
			url.SetTranslatable(kFalse);

			
			actionData->SetURL(url);

			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::AddHyperlinkDestination
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::AddHyperlinkDestination()
{
	// The goal here is to auto-add a URL based hyperlink destination, but only
	// if the destination does not already exist.
	if ( !fDB )
		return;

	// Get the potential url from the edit field
	PMString url(GetTextControlData(kGoToURLWidgetID));
	url.SetTranslatable(kFalse);
	url.StripWhiteSpace(PMString::kTrailingWhiteSpace);

	InterfacePtr<IStringListControlData> listData((IStringListControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kGoToURLWidgetID, IID_ISTRINGLISTCONTROLDATA));
	InterfacePtr<IDropDownListController> controller(listData, UseDefaultIID());
	
	PMString popupItemURL("http://");
	popupItemURL.SetTranslatable(kFalse);
	
	int32 count = listData->Length();
	int32 selection = controller->GetSelected();
	
	bool bFound(false);
	UIDRef destRef(UIDRef::gNull);

	// Check the selected popup item first since it is the most likely to match
	destRef = GetSelectedObjectsUIDRef(listData, selection);

	// Now get the information out of the destination if there is only one destination
	if (destRef != UIDRef::gNull)
	{
		InterfacePtr<IStringData> stringData(destRef, IID_ISTRINGDATA);
		if (stringData)
		{
			popupItemURL = stringData->GetString();
			popupItemURL.SetTranslated(); // The user has chosen this text so it is automatically translated
			bFound = ( popupItemURL == url );
		}
	}

	// If the selected popup item does not match, check the other items
	for ( int32 i = 0; !bFound && i < count; ++i )
	{
		if ( i == selection )
			continue;

		destRef = GetSelectedObjectsUIDRef(listData, i);

		// Now get the information out of the destination if there is only one destination
		if (destRef != UIDRef::gNull)
		{
			InterfacePtr<IStringData> stringData(destRef, IID_ISTRINGDATA);
			if (stringData)
			{
				popupItemURL = stringData->GetString();
				popupItemURL.SetTranslated(); // The user has chosen this text so it is automatically translated
				popupItemURL.StripWhiteSpace(PMString::kTrailingWhiteSpace);

				if ( popupItemURL == url )
				{
					bFound = true;
					break;
				}
			}
		}
	}

	if ( !bFound && !url.IsEmpty() )
	{
		UIDRef newDestRef;
		if ( Utils<Facade::IHyperlinkFacade>()->CreateHyperlinkURLDestination(fDB, url, &newDestRef, url) == kSuccess )
		{
			// add url to popup by rebuilding the popup. This approach ensures that
			// the list will be sorted.
			LoadURLs();
		}
	}
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::GetSelectedObjectsUIDRef
//----------------------------------------------------------------------------------------
UIDRef GoToURLPanelObserver::GetSelectedObjectsUIDRef(IStringListControlData *destStringListController, int32 selected) const
{
	InterfacePtr<IUIDListData> destinationListData(destStringListController, IID_IDESTINATIONUIDLIST);
	UIDRef retVal(UIDRef(destinationListData->GetDataBase(), kInvalidUID));

	PMString noDoc("No document selected");
	noDoc.Translate();

	if (destStringListController->GetIndexOfPartialString(noDoc, kTrue) == selected)
	{
		// There is not a document selected in the document drop down
		retVal = UIDRef::gNull;
	}
	else if ( selected != -1 && selected < destinationListData->GetRef()->Length() )
	{
		// There is an item selected in the list
		retVal = destinationListData->GetItemRef(selected);
	}
	else if (selected == -1) // Nothing was selected
		retVal = UIDRef::gNull;
	else // None was selected
		retVal = UIDRef(destinationListData->GetDataBase(), kInvalidUID);

	return retVal;
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::LoadURLs
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::LoadURLs()
{
	InterfacePtr<IStringListControlData> listData((IStringListControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kGoToURLWidgetID, IID_ISTRINGLISTCONTROLDATA));
	InterfacePtr<IDropDownListController> controller(listData, UseDefaultIID());
	InterfacePtr<IUIDListData> destListData(controller, IID_IDESTINATIONUIDLIST);
	
	IDocument *doc = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	fDB = ::GetDataBase(doc);
	UIDList *destList = new UIDList(fDB);
	listData->Clear();
	destListData->Set(destList);
	
	K2Vector<ClassID> bossList;
	bossList.push_back(kHyperlinkURLDestinationBoss);
		
	bool16 bSorted = kTrue;
	
	Utils<ILayoutUIUtils>()->FillListWithHyperlinkDestinations(listData.get(), fDB, destList, &bossList, ILayoutUIUtils::includeVisibleOnly, bSorted);
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::GoToURLPanelObserver
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::DoPopupChange()
{
	InterfacePtr<IStringListControlData> listData((IStringListControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kGoToURLWidgetID, IID_ISTRINGLISTCONTROLDATA));
	InterfacePtr<ITextControlData> urlTextWidget(listData, UseDefaultIID());
	InterfacePtr<IDropDownListController> controller(listData, UseDefaultIID());
	
	PMString urlStr("http://");
	urlStr.SetTranslatable(kFalse);
	int32 selection = controller->GetSelected();
	//if ( selection >= 0 && selection < theAnchorTypeList.size() )
	//	urlStr = listData->GetString(selection);
	
	UIDRef destRef(GetSelectedObjectsUIDRef(listData, selection));

	// Now get the information out of the destination if there is only one destination
	if (destRef != UIDRef::gNull)
	{
		InterfacePtr<IStringData> stringData(destRef, IID_ISTRINGDATA);
		if (stringData)
			urlStr = stringData->GetString();
	}

	urlStr.SetTranslated(); // The user has chosen this text so it is automatically translated

	// Set the current text in the control
	urlTextWidget->SetString( urlStr );
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::ActiveDocChange: 
//----------------------------------------------------------------------------------------

bool16 GoToURLPanelObserver::ActiveDocChange()
{
	IDocument *doc = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	IDataBase *db = ::GetDataBase(doc);
	bool16 bReallyChanged = kFalse;
	
	if (db != fDB)
	{
		if (fDB)
			this->DetachFrom(fDB);
		
		if (db)
			this->AttachTo(db);
		
		fDB = db;
		bReallyChanged = kTrue;
	}
	
	return (bReallyChanged);
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::AttachTo: 
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::AttachTo(IDataBase* db)
{
	InterfacePtr<ISubject> docSubject(db, db->GetRootUID(), IID_ISUBJECT);
	if (docSubject && !docSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IDESTINATIONCHANGE, IID_IOBSERVER))
	{
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IDESTINATIONCHANGE, IID_IOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// GoToURLPanelObserver::DetachFrom: 
//----------------------------------------------------------------------------------------

void GoToURLPanelObserver::DetachFrom(IDataBase* db)
{ 	
	InterfacePtr<ISubject> oldSubject(db, db->GetRootUID(), IID_ISUBJECT);
	if (oldSubject && oldSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IDESTINATIONCHANGE, IID_IOBSERVER))
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IDESTINATIONCHANGE, IID_IOBSERVER);
}