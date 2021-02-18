//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableModelList.h $
//  
//  Owner: Joe Shankar
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
#ifndef __ITableModelList__
#define __ITableModelList__

#include "TablesID.h"
#include "PMTextUtils.h"


//-----------------------------------
//	Forward References
//
class ITableModel;

/** A class that maintains references to the ITableModel's present in a story.  Currently tables 
	are connected to the Story through	two ways - the TableModelList and the TextStoryThreadDictHier.
	The latter represents the new scheme.  This interface may therefore become reduced in significance 
	as time wears on.

*/
class ITableModelList : public IPMUnknown {

public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ITABLEMODELLIST };

	// ----- Iteration -----
	/** Determine the number of table models in the list.
		@return count of the table models in the list
		@postcondition result >= 0
	*/
	virtual int32 		GetModelCount() const = 0;
	
	/** Query for a table model by position in the list, acquiring a reference-increment ptr.
		@param index specifies position in table model list to select
		@return reference-incremented ptr to the table model at list position specified by index, or nil
				if the index given was invalid
		@precondition index >= 0 and index < GetModelCount()
		@postcondition result <> nil
		@postcondition result.GetRefCount() = result@pre.GetRefCount() + 1
	*/
	virtual ITableModel* QueryNthModel(int32 index) const = 0;

	/** Acquire the UID of a table model in the list by index position.
		@param index specifies position in table model list to select
		@precondition index >= 0 and index < GetModelCount()
		@postcondition result <> kInvalidUID			
	*/
	virtual UID			GetNthModelUID(int32 index) const = 0;

						
	/** Returns a sorted list of story ranges for the anchor
		characters of Tables in the specified thread. Only
		ranges that are longer than 1 are returned.

		@param indexWithinThread location in the text model for the story-thread of interest
		@param resultList OUT parameter, where the sorted story ranges will be returned
		
	*/
	virtual void		CollectAnchorSpansInThread(TextIndex indexWithinThread,
									Text::StoryRangeList* resultList) const = 0;

	
	/** Returns the offset (negative or positive) to adjust the specified text index 
		so it covers an intersecting table. If the text index is at the beginning of the
		table a positive value corresponding to the number of additional anchor characters 
		(a table with two anchor characters would return '1'). If the text
		index is at the end of the table a negative value will be returned.
		
		@param at specifies the text index of interest
		@return offset to adjust the specified text index  so it covers an intersecting table
	*/
	virtual int32		GetAnchorDeltaInThread(TextIndex at) const = 0;

	// ----- Addition and Removal -----	
	/** Method to add a table model into the list.
		@param modelUID specifies the new table model to add to the list
		@param insertionThreadDictUID 
		@param insertionThreadDictKey 
	
		@precondition modelUID <> kInvalidUID
		@precondition not models->select(model | model = modelUID)
		@postcondition models->select(model | model = modelUID)
	*/
	virtual void 		AddModel(UID modelUID,
								UID insertionThreadDictUID,
								uint32 insertionThreadDictKey) = 0;	
	/** Remove a table model from the list by UID.
		@param UID specifies the model to remove
		@precondition modelUID <> kInvalidUID
		@precondition models->select(model | model = modelUID)
				
	*/
	virtual void 		RemoveModel(UID modelUID) = 0;

	/** We are notified when any story threads are joined or created.
		This gives us the opportunity to patch up the parents for
		any tables in the affected range
		@precondition dictUID <> kInvalidUID
				
	*/
	virtual void 		StoryThreadChanged(UID tableModelUID, UID dictUID, uint32 dictKey) = 0;
protected:

	/** 
		@invariant models->size == GetModelCount()
		@invariant models->forall(model | models->count(model) = 1), i.e. no duplicate models
	*/
	virtual void 		Invariant() const = 0;

};


#endif // __ITableModelList__
