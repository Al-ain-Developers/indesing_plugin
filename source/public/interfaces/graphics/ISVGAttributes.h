//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGAttributes.h $
//  
//  Owner: Gaurav T Kakkar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose:
//  Stores info about an SVG page item.
//  
//========================================================================================

#pragma once
#ifndef __ISVGAttributes__
#define __ISVGAttributes__

#include "IPMUnknown.h"
#include "EPSID.h"

class ISVGAttributes : public IPMUnknown
{
public:
	
	/** Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_ISVGATTRIBUTES };
	
	typedef enum {
		//Export with SVG code embedded in stream
		kEPubExportAsEmbededCode = 0,
		//Export with object tag
		kEPubExportAsObjectTag
	}EPubExportSVGStrategy;

	/**
	@param strategy		IN the strategy with which this SVG will be exported
	Sets the EPUB/HTML export strategy for this SVG item.
	*/
	virtual void SetEPubExportStrategy(const EPubExportSVGStrategy strategy) =0;
	
	/**
	Returns the EPUB/HTML export strategy for this SVG item.
	*/
	virtual EPubExportSVGStrategy GetEPubExportStrategy() const = 0;
};

#endif
