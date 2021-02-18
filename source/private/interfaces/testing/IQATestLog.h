//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/interfaces/testing/IQATestLog.h $
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
#ifndef __IQATestLog__
	#define __IQATestLog__

#include "IPMUnknown.h"

class QAFile;
class BaseTestMessage;

class IQATestLog : public IPMUnknown
{
	public:
		virtual ~IQATestLog() {}
		
		virtual void	Init(void) = 0;
		virtual bool16	IsInited(void) = 0;
		
		virtual void	CloseLog(void) = 0;
		virtual bool16	Good(void) = 0;
		
		virtual void	SetFile(const QAFile *logFile) = 0;
		virtual void	SetWriteMemoryInfo(bool16 writeIt) = 0;
		virtual void	SetUseNewFile(bool16 newFile) = 0;
		virtual void	SetWriteTrailer(bool16 writeIt) = 0;
		
		virtual void		SetKey(const PMString &key) = 0;
		virtual PMString	GetKey(void) = 0;
		
		virtual void		Error(const PMString &msg) = 0;
		virtual	void		Warning(const PMString &msg) = 0;
		virtual	void		FatalError(const PMString &msg) = 0;
		virtual	void		Comment(const PMString &msg) = 0;
		virtual	void		ResultFile(const  PMString &msg) = 0;
		virtual	void		Alert(const PMString &msg) = 0;
		virtual	void		Assert(const PMString &msg) = 0;
		virtual	void		Step(const PMString &msg) = 0;

		virtual	void		LogString(PMString &format, const PMString &msg) = 0;
		
		virtual void		Message(const PMString &msg) = 0;
		virtual void		Message(void *msg) = 0;
		virtual void		Message(BaseTestMessage *msg) = 0;
		
		virtual void		WriteSeparator(void) = 0;
		
		virtual void		PushMessageHeader(const PMString &head) = 0;
		virtual void		PopMessageHeader(void) = 0;
};

#define kQASessionLogName 	 	"QASessionLog.txt"
#define kQASessionXMLLogName  	"QASessionLog.xml"
#define kQASessionLogKeyStr		"DefaultTestLog"
#define kQASessionXMLLogKeyStr	"DefaultXMLTestLog"

#endif //__IQATestLog__


