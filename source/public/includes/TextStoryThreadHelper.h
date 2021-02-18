//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextStoryThreadHelper.h $
//  
//  Owner: dwaterfa
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
#ifndef __TextStoryThreadHelper__
#define __TextStoryThreadHelper__


#include "ITextModel.h"
#include "ITextStoryThreadDict.h"

#pragma export on

/** Helper class for determining composable state of a given text index or text range, regardless
	of whether or not it is in the primary story thread.
	@see ITextUtils
	@see ITextModel
	@see TextIndex
	@see RangeData
*/
class PUBLIC_DECL TextStoryThreadHelper
{
	public:

					TextStoryThreadHelper(const ITextModel* textModel);

		/**
			IsComposable: Returns kTrue if the TextIndex is in a StoryThread that is currently composable.
		
			@param	at: a TextIndex
			@return bool16 - Returns kTrue if the TextIndex is in a StoryThread that is currently composable.
		*/
		bool16		IsComposable(TextIndex at)
			{
			UpdateST(at);
			return fCurrentSTComposable;
			}

		/**
			GetComposedEndTextIndex: Returns the first TextIndex after the last composed TextIndex in
			that specified Range that is fully composed.
			
			Note
				Text which is in overset is considered in this case as being fully
				composed. If the returned value is less than range.End() and
				pFrameUIDToWaitOn is non-nil, then pFrameUIDToWaitOn will be set 
				to the next TextFrame that needs composition in the primary
				StoryThread.
			
				This method operates on cached information which is NOT invalidated
				due to external composition.
		
			@param IN	range: specified range of text
			@param OUT	pFrameRefToWaitOn: set to the next frame that needs composition in the primary story thread
			@return TextIndex - Returns the first TextIndex after the last composed TextIndex in
			that specified Range that is fully composed.
		*/
		TextIndex	GetComposedEndTextIndex(const RangeData& range,
												UIDRef* pFrameRefToWaitOn);

		/**
			IsInOverset: Returns kTrue if the TextIndex is in a WaxLine that is overset in a Parcel that is overset
		
			@param	at: a TextIndex
			@return bool16 - Returns kTrue if the TextIndex is in a WaxLine that is overset in a Parcel that is overset.
		*/
		bool16		IsInOverset(TextIndex at)
			{
			UpdateST(at);
			return (fCurrentSTComposable && (at >= fCurrentSTOversetStart));
			}
			
		/**
			IsInUIViewableOverset: Returns kTrue if the TextIndex is in a WaxLine that is overset in an artificial overset container
			created so that the user can see it or for text statistics purposes. 
		
			@param	at: a TextIndex
			@return bool16 - Returns kTrue if the TextIndex is in a WaxLine that is in an overset container.
		*/
		bool16		IsInUIViewableOverset(TextIndex at)
			{
			UpdateST(at);
			return (fCurrentSTComposable && (at >= fCurrentSTUIViewableOversetStart));
			}

	private:
		void			UpdateST(TextIndex at);

		//
		// Members
		//
		IDataBase*		fDB;
		UID				fStoryUID;
		InterfacePtr<const ITextModel> fTextModel;

		TextIndex		fCurrentSTStart;
		TextIndex		fCurrentSTEnd;
		TextIndex		fCurrentSTUnComposedStart;
		TextIndex		fCurrentSTOversetStart;
		bool16			fCurrentSTComposable;

		UID				fCurrentSTDictUID;		
		InterfacePtr<const ITextStoryThreadDict> fCurrentSTDict;
		TextIndex		fCurrentSTDictAnchorIndex;
		int32			fCurrentSTDictParcelCount;
		int32			fCurrentSTDictComposedParcelCount;
		int32			fCurrentSTDictNonOversetParcelCount;
		bool16			fCurrentSTDictComposable;
		TextIndex		fCurrentSTUIViewableOversetStart;
};

#pragma export off

#endif
