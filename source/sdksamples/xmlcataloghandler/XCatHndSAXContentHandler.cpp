//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndSAXContentHandler.cpp $
//  
//  Owner: Ian Paterson
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
// Interface includes
#include "IIDXMLElement.h"
#include "ISAXAttributes.h"
#include "ISAXAttributes.h"
#include "ISAXServices.h"
#include "IXCatHndFacade.h"
#include "IXCatHndParsingContext.h"
#include "IXMLParsingContext.h"
#include "IXMLServicesError.h"
#include "IXMLUtils.h"
// General includes
#include "Utils.h"
#include "CSAXContentHandler.h"
#include <map>
// Project includes
#include "XCatHndID.h"


struct XCatHndMapEntry;
class XCatHndSAXContentHandler;
typedef void (XCatHndSAXContentHandler::*XCatHndPMemberFn)
	(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs) ;
typedef std::map<PMString,XCatHndPMemberFn> XCatHndMap;

/** Implement a SAX content handler that reads info from an XML Catalog file.

	For the spec for this see: http://www.oasis-open.org/committees/entity/spec.html

	This content came from the spec:

	"An XML catalog can be used in two different, independent ways: 
	\li it can be used to locate the replacement text for an external entity,
	\li it can be used to locate an alternate URI reference for a resource. 

	Although these functions are similar in nature, they are distinct and 
	exercise two different sets of entries in the catalog."

	We are using it here to locate a SYSTEM URI given a PUBLIC identifier.
	@ingroup xmlcataloghandler
*/
class XCatHndSAXContentHandler : public CSAXContentHandler
{
public:

	/** Constructor
		@param boss ptr to boss object on which interface we implement is aggregated
	*/
	XCatHndSAXContentHandler(IPMUnknown* boss);
	
	/** Destructor 
	*/
	virtual ~XCatHndSAXContentHandler();


	/**	@see ISAXContentHandler::Register
	 */
	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer);

	/**	@see ISAXContentHandler::HandlesSubElements
	*/
	virtual bool16 HandlesSubElements() const;

	/**	@see ISAXContentHandler::Characters
	*/
	virtual void Characters(const WideString& chars);

	/**	@see ISAXContentHandler::StartElement
	*/
	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);

	/**	@see ISAXContentHandler::EndElement
	*/
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);

	/** Used to build handler table */
	struct XCatHndMapEntry {
		const char* name;
		XCatHndPMemberFn handler;
	};
	
private:
	void beginCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginDelegatePublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endDelegatePublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginDelegateSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endDelegateSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginDelegateURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endDelegateURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginGroup(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endGroup(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginNextCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endNextCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginPublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endPublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginRewriteSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endRewriteSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginRewriteURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endRewriteURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void beginUri(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void endUri(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs);
	void initMaps();
	void processElement(const XCatHndMap& hndMap,
						const PMString& uri, 
						const PMString& localname, 
						const PMString& qname, 
						ISAXAttributes* attrs);


	ISAXServices* fSAXServices;
	XCatHndMap fBeginMap;
	XCatHndMap fEndMap;


	// Constants
	static const PMString kNamespace;
	static const PMString kTopLevelElement;
	static const XCatHndMapEntry kBeginElemHandlerMap[] ;
	static const XCatHndMapEntry kEndElemHandlerMap[];

};

// Static, constants for this class
const PMString XCatHndSAXContentHandler::kNamespace = "urn:oasis:names:tc:entity:xmlns:xml:catalog";

const PMString XCatHndSAXContentHandler::kTopLevelElement = "catalog";

const XCatHndSAXContentHandler::XCatHndMapEntry XCatHndSAXContentHandler::kBeginElemHandlerMap [] = {
	{"catalog", &XCatHndSAXContentHandler::beginCatalog},
	{"delegatePublic", &XCatHndSAXContentHandler::beginDelegatePublic},
	{"delegateSystem", &XCatHndSAXContentHandler::beginDelegateSystem},
	{"delegateURI", &XCatHndSAXContentHandler::beginDelegateURI},
	{"group", &XCatHndSAXContentHandler::beginGroup},
	{"nextCatalog", &XCatHndSAXContentHandler::beginNextCatalog},
	{"public", &XCatHndSAXContentHandler::beginPublic},
	{"rewriteSystem", &XCatHndSAXContentHandler::beginRewriteSystem},
	{"rewriteURI", &XCatHndSAXContentHandler::beginRewriteURI},
	{"system", &XCatHndSAXContentHandler::beginSystem},
	{"uri", &XCatHndSAXContentHandler::beginUri}
};

const XCatHndSAXContentHandler::XCatHndMapEntry XCatHndSAXContentHandler::kEndElemHandlerMap [] = {
	{"catalog", &XCatHndSAXContentHandler::endCatalog},
	{"delegatePublic", &XCatHndSAXContentHandler::endDelegatePublic},
	{"delegateSystem", &XCatHndSAXContentHandler::endDelegateSystem},
	{"delegateURI", &XCatHndSAXContentHandler::endDelegateURI},
	{"group", &XCatHndSAXContentHandler::endGroup},
	{"nextCatalog", &XCatHndSAXContentHandler::endNextCatalog},
	{"public", &XCatHndSAXContentHandler::endPublic},
	{"rewriteSystem", &XCatHndSAXContentHandler::endRewriteSystem},
	{"rewriteURI", &XCatHndSAXContentHandler::endRewriteURI},
	{"system", &XCatHndSAXContentHandler::endSystem},
	{"uri", &XCatHndSAXContentHandler::endUri}
};

/** Elements we can expect: : catalog, 
delegatePublic, 
delegateSystem, 
delegateURI, 
group, 
nextCatalog,
public, 
rewriteSystem, 
rewriteURI, 
system, 
uri

*/

CREATE_PMINTERFACE(XCatHndSAXContentHandler, kXCatHndSAXContentHandlerImpl)

XCatHndSAXContentHandler::XCatHndSAXContentHandler(IPMUnknown* boss) :
	CSAXContentHandler(boss),
	fSAXServices(nil)
{
	this->initMaps();
}

XCatHndSAXContentHandler::~XCatHndSAXContentHandler()
{
	if (fSAXServices) {
		fSAXServices->Release();
	}
}

void XCatHndSAXContentHandler::initMaps()
{
	// Create lookup tables keyed on the element name
	int32 kMaxBeginEntries = sizeof(kBeginElemHandlerMap) / sizeof(kBeginElemHandlerMap[0]);
	for(int32 i=0; i < kMaxBeginEntries; i++) {
		PMString name(kBeginElemHandlerMap[i].name);
		XCatHndPMemberFn handler = kBeginElemHandlerMap[i].handler;
		fBeginMap.insert( std::pair<PMString,XCatHndPMemberFn>(name,handler));
		PMString qualifiedName(PMString(this->kNamespace + ":" + kBeginElemHandlerMap[i].name));
		fBeginMap.insert( std::pair<PMString,XCatHndPMemberFn>(qualifiedName,handler));
	}

	int32 kMaxEndEntries = sizeof(kEndElemHandlerMap) / sizeof(kEndElemHandlerMap[0]);
	for(int32 i=0; i < kMaxEndEntries; i++) {
		PMString name(kEndElemHandlerMap[i].name);
		XCatHndPMemberFn handler = kEndElemHandlerMap[i].handler;
		fEndMap.insert( std::pair<PMString,XCatHndPMemberFn>(name,handler));
		PMString qualifiedName(this->kNamespace + ":" + kEndElemHandlerMap[i].name);
		fEndMap.insert( std::pair<PMString,XCatHndPMemberFn>(qualifiedName,handler));
	}

}

void XCatHndSAXContentHandler::Register(ISAXServices* saxServices, IPMUnknown *importer)
{
	do {
		ASSERT(saxServices);
		if(!saxServices) {
			break;
		}
		// Register for the fully qualified version
		// See specification at: http://www.oasis-open.org/committees/entity/spec.html
		saxServices->RegisterElementHandler(WideString(kNamespace), WideString(kTopLevelElement), this);
		saxServices->RegisterElementHandler(WideString(""), WideString(kTopLevelElement), this);
	
		// Cache this interface; we need this later.
		// In general we shouldn't do this but we happen to know that 
		// the lifetime of the SAX services object
		// is greater than the lifetime of this object
		fSAXServices = saxServices;
		fSAXServices->AddRef();
	} while(kFalse);
}


bool16 XCatHndSAXContentHandler::HandlesSubElements( ) const
{
	// Yes, we have registered for the top-level catalog element and
	// we will handle all its dependents
	return kTrue;
}

/*
*/
void XCatHndSAXContentHandler::Characters(const WideString& chars)
{

	
}


/*
*/
void XCatHndSAXContentHandler::StartElement(const WideString& uri, 
											const WideString& localname, 
											const WideString& qname, ISAXAttributes* attrs)
{
	this->processElement(this->fBeginMap,uri,localname,qname,attrs);
}


/*
*/
void XCatHndSAXContentHandler::EndElement(const WideString& uri, 
										  const WideString& localname, 
										  const WideString& qname )
{
	this->processElement(this->fEndMap,uri,localname,qname,nil);
}

/* Avoid duplicating code between BeginElement and EndElement, only diff is that
	we have a different handler map and nil ISAXAttributes ptr for EndElement
*/
void XCatHndSAXContentHandler::processElement(
	const XCatHndMap& hndMap,
	const PMString& uri, 
	const PMString& localname, 
	const PMString& qname, 
	ISAXAttributes* attrs
	)
{
	do {
		try {
			ASSERT(this->fSAXServices);
			if(!this->fSAXServices) {
				break;
			}
			InterfacePtr<IXMLParsingContext> context(this->fSAXServices->QueryCurrentParsingContext());
			InterfacePtr<IXCatHndParsingContext> 
				xCatHndContext(context, UseDefaultIID());
			ASSERT(context && xCatHndContext);
			if(!(context && xCatHndContext)) {
				break;
			}
			// XML is case-sensitive so we shouldn't change the case looking for a match
			XCatHndMap::const_iterator result = hndMap.find(qname);
			if(result != hndMap.end()) {
				XCatHndPMemberFn handler  = result->second;
				(this->*handler)(context, xCatHndContext, attrs);
			}
		}
		catch (ErrorCode code) {
			InterfacePtr<IXMLServicesError> servicesError(fSAXServices, UseDefaultIID());
			ASSERT(servicesError);
			if(!servicesError) {
				break;
			}
			servicesError->SetErrorCode(code);
			servicesError->SetErrorTag(qname);
			
			break;
		}
	} while(kFalse);
}

void XCatHndSAXContentHandler::beginCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginCatalog\n");
}

void XCatHndSAXContentHandler::endCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endCatalog\n");
}

void XCatHndSAXContentHandler::beginDelegatePublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginDelegatePublic\n");
}

void XCatHndSAXContentHandler::endDelegatePublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endDelegatePublic\n");
}

void XCatHndSAXContentHandler::beginDelegateSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginDelegateSystem\n");
}

void XCatHndSAXContentHandler::endDelegateSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endDelegateSystem\n");
}

void XCatHndSAXContentHandler::beginDelegateURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endDelegateSystem\n");
}

void XCatHndSAXContentHandler::endDelegateURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endDelegateURI\n");
}

void XCatHndSAXContentHandler::beginGroup(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	//  <group  xml:base="file:///usr/share/xml/" >
	do {
		WideString base,qBase;
		bool16 got1 = attrs->GetValue(WideString("base"), base);
		bool16 got2 = attrs->GetValue(WideString("xml:base"), qBase);
		if(got1) {
			TRACEFLOW(kXCatHndPluginName, "got %s\n", PMString(base).GetUTF8String().c_str());
		}	

		if(got2) {
			TRACEFLOW(kXCatHndPluginName, "got %s\n", PMString(qBase).GetUTF8String().c_str());
		}
		if(!(got1 || got2)) {
			break;
		}
		PMString baseFolder(got1 ? base : qBase);
		ASSERT(xcatHndCtx);
		if(!xcatHndCtx) {
			break;
		}
		// make it stick
		WideString wbase(baseFolder);
		if(wbase.CharCount()>0) {
			Utils<IXCatHndFacade>()->AddXMLBase(wbase);
		}
		xcatHndCtx->SetCurrentXmlBase(wbase);
	
	} while(kFalse);
}

void XCatHndSAXContentHandler::endGroup(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	do {
		ASSERT(xcatHndCtx);
		if(!xcatHndCtx) {
			break;
		} 
		xcatHndCtx->SetCurrentXmlBase(WideString(PMString("")));
	} while(kFalse);
}

void XCatHndSAXContentHandler::beginNextCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginNextCatalog\n");
}

void XCatHndSAXContentHandler::endNextCatalog(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endNextCatalog\n");
}

void XCatHndSAXContentHandler::beginPublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	//<public publicId="-//OASIS//DTD DocBook CALS Table Model V4.2//EN"
    //    uri="calstblx.dtd"/>
	do {
		WideString publicId, uri;
		bool16 got1 = attrs->GetValue(WideString("publicId"), publicId);
		bool16 got2 = attrs->GetValue(WideString("uri"), uri);
		if(got1 && got2) {
			// This, then is the basic material we need for our entity resolver
			Utils<IXCatHndFacade> facade;
			ASSERT(facade);
			if(!facade) {
				break;
			} 
			// Add the xml current base if we're in a group to the URI to
			// map to our system
			ASSERT(xcatHndCtx);
			if(!xcatHndCtx) {
				break;
			} 
			PMString xmlbase = xcatHndCtx->GetCurrentXmlBase();
			facade->AddPublicToUriMapping(publicId, uri); // Was xmlbase + uri);
		}

	} while(kFalse);
}

void XCatHndSAXContentHandler::endPublic(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endPublic\n");
}

void XCatHndSAXContentHandler::beginRewriteSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginRewriteSystem\n");
}

void XCatHndSAXContentHandler::endRewriteSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endRewriteSystem\n");
}

void XCatHndSAXContentHandler::beginRewriteURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginRewriteURI\n");
}

void XCatHndSAXContentHandler::endRewriteURI(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endRewriteURI\n");
}

void XCatHndSAXContentHandler::beginSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginSystem\n");
}

void XCatHndSAXContentHandler::endSystem(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endSystem\n");
}

void XCatHndSAXContentHandler::beginUri(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::beginUri\n");
}

void XCatHndSAXContentHandler::endUri(IXMLParsingContext* ctx, IXCatHndParsingContext* xcatHndCtx, ISAXAttributes* attrs)
{
	TRACEFLOW(kXCatHndPluginName, "void XCatHndSAXContentHandler::endUri\n");
}

//  Code generated by DollyXS code generator
