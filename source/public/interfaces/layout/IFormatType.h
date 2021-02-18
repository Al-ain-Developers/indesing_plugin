//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFormatType.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IFormatType__
#define __IFormatType__

// IID_IFORMATTYPE interface.

/** Used to indicate the format of a given file */
class IFormatType : public IPMUnknown
{
public:
	/** Use this method to persist the data in this class to a stream or get the data
		out of a stream
		@param *iPMStream - The stream containing or receiving the data
		@param id - Implementation ID
	*/
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;

	/** Use this to setup the format type information for this class
		@param type - the filetype
		@param creator - The creator
		@param basename - The shortname that identifies the file
	*/
	virtual void SetFormatType(SysOSType type, SysOSType creator, PMString &basename) = 0;

	/** Use to get the type of this file
		@return - The type of the object
	*/
	virtual SysOSType GetSysOSType() = 0;

	/** Use to get the creator of this file
		@return - The creator of the object
	*/
	virtual SysOSType GetSysOSCreator() = 0;

	/** Use to get the extension of this file
		@param extension - [OUT] The file extension
	*/
	virtual void GetExtension(PMString &extension) = 0;

	/** Use to get the basename of this file
		@param basename - [OUT] The file name
	*/
	virtual void GetBaseName(PMString &basename) = 0;
};

#endif // __IFormatType__