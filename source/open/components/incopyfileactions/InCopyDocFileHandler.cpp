//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactions/InCopyDocFileHandler.cpp $
//  
//  Owner: cparrish
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
//  Ensures that clients outside of the file
//  
//  Ensures that clients outside of the file
//  
//  Ensures that clients outside of the file
//  
//  Ensures that clients outside of the file
//  
//  Ensures that clients outside of the file
//  
//  IDocFileHandler implementation for InCopy. Ensures that clients outside of the file
//  actions plugin get vectored through our file actions. Third parties will want
//  their own version of this interface installed as the default doc file handler
//  if they do not use our simple file system workflow.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IDocFileHandler.h"
#include "IInCopyDocUtils.h"
#include "IInCopyWorkFlowUtils.h"
#include "IStandAloneDoc.h"
#include "IStoryList.h"

// ----- Includes -----

#include "CPMUnknown.h"

// ----- Utility files -----

#include "IStoryUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "InCopyFileActionsID.h"


class InCopyDocFileHandler : public CPMUnknown<IDocFileHandler>
{
public:
		InCopyDocFileHandler(IPMUnknown *boss);
		
		virtual bool8 CanSave(const UIDRef& doc);
		virtual void Save(const UIDRef& doc, UIFlags uiFlags = kFullUI);

		virtual bool8 CanSaveAs(const UIDRef& doc);
		virtual void SaveAs(const UIDRef& doc, const IDFile *destFile = nil,
												UIFlags uiFlags = kFullUI,
												bool8 asStationery = kFalse,
												FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID);

		virtual bool8 CanSaveACopy(const UIDRef& doc);
		virtual void SaveACopy(const UIDRef& doc, const IDFile *destFile = nil,
												UIFlags uiFlags = kFullUI,
												bool8 asStationery = kFalse,
												FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID);

		virtual bool8 CanRevert(const UIDRef& doc);
		virtual void Revert(const UIDRef& doc, UIFlags uiFlags = kFullUI);

		virtual bool8 CanClose(const UIDRef& doc);
		virtual void Close(const UIDRef& doc, UIFlags uiFlags = kFullUI, bool8 allowCancel = kTrue, CloseCmdMode cmdMode = kSchedule);

		virtual CloseOptions CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel);
		virtual void GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir);

		virtual void SaveAs2(const UIDRef& doc, const PMString &fileName,
			UIFlags uiFlags = kFullUI,
			bool8 asStationery = kFalse,
			FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID);
private:

		bool16 IsStandAloneGraphicDoc(const UIDRef& doc);
};


CREATE_PMINTERFACE(InCopyDocFileHandler, kInCopyDocFileHandlerImpl)



//-----
// InCopyDocFileHandler()

InCopyDocFileHandler :: InCopyDocFileHandler(IPMUnknown *boss) :
	CPMUnknown<IDocFileHandler>(boss)
{
}


//----------------------------------------------------------------------------------------------------------
#pragma mark-

//-----
// CanSave()

bool8 InCopyDocFileHandler::CanSave(const UIDRef& doc)
{
	return Utils<IInCopyDocUtils>()->CanDoSave(doc);
}


//-----
// Save()

void InCopyDocFileHandler::Save(const UIDRef& doc, UIFlags uiFlags)
{
	Utils<IInCopyDocUtils>()->DoSaveAll(doc, uiFlags);
}


//-----
// CanSaveAs()

bool8 InCopyDocFileHandler::CanSaveAs(const UIDRef& doc)
{
	//----- Save as only available for standalone docs
	InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
	if (standAlone)
		return standAlone->IsStandAloneDoc() && !this->IsStandAloneGraphicDoc(doc);
		
	return kFalse;
}


//-----
// SaveAs()

void InCopyDocFileHandler::SaveAs(const UIDRef& doc, const IDFile *destFile, UIFlags uiFlags, bool8 asStationery, FileTypeInfoID fileTypeID)
{	
	//----- We don't do stationary in InCopy
	Utils<IInCopyDocUtils>()->DoSaveAs(doc, kFalse, destFile, uiFlags, kFalse, fileTypeID);
}

//-----
// SaveAs2()
void InCopyDocFileHandler::SaveAs2(const UIDRef& doc, const PMString &fileName, UIFlags uiFlags,bool8 asStationery, FileTypeInfoID fileTypeID)
{
	ASSERT_FAIL("You should not be calling this function. It is only a placeholder. The actual working implementation is in overridden"
		" DocFileHandler::SaveAs()");
	IDFile idfile(fileName);
	SaveAs(doc, &idfile, uiFlags, asStationery, fileTypeID);
}


//-----
// CanSaveACopy()

bool8 InCopyDocFileHandler::CanSaveACopy(const UIDRef& doc)
{
	//----- Save a copy only available for standalone docs
	InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
	if (standAlone)
		return standAlone->IsStandAloneDoc() && !this->IsStandAloneGraphicDoc(doc);
		
	return kFalse;
}


//-----
// SaveACopy()

void InCopyDocFileHandler::SaveACopy(const UIDRef& doc, const IDFile *destFile, UIFlags uiFlags, bool8 asStationery, FileTypeInfoID fileTypeID)
{	
	//----- We don't do stationary in InCopy
	Utils<IInCopyDocUtils>()->DoSaveAs(doc, kTrue, destFile, uiFlags, kFalse, fileTypeID);
}


//-----
// CanRevert()

bool8 InCopyDocFileHandler::CanRevert(const UIDRef& doc)
{
	return Utils<IInCopyDocUtils>()->CanDoRevert(doc);
}


//-----
// Revert()

void InCopyDocFileHandler::Revert(const UIDRef& doc, UIFlags uiFlags)
{
	Utils<IInCopyDocUtils>()->DoRevert(doc, uiFlags);
}


//-----
// CanClose()

bool8 InCopyDocFileHandler::CanClose(const UIDRef& doc)
{
	return kTrue;
}


//-----
// Close()
//
//	This hackery is intended to suppress a cascade of dialogs which can happen when 
//	throwing your open and modified standalone file into the trash.  When that happens, a UI event from the system
//	makes us notice that our files were moved, so we close them, making the "do you want to save" dialog
//	appear. This causes a UI event which makes us notice that our files were moved, so we close them,
//	making the "do you want to save" dialog layer on top of the previous one, ad nausium.
//
//	So, we keep a little list of database pointers.  You only get called to close if you aren't in the list.
//	Then we put you in the list and call close, where the dialog hangs and we get reentered.  The next time,
//	you are already in the list, so you don't get Close called and everything is fine.  It's a list because
//	you could have several documents open and tossed into the trash all at once.
//
namespace icdfh
{
	static IDThreading::ThreadLocalManagedObject< K2Vector<IDataBase*> > tl_DBList;
}

void InCopyDocFileHandler::Close(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel, CloseCmdMode cmdMode)
{
	IDataBase* db = doc.GetDataBase();
	K2Vector<IDataBase *> * vectorPtr = icdfh::tl_DBList.Get();
	K2Vector<IDataBase*>::iterator dbiter = std::find(vectorPtr->begin(), vectorPtr->end(), db);
	if (dbiter == vectorPtr->end())
	{
		vectorPtr->push_back(db);

		Utils<IInCopyDocUtils>()->DoClose(doc, uiFlags, allowCancel, cmdMode);

		K2Vector<IDataBase*>::iterator dbitez = std::find(vectorPtr->begin(), vectorPtr->end(), db);
		vectorPtr->erase(dbitez);
	}
}


//-----
// CheckOnClose()

IDocFileHandler::CloseOptions InCopyDocFileHandler::CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel)
{
	return Utils<IInCopyDocUtils>()->CheckOnClose(doc, uiFlags, allowCancel);
}


//-----
// GetCopyDefaultName()

void InCopyDocFileHandler::GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir)
{
	Utils<IInCopyDocUtils>()->GetCopyDefaultName(doc, name, useSystemDefaultDir);
}

//-----
// IsStandAloneGraphicDoc()

bool16 InCopyDocFileHandler::IsStandAloneGraphicDoc(const UIDRef& doc)
{
	// assumes already know it is stand alone doc, just check if it is graphic stand alone

	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
	if( !storyList || storyList->GetUserAccessibleStoryCount() == 0 )
	{
		Utils<IInCopyWorkFlowUtils> icWorkflowUtils;
		if (icWorkflowUtils)
		{
			UIDRef storyRef = icWorkflowUtils->GetFirstGraphicStory(doc);
			if (storyRef != UIDRef::gNull)
				return Utils<IStoryUtils>()->IsAStory(storyRef);
		}
	}
	return kFalse;
}
