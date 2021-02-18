//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextStoryThreadDictHier.h $
//  
//  Owner: Mat Marcus
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
#ifndef __ITTextStoryThreadDictHier__
#define __ITTextStoryThreadDictHier__

#include "IPMUnknown.h"
#include "TextID.h"

/** 
	This interface is implemented on every kTextStoryBoss and is used to manage
	the layout of ITextStoryThreadDict thread blocks within the ITextModel. The
	proper ordering of thread blocks within the the ITextModel is vital because
	of undo issues.
	Consider the case of nested tables - within one thread block
	(the primary story thread) is anchored the first table. Within its thread
	block is anchored another table. It is important that the relative ordering
	be maintained.
	@see ITextStoryThreadDict
	@see ITextModel
	@see ITextStoryThread
	@ingroup text_story
*/
class ITextStoryThreadDictHier : public IPMUnknown {
public:
	enum { kDefaultIID = IID_ITEXTSTORYTHREADDICTHIER };

	/**
	Insert the boss implementing ITextStoryThreadDict into the
	hierarchy.
	@param dictUID UID of the boss
	*/
	virtual void		Insert(UID dictUID) = 0;

	/**
	Insert the boss implementing ITextStoryThreadDict into the
	hierarchy.
	@param dictUID UID of the boss
	*/
	virtual void		Remove(UID dictUID) = 0;

	/**
	This method aids in determing the neighboring boss within the hierchy. This
	is done by flattening the hierarchy and returning the next boss relative to
	the specified one.
	One use of this method is in determing where the thread block
	range for the dictionary is to be located. This can be accomplished as
	follows:
	\verbatim
	InterfacePtr<const ITextStoryThreadDictHier> dictHier(myTextModel, UseDefaultIID());
	const UID nextDictUID = dictHier->NextUID(myDictUID);
	if (nextDictUID.IsValid())
	{
	   InterfacePtr<const ITextStoryThreadDict> nextDict(::GetDataBase(myTextModel), nextDictUID, UseDefaultIID());
	   retIndex = nextDict->GetThreadBlockTextRange().GetStart();
	}
	else
	{
	   // no next, so we use the end of the TextModel.
	   retIndex = myTextModel->TotalLength();
	}
	\endverbatim
	@param dictUID UID of the boss you wish to find the next boss of
	@return UID of the next boss in the hierarchy, or kInvalidUID if no bosses follow.
	*/
	virtual UID			NextUID(UID dictUID) const = 0;
	
	/**
	For comparing positions relative to the hierarchy of TextIndexes in
	different dictionaries.
	*/
	typedef enum
	{
		/** (dict1, pos1) is hierarchicaly before (dict2, pos2) */
		kIsBefore = -1,

		/** pos1 is the same as pos2 */
		kIsEqual = 0,

		/** (dict1, pos1) is hierarchicaly after (dict2, pos2) */
		kIsAfter = 1

	} CompareResult;

	/**
	This method is used to determine the hierarchical ordering of TextIndexes
	in dictionaries. Ordering is determined not by strict TextIndex ordering but
	rather by ordering relative to the anchors of the dictionaries themselves.
	For example, if dict2 is anchored in dict1 and pos2 is within the thread
	block of dict2, then if pos1 in dict1 is greater than the anchor TextIndex
	of dict2 then this method will return kIsAfter.
	@param dict1 UID of first dictionary
	@param pos1 TextIndex within the first dictionary's thread block
	@param dict2 UID of second dictionary, may be the same as the first
	@param pos2 TextIndex within the second dictionary's thread block
	@return CompareResult
	*/
	virtual CompareResult Compare(UID dict1, TextIndex pos1,
								UID dict2, TextIndex pos2) const = 0;

};

#endif //__ITTextStoryThreadDictHier__
