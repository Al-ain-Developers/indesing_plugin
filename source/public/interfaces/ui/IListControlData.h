//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IListControlData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IListControlData_h__
#define __IListControlData_h__

#include "widgetid.h"

/** Interface representing part of listbox data-model. See also IListControlDataOf for residual.
*/
class IListControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILISTCONTROLDATA };

	/** Remove item by index.
		@param index position of item to remove from list
		@param invalidate specifies whether control should be invalidated
		@param notifyOfChange specifies if registered observers should be notified about this change to the data model
	*/
	virtual void		Remove(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
							 
	/** Clear the list, that is, remove all elements.
		@param invalidate specifies whether control should be invalidated
		@param notifyOfChange specifies if registered observers should be notified about this change to the data model
	*/
	virtual void		Clear(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

							 
	/** How many items are in the list?
		@return count of items in the list
	*/
	virtual int32		Length() const = 0;

	/** Synchronize the data stored in IListControlData with the tree control.

		Note: Refresh is acutally an implementation detail and doesn't 
		seem right to be in this interface. 
						
	*/
	virtual void		Refresh() const = 0;
						 
	/** Synchronize the data stored in IListControlData with the sysControl.
		Typically it's called right after the sysControl is created.

		Note: Synchronize is acutally an implementation detail and doesn't 
		seem right to be in this interface. However, IListControlDataOf <T>
		(which derives from IListControlData) is a template based interface
		and we want to avoid templatizing the IControlView interface.
						
	*/
	virtual void		Synchronize(SysControl sysControl) const = 0;
							//		[lxia]	01/25/01
};

#endif // __IListControlData_h__
