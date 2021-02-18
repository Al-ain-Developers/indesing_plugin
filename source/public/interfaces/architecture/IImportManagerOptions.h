//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportManagerOptions.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IImportManagerOptions__
#define __IImportManagerOptions__

#include "IPMUnknown.h"

/** Interface used to retrieve import options from the import/place dialog.

		@see IPlaceDialogPrefs, IPlaceDialogPrefsCmdData, IPlaceOptions
*/
class IImportManagerOptions : public IPMUnknown
{
	public:
		/** Initialize the data

			@param showFilterPrefs IN should the filter prefs dialog be shown
			@param retainFormat IN retain text format, applies to text import
			@param convertQuotes IN convert quotation mark types, applies to text import
		*/
		virtual void Set(bool16 showFilterPrefs, bool16 retainFormat, bool16 convertQuotes) = 0;

		/** Get the show filter prefs dialog flag */
		virtual bool16 GetShowFilterPrefs() const = 0;
		/** Get the retain text format flag */
		virtual bool16 GetRetainFormat() const = 0;
		/** Get the convert quotation mark types flag */
		virtual bool16 GetConvertQuotes() const = 0;
		
		/** Set the replace selected item flag
			@param replace IN should import replace the selected item
		*/
		virtual void SetReplaceSelectedItem(bool16 replace) = 0;
		/** Get the replace selected item flag */
		virtual bool16 GetReplaceSelectedItem() const = 0;
		/** Enable/Disable the "replace selected item" control */
		virtual void EnableReplaceSelectedItem(bool16 replaceEnable) = 0;
		/** Is the "replace selected item" control enabled */
		virtual bool16 IsReplaceSelectedItemEnabled() const = 0;
		
		/** Set the CJK grid options flag
			@param apply IN apply CJK grid if present, applies to text import
		*/
		virtual void SetApplyCJKGrid(bool16 apply) = 0;
		/** Get the CJK grid options flag */
		virtual bool16 GetApplyCJKGrid() const = 0;

		/** Set the show preview flag
			@param yesNo IN
		*/
		virtual void SetShowPreview(bool16 yesNo) = 0;
		/** Get the show preview flag */
		virtual bool16 GetShowPreview(void) const = 0;

		/** Set the 'search for missing' flag used by the Relink dialog
			@param yesNo IN
		*/
		virtual void SetSearchForMissing(bool16 yesNo) = 0;
		
		/** Get the 'search for missing' flag, used by the Relink dialog */
		virtual bool16 GetSearchForMissing() const = 0;
		
		/** Set "generate captions" flag */
		virtual void SetGenerateCaptions(bool16 replace) = 0;
		/** Get the "generate captions" flag */
		virtual bool16 GetGenerateCaptions() const = 0;

		/** Set the create link flag
			@param create IN should import create a link
		*/
		virtual void SetCreateLink(bool16 create) = 0;
		/** Get the create link flag */
		virtual bool16 GetCreateLink() const = 0;
		/** Enable/Disable the "create link" control */
		virtual void EnableCreateLink(bool16 enable) = 0;
		/** Is the "create link" control enabled */
		virtual bool16 IsCreateLinkEnabled() const = 0;
};

#endif

