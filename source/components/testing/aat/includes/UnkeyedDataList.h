//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/UnkeyedDataList.h $
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
#ifndef __UnkeyedDataList__
	#define __UnkeyedDataList__

#include "K2Pair.h"

#include "AATDataTypes.h"



class AATLIB_DECL UnkeyedDataList : public CAATData
{
	public:
		UnkeyedDataList(const ProdString &tag,  
					const ProdString &varName,
					const ProdString &uiString,
					ProdInt32 code);
		UnkeyedDataList(void);
		virtual ~UnkeyedDataList();
		
		virtual VirtualType GetType(void) { return kUnkeyedDataListType; }
		
		virtual	void	Write(IXMLOutStream *stream, ProdBool asModel);
		virtual void	WriteSubData(IXMLOutStream *stream, ProdBool asModel);
		virtual void	WriteUIData(IXMLOutStream *stream);
		
		virtual ProdBool	IsInSubData(void);
		virtual ProdInt32	GetMatchingCount(void) { return fMatchingTagCount; }
		virtual ProdInt32	IsOpen(void) { return fMatchingTagCount > 0; }
		
		virtual	void	Read(const ProdString &localName, ISAXAttributes* attrs);
		
		virtual	void	StartElement(const ProdString &localName, ISAXAttributes* attrs);
		virtual	void	EndElement(const ProdString &localName);
		
		virtual void	Copy(VAATData *srcData);
		virtual void	Clear(void);
		
		
		//Adds the entry, if isDeletable is set to kTrue, List will delete item when list
		//destructs or item is removed.  By default, the list does NOT own the memory.
		virtual ProdBool 		AddDataEntry(VAATData *dataEntry, ProdBool isDeletable = kFalse);
		virtual ProdBool 		RemoveNthDataEntry(ProdInt32 index);
		
		virtual ProdInt32 		Length(void);
		virtual VAATData* GetNthDataEntry(ProdInt32 index);
		
		virtual VAATData& operator[](const ProdInt32 index) const;
		
	protected:
		K2Vector<VAATData*> fDataList;
		K2Vector<ProdBool>		  fDeletable;
		ProdBool					  fInSubData;
		ProdInt32					  fMatchingTagCount;
};



#endif //__UnkeyedDataList__