//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CAcquireCoordSys.h $
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
#ifndef __CAcquireCoordSys__
#define __CAcquireCoordSys__

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/**
 An object that sets up the coordinate system for a given view or port. This is 
 usually not used standalone but as the base class for a template parameter to 
 AGMGraphicsContextWith.
 
 @see AGMGraphicsContextWith
 */
class PUBLIC_DECL CAcquireCoordSys
{
public:
	// ----- Initialization -----
	
	/**
	 Constructor
	 */
	CAcquireCoordSys();
	
	/**
	 Destructor
	 */
	~CAcquireCoordSys();

	/**
	 Called when this object is made the current coordinate system acquisition object
	 */
	virtual void			Resume() = 0;
	
	/**
	 Called when another object is made the current coordinate system acquisition object
	 */
	virtual void			Suspend() = 0;

protected:
	static int16			GetStackDepth();
	static void				IncrStackDepth();
	static void				DecrStackDepth();

	static CAcquireCoordSys*	GetFirstContext();
	static void	SetFirstContext(CAcquireCoordSys*);
	int16					fDepth;

	CAcquireCoordSys*			fNextContext;
};

#pragma export off

#endif
