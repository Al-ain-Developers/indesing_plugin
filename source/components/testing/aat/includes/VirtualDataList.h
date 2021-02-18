//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/VirtualDataList.h $
//  
//  Owner: Gregor Kaplan
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __KeyVirtualDataList__
	#define __KeyVirtualDataList__

#include "K2Pair.h"

#include "UnkeyedDataList.h"



class AATLIB_DECL VirtualDataList : public UnkeyedDataList
{
	public:
		VirtualDataList(const ProdString &tag,  
					const ProdString &varName,
					const ProdString &uiString,
					ProdInt32 code);
		VirtualDataList(void);
		virtual ~VirtualDataList();
		
		virtual VirtualType GetType(void) { return kDataListType; }
		
		virtual void	Copy(VAATData *srcData);
		
		//Adds the entry, if isDeletable is set to kTrue, List will delete item when list
		//destructs or item is removed.  By default, the list does NOT own the memory.
		virtual ProdBool 		AddKeyDataEntry(VAATData *dataEntry, ProdBool isDeletable = kFalse);
		virtual ProdBool 		AddDataEntry(VAATData *dataEntry, ProdBool isDeletable = kFalse);
		
		virtual ProdBool 		RemoveKeyDataEntry(const ProdString &key);
		
		virtual ProdInt32 			Length(void);
		virtual ProdString 			GetNthKey(ProdInt32 index);
		virtual ProdInt32			GetIndexOfKey(const ProdString &key);
		virtual VAATData* 	GetDataEntry(const ProdString &key);
		
		//Copies data which has the same grouping
		virtual	void	GetGroupNames(K2Vector<ProdString> &groupVec);
		virtual void	GetDataByGroup(const ProdString  &groupID, VirtualDataList *copyTo);
		
		virtual VAATData& operator[](const ProdInt32 index) const;
		
	protected:
};



#endif //__KeyVirtualDataList__