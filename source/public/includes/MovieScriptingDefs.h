//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MovieScriptingDefs.h $
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
#ifndef __MOVIESCRIPTINGDEFS__
#define __MOVIESCRIPTINGDEFS__

#include "MediaScriptingDefs.h"

// ------------------------------------------------------------------

//
// Please make sure any id's you add are unique !!!
//

enum MovieItemDefs 
{
	//These are used for inheritance in the AETE
	MovieItemProperties =	'MPrp',

	c_Movie							= 'Movi',	// cRectangle in AERegistry.h
	c_Movies						= 'Mvis',
	c_NavigationPoint				= 'nvpt',
	c_NavigationPoints				= 'nvps',
	
	// enumerated types

	en_MoviePlayMode				= 'Mplm',
	en_MovieOnce					= 'Sone',
	en_MovieOpen					= 'Mopn',
	en_MovieRepeat					= 'Srep',

	en_MovieFloatingWindowSize		= 'Mfws',
	en_MovieOneFifth				= 'Mfif',
	en_MovieOneFourth				= 'Mfor',
	en_MovieOneHalf					= 'Mhal',
	en_MovieFull					= 'Mful',
	en_MovieDouble					= 'Mtox',
	en_MovieTriple					= 'Mtrx',
	en_MovieQuadruple				= 'Mqux',
	en_MovieMax						= 'Mmax',

	en_MovieFloatingWindowPosition	= 'Mfwp', // needed for Mac Scripting
	en_MovieUpperLeft				= en_UpperLeft,
	en_MovieUpperMiddle				= 'Mumd',
	en_MovieUpperRight				= 'Murt',
	en_MovieCenterLeft				= 'Mclf',
	en_MovieCenter					= 'Mcen',
	en_MovieCenterRight				= 'Mcrt',
	en_MovieLowerLeft				= 'Mllf',
	en_MovieLowerMiddle				= 'Mlmd',
	en_MovieLowerRight				= 'Mlrt',

	en_MoviePosterType				= 'Mmpt',

	// properties

	p_MovieFloatingWindowPosition	= 'Mwpt',
	p_MovieFloatingWindowSize		= 'Mwsz',
	p_MovieHasFloatingWindow		= 'Mhfw',
	p_MoviePlayMode					= 'Mmod',
	p_MovieShowController			= 'Msho',
	p_MoviePosterType				= 'Mpty', // added [Vantive 616739]
	p_NavigationPointIdentifier		= p_ID,
	p_NavigationPointDisplayName	= p_Name,
	p_NavigationPointTime			= 'Nvpt',
	p_MovieControllerSkin			= 'Mskn',
	p_MovieShowControllerOnRollover = 'Mscr',
	p_MovieLoop						= 'Mlpf',
	
	// events

	e_VerifyURL						= 'Sepo',
	
	// hidden properties for save backwards
	
	p_CustomPoster					= 'Mcsp',
	p_IntrinsicBounds				= 'Mibd',
	p_PosterIsAvailable				= 'Mpia',
	p_CanChoosePosters				= 'Mccp'

};

#endif	//#ifndef __MOVIESCRIPTINGDEFS__
