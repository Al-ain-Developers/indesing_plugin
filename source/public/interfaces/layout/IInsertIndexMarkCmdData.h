//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IInsertIndexMarkCmdData.h $
//  
//  Owner: Michel Hutinel
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
#ifndef __IInsertIndexMarkCmdData__
#define __IInsertIndexMarkCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"
#include "UIDRef.h" 
#include "ITextModel.h" 
#include "K2Pair.h" 
#include "K2Vector.h" 

typedef K2Pair<UIDRef, TextIndex> PageEntryInfo;
typedef K2Vector<PageEntryInfo> PageEntryInfoArray;

/** Command data interface for creating a topic List.
	This interface holds the data for kInsertIndexMarkCmdBoss which
	is used to insert the index markers in the text.

	SetPageEntryUIDRef and SetPageEntriesInfo should not be called
	on the same command instance.

	@ingroup layout_index
	@see kInsertIndexMarkCmdBoss 
*/
class IInsertIndexMarkCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINSERTINDEXMARKCMDDATA };

		/** Gets the page entry for the command.
			@return the UIDRef of the page entry.
		*/
		virtual const UIDRef& GetPageEntryUIDRef() const = 0;

		/** Sets the page entry for the command.
			This method is used when the command should insert only
			one index marker. For inserting multiple index markers use 
			SetPageEntriesInfo.
			@param pageEntryUIDRef [IN] - the UIDRef of the page entry for which
			we want to insert the index marker. The index marker will be inserted
			at the beginning of the word where the cursor is.
		*/
		virtual void SetPageEntryUIDRef(const UIDRef& pageEntryUIDRef) = 0;

		/** Gets the page entries for the command.
			@return array of page entries and their positions.
		*/
		virtual PageEntryInfoArray const& GetPageEntriesInfo() const = 0;

		/** Sets the page entries for the command.
			This method is used when multiple index markers need to be set.
			@param pageEntries [IN] - array of page entries and their positions.
		*/
		virtual void SetPageEntriesInfo(PageEntryInfoArray const& pageEntries) = 0;

		/** Gets the target of the command.
			@return the UIDRef of the target item (usually the text model).
		*/
		virtual const UIDRef& GetTargetItem() const = 0;

		/** Sets the target of the command.
			@param targetItem [IN] - the UIDRef of the target item (usually the text model).
		*/
		virtual void SetTargetItem(const UIDRef& targetItem) = 0;

		/** Specifies if the index marker characters
			are already inserted in the text model.		
		*/
		virtual void SkipInsertingMarkerCharacter() = 0;

		/** Specifies if the index marker characters
			are already inserted in the text model.		
		*/
		virtual bool16 ShouldSkipInsertingMarkerCharacter() const = 0;
};

#endif	// __IInsertIndexMarkCmdData__