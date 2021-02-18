//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IOwnedItemUtils.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IOWNEDITEMUTILS__
#define __IOWNEDITEMUTILS__

#include "InCopySharedID.h"

class ITextModel;

/** Notes related utility interface. 
*/
class IOwnedItemUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOWNEDITEMUTILS };
	
	/** Return true if the text index is in a note. Optionally iterates up until finding the desired item or hit the primary story.
		@param model of the text index
		@param textPosition the text index you want to find out information about
		@param ownedItemUID optionally return a uid of the note owned item.
		@param iterate whether to iterate if item holding the textPosition didn't match (i.e. inline text frame, table, etc.)
		@return kTrue if index is within a note
	*/
	virtual bool16 IsLocationInNote(const ITextModel *model, TextIndex textPosition, UID *ownedItemUID = nil, bool16 iterate = kFalse) = 0;
	
	/** Return true if the text index is in a footnote. Optionally iterates up until finding the desired item or hit the primary story.
		@param model of the text index
		@param textPosition the text index you want to find out information about
		@param ownedItemUID optionally return a uid of the footnote owned item.
		@param iterate whether to iterate if item holding the textPosition didn't match (i.e. inline text frame, table, etc.)
		@return kTrue if index is within a footnote
	*/
	virtual bool16 IsLocationInFootnote(const ITextModel *model, TextIndex textPosition, UID *ownedItemUID = nil, bool16 iterate = kFalse) = 0;
	
	/** Return true if the text index is in tracked change deleted text. Optionally iterates up until finding the desired item or hit the primary story.
		@param model of the text index
		@param textPosition the text index you want to find out information about
		@param ownedItemUID optionally return a uid of the deleted text owned item.
		@param iterate whether to iterate if item holding the textPosition didn't match (i.e. inline text frame, table, etc.)
		@return kTrue if index is within tracked change deleted text
	*/
	virtual bool16 IsLocationInDeletedText(const ITextModel *model, TextIndex textPosition, UID *ownedItemUID = nil, bool16 iterate = kFalse) = 0;
	
	/** Return true if the text index is in a table. Optionally iterates up until finding the desired item or hit the primary story.
		@param model of the text index
		@param textPosition the text index you want to find out information about
		@param ownedItemUID optionally return a uid of the table owned item.
		@param iterate whether to iterate if item holding the textPosition didn't match (i.e. inline text frame, table, etc.)
		@return kTrue if index is within table text
	*/
	virtual bool16 IsLocationInTable(const ITextModel *model, TextIndex textPosition, UID *ownedItemUID = nil, bool16 iterate = kFalse) = 0;
	
	/** Return true if the text index is in a hidden text. Optionally iterates up until finding the desired item or hit the primary story.
		@param model of the text index
		@param textPosition the text index you want to find out information about
		@param ownedItemUID optionally return a uid of the hidden text owned item.
		@param iterate whether to iterate if item holding the textPosition didn't match (i.e. inline text frame, table, etc.)
		@return kTrue if index is within a hidden text
	*/
	virtual bool16 IsLocationInHiddenText(const ITextModel *model, TextIndex textPosition, UID *ownedItemUID = nil, bool16 iterate = kFalse) = 0;
};

#endif // __IOWNEDITEMUTILS__
