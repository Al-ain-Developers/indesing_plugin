//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRCodeMetaData.h $
//  
//  Owner: Kaustubh Bansal
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
//  Comments:	Data common for all types of QR codes.
//  
//========================================================================================

#pragma once

#ifndef __IQRCODEMETADATA__
#define __IQRCODEMETADATA__

#include "IPMUnknown.h"
#include "IQRCodeStringData.h"

#include "EPSID.h"

/** Interface for keeping data common to all types of QR codes.
	*/

class IQRCodeMetaData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQRCODEMETADATA };

	enum ErrorLevel
	{
		kL = 1,		// upto 7% damage
		kM,			// upto 15% damage. This is the default error level.
		kQ,			// upto 25% dmamage
		kH			// upto 30% damage
	};

	/** Set the error level to be used for creating the QR code.
		The default error level is kM.
	*/
	virtual void SetErrorLevel (ErrorLevel er) = 0;

	/** Set the swatch UID to be used for creating the QR code.
	*/
	virtual void SetQRCodeColorUID (UID swatchUID) = 0;

	/** Get the error level used for creating the QR code.
		@return error level used.
	*/
	virtual ErrorLevel GetErrorLevel () const = 0;

	/** Get the swatch UID used for creating the QR code.
		@return UID of the swatch used..
	*/
	virtual UID GetQRCodeColorUID () const = 0;

};

#endif
