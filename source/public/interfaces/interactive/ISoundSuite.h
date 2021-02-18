//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISoundSuite.h $
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
//  
//  Comments:	Selection suite for Sound page items
//  
//========================================================================================

#pragma once
#ifndef _ISoundSuite_
#define _ISoundSuite_

#include "SoundID.h"


/** Selection suite for manipulating Sound page items and attributes.
	
*/

class ISoundSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISOUNDSUITE };

	/** Obtains an existing empty frame that can be converted into a sound frame.
		@precondition A single empty frame must be selected; multiple selections are
					  not supported.
		@return UIDRef to a single empty frame.
	*/
	virtual UIDRef GetEmptyFrameRef() const = 0;

	/** Obtains the UIDRef of a single selected sond page item.
		@precondition A single sound page item must be selected; multiple selections are
					  not supported.
		@return UIDRef to a single sound page item.
	*/
	virtual UIDRef GetSelectedSoundRef() const = 0;

	/** Tests the current selection for Sound page items
		@return kTrue if selection is all Sound page items (or default selection)
	*/
	virtual bool16 IsSoundSelection() const = 0;
	
	/** Tests if the selection can be converted into a Sound page item.
		@return kTrue if the selection can be converted into a Sound page item.
	*/
	virtual bool16 CanConvertToSound() const = 0; 
};


#endif // _ISoundSuite_