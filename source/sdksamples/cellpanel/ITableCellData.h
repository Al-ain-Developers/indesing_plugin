//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/ITableCellData.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ITCPJData__
#define __ITCPJData__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "CelPnlID.h"		

/**
	From SDK sample;  an interface for an implementation that manages the data in TableCell.
	
	@ingroup cellpanel
	
*/
class ITableCellData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITABLECELLDATA };  // for UseDefaultIID()
	
		/**
			Get the maximum number of columns.
		*/
		virtual int32	GetMaxColumn(void) const = 0;
		
		/**
			Get the maximum number of rows.
		*/
		virtual int32	GetMaxRow(void) const = 0;
		
		/**
			Calculate of how many cells go into each column of the table.
		*/
		virtual int32	GetCellNumberOfColumns(void) const = 0;
		
		/**
			Calculate of how many cells go into each row of the table.
		*/
		virtual int32	GetCellNumberOfRows(void) const = 0;
		
		/**
			Calculate the width of the table.	
		*/
		virtual int32	GetTableWidth(void) const = 0;
		
		/**
			Calculate the height of the table.	
		*/
		virtual	int32	GetTableHeight(void) const = 0;
		
		/**
			Get the width of each cell.
		*/
		virtual int32	GetCellWidth(void) const = 0;
		
		/**
			Get the height of each cell.
		*/
		virtual	int32	GetCellHeight(void) const = 0;
		
		/**
			Get the row to show at the top of the visible area.
		*/
		virtual	int32	GetViewTopRow(void) const = 0;
		
		/**
			Set up row to show at the top of the visible area.
			@param Row is 32 bit integer.
		*/
 		virtual	void	SetViewTopRow(const int32 row) = 0;
		
		/**
			Get the column to show at the left of the visible area.
		*/
		virtual	int32	GetViewLeftColumn(void) const = 0;
		
		/**
			Set up column to show at the left of the visible area.
			@param column is 32 bit integer.
		*/
		virtual	void	SetViewLeftColumn(const int32 column) = 0;
		
		/**
			Acquire row of chosen cell.
		*/
		virtual	int32	GetSelectRow(void) const = 0;
		
		/**
			Set up row number of chosen cell.
			@param row is 32 bit integer.
		*/
		virtual	void	SetSelectRow(const int32 row) = 0;
		
		/**
			Acquire column of chosen cell.
		*/
		virtual	int32	GetSelectColumn(void) const = 0;
		
		/**
			Set up column number of chosen cell.
			@param row is 32 bit integer.
		*/
		virtual	void	SetSelectColumn(const int32 column) = 0;
		
		/**
			Examine whether cell is chosen.
			@param row Specify row number to examine.
			@param column Specify column number to examine.
		*/
		virtual bool	isSelection(const int32 column, const int32 row) const = 0;
		
		/**
			Acquire the string data of specified cell.
			@param column Specifies the column number of the cell.
			@param row Specifiesthe row number of the cell.
			@return String of the specified cell
		*/
		virtual const WideString&	GetCellString(int32 column, int32 row) const = 0;
		
		/**
			Acquire the string data of chosen Cell.
		*/
		virtual const WideString&	GetCellString(void) const = 0;
		
		/**
			Set up the string data of specified Cell.
			@param string String to set in specified cell.
			@param column Specifies the column number of the cell.
			@param row Specifies the row number of the cell.
		*/
		virtual bool16	SetCellString(const WideString& string,  int32 column, int32 row) = 0;
		
		/**
			Set up a string in chosen cell.
			@param string String to set in selected cell.
		*/
		virtual bool	SetCellString(const WideString &string) = 0;
		
		/**
			Invalidate the table cells by calling IControlView::Invalidate() on the kTableCellWidgetID widget.
			@param forceInvalidate default is false.
		*/
		virtual void	Invalidate(bool16 forceInvalidate = false) = 0;
		
		/** 
			Before resizing a table of panel widget, Calculate height and width of 
			the table for resizing of the panel. The client can ask if the size makes 
			sense by calling this method. Return size constraints. 
			This method is called from ConstrainDimensions method of panel view widget.
			@param desiredDimen The size of the adjusted table
		*/
		virtual PMPoint ConstrainDimensions(const PMPoint& desiredDimen) const = 0;
		

	enum {	kNoSelected = -1 };

};

#endif

// End, ITableCellData.h.