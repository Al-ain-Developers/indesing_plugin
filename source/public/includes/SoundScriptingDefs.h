//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SoundScriptingDefs.h $
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
#ifndef __SOUNDSCRIPTINGDEFS__
#define __SOUNDSCRIPTINGDEFS__

#include "MediaScriptingDefs.h"


// ------------------------------------------------------------------

//
// Please make sure any id's you add are unique !!!
//

enum SoundDefs 
{
	//These are used for inheritance in the AETE
	SoundItemProperties =		'SPrp',

	c_Sound 						= 'Sndi',	// cRectangle in AERegistry.h
 	c_Sounds						= 'Snds',
 	
 	en_SoundPosterType				= 'Smpt',
 	p_SoundPosterType				= 'Spty',	// WHT: added 7/14/2003 [Vantive 616739]
 	p_SoundStopOnPageTurn			= 'Sopt',
 	p_SoundLoopForever				= 'Slpf'
};

#endif	//#ifndef __SOUNDSCRIPTINGDEFS__

