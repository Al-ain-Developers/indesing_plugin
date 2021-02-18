//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IFileNameWidgetController.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IFileNameWidgetController__
#define __IFileNameWidgetController__

#include "IPMUnknown.h"
#include "XMediaUIID.h"

class IDocument;
//----------------------------------------------------------------------------------------
// IFileNameWidgetController
//----------------------------------------------------------------------------------------

/** Interface that provides methods needed for the
	fileNameWidget to function properly
*/
class IFileNameWidgetController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFILENAMEWIDGETCONTROLLER };

	/** Use this method to set the Controller in the interface
		@param widgetName - The anem that should be displayed by the checkbox
		@param fileName - The filename that the widget points to
		@param enabled - Whether this widget should be enabled
		@param selected - Whether this widget should be selected (turned on)
		@param defaultText - The text to display when there is no valid filename
		@param validExt - The extensions that are valid when browsing for files
	*/
	virtual void Set(const PMString &widgetName, const IDFile &fileName, bool16 enabled, bool16 selected, const PMString &defaultText, const PMString &validFileType, const K2Vector<PMString> &validExt) = 0;

	/** Use this to set the file name the widget should point to. The name must either point
		to a file that exists or be an uninitialized IDFile. Any other case will not change
		the data and will return an error.
		@param newName - The name to use
		@return - kSuccess if name was valid and could be changed : kFailure if name was invalid
	*/
	virtual ErrorCode SetFileName(const IDFile &newName) = 0;

	/** Use this to get the file name the widget should point to
		@return - The name to use
	*/
	virtual IDFile GetFileName() const = 0;

	/** Use this to enable the edit box and browse button */
	virtual void Enable() = 0;

	/** Use this to disable the edit box and browse button */
	virtual void Disable() = 0;

	/** Use this to find out if the widget should be enabled or not
		@return - kTrue:Enabled/kFalse:Disabled
	*/
	virtual bool16 GetEnabledState() const = 0;

	/** Use this to get the filetype information
		@param fileName - The to display for this file type
		@param extension - The extension this file should have
	*/
	virtual void GetFileTypeInfo(PMString &fileName, K2Vector<PMString> &extensions) const = 0;
};	

#endif // __IXMLImportOptionsDialog__
