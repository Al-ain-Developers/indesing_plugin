//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableTextContent.h $
//  
//  Owner: ???
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

#pragma once
#ifndef __ITableTextContent__
#define __ITableTextContent__

#include "TableTypes.h"
#include "TablesID.h"
#include "K2Vector.h"

class ITextModel;
class ITextModelMemento;
class PasteDataXRefContext;
class ICommand;

/**
	Abstract interface for manipulating text content within a table,  
	allows access to information about Text content within the Table.

	The Text content of the Table is always within the same Text Model that the
	Table Model is anchored in and it consists of zero or more contigous
	TextStoryThreads that are ALWAYS at greater TextIndex than the Text
	Story Thread that the Table Model is anchored in.

	Note that the returned ranges from some methods MAY cross one or more TextStoryThread
	boundaries and it is up to the caller to take proper steps to avoid
	mis-handling the final carriage returns in each TextStoryThread.

*/
class ITableTextContent : public IPMUnknown
{
public:
	enum  { kDefaultIID = IID_ITABLETEXTCONTENT };


	
	/** Acquire a persistent reference (UIDRef) to text model associated with a table.	
		 The UIDRef returned can be used to acquire an ITextModel interface.

		 @return persistent reference to the underlying text model.
	*/
	virtual UIDRef			GetTextModelRef() const = 0;

	/** Acquire a reference-incremented interface ptr to the underlying text model
		associated with the table.
    
		@return reference-incremented interface ptr to text model
	*/	
	virtual ITextModel*		QueryTextModel() const = 0;
	
	/** 
		Returns the entire contiguous Text Range used by the
		Table Model to store its Text content.

		Note that the returned ranges MAY cross one or more TextStoryThread
		boundaries and it is up to the caller to take proper steps to avoid
		mis-handling the final carriage returns in each TextStoryThread.

	*/
	virtual void			GetTextRange(TextIndex& tableStartIndex,
										int32& tableTextSpan) const = 0;
	
	/** Returns Text Range(s) for an arbitrary GridArea of the
          TableModel.

          Because the GridArea may not allow the return of a
          single contiguous Text Range the specified GridArea is
          used as a iterator cookie and the largest contigous
          range is returned on each invocation and the cookie
          modified.
          Returns zero when no more Ranges exist.

          @param inOutArea IN/OUT parameter, specifies dimension of area of interest
          @param outStart OUT parameter, index within the text model where the area's text starts
          @return characters within text model for specified area, or 0 if no text range left
	*/
	virtual int32			GetTextChunk(GridArea& inOutArea,
										TextIndex& outStart) const = 0;

	/**
		 Determine if there is a text model currently associated with the table.
		 
		 At various times the Table needs to be disconnected from the
		 responsibility of managing the Text Range of the TextStoryThreads.
		
		 If the Table is connected then the deletion of the Table requires the
		 deletion of the Text content. If the Table is NOT connected that it
		 simply does everything it would normally EXCEPT touch the StoryThreads.

		 @return kTrue if there is an underlying text model, kFalse otherwise
    */
	virtual bool16			GetConnectedToTextContent() const = 0;
	
	virtual void			SetConnectedToTextContent(bool16 connected) = 0;


	/** Helper class nested in ITableTextContent for changes to the text model underlying the table.
	*	<br>This is an instance of the Memento pattern described in Design Patterns,
	*	Gamma et al. <br>Briefly: without violating encapsulation, it can be used to
	*	capture and externalize an object's internal state so that the object can be restored to this state later.
	*	<br>Used when: <ol><li>Need to save a "snapshot", 
	*	<li>Need to save state without exposing the implementation of an object.
	*	Preserves encapsulation boundaries, simplifies code, but can have relatively high storage costs.
	*/
	class Memento
	{
	public:
		virtual			~Memento() { };

		virtual void	TransferTo(PasteDataXRefContext* xRefContext) = 0;

	};
	//
	// These next four methods are used to manipulate the ENTIRE Text content.
	// by either deleting it (take), undeleting it (restore), copying it, or
	// pasting it into the same or different table.
	//
	// These operations mirror what can be done with the TextModel.
	//


	/** Delete the text content associated with the Table.
	*/
	virtual void			ProcessDeleteTextContent() = 0;

	/** Take (delete) the text content associated with the Table and hold it
		in the Memento. Client code owns the storage allocated.
		@return memento ptr which can be used in subsequent paste operations
	*/
	virtual Memento*		ProcessCutTextContent() = 0;

	/** Undelete text from text model underlying the table.
		@param m memento from previous delete operation
	*/
	virtual void			RestoreTextContent() = 0;

	/** Copy text within the table and return a memento ptr. 
		It is up to the client
		code to release the storage.
		@return memento ptr which can be used in subsequent paste operations
	*/
	virtual Memento*		CopyTextContent() = 0;

	/** Paste content into the table.
	*/	
	virtual void			ProcessPasteTextContent(Memento*) = 0;

};

#endif
