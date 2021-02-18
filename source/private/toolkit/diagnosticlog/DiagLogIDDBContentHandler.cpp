//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogIDDBContentHandler.cpp $
//  
//  Owner:
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

#include "CSAXContentHandler.h"

#include "ISAXAttributes.h"
#include "IDiagLogIDDatabase.h"

#include "DiagnosticLogID.h"

#include <vector>

// ===================================================================================
//	Parser Classes		
// ===================================================================================

class DiagLogIDDBContentHandler : public CSAXContentHandler
{
public:
	DiagLogIDDBContentHandler(IPMUnknown* boss);
	virtual ~DiagLogIDDBContentHandler();

	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);

protected:

	void BeginChildren(const WideString& qname);
	void EndChildren();
	
	void ParseIDSpace(ISAXAttributes* attrs);
	void ParseID(ISAXAttributes* attrs);

private:
	int32 fIdSpace;
	PMString fParentElement;
	mutable std::vector<PMString> fStack;
};

//========================================================================================
// METHODS DiagLogIDDBContentHandler
//========================================================================================

CREATE_PMINTERFACE(DiagLogIDDBContentHandler, kDiagLogIDDBContentHandlerImpl)


//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::DebugPrefsDocumentHandler
//----------------------------------------------------------------------------------------

DiagLogIDDBContentHandler::DiagLogIDDBContentHandler(IPMUnknown* boss) :
	CSAXContentHandler(boss)
{
}


//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::~DebugPrefsDocumentHandler
//----------------------------------------------------------------------------------------

DiagLogIDDBContentHandler::~DiagLogIDDBContentHandler()
{
}

//----------------------------------------------------------------------------------------
// DiagLogIDDBContentHandler::StartElement
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{	
	if (qname == WideString("idspace"))
		ParseIDSpace(attrs);
		
	else if (qname == WideString("id"))
		ParseID(attrs);
	
	else if (qname != WideString("indesigniddatabase"))
		ASSERT_FAIL(FORMAT_ARGS("Ignoring the unrecognized element named %s", PMString(qname).GetUTF8String().c_str()));

	// --- Save the current state
	this->BeginChildren(qname);
}


//----------------------------------------------------------------------------------------
// DiagLogIDDBContentHandler::EndElement
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname )
{
	this->EndChildren();
}


//----------------------------------------------------------------------------------------
// DiagLogIDDBContentHandler::BeginChildren
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::BeginChildren(const WideString& qname)
{
	fStack.push_back(fParentElement);
	fParentElement = qname;
}


//----------------------------------------------------------------------------------------
// DiagLogIDDBContentHandler::EndChildren
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::EndChildren()
{
	fParentElement = fStack.back();
	fStack.pop_back();
}

//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::ParseIDSpace
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::ParseIDSpace(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("indesigniddatabase"));
	GetAttributeString(attrs, "name");
	fIdSpace = GetAttributeInt(attrs, "value");
}


//----------------------------------------------------------------------------------------
// DiagLogIDDBContentHandler::ParseID
//----------------------------------------------------------------------------------------

void DiagLogIDDBContentHandler::ParseID(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("idspace"));
	PMString idName = GetAttributeString(attrs, "name");
	int32 id = GetAttributeInt(attrs, "value");

	InterfacePtr<IDiagLogIDDatabase> iDiagLogIDDB(this, UseDefaultIID());
	iDiagLogIDDB->AddID(fIdSpace, id, idName.GetUTF8String().c_str());
}
