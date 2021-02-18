//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IIDFileData.h $
//  
//  Owner: Michael Easter
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
#ifndef __IIDFileData__
#define __IIDFileData__

// ----- Includes -----
#include "IPMUnknown.h"
#include "CommandID.h"

class IDFile;

/**
 Data interface used for storing a file (IDFile).
*/
class IIDFileData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIDFILEDATA };

	/**
	 Set the file to store.
	 @param file [IN] File to store.
	 */
	virtual void Set(const IDFile& file) = 0;

	/**
	 Return the stored file.
	 @return Reference to the stored file.
	 */
	virtual const IDFile& Get() const = 0;
};



#endif // __IIDFileData__
