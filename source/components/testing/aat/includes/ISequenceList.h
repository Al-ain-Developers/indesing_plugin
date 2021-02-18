//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/ISequenceList.h $
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
#ifndef __ISequenceList__
	#define __ISequenceList__
	
#include "CSequenceItem.h"

class QAObjectRef;
class VirtualDataList;
class ITestSession;

class ISequenceList : public CSequenceItem
{
	public:
		ISequenceList(IPMUnknown *boss) : CSequenceItem(boss) {}
		virtual ~ISequenceList() {}
		
		//Initialize - if used in session/sequence don't call until parent is set!
		virtual ProdBool	Init(void) = 0;
		virtual ProdBool	IsInited(void) = 0;
		
		//Set/Get the parent Session
		virtual void			SetParentSession(ITestSession *ses) = 0;
		virtual ITestSession*	GetParentSession(void) = 0;
		
		//Get Loop kind
		virtual ProdString	GetListType(void) = 0;
		virtual void		SetListType(ProdString type) = 0;
		
		virtual ProdInt32		GetCurrentIteration(void) = 0;
		
		//Execution method - std single pass
		virtual ErrorCode Execute(IAATSessionProperties* properties) = 0;
		
		//Add/Remove sequence items.  Also access to items
		// AddSequenceItem adds the item before the item currently at that index
		virtual void			AddSequenceItem(ISequenceItem *test, ProdInt32 index=-1) = 0;
		virtual ProdInt32			GetNumSequenceItems(void) = 0;
		virtual void			RemoveNthSequenceItem(ProdInt32 index) = 0;
		virtual ISequenceItem*	GetNthSequenceItem(ProdInt32 index) = 0;
		// Gets the number of actions, including in its child sequences
		virtual ProdInt32			GetNumActions() = 0;
		
		//Messaging system for shared data
		virtual void	ProcessKeys(VirtualDataList *dataList) = 0;
		virtual ProdBool	AddSharedDataKey(const ProdString &key) = 0;
		virtual void	AddSharedDataEntry(VAATData *listner) = 0;
		virtual void	RemoveSharedDataEntry(VAATData *listner) = 0;
		virtual void 	ClearMessageRegistry() = 0;
		virtual void	ResetMessageRegistry() = 0;
		
		virtual void	PostMsg(VAATData *data) = 0;
		
		virtual ISequenceItem*	GetItemByItemUID(uint32	uid) = 0;
		virtual bool16			ContainsItem(ProdUInt32 id, bool16 checkParent) = 0;
		
		virtual ProdUInt32		NewItemUID(ISequenceItem *item) = 0;
		virtual ProdUInt32		GetLastItemUID(void) = 0;
		virtual void			SetLastItemUID(ProdUInt32 lastID) = 0;
		
		virtual void			ConvertItemUIDs(ISequenceList *list, K2Vector<K2Pair<uint32, uint32> > &convertedIDs) = 0;
		virtual void			ApplyItemIDConversions(K2Vector<K2Pair<uint32, uint32> > &convertedIDs) = 0;

		virtual void			GetChildActionsUID(K2Vector<ProdUInt32> &actionUIDs) = 0;
		
	protected:
		
		// transfers this sequence's keys to the recipient, then deletes them from its own registry.
		virtual void	XferAndDeleteKeys(ISequenceList* recipient) = 0;
		
		
};

#endif //ISequenceList






