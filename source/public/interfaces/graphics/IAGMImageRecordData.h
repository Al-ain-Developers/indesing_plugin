//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAGMImageRecordData.h $
//  
//  Owner: jargast
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
#ifndef __IAGMImageRecordData__
#define __IAGMImageRecordData__

#include "IPMUnknown.h"
#include "GraphicsID.h"
#include "BravoForwardDecl.h"

/**
 Simple data interface for storing an AGMImageRecord.
 */
class IAGMImageRecordData : public IPMUnknown
{
public:
	/**
	 Sets the image record. This interface makes a copy of the image record 
	 data. The caller is still responsible for destroying the data pointed to 
	 by base addr. If not enough memory then Set will return an error.
	 
	 @param agmImageRecord		IN The image record to store
	 @return kSuccess if successful, else an error code
	 */
	virtual ErrorCode Set (const _t_AGMImageRecord& agmImageRecord) = 0;
	
	/**
	 Retrieves the stored AGMImageRecord. This interface owns the pointer that 
	 base addr points to. The caller must not delete the pointer. Further, the 
	 caller must guarantee this interface is instantiated during the use of the 
	 AGMImageRecord.
	 
	 @param agmImageRecord		OUT Pointer to storage for the image record to retrieve
	 */
	virtual void Get (_t_AGMImageRecord* agmImageRecord) const = 0;
	
};

#endif // __IAGMImageRecordData__