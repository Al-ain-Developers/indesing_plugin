//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRCodeStringData.h $
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

#ifndef __IQRCODESTRINGDATA__
#define __IQRCODESTRINGDATA__

#include "IPMUnknown.h"
//#include "EPSID.h"

/** Interface for keeping data common to all types of QR codes.
	*/

class IQRCodeStringData : public IPMUnknown
{
public:

	/** This enum defines the various types of QR codes.
	*/
	enum
	{
		/** Web URL QR code type.*/
		kWebHyperlink = 0,	

		/** Simple text QR code type.*/
		kPlainText,

		/** SMS text message QR code type.*/
		kTextMessage,

		/** Email QR code type.*/
		kEmail,

		/** Visiting card QR code type.*/
		kBusinessCard
	}QRCodeTypes;

	/** Return the encoded string data for the QR code.
		@return encoded string for the QR code.
	*/
	virtual PMString GetEncodedString() const = 0;

	/** Return the tool tip string to be shown for the QR code.
		@return tool tip string for the QR code.
	*/
	virtual PMString GetToolTipString() const = 0;

};

#endif