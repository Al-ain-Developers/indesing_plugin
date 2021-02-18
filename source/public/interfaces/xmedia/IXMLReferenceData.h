//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLReferenceData.h $
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
//========================================================================================

#pragma once
#ifndef __IXMLReferenceData__
#define __IXMLReferenceData__

#include "IPMUnknown.h"
#include "XMLID.h"

class XMLReference;


/** Data interface for specifying an element on the XML structure tree. */
class IXMLReferenceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLREFERENCEDATA };


	/**	Mutator for reference stored on this interface
		@param newItem specifies new value for stored reference
	 */
	virtual void Set(const XMLReference& newItem) = 0;

	/**	Accessor for reference stored on this interface
		@return XMLReference stored on this interface 
	 */
	virtual const XMLReference& GetReference() const = 0;
};

#endif	// __IXMLReferenceData__
