//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AGMGraphicsContext.h $
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
#ifndef __AGMGraphicsContext__
#define __AGMGraphicsContext__

#include "AGMGraphicsContextWith.h"

/**
 This is a convenience typedef for declaring a platform-specific graphics 
 context to wrap an AGM-based port
 
 This is intended to be used as a stack-based object to set up a view port for 
 drawing. For instance, a typical use is in the Draw method of an IControlView:
 
 <pre>
 void MyExampleControlView::Draw(IViewPort *viewPort, SysRgn updateRgn)
 {
	AGMGraphicsContext gc(viewPort, this, updateRgn);
	IGraphicsPort port(gc.GetViewPort(), UseDefaultIID());
	
	port->gsave();
	...
	port->grestore();
 }
 </pre>
  
 @see AGMGraphicsContextWith
 */

#include "DVAGMAcquireCoordSys.h"
#include "DVAGMAcquireClip.h"
typedef AGMGraphicsContextWith<DVAGMAcquireCoordSys, DVAGMAcquireClip> AGMGraphicsContext;

#endif

//Non Marking Graphics Context for hit testing and invalidation
#include "NonMarkingAGMGraphicsContext.h"

// Unconverted direct drawing macros can either assert or beep and trace
#define ID_UNCONVERTED_DIRECT_DRAWING_SHOULD_ASSERT	1
#define ID_UNCONVERTED_DRAGDROP_TARGET_HILITING_SHOULD_ASSERT 0

#if ID_UNCONVERTED_DIRECT_DRAWING_SHOULD_ASSERT
	#define UNCONVERTED_DIRECT_DRAWING_MACRO() ASSERT_FAIL("Unconverted Direct Drawing encountered. Please convert this code.");
#else
	#define UNCONVERTED_DIRECT_DRAWING_MACRO() {TRACEFLOW("Drover:NoDirectDraw", "UnconvertedDirect Drawing encountered. Please convert this code.\n");}
#endif

#if ID_UNCONVERTED_DRAGDROP_TARGET_HILITING_SHOULD_ASSERT
	#define UNCONVERTED_DRAGDROP_TARGET_HILITING_MACRO() ASSERT_FAIL("Unconverted DragDrop target hiliting encountered. Please convert this code.");
#else
	#define UNCONVERTED_DRAGDROP_TARGET_HILITING_MACRO() {TRACEFLOW("Drover:NoDirectDraw", "DragDrop target hiliting encountered. Please convert this code. (see CTreeViewDragDropTarget.cpp)\n");}
#endif



