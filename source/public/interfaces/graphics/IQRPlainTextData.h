//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRPlainTextData.h $
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

#ifndef __IQRPLAINTEXTDATA__
#define __IQRPLAINTEXTDATA__

#include "IPMUnknown.h"
#include "EPSID.h"

#include "IQRCodeStringData.h"

/** Interface for simple text type of QR code.
	*/

class IQRPlainTextData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQRPLAINTEXTDATA };

	/** Set the text to be encoded as QR code.
		@param text IN The text to be encoded.
	*/
	virtual void SetText(const PMString& text) = 0;
	
	/** Get the text encoded as QR code.
		@return text encoded as QR code.
	*/
	virtual PMString GetText() const = 0;

	/** Copy the text to be encoded from source IQRPlainTextData.
		@param source IN The plain text data to copy.
	*/
	virtual void CopyFromText(const IQRPlainTextData* source) = 0;
};

#endif