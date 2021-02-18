//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageNumberPrefsCmdData.h $
//  
//  Owner: Paul Sorrick
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
//  Data interface for Page Number prefs command.
//  includes : 	Page numbers display in ordinal or section format.
//  
//========================================================================================

#pragma once
#ifndef __IPageNumberPrefsCmdData__
#define __IPageNumberPrefsCmdData__

#include "IPMUnknown.h"

/** Command data interface for the page number prefs command to set the session preference relating how UI widgets display page numbers. 
	This is a UI-only setting that doesn't affect how page number characters in text stories are computed/displayed.
	@see kWorkspaceBoss
    @see kSetPageNumberPrefsCmdCmdBoss
	@see IPageNumberPrefs.h
*/
class IPageNumberPrefsCmdData : public IPMUnknown
{
public:

	/**	Set the data member for ordinal numbering (kTrue) or standard/section numbering (kFalse) to use
		used for page number and page number range widget display. The UI control for this setting is
		in the general preferences dialog for InDesign.
		@param const bool16 ordinalOn kTrue for ordinal, kFalse for standard/section numbering (the default).
	 */
	virtual void Set( const bool16 ordinalOn) = 0;

	/**	Return the data member for ordinal numbering (kTrue) or standard/section numbering (kFalse) 
		@param none
		@return const bool16 the page numbering value
	 */
	virtual const bool16 GetOrdinalNumbering() const = 0;
};

#endif // __IPageNumberPrefsCmdData__
