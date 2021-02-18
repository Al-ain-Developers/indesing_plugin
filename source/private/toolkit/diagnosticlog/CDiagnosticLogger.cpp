//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/CDiagnosticLogger.cpp $
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

#include "CDiagnosticLogger.h"

CDiagnosticLogger::CDiagnosticLogger(IPMUnknown *boss, PMString name) :
	CPMUnknown<IDiagnosticLogger>(boss),
	fEnabled(kFalse)
{
	fName = name;
	fStringBuffer = new char[kDIAGLOGSTRINGBUFFERSIZE];
	fLineBuffer = new char[kDIAGLOGLINEBUFFERSIZE];
}

CDiagnosticLogger::~CDiagnosticLogger()
{
	delete [] fStringBuffer;
	delete [] fLineBuffer;
}


void CDiagnosticLogger::GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs)
{
    IXMLOutStream::Attribute aAttr;

	aAttr.fName = WideString("name");
	aAttr.fValue = WideString(fName);
	attrs.push_back(aAttr);

	PMString temp = fEnabled ? "true" : "false";
	aAttr.fName = WideString("enabled");
	aAttr.fValue = WideString(temp);
	attrs.push_back(aAttr);
}


char * CDiagnosticLogger::PrintToString(const char *str, ...)
{
	va_list args;
	va_start(args, str);
#ifdef MACINTOSH
#ifdef __MWERKS__
	std::vsnprintf(fStringBuffer, kDIAGLOGSTRINGBUFFERSIZE-1, str, args);
#else
	vsnprintf(fStringBuffer, kDIAGLOGSTRINGBUFFERSIZE-1, str, args);
#endif
#endif
#ifdef WINDOWS
	_vsnprintf(fStringBuffer, kDIAGLOGSTRINGBUFFERSIZE-1, str, args);
#endif
	va_end(args);
	
	return fStringBuffer;
}
