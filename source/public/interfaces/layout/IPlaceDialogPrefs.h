//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPlaceDialogPrefs.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IPlaceDialogPrefs__
#define __IPlaceDialogPrefs__

#include "IPMUnknown.h"
#include "LinksID.h"

/** Interface for remembering the preferences from the Place dialog.
		Used to remember the settings used when an item is placed (and stored on the placed object), so
		that if it needs to be reimported these settings can be reused.
		
		@see IPlaceDialogPrefsCmdData, IImportManagerOptions
*/
class IPlaceDialogPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPLACEDIALOGPREFS };
	/** read/write */
	virtual void ReadWrite(IPMStream* iPMStream, ImplementationID id) = 0;

	/** Get the retain text format flag */
	virtual bool16 GetRetainFormat() = 0;
	/** Get the convert quotation mark types flag */
	virtual bool16 GetConvertQuotes() = 0; 
	/** Set the retain text format flag */
	virtual void SetRetainFormat(bool16 value) = 0;
	/** Set the convert quotation mark types flag */
	virtual void SetConvertQuotes(bool16 value) = 0;
};

#endif // __IPlaceDialogPrefs__
