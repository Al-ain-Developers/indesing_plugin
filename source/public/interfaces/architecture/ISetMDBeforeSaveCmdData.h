//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetMDBeforeSaveCmdData.h $
//  
//  Owner: Lin Xia
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

#ifndef __ISetMDBeforeSaveCmdData_h__
#define __ISetMDBeforeSaveCmdData_h__

// ----- Interfaces -----
#include "IPMUnknown.h"

// ----- ID.h files -----

#include "MetaDataID.h"

/**
	A data interface used by SetMetadataBeforeSaveCmd.
*/

//========================================================================================
// INTERFACE ISetMDBeforeSaveCmdData
//========================================================================================

class ISetMDBeforeSaveCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETMDBEFORESAVECMDDATA };

	/**
		Set the command data.
		@param	targetObject		IN	The target object of the command. It must have a IID_IMETADATA interface.
		@param	fileToSave			IN	The file to be saved.
		@param	generateManifest	IN	Whether to generate xapMM:Manifest.
		@param  isSaved				IN  Whether the file has been saved.
	*/
	virtual void			Set(IPMUnknown* targetObject, const IDFile &fileToSave, bool16 generateManifest, bool16 isSaved) = 0;

	/**
		Query an interface on the target object.
		@param	iid	IN	The ID of the interface to query.
		@return	The requested interface.
	*/
	virtual IPMUnknown*		QueryTargetObject(const PMIID& iid) const = 0;

	/**
		@return	The file to be saved.
	*/
	virtual IDFile			GetFileToSave() const = 0;
	/**
		@return	Whether to generate xapMM:Manifest.
	*/
	virtual bool16			ShouldGenerateManifest() const = 0;
	/**
		@return	Whether the file has been saved.
	*/
	virtual bool16			IsSaved() const = 0;
};

#endif // __ISetMDBeforeSaveCmdData_h__
