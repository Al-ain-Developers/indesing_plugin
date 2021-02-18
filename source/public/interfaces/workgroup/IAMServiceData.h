//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMServiceData.h $
//  
//  Owner: Bill Tislar
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
#ifndef __IAMSERVICEDATA__
#define __IAMSERVICEDATA__

#include "IPMUnknown.h"
#include "workgroupid.h"
#include "IAMUIService.h"

#include "IDFile.h"
#include "PMString.h"
#include "UIDRef.h"

#include <vector>


/** The IAMServiceData interface exchanges parameters with IAMService or IAMUIService
	implementations. The accessors ("Get" methods) and mutators ("Set" methods) of the
	interface handle the most the commonly used data types. Parameters are identified
	by specifying a predefined data identifier (dataID) which serves as the key. Predefined
	data identifiers used by InDesign/InCopy/InDesignServer are defined in IAMService.h and
	IAMUIService.h. The data type that a particular data identifier is mapped to is determined
	by the IAMService implementation. For example, "IAMService::enTargetAsset" could refer
	to a UIDRef, IDFile, or vector of IDFiles. See IAMServiceProvider.h for the currently
	used mappings.
	
	With the exception of the GetFlag() and Get void * accessors, all of the accessors return
	kTrue if the parameter could be found, and kFalse otherwise.
	
	@see IAMService.
	@see IAMUIService.
	@see IAMServiceProvider.
*/
class IAMServiceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMSERVICEDATA };

	typedef std::vector<IDFile> IDFileList;
	typedef std::vector<UIDRef> UIDRefList;
	
	/** Retrieves a service data parameter of type IDFile.
		@param dataID is a unique key to identify the data.
		@param outFile will be populated with the IDFile.
		@return kTrue if the data was found; kFalse otherwise.
	*/	
	virtual bool16 Get( int32 dataID, IDFile & outFile ) const = 0;
	
	/** Retrieves a service data parameter of type int32.
		@param dataID is a unique key to identify the data.
		@param outInt32 will be populated with the int32.
		@return kTrue if the data was found; kFalse otherwise.
	*/	
	virtual bool16 Get( int32 dataID, int32 & outInt32 ) const = 0;
	
	/** Retrieves a service data parameter of type void *.
		@param dataID is a unique key to identify the pointer data.
		@return non-nil void * pointer if the data was found; nil otherwise.
	*/	
	virtual void * Get( int32 dataID ) const = 0;
	
	/** Retrieves a service data parameter of type PMString.
		@param dataID is a unique key to identify the data.
		@param outPMString will be populated with the PMString.
		@return kTrue if the data was found; kFalse otherwise.
	*/		
	virtual bool16 Get( int32 dataID, PMString & outPMString ) const = 0;
	
	/** Retrieves a service data parameter of type UIDRef.
		@param dataID is a unique key to identify the data.
		@param outUIDRef will be populated with the UIDRef.
		@return kTrue if the data was found; kFalse otherwise.
	*/		
	virtual bool16 Get( int32 dataID, UIDRef & outUIDRef ) const = 0;
		
	/** Retrieves a service data parameter of type UIFlags.
		@param dataID is a unique key to identify the data.
		@param outUiFlags will be populated with the UIFlags.
		@return kTrue if the data was found; kFalse otherwise.
	*/
	virtual bool16 Get( int32 dataID, UIFlags & outUiFlags ) const = 0;
		
	/** Retrieves a service data parameter of type IAMUIService::FollowupAction.
		@param dataID is a unique key to identify the data.
		@param outAction will be populated with the IAMUIService::FollowupAction.
		@return kTrue if the data was found; kFalse otherwise.
	*/	
	virtual bool16 Get( int32 dataID, IAMUIService::FollowupAction & outAction ) const = 0;
		
	/** Retrieves an IAMService::enTargetAsset service data parameter of type IAMServiceData::UIDRefList.
		@param outUIDRefList will be populated with one or more UIDRefs.
		@return kTrue if the data was found; kFalse otherwise.
	*/		
	virtual bool16 Get( IAMServiceData::UIDRefList & outUIDRefList ) = 0;
	
	/** Retrieves an IAMService::enTargetAsset service data parameter of type IAMServiceData::IDFileList.
		@param outIDFileList will be populated with one or more IDFiles.
		@return kTrue if the data was found; kFalse otherwise.
	*/		
	virtual bool16 Get( IAMServiceData::IDFileList & outIDFileList ) = 0;
	
	/** Retrieves a binary flag value (kTrue or kFalse).
		@param dataID is a unique key to identify the flag.
		@return kTrue if the flag is set; kFalse otherwise.
	*/		
	virtual bool16 GetFlag( int32 dataID ) const = 0;


	/** Sets the value of a service data parameter of type IDFile.
		@param dataID is a unique key to identify the data.
		@param inFile the contents of this are copied and saved.
	*/	
	virtual void Set( int32 dataID, const IDFile & inFile ) = 0;
	
	/** Sets the value of a service data parameter of type int32.
		@param dataID is a unique key to identify the data.
		@param inInt32 the contents of this are copied and saved.
	*/	
	virtual void Set( int32 dataID, int32 inInt32 ) = 0;

	/** Sets the value of a service data parameter of type void *.
		@param dataID is a unique key to identify the pointer.
		@param inInterface the contents of this are copied and saved.
	*/		
	virtual void Set( int32 dataID, void * inInterface ) = 0;
	
	/** Sets the value of a service data parameter of type PMString.
		@param dataID is a unique key to identify the data.
		@param inPMString the contents of this are copied and saved.
	*/	
	virtual void Set( int32 dataID, const PMString & inPMString ) = 0;
	
	/** Sets the value of a service data parameter of type UIDRef.
		@param dataID is a unique key to identify the data.
		@param inUIDRef the contents of this are copied and saved.
	*/	
	virtual void Set( int32 dataID, const UIDRef & inUIDRef ) = 0;
	
	/** Sets the value of a service data parameter of type UIFlags.
		@param dataID is a unique key to identify the data.
		@param inUiFlags the contents of this are copied and saved.
	*/		
	virtual void Set( int32 dataID, UIFlags inUIFlags ) = 0;
	
	/** Sets the value of a service data parameter of type IAMUIService::FollowupAction.
		@param dataID is a unique key to identify the data.
		@param inAction the contents of this are copied and saved.
	*/		
	virtual void Set( int32 dataID, IAMUIService::FollowupAction inAction ) = 0;
	
	/** Sets the value of a service data parameter of type IAMServiceData::UIDRefList. The dataID
		is implicitly IAMService::enTargetAsset.
		@param inUIDRefList the contents of this list are copied and saved.
	*/	
	virtual void Set( const IAMServiceData::UIDRefList & inUIDRefList ) = 0;
	
	/** Sets the value of a service data parameter of type IAMServiceData::IDFileList. The dataID
		is implicitly IAMService::enTargetAsset.
		@param inIDFileList the contents of this list are copied and saved.
	*/		
	virtual void Set( const IAMServiceData::IDFileList & inIDFileList ) = 0;
	
	/** Sets or clears a flag service data parameter.
		@param dataID is a unique key to identify the flag.
		@param b flag value; specify kTrue to set the flag, or kFalse to clear it.
	*/	
	virtual void SetFlag( int32 dataID, bool16 b = kTrue ) = 0;
	
}; // end IAMServiceData interface

#endif // __IAMSERVICEDATA__
