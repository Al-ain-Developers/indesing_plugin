//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextModelMemento.h $
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
#ifndef __ITEXTMODELMEMENTO__
#define __ITEXTMODELMEMENTO__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"
#include "RangeData.h"
#include "ErrorUtils.h"

class PasteData;
class PasteDataXRefContext;
class ICommand;




/** The Memento provides a mechanism for an entity that manages some
	resource, for example an OwnedItem, to understand the full context
	of and participate in TextModel operations that affect them.
	Further, they are REQUIRED to do the right thing in regards to their
	own existence depending on the particular TextModel operation.
	@ingroup text_story
*/
class ITextModelMemento : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTMODELMEMENTO };

		//
		// Returns the UID that this Memento represents. This value
		// may be kInvalidUID if no object is associated.
		//
		virtual UID		GetAssociatedUID() const = 0;

		virtual ErrorCode	OnDelete(const UIDRef& story, 
								 TextIndex dataStart,
								 int32		dataLen,
								 const Text::StoryRangeList& subranges, 
								 K2Vector<InterfacePtr<ICommand> >& cmdList) = 0;
		virtual ErrorCode	OnCut(const UIDRef& story, 
							  TextIndex dataStart,
							  int32		dataLen,
							  const Text::StoryRangeList& subranges) = 0;
		virtual ErrorCode	OnCopyRange(PasteData* context) = 0;
		virtual ErrorCode	OnReplace(const UIDRef& story, 
								  TextIndex dataStart,
								  int32		dataLen,
								  int32		replaceDataLen,
								  const Text::StoryRangeList& subranges, 
								  K2Vector<InterfacePtr<ICommand> >& cmdList) = 0;

		virtual ErrorCode	TransferTo(PasteDataXRefContext* xRefContext) = 0;
		virtual ErrorCode	OnPaste() = 0;
		virtual bool16		MustHandleReplaceIndividually() = 0;

};


#endif	// __ITEXTMODELMEMENTO__
