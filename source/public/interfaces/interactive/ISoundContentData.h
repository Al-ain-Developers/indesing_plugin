//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISoundContentData.h $
//  
//  Owner: wtislar
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
#ifndef __ISoundContentData__
#define __ISoundContentData__

#include "SoundID.h"



/**
	This interface provides methods for accessing sound page item attributes.
*/

class ISoundContentData
{
public:

	/** this enum defines the sound sample data formats */
	enum SampleDataFormat
	{ 
		enRawData 	= 0,
		enSignedData 	= 1,
		enMuLawData 	= 2,
		enALawData 	= 3
	};

	/** this enum defines the IDs of all attributes specific to sound media content.
	*/
	enum SoundContentDataID
	{
		/** The sound sample rate in samples per second. */
		enSampleRate				= kSoundPrefix + 0,	// int32; unit: Hz; CONTENT DATA
		/** The number of sound channels (1: Mono, 2: Stereo). */
		enNumberOfSoundChannels		= kSoundPrefix + 1,	// int16; CONTENT DATA
		/** The number of bits per sound sample per channel. */
		enBitsPerSample				= kSoundPrefix + 2,	// int16 CONTENT DATA
		/** The sound SampleDataFormat */
		enFormatOfSampleData		= kSoundPrefix + 3,	// int16 CONTENT DATA
		/** The name for the sound compression format. */
		enFormatOfCompression		= kSoundPrefix + 4,	// PMString CONTENT DATA
		/** The sound playback volume. */
		enVolume					= kSoundPrefix + 5,	// PMReal CONTENT DATA

		/** Plays the sound synchronously if set */
		enSynchronous				= kSoundPrefix + 6,	// flag CONTENT DATA
		/** Repeats play if set */
		enRepeat					= kSoundPrefix + 7,	// flag CONTENT DATA
		/** Mix play if set */
		enMix						= kSoundPrefix + 8	// flag CONTENT DATA
	};



}; // end ISoundContentData interface

#endif // __ISoundContentData__
