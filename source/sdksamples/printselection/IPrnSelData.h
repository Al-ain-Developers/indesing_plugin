//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/IPrnSelData.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __IPrnSelData_h__
#define __IPrnSelData_h__

// Interface includes:
#include "IPMUnknown.h"
#include "IDocument.h"

// General includes:

// Project includes:
#include "PrnSelID.h"

/** From SDK sample;  stores data relative to printing only selected items.
  
	
	@ingroup printselection
*/
class IPrnSelData : public IPMUnknown
{
public:

	enum {kDefaultIID = IID_IPRNSELDATA};

	/** Sets whether print selection checkbox was checked.
		@param	bchecked [in] specifies whether print selection checkbox was checked.
	*/
	virtual void SetIsChecked(bool16 bchecked) = 0;
	
	/** Retrieves whether print selection checkbox was checked.
		@return	Returns whether print selection checkbox was checked.
	*/
	virtual bool16 GetIsChecked() = 0;
	
	/** Sets whether should suppress print selection dialog. Used by scripting.
		@param bSuppress Specifies whether should suppress print selection dialog.
	*/
	virtual void SetSuppressPrintSelectionDialog(bool16 bSuppress)= 0;

	/** Retrieves whether should suppress print selection dialog.
		@return	Returns whether should suppress print selection dialog.
	*/
	virtual bool16 GetSuppressPrintSelectionDialog() = 0;

	/** Retrieves whether a page contained a selected item.
		@param	pageuid [in] specifies page uid being queried.
		@return	Returns whether specified page UID represents a page containing a selected item.
	*/
	virtual bool16 GetPageUIDHadSelection(UID pageuid) = 0;

	/** Loads page UID into custom data structure.
		@param	pageuid [in] specifies page UID being loaded.
	*/
	virtual void LoadPageUID(UID pageuid) = 0;
	
	/** Retrieves whether a specified UID represents a selected item.
		@param	uid [in] specifies uid being queried.
		@return	Returns whether specified UID represents a selected item.
	*/
	virtual bool16 GetPageItemUIDHadSelection(UID uid) = 0;

	/** Loads page item UID into a custom data structure.
		@param	uid [in] specifies uid being loaded.
	*/
	virtual void LoadPageItemUID(UID uid) = 0;

	/** Empties custom data structures.
	*/
	virtual void FlushUIDs() = 0;
};

#endif // __IPrnSelData_h__

// End, IPrnSelData.h.