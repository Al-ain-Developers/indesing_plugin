//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameOversetOverride.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITEXTFRAMEOVERSETOVERRIDE__
#define __ITEXTFRAMEOVERSETOVERRIDE__

#include "TextID.h"

class GraphicsData;

/**
This class allows private boss implementations that use the kTextFrameImpl
to override its default overset indicator handing behavior. This implementation
must be on the same boss as the kTextFrameImpl. TextOnAPath is an example of
an implementation which uses kTextFrameImpl but draws its own overset
indicator. Boss implementations which are happy with the default behavior do
not need to supply this implementation.
*/

class ITextFrameOversetOverride : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTFRAMEOVERSETOVERRIDE };

		/**
		This method will be called from the FrameShape::Inval() method as a
		result of a broadcast of kTextFrameOversetChangedMsg on the TextFrame.
		The implementation is expected to use the specified GraphicsData
		parameter to invalidate the appropriate amount of the view.
		*/
		virtual void	Inval(GraphicsData* gd) const = 0;

		/**
		This method will be called from FrameShape::DrawShape() as required
		if the TextFrame is overset and we are not printing. Note that for the
		standard kTextFrameBoss the overset indicator is also drawn by the 
		IHandleShape() implementation of the spline and this drawing will
		usually overwrite what is drawn here. The exception occurs during
		drawing of the TextFrame with the TextOffscreen active in which case
		the drawing of the handles is suppressed and what is drawn here will
		be effective.
		*/
		virtual void	Draw(GraphicsData* gd, int32 iShapeFlags) const = 0;

};

#endif
