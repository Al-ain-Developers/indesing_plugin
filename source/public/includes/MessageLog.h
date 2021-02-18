//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MessageLog.h $
//  
//  Owner: Michael Burbidge
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __MessageLog_h__
#define __MessageLog_h__

#include <iostream>

class MessageLogImpl;

//========================================================================================
// CLASS MessageLog
//========================================================================================

class PUBLIC_DECL MessageLog
{
public:
	enum Manipulator { kNewLine, kTab, kFlush };
	enum Translate { kDontTranslate, kTranslate, kBootStrapTranslate };
	
	MessageLog(std::ostream& stream, const int16& level);
	virtual ~MessageLog();
	
	void SetImpl(MessageLogImpl* impl);
	
	MessageLog& Write(const Manipulator& manipulator);
	MessageLog& Write(const PMString& msg, const PMString& label = "server", const Translate& translate = kTranslate);
	MessageLog& Write(const PMString& msg, const ErrorCode& errorCode, const PMString& label = "server", const Translate& translate = kTranslate);

private:
	MessageLogImpl*	fImpl;
	std::ostream&	fStream;
	int16			fLevel;
};

extern PUBLIC_DECL MessageLog gInfoLog;
extern PUBLIC_DECL MessageLog gWarnLog;
extern PUBLIC_DECL MessageLog gErrorLog;

#endif
