//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkScript.cpp $
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
#include "ILinkObjectReference.h"

// General includes:
#include "CScript.h" // includes IScript.h and IPMUnknown.h

// Project includes:
#include "CusDtLnkID.h"
#include "CusDtLnkScriptingDefs.h"


/** Implements IScript to support roundtripping our custom datalinks through INX/Snippets
	@ingroup customdatalink	
*/
class CusDtLnkScript : public CScript
{
public:
	/** Constructor */
	CusDtLnkScript(IPMUnknown* boss);

	/** Destructor */
	virtual ~CusDtLnkScript();

	/** Return the object's type */
	virtual ScriptID		GetObjectType( const RequestContext& context ) const { return c_CusDtLnkCustomDataLink; }

	/**	Return the parent of this object in the script hierarchy */
	virtual IPMUnknown*		QueryParent( const PMIID& iid, const RequestContext& context ) const;
};


CREATE_PMINTERFACE(CusDtLnkScript, kCusDtLnkScriptImpl)

/* Constructor
*/
CusDtLnkScript::CusDtLnkScript(IPMUnknown* boss) : 
CScript(boss)
{
}

/*
*/
CusDtLnkScript::~CusDtLnkScript() 
{
}

/*
*/
IPMUnknown* CusDtLnkScript::QueryParent( const PMIID& iid, const RequestContext& context ) const
{
	IPMUnknown* parent = nil;
	// return associated page item (not doc)
	InterfacePtr<ILinkObjectReference> pageItemReference( (IPMUnknown*) this, UseDefaultIID() ) ;
	if ( pageItemReference != nil ) {
		parent = pageItemReference->QueryLinkedObject(iid) ;
	}
	return parent ;
}


