//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IReadWriteTest.h $
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
#ifndef __IReadWriteTest__
	#define __IReadWriteTest__

#include "IPMUnknown.h"
#include  "IXMLOutStream.h"

#include "ProductTypeDefs.h"

class ISAXAttributes;
class VirtualDataList;
class IXMLOutStream;
class VAATData;


class IReadWriteTest : public IPMUnknown
{
	public:
	
		typedef enum {
			kUnknownType = 0,
			kSessionType = 1,
			kSequenceListType,
			kAATActionListType,
			kOtherSeqItemType,
			kReadWriteContainerType,
			kDialogDescriptionType,
			kDialogDescriptionListType
		}eReadWriteTestType;

		virtual ~IReadWriteTest() {}
		
		virtual ProdBool	Init(void) = 0;
		virtual ProdBool	IsInited(void) = 0;
		
		virtual void	WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse) = 0;
		
		//Return the tag to be used when starting an entry in an XML file.
		virtual	ProdString	GetPrimaryTag(void) = 0;
		
		virtual VirtualDataList* GetDataList(void) = 0;
		
		virtual void	GetHierarchyIndicies(K2Vector<int32> &indicies) = 0;
		
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags) = 0;
		
		virtual ProdBool	ApplyParam(VAATData &data, ProdInt32 version) = 0;
		virtual void 	WriteParams(IXMLOutStream *stream, ProdBool asModel, VirtualDataList *editedList = nil) = 0;
		
		virtual ProdString 	GetName(void) = 0;
		virtual void		SetName(const ProdString &str) = 0;
		
		virtual void	CommentOut(ProdBool rem) = 0;
		virtual ProdBool	IsCommentedOut(void) = 0;
		
		virtual ProdInt32	GetVersion(void) = 0;
		virtual void	IncrementVersion(void) = 0;
		virtual void	DecrementVersion(void) = 0;
		
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version) = 0;
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil) = 0;
		
		virtual IReadWriteTest* Duplicate(ProdBool copyChildren=kTrue) = 0;
		
		virtual eReadWriteTestType 	GetReadWriteTestType() = 0;
		virtual void	 			SetReadWriteTestType(eReadWriteTestType theType) = 0;
		
		virtual ProdBool	SupportsExtensibleParams(void) = 0;
		virtual ProdBool	AddParamExtension(VAATData *dataPtr) = 0;
		virtual ProdBool	RemoveParamExtension(const ProdString &tag) = 0;
		
		virtual ProdInt32		GetNumParamExtensions(void) = 0;
		virtual ProdString	GetNthParamExtensionTag(ProdInt32 index) = 0;
		
		virtual void	InitForEdit(void) = 0;
		virtual void	PostEdit(void) = 0;
		
		virtual K2Vector<IReadWriteTest*>	Search(const PMString& searchFor, K2Vector<int32> currentPath, K2Vector<K2Vector<int32> >& foundList) = 0;
		
	protected:
		virtual void CollectReadWriteParams(void) = 0;
};


#endif //__IAATFactory__
