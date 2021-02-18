//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CAATActionList.h $
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
#ifndef __CAATActionList__
	#define __CAATActionList__

#include "IAATActionList.h"

#define kAATActionListVersion 1



class AATLIB_DECL CAATActionList : public IAATActionList
{
	public:
		CAATActionList(IPMUnknown *boss);
		virtual ~CAATActionList();
		
		//Return the tag to be used when starting an entry in an XML file.
		virtual	ProdString	GetPrimaryTag(void);
		
		virtual	void	GetHierarchyIndicies(K2Vector<int32> &indicies);
		
		virtual ProdString 	GetListName(void) { return fName; }
		
		virtual ErrorCode Execute(IAATSessionProperties* properties);
		
		//Initialization
		virtual ProdBool	Init(void);
		virtual ProdBool 	IsInited(void) { return fInited; }
		virtual void	InitForEdit(void);
		
		virtual void 	RegisterWithFactory(IAATFactory *factory);

		virtual ProdString	GetDefaultTreeLocation(void);
		
		virtual void 	AddAATActionID(AATActionHexID id);
		virtual void 	RemoveAATActionID(AATActionHexID &id);
		virtual ProdBool	HasThisID(AATActionHexID &id);
		
		virtual ProdInt32 GetNumAATActionIDs(void);
		virtual AATActionHexID* GetNthAATActionID(ProdInt32 index);
		
		
		virtual ProdBool SetActiveAATAction(AATActionHexID &id);
		virtual VAATAction* GetActiveAATAction(void);
		
		virtual AATActionHexID GetActiveAATActionID(void);
		
		virtual ProdBool		GetBreak(void) { return fBreak; }
		virtual void			SetBreak(ProdBool breakMe) { fBreak = breakMe; }
		
		virtual	void	WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse);
		
		virtual ProdString	GetUIString(void);
		virtual	ProdString 	GetName(void);
		
		virtual void		SetParent(ISequenceList *seq);
		
		virtual IReadWriteTest* 	Duplicate(ProdBool copyChildren);
		
		virtual K2Vector<IReadWriteTest*>	Search(const PMString& searchFor, K2Vector<int32> currentPath, K2Vector<K2Vector<int32> >& foundList);		
		
		virtual bool16		IsGenericActionList(void) { return kFalse; }
		
		virtual void	SetActiveAATActionVersion(ProdInt32 version) { fReadAATActionVersion = version; }
		virtual ProdInt32	GetActiveAATActionVersion(void) { return fReadAATActionVersion; }
		
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version);
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil);
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags);
		
		virtual ProdBool	SupportsExtensibleParams(void);
		
	protected:
		virtual VAATAction*	CreateActionFromID(AATActionHexID &id);
		
		//Override this to add in your action IDs.  This is called by the base
		//class when Init is called.  fInited is set by the return value.
		virtual ProdBool	Initialize(void) = 0;
		
		//override this method to register your actions.  This is called by the 
		//base class when RegisterWithFactory is called.
		virtual void 	RegisterAATActions(IAATFactory *factory) = 0;
		
		virtual void	CollectReadWriteParams(void);
		
		virtual void	StartLogEntry(LogObject *theLog);
		virtual void	EndLogEntry(LogObject *theLog, ProdReal elapsedTime, ErrorCode result);
		
		K2Vector<AATActionHexID*> fAATActions;
		VAATAction		*fActiveTest;
		
		ProdBool 			fInited;
		qaBool16			fBreak;
		ProdInt32 		fReadAATActionVersion;
		K2Vector<ClassID> 	fAddOns;
		
	private:
		virtual void	ProcessAddOns(void);
		virtual void	RegisterAddOns(IAATFactory *factory);
};



#endif //__CAATActionList__



