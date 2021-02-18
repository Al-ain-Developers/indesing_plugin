//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFileStreamData.h $
//  
//  Owner: robin briggs
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
#ifndef __IFileStreamData__
#define __IFileStreamData__

#include "ShuksanID.h"

/**
 Container interface used to hold information about a file accessed via a file stream. 
 @see IDFile
 */
class IFileStreamData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFILESTREAMDATA };
	
		/**
		Sets information about the file accessed via the stream.
		@param sysFile	IN File accessed via the stream.
		@param mode	IN File mode used by the stream when opening the given file.
		@param fileType	IN File type of the given file.
		@param creator	IN Creator of the given file.
		*/
		virtual void Set(const IDFile& sysFile, uint32 mode, OSType fileType = 0x3f3f3f3f, OSType creator = 0x3f3f3f3f) = 0;

		/**
		Returns the file accessed via the stream.
		@return Reference to the file accessed via the stream.
		*/
		virtual const IDFile& GetSysFile() const = 0;

		/**
		Returns the file mode used by the stream when opening the file.
		@return File mode used by the stream when opening the file.
		*/
		virtual uint32 GetMode() const = 0;

		/**
		Returns the file type of the file accessed via the stream.
		@return File type of the file accessed via the stream.
		*/
		virtual OSType GetFileType() const = 0;

		/**
		Returns the creator of the file accessed via the stream.
		@return Creator of the file accessed via the stream.
		*/
		virtual OSType GetCreator() const = 0;
};


#endif // __IPointerStreamData__
