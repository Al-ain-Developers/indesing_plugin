//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/structure/CXMLGenerator.cpp $
//  
//  Owner: Lonnie Millett
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "CXMLGenerator.h"
#include "IIDXMLElement.h"
#include "IXMLTag.h"
#include "IPMStringMapData.h"
#include "IXMLFormattedMapData.h"


CXMLGenerator::CXMLGenerator(IPMUnknown *boss) :
	CPMUnknown<IXMLGenerator>(boss)
{
}

void CXMLGenerator::GenerateBeginTag(IXMLOutStream *stream)
{
	InterfacePtr<IIDXMLElement> element(this, UseDefaultIID());
	if (element)
	{
		// --- Push this tag on the stack
		InterfacePtr<IXMLTag> tag(element->GetXMLReference().GetDataBase(), element->GetTagUID(), IID_IXMLTAG);
		if (tag)
		{
			
			// --- Grab the attributes of the tag if there are any
			IXMLOutStream::AttributeList attrs;
			CollectAttributes(stream, &attrs);

			if (!attrs.empty())
			{
				stream->PushWithAttributes(tag->GetTagName(), attrs, kFalse);				
			}
			else
			{
				stream->Push(tag->GetTagName(), kFalse);
			}
		
			// --- Stream out the XML content
			this->GenerateContent(stream);
		}
	}
}

void CXMLGenerator::CollectAttributes(IXMLOutStream *stream, IXMLOutStream::AttributeList *attrs)
{
	InterfacePtr<IIDXMLElement> element(this, UseDefaultIID());
	if (element)
	{
		// --- If there are any attributes associated with this element, collect them in the attributelist
		int32 attributeCount = element->GetAttributeCount();
		if (attributeCount > 0)
		{
			for (int32 i = 0; i < attributeCount; i++)
			{
				WideString name = element->GetAttributeNameAt(i);
				WideString value = element->GetAttributeValue(name);
				
				// -- Check for attribute replacement when working with href attributes.  If image conversion
				// -- is being done then the original asset has been replaced with an optimized one in a different
				// -- location.  We need to make sure that the XML exported reflects the new location.
				if (name == (WideString)"href")
				{
				    // -- If the element does not have an "href_opt" or "href_fmt" then we might
				    // -- have to add some depending on whether something was converted.
				    if (!element->HasAttribute((WideString)"href_opt"))
				    {
				    	InterfacePtr<IPMStringMapData> optimizedMap(stream, IID_XMLOPTIMIZEDMAP);
					    PMString optimizedValue = optimizedMap->GetSecond(value);
					    if (optimizedValue != kNullString)
					    {
					    	PMString optimizedName("href_opt");
							attrs->push_back(IXMLOutStream::Attribute(optimizedName.GrabUTF16Buffer(nil), optimizedValue.GrabUTF16Buffer(nil)));
						}
				    }

				    if (!element->HasAttribute((WideString)"href_fmt"))
				    {
				    	InterfacePtr<IXMLFormattedMapData> formatMap(stream, UseDefaultIID());
					    PMString formatValue = formatMap->GetSecond(element->GetXMLReference());
					    if (formatValue != kNullString)
					    {
					    	PMString formatName("href_fmt");
							attrs->push_back(IXMLOutStream::Attribute(formatName.GrabUTF16Buffer(nil), formatValue.GrabUTF16Buffer(nil)));
						}
				    }
				    
				    InterfacePtr<IPMStringMapData> copyMap(stream, IID_XMLCOPYMAP);
				    PMString newValue = copyMap->GetSecond(value);
				    if (newValue != kNullString)
				    	value = (WideString)newValue;
				}
				else if (name == (WideString)"href_opt")
				{
				    InterfacePtr<IPMStringMapData> optimizedMap(stream, IID_XMLOPTIMIZEDMAP);
				    PMString newValue = optimizedMap->GetSecond(value);
				    if (newValue != kNullString)
				    	value = (WideString)newValue;
				}
				else if (name == (WideString)"href_fmt")
				{
				    InterfacePtr<IXMLFormattedMapData> formatMap(stream, UseDefaultIID());
				    PMString newValue = formatMap->GetSecond(element->GetXMLReference());
				    if (newValue != kNullString)
				    	value = (WideString)newValue;
				}

				attrs->push_back(IXMLOutStream::Attribute(name.GrabUTF16Buffer(nil), value.GrabUTF16Buffer(nil)));
			}
		}
	}
}

void CXMLGenerator::GenerateContent(IXMLOutStream *stream, int32 beforeChildIndex)
{
}


void CXMLGenerator::GenerateEndTag(IXMLOutStream *stream)
{
	stream->Pop(kFalse);
}


