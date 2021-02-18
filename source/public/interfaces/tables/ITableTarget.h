//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableTarget.h $
//  
//  Owner: Danielle Bessette
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
//  
//========================================================================================

#pragma once
#ifndef __ITableTarget__
#define __ITableTarget__

#include "TablesID.h"
#include "TableTypes.h"

class ITableModel;
class IFrameAnchorGeom;
class ICellFocus;

/** 
	This is a rectangular target area in a table. This target is usually set up so you can preform actions on this area.
*/
class ITableTarget : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITABLETARGET };

	/**
		Sets the ITableModel this target is in.
		@param model The ITableModel
	*/
	virtual void			SetModel(const ITableModel* model) = 0;	

	/**
		Sets the ITableModel this target is in.
		@param tableRef	The model UIDRef
	*/
	virtual void			SetModel(const UIDRef& tableRef) = 0;	
	
	/**
		Returns the ITableModel this target is in.
	*/
	virtual ITableModel*	QueryModel() const = 0;

	/**
		Returns the UIDRef of the ITableModel this target is in.
	*/
	virtual UIDRef 			GetModel() const = 0;	

	/**
		Sets the rectangular area of the table this target is in.
		@param cells	GridArea range of cells
	*/
	virtual	void			SetRange(const GridArea& cells) = 0;

	/**
		Returns the rectangular area of the table this target is in.
	*/
	virtual const GridArea&	GetRange() const = 0;

	/**
		Sets up the table target with a model and a GridArea, but it doesn't add the cell focus 
		(representing the target) to the cell focus manager.  This should only be used when doing 
		one time opporations with the TableTarget -- using this when the model changes under in 
		the GridArea of the target will cause crashes.  After SetTargetUnManaged has been called, 
		SetModel can never be called!

		@param		model		the ITableModel being unmanaged
		@param		cells			the GridArea being unmanaged
	*/
	virtual	void			SetTargetUnManaged(const ITableModel* model, const GridArea& cells) = 0;

	/**
		Clears the target.
	*/
	virtual void			Clear (void) = 0;

	/**
		Returns kTrue if this target is valid.
	*/
	virtual bool16			HasContent (void) const = 0;

	/**     Initialize 
			@param	db		Database the target is associated with. 
	*/
        virtual void            Initialize      (IDataBase* db) = 0;
};

#endif // __ITableTarget__
