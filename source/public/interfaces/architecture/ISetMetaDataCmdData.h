//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetMetaDataCmdData.h $
//  
//  Owner: 
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
#ifndef __ISetMetaDataCmdData__
#define __ISetMetaDataCmdData__

#include "IPMUnknown.h"

//Utils && IDs
#include "LibraryProviderID.h"
#include "ILibraryAssetMetaData.h"
#include "GlobalTime.h"

//========================================================================================
// INTERFACE ISetMetaDataCmdData
//========================================================================================

/** 
	Data interface for the command (kSetMetaDataCmdBoss) to set meta data of Library Assets.
*/

class ISetMetaDataCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISETMETADATACMDDATA };

		/** Get library asset's pointer.
			@return the pointer to the library asset this command is being executed against.
		*/
		virtual IPMUnknown* GetLibraryAsset() const = 0;

		/** Set the library asset that this command is going to be executed against.
			@param asset IN pointer to the library asset
		*/
		virtual void SetLibraryAsset(IPMUnknown* asset) = 0;
		
		/** Set the asset's name.
			@param name IN string containing a new name for the asset
		*/
		virtual void SetName(const PMString &name) = 0;
		
		/** Get the asset's name.
			@return the name given the asset
		*/
		virtual PMString GetName() const = 0;
		
		/** Set the asset's User Type 
			@param userType IN User Type to assign to the asset
		*/
		virtual void SetUserType(const  ILibraryAssetMetaData::UserType  userType) = 0 ;
		
		/** Get the asset's User Type.
			NOTE: User Type is just for user classification.  It may or may not be accurate.
			@return the UserType given the asset
		*/
		virtual ILibraryAssetMetaData::UserType GetUserType() const = 0 ;
		
		/** Sets the asset's description.
			@param description IN string containing a new description for the asset
		*/
		virtual void SetDescription(const PMString &description) = 0 ;
		
		/** Get the asset's description.
			@return the description given the asset
		*/
		virtual PMString GetDescription() const = 0 ;
		
		/** Set the creation time of the asset.  This method is intended for use by 
			code converters; clients in general should not re-set an existing creation time for an 
			asset.
			@param t IN the time to assign to the asset's creation time
		*/
		virtual void SetCreationTime(GlobalTime t) = 0 ;
		
		/** Get the creation time (and date) of the asset
			@return the timestamp for the asset's creation
		*/
		virtual GlobalTime GetCreationTime() const = 0;
		
};
#endif
