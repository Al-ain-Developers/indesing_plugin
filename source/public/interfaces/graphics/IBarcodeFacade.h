//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IBarcodeFacade.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef _IBARCODEFACADE_
#define _IBARCODEFACADE_

#include "EPSID.h"
#include "PMString.h"
#include "IQRCodeMetaData.h"

namespace Facade
{
	class IBarcodeFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IBARCODEFACADE};

		struct VCardData 
		{
			PMString	FirstName,
						LastName,
						JobTitle,
						TelNo,
						CellNo,
						Email,
						Website,
						Org,
						Street,
						City,
						Zip,
						Country;
		};

		struct VCardData2 // Adds State
		{
			PMString	FirstName,
						LastName,
						JobTitle,
						TelNo,
						CellNo,
						Email,
						Website,
						Org,
						Street,
						City,
						State,
						Zip,
						Country;
		};

		// Utility methods to Create QRCodes.
		// 1. If the QRCode will replace a page item, specify its UIDRef as 1st parameter.
		//    	If QRCode will instead load in placegun, create a UIDRef with UID == kInvalidUID, pointing to document database.
		// 2. ErrorLevel is used to specify the fault tolerance level for QRCode. Currently, only QRCodes with fault tolerance of 15% (kM) can be created. 
		//		Other values from IQRCodeMetaData::ErrorLevel enum can be passed in, but they are not applied right now.
		// 3. Returns - UID of created QRCode if successful, kInvalidUID otherwise.

		virtual UID CreateQRCodeEmail(const UIDRef& toReplace, const PMString& to, const PMString& subject, const PMString& message, 
			IQRCodeMetaData::ErrorLevel level = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;

		/* 
			@Deprecated This API is deprecated. Please Use CreateQRCodeVCard_2() instead. This API does not include the state field in the address field of the vCard.
		*/ 

		virtual UID CreateQRCodeVCard(const UIDRef& toReplace, const VCardData& vcardData, IQRCodeMetaData::ErrorLevel level  = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;

		virtual UID CreateQRCodeSMS(const UIDRef& toReplace, const PMString& to, const PMString& message,
			IQRCodeMetaData::ErrorLevel level  = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;

		virtual UID CreateQRCodeHyperLink(const UIDRef& toReplace, const PMString& url,
			IQRCodeMetaData::ErrorLevel level = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;

		virtual UID CreateQRCodeText(const UIDRef& toReplace, const PMString& text,
			IQRCodeMetaData::ErrorLevel level = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;

		virtual bool16 IsQRCode(const UIDRef& uidref) = 0;
		
		// Creates QRCode of type Business Card (vCard). CreateQRCodeVCard() did not include the state field in the address of the vCard. 
		// CreateQRCodeVCard_2() adds the state to the address as well.

		virtual UID CreateQRCodeVCard_2(const UIDRef& toReplace, const VCardData2& vcardData, IQRCodeMetaData::ErrorLevel level  = IQRCodeMetaData::kM, const UID& qrCodeSwatchUID = kInvalidUID) = 0;
	};
}

#endif // IBarcodeFacade
