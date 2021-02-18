//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicsContext.h $
//  
//  Owner: Jack Kirstein
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
#ifndef __IGraphicsContext__
#define __IGraphicsContext__

#include "PMPoint.h"

class PMMatrix;
class IViewPort;
class ITransform;
class IControlView;

#include "DVAForwardDeclarations.h"

/**
 IGraphicsContext is a data container interface which is passed into drawing code
 It contains the target viewport, transform, and cliprgn for drawing. It not a Shuksan
 object model interface, but simply an abstract interface from which implementation
 classes derive.
 
 @see IViewPort
 @see IControlView
 */
class IGraphicsContext INHERITFROM
{
public:
	// ----- Clipping -----
	/**
	 Gets the clipping region for this context
	 
	 @return the clipping region as a SysRgn
	 */
	virtual SysRgn				GetClip() const = 0;
	
	/**
	 Gets the origin-adjusted clipping region for this context
	 
	 @return the origin-adjusted clipping region as a SysRgn
	 */
	virtual SysRgn				GetOriginAdjustedClip() const = 0;
	
	// ----- Accessors -----
	
	/**
	 Gets the SysPort for this context
	 
	 @return the SysPort
	 */
	virtual SysPort				GetSysPort() const = 0;
	
	/**
	 Gets the view port for this context
	 
	 @see IViewPort
	 @return the view port
	 */
	virtual IViewPort*			GetViewPort() const = 0;
	
	/**
	 Gets the transform matrix for this context
	 
	 @see PMMatrix
	 @see IGraphicsContext::GetInverseTransform
	 @return the transform matrix
	 */
	virtual const PMMatrix&		GetContentToViewTransform() const = 0;
	
	/**
	 Gets the inverse transform matrix for this context
	 
	 @see PMMatrix
	 @see IGraphicsContext::GetTransform
	 @return the inverse transform matrix
	 */
	virtual const PMMatrix&		GetViewToContentTransform() const = 0;
	
	/**
	 Gets the control view for this context
	 
	 @see IControlView
	 @return the control view
	 */
	virtual IControlView*		GetView() const = 0;

	/**
	 Returns kTrue if this context is current, else kFalse
	 
	 @see IGraphicsContextArbitrator
	 @return whether this context is current
	 */
	virtual bool16				IsCurrent() const = 0;

	/** 
	 Gets the Drawbot for this context 
	 @return the Drawbot* 
	*/ 
	virtual dvaui::drawbot::Drawbot* GetDrawbot() const = 0;
};

#endif