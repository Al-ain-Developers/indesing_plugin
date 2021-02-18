//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/ITestSession.h $
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
#ifndef __ITestSession__
	#define __ITestSession__
	
#include "CReadWriteTest.h"

class ISequenceList;
class IAATSessionProperties;
class ITestSessionList;

class ITestSession : public CReadWriteTest
{
	public:
		ITestSession(IPMUnknown *boss) : CReadWriteTest(boss) {}
		virtual ~ITestSession() {}
		
		virtual	void	SetTestSessionList(ITestSessionList *parent) = 0;
		virtual ITestSessionList* GetTestSessionList(void) = 0;
		
		virtual void	WriteToStream(IXMLOutStream *s, ProdBool asModel = kFalse) = 0;
		
		virtual ErrorCode Execute(IAATSessionProperties* properties) = 0;
		
		virtual ProdReal	GetGlobalYield(void) = 0;
		virtual void		SetGlobalYield(ProdReal yield) = 0;
		
		// AddSequence adds the sequence before the item currently at the specified index
		//  thus giving the new item the specified index.
		virtual void	AddSequence(ISequenceList *seq, ProdInt32 index=-1) = 0;
		virtual void	RemoveNthSequence(ProdInt32 index) = 0;
		virtual ProdInt32	GetNumSequences(void) = 0;
		virtual ISequenceList* GetNthSequence(ProdInt32 index) = 0;
		virtual ProdBool	Clear() = 0;
		
		// Gets the number of actions in its child sequences
		virtual ProdInt32	GetNumActions() = 0;

		virtual ProdString	GetUIString() = 0;
		
		virtual void		Copy(ITestSession* copyThis) = 0;
		
		virtual void		SetSessionFile(const QAFile& file, ProdBool isRequiredFile = kFalse) = 0;
		virtual QAFile		GetSessionFile() = 0;
		virtual ProdBool		IsRequiredFile() = 0;

		virtual void		GetChildActionsUID(K2Vector<ProdUInt32> &actionUIDs) = 0;

};

#endif //__ITestSession__




