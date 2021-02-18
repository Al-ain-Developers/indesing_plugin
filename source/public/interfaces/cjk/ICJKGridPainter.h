//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridPainter.h $
//  
//  Owner: Heath Lynn
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
#ifndef __ICJKGridPainter__
#define __ICJKGridPainter__

#include "IPMUnknown.h"
#include "IDrawCJKGrid.h"

/** ICJKGridPainter allows for custom grid drawing.  This interface can be used to 
specify a ClassID of a boss that implements the IDrawCJKGrid interface.  This
implementation will be used to draw the grid instead of the default implementation
provided by InDesign.

The default grid drawing boss is kDefaultCJKGridDrawBoss.  It's important to note
that if another boss is specified in this interface, there is nothing stopping you from
manually instantiating a kDefaultCJKGridDrawBoss and calling the Draw methods 
from the custom implementation.  This would allow you to draw before or after the 
default grid drawing code.

*/
class ICJKGridPainter : public IPMUnknown
{

public:

	/**  Query for the IDrawCJKGrid instance as specified by the ClassID stored in this object.
		
		@return A pointer to a valid IDrawCJKGrid instance or nil on failure.
	*/
	virtual IDrawCJKGrid * QueryDrawCJKGrid() = 0;

	/**  Set the boss that will draw this grid.
		@param drawBoss IN The ClassID of the boss that will be used to draw this grid.
		@precondition The boss specified by drawBoss should implement IDrawCJKGrid.
	*/
	virtual void SetDrawBoss(ClassID drawBoss) = 0;
	
	/** Get the boss that will draw this grid.
		@return ClassID of the boss that will be used to draw this grid.
	*/
	virtual ClassID GetDrawBoss() = 0;
	
};

#endif
