//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintCopyCustomDataProvider.h $
//  
//  Owner: David Berggren
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
//  
//  Purpose:
//  Provider interface for allowing third parties a chance to copy their own print
//  settings, if desired. The providers will be called every time IPrintData::CopyData
//  is called, after the CopyData has already taken place.
//  
//========================================================================================

#pragma once
#ifndef __IPrintCopyCustomDataProvider__
#define __IPrintCopyCustomDataProvider__

#include "PrintID.h"
#include "IPMUnknown.h"

class IPrintData;

/**
	Provider interface for allowing third parties a chance to copy their own print
	setting, if desired. The providers will be called every time IPrintData::CopyData
	is called, after the CopyData has already taken place.
*/
class IPrintCopyCustomDataProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRINTCOPYCUSTOMDATAPROVIDER };

	/**
	 Called from IPrintData::CopyData(), after the copy has been done.
	 @param srcPrintData	IN the IPrintData interface being copied from.
	 @param dstPrintData	IN the IPrintData interface being copied to.
	 */
	virtual void CopyData (
			const IPrintData*	srcPrintData,
			IPrintData*			dstPrintData
			) = 0;
};

#endif
