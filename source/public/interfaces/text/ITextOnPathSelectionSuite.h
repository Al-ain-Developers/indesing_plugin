//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextOnPathSelectionSuite.h $
//  
//  Owner: Bryce Morsello
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
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _ITOPSelectionSuite_
	#define _ITOPSelectionSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "TOPOptionsType.h"

	#include "TextOnPathID.h"

//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________

/**
	Provides access through a selection to the Text on a Path settings
	@ingroup text_suite
	@ingroup text_onpath
	@author Bryce Morsello
*/
class ITextOnPathSelectionSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ITEXTONPATHSELECTIONSUITE };

		/**	Retrieves the configured Text on Path parameters for the object(s) in a given selection
			@param typeEffect IN the algorithm used to place glyphs on a spline, from TOPOptionsType.h
			@param textAlign IN the line on the glyph to which the characters are aligned
			@param pathAlign IN the top, center, or bottom edge of the spline to which to align the characters
			@param overlapOffset IN the distance, in points, by which a ghost spline is projected from the actual spline for the purpose of changing the spacing
			@param flip IN whether the characters are placed upside-down and backwards along the spline: constants in TOPOptionsData.h
			@param verticality -1 for a mixed selection, 1 for vertical, 0 for horizontal only
		*/
		virtual void SetOptionValues(	EffectType typeEffect,	TextAlignType textAlign,PathAlignType pathAlign, int16 overlapOffset, int16 flip) = 0;
		virtual void GetOptionValues (EffectType &typeEffect,	TextAlignType &textAlign,PathAlignType &pathAlign, int16 &overlapOffset, int16 &flip, int16 &verticality) = 0;

		/** Identifies whether the Text on Path can be configured
			@return kTrue if SetOptionValues can be executed
		*/
		virtual bool16 CanModifyTextOnPathOptions() const = 0;

		/** Identifies whether all Text on Path can be removed from all objects in the selection
			@return kTrue if all objects can have Text on Path removed from them
		*/
		virtual bool16 CanDeleteTextOnPath() const = 0;

		/** Remove Text on Path from all objects in the selection
		*/
		virtual ErrorCode DeleteTextOnPath() = 0;

		//_____________________________
		/**  FreezeSelectionForModalDialog is used to freeze the selection when a modal dialog is about to be invoked.
		This allows the modal dialog to operate on the same items regardless of how the changes affect the selection over time.
		(For example, if you have a caret and increase the columns, such that the caret moves to the next frame, the dialog will still
		operate on the original text frame).
		THIS CALL MUST BE PAIRED WITH A CALL TO ThawSelectionForModalDialog()
		*/
		virtual void	FreezeSelectionForModalDialog() = 0;

		/**  ThawSelectionForModalDialog is used to thaw the selection when a modal dialog has been closed.
		see FreezeSelectionForModalDialog for more details.
		THIS CALL MUST BE PAIRED WITH A CALL TO FreezeSelectionForModalDialog()
		*/
		virtual void	ThawSelectionForModalDialog() = 0;
	//	Member functions
	//____________________________________________________________________________________________
	public:
	};

#endif // _ITextMiscellanySuite_

