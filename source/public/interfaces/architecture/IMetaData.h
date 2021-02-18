//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMetaData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IMetaData_h__
#define __IMetaData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


class ILink;
class IPMStream;

//========================================================================================
// CLASS IMetaData
//========================================================================================

/**
    Interface for replicating MetaData
*/

class IMetaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMETADATA };
	
	/**	Creates a clone metadata object for a rendition.
		Clears the 'xapMM:Manifest' property of the cloned object.
		The 'xapMM:RenditionClass' property of the cloned object is set to renditionClass.
		And the 'xap:Format' property of the cloned object is set to format.
		@param renditionClass	IN	The rendition class name.
		@param format			IN	The resource format.
		@return IMetaData*		IID_IMETADATA interface on newly cloned object.
	 */
	virtual IMetaData*		CloneForRendition(const PMString& renditionClass, const metadata::MIMEType& format) const = 0;
	

	/**	Clones new object of classID and returns IID_IMETADATA interface on newly created object.
		If db is non-nil, new object is created persistently. Otherwise it is non-persistent.
		Returns nil if the object cannot be created or IID_IMETADATA interface does not exist.
		@param db			IN	DataBase
		@param classID		IN	Boss class
		@return IMetaData*	IID_IMETADATA interface on newly created object.
		@see IDataBase
	 */
	virtual IMetaData*		Clone(IDataBase* db = nil, const ClassID& classID = kMetaDataBoss) const = 0;

	/**	Fills this metadata boss with metadata from 'srcMetaData'
		@param srcMetaData IN The source MetaData
	 */
	virtual void			Copy(const IMetaData* srcMetaData) = 0;

	/**	Adds a reference of the link to xmpMM:Manifest
		The reference of the link in the Manifest is obtained through asset management system or the link's XMP data.
		If neither of them are avilable and useFileURL is kTrue, the link's file location is used as the reference.
		@param iLink		IN	Pointer to the ILink instance that can be used to obtain the metadata.
		@param useFileURL	IN	whether to use link's file location as the reference, if the reference of the link is not obtained through both asset management system and the link's XMP data
		@see ILink
	 */
	virtual void			LinkedResourceAdded(ILink* iLink, bool16 useFileURL = kTrue) = 0;
};

#endif // __IMetaData_h__
