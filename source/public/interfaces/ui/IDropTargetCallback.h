//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDropTargetCallback.h $
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
//  Interface definition to allow Drop targets
//  to notify other objects of their tracking state.
//  
//========================================================================================

#pragma once
#ifndef __IDropTargetCallback__
#define __IDropTargetCallback__

#include "IPMUnknown.h"

class PMPoint;
class PMRect;

/** IDropTargetCallback allows drag drop targets to directly notify other objects during the drag tracking process.

	@see IDragDropTarget::RegisterTargetCallback, IDragDropTarget::ReleaseTargetCallback
*/

class IDropTargetCallback : public IPMUnknown
{
	public:
		/** constants for indicating the current phase of the drag	*/
		enum eCallbackState	{ 
			/** drag has entered the target */
			kTargetEntered = 0, 
			/** drag is moving within the target */
			kTargetWithin = 1, 
			/** drag has left the target */
			kTargetLeft = 2
		};
		
		/** Callback for drag tracking.
				The localPt parameter is only valid in the kTargetWithin state, which is called periodically 
				as the mouse moves within the target.

			@param state IN the current state of the drag
			@param localPt IN current mouse location within the target
			@param rect IN bounds of the drag feedback

		*/
		virtual void				TrackingCallback(eCallbackState state, const PMPoint& localPt, PMRect& rect) = 0;
};

#endif
