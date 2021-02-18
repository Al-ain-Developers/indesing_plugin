//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableTextContainer.h $
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
#ifndef __ITableTextContainer__
#define __ITableTextContainer__

#include "TableTypes.h"
#include "TablesID.h"
#include "PMTextUtils.h"

class ITextModel;
class ITextParcelList;

/** Interface to query and manipulate the relation between the table model and text model. Provides
	means to get at the text model underlying a table model, and vary the association. Can also find out
	where in the text model the table is anchored, e.g. find the index of the first table frame character
	in the text model for the table.

	The container in this case refers to the containing Text flow, or
	TextStoryThread, and the TextParcelList that it is flowing through.

	The Table is anchored to the Text flow via the Text Model in two ways:

	1.	A contiguous range of special "anchor" characters (one or more) are
	maintained in the Text Model. In general the number of characters
	used varies with the number of Rows in the Table Model but it will
	not necessarily be a one to one correspondence.

	2.	Associated with the range of anchor characters are one or more
	TableFrames attached via the OwnedItem Strand. Again, the number,
	location, and state of the TableFrames will vary with the only
	constants being that the first anchor character will ALWAYS have
	a TableFrame associated with it (although not always the same) and
	it will ALWAYS manage Row 0.

	Because the anchoring is done on a TextStoryThread basic, Tables can be
	inserted anywhere in the Text Model, even within other Table Text Cells.
*/

class ITableTextContainer : public IPMUnknown
{
public:
	enum  { kDefaultIID = IID_ITABLETEXTCONTAINER };

	/** Acquire a persistent reference to the underlying text model. 
		The UIDRef returned can be used to acquire an ITextModel interface.
		@return reference to the underlying text model as UIDRef
	*/
	virtual const UIDRef&		GetTextModelRef() const = 0;

	/** Acquire a reference-incremented interface ptr to text model.
		@return reference-incremented ptr to text model
	*/
	virtual ITextModel*			QueryTextModel() const = 0;


	/** Attaches the Table to the specified TextModel and
		related Text interfaces (such as ITableModelList).
		@param textModelUID specifies text model to associate with this table model
	*/
	virtual void				AttachToTextModel(UID textModelUID) = 0;

	/** Detaches the Table from the specified TextModel and
		related Text interfaces (such as ITableModelList).
	*/
	virtual void				DetachFromTextModel() = 0;

	/** Associates a particular text model by UID with the table model.
		@param textModelUID gives text model to associate with the table model
	*/
	virtual void				SetTextModelUID(UID textModelUID) = 0;

	// 01/19/01 dwaterfa: These methods will likely disappear as this
	// information is hidden within the Layout Strand.

	/** Deprecated. Get the UID of the first  
		TableFrame used by the TableModel.
		@return UID of the first table frame used by the table model.
	*/
	virtual UID					GetFirstTableFrameUID() const = 0;

	/** Deprecated. Set the UID of the first TableFrame used by the 
		table model.
		@param uid specifies UID of the table frame to use as first in table model
	*/
	virtual void				SetFirstTableFrameUID(UID uid) = 0;	


	/** Information about where the Table is anchored in the TextModel
		Should return the TextIndex of the first TableFrame.

		@return the index in the text model of first table frame
	*/
	virtual TextIndex			GetAnchorTextIndex() const = 0;

	/** Information about how the Table is anchored.

        @return the number of Table anchor characters used to anchor the Table.
	*/
	virtual int32				GetAnchorSpan() const = 0;

	/**
		Returns the TextIndex of the ThreadBlock
		for this Table. The value returned will
		be valid even if the Table has not created
		any StoryThreads.

		Note that the TextIndex values will change over time Text 
		is inserted or deleted before them so you cannot cache them.

        @return the range within the text model where the characters from this table are stored
	*/
	virtual Text::StoryRange	GetThreadBlockTextRange() const = 0;

	/** Acquire a reference to the text parcel list associated with the 
		table. 
		@return reference-incremented interface ptr to the text parcel list.
	*/
	virtual ITextParcelList*	QueryTextParcelList() const = 0;

};

#endif
