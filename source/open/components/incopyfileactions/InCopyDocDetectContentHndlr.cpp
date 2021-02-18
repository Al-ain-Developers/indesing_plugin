//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactions/InCopyDocDetectContentHndlr.cpp $
//  
//  Owner: Will Lin
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
//  
//  NOTE: This plugin and all of its code was given to System Integraters 
//  as a part of Denali. To do this we needed to make sure that no
//  headers from private were included anywhere in this project. This
//  forced us to move FileUtils.h to public. To merge this code with Dragontail
//  if have re-added private access paths to this project. At some point
//  in the future FileUtils.h will need to be made public or another solution 
//  is needed for Mont Blanc. --cparrish 06.24.02
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CSAXContentHandler.h"
#include "InCopyFileActionsID.h"
#include "InCopyImportExportDefs.h"
#include "WideString.h"
#include "SnippetStringDefs.h"

#include "IBoolData.h"
#include "IIntData.h"

#include "SnippetID.h"

class InCopyDocDetectContentHandler : public CSAXContentHandler
{
public:
	InCopyDocDetectContentHandler(IPMUnknown *boss);
	virtual ~InCopyDocDetectContentHandler();

    virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);

private:
	bool16 fFirstTime;
};

CREATE_PMINTERFACE(InCopyDocDetectContentHandler, kInCopyDocDetectContentHandlerImpl)


InCopyDocDetectContentHandler::InCopyDocDetectContentHandler(IPMUnknown *boss) :
	CSAXContentHandler(boss),
	fFirstTime(kTrue)
{
}


InCopyDocDetectContentHandler::~InCopyDocDetectContentHandler()
{
}


void InCopyDocDetectContentHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{
	// only do something the first time. The rest of the time just do nothing. Do this rather 
	//	than just throw a kCancel because we don't want to enable exceptions in this plug-in
	if (fFirstTime) {
		fFirstTime = kFalse;

		// if we got here, then this is at least a XML file
		InterfacePtr<IBoolData> fileTypeFoundBool(this, IID_IDOCDETECTFILETYPEFOUND);
		fileTypeFoundBool->Set(kTrue);

		// whether this is an InCopy file depends on whether the qualified name is InCopy document
		InterfacePtr<IIntData> isInCopyFileFlag(this, IID_IDOCDETECTISINCOPYFILE);
		
		/* now two InCopy file formats */
		int16 type = 0;
		
		if (qname.Contains(WideString(InCopy::kNamespacePrefix)) && localname == WideString(InCopy::kInCopyStoryElementName))
			type = 1;
		else if (qname.Contains(WideString(kSnippetRootElement)) && localname == WideString(kSnippetRootElement))
			type = 2;
		else if (localname == WideString(InCopy::kInCopyDocumentElementName))	// nasty heuristic 
			type = 3;

		isInCopyFileFlag->Set(type);
	}
}

