//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGUtils.h $ 
//   
//  Owner: Gaurav T Kakkar
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
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved. 
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
#ifndef __ISVGUtils__ 
#define __ISVGUtils__ 

#include "EPSID.h" 

class ISVGUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISVGUTILS };
	/** Method to copy preferences from one interface to another.
	@param file is the input IDFile to create gzip compressed stream.
	@param mode is OpenMode: kOpenIn = 0x01, kOpenOut = 0x02,  kOpenApp = 0x04, kOpenTrunc = 0x08 
	@return gzip compressed stream.
	*/
	virtual IPMStream *CreateZipStream(IDFile const &file, uint32 mode) = 0;

	/** Method to copy preferences from one interface to another.
	@param fileStream is the file stream of the file to create gzip compressed stream.
	@param mode is OpenMode: kOpenIn = 0x01, kOpenOut = 0x02,  kOpenApp = 0x04, kOpenTrunc = 0x08
	@return gzip compressed stream.
	*/
	virtual IPMStream *CreateZipStream(IPMStream *fileStream, uint32 mode) = 0;
	

	/** Method to check if a file stream is valid gzip compression or not.
	@param fileStream is the file stream to check if it is valid gzip compression or not.
	@return kTrue if valid gzip compression otherwise kFalse.
	*/
	virtual bool16 IsCompressed(IPMStream* fileStream) = 0;
};

#endif    // __ISVGUtils__ 
