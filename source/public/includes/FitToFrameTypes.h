//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FitToFrameTypes.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __FitToFrameTypes__
#define __FitToFrameTypes__

namespace FitContentToFrameCmdSpace
{
	/** With the use of these enum values it's possible to control the behavior of the FitContentToFrameCmd
		more precisely. There is an IIntData interface on the command boss. Initialize it with one of these
		values and the direction that the resize of the frame for fit can be controlled. kStandard is equivalent
		of not filling in the int value at all and is the default behavior.
	*/
	enum FitToFrameType
	{
		/** Standard behavior, resize text frames bottom down and graphic frames in all directions to fit content */
		kStandard = 0,
		/** Adjust bottom and right sides to fit content */
		kLockTopLeft,
		/** Adjust bottom side to fit content */
		kLockTop,
		/** Adjust bottom and left sides fit content */
		kLockTopRight,
		/** Adjust left side fit content */
		kLockRight,
		/** Adjust top and left sides fit content */
		kLockBottomRight,
		/** Adjust top side fit content */
		kLockBottom,
		/** Adjust top and right sides fit content */
		kLockBottomLeft,
		/** Adjust right side fit content  */
		kLockLeft
	};
	
	/** With the use of these enum values it's possible to control the behavior of the FitContentToFrameCmd
		more precisely. See IID_IFRAMEFITVARIANT int data on the command boss this enum can alter the behavior
		of the command. See descriptions on enum values for details on how. If not filled in it will default to
		kStandard.
	*/
	enum FitFrameVariant
	{	
		/** For graphic frames move parent to content and fit according to FitToFrameType, for text frames lock side according to FitToFrameType */
		kStandardBehavior = 0,
		/** No effect on text frames, but for graphic frames content will move to parent so that a side of the parent can be locked in place. */
		kMoveGraphicContent
	};
}

#endif // __FitToFrameTypes__