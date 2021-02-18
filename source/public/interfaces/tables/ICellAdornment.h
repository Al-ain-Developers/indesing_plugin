//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellAdornment.h $
//  
//  Owner: Jesse Jones (jejones)
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
#ifndef __ICellAdornment__
#define __ICellAdornment__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"


//-----------------------------------
//	Forward References
//
class IGraphicsPort;
class ITableFrame;
class PMMatrix;
class ICallback;


// ===================================================================================
//	class ICellAdornment		
// ===================================================================================
/** 
	Interface that is added to ITableAdorners to change how cells draw.

	Adornments can be drawn before or after cells; e.g. adornments may be drawn 
	behind text (kPassBeforeCell), but above the fill,
	
	Alternatively, cells can be drawn before adornments on each pass (adornment would be kPassAfterCell).
*/
class ICellAdornment : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ICELLADORNMENT};

	typedef enum { kPassBeforeCell = -1, kPassAfterCell = 1 } DrawPass;
	typedef K2Vector<DrawPass>	DrawPassList;

	// ----- API -----
	/** Method that draws the adornment. Use ITableFrame::GetCellArea to determine where you can draw.
		Note that you should not draw outside the cell's ink area.
		@param port graphics port that's target for drawing
		@precondition port <> nil
		@precondition frame <> nil
		@precondition cells.size() > 0
	*/
	virtual void 		Draw(IGraphicsPort* port, int32 shapeFlags, DrawPass pass, 
							 const ITableFrame* frame, const K2Vector<GridAddress>& cells) const = 0;
					

	/** This is called when the table shape has to hilite the cells
		that are part of a table selection. 
		@param port graphics port that's target for drawing
		@param frame table frame in which this adornment is being drawn
		@param cells specifies cells affected by this operation
		@precondition port <> nil
		@precondition frame <> nil
		@precondition cells.size() > 0
	*/
	virtual void 		Hilite(IGraphicsPort* port, const ITableFrame* frame, const K2Vector<GridAddress>& cells) const = 0;
					
	/** Collects up all the passes the adornment wants to draw in.
		@param passes OUT parameter used in specifying passes that this adornment draws in
		@postcondition passes.size() >= passes@pre.size()
	*/
	virtual void 		GetPassInfo(DrawPassList& passes) const = 0;
					
	/** Iterate over every cell with this adornemnt and add it to the callback
		@param frame
		@param cells
		@param xform
		@param callbackInfo
		@param iShapeFlags
	*/
    virtual void		IterateCellAdornmentDrawOrder(const ITableFrame* frame,
										const K2Vector<GridAddress>& cells, 
								  		const PMMatrix *xform,
										ICallback *callbackInfo,
										int32 iShapeFlags = 0) = 0;
						 
};

DECLARE_BASE_TYPE(ICellAdornment::DrawPass);

#endif // __ICellAdornment__
