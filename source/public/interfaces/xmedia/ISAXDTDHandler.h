//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXDTDHandler.h $
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
//  A wrapper for HAXEDTDHandlerBase.
//  
//========================================================================================

#pragma once
#ifndef __ISAXDTDHandler_h__
#define __ISAXDTDHandler_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

    /**
    Basic handler for entity/notation declarations

    If a SAX client needs information about notations and
    unparsed entities, then the client implements this interface
    and passes it to the parser using the ParseStream method of
    ISAXService.  The parser uses the instance to report notation
     and unparsed entity declarations to the application.

    The SAX parser may report these events in any order,
    regardless of the order in which the notations and unparsed
    entities were declared; however, all DTD events must be
    reported after the document handler's startDocument event,
    and before the first startElement event.

    It is up to the application to copy the information for
    future use (perhaps in a hash table or object tree). If the
    application encounters attributes of type "NOTATION",
    "ENTITY", or "ENTITIES", it can use the information that it
    obtained through this interface to find the entity and/or
    notation corresponding with the attribute value.

    @see CAXESAX2Parser#setDTDHandler
    */
class ISAXDTDHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXDTDHANDLER };
	
    /**
    Notation declaration notification


    It is up to the client to copy the notation for later
    reference, if necessary.

    @param name             The notation name.

    @param publicID         The notation's public identifier, or
                            null if none was given.

    @param systemID         The notation's system identifier, or
                            null if none was given.

    @see #UnparsedEntityDecl
    @see ISAXAttributes
    */
	virtual void NotationDecl(const PMString& name, const PMString& publicID, const PMString& systemID) = 0;

    /**
    Unparsed entity notification


    Note that the notation name corresponds to a notation
    reported by the notationDecl() event.  It is up to the
    application to copy the entity for later reference, if
    necessary.

    @param name             The notation name.

    @param publicID         The notation's public identifier, or
                            null if none was given.

    @param systemID         The notation's system identifier, or
                            null if none was given.

    @param notationName     The name of the associated notation.

    @see #NotationDecl
    @see ISAXAttributes
    */
	virtual void UnparsedEntityDecl(const PMString& name, const PMString& publicID,
										const PMString& systemID, const PMString& notationName) = 0;

    /**
    Reset handler


    This method helps in reseting the DTD object implementation
    defaults each time the DTD is begun.
    */
	virtual void ResetDocType() = 0;
};

#endif