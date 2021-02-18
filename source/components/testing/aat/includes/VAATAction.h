//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/VAATAction.h $
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
#ifndef __VAATAction__
	#define __VAATAction__
	
#include "ProductTypeDefs.h"

class AATActionHexID;
class VirtualDataList;
class ISequenceList;
class VAATData;
class IAATSessionProperties;
class IXMLOutStream;
class ISequenceItem;
class IAATActionList;

typedef enum {
		kUIFlag =			0x8000, 		// uses the high bit
		kJapaneseFlag = 	0x4000,			// another "shared" bit
		kInDesign = 		0x0001,
		kInCopy = 			0x0002,
		kInDesignServer = 	kInDesign,
		kInDesignUI = 		kInDesign | kUIFlag,
		kInCopyUI = 		kInCopy | kUIFlag,
		kInDesignJ = 		kJapaneseFlag | kInDesign,
		kInCopyJ = 			kJapaneseFlag | kInCopy,
		kInDesignJUI = 		kInDesignJ | kUIFlag,	//These needed to be added because sometimes there are 
		kInCopyJUI = 		kInCopyJ | kUIFlag,		//J UI requirements - like for the IME
		
		kAllProducts = 		kInDesign | kInCopy		// please update me if more products are added!
	}eProductCompatibility;


class VAATAction
{
	public:	
		virtual ~VAATAction(void) {}
		
		virtual ErrorCode Execute(void) = 0;
		virtual void 	Init(void) = 0;
		virtual ProdBool	IsInited(void) = 0;
		
		virtual void			WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse) = 0;
		
		virtual ProdBool		IsContainerAATAction(void) = 0;
		virtual void			AddContainedItem(ISequenceItem *test, int32 index = -1) = 0;
		virtual void			RemoveNthContainedItem(int32 index) = 0;
		virtual ProdInt32		GetIndexOfItem(uint32 itemID) = 0;
		virtual ProdBool		ContainsItem(uint32 itemID) = 0;
		
		virtual bool16			IsGenericAction(void) = 0;
		
		virtual void			SetParentAATAction(VAATAction *action) = 0;
		virtual VAATAction*		GetParentAATAction(void) = 0;
		
		virtual ProdInt32		GetNumContainedItems(void) = 0;
		virtual ISequenceItem* 	GetNthContainedItem(ProdInt32 index) = 0;
		
		virtual ProdString 	GetInstanceName(void) = 0;
		virtual void		SetInstanceName(ProdString &str) = 0;
		
		virtual void		SetFlavor(const PMString &str) = 0;
		virtual ProdString	GetFlavor(void) = 0;
		
		virtual ProdString	GetTypeName(void) = 0;
		virtual void		SetTypeName(ProdString &str) = 0;
		
		virtual void				SetAATActionList(IAATActionList *parentList) = 0;
		virtual IAATActionList*		GetAATActionList(void) = 0;
		
		virtual ISequenceList*	GetParentSequence(void) = 0;
		virtual void			SetParentSequence(ISequenceList* parent) = 0;
		
		virtual ProdBool	ShowInSourceTree(void) = 0;
		virtual void	SetShowInSourceTree(ProdBool show) = 0;
		
		virtual AATActionHexID GetAATActionID(void) = 0;
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList) = 0;
		virtual void	InitForEdit(void) = 0;
		
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags) = 0;
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version) = 0;
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil) = 0;
		
		virtual ProdInt32	GetVersion(void) = 0;
		
		virtual ProdBool	SupportsExtensibleParams(void) = 0;
		virtual bool16		AddParam(const PMString &token, const PMString &type, const PMString &value, VAATData **dataHndl) = 0;
		
		virtual ProdInt32	GetProductCompatibility(void) = 0;
		virtual ProdBool	IsCompatibleWith(eProductCompatibility product) = 0;
		
		virtual void	SetSessionProperties(IAATSessionProperties *props) = 0;
		
		virtual ProdString	GetUIString(void) = 0;
    
        virtual ProdBool    RequiresUIThread(void) const = 0;

        virtual ErrorCode ExecuteInUIThread(void) = 0; // Execute the test in the main UI thread only
    
        virtual ErrorCode ExecuteFromMainThread() = 0;  // This is really complicated. I am just testing this now. Once this works, I will have to write a really long documentation of this work.
};


#endif //__VAATAction__


