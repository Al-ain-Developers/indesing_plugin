//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CAATAction.h $
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
#ifndef __CAATAction__
	#define __CAATAction__
	
#include "VAATAction.h"
#include "AATDataTypes.h"

class AATActionHexID;
class VirtualDataList;
class ISequenceList;

#include "boost/bind.hpp"
#include "boost/function.hpp"
#include "IAsyncWorkManager.h"

class AATLIB_DECL CAATAction : public VAATAction
{
	public:
		CAATAction(const ProdString &typeStr, 
			const ProdString &subject, 
			const ProdString &product);
		virtual ~CAATAction(void);
		
		virtual ErrorCode Execute(void) = 0;
		
		//default is nothing.  Override if you need to do something after reading in
		virtual void 	Init(void) {}
		virtual ProdBool	IsInited(void) { return fInited; }
		
		virtual void			WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse);
		
		virtual ProdBool		IsContainerAATAction(void) { return kFalse; }
		virtual void			AddContainedItem(ISequenceItem *test, int32 index = -1);
		virtual void			RemoveNthContainedItem(int32 index);
		virtual ProdBool		ContainsItem(uint32 itemID);
		virtual ProdInt32		GetIndexOfItem(uint32 itemID);
		virtual ProdInt32		GetNumContainedItems(void);
		virtual ISequenceItem* 	GetNthContainedItem(ProdInt32 index);
		
		virtual bool16			IsGenericAction(void) { return kFalse; }
		
		virtual void		SetParentAATAction(VAATAction *action) { fParentContainer = action; }
		virtual VAATAction*	GetParentAATAction(void) { return fParentContainer; }
		
		
		virtual ProdString 	GetInstanceName(void) { return fName.Get(); }
		virtual void		SetInstanceName(ProdString &str) { fName = str; }
		
		virtual void		SetFlavor(const PMString &str) { fFlavor = str; }
		virtual ProdString	GetFlavor(void) { return fFlavor; }
		
		virtual ProdString		GetTypeName(void) { return fType.Get(); }
		virtual void			SetTypeName(ProdString &str) { fType = str; }
		
		virtual void				SetAATActionList(IAATActionList *parentList) { fParentList = parentList; }
		virtual IAATActionList*		GetAATActionList(void) { return fParentList; }
		
		virtual ISequenceList*	GetParentSequence(void) { return fParentSeq; }
		virtual void			SetParentSequence(ISequenceList* parent) { fParentSeq = parent; }
		
		virtual ProdBool	ShowInSourceTree(void) { return fShowInTree; }
		virtual void	SetShowInSourceTree(ProdBool show) { fShowInTree = show; }
		
		virtual AATActionHexID GetAATActionID(void) = 0;
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		virtual void	InitForEdit(void) { return; }
		
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags);
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version);
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil);
		
		virtual ProdInt32	GetVersion(void) { return fVersion; }
		
		virtual ProdBool	SupportsExtensibleParams(void) { return fSupportsExtensions; }
		virtual bool16		AddParam(const PMString &token, const PMString &type, const PMString &value, VAATData **dataHndl);
		
		virtual ProdInt32	GetProductCompatibility(void) { return fProductCompatibility; }
		virtual ProdBool	IsCompatibleWith(eProductCompatibility product);
		
		virtual void	SetSessionProperties(IAATSessionProperties *props);
		
		virtual ProdString	GetUIString(void);
    
        virtual ProdBool RequiresUIThread(void) const;
    
        virtual ErrorCode ExecuteInUIThread(void); // Execute the test in the main UI thread only
    
	protected:
		
		virtual void	ReportVerification(ProdString description, bool16 result);
		
		IAATActionList				*fParentList;
		ISequenceList 				*fParentSeq;
		VAATAction				*fParentContainer;
		IAATSessionProperties 	*fSessProps;
		K2Vector<ISequenceItem*>		fItems;
		
		qaString fName;
		qaString fType;
		qaString fTypeCode;
		qaBool16 fDefault;
		qaUIDRef fSubject;
		qaUIDRef fProduct;
		qaString fValidationLevel;
		qaBool16 fAbortOnError;
		qaBool16 fShowInTree;
		qaString fActionDescription;
		qaString fErrMsg;
		
		ProdBool	fSupportsExtensions;
		ProdString 	fFlavor;
		
		VirtualDataList		*fParamExtensions;
		
		ProdInt32 	fVersion;
		ProdInt32	fProductCompatibility;
		ProdBool	fInited;
    
    public:
        virtual ErrorCode ExecuteFromMainThread();
};



#endif //__CAATAction__


