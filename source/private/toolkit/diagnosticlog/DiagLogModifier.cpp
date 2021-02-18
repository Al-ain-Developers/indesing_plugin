//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogModifier.cpp $
//  
//  Owner: gxiao 
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

#include "VCPlugInHeaders.h"

#include "IDiagLogModifier.h"

#include "DiagnosticLogID.h"

class DiagLogModifier : public CPMUnknown<IDiagLogModifier>
{
public:		
	DiagLogModifier(IPMUnknown *boss);
	~DiagLogModifier();

	// Logging API
	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil, const void * Param2 = nil);
	virtual void ExitContext(const PMString & context);
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1);
};

CREATE_PMINTERFACE(DiagLogModifier, kDiagLogModifierImpl)

DiagLogModifier::DiagLogModifier(IPMUnknown *boss) : 
	CPMUnknown<IDiagLogModifier>(boss)
{
}


DiagLogModifier::~DiagLogModifier()
{
}


void DiagLogModifier::EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2)
{
}


void DiagLogModifier::ExitContext(const PMString & context)
{
}


void DiagLogModifier::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
{
}
