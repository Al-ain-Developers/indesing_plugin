//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDragDropSource_Extensible.h $
//  
//  Owner: Dave Burnard
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
//  Interface for a generic extensible Drag and Drop source
//  
//========================================================================================

#pragma once
#ifndef __CDragDropSource_Extensible__
#define __CDragDropSource_Extensible__

#include "HelperInterface.h"
#include "IK2ServiceProvider.h"
#include "IDragDropSource.h"
#include "IDragDropController.h"

class IEvent;
class IDragDropTarget;
class IDragDropSourceContentHelper;

#pragma export on

/** Extensible implementation of the IDragDropSource interface, representing the source object that initiates a drag drop operation.
		Implementors of IDragDropSource should derive from either this or CDragDropSource.

		@see IDragDropSource, IDragDropSourceContentHelper
 */
class WIDGET_DECL CDragDropSource_Extensible : public IDragDropSource
{
	public:
										CDragDropSource_Extensible(IPMUnknown *boss);
		virtual						~CDragDropSource_Extensible();
		
		/** Default implementation calls Delegate_WillDrag to query content helpers to start the drag.
				When overriding this method, make sure to call the inherited version.
		*/
		virtual bool16 			WillDrag(IEvent* e) const;
		
		/** Default implementation calls Delegate_GetDragCursor to query the active content helper for the drag cursor. */
		virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;

		/** Default implementation calls Delegate_DoMakeDragOutlineRegion to query the active content helper for the drag outline region. */
		virtual SysWireframe 			DoMakeDragOutlineRegion() const;

		/** Default implementation forwards the DoAddDragContent method to the active content helper. */
		virtual bool16			DoAddDragContent(IDragDropController*);
		
		/** Default implementation forwards the ProcessDragDropCommand method to the active content helper. */
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		
		/** Override this if your source needs to support removing data when it is moved to another target (or the trash), 
				default implementation returns nil, which implies that data cannot be "moved" to any target not identical to this one.
		*/
		virtual IDataBase*	GetSourceDataBase() const;
		
		/** Override this to return the service ID that content helpers for this source will respond to. 
		*/
		virtual ServiceID GetContentHelperServiceID() const = 0;
		
		/** Query for the active content handler, nil if one has not been set. */
		IDragDropSourceContentHelper*	QueryActiveContentHelper() const;
		/** Get the active content handler, nil if one has not been set. */
		IDragDropSourceContentHelper*	GetActiveContentHelper() const;
		/** Set the active content handler. Called by Delegate_WillDrag when/if it finds a helper willing to start a drag. */
		void	SetActiveContentHelper(IDragDropSourceContentHelper*);

		/** Forwards the CouldStartDrag call to the content helpers for this target, to determine if a drag can be started
				at the specified location. Helper responses are prioritized based on the eHelperType returned by the helper.
				If a willing helper is found, it is set as the active content helper and the drag proceeds.
		*/
		bool16						Delegate_WillDrag(IEvent* e);

		/** Forwards the GetDragCursor method to the active content helper. */
		CursorSpec 				Delegate_GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal);
		/** Forwards the CreateDragOutlineRegion method to the active content helper. */
		SysWireframe 					Delegate_DoMakeDragOutlineRegion();

	private:
		IDragDropSourceContentHelper*	fActiveContentHelper;
		
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif //__CDragDropSource__

