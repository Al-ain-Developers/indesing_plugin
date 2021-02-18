//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IBarcodeSuite.h $
//  
//  Owner: Reena Agrawal
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
//  Comments:	Selection suite for barcode page items
//  
//========================================================================================

#pragma once
#ifndef _IBarcodeSuite_
#define _IBarcodeSuite_

#include "EPSID.h"
#include "IBarcodeFacade.h"
#include "IQRCodeMetaData.h"
#include "IQREmailData.h"
#include "IQRvCardData.h"
#include "IQRSmsData.h"
#include "IQRHyperLinkData.h"
#include "IQRPlainTextData.h"

/** Selection suite for manipulating barcodes like QR codes.	
*/

class IBarcodeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBARCODESUITE};

	/** @return kTrue if we can create a QR code from the selection. If there is no selection or a qr code can not 
		be created from the selection, this method returns false.
	*/
	virtual bool16 CanCreateQRCodeFromSelection() const = 0;
	
	/** Create an email QR code to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully.
	*/
	virtual ErrorCode CreateQRCodeEmailFromSelection(const PMString& to, const PMString& sub, const PMString& msg, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;

	/** Create a business card QR code to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully.
	*/
	virtual ErrorCode CreateQRCodevCardFromSelection(const Facade::IBarcodeFacade::VCardData& vCardData, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;

	/** Create a sms QR code to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully.
	*/
	virtual ErrorCode CreateQRCodeSmsFromSelection(const PMString& to, const PMString& message, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;	

	/** Create a hyperlink QR code to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully.
	*/
	virtual ErrorCode CreateQRCodeHyperLinkFromSelection(const PMString& url, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;

	/** Create a text QR code to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully.
	*/
	virtual ErrorCode CreateQRCodePlainTextFromSelection(const PMString& text, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;
	
	/** @return kTrue if selection is QR Code (or default selection) */
	virtual bool16 IsQRCodeSelection() const = 0;
	
	/** Get the UID of the data for the selected QR code.
		@return UID of the data.
	*/
	virtual UID GetQRCodeDataUID() const = 0;

	/** Get the UIDRef of the data for the selected QR code.
		@return UIDRef of the data.
	*/
	virtual UIDRef GetQRCodeDataUIDRef() const = 0;

	/** Create a business card QR code (including State) to be placed into the selected page item or the place gun as the case may be.
		@return kSuccess if QR code gets created successfully. Uses VCardData2 which contains State information.
	*/
	virtual ErrorCode CreateQRCodevCardFromSelection_2(const Facade::IBarcodeFacade::VCardData2& vCardData, IQRCodeMetaData::ErrorLevel level, const UID& qrCodeSwatchUID) = 0;
};


#endif // _IQRCodeSuite_
