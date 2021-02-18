//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkXMLTransformer.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IDataServices.h"
#include "IIDXMLDOMDocument.h"
#include "IIDXMLDOMNList.h"
#include "IIDXMLDOMNode.h"
#include "IImportXMLData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPMUnknownData.h"
#include "ISysFileData.h"
#include "IXDocBkFacade.h"
#include "IXMLImporter.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"
#include "IXSLServices.h"


// General includes:
#include "StreamUtil.h"
#include "ErrorUtils.h"
#include "Utils.h"
#include "CXMLTransformer.h"
#include "SDKFileHelper.h"
#include "KeyValuePair.h"
#include "K2Vector.tpp"
#include <boost/tokenizer.hpp>
// Project includes:
#include "XDocBkID.h"


/** Implements an XML transformer (IXMLTransformer) to apply a context-sensitive mapping between
	elements and styles, using InDesign's built-in XSLT engine.

	Based on XSLTransformerPI.
	XDocBkAttribute stylemapping: impl cls XMLImporterPostImportMapping, XMLImporterPostImpMapping.cpp

	See http://www.w3.org/TR/xml-stylesheet/ for more on PIs for stylesheets

	@ingroup xdocbookworkflow

*/
class XDocBkXMLTransformer : public CXMLTransformer
{

	public:
		/** Constructor
			@param boss refers to boss object on which this implementation is aggregated
		*/
		XDocBkXMLTransformer(IPMUnknown *boss);

		/** Manipulate the DOM by applying XSLT transform to it
			@param dom element of DOM to start transform from
			@param xmlImporter reference to kXMLImporterBoss performing the import
			@see IXMLTransfomer::TransformDOM

		*/
		virtual ErrorCode TransformDOM(IIDXMLDOMDocument *dom, IPMUnknown *xmlImporter);

private:
	/** Defines type that a boost::tokenizer can act on */
	typedef std::basic_string<UTF16TextChar, std::char_traits<UTF16TextChar>, std::allocator<UTF16TextChar> > XDocBkString;
	/** Define specific type to tokenize something close to WideString */
	typedef boost::tokenizer<boost::char_separator<UTF16TextChar>, XDocBkString::const_iterator,
		XDocBkString > XDocBkWideTokenizer;
	/** Define a key-value pair to represent attributes in a DOM node */
	typedef std::pair<WideString, WideString> XDocBkAttribute;
	/** Define a list of attributes present on a node */
	typedef std::vector<XDocBkAttribute> XDocBkAttributeList;

	/** Define struct to help the comparisons required by std::find_if. This is a "Predicate", in STL terms.
		@see http://www.sgi.com/tech/stl/find_if.html
	*/
	struct XDocBkNameEquals
	{
	public:
		/** Constructor.  explicit - keyword used to define a constructor so that it isn't used for implicit conversions.
			@see http://www.research.att.com/~bs/glossary.html re explicit constructors

			@param name string to encapsulate in this struct
		*/
		explicit XDocBkNameEquals(const WideString& name)
			: fName(name)
			{}

		/** Operator ().
			@param attr specifies comparand attribute
			@see http://www.sgi.com/tech/stl/Predicate.html
		*/
		bool operator()(XDocBkAttribute& attr) const
			{ return attr.first == fName; }

	private:
		const WideString&	fName;
	};

	/**	Create stream opened onto XSL file.
		Takes a simple file name and searches for opens the corresponding XSLT file,
		returning it as a stream.


		@param xmlImporter instance of importer (kXMLImporterBoss). Reason for providing this
			is if we want to have a relative path for the XSL file and we use the fact that the
			importer knows what XML file it's currently importing
		@param fileName
		@return IPMStream opened onto the XSL file referred to by fileName
	 */
	IPMStream* CreateXSLTStream(IPMUnknown *xmlImporter, PMString& fileName) const;



	/**	Determine a path to the stylesheet, given an xml-stylesheet processing-instruction
		@param dom IN
		@return PMString specifying a possible path to the stylesheet
	 */
	PMString GetStylesheetPathFromPI(IIDXMLDOMDocument *dom) const;


	/**	Return count of parsed attributes
		@param data IN what we're going to parse
		@param attrList OUT
		@return int32 giving count of parsed attributes
	 */
	int32 GetParsedAttributes(const WideString & data, XDocBkAttributeList& attrList) const;


	/**	Find named attribute's value given an attribute list
		@param attrList IN
		@param name IN
		@return WideString
	 */
	WideString GetAttrValue(XDocBkAttributeList& attrList, const WideString& name) const;


	/**	Description
		@param itr IN/OUT
		@param endItr IN
		@param token OUT
		@return bool16 kTrue if token could be found, kFalse otherwise
	 */
	bool16 GetNextToken(XDocBkWideTokenizer::iterator& itr,
							const XDocBkWideTokenizer::iterator& endItr,
							WideString& token) const;



};

CREATE_PMINTERFACE(XDocBkXMLTransformer, kXDocBkXMLTransformerImpl)


/* Constructor
*/
XDocBkXMLTransformer::XDocBkXMLTransformer(IPMUnknown *boss) :
	CXMLTransformer(boss)
{
}

/*
*/
ErrorCode XDocBkXMLTransformer::TransformDOM(IIDXMLDOMDocument *dom, IPMUnknown *xmlImporter)
{
	ErrorCode retval = kFailure;
	do {
		ASSERT(dom && xmlImporter);
		if(!Utils<IXDocBkFacade>()->IsUsingXMLTransformer()) {
			// If we are not enabled, then a 'success' permits rest of import
			// to proceed without being rolled back if one component claims to have failed
			retval = kSuccess;
			break;
		}
		// end of check to see if we're turned on
		// See if we were passed in stylesheet.
		InterfacePtr<IPMUnknownData> unknownData(xmlImporter, UseDefaultIID());
		ASSERT(unknownData);
		if(!unknownData) {
			break;
		}

		InterfacePtr<IImportXMLData> importXMLData(unknownData->GetPMUnknown(), UseDefaultIID());
		ASSERT(importXMLData);
		if(!importXMLData) {
			break;
		}

		PMString potentialXSLPath;
		// Condition 1: we've been told that the PI overrides the stylesheet
		if(!Utils<IXDocBkFacade>()->IsSuppliedXSLOverridingPI()) {
			potentialXSLPath = this->GetStylesheetPathFromPI(dom);
		}
		else {
			// Condition 2: we've been told that supplied XSL (if any) overrides the PI
			PMString stylesheetPath = Utils<IXDocBkFacade>()->GetStylesheetPath();
			SDKFileHelper suppliedStylesheetFileHelper(stylesheetPath);
			if(suppliedStylesheetFileHelper.IsExisting()) {
				potentialXSLPath = suppliedStylesheetFileHelper.GetPath();
			} else {
				// fallback to having a look in the PI
				potentialXSLPath = this->GetStylesheetPathFromPI(dom);
			}
		}

		//- If no stylesheet at all, then stop now
		if (potentialXSLPath.empty()) {
			// Don't return a fail, as this will undo the whole import
			retval = kSuccess;
			break;
		}
		// We don't need at this point to check that potentialXSLPath is referring to
		// a file, because we are going to look in the folder containing the XML if
		// it doesn't (in CreateXSLTStream)

		IXSLServices::Params params;
		// If there was a stylesheet then use it.
		InterfacePtr<IPMStream> xslStream(this->CreateXSLTStream(xmlImporter, potentialXSLPath));
		// If no XSL file existing, then that's OK, just don't do anything
		//
		if(!xslStream) {
			retval = kSuccess;
			break;
		}

		InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(registry);
		if(!registry) {
			break;
		}
		InterfacePtr<IK2ServiceProvider> xslProvider(registry->QueryServiceProviderByClassID(kXSLTransformService, kXSLTransformBoss));
		ASSERT(xslProvider);
		if(!xslProvider) {
			break;
		}
		InterfacePtr<IXSLServices> xslServices(xslProvider, UseDefaultIID());
		ASSERT(xslServices);
		if(!xslServices) {
			break;
		}

		// Pass the source file to the XSLServices. It's used to resolve relative path names.
		InterfacePtr<ISysFileData> fileData(xslServices, UseDefaultIID());
		ASSERT(fileData);
		if(!fileData) {
			break;
		}
		fileData->Set(importXMLData->GetImportSource());

		xslServices->Transform(dom, xslStream, params, dom);
		retval = ErrorUtils::PMGetGlobalErrorCode();
	} while(kFalse);

	return retval;
}


/*
*/
IPMStream *XDocBkXMLTransformer::CreateXSLTStream(IPMUnknown *xmlImporter, PMString& fileName) const
{
	// First, just try opening the literal stream
	IPMStream *xslStream = nil;


	do {
		if(fileName.empty()) {
			// Can't proceed as no-one has told us XSL file name
			break;
		}
		SDKFileHelper fileHelper(fileName);
		if(fileHelper.IsExisting()) {
			xslStream = StreamUtil::CreateFileStreamRead(fileHelper.GetIDFile());
			ASSERT(xslStream);
			if(xslStream) {
				break;
			}
		}

		// Could be XSL stylesheet is a relative path
		// and we just look in the same folder as XML impmort
		InterfacePtr<IPMUnknownData> importData(xmlImporter, UseDefaultIID());
		ASSERT(importData);
		if(!importData) {
			break;
		}
		InterfacePtr<IImportXMLData> importXMLData(importData->GetPMUnknown(), UseDefaultIID());
		ASSERT(importXMLData);
		if(!importXMLData) {
			break;
		}

		const IDFile& srcFile = importXMLData->GetImportSource();
		SDKFileHelper importSourceFileHelper(srcFile);
		PMString currFolder(importSourceFileHelper.GetParentFolderAsString());
		currFolder = Utils<IXDocBkFacade>()->AddPathSeparator(currFolder);
		PMString tryXSLPath = currFolder + fileName;
		SDKFileHelper xslFileHelper(tryXSLPath);
		if(xslFileHelper.IsExisting()) {
			xslStream = StreamUtil::CreateFileStreamRead(xslFileHelper.GetIDFile());
			ASSERT(xslStream);
		}

	} while(kFalse);

	return xslStream;
}


/*
*/
PMString XDocBkXMLTransformer::GetStylesheetPathFromPI(IIDXMLDOMDocument *dom) const
{
	PMString retval;
	WideString target("xml-stylesheet");
	do {
		ASSERT(dom);
		if(!dom) {
			break;
		}
		// The stylesheet PI, if it exists, will be a child of the document node.
		// Search the children and see if it's there.
		IIDXMLDOMNode *docNode = dom->GetDocumentNode();
		ASSERT(docNode);
		if(!docNode) {
			break;
		}
		IIDXMLDOMNList *childList = docNode->GetChildNodes();
		ASSERT(childList);
		if(!childList) {
			break;
		}
		int32 childCount = childList->Length();
		for (int32 i = 0; i < childCount; ++i)
		{
			IIDXMLDOMNode *child = childList->GetNthNode(i);
			ASSERT(child);
			if(!child) {
				break;
			}
			if (child->GetNodeType() == IIDXMLDOMNode::kProcessingInstruction)		// is it a PI?
			{
				WideString nodeName;
				if (child->GetNodeName(nodeName) && nodeName == target) // is it a stylesheet PI?
				{
					XDocBkAttributeList attrs;
					WideString nodeValue;
					child->GetNodeValue(nodeValue);
					int32 numAttrs = this->GetParsedAttributes(WideString(nodeValue), attrs);
					if(numAttrs == 0) {
						break;
					}
					// We're looking for a PI like this:
					// <?xml-stylesheet href="copy-with-contxt-sens-styling.xsl" type="text/xsl"?>
					// See http://www.w3.org/TR/xml-stylesheet/
					if (this->GetAttrValue(attrs, WideString("type")) == WideString("text/xsl"))
					{
						// It's our PI. Now we just have to get the stylesheet file name
						retval = this->GetAttrValue(attrs, WideString("href"));
						break;
					}
				}
			}
		}
	} while(kFalse);

	return retval;
}



/*
*/
static const UTF16TextChar k_equalsSign[] = { kTextChar_EqualsSign, kTextChar_Null};
static const UTF16TextChar k_quoteSpace[] = { kTextChar_QuotationMark, kTextChar_Space, kTextChar_Null};
static const WideString k_equalStr(k_equalsSign);
int32 XDocBkXMLTransformer::GetParsedAttributes(const WideString & data, XDocBkXMLTransformer::XDocBkAttributeList& attrList) const
{
	attrList.clear();
	// Break the data into tokens.
	XDocBkString s(data.GrabUTF16Buffer(nil), data.CharCount());

	// http://www.boost.org/libs/tokenizer/
	boost::char_separator<UTF16TextChar>  separator(k_quoteSpace, k_equalsSign, boost::keep_empty_tokens);
	XDocBkWideTokenizer tok(s, separator);
	XDocBkWideTokenizer::iterator itr = tok.begin();
	for (;;)
	{
		// We should get three tokens:
		//    <name> = <value>
		// We look for the '=' as a sanity check.
		WideString name, equal, value;
		if (!this->GetNextToken(itr, tok.end(), name)) {
			break;
		}
		if (!this->GetNextToken(itr, tok.end(), equal)) {
			break;
		}
		if (!this->GetNextToken(itr, tok.end(), value)) {
			break;
		}
		// Verify that we have the = we think we have
		ASSERT(equal == WideString(k_equalsSign));
		if (equal == k_equalStr)
		{
			attrList.push_back(XDocBkAttribute(name, value));
		}
	}

	return static_cast<int32>(attrList.size());
}

/*
*/
WideString XDocBkXMLTransformer::GetAttrValue(XDocBkXMLTransformer::XDocBkAttributeList& attrList, const WideString& name) const
{
	// Define a comparison helper
	XDocBkNameEquals nameComparisonHelper(name);
    XDocBkAttributeList::const_iterator iter = std::find_if(attrList.begin(), attrList.end(), nameComparisonHelper);
    if (iter != attrList.end()) {
		return iter->second;
	}
	// Failed to find the named attribute
	return WideString();
}

/*
*/
bool16 XDocBkXMLTransformer::GetNextToken(XDocBkWideTokenizer::iterator& itr,
											const XDocBkWideTokenizer::iterator& endItr,
											WideString& token) const
{
	bool16 retval = kFalse;
	for (;;)
	{
		// End if we are out of tokens.
		if (itr == endItr) {
			break;
		}

		// Return a token if we found one.
		XDocBkString dbkStr = *itr;
		token = WideString(dbkStr.c_str());
		itr++;
		if (!token.empty()) {
			retval= kTrue;
			break;
		}
		// Got an empty token. Try again.
	}
	return retval;
}
//  Code generated by DollyXS code generator
