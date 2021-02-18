//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/VAATData.h $
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
#ifndef __VAATData__
	#define __VAATData__
	
#include "ProductTypeDefs.h"

const ProdInt32 kUnsetIteration(-1);

class IXMLOutStream;
class ISAXAttributes;
	
class VAATData
{
	public:
		virtual ~VAATData() {}
		
		typedef enum {
			kInvalidDataType = 0,
			kPMRealType = 1,
			kPMStringType,
			kQARectType,
			kint32Type,
			kuint32Type,
			kcharType,
			kbool16Type,
			kQAPointType,
			kUIDType,
			kUIDRefType,
			kUIDListType,
			kDataListType,
			kUnkeyedDataListType,
			kIndeterminateType,
			kQAMeasurementType,
			kQAFileType,
			kScarfDataType,
			kLastDataType
		} VirtualType;
		
		virtual void	Write(IXMLOutStream *stream, ProdBool asModel) = 0;
		virtual void	Read(const ProdString &localName, ISAXAttributes* attrs) = 0;
		
		virtual void	Copy(VAATData *srcData) = 0;
		
		virtual VirtualType GetType(void) = 0;
		
		virtual ProdString GetTag(void) = 0;
		virtual void 	 SetTag(const ProdString &str) = 0;
	
		virtual ProdInt32	GetIterationKey(void) const = 0;
		virtual void	SetIterationKey(ProdInt32 val) = 0;
		virtual ProdBool	CanAssign(ProdInt32 iter) = 0;
		
		virtual ProdString	GetVariableName(void) = 0;
		virtual void	SetVariableName(const ProdString &str) = 0;
		
		virtual void	SetIsPosting(ProdBool post) = 0;
		virtual ProdBool	GetIsPosting(void) = 0;
		
		virtual ProdString GetUITextString(void) = 0;
		virtual void SetUITextString(const ProdString &str) = 0;
		
		virtual ProdString 	GetUIElementString(void) = 0;
		virtual ProdInt32 		GetUIElementCode(void) = 0;
		virtual void 		SetUIElement(ProdInt32 code) = 0;
		
		virtual void		SetGrouping(const ProdString &group) = 0;
		virtual ProdString	GetGrouping(void) = 0;
		
		virtual ProdBool	IsEditable(void) = 0;
		virtual void	SetEditable(ProdBool edit) = 0;
		
		virtual ProdBool		AddAcceptableValue(const ProdString &str) = 0;
		virtual ProdBool		ReadAcceptableFromFile(void) = 0;
		virtual void		SetReadAcceptable(ProdBool readIt) = 0;
		virtual ProdBool		WriteAcceptableToFile(void) = 0;
		virtual void		SetWriteAcceptable(ProdBool writeIt) = 0;
		
		virtual void		ClearAcceptableValues(void) = 0;
		virtual void		SetValueFromAcceptableValues(ProdInt32 index) = 0;
		virtual ProdInt32		GetNumAcceptableValues(void) = 0;
		virtual ProdString* 	GetNthAcceptableValue(ProdInt32 index) = 0;
};





#endif //__VAATData__
