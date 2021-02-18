//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrawInterruptContext.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  This is the handle shape interface for page item adornments.  This interface can
//  return trackers just like a normal handle shape.  Keep in mind, however, that
//  it is the page item which is in the selection, not the adornment.  
//  
//========================================================================================

#pragma once
#ifndef __IDrawInterruptContext__
#define __IDrawInterruptContext__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"

class IWindow;

#define kSecondsOfEasyInterrupt 2

class IDrawInterruptContext: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDRAWINTERRUPTCONTEXT };

	enum DrawType
	{
		kDocDrawForeground,
		kDocDrawBackground,
		kDocNotDrawing,
		kGraphicPreviewDrawing,
		kImportingInDesignPage
	};

	enum InterruptEventType
	{
		kInterruptCommandPeriod,
		kInterruptCommandSomething,
		kInterruptOtherKeystroke,
		kInterruptMouseClick
	};

public:
	/**
	 * Returns whether the doc is drawing in the background, in the forground,
	 * Or not at all.
	 */

	virtual DrawType GetCurrentDrawType() = 0;

	/** 
	 * Returns when the document began its current draw, or zero if it is not
	 * Currently being drawn.  
	 */

	virtual time_t GetCurrentDrawStart() = 0;

	/**
	 * Returns the number of times so far the draw has been interrupted.  When a document
	 * does a full, non-interrupted draw, this value is reset to zero.  Each time we 
	 * interrupt in the middle of the draw, the value is incremented by 1.
	 */

	virtual int32 GetRepeatedDrawInterruptCount() = 0;

	/**
	 * This method is used to determine whether a given draw can be cancelled based on:
	 * A. The type of event that is supposed to cancel it.
	 * B. Whether the document is in the background or the forground.
	 * C. How long it has been since the draw started.
	 * It is called by the internal code that decides whether to cancel draws.  It is
	 * not much use unless you are trying to predict whether a draw will be cancelled.
	 */

	virtual bool16 ShouldCancelDrawIf( InterruptEventType nType ) = 0;

	/**
	 * Sets the value for GetCurrentDrawType.
	 */

	virtual void StartCurrentDraw( DrawType nDraw, IWindow* pWindow ) = 0;

	/**
	 * Gets the window currently being drawn, or nil if now window is being drawn.
	 */

	virtual IWindow* GetCurrentWindow() = 0;

	/**
	 * Sets the value for repeated draw interrupt count.
	 */

	virtual void IncrementCurrentDrawInterruptCount() = 0;
	virtual void ClearCurrentDrawInterruptCount() = 0;

	/**
	 * Used to indicate that the draw of this document has completed.
	 */

	virtual void FinishCurrentDraw(bool16 bAborted) = 0;
};

#endif
