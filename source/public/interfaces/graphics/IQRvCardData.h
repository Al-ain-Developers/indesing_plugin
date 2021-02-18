//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IQRvCardData.h $
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

#ifndef __IQRVCARDDATA__
#define __IQRVCARDDATA__

#include "IPMUnknown.h"
#include "EPSID.h"

#include "IQRCodeStringData.h"

/** Interface for visiting card type of QR code.
	*/

class IQRvCardData : public IQRCodeStringData
{
public:
	enum { kDefaultIID = IID_IQRVCARDDATA };

	/** Set the first name for the vcard type QR code.
		@param firstName IN The first name.
	*/
	virtual void SetFirstName(const PMString &firstName) = 0;

	/** Get the first name for the vcard type QR code.
		@return first name for the vcard type QR code.
	*/
	virtual PMString GetFirstName() const = 0;

	/** Set the last name for the vcard type QR code.
		@param lastName IN The last name.
	*/
	virtual void SetLastName(const PMString &lastName) = 0;

	/** Get the last name for the vcard type QR code.
		@return last name for the vcard type QR code.
	*/
	virtual PMString GetLastName() const = 0;

	/** Set the job title for the vcard type QR code.
		@param jobTitle IN The job title.
	*/
	virtual void SetJobTitle(const PMString &jobTitle) = 0;

	/** Get the job title for the vcard type QR code.
		@return job title for the vcard type QR code.
	*/
	virtual PMString GetJobTitle() const = 0;

	/** Set the telephone number for the vcard type QR code.
		@param telNo IN The telephone number.
	*/
	virtual void SetTelNo(const PMString &telNo) = 0;

	/** Get the telephone number for the vcard type QR code.
		@return telephone number for the vcard type QR code.
	*/
	virtual PMString GetTelNo() const = 0;

	/** Set the cell phone number for the vcard type QR code.
		@param cellNo IN The cell phone number.
	*/
	virtual void SetCellNo(const PMString &cellNo) = 0;

	/** Get the cell phone number for the vcard type QR code.
		@return cell phone number for the vcard type QR code.
	*/
	virtual PMString GetCellNo() const = 0;

	/** Set the email address for the vcard type QR code.
		@param email IN The email address.
	*/
	virtual void SetEmail(const PMString &email) = 0;

	/** Get the email address for the vcard type QR code.
		@return email address for the vcard type QR code.
	*/
	virtual PMString GetEmail() const = 0;

	/** Set the web site URL for the vcard type QR code.
		@param website IN The website URL.
	*/
	virtual void SetWebsite(const PMString &website) = 0;

	/** Get the web site URL for the vcard type QR code.
		@return web site URL for the vcard type QR code.
	*/
	virtual PMString GetWebsite() const = 0;

	/** Set the organization for the vcard type QR code.
		@param org IN The organization.
	*/
	virtual void SetOrganization(const PMString &org) = 0;

	/** Get the organization for the vcard type QR code.
		@return organization for the vcard type QR code.
	*/
	virtual PMString GetOrganization() const = 0;

	/** Set the street address for the vcard type QR code.
		@param street IN The street address.
	*/
	virtual void SetStreetAddress(const PMString &street) = 0;

	/** Get the street address for the vcard type QR code.
		@return street address for the vcard type QR code.
	*/
	virtual PMString GetStreetAddress() const = 0;

	/** Set the city for the vcard type QR code.
		@param city IN The city.
	*/
	virtual void SetCity(const PMString &city) = 0;

	/** Get the city for the vcard type QR code.
		@return city for the vcard type QR code.
	*/
	virtual PMString GetCity() const = 0;

	/** Set the postal code for the vcard type QR code.
		@param zip IN The postal code.
	*/
	virtual void SetZip(const PMString &zip) = 0;

	/** Get the postal code for the vcard type QR code.
		@return postal code for the vcard type QR code.
	*/
	virtual PMString GetZip() const = 0;

	/** Set the country for the vcard type QR code.
		@param country IN The country.
	*/
	virtual void SetCountry(const PMString &country) = 0;

	/** Get the country for the vcard type QR code.
		@return country for the vcard type QR code.
	*/
	virtual PMString GetCountry() const = 0;

	/** Copy the data for visiting card type QR code data from source IQRvCardData.
		@param source IN The visiting card type QR code data to copy.
	*/
	virtual void CopyFromVCard(const IQRvCardData* source ) = 0;

	/** Set the state for the vcard type QR code.
		@param state IN The state.
	*/
	virtual void SetState(const PMString &state) = 0;

	/** Get the state for the vcard type QR code.
		@return state for the vcard type QR code.
	*/
	virtual PMString GetState() const = 0;
};

#endif
