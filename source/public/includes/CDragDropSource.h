//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CDragDropSource.h $
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
//  Interface for a generic Drag and Drop source
//  
//========================================================================================

#pragma once
#ifndef __CDragDropSource__
#define __CDragDropSource__

#include "HelperInterface.h"
#include "IDragDropSource.h"
#include "IDragDropController.h"

class IEvent;
class IDragDropTarget;

#pragma export on

/** Basic implementation of the IDragDropSource interface, representing the source object that initiates a drag drop operation.
		Implementors of IDragDropSource should derive from either this or CDragDropSource_Extensible.

		@see IDragDropSource, CDragDropSource_Extensible
 */
class WIDGET_DECL CDragDropSource : public IDragDropSource
{
	public:
										CDragDropSource(IPMUnknown *boss);
		virtual						~CDragDropSource();
		
		/** Override this if you can only start drags from certain areas within the source widget, 
				default implementation always returns kTrue
		*/
		virtual bool16 			WillDrag(IEvent* e) const;
		
		/** Override this if you want to use non-standard drag cursors (which is pretty common), 
				default implementation returns DragDrop::kDefaultDragCursors
		*/
		virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;
		
		/** Override this if you want to use non-standard drag outline for the data being dragged (which is pretty common), 
				default implementation returns DragDrop::kDefaultDragOutline which uses the source widget's bounds.
		*/
		virtual SysWireframe 			DoMakeDragOutlineRegion() const;

		/** Override this to add your own content to the drag, 
				default implementation adds a bit of text data to the drag for demonstration purposes.
		*/
		virtual bool16			DoAddDragContent(IDragDropController*);
		
		/** Override this if your source needs to support removing data when it is moved to another target (or the trash), 
				default implementation returns kFailure
		*/
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		
		/** Override this if your source needs to support removing data when it is moved to another target (or the trash), 
				default implementation returns nil, which implies that data cannot be "moved" to any target not identical to this one.
		*/
		virtual IDataBase*	GetSourceDataBase() const;

	private:

		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif //__CDragDropSource__

