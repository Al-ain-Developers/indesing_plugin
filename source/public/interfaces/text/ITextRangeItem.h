//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextRangeItem.h $
//  
//  Owner: Jianlan Song
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
#ifndef __ITEXTRANGEITEM__
#define __ITEXTRANGEITEM__

#include "IPMUnknown.h"
#include "TextID.h"

#include "ITextModelMemento.h"
#include "itextRangeNode.h"
#include "RangeData.h"
#include "IScript.h"

class ITextModel;
class IParcelList;
class IWaxLine;
class IWaxRun;


/** 	ITextRangeItem needs to be implemented by any object tracked by text range strand.
	This interface is used by the text range strand to communicate information between the 
	small boss range object with the real text object occupying the range during text operations,
	such as copy/paste.
	@ingroup text_story
*/
class ITextRangeItem : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTRANGEITEM };

		/**
		When the ITextModel which the ITextRangeItem is anchored in is being deleted it
		will query the ITextRangeItems via this method for Command to remove it
		from the document. At the time the returned command is executed the
		ITextModel will be in an indeterminate state and so it must not access
		it in any way. Further, this command should NOT remove any Text (ITextStoryThreads, etc)
		in the same ITextModel as a result of this operation - the entire ITextModel
		is processed at this time and anything in those ITextStoryThreads will be
		found. In addition, callees are NOT required to return a command.
		@return Pointer to remove from document command
		*/
		virtual ICommand * QueryRemoveFromDocumentCmd() const = 0;
		
		/**
		The ITextModelMomento provides a mechanism for the ITextModel to notify
		the associated object about changes to the model that affect the object.
		@return Pointer to Memento for this object.
		*/
		virtual ITextModelMemento*	QueryMemento() const = 0;

		virtual void SetRangeReference(TextRangeReference reference) = 0;

		/**
		The range item is asked it supports Scripting - the object itself does not
		have to have an IScript, just that it will return an object that does if
		asked.
		@return kTrue if the range item can return an object with an IScript interfaces, kFalse otherwise.
		*/
		virtual bool16 CanReturnIScript() const = 0;

		/**
		The range item is asked to return an object associated with it that supports
		scripting. The range item does not necessarily have to have an IScript to do
		this - just that it returns something asked.
		@return Pointer to boss with IScript interface
		*/
		virtual IScript* QueryIScript() const = 0;

		/**
		This method is called when WaxRuns are rebuilt for the specied WaxLine
		and the ITextRangeItem span intersects the text range of the WaxRun.
		Implementations may find this useful to attach TextAdornments at this
		time. Note that more than one ITextRangeItem may intersect the same
		WaxRun text range is implementations must give some thought to how they
		avoid collisions for the same type of ITextRangeItem.
		@param textModel The ITextModel containing the IOwnedItem
		@param pl IParcelList of the TextStoryThread containing the IWaxLine
		@param waxLine The IWaxLine containing the IOwnedItem
		@param waxRun The IWaxRun containing the IOwnedItem
		@param textRangeItemRange RangeData of the TextRangeItem. May be beyond the start/end of the WaxRun or WaxLine
		@param waxLineTextIndex	The TextIndex of the IWaxLine
		*/
		virtual void	Rebuilt(ITextModel* textModel,
								IParcelList* pl,
								const IWaxLine* waxLine,
								IWaxRun* waxRun,
								const RangeData& textRangeItemRange,
								TextIndex waxLineTextIndex) = 0;

};


#endif	// __ITEXTRANGEITEM__

