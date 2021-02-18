//========================================================================================
 //  
 //  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICreateQRCodeCmdData.h $
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
 //========================================================================================
 
 #pragma once
 #ifndef __ICreateQRCodeCmdData_h__
 #define __ICreateQRCodeCmdData_h__
 
 #include "IPMUnknown.h"
 #include "IQRCodeMetaData.h"
 #include "PMString.h"
 #include "EPSID.h"
 
 /** Command parameters for the CreateFormField command
 */
 class ICreateQRCodeCmdData : public IPMUnknown
 {
 public:
	 enum { kDefaultIID = IID_ICREATEQRCODECMDDATA };

	 /** Set the data required by the command for creating the QR code.
		@param db IN The target database.
		@param textToEncode IN The text to encode as QR code.
		@param level IN The error tolerance level of the QR code.
		@param swatchUID IN The UID of the color swatch used for creating the QR code.
	*/
	 virtual void Set(IDataBase* db, const PMString& textToEncode, IQRCodeMetaData::ErrorLevel level, UID swatchUID) = 0;

	 /** Get the text string to encode as QR code.
		@return text to encode as QR code.
	*/
	 virtual PMString GetTextToEncode() const = 0;
	 
	 /** Get the error tolerance level of the QR code.
		@return error tolerance level of the QR code.
	*/
	 virtual IQRCodeMetaData::ErrorLevel GetErrorToleranceLevel() const = 0;
	 
	 /** Get the target database.
		@return target database.
	*/
	 virtual IDataBase* GetDataBase () const = 0;

	 /** Get the UID of the color swatch used for creating the QR code.
		@return UID of the color swatch used for creating the QR code.
	*/
	 virtual UID GetQRCodeSwatchUID () const = 0;

 };
 
 //=============================================================================
 
 #endif // __ICreateQRCodeCmdData_h__
