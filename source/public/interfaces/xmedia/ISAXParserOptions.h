//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXParserOptions.h $
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
//========================================================================================

#pragma once
#ifndef __ISAXParserOptions_h__
#define __ISAXParserOptions_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

class ISAXContentHandler;
class ISAXEntityResolver;

	/**
	An interface for specifying the set of options/features desired when parsing
	an XML file.  Used in conjunction with SAXServices to parse XML content correctly.
	*/
class ISAXParserOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXPARSEROPTIONS };
	
    /** Returns kTrue if namespace constraints are enabled. */
	virtual bool16 IsNamespacesFeatureEnabled() const = 0;
 
    /** Apply namespace constraints and processing. Enabled by default. */
	virtual void SetNamespacesFeature(bool16 enable) = 0;
	
    /** Returns kTrue if an parsing warnings will display an alert. */
	virtual bool16 IsShowWarningAlertEnabled() const = 0;

    /** When enabled, a parsing alert will display a warning.  Enabled by default. */
	virtual void SetShowWarningAlert(bool16 enable) = 0;

    /** Returns kTrue if parsing will abort if a warning is encountered. */
	virtual bool16 IsAbortAfterWarningEnabled() const = 0;

    /** When enabled, a parsing warning will also abort any furthur parsing just like an error. */
	virtual void SetAbortAfterWarning(bool16 enable) = 0;
};

#endif