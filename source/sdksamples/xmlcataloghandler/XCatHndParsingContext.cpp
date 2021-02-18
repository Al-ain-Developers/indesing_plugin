//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndParsingContext.cpp $
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

// Interface Includes
#include "IXCatHndParsingContext.h"


// Implementation Includes

#include "CPMUnknown.h"
// Project includes:

/** Stores state we read or need when parsing.
	The intent was that we could have a catalog with groups with different xml:base
	attributes and we could read those and somehow support different XML vocabularies,
	as the xml:base would point at where the assets were (DTD etc) needed to support a 
	particular vocabulary. But at present this plug-in just supports one active xml:base,
	so this implementation is not fully utilised..

	@ingroup xmlcataloghandler
*/

class XCatHndParsingContext : public CPMUnknown<IXCatHndParsingContext>
{
public:

	/** Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	XCatHndParsingContext(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~XCatHndParsingContext() {}

	/** Set up the current xml:base
		@param base specifying the new xml:base
	*/
	virtual void SetCurrentXmlBase(const WideString& base) {
		this->fXmlBase = base;
	}

	/** Acquire current xml:base
		@return WideString with xml:base
	*/
	virtual WideString GetCurrentXmlBase() const {
		return this->fXmlBase;
	}

private:
	WideString fXmlBase;
};


/*	
*/
CREATE_PMINTERFACE(XCatHndParsingContext, kXCatHndParsingContextImpl)

/*	Constructor
*/
XCatHndParsingContext::XCatHndParsingContext(IPMUnknown* boss) :
		CPMUnknown<IXCatHndParsingContext>(boss)
{
}


//	end, File: XCatHndParsingContext.cpp
