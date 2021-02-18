//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtSnapshotInterface.cpp $
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

// Interfaces:
#include "IPMStream.h"

//General:
#include "CPMUnknown.h"

// Project:
#include "GTTxtEdtID.h"
#include "IGTTxtEdtSnapshotInterface.h"

/** 
Implementation of the undoable data interface. Responsible for maintaining the last used story and text index.
Using the CREATE_SNAPSHOT_PMINTERFACE macro to bind the implementation into the object model also identifies it
as a snapshot interface

@ingroup gotolasttextedit
*/
class GTTxtEdtSnapshotInterface : public CPMUnknown<IGTTxtEdtSnapshotInterface>
{
public:
	/**
	ctor
	*/
	GTTxtEdtSnapshotInterface(IPMUnknown* boss);
	/**
	dtor
	*/
	virtual ~GTTxtEdtSnapshotInterface();
	/**
	Provides the last story edited.
	@return the last story edited.
	*/
	UIDRef& GetStory();
	/**
	Sets the last story edited.
	@param story IN the story that was edited.
	*/
	void SetStory(UIDRef story);
	/**
	Determines if the story maintained is valid (not kInvalidUID).
	@return kTrue if the story is valid.
	*/
	bool16 StoryValid();

	/**
	Returns the last story edit index, the position in the text the story was edited at.
	@return the story index.
	*/
	TextIndex GetStoryIndex();
	/**
	Sets the story index. Used to indicate the story index at which a story edit occurred.
	@param index IN the position the story was edited.
	*/
	void SetStoryIndex(TextIndex index);
	/**
	Sets both the story and the text index relating to the last text edit.
	@param story IN the story that was edited.
	@param index IN the text index at which the story was edited.
	*/
	void SetStoryAndIndex(UIDRef story, TextIndex index);

	/**
	Allows the internal state of the implementation to be marshalled out into the snapshot.
	@param s IN the stream the snapshot is being written to
	@param implID IN implementation ID
	*/
	void SnapshotReadWrite(IPMStream* s, ImplementationID implID);

private:
	/**
	cached text model
	*/
	UIDRef fTextModelRef;
	/**
	index within the model
	*/
	TextIndex fStoryIndex;
};


/*	
*/
CREATE_SNAPSHOT_PMINTERFACE(GTTxtEdtSnapshotInterface, kGTTxtEdtSnapshotInterfaceImpl)

/*	Constructor
*/
GTTxtEdtSnapshotInterface::GTTxtEdtSnapshotInterface(IPMUnknown* boss) : 	
CPMUnknown<IGTTxtEdtSnapshotInterface>(boss),
fTextModelRef(UIDRef::gNull), fStoryIndex(0)
{
}

/*	Destructor
*/
GTTxtEdtSnapshotInterface::~GTTxtEdtSnapshotInterface()
{
}

UIDRef& GTTxtEdtSnapshotInterface::GetStory() 
{
	return fTextModelRef;
}

void GTTxtEdtSnapshotInterface::SetStory(UIDRef story)
{
	// make sure it is a real update to the model
	if (story != fTextModelRef){
		PreDirty();
		fTextModelRef = story;
	}
}

bool16 GTTxtEdtSnapshotInterface::StoryValid()
{
	if (fTextModelRef == UIDRef::gNull || fTextModelRef.GetUID() == kInvalidUID)
		return kFalse;
	return kTrue;
}

TextIndex GTTxtEdtSnapshotInterface::GetStoryIndex() 
{
	return fStoryIndex;
}
void GTTxtEdtSnapshotInterface::SetStoryIndex(TextIndex index)
{
	// make sure the index has been updated
	if (index != fStoryIndex){
		PreDirty();
		fStoryIndex = index;	
	}
}

void GTTxtEdtSnapshotInterface::SetStoryAndIndex(UIDRef story, TextIndex index)
{
	// make sure the story or index has been updated
	if (story != fTextModelRef || index != fStoryIndex){
		PreDirty();
		fStoryIndex = index;	
		fTextModelRef = story;
	}
}


void GTTxtEdtSnapshotInterface::SnapshotReadWrite(IPMStream* s, ImplementationID implID)
{
	s->XferInt32(fStoryIndex);
	if (s->IsReading())
	{
		UID textModelUID(kInvalidUID);
		s->XferReference(textModelUID);
		fTextModelRef = UIDRef(::GetDataBase(this), textModelUID);
		TRACEFLOW(kGTTxtEdtPluginName,">>read>>>>GTTxtEdtSnapshotInterface::SnapshotReadWrite, UID: %d index %d\n", fTextModelRef.GetUID().Get(),fStoryIndex);
	}
	else
	{
		UID textModelUID(fTextModelRef.GetUID());
		s->XferReference(textModelUID);		
		TRACEFLOW(kGTTxtEdtPluginName,"<<write<<<GTTxtEdtSnapshotInterface::SnapshotReadWrite, UID: %d index %d\n", fTextModelRef.GetUID().Get(),fStoryIndex);
	}
}

// End, GTTxtEdtSnapshotInterface.cpp

