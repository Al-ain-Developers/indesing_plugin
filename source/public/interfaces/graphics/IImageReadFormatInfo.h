//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageReadFormatInfo.h $
//  
//  Owner: jargast
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
#ifndef __IImageReadFormatInfo__
#define __IImageReadFormatInfo__

#include "PMTypes.h"
#include "PMFlavorTypes.h"
#include "IPMUnknown.h"
#include "FileTypeList.h"
#include "IDocument.h"

/**
 Interface that provides additional data about the capabilities of an
 IImageReadFormat implementation and that defines a mechanism for passing
 preference information to an IImageReadFormat.
 
 @see IImageReadFormat
 */ 
class IImageReadFormatInfo : public IPMUnknown
{
public:	
	/**
	 Returns list of file types supported by this filter.
	 
	 @param fileTypeList		OUT Pointer to OSTypeList to be filled with supported file types
	 */
	virtual void GetFileTypes(OSTypeList* fileTypeList) = 0;
	
	/**
	 Returns list of file extensions supported by this filter.
	 
	 @param fileTypeList		OUT Pointer to ExtensionList to be filled with supported file extensions
	 */
	virtual void GetExtensions(ExtensionList* extensionList) = 0;
	
	/**
	 Gets the format name for this filter
	 
	 @param formatName			OUT Pointer to PMString to be filled with this filter's format name
	 */
	virtual void GetFormatName(PMString* formatName) = 0;
	
	/**
	 Gets the list of external clipboard flavors supported by this filter.
	 
	 On the Mac, a clipboard flavor/type is equivalent to an OSType.
	 
	 On Windows, to get the clipboard flavor/type you must register the format 
	 name with Windows and it will return the format.
	 
	 @param flavorList			OUT Pointer to ExternalPMFlavorList to be filled with supported clipboard flavors
	 */
	virtual void GetExternalFlavors(ExternalPMFlavorList *flavorList) = 0;

	/**
	 Returns kTrue if the filter can read files with the specified type. Allows 
	 a user to call in with a specific filetype instead of caching the results 
	 of GetFileTypes.
	 
	 @param fileType			IN The file type
	 @return kTrue if the filter can read files of the specified type, else kFalse
	 */
	virtual bool16 CanReadFileType(OSType fileType) = 0;
	
	/**
	 Returns kTrue if the filter can read files with the specified extension. 
	 Allows a user to call in with a specific extension instead of caching the 
	 results of GetExtenions.
	 
	 @param extension			IN The extension
	 @return kTrue if the filter can read files with the specified extension, else kFalse
	 */
	virtual bool16 CanReadExtension(const PMString& extension) = 0;

	/**
	 Returns kTrue if the filter can read the specified external clipboard 
	 flavor. Allows a user to call in with a specific clipboard format instead
	 of caching the results of GetExternalFlavors.
	 
	 @param flavor				IN The external clipboard flavor
	 @return kTrue if the filter can read the specified clipboard flavor, else kFalse
	 */
	virtual bool16 CanReadFlavor(ExternalPMFlavor flavor) = 0;
	
	/**
	 Copies the current preferences for the filter to the specified target.
	 This is called by the place provider after the UI for the filter has been 
	 displayed (if any) and before reading any data. This allows the filter to 
	 store the current settings with the page item. If the filter wishes, it 
	 can store the settings with the Session at this time as well to make the 
	 current settings global. 
	 
	 Note: This method is called after GetPreferencesPanel() or PassPreferences().
	 
	 @param targetDB		IN The database for the target pageitem
	 @param targetUID		IN The UID for the target pageitem
	 */
	virtual void CopyPreferencesToTarget(IDataBase *targetDB, UID targetUID) = 0;

	/**
	 Returns the WidgetID of the panel to add to the Import Preferences dialog,
	 if any.
	 
	 The filter is responsible for setting the panel's parent to 'ImageImportUI'
	 via the IDListPair resource definition of the panel and for setting the 
	 'Visible' field of the panel's resource definition to kFalse.
	 
	 At import time, the image place provider will ask the filter for its 
	 preference panel's WidgetID. If not kInvalidWidgetID, the provider will 
	 use the WidgetID to query for the panel's IID_IUIDDATA and use it to set 
	 the source UID to be used to initialize the panel. Afterwards, the 
	 provider will show the panel, allowing the IntializeFields() method of the
	 panel's IDialogController to be called.
	 
	 @return The WidgetID of the filter's preferences panel, or kInvalidWidgetID if it does not have one
	 */
	virtual WidgetID GetPreferencesPanel() = 0;
		
	/**
	 Passes the preferences stored on the specified page item to the filter
	 prior to a call to the IImageReadFormat's Open method. This allows a user 
	 to pass a set of preferences into the filter without any UI. 
	 
	 The sourceDB and the sourceUID represent the image item (or Session 
	 Workspace) whose preferences we would like to use.
	 
	 @param sourceDB		IN The database for the source pageitem or workspace
	 @param sourceUID		IN The UID for the source pageitem or workspace
	 */
	virtual void PassPreferences(IDataBase *sourceDB, UID sourceUID) = 0;
};


#endif
