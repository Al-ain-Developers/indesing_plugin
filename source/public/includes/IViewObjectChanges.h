//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IViewObjectChanges.h $
//  
//  Owner: Habib Khalfallah
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
#ifndef __IViewObjectChanges__
#define __IViewObjectChanges__

#include "ShuksanID.h"

/**	IViewObjectChanges plays a similar role for 
	snapshot view interfaces that IPMPersist plays for persistent
	interfaces. 
	
	Add kViewObjectChangesImpl to the class definition of any boss 
	that has one or more snapshot view interfaces.

	This interface holds a reference to the database that the view interfaces 
	pertaining to this boss target. Multiple view interfaces located on the
	same boss target the same database at any point in time.

	Use the SetTargetDB function to set the target database of the 
	view interfaces located on this boss. This target can be changed
	multiple times through the lifetime of the boss. 
	Use GetTargetDB to identify the target database at any point in time.

	@see CViewInterface
 */
class IViewObjectChanges : public IPMUnknown
{
	public:

		enum {kDefaultIID = IID_IVIEWOBJECTCHANGES};

		/**	Use the SetTargetDB function to set the target database of the 
			view interfaces located on this boss. 

			@param viewTarget 
		 */
		virtual void SetTargetDB(IDataBase* viewTarget) = 0;

		/**	For internal use only
			@param boss
			@param obj
			@param prop
			@param allowModification
		 */
		virtual void  SetDirty	(IControllingUnknown *boss, IPMUnknown* obj, ImplementationID prop, bool16 allowModification = true) = 0;

		/**	For internal use only
		 */
		virtual void ResetAll() = 0;

		/**	Use GetTargetDB to identify the target database at any point in time.
			@return IDataBase* 
		 */
		virtual IDataBase* GetTargetDB() const = 0;

		/**	For internal use only
		 */
		virtual void SetBusy (bool busy) = 0;

		/**	For internal use only
		 */
		virtual bool IsBusy () const = 0;

		/**	For internal use only
		 */
		virtual void ResetOneToSnapshot(ImplementationID prop, SnapshotID snapshotID) = 0;
		/**	For internal use only
		 */
		virtual SnapshotID SnapshotOneIfNecessary (ImplementationID prop) = 0;
};
#endif
