//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQREmailData.h $
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

#ifndef __IQREMAILDATA__
#define __IQREMAILDATA__

#include "IPMUnknown.h"
#include "EPSID.h"

#include "IQRCodeStringData.h"

/** Interface for Email type of QR code.
	*/

class IQREmailData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQREMAILDATA };

	/** Set the email address of the recipient for the email type QR code.
		@param address IN The email address.
	*/
	virtual void SetAddress(const PMString& address) = 0;

	/** Get the email address of the recipient for the email type QR code.
		@return email address of the email type QR code.
	*/
	virtual PMString GetAddress() const = 0;

	/** Set the subject for the email type QR code.
		@param subject IN The subject for the email.
	*/
	virtual void SetSubject(const PMString& subject) = 0;

	/** Get the subject for the email type QR code.
		@return subject of the email type QR code.
	*/
	virtual PMString GetSubject() const = 0;

	/** Set the email message for the email type QR code.
		@param message IN The email message.
	*/
	virtual void SetMessage(const PMString& message) = 0;

	/** Get the email message for the email type QR code.
		@return email message of the email type QR code.
	*/
	virtual PMString GetMessage() const = 0;

	/** Copy the data for email type QR code data from source IQREmailData.
		@param source IN The email type QR code data to copy.
	*/
	virtual void CopyFromEmail(const IQREmailData* source) = 0;
};

#endif
