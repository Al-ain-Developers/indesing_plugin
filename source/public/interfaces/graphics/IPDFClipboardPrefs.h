//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFClipboardPrefs.h $
//  
//  Owner: Greg St. Pierre
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
//  Purpose: Preferences related to clipboard support for PDF format
//  
//========================================================================================

#pragma once
#ifndef __IPDFClipboardPrefs__
#define __IPDFClipboardPrefs__

#include "IPMUnknown.h"

#include "PDFID.h"

/**
 Data interface for storing settings related to clipboard support for PDF
 */
class IPDFClipboardPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFCLIPBOARDPREFS };

	/**
	 Copies specified prefs into this instance
	 
	 @param prefsToCopy		The prefs to copy
	 */
	virtual void CopyPrefs(IPDFClipboardPrefs const *prefsToCopy) = 0;

	/**
	 Returns whether should prefer PDF if multiple usable formats are available
	 (eg. PDF and AICB). Used to break tie if both PDF and AICB are available
	 
	 @return kTrue if should prefer PDF, else kFalse
	 */
	virtual bool16 GetPreferPDFFormat() const = 0;

	/**
	 Sets 'prefer PDF format' preference
	 
	 @param preferPDF		kTrue if PDF should be preferred, else kFalse
	 */
	virtual void SetPreferPDFFormat(bool16 preferPDF) = 0;

	/**
	 Returns whether PDF data should be copied to the clipboard
	 
	 @return kTrue if should copy PDF to the clipboard, else kFalse
	 */
	virtual bool16 GetCopyPDFToClipboard() const = 0;

	/**
	 Sets 'copy PDF to clipboard' preference
	 
	 @param copyPDF			kTrue if PDF should be copied, else kFalse
	 */	 
	virtual void SetCopyPDFToClipboard(bool16 copyPDF) = 0;
	
	/**
	 Returns whether clipboard data should be externalized at quit
	 
	 @return kTrue if should externalize PDF to the clipboard at quit, else kFalse
	 */
	virtual bool16 GetExternalizePDFAtQuit() const = 0;

	/**
	 Set 'externalize at quit' pref

	 @param externalize		kTrue if PDF should be externalized at quit, else kFalse
	 */
	virtual void SetExternalizePDFAtQuit(bool16 externalize) = 0;
};

#endif //!def __IPDFClipboardPrefs__
