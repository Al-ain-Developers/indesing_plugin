//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBlackBoxData.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IBlackBoxData__
#define __IBlackBoxData__


#include "IPMUnknown.h"
#include "DocFrameworkID.h"


typedef ClassID BlackBoxKey;

#define kInvalidBlackBoxKey kInvalidClass

/** This is an interface to a container for generic data. Use this interface if you want
	to attach data to an InDesign document, but you want complete control and responsibility
	over how the data is managed. 
*/
class IBlackBoxData : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IBLACKBOXDATA };

	/** Use this to find out if the black box already has data stored under your key.
		@param key the key to check for
		@return bool16 kTrue if black box does contain data, kFalse otherwise
	*/
	virtual int32 GetDataLength(BlackBoxKey clsID) = 0;
	
	/** Read data out of the black box and into the buffer passed in by the client.
		@param key the key used for storing the data originally
		@param buffer to place the data in
		@param amountToRead maximum amount to read
		@return int32 number of bytes read
	*/
	virtual int32 ReadData(BlackBoxKey key, void *buffer, int32 amountToRead) = 0;
	
	/** Write data out of the buffer, into the black box, using the supplied key.
		The key can be used later to read the data back in. If there is already
		data stored under that key, the old data is replaced by the new data.
		Therefore make sure you use a unique key that was created using a prefix
		that has been assigned to your exclusive use.
		@param key to associate with the data
		@param buffer that contains the data
		@param length number of bytes to write
	*/
	virtual void WriteData(BlackBoxKey key, void *buffer, int32 length) = 0;
	
	/** Remove the data stored with the key from the buffer. If there is no data
		this does nothing.
		@param key specifies which piece of data to delete (@see WriteData).
	*/
	virtual void RemoveData(BlackBoxKey key) = 0;
	
	/** For internal use only */
	virtual BlackBoxKey GetNextKey(BlackBoxKey key) const = 0;

};



#endif // __IBlackBoxData__
