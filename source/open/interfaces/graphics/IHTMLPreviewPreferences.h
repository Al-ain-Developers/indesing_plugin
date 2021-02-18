//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/graphics/IHTMLPreviewPreferences.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IHTMLPreviewPreferences__
#define __IHTMLPreviewPreferences__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"

class IHTMLPreviewPreferences : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IHTMLPREVIEWPREFERENCES };
	typedef enum 
	{ 
		kShowDevices = 0, 
		kShowDesktop
	} HTMLPreviewMode;

	/** Set the view to display either two fixed sized devices or fill the window as if it were a desktop browser.
		@param previewMode [IN] The view mode
	 */
	virtual void SetPreviewMode(IHTMLPreviewPreferences::HTMLPreviewMode const previewMode) = 0;

	/** Get the current view mode
	 @param previewMode [IN] The view mode
	 */
	virtual HTMLPreviewMode  GetPreviewMode( ) const = 0;
	
	/** Copy all options from the provided IHTMLPreviewPreferences instance
	 */
	virtual void Copy(IHTMLPreviewPreferences const *fromPrefs) = 0;
	
	/** [INTERNAL] Set the device options, as an XML string
	 @param options [IN] A collection of device options formatted as XML
	 */
	virtual void SetDeviceOptions(const PMString &options) = 0;
	
	/** [INTERNAL] Get the device options as an XML string
	 return an XML representation of the device options
	 */
	virtual const PMString& GetDeviceOptions( ) const = 0;
};

#endif
