//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagLoggingAPI.h $
//  
//  Owner: rbriggs 
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
#ifndef __IDiagLoggingAPI__
#define __IDiagLoggingAPI__

#include "IPMUnknown.h"
#include "IXMLOutStream.h"

/**
	Logging API for DiagnosticLog. Each information collector use this interface to communicate 
	with logger. Three classes implement this interface in DiagnosticLog.

	@see IDiagLoggerManager
	@see IDiagnosticLogger
	@see IDiagLogModifier	
*/
class IDiagLoggingAPI : public IPMUnknown 
{
public:
	/**
		Enter pre-defined context.

		@param context The name of context ("action", "command", etc.).
		@param attrs A reference to attribute list that contains the name and value pairs about context.
		@param Param1 A generic pointer associated with context. See following table
		@param Param2 A generic pointer associated with context. See following table

		<TABLE>
		<TR><TD><STRONG>Context</TD><TD>Param1</TD><TD>Param2</STRONG></TD></TR>
		<TR><TD>&quot;Action&quot;</TD><TD>nil</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Command&quot;</TD><TD>ICommand *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;CommmandSequence&quot;</TD><TD>ICommandSequence *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;IdleTask&quot;</TD><TD>nil</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Task&quot;</TD><TD>IdleTask *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Subject&quot;</TD><TD>ISubject *</TD><TD>changedBy *</TD></TR>
		<TR><TD>&quot;Observer&quot;</TD><TD>IObserver *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Signal&quot;</TD><TD>ISignalMgr *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Responder&quot;</TD><TD>IResponder *</TD><TD>nil</TD></TR>
		<TR><TD>&quot;Event&quot;</TD><TD>IEvent *</TD><TD>nil</TD></TR>
		</TABLE>
	*/
	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil, const void * Param2 = nil) = 0;


	/**
		Exit pre-defined context.

		@param context The name of context ("action", "command", etc.). It should match the context in 
		EnterContext method.
	*/
	virtual void ExitContext(const PMString & context) = 0;


	/**
		Log a message.

		@param messageType The name of message ("tracking", "transaction", etc.).
		@param attrs A reference to attribute list that contains the name and value pairs about message.
		@param Param1 A generic pointer associated with message. See following table

		<TABLE>
		<TR><TD><STRONG>Context</TD><TD>Param1</STRONG></TD></TR>
		<TR><TD>&quot;Tracking&quot;</TD><TD>ITracker *</TD></TR>
		<TR><TD>&quot;Transaction&quot;</TD><TD>IDataBase *</TD></TR>
		<TR><TD>All other cases</TD><TD>nil</TD></TR>
		</TABLE>
	*/
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil) = 0;
};

#endif // __IDiagLoggingAPI__