//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyImportSupport.h $
//  
//  Owner: craig rainwater
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
#ifndef __IInCopyImportSupport__
#define __IInCopyImportSupport__

#include "IPMUnknown.h"
#include "IXMLOutStream.h"

#include "InCopyWorkflowID.h"


/**------------------------------------------------------------------------------------------------
//	Class IInCopyImportSupport
//
//	The IInCopyImportSupport interface provides alternate methods to match style/swatch names that
//	are encountered in the InCopy story but not found in the style/swatch lists.
//
//	Third-parties may provide an implementation for this interface and use it along with the
//	IInCopyImportOptions to control how various InCopy file data are imported.
//
//	In normal operation, InCopy import will try to match a swatch name or style name used in a 
//	story with one that exists in current style list/swatch table.  If there is no match, the
//	user will be presented with a dialog allowing them to assign a new style/swatch to the missing
//	name.  If there the user does not reassign a missing style/swatch, the default will be used.
//
//	Using the IInCopyImportSupport interface third-party develepers can provide an alternate
//	method for finding a style/swatch match.  If a valid IInCopyImportSupport* is provided
//	to the IInCopyImportOptions, when a missing style/swatch is encountered, the 
//	IInCopyImportSupport->FindSwatchByName() or IInCopyImportSupport->FindStyleByName() will be
//	called.  If a valid UID is returned (!= kInvalidUID), that UID will be used to mapped the
//	swatch/style name.
//
//------------------------------------------------------------------------------------------------
*/
class IInCopyImportSupport : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINCOPYIMPORTSUPPORT };

		/**	Returns a valid swatch UID by given param swatchName or kInvalidUID
			@param db The database to search the swatch
			@param swatchName The swatch name
			@return UID 
		*/
		virtual	UID FindSwatchByName(
			IDataBase* db,
			const PMString& swatchName
			) const = 0;

		/**	Returns a valid style UID by given param styleName or kInvalidUID
			@param db The database to search the style
			@param styleName The style name
			@return UID 
		*/
		virtual UID FindStyleByName(
			IDataBase* db,
			const PMString& styleName
			) const = 0;
};
#endif // __IInCopyImportSupport__