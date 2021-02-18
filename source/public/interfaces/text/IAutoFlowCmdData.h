//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAutoFlowCmdData.h $
//  
//  Owner: eric_menninga
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
#ifndef __IAutoFlowCmdData__
#define __IAutoFlowCmdData__

#include "TextID.h"
#include "IPMUnknown.h"

class IFrameList;
class IGeometry;
class UIDRef;
class PMPoint;

/**	Used by the auto-flow text command, this interface sets the parameters for
	the command to use.
	@ingroup text_autoflow
*/
class IAutoFlowCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IAUTOFLOWCMDDATA };

		/**	Set the parameters for the command to use.
			@param page is which page UID to start autoflowing on.
			@param framelist is the framelist UID of the story to start autoflowing with.
					If the frame list is kInvalidUID, the cmd will use the contents of
					the place gun or content dropper; otherwise it will use the provided framelist and
					delete the place gun's(or content dropper's)
			@param parent is the layer within to document to autoflow into. This becomes
					the hierarchical parent of the new text frames.
			@param where specifies to point in pasteboard coordinates of the initial mouse-down.
			@param usePB specified whether to use a progress bar during auto-flow.
			@param usePlaceGun specifies whether to use the place gun or content dropper
		*/
		virtual void Set(UID page, UID framelist, UIDRef& parent, PMPoint& where, bool16 usePB = kFalse, 
						bool16 usePlaceGun = kTrue) = 0;

		/** Get the IFrameList interface of story to autoflow.
			@return an AddRef'd IFrameList interface of the story.
		*/
		virtual IFrameList*		QueryFrameList() = 0;

		/** Get the page to start autoflowing on.
			@return an AddRef'd IGeometry interface of the starting page.
		*/
		virtual IGeometry*		QueryStartPage() = 0;

		/** Get the layer to flow onto.
			@return the UIDRef of the layer to place into.
		*/
		virtual const UIDRef&	GetParent() const = 0;

		/** Get the mouse-down position.
			@return the mouse-down point in pasteboard coordinates.
		*/
		virtual const PMPoint&	GetClickPoint() const = 0;

		/** Control the progress bar.
			@return kFalse to suppress the progress bar.
		*/
		virtual bool16			UseProgressBar() const = 0;

		/** Get the number of characters that will be autoflowed - used for the progress bar.
			@return the length of the story.
		*/
		virtual TextIndex		GetTextLength() = 0;

		/** Get the IFrameList reference.
			@return the UID of the frame list.
		*/
		virtual UID			GetFrameListUID() = 0;

		/** Get the initial text frame to start autoflowing with.
			@return the UID of the starting text frame.
		*/
		virtual UID			GetInitialTextFrameUID() const = 0;

		/** Get the first item on the place gun if UsePlaceGun returns kTrue else returns
			the first item on the content dropper's place head.
			@return the UID of the first place item.
		*/
		virtual UID			GetFirstPlaceItemUID() const = 0;

		/** Controls whether to use the place or content dropper. This option will be
			used if the framelist provided in the Set method is kInvalidUID.
			@return kTrue if place gun is to be used.
		*/
		virtual bool16		UsePlaceGun() const = 0;
};

#endif
