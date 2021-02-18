//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IUIDListControlData.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IUIDListControlData_h__
#define __IUIDListControlData_h__

#include "IPMUnknown.h"
#include "widgetid.h"

const int32 kUIDListControlDataDefaultChunkSize = 8;

//========================================================================================
// CLASS IUIDListControlData
/** Control Data Interface for a list of UIDs, currently part of the kPagesPanelWidgetBoss.
*/
//========================================================================================

class IUIDListControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIDLISTCONTROLDATA };
	
	// ----- Constants -----
	/** @name list position constants */
	enum {
		/** at the beginning of the list */
		kBeginning___ = 0, 
		/** at the end of the list */
		kEnd___ = -2, 
		/** not found in the list */
		kInvalidUIDIndex___ = -1 
	};
	/** @name draw action constants */
	enum { 
		/** do nothing */
		kNoDrawOrInval___ = 0, 
		/** force widget to redraw immediately */
		kForceDraw___ = 1, 
		/** inval the widget */
		kDoInval___ = 2,
		
		kDefaultDrawAction___ = kForceDraw___
	};

	// ----- List maintainence -----

	/** Set the database that the UID's are from. */
	virtual void			SetDataBase___(IDataBase *db) = 0;
	/** Get the database that the UID's are from. */
	virtual	IDataBase		*GetDataBase___()	const = 0;

  /** Add a UID to the list.

  	@param newUID IN the UID to add
  	@param drawAction IN draw action to apply to the associated widget
  */
  virtual void			AddUID___(const UID& newUID, int32 drawAction /*= kForceDraw*/, bool16 notifyOfChange = kTrue) = 0;

  /** Remove a UID from the list.

  	@param uid IN the UID to remove
  	@param drawAction IN draw action to apply to the associated widget
  */
	virtual void			RemoveUID___(UID uid, int32 drawAction /*= kForceDraw*/, bool16 notifyOfChange = kTrue) = 0;

  /** Clear the list (remove all the UIDs).

  	@param drawAction IN draw action to apply to the associated widget
  */
	virtual void			Clear___(int32 drawAction /*= kForceDraw*/, bool16 notifyOfChange = kTrue) = 0;
	
	/** Get the UID value at a given index in the list. */
	virtual UID				GetUID___(int32 index) const = 0;
							
	/** Get the index for the given UID. */
	virtual int32			GetIndex___(const UID& uid) const = 0;
								
	/** How many UIDs are in the list? */
	virtual int32			Length___() const = 0;

	/** Sort UIDs into order they appear in PageList or MasterSpreadList. If bReverse is set, sort in opposite order. */
	virtual void			Sort___(bool16 bReverse = kFalse) = 0;

	/** Replace the value at the location with another UID. */
	virtual void			Replace___(int32 at, const UID& uid) = 0;

};

#endif
