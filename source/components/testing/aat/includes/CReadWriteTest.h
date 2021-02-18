//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CReadWriteTest.h $
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
#ifndef __CReadWriteTest__
	#define __CReadWriteTest__

#include "IReadWriteTest.h"
#include "UnitIDs.h"
#include "AATDataTypes.h"

class Stopwatch;


class AATLIB_DECL CReadWriteTest : public CPMUnknown<IReadWriteTest>
{
	public:
		CReadWriteTest(IPMUnknown *boss);
		virtual ~CReadWriteTest();
		
		//Override these if your impl needs to initialize itself.
		virtual ProdBool	Init(void) { return kTrue; }
		virtual ProdBool	IsInited(void) { return kTrue; }
		
		//Return the tag to be used when starting an entry in an XML file.
		virtual	ProdString	GetPrimaryTag(void);
		
		virtual VirtualDataList* GetDataList(void);
		
		virtual void	GetHierarchyIndicies(K2Vector<int32> &indicies);
		
		virtual void	WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse);
		
		virtual ProdBool	ApplyParam(VAATData &data, ProdInt32 version);
		virtual void WriteParams(IXMLOutStream *stream, ProdBool asModel, VirtualDataList *editedList = nil);
		
		//This class can stand on its own, but descendents will need to set/get their names
		virtual ProdString 	GetName(void) { return fName.Get(); }
		virtual void		SetName(const ProdString &str) { fName = str; }
		
		virtual void	CommentOut(ProdBool rem) { fRemOut = rem; }
		virtual ProdBool	IsCommentedOut(void) { return fRemOut; }
		
		virtual ProdInt32	GetVersion(void) { return fVersion; }
		virtual void	IncrementVersion(void) { fVersion = fVersion + 1; }
		virtual void	DecrementVersion(void) { fVersion = fVersion - 1; }
		
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version);
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil);
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags);
		
		virtual IReadWriteTest* Duplicate(ProdBool copyChildren);
		
		virtual eReadWriteTestType 	GetReadWriteTestType() { return fRWTType; }
		virtual void	 			SetReadWriteTestType(eReadWriteTestType theType) { fRWTType = theType; }
		
		virtual ProdBool	SupportsExtensibleParams(void) { return fSupportsExtensions; }
		virtual ProdBool	AddParamExtension(VAATData *dataPtr);
		virtual ProdBool	RemoveParamExtension(const ProdString &tag);
		
		virtual ProdInt32		GetNumParamExtensions(void);
		virtual ProdString	GetNthParamExtensionTag(ProdInt32 index);
		
		virtual void	InitForEdit(void);
		virtual void	PostEdit(void);
		
		virtual K2Vector<IReadWriteTest*>	Search(const PMString& searchFor, K2Vector<int32> currentPath, K2Vector<K2Vector<int32> >& foundList);

		
	protected:
		virtual void	CollectReadWriteParams(void);
		virtual void	RefreshDataList(void);
		virtual void	LogResult(LogObject *theLog, PMReal elapsed = -1.0, PMString initialStr = "" , ErrorCode result = kSuccess, bool16 unindentLog = kTrue);
		
		VirtualDataList		*fDataList;
		qaString 			fName;
		eReadWriteTestType	fRWTType;
		qaBool16			fSupportsExtensions;
		qaString			fComment;
		qaBool16			fRemOut;
		
		VirtualDataList		*fParamExtensions;
		K2Vector<ProdString>	fConvertTags;
		
	private:
		
		qaInt32		fVersion;
};


#endif //__CReadWriteTest__