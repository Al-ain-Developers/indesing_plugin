//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPlaceDialogPrefsCmdData.h $
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
#ifndef __IPlaceDialogPrefsCmdData__
#define __IPlaceDialogPrefsCmdData__

#include "IPMUnknown.h"

/** Interface for the command data for the Place dialog command.
		
		@see IPlaceDialogPrefs, IImportManagerOptions
*/
class IPlaceDialogPrefsCmdData : public IPMUnknown
{
public:
	/** Initialize the data

		@param db IN database accepting the place
		@param pageItem IN the pageitem to place
		@param retainFormat IN retain text format, applies to text import
		@param convertQuotes IN convert quotation mark types, applies to text import
	*/
	virtual void Set(IDataBase *db, UID pageItem, bool16 retainFormat, bool16 convertQuotes) = 0;
	
	/** Get the target database */
	virtual IDataBase *GetDataBase() = 0;
	/** Get the pageitem to place */
	virtual UID GetPageItem() = 0;
	/** Get the retain text format flag */
	virtual bool16 GetRetainFormat() = 0;
	/** Get the convert quotation mark types flag */
	virtual bool16 GetConvertQuotes() = 0;
};

#endif
