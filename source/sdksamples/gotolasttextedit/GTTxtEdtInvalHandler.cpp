//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtInvalHandler.cpp $
//  
//  Owner: Developer Technologies
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

// Interface includes
#include "IObserver.h"
#include "ICommand.h"

// general includes
#include "CmdUtils.h"
#include "UIDList.h"
//#include "K2Vector.tpp"
#include "DBUtils.h"

// project includes
#include "GTTxtEdtID.h"
#include "GTTxtEdtInvalHandler.h"

#pragma mark GTTxtEdtInvalCookie

/** Allows us to attach our observer to the text model on cookie transactions or inval handler reset calls

@ingroup gotolasttextedit
*/
static void AttachDetachTextModel(const UIDRef& storyUIDRef, const bool16 bAttach);

/*
*/
GTTxtEdtInvalCookie::GTTxtEdtInvalCookie(const UIDRef& storyUIDRef, bool16 storyCreated) 
{
	fCookieCrumbList.clear();
	fCookieCrumbList.push_back(GTTxtEdtCookieCrumb(storyUIDRef.GetUID(), storyCreated));
	fDataBase = storyUIDRef.GetDataBase();
}

/*
*/
GTTxtEdtInvalCookie::~GTTxtEdtInvalCookie()
{
}

/*
*/
void GTTxtEdtInvalCookie::AddNewCookieCrumb(const UIDRef& storyUIDRef, bool16 storyCreated)
{
	ASSERT_MSG(fDataBase == storyUIDRef.GetDataBase(),"GTTxtEdtInvalCookie::AddNewCookieCrumb - single database expected");
	GTTxtEdtCookieCrumbList::iterator iter = std::find(fCookieCrumbList.begin(), fCookieCrumbList.end(), GTTxtEdtCookieCrumb(storyUIDRef.GetUID(), !storyCreated));
	if (iter != fCookieCrumbList.end())
	{
		// We have an add and a delete of the same UID in the same transaction.
		// On undo or redo the observer for this UID does not need to
		// be detached / re-attached.
		// Note: Delete then add of the same UID in the same transaction
		// shouldn't ever happen - but if it does it amounts to a no-op on undo / redo
		// for this cookie's functionality.
		fCookieCrumbList.erase(iter);
	}
	else
	{
		fCookieCrumbList.push_back(GTTxtEdtCookieCrumb(storyUIDRef.GetUID(), storyCreated));
	}
}

/*
*/
void GTTxtEdtInvalCookie::InvalBeforeUndo()
{
	for (GTTxtEdtInvalCookie::GTTxtEdtCookieCrumbList::iterator iter = fCookieCrumbList.begin(); iter != fCookieCrumbList.end(); ++iter)
	{
		if (iter->second == kTrue) 
		{
			// if we are undoing the creation of a story, detach the observer
			// if we are undoing the deletion of the story, do nothing at this point
			AttachDetachTextModel(UIDRef(fDataBase,iter->first),kFalse);
		}
	}
}

/*
*/
void GTTxtEdtInvalCookie::InvalAfterUndo()
{
	for (GTTxtEdtInvalCookie::GTTxtEdtCookieCrumbList::iterator iter = fCookieCrumbList.begin(); iter != fCookieCrumbList.end(); ++iter)
	{
		if (iter->second == kFalse) 
		{
			// if we are undoing the creation of a story, do nothing at this point
			// if we are undoing the deletion of the story, attach the observer
			AttachDetachTextModel(UIDRef(fDataBase,iter->first),kTrue);
		}
	}
}

/*
*/
void GTTxtEdtInvalCookie::InvalBeforeRedo()
{
	for (GTTxtEdtInvalCookie::GTTxtEdtCookieCrumbList::iterator iter = fCookieCrumbList.begin(); iter != fCookieCrumbList.end(); ++iter)
	{
		if (iter->second == kFalse) 
		{
			// if we are redoing the creation of a story, do nothing at this point
			// if we are redoing the deletion of the story, detach the observer
			AttachDetachTextModel(UIDRef(fDataBase,iter->first),kFalse);
		}
	}
}

/*
*/
void GTTxtEdtInvalCookie::InvalAfterRedo()
{
	for (GTTxtEdtInvalCookie::GTTxtEdtCookieCrumbList::iterator iter = fCookieCrumbList.begin(); iter != fCookieCrumbList.end(); ++iter)
	{
		if (iter->second == kTrue) 
		{
			// if we are redoing the creation of a story, attach the observer
			// if we are redoing the deletion of the story, do nothing at this point
			AttachDetachTextModel(UIDRef(fDataBase,iter->first),kTrue);
		}
	}
}

/*
*/
void GTTxtEdtInvalCookie::Merge(const IInvalCookie* other)
{
	const GTTxtEdtInvalCookie* otherCookie = (const GTTxtEdtInvalCookie*) other;
	for (GTTxtEdtInvalCookie::GTTxtEdtCookieCrumbList::const_iterator iter = otherCookie->fCookieCrumbList.begin(); iter != otherCookie->fCookieCrumbList.end(); ++iter)
	{
		this->AddNewCookieCrumb(UIDRef(otherCookie->fDataBase, iter->first), iter->second);
	}
}

/* If all that happens within a sequence is that one story
	gets created and then deleted the cookie does not need
	to be called on undo / redo - the observer does not need 
	to be detached / re-attached.
*/
bool16 GTTxtEdtInvalCookie::IsUndoRequired()
{
	return fCookieCrumbList.size() > 0;
}

#pragma mark GTTxtEdtInvalHandler

/*
*/
void GTTxtEdtInvalHandler::AddStoryInvalInfo(const UIDRef& storyUIDRef, bool16 storyCreated)
{
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtInvalHandler::SetUIDRef - %d\n",storyUIDRef.GetUID().Get());
	if (!fCollectingInvals)
	{
		// An event for which we need to be called on undo or redo has happened.
		// Start collecting invals if appropriate.
		ASSERT_MSG(fInvalCookie == nil,"GTTxtEdtInvalHandler::SetUIDRef - expected a dead cookie");
		fCollectingInvals = DBUtils::StartCollectingInvals(storyUIDRef.GetDataBase(), this);
		if (fCollectingInvals)
		{
			// An undoable transaction is in progress - collect the first inval.
			fInvalCookie = new GTTxtEdtInvalCookie(storyUIDRef, storyCreated);
		}
	}
	else
	{
		// Continue collecting invals.
		ASSERT_MSG(fInvalCookie != nil,"GTTxtEdtInvalHandler::SetUIDRef - expected a live cookie");
		fInvalCookie->AddNewCookieCrumb(storyUIDRef, storyCreated);
	}
}

/*
*/
IInvalCookie* GTTxtEdtInvalHandler::EndCollectingInvals ()
{
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtInvalHandler::EndCollectingInvals\n");
	IInvalCookie* result = nil;
	ASSERT_MSG(fCollectingInvals,"GTTxtEdtInvalHandler::EndCollectingInvals  - EndCollectingInvals called when not collecting invals?");
	this->fCollectingInvals=kFalse;
	ASSERT_MSG(fInvalCookie != nil,"GTTxtEdtInvalHandler::SetUIDRef - expected a live cookie");
	if (fInvalCookie->IsUndoRequired())
	{
		// ownership for the cookie passes to caller
		result = fInvalCookie;
	}
	else
	{
		// If there's no data in the cookie there's nothing to be done on undo or redo.
		delete fInvalCookie;
	}
	fInvalCookie = nil;
	return result;
}

/*
*/
InvalHandlerID GTTxtEdtInvalHandler::GetID() const 
{
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtInvalHandler::GetID\n");
	return kGTTxtEdtInvalHandlerID;
}

/*
*/
void GTTxtEdtInvalHandler::BeforeRevert_InvalAll()
{
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtInvalHandler::BeforeRevert_InvalAll\n");
}

/*
*/
void GTTxtEdtInvalHandler::AfterRevert_InvalAll()
{
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtInvalHandler::AfterRevert_InvalAll\n");
}

/*
*/
void AttachDetachTextModel(const UIDRef& storyUIDRef, const bool16 bAttach)
{
	IDataBase* db = storyUIDRef.GetDataBase();
	if (db==nil || !db->IsValidUID(storyUIDRef.GetUID()))
		return ;

	InterfacePtr<IObserver> iObserver(storyUIDRef, IID_IGTTXTEDTSTORYOBSERVER);

	if (iObserver == nil){
		return ;
	}
	if (bAttach == kTrue){
		iObserver->AutoAttach();
	}
	else{
		iObserver->AutoDetach();
	}
	return;
}

// end GTTxtEdtInvalHandler.cpp
