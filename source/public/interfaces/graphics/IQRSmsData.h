//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRSmsData.h $
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

#ifndef __IQRSMSDATA__
#define __IQRSMSDATA__

#include "IPMUnknown.h"
#include "EPSID.h"

#include "IQRCodeStringData.h"

/** Interface for SMS type of QR code.
	*/

class IQRSMSData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQRSMSDATA };

	/** Set the phone number for the SMS type QR code.
		@param number IN The phone number.
	*/
	virtual void SetPhoneNumber(const PMString& number) = 0;

	/** Get the phone number of the SMS type QR code.
		@return phone number of the SMS type QR code.
	*/
	virtual PMString GetPhoneNumber() const = 0;
	
	/** Set the text SMS message encoded as SMS type QR code.
		@param message IN The SMS text message to be encoded.
	*/
	virtual void SetMessage(const PMString& message) = 0;

	/** Get the text SMS message encoded as SMS type QR code.
		@return SMS text message encoded as SMS type QR code.
	*/
	virtual PMString GetMessage() const = 0;

	/** Copy the data for SMS type QR code data from source IQRSMSData.
		@param source IN The SMS QR code data to copy.
	*/
	virtual void CopyFromSms(const IQRSMSData* source) = 0;
};

#endif