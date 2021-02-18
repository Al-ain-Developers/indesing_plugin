//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IJPEGImageWriteOptions.h $
//  
//  Owner: Lori Slater
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
#ifndef __IJPEGImageWriteOptions__
#define __IJPEGImageWriteOptions__

#include "IPMUnknown.h"
#include "IJPEGEncoder.h"

/** Data Interface used by the JPEGImageWriteFormat filter
@see IJPEGEncoder
*/
class IJPEGImageWriteOptions : public IPMUnknown
{
	public:
		/** Set the compression quality.  Has nothing to do with resolution or image quality.
			@param quality - IN: compression quality.
		*/
		virtual void SetJPEGQuality(JPEGQuality quality) = 0;

		/** Set the encoding scheme
			@param encoding - IN: jpeg encoding scheme.
		*/
		virtual void SetEncoding(JPEGEncoding encoding) = 0;

		/** Set whether or not to use huffman encoding.
			@param custom - IN: Use huffman encoding?
		*/
		virtual void SetCustomHuff(bool16 custom) = 0;

		/** Obsolete. You can safely ignore this method as the encoder does not actually use it.
		*/
		virtual void SetScanTabGroup(JPEGScanTabGroup group) = 0;

		/** Get counterpart to SetJPEGQuality
			@return compression quality
		*/
		virtual JPEGQuality GetJPEGQuality() const = 0;

		/** Get counterpart to SetEncoding
			@return encoding scheme
		*/
		virtual JPEGEncoding GetEncoding() const = 0;

		/** Retrieve the huffman encoding setting.
			@return kTrue to use custom huffman encoding
		*/
		virtual bool16 GetCustomHuff() const = 0;

		/** Obsolete
		*/
		virtual JPEGScanTabGroup GetScanTabGroup() const = 0;
};


#endif

