//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterExportHandler.cpp $
//  
//  Owner: robin briggs
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
//  Purpose:
//  Handler for exporting XML, called for every element of the structure tree.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IIDXMLElement.h"
#include "IXMLAttributeCommands.h"
#include "IXMLExportHandler.h"
#include "IXMLGenerator.h"

#include "DataUpdaterID.h"
#include "DataUpdaterConst.h"

class DataUpdaterExportHandler : public CPMUnknown<IXMLExportHandler>
{
	public:
		DataUpdaterExportHandler(IPMUnknown *boss);
		
		virtual bool16 CanHandleElement(IIDXMLElement *element);
		virtual bool16 HandleElementBefore(IXMLOutStream* stream, IIDXMLElement *element);
		virtual bool16 HandleAfterNthChild(IXMLOutStream* stream, IIDXMLElement *element, int32 childIndex);
		virtual bool16 HandleElementAfter(IXMLOutStream* stream, IIDXMLElement *element);
		
	private:
};


CREATE_PMINTERFACE(DataUpdaterExportHandler, kDataUpdaterExportHandlerImpl)


DataUpdaterExportHandler::DataUpdaterExportHandler(IPMUnknown *boss) :
	CPMUnknown<IXMLExportHandler>(boss)
{
}

bool16 DataUpdaterExportHandler::CanHandleElement(IIDXMLElement *element)
{
	WideString tagString(element->GetTagString());
	
	if (tagString == kDataUpdaterKeyTag || tagString == kDataUpdaterFieldTag)
		return kTrue;

	return kFalse;
}

bool16 DataUpdaterExportHandler::HandleElementBefore(IXMLOutStream* stream, IIDXMLElement *element)
{
	ASSERT_MSG(stream != nil, "DataUpdaterExportHandler::HandleElementBefore -- stream is nil!");

	WideString tagString(element->GetTagString());
	if (tagString != kDataUpdaterFieldTag)
	{ // we try to omit the field tags 
		return kFalse;
	}
	

	InterfacePtr<IXMLGenerator> generator(element, UseDefaultIID());
	if (generator)
		generator->GenerateContent(stream);


	return kTrue;
}

//
//	DataUpdaterExportHandler::HandleAfterNthChild
//
//	Called after each child is iterated. This is the place to do things in
//		between child elements
//
//	Parameters:
//		element		-> main/root/parent element
//		childIndex	-> index of element's child that was just processed
//
bool16 DataUpdaterExportHandler::HandleAfterNthChild(IXMLOutStream* stream, IIDXMLElement *element, int32 childIndex)
{
	// For every child of the record (field), we need a "; " to separate (except for the last child)
	WideString tagString(element->GetTagString());
	if (tagString == kDataUpdaterKeyTag)
	{ 
		if (element->GetChildCount() - 1 == childIndex)
			stream->Write(WideString(), kFalse);
		else
			stream->Write(WideString(", "), kFalse);

		return kTrue;
	}
	
	return kFalse;
}

bool16 DataUpdaterExportHandler::HandleElementAfter(IXMLOutStream* stream, IIDXMLElement *element)
{
	// I actually don't want closing tag for field element for exporting too
	WideString tagString(element->GetTagString());
	if (tagString == kDataUpdaterFieldTag)
	{ // we try to omit the field tags 
		return kTrue;
	}

	return kFalse;
}

