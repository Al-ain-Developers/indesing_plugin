//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISyncMasterPageData.h $
//  
//  Owner: Yeming Liu
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
//  
//  Comments: Data interface for storing a map between style name(key) and doc name(value).
//  
//========================================================================================

#pragma once
#ifndef __ISYNCMASTERPAGEDATA__
#define __ISYNCMASTERPAGEDATA__

// ----- Interface files

#include "IPMStream.h"
#include "IPMUnknown.h"

// ----- Include files

#include "KeyValuePair.h"
#include "K2Vector.h"

// ----- ID files

#include "MasterPageID.h"

/** This class defines the data structure used in the interface ISyncMasterPageData.
*/
class MasterPageItemInfo
{
	public:
		typedef object_type data_type;

		MasterPageItemInfo() {}

		MasterPageItemInfo(
				const UID& pageUID,		// UID of page 
				const UID& pageItemUID):// UID of page items on master spread
			fPageUID(pageUID),
			fPageItemUID(pageItemUID) {}
	
		bool16 operator==(const MasterPageItemInfo& other) const
		{ 
			//return ((fPageUID == other.fPageUID) && (fPageItemUID == other.fPageItemUID));
			return (fPageItemUID == other.fPageItemUID);
		}

		void KeyReadWrite(IPMStream *s)
		{
			s->XferInt32((int32&)fPageUID);
			s->XferInt32((int32&)fPageItemUID);
		}

		void ValueReadWrite(IPMStream *s)
		{
			s->XferReference(fPageUID);
			s->XferReference(fPageItemUID);
		}

		UID     fPageUID;
		UID		fPageItemUID;
};

typedef K2Vector<KeyValuePair<MasterPageItemInfo, MasterPageItemInfo> >  SyncMasterSpreadPageItemMap;
typedef K2Vector<KeyValuePair<UID, UID> >  SyncMasterSpreadPageMap;

/** This interface resides on kDocBoss. It has a map recording which page item on the target was loaded 
	from source document. It also caches the sync master page options (either replace or rename).
*/
class ISyncMasterPageData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISYNCMASTERPAGEDATA };

		enum SyncMasterPageOptions { kReplace = 1, kRename } ;

		/** Set synchronizing master spread page item info on the document boss 
		    which has source MasterPageItemInfo as key and target MasterPageItemInfo as value.
		    @param newMap [IN] the new map to be set.
		*/
		virtual void SetSyncMasterSpreadPageItemMap(const SyncMasterSpreadPageItemMap& newMap) = 0;

		/** Get the map about synchronizing master spread page item info on the document boss.
			@return SyncMasterSpreadPageItemMap.
		*/
		virtual const SyncMasterSpreadPageItemMap& GetSyncMasterSpreadPageItemMap() = 0;

		/** Set synchronizing master spread page which has the source page UID as key and 
		    target page UID as value.
			@param newMap [IN] the new map to be set.
		*/
		virtual void SetSyncMasterSpreadPageMap(const SyncMasterSpreadPageMap& newMap) = 0;

		/** Get the map about synchronizing master spread page info on the document boss.
			@return SyncMasterSpreadPageMap.
		*/
		virtual const SyncMasterSpreadPageMap& GetSyncMasterSpreadPageMap() = 0;

		/** Get the option of synchronization master spreads.
		    @return ISyncMasterPageData::SyncMasterPageOptions, either kReplace or kRename.
		*/
		virtual const ISyncMasterPageData::SyncMasterPageOptions& GetSyncMasterPagePageItemOptionSetting() = 0;

		/** Set the option of synchronization master spreads.
		    @param pageItemOption [IN]: either kReplace or kRename.
		*/
		virtual void SetSyncMasterPagePageItemOptionSetting(const ISyncMasterPageData::SyncMasterPageOptions& pageItemOption) = 0;
};

#endif // __ISYNCMASTERPAGEDATA__
