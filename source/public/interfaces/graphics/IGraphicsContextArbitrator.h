//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicsContextArbitrator.h $
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
 #ifndef __IGraphicsContextArbitrator__
 #define __IGraphicsContextArbitrator__
 
 #include "GraphicsID.h"
 
class IGraphicsContext;
 
 /**
  Manages a stack of graphics contexts
  
  @see IGraphicsContext
  */
 class IGraphicsContextArbitrator : public IPMUnknown
 {
 public:
	/**
	 Pushes context on the stack of graphics contexts, making it the new
	 current context
	 
	 @see IGraphicsContext
	 */
	virtual void				SetContext(IGraphicsContext* context) = 0;

	/**
	 Pops the topmost graphics context from the stack, restoring the previous
	 context
	 
	 @return The old current context
	 @see IGraphicsContext
	 */
	virtual IGraphicsContext*	RestorePriorContext() = 0;

	/**
	 Returns the current context
	 
	 @return The current context
	 @see IGraphicsContext
	 */
	virtual IGraphicsContext*	GetCurrentContext() = 0;
 };
 #endif
