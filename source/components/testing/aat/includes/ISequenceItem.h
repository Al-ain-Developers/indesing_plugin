//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/ISequenceItem.h $
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
#ifndef __ISequenceItem__
	#define __ISequenceItem__
	
#include "CReadWriteTest.h"
#include "K2Pair.h"

class ISequenceList;
class IAATSessionProperties;
class LogObject;
class VirtualDataList;

typedef enum {
		kAlwaysFirst = 1,
		kAlwaysLast,
		kKeepWithNext,
		kKeepWithPrev,
		kAnyOrder
	}eReorderFlags;

typedef enum {
		kUnknownItemType = 0,
		kSeqList = 1,
		kAATActionList,
		kObjectFinder
	}eSeqItemType;
	
class ISequenceItem : public CReadWriteTest
{
	public:
		ISequenceItem(IPMUnknown *boss) : CReadWriteTest(boss) {}
		virtual ~ISequenceItem() {}
		
		virtual ErrorCode Execute(IAATSessionProperties* properties) = 0;
		
		//return a : delimited string indicating desired location in default Editor Source Tree
		virtual ProdString	GetDefaultTreeLocation(void) = 0;
		virtual void		SetDefaultTreeLocation(const ProdString &str) = 0;
		
		virtual eReorderFlags	GetReorderFlag(void) = 0;
		virtual void			SetReorderFlag(eReorderFlags flag) = 0;
		
		virtual eSeqItemType	GetItemType(void) = 0;
		virtual void			SetItemType(eSeqItemType type) = 0;
		
		virtual void		SetParent(ISequenceList *seq) = 0;
		virtual ISequenceList* GetParent(void) = 0;
		
		virtual ProdString	GetUIString(void) = 0;
		
		virtual ProdUInt32	GetItemUID(void) = 0;
		virtual void		SetItemUID(ProdUInt32 id) = 0;
		
		virtual int32		GetSourceBuildNumber(void) = 0;
		virtual void		SetSourceBuildNumber(int32 buildNum) = 0;
		
		virtual PMReal		GetSourceProdVersion(void) = 0;
		virtual void		SetSourceProdVersion(const PMReal &prod) = 0;
		
		//Note that base impl only converts it's own UID NOT any refs!
		virtual void		ConvertItemUIDRefs(const K2Vector< K2Pair<ProdUInt32, ProdUInt32> >&oldIDs) = 0;
	
	protected:
		virtual void	StartLogEntry(LogObject *theLog) = 0;
		virtual void	EndLogEntry(LogObject *theLog, ProdReal elapsedTime=-1.0, ErrorCode result=kSuccess) = 0;
};

//Technically this is not invalid, but indicates the highest SequenceList.
#define kInvalidItemUID 0

#endif //__ISequenceItem__







