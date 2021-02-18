//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IRelinkToFolderOptions.h $
//  
//  Owner: lance bushore
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
#ifndef __IRelinkToFolderOptions__
#define __IRelinkToFolderOptions__

#include "IPMUnknown.h"
#include "ImportExportUIID.h"

/** IRelinkToFolderOptions
	Preferences for the behavior of relink to folder dialog options.
*/
class IRelinkToFolderOptions : public IPMUnknown
{
public:
	/** default IID for this interface */
	enum { kDefaultIID = IID_RELINKTOFOLDEROPTIONS };

	/** When relinking to a folder, set the default for the option which controls relinking
		to same filenames + new extension, or same filenames + same extension
		@param useNewExtension [IN]: kTrue to relink files to a new extension
	*/
	virtual void SetRelinkToNewExtension(bool16 useNewExtension) = 0;

	/** Get whether or not to relink to a new extension
		@return kTrue if relinking to a new extension
	*/
	virtual bool16 GetRelinkToNewExtension() const = 0;

	/** When relinking to a folder, and 'relink to new extension' is selected, this sets the default extension to relink to.
		@param newExtensionStr [IN]: the new default extension to use
	*/
	virtual void SetExtensionForRelink(const PMString& newExtensionStr) = 0;

	/** Get the default extension for relinking to a folder.
		@return string of extension to use.
	*/
	virtual PMString GetExtensionForRelink() const = 0;

};

#endif
