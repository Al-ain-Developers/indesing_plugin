//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DVOffscreenGraphicsContext.h $
//  
//  Owner: jargast
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
#ifndef __DVOffscreenGraphicsContext__
#define __DVOffscreenGraphicsContext__

#include "IGraphicsContext.h"
#include "PMMatrix.h"

class IControlView;
class IViewPort;
class ITransform;
class IGraphicsContext;

/**
 DVOffscreenGraphicsContext is a Drover based implementation for IGraphicsContext.
 IGraphicsContext is a data container interface which is passed into drawing code, the 
 DVOffscreenGraphicsContext is a wrapper around DVOffscreenPortData.
 It contains the target viewport, transform, and cliprgn for drawing. It not a Shuksan
 object model interface, but simply an abstract interface from which implementation
 classes derive. It is being used from DVLayoutControlView (droverized layout widget).
 
 @see DVLayoutControlView
 @see DVOffscreenPortData
 @see IControlView
 */

class PUBLIC_DECL DVOffscreenGraphicsContext : public IGraphicsContext
{
public:

	// ----- Initialization -----
	DVOffscreenGraphicsContext(IViewPort* viewPort, const PMMatrix& toWindowMatrix, IControlView* iView, SysRgn clipRgnInWinCoords = nil);
	virtual ~DVOffscreenGraphicsContext();

	// ----- Clipping -----
	
	virtual SysRgn				GetClip() const;
	virtual SysRgn				GetOriginAdjustedClip() const;

	// ----- Accessors -----
	
	/**
	 Obsolete don't use
	 
	 It will cause an assert when called
	 */
	virtual SysPort				GetSysPort() const;
	
	virtual IViewPort*			GetViewPort() const;
	virtual const PMMatrix&		GetContentToViewTransform() const;
	virtual const PMMatrix&		GetViewToContentTransform() const;
	virtual IControlView*		GetView() const;

	bool16						IsCurrent() const;

	virtual dvaui::drawbot::Drawbot* GetDrawbot() const;

private:
	PMMatrix	fToWindowMatrix;
	PMMatrix	fFromWindowMatrix;
	PMMatrix	fOldTransform;
	
	IViewPort*		fViewPort;
	IControlView*	fView;

	SysRgn			fClipRgnInWinCoords;
};

#endif
