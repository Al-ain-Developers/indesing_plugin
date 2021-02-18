//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IScrapImageList.h $
//  
//  Owner: Dave Stephens
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
#ifndef __IScrapImageList__
#define __IScrapImageList__

#include "IPMUnknown.h"

/** The IScrapImageList is an interface, which should probably be private, which is used
	the LowResImageRefConverter when copying and pasting images.  Its purpose is to make the
	copying and pasting of placed images as efficient as possible by reference counting the
	proxy images for these placed images instead of duplicating the pixel data.  This reference
	counting strategy is performed using the ILowResImageList interface which is present for
	each document.
	@see ILowResImageList
*/
class IScrapImageList : public IPMUnknown
{
public:
	/** Find the zero-based index of the entry in the ScrapImageList for the given proxy UID.
		@param lowResUID - IN: UID of the proxy image of the placed image.
		@return Zero based index of the element in the list or -1 if it cannot be found.
	*/
	virtual int32 FindImage(UID lowResUID) const = 0;

	/** This method is similar to FindImage except that there are actually two UIDs for each
		image maintained by this list.  The 2 UIDs are necessary because the target document
		may be a different document from the source document.  The actual UID should be that 
		of the original image which was copied.  The lowResUIDkey is a dummy "promise" proxy 
		which is created on the scrap for the purpose of getting the LowResImageRefConverter 
		to be called at paste time.
		@param actualLowResUID - IN: UID of the original proxy image that was copied.
		@return Zero based index of the element in the list or -1 if it cannot be found.
	*/
	virtual int32 FindImageActualUID(UID actualLowResUID, IDataBase *db) const = 0;

	/** @return The number of proxy image entries in the list
	*/
	virtual int32 Length(void) const = 0;

	/** Add an entry to the list which is keyed by the UID of a proxy
		image.  The actual UID should be that of the original image which was copied.
		The lowResUIDkey is a dummy "promise" proxy which is created on the scrap for the
		purpose of getting the LowResImageRefConverter to be called at paste time.
		@param lowResUIDkey - IN: dummy UID "promise" for the proxy valid only on the scrap.
		@param actualUID - IN: UID of the original proxy image which was copied.
		@param srcDB - IN: Pointer to the source database.
	*/
	virtual void Add(UID lowResUIDkey, UID actualUID, IDataBase* srcDB) = 0;

	/** Remove the entry at position 'at'
		@param at - IN: zero based index of the image entry to remove
	*/
	virtual void Remove(int32 at) = 0;

	/** After a conversion is performed, store the UID of the converted image.
		@param at - IN: zero-based index of the image entry
		@param lastUID - IN: the UID of the converted image
		@param lastDB - IN: The database in which the lastUID refers.
	*/
	virtual void SetLastUIDConverted(int32 at, UID lastUID, IDataBase *lastDB) = 0;

	/** Retrieve the UID and IDataBase of the last converted image for the given image entry.
		@param at - IN: zero-based index of the image entry
		@param lastUID - OUT: the UID of the converted image
		@param lastDB - OUT: The database in which the lastUID refers.
	*/
	virtual void GetLastUIDConverted(int32 at, UID *lastUID, IDataBase **lastDB) = 0;

	/** If the original image which was copied gets deleted, then an actual copy
		is added to the scrap and this method is called to update an entry which used
		to reference the original.
		@param at - IN: zero-based index of the image entry
		@param newUID - IN: UID of the newly created proxy image.
	*/
	virtual void SetActualUID(int32 at, UID newUID) = 0;

	/** Retrieve the actual UID.
		@param at - IN: zero-based index of the image entry
		@return UID of the actual image.
		@see SetActualUID
	*/
	virtual UID GetActualUID(int32 at) const = 0;

	/** Set the source database.
		@param at - IN: zero-based index of the image entry
		@param newDB - IN: pointer to the new source database.
	*/
	virtual void SetDataBase(int32 at, IDataBase *newDB) = 0;
	
	/** Get the UID stored at zero-based index 'at'.  Keep in mind that the UID
		may be a dummy "promise" UID.
		@param at - IN: zero-based index of the image entry
		@return promise UID
	*/
	virtual UID GetUID(int32 at) const = 0;

	/** Get the source database.
		@param at - IN: zero-based index of the image entry
		@return source database
	*/
	virtual IDataBase* GetDataBase(int32 at) const = 0;

	/** Method to persist or read this interface.
		@param iPMStream - IN/OUT: if reading, then this is the input stream.  If writing then this
			is the output stream.
		@param prop - IN: Implementation ID
	*/
	virtual void ReadWrite (IPMStream* iPMStream, ImplementationID prop) = 0;
};

#endif

