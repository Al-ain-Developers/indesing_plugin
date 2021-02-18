//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMLockFileData.h $
//  
//  Owner: Gang Xiao
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
#ifndef __IPMLockFileData_h__
#define __IPMLockFileData_h__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"

class IPMLockFile;

//========================================================================================
// INTERFACE ILockFileData
//========================================================================================

/**
 Container interface used to hold a document lock file.
 @see IPMLockFile
 */
class IPMLockFileData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPMLOCKFILEDATA };

	/**
	 Sets the document lock file.
	 @param thePMLockFile	IN Pointer to the document lock file.
	 */
	virtual void SetPMLockFile(IPMLockFile* thePMLockFile) = 0;

	/**
	 Returns the document lock file.
	 @return Pointer to the document lock file.
	 */
	virtual IPMLockFile* GetPMLockFile()  const = 0;
};

#endif // __ILockFile_h__
