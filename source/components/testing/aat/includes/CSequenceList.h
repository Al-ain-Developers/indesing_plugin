//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CSequenceList.h $
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
#ifndef __CSequenceList__
	#define __CSequenceList__
	
#include "ISequenceList.h"
#include "SequenceMessagingRegistry.h"

#define kSequenceListVersion 1



class AATLIB_DECL CSequenceList : public ISequenceList
{
	public:
		CSequenceList(IPMUnknown *boss);
		virtual ~CSequenceList();
		
		//Return the tag to be used when starting an entry in an XML file.
		virtual	ProdString	GetPrimaryTag(void);
		
		virtual	void	GetHierarchyIndicies(K2Vector<int32> &indicies);
		
		//Initialize - if used in session/sequence don't call until parent is set!
		virtual ProdBool	Init(void);
		virtual ProdBool	IsInited(void) { return fInited; }
		
		//Set/Get the parent Session
		virtual void			SetParentSession(ITestSession *ses);
		virtual ITestSession*	GetParentSession(void);
		
		virtual ProdString	GetDefaultTreeLocation(void);
		
		virtual ProdString	GetListType(void) { return fListKind.Get(); }
		virtual void		SetListType(ProdString type) { fListKind = type; }
		
		//Get the current iteration
		virtual ProdInt32		GetCurrentIteration(void) { return fCurIteration; }
		
		//Execution method - std single pass
		virtual ErrorCode Execute(IAATSessionProperties* properties);
		
		virtual	void	WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse);
		
		virtual ProdString	GetUIString(void);
		
		virtual IReadWriteTest* 	Duplicate(ProdBool copyChildren);
		
		virtual K2Vector<IReadWriteTest*>	Search(const PMString& searchFor, K2Vector<int32> currentPath, K2Vector<K2Vector<int32> >& foundList);

		virtual void		SetParent(ISequenceList *seq);
		
		//Add/Remove sequence items.  Also access to items
		virtual void			AddSequenceItem(ISequenceItem *test, ProdInt32 index);
		virtual ProdInt32		GetNumSequenceItems(void);
		virtual void			RemoveNthSequenceItem(ProdInt32 index);
		virtual ISequenceItem*	GetNthSequenceItem(ProdInt32 index);
		virtual ProdInt32		GetNumActions();
		
		//New Messaging system
		virtual void		ProcessKeys(VirtualDataList *dataList);
		
		virtual ProdBool	AddSharedDataKey(const ProdString &key);
		virtual void		AddSharedDataEntry(VAATData *listner);
		virtual void		RemoveSharedDataEntry(VAATData *listner);
		virtual void 		ClearMessageRegistry();
		virtual void		ResetMessageRegistry();
		virtual void		PostMsg(VAATData *data);
		
		virtual ISequenceItem*	GetItemByItemUID(uint32	uid);
		virtual bool16			ContainsItem(ProdUInt32 id, bool16 checkParent);
		
		virtual ProdUInt32		NewItemUID(ISequenceItem *item);
		virtual ProdUInt32		GetLastItemUID(void);
		virtual void			SetLastItemUID(ProdUInt32 lastID);
		
		virtual void			ConvertItemUIDs(ISequenceList *list, K2Vector<K2Pair<uint32, uint32> > &convertedIDs);
		virtual void			ApplyItemIDConversions(K2Vector<K2Pair<uint32, uint32> > &convertedIDs);

		virtual void			GetChildActionsUID(K2Vector<ProdUInt32> &actionUIDs);
	protected:
		
		virtual void		ProcessKeys(ISequenceItem *item);
		virtual void		ProcessItemUIDs(ISequenceItem *item, bool16 checkDupes);
		virtual void		ConvertItemID(ISequenceItem *item, K2Vector<K2Pair<uint32, uint32> > &convertedIDs);
		
		virtual void		XferAndDeleteKeys(ISequenceList* recipient);
		
		virtual void		CollectReadWriteParams(void);
		
		virtual void		StartLogEntry(LogObject *theLog);
		virtual void		EndLogEntry(LogObject *theLog, ProdReal elapsedTime, ErrorCode result);
		
		
		SequenceMessagingRegistry	*fMsgReg;
		K2Vector<ISequenceItem*> 	fTestReg;
		ITestSession				*fParentSession;
		
		qaString					fListKind;
		qaInt32						fCurIteration;
		ProdBool					fInited;
		
	private:
		ProdUInt32			fLastUID;
};



#endif //CSequenceList




		
			
		
		



