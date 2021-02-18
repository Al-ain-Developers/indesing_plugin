//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IExportOptionsUtils.h $
//  
//  Owner: Mainak Ghosh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this
//  file in accordance with the terms of the Adobe license agreement
//  accompanying it. If you have received this file from a source
//  other than Adobe, then your use, modification, or distribution of
//  it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IExportOptionsUtils__
#define __IExportOptionsUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

/**
	Utils for Object export options.
*/
class IExportOptionsUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEXPORTOPTIONSUTILS };

	/**
		This method computes the alternate text for an object based on its export options preferences.
		@param item IN the object to get the alternate text for
		@param altText OUT the alternate text
		@return ErrorCode: return error code on the basis of whether alt text exists or not
	*/
	virtual ErrorCode GetAlternateText(const UIDRef &item, PMString &altText) = 0;

	/**
		This method computes the actual text for an object based on its export options preferences.
		@param item IN the object to get the actual text for
		@param actualText OUT the actual text
		@return ErrorCode: return error code on the basis of whether actual text exists or not
	*/
	virtual ErrorCode GetActualText(const UIDRef &item, PMString &actualText) = 0;

	/**
		This method computes the metadata property value for an object given its xmp schema namespace prefix and path.
		@param item IN the object to get the metadata property value for
		@param nsPrefix IN metadata property xmp schema namespace prefix
		@param propertyPath IN metadata property path
		@param value OUT the value of the metadata property
		@return ErrorCode: return error code on the basis of whether metadata value exists or not
	*/
	virtual ErrorCode GetMetadataValue(const UIDRef &item, const PMString &nsPrefix, const PMString &propertyPath, PMString &value) = 0;

	/**
		This method computes the alternate/actual text for an object from the XML structure.
		@param item IN the object to get the alternate/actual text for
		@param alt IN bool value to specify whether to get alternate or actual text
		@param value OUT the value from the structure
		@return ErrorCode: return error code on the basis of whether structure text exists or not
	*/
	virtual ErrorCode GetStructureAttribute(const UIDRef &item, bool16 alt, PMString &value) = 0;
};

#endif	// __IExportOptionsUtils__
