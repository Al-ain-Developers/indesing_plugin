//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRHyperLinkData.h $
//  
//  Owner: kaubansa
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once

#ifndef __IQRHYPERLINKDATA__
#define __IQRHYPERLINKDATA__

#include "IPMUnknown.h"
#include "EPSID.h"

#include "IQRCodeStringData.h"

/** Interface for web URL type of QR code.
	*/
class IQRHyperLinkData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQRHYPERLINKDATA };

	/** Set the web URL for the web hyperlink type QR code.
		@param link IN The web URL.
	*/
	virtual void SetLink(const PMString& link) = 0;

	/** Get the web URL encoded as web hyperlink type QR code.
		@return web URL encoded as web hyperlink type QR code.
	*/
	virtual PMString GetLink() const = 0;

	/** Copy the data for web hyperlink type QR code data from source IQRHyperLinkData.
		@param source IN The web hyperlink QR code data to copy.
	*/
	virtual void CopyFromHyperLink(const IQRHyperLinkData*) = 0;
};

#endif