//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/sound/SoundListElement.h $
//  
//  Owner: Tim Wright
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
#ifndef __SoundListElement_h__
#define __SoundListElement_h__

#include "UIDRef.h"

//========================================================================================
// CLASS SoundListElement
//========================================================================================

class SoundListElement
{
public:
	typedef object_type data_type;

	SoundListElement(const UIDRef& sound) :
		fSound(sound)
	{
	}
	
	SoundListElement(const SoundListElement& other) :
		fSound(other.fSound)
	{
	}
	
	SoundListElement& operator=(const SoundListElement& other)
	{
		if (this != &other)
			fSound = other.fSound;
		
		return *this;
	}

	UIDRef GetSoundRef() const
	{
		return fSound;
	}
	
public:
	UIDRef		fSound;
};

#endif // __SoundListElement_h__
