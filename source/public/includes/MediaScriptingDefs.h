//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MediaScriptingDefs.h $
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
#ifndef __MEDIASCRIPTINGDEFS__
#define __MEDIASCRIPTINGDEFS__

#include "ScriptingDefs.h"
#include "BehaviorID.h"

// ------------------------------------------------------------------

//
// Please make sure any id's you add are unique !!!
//

enum MediaDefs 
{
	en_PosterOption					= 'Mpos',
	en_NoPoster						= en_None,
	en_StandardPoster				= en_Standard,

	en_ProxyImage					= 'Mpxy',
	en_FromMedia					= 'Mfmf',

	p_DoNotPrintPoster				= 'Sprn',
	p_EmbedContentInPDF				= 'Semb',
	p_PlayOnPageTurn				= 'Mplo',
	p_PosterFile					= 'Sspf'
//	p_PosterOption					= 'Spop', removed [Vantive 616739]
//	p_PosterType					= 'Spty'  removed [Vantive 616739]	
};

#endif	// __MEDIASCRIPTINGDEFS__

