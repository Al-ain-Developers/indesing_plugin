//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXLocator.h $
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
//  An InDesign friendly wrapper for CAXELocator.  An instance of this class will be passed to
//  ISaxContentHandler::SetDocumentLocator.
//  
//========================================================================================

#pragma once
#ifndef __ISAXLocator_h__
#define __ISAXLocator_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

// Forward declaration
struct AXE8_ParserStruct;
typedef struct AXE8_ParserStruct *AXE8_Parser;

class ISAXServices;

/**
Interface for associating a SAX event with a document location.

If a SAX parser provides location information to the SAX
application, it does so by implementing this interface and
passing an instance to the application using the ISAXContentHandler's
SetDocumentLocator method.  The application can use the
object to obtain the location of any other document handler event
in the XML source document.

Note that the results returned by the object will be valid only
during the scope of each content handler method: the application
will receive unpredictable results if it attempts to use the
locator at any other time.

The locator object is provided before reporting any other document
events (@see ISAXContentHandler). If no locator has been set by
the time the application receives the startDocument event, the
application should assume that a locator is not available.


@see ISAXContentHandler#SetDocumentLocator
        */

class ISAXLocator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXLOCATOR };
	
        /**
        Adopt an instance of a CAXELocator class provided by the parser.
        This is not intended to by used by clients.
        */

	virtual void Adopt(const AXE8_Parser parser, ISAXServices* owner) = 0;

        /**
        Public identifier for the current document event

        @param s                Set to the public identifier or
                                left unchanged if kFalse is
                                returned.

        @return                 kTrue if a public identifier is
                                defined, kFalse otherwise.

        @see #GetSystemId
        */
	virtual bool16 GetPublicId(WideString& s) const = 0;

        /**
        System identifier for the current document event

        If the system identifier is a URL, the parser must resolve it
        fully before passing it to the application.

        @param s                Set to the system identifier or
                                left unchanged if kFalse is
                                returned.

        @return                 kTrue if a system identifier is
                                defined, kFalse otherwise.

        @see #GetPublicId
        */
	virtual bool16 GetSystemId(WideString& s) const = 0;
	
        /**
        Line number where the current document event ends

        Note that this is the line position of the first character
        after the text associated with the document event.

        @return The line number, or -1 if none is available.

        @see #GetColumnNumber
        */
	virtual int32 GetLineNumber() const = 0;

        /**
        Column number where the current document event ends.

        Note that this is the column number of the first
        character after the text associated with the document
        event.  The first column in a line is position 1.

        @return The column number, or -1 if none is available.

        @see #GetLineNumber
        */
	virtual int32 GetColumnNumber() const = 0;

		/*
		The two following functions are intended to be private
		calls made by the parser callbacks for Shared Expat.
		*/
	virtual void setPublicID(const WideString& s) = 0;
	virtual void setSystemID(const WideString& s) = 0;

};

#endif