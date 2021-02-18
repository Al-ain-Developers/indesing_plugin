//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleRemapData.h $
//  
//  Owner: Sanjay Kumar
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
#ifndef __IStyleRemapData__
#define __IStyleRemapData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "KeyValuePair.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

/** struct to hold style uid to be replaced with and preserve formatting flag.
*/
struct RemappedValue
{
	/** style to be replaced with*/
	UID fReplaceWithUID;

	/** if formatting is to be preserved, valid only if replace with UID is kInvalidUID. */
	bool16 fPreserveFormatting;

	RemappedValue(UID replaceUID, bool16 preserveFormatting) : fReplaceWithUID(replaceUID),fPreserveFormatting(preserveFormatting) {}

};

/** Stores the style to be deleted and style to be replaced with uid.
*/
typedef KeyValuePair<UID,RemappedValue> RemappingPair;

/** stores a list of styles to be deleted and thier corresponding replace with style uid and preserve formatting flag.
*/
typedef K2Vector<RemappingPair> RemappingList;


/** Command data interface for kDeleteParaStyleGroupCmdBoss, and kDeleteCharStyleGroupCmdBoss.
	When a style set is deleted a number of styles which are child of the style set being deleted
	also gets deleted. Through this interface a client can specify which style to replace with when
	a particular style is deleted with in a style set.
	@ingroup text
*/
class IStyleRemapData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTYLEREMAPDATA };

		enum ConflictFlagEnum
		{
			/** no action required */
			kConflictFlagNone = 0,

			/** Skip the conflicting styles/sets */
			kConflictFlagSkip = 1,

			/** Ovewrite the conflicting styles/sets with the droppped styles/sets */
			kConflictFlagOverwrite = 2,

			/** AutoRename the dropped styles/sets */
			kConflictFlagRename = 4
		};

		/** Sets the remapping list
			@param remapList [IN] sets the remapping list that will be used by the command
		*/
		virtual void SetRemappingList(const RemappingList& remapList) = 0;

		/** Gets the remapping list
			@return the remapping list that has been set.
		*/
		virtual const RemappingList& GetRemappingList() const = 0;

		/** Set the conflict flag, from ConflictFlagEnum, the action to be taken in case of conflict,
			@param conflictFlag [IN] a value from ConflictFlagEnum
			@see ConflictFlagEnum
		*/
		virtual void SetConflictFlag (int32 conflictFlag) = 0;

		/** Returns the conflict flag.
			@return conflict flag
		*/
		virtual int32 GetConflictFlag() const = 0;
};


#endif // __IStyleRemapData__
