//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXEntityResolver.h $
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
//  A wrapper for HAXEEntityResolverBase.
//  
//========================================================================================

#pragma once
#ifndef __ISAXEntityResolver_h__
#define __ISAXEntityResolver_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

	/**
	Basic interface for resolving entities

	If a SAX client requires validation with external DTDs,
	or if the client needs to implement customized handling
	for external entities, it must implement this interface and
	register an instance with the SAX parser using the parser's
	setEntityResolver method.

	The parser will then allow the application to intercept any
	external entities (including the external DTD subset and
	external parameter entities, if any) before including
	them.

	SAX clients that do not require validation need not
	implement nor register this handler.

	The client can also use this interface to redirect system
	identifiers to local URIs or to look up replacements in a
	catalog (possibly by using the public identifier).
	*/
class ISAXEntityResolver : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXENTITYRESOLVER };
	
    /**
    Resolve entity

    The parser will call this method before opening any external
    entity (including the external DTD subset, external entities
    referenced within the DTD, and external entities referenced
    within the document element).

    Application writers can use this method to redirect external
    system identifiers to secure and/or local URIs, to look up
    public identifiers in a catalogue, or to read an entity from
    a file or database.

    @param publicID             The public identifier of the
                                external entity being referenced.
                                The string will be invalid if
                                no identifier was supplied.

    @param systemID             The system identifier of the
                                external entity being referenced.

    @return                     A client implemented input
                                stream to the new input source.
                                The client should return NULL
                                if it does not know how to
                                resolve the entity. This will
                                result in a parser error being
                                generated.  The stream will be owned
                                by the parsing system.

    @see IPMStream
    */
	virtual IPMStream* ResolveEntity(const WideString& publicID, const WideString& systemID) = 0;
};

#endif