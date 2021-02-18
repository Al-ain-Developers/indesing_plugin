//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StyleClashResolutionTypes.h $
//  
//  Owner: Jagadish Y
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
	#ifndef _StyleClashResolutionTypes_
	#define _StyleClashResolutionTypes_
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION (pseudo namespace)
//________________________________________________________________________________________
class StyleClashResolutionTypes
{
public:
	/**
		The choices for global clash resolution strategies (for style clash cases)
	*/
	enum GlobalClashResolutionStrategy
	{
		/** Overwrite the existing style with Incoming style */
		kLoadAllWithOverwrite = 0,

		/** Do not load the Incoming style (existing style is not effected) */
		kDecline,

		/** Import the Incoming style by renaming (existing style is not effected) */
		kLoadAllWithRename,

		/** Each style has different choice. This choice is available with UI (currently not available through scripting) */
		kLoadSelectively
	};

	/**
		This is used only when global clash resolution strategy is kLoadSelectively
		The choices for individual styles clash-resolution-strategy (whenever style clashes)
	*/
	enum StyleClashResolutionStrategy
	{
		/** Import the Incoming style by renaming (existing style is not effected) */
		kAutoRename = 0,

		/** Overwrite the existing style with Incoming style */
		kUseIncomingStyleDefinition,

		/** Only Auto rename is allowed, since style is conflicting with style sets */
		kAutoRenameOnly
	};

	/**
		The choices for matching strategy used to find the clashing styles in target document.
		Used for book synchronization. 
		@see IStyleSyncService.h
	*/
	enum StyleMatchingStrategyEnum
    {
		/** Matches only leaf styles names at any location, this is the default value  */
        kMatchStyleName = 0,

		/** Matches Full path of styles */
        kMatchStyleFullPath  
	};
};
	
#endif // _StyleClashResolutionEnums_
