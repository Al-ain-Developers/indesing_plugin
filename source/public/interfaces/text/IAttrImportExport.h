//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAttrImportExport.h $
//  
//  Owner: Rahul Shinde
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
#ifndef __IAttrImportExport__
#define __IAttrImportExport__

#include "IPMUnknown.h"
#include "TaggedTextTypes.h"

class PMString;
class IPMStream;

/**
    Utility interface for the tagged text attributes import and export.
*/
class IAttrImportExport : public IPMUnknown
{
	public:
		
		/** Global error codes */
		typedef enum {
			/** No error */
			kNoError = 0x00,
			/** Error in value conversion */
			kConversionError = 0x01,
			/** Value is out of range */
			kOutOfRange = 0x02,
			/** Invalid value */
			kInvalidValue = 0x03
		} SetValueErrorCode;

		
/**	 Get the verbose tag name
	@param pTagName OUT Verbose tag name  
 */
		virtual void GetTagName(PMString *pTagName) const = 0;

/**	 Get the abbreviated tag name
	@param pTagAbbr OUT Abbreviated tag name
 */
		virtual void GetTagAbbr(PMString *pTagAbbr) const = 0;

/**	 Get the tag value 
	@param pTagValue OUT Tag value 
	@param dB        IN  Database associated with the tag 
 */
		virtual void GetTagValue(PMString *pTagValue, IDataBase *dB = nil)  const = 0;

/**	 Set the tag value
	@param rTagValue IN Tag value
	@param dB        IN Database associated with the tag
	@return IAttrImportExport::SetValueErrorCode  Error occurred while doing value conversion, return kNoError if succeeded
 */
		virtual IAttrImportExport::SetValueErrorCode SetTagValue(const PMString& rTagValue, IDataBase *dB = nil) = 0;


/**	 Get the PMIID of the Data Interface to which the attribute belongs
	@param none
	@return PMIID PMIID of the Data interface
 */
		virtual PMIID GetDataPMIID() const = 0;

/**	 Get the BossID of Boss to which the attribute belongs
	@param none
	@return ClassID 
 */
		virtual ClassID GetClassID() const = 0;

/**	 Read/Write the Tag Value from stream based on the stream type
	@param s        INOUT Stream
	@param encoding IN    Encoding type
	@param dB       IN    Database associated with the attribute
 */
		virtual void ReadWriteTagValue(IPMStream *s, EncodingType encoding, IDataBase *dB = nil) = 0;
};

#endif		// __IAttrImportExport__
