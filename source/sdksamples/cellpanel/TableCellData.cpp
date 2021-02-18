//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/TableCellData.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IPMStream.h"
#include "IPanelControlData.h"
#include "ITableCellData.h"

// General includes:
#include "CPMUnknown.h"
#include "CellTable.h"

// Project includes:
#include "CelPnlID.h"
#include "CelPnlDefines.h"

/**
	TableCellData is an interface for an implementation that manages the data in TableCell.
	
	@ingroup cellpanel
	
*/
class TableCellData : public CPMUnknown<ITableCellData>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TableCellData(IPMUnknown *boss);
		/**
			Destructor.
		*/
		virtual ~TableCellData();
		
		/**
			ReadWrite of Persistance 
		*/
		virtual void	ReadWrite(IPMStream *s, ImplementationID prop);
		
		/**
			Get the maximum number of columns.
		*/
		virtual int32	GetMaxColumn(void) const;
		
		/**
			Get the maximum number of rows.
		*/
		virtual int32	GetMaxRow(void) const;
		
		/**
			Calculate of how many cells go into each column of the table.
		*/
		virtual int32	GetCellNumberOfColumns(void) const;
		
		/**
			Calculate of how many cells go into each row of the table.
		*/
		virtual int32	GetCellNumberOfRows(void) const;
		
		/**
			Calculate the width of the table.	
		*/
		virtual int32	GetTableWidth(void) const;
		
		/**
			Calculate the height of the table.	
		*/
		virtual	int32	GetTableHeight(void) const;
		
		/**
			Get the width of each cell.
		*/
		virtual int32	GetCellWidth(void) const;
		
		/** 
			Get the height of each cell.
		*/
		virtual	int32	GetCellHeight(void) const;
		
		/**
			Get the row to show at the top of the visible area.
		*/
		virtual	int32	GetViewTopRow(void) const;
		
		/**
			Set up row to show at the top of the visible area.
			@param Row is 32 bit integer.
		*/
		virtual	void	SetViewTopRow(const int32 row);
		
		/**
			Get the column to show at the left of the visible area.
		*/
		virtual	int32	GetViewLeftColumn(void) const;
		
		/**
			Set up column to show at the left of the visible area.
			@param column is 32 bit integer.
		*/
		
		virtual	void	SetViewLeftColumn(const int32 column);
		
		/**
			Acquire row of chosen cell.
		*/
		virtual	int32	GetSelectRow(void) const;
		
		/**
			Set up row number of chosen cell.
			@param row is 32 bit integer.
		*/
		virtual	void	SetSelectRow(const int32 row);
		
		/**
			Acquire column of chosen cell.
		*/
		virtual	int32	GetSelectColumn(void) const;
		
		/**
			Set up column number of chosen cell.
			@param row is 32 bit integer.
		*/
		virtual	void	SetSelectColumn(const int32 column);
		
		/**
			Examine whether cell is chosen.
			@param row Specify row number to examine.
			@param column Specify column number to examine.
		*/
		virtual bool	isSelection(const int32 column, const int32 row) const;
				
		/**
			Acquire the string data of specified cell.
			@param column Specifies the column number of the cell.
			@param row Specifiesthe row number of the cell.
			@return String of the specified cell
		*/
		virtual const WideString&	GetCellString(int32 column, int32 row) const;
		
		/**
			Acquire the string data of chosen Cell.
		*/
		virtual const WideString&	GetCellString(void) const;
		
		/**
			Set up the string data of specified Cell.
			@param string String to set in specified cell.
			@param column Specifies the column number of the cell.
			@param row Specifies the row number of the cell.
		*/
		virtual bool16		SetCellString(const WideString& string,  int32 column, int32 row);
		
		/**
			Set up a string in chosen cell.
			@param string String to set in selected cell.
		*/
		virtual bool		SetCellString(const WideString& string);
		
		/**
			Invalidate the table cells by calling IControlView::Invalidate() on the kTableCellWidgetID widget.
			@param forceInvalidate default is false.
		*/
		virtual void	Invalidate(bool16 forceInvalidate);
		
		/** 
			Before resizing a table of panel widget, Calculate height and width of 
			the table for resizing of the panel. The client can ask if the size makes 
			sense by calling this method. Return size constraints. 
			This method is called from ConstrainDimensions method of panel view widget.
			@param desiredDimen The size of the adjusted table
		*/
		virtual PMPoint ConstrainDimensions(const PMPoint& desiredDimen) const;
		
	private:
	
		virtual void	CalculateRowsColumns(void);
		
	private:
		
				CellTable	*table;
				
				int32		fMaxColumns;
			 	int32		fMaxRows;
				
				int32		fNumberOfColumns;
			 	int32		fNumberOfRows;
				
				int32		fCellWidth;
				int32		fCellHeight;
				
				int32		fLeftColumn;
				int32		fTopRow;
				
				int32		fSelectColumn;
				int32		fSelectRow;
 
 };

CREATE_PERSIST_PMINTERFACE(TableCellData, kTableCellDataImpl)

/* TableCellData
*/
TableCellData::TableCellData(IPMUnknown *boss) : CPMUnknown<ITableCellData>(boss),
			fMaxColumns(kMaxColumnData) ,
			fMaxRows(kMaxRowData),
			fNumberOfColumns(kMaxColumnData),
			fNumberOfRows(kMaxRowData),
			fCellWidth(kDefaultCellWidth),
			fCellHeight(kDefaultCellHeight),
			fLeftColumn(0),
			fTopRow(0),
			fSelectColumn(kNoSelected),
			fSelectRow(kNoSelected)
{

	table = new CellTable(fNumberOfColumns, fNumberOfRows);
	
#if DEBUG //Test Code.
	char s[64];
	for(int32 row = 0; row < fNumberOfRows; row++){
		for(int32 column = 0; column < fNumberOfColumns; column++){
			sprintf(s, "Cell %d:%d", column, row);
			table->SetString(WideString(s), column, row);
		}
	}
#endif
}

/* ~TableCellData
*/
TableCellData::~TableCellData()
{
	delete table;
}

/* ReadWrite
*/
void TableCellData::ReadWrite(IPMStream *s, ImplementationID prop)
{
	s->XferInt32(fCellHeight);
	s->XferInt32(fCellWidth);
	s->XferInt32(fNumberOfRows);
	s->XferInt32(fNumberOfColumns);
}

/* GetMaxColumn
*/
int32 TableCellData::GetMaxColumn(void) const
{
 	return fMaxColumns;
}

/* GetMaxRow
*/
int32 TableCellData::GetMaxRow(void) const
{
 	return fMaxRows;
}

/* GetCellNumberOfColumns
*/
int32 TableCellData::GetCellNumberOfColumns(void) const
{
 	return (this->GetTableWidth() / this->GetCellWidth());
}

/* GetCellNumberOfRows
*/
int32 TableCellData::GetCellNumberOfRows(void) const
{
 	return (this->GetTableHeight() / this->GetCellHeight());
}

/* GetTableWidth
*/
int32	TableCellData::GetTableWidth(void) const
{
	return	fNumberOfColumns * fCellWidth;
}

/* GetTableHeight
*/
int32	TableCellData::GetTableHeight(void) const
{
	return	fNumberOfRows * fCellHeight;
}

/* GetCellWidth
*/
int32	TableCellData::GetCellWidth(void) const
{
	return fCellWidth;
}

/* GetCellHeight
*/
int32	TableCellData::GetCellHeight(void) const
{
	return fCellHeight;
}

/* GetViewTopRow
*/
int32	TableCellData::GetViewTopRow(void) const
{
	return fTopRow;
}

/* SetViewTopRow
*/
void	TableCellData::SetViewTopRow(const int32 row)
{
	if((0 <= row) && (row < GetMaxRow())){
		fTopRow = row;
	}
}

/* GetViewLeftColumn
*/
int32	TableCellData::GetViewLeftColumn(void) const
{
	return	fLeftColumn;
}

/* SetViewLeftColumn
*/
void	TableCellData::SetViewLeftColumn(const int32 column)
{
	if((0 <= column) && (column < GetMaxColumn())){
		fLeftColumn = column;
	}
}

/* GetSelectRow
*/
int32	TableCellData::GetSelectRow(void) const
{
	return 	fSelectRow;
}

/* SetSelectRow
*/
void	TableCellData::SetSelectRow(const int32 row)
{
	if(row != kNoSelected)
	{
		if((0 <= row) && ((GetViewTopRow() + row) < GetMaxRow())){
			fSelectRow = GetViewTopRow() + row;
		}
		else
			fSelectRow = kNoSelected;
	}
}

/* GetSelectColumn
*/
int32	TableCellData::GetSelectColumn(void) const
{
	return fSelectColumn;
}

/* SetSelectColumn
*/
void	TableCellData::SetSelectColumn(const int32 column)
{
	if(column != kNoSelected)
	{
		if((0 <= column) && ((GetViewLeftColumn() + column) < GetMaxColumn())){
			fSelectColumn = GetViewLeftColumn() + column;
		}
		else
			fSelectColumn = kNoSelected;
	}
}

/* isSelection
*/
bool TableCellData::isSelection(const int32 column, const int32 row) const
{
	if((column == GetSelectColumn()) && (row == GetSelectRow())){
		return kTrue;
	}else{
		return kFalse;
	}
}

/* GetCellString
*/
const WideString& TableCellData::GetCellString(int32 column, int32 row) const
{
	if((column < 0) || (row < 0))  return kNullWideString;
	if(((fMaxColumns - 1) < column) || ((fMaxRows - 1) <  row)) return kNullWideString;
	
	return table->GetString(column, row);
}

/* GetCellString
*/
const WideString& TableCellData::GetCellString(void) const
{
	return GetCellString(fSelectColumn, fSelectRow);

}

/* SetCellString
*/
bool16 TableCellData::SetCellString(const WideString& string,  int32 column, int32 row) 
{
	if((column < 0) || (row < 0))  return 0;
	if(((fMaxColumns - 1) < column) || ((fMaxRows - 1) <  row)) return 0;

	return table->SetString(string, column, row);
}

/* SetCellString
*/
bool TableCellData::SetCellString(const WideString& string) 
{
	return SetCellString(string, fSelectColumn, fSelectRow);
}

/* Invalidate
*/
void TableCellData::Invalidate(bool16 forceInvalidate)
{
	int32 oldNumberOfRows = fNumberOfRows;
	int32 oldNumberOfColumns = fNumberOfColumns;
	
	this->CalculateRowsColumns();
	
	if(forceInvalidate 
		|| (oldNumberOfRows != fNumberOfRows)
		|| (oldNumberOfColumns != fNumberOfColumns))
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		// Assert message
		ASSERT_MSG(panelData != nil, "TableCellData::Invalidate - missing IID_IPANELCONTROLDATA at server's boss..");
		
		if(panelData){
			InterfacePtr<IControlView> pTableCellView(panelData->FindWidget(kTableCellWidgetID) , UseDefaultIID());
			if(pTableCellView)
				pTableCellView->Invalidate();
		}
	}
}

/* ConstrainDimensions
*/
PMPoint TableCellData::ConstrainDimensions(const PMPoint& desiredDimen) const
{
	PMPoint constrainedDim = desiredDimen;
		
	// The table width
	int32 columnCount = ::ToInt32(((constrainedDim.X()) + fCellWidth / 2) / fCellWidth);
	
	if (columnCount > fMaxColumns) columnCount = fMaxColumns;
	else if (columnCount < 1) columnCount = 1;

	constrainedDim.X(columnCount * fCellWidth);
	
	// The table height
	int32	rowCount = ::ToInt32(((constrainedDim.Y()) + fCellHeight / 2) / fCellHeight);
	
	if (rowCount > fMaxRows) rowCount = fMaxRows;
	else if (rowCount < 1) rowCount = 1;

	constrainedDim.Y(rowCount * fCellHeight);
	
	return constrainedDim;

}

/* CalculateRowsColumns
*/
void TableCellData::CalculateRowsColumns(void)
{
	do{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		if(panelData == nil) break;

		InterfacePtr<IControlView> pTableCellView(panelData->FindWidget(kTableCellWidgetID) , UseDefaultIID());
		if(pTableCellView == nil ) break;
		
		PMReal height = pTableCellView->GetFrame().Height();
		PMReal width = pTableCellView->GetFrame().Width();
		
		if (width < kPanelWidth)
			width = kPanelWidth;
		else if (width > 1000)
			 width = 1000;

		if (height < kPanelHeight)
			height = kPanelHeight;
		else if (height > 1000)
			height = 1000;
		
		int32 newNumberOfRows = ::ToInt32(height) / fCellHeight;
		int32 newNumberOfColumns = ::ToInt32(width) / fCellWidth;

		if (newNumberOfRows < 1) newNumberOfRows = 1;
		if (newNumberOfColumns < 1) newNumberOfColumns = 1;
		
		if ((newNumberOfRows != fNumberOfRows) || (newNumberOfColumns != fNumberOfColumns))
		{
			PreDirty ();
			fNumberOfRows = newNumberOfRows;
			fNumberOfColumns = newNumberOfColumns;
		
			 // This is create from DEFINE_HELPER_METHODS macro.
		}
	}while(false);
}

// End, TableCellData.cpp.

