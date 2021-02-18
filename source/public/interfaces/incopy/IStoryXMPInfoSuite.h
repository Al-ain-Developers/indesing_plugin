//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryXMPInfoSuite.h $
//  
//  Owner: ???
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
#ifndef __IStoryXMPInfoSuite__
#define __IStoryXMPInfoSuite__

#include "IPMUnknown.h"
#include "InCopyCoreUIID.h"
#include "ISelectionManager.h"

/** InCopy only. Suite interface to get XMP data of the InCopy story file
*/
class IStoryXMPInfoSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTORYXMPINFOSUITE };


/**	Can get the XMP information
	@param none
	@return bool16 
 */
	virtual bool16 CanStoryXMPInfo() const = 0;

/**	Access the story information XMP dialog
	@param none
 */
	virtual void DoStoryXMPInfo() = 0;
};

#endif // _IStoryXMPInfoSuite_
