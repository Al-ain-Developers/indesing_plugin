//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/IAsciiEncodingUtils.h $
//  
//  Owner: Chris Jones
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
#ifndef __IEncodingUtils__
#define __IEncodingUtils__

#include "IPMUnknown.h"

#include "UtilitiesID.h"

class IPMStream;


class IAsciiEncodingUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASCIIENCODINGUTILS };

	// Type of encoding
	typedef enum
	{
		// encoding type.
		kHexEncoding      = 0x01,
		kAscii85Encoding  = 0x02,
		kAscii64Encoding  = 0x04
		
		// future, compression types.
		// todo
	} EncodingOptions;

	/**
	 *  Encode the specificed src array and place the result in the specified string.
	 */
	virtual void Encode( int32 nOptions, unsigned char* pSrc, int32 nSrcBytes, PMString& strDst ) = 0;

	/**
	 *  Encode the specificed src stream and place the result in the specified string.
	 */
	virtual void Encode( int32 nOptions, IPMStream* sStream, PMString& strDst ) = 0;

	/**
	 *  Encode the specificed src stream and place the result in the specified destination stream.
	 */
	virtual void Encode( int32 nOptions, IPMStream* sStream, IPMStream* dStream ) = 0;

	/**
	 *  Decode the specified string and return a dst array and the number of bytes it contains.
	 */
	virtual unsigned char* Decode( int32 nOptions, const PMString& strSrc, int32& nDstBytes ) = 0;

	/**
	 *  Decode the specified string and write the binary to the destination stream.
	 */
	virtual void Decode( int32 nOptions, const PMString& strSrc, IPMStream* dStream ) = 0;

	/**
	 *  Decode the specified source stream and write the binary to the destination stream.
	 */
	virtual void Decode( int32 nOptions, IPMStream* sStream, IPMStream* dStream ) = 0;



	/**
	 *  Encode the specificed src stream and place the result in the specified string.
	 */
	virtual void Encode( int32 nOptions, IPMStream* sStream, std::string& destString ) = 0;

	/**
	 *  Decode the specified string and return a dst array and the number of bytes it contains.
	 */
	virtual unsigned char* Decode( int32 nOptions, const std::string& strSrc, int32& nDstBytes ) = 0;

	/**
	 *  Decode the specified string and write the binary to the destination stream.
	 */
	virtual void Decode( int32 nOptions, const std::string& sourceString, IPMStream* dStream ) = 0;

};


#endif	
