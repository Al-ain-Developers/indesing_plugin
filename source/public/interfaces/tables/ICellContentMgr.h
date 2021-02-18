//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellContentMgr.h $
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
#ifndef __ICellContentMgr__
#define __ICellContentMgr__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

//-----------------------------------
//	Forward References
//
class ITableModel;
class TableMementoPiece;

/** Abstract interface, exposes API for creating and destroying cell bosses.
	See ITableStrand and ITableModel for more information on the table-model specific API.
*/
class ICellContentMgr : public IPMUnknown {

//-----------------------------------
//	API
//
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ICELLCONTENTMGR};
	
	enum ECreateRelative { eNone, eLeft, eRight, eTop, eBottom };

	/**@name  Main API */
	//@{-----------------------------------------------------------------------------

	/** Called by core when cell-content boss objects should be created. 
		
		For instance, in a 4x4 table a call to 
		ITableModel::InsertRows(RowRange(2,3), eAfter) will result in a call to 
		ICellContentManager::Create(GridArea(3,0,6,4), eTop).
		The text content manager might use
		this info to propagate text attributes of row 2 to the newly created text content for 
		row 3 through 6.

		@param area
		@param relative
		enum is used to indicate which edge
		of the GridArea the creation is relative to. The content manager may use this to decide
		how to propagate attributes of the content. 
		
	
		@precondition area.forall(anchors | area.Contains(self.GetModel()->GetCellArea(anchor))
		@precondition  area.forall(anchors | self.GetModel()->GetCellType(anchor) == self.GetType())
					
		@postcondition  Content bosses and other resource associated with content are created.
	*/
	virtual void		Create(const GridArea& area, const ECreateRelative relative) = 0;

	/**
		@precondition area.forall(anchors | area.Contains(self.GetModel()->GetCellArea(anchor))
		@precondition area.forall(anchors | self.GetModel()->GetCellType(anchor) == self.GetType())
		@postcondition All content and content bosses of cells managed by this cell content
						manager are destroyed.
	*/
	virtual void 		Destroy(const GridArea& area) = 0;	
					
	/**  Returns a user readable description of the content
		type, eg "Text", "Image", etc.
	*/
	virtual PMString 	GetName() const = 0;
					
	/** Returns type described cell-content type. Existing possibilities are 
		e.g. kNoContentType, kTextContentType. Note: CellType is effectively alias of ClassID.
	*/
	virtual CellType 	GetType() const = 0;
	//@}-----------------------------------------------------------------------------


 	/**@name  Table model specific API */
	//@{-----------------------------------------------------------------------------

	/** @return the ImplementationID of the implementing class, 
			e.g. kTextICellContentMgrImpl for existing text cell content type
	*/
	virtual ImplementationID	GetKey() const = 0;

	/** 
	*/
	virtual	void				AttachingToTableModel(UID modelUID) = 0;
	
	/** Take copy of underlying content associated with given cells.
		@param cells operate on cells contained wholly within this area
		@return memento that can be used in subsequent Paste operation
	*/
	virtual TableMementoPiece*	Copy	(const GridArea& cells) const = 0;

	/** Remove underlying content associated with given area, returning a memento for pasting. Final state is as if a Destroy() was performed.
		@param cells operate on cells contained wholly within this area
		@return memento that can be used in subsequent Paste operation
	*/
	virtual TableMementoPiece*	Cut		(const GridArea& cells) = 0;

	/** Pre-condition to calling self.Clear
		@param cells operate on cells contained wholly within this area
	*/
	virtual bool16 				CanClear(const GridArea& cells) const = 0;

	/** Remove underlying content associated with given area. Pre: self.CanClear
		@param cells operate on cells contained wholly within this area
	*/
	virtual void				Clear	(const GridArea& cells) = 0;

	/** This should be called before calling paste. It creates the content for pasting. 
		@param atAnchor specifying location in table where content to be pasted
		@param piece memento from previous cut or copy operation
	*/
	virtual void				PrePaste	(const GridAddress& atAnchor, TableMementoPiece* piece) = 0;

	/** Add  underlying content mapping to given location in table. PrePaste should be called before calling paste
		@param atAnchor specifying location in table where content to be pasted
		@param piece memento from previous cut or copy operation
		@param notificationPiece notification memento from previous cut or copy operation
	*/
	virtual void				Paste	(const GridAddress& atAnchor, TableMementoPiece* piece, TableMementoPiece* notificationPiece = nil) = 0;

	/** 
		@param return reference-count incremented pointer to table model associated with this 
	*/
	virtual ITableModel*		QueryTableModel(void) const = 0;

	/** Called to concatenate the content of cells to be merged.

		@precondition self.GetModel()->GetCellType(cells.GetTopLeft) == self.GetType())
		@postcondition If possible the content manager makes cells.GetTopLeft contain
		concatenated content of all anchors in cells that have a CellType
		of self.GetType. This is primarily used for merge cells behavior.
	*/
	virtual void				ConcatenateContentForMerge(const GridArea& cells) = 0;

	/** Processes commands to scale the content of cells.
		@param cells
		@param xScale
		@param yScale
	*/
	virtual ErrorCode			Scale(const PMReal& xScale, const PMReal& yScale) = 0;
	
	/** Called before calling concatenating the content of cells to be merged.
		The content managers can preserve data with appropriate conversion, if possible.

		@param	cells: cells which are going to be merged
		@param	cell type: cell type of the final merged cell
	*/
	virtual void				PreConcatenateContentForMerge(const GridArea& cells, const CellType& mergedCellType) = 0;

	/** Called before converting the type of cell
	It will return the UID of object to be preserved during conversion

	@param	cell: cell which is going to be converted
	@param	destType: cell type to which cell will be converted
	@return UID: UID of object that is present in the cell, and needs to be preserved during conversion.
	*/
	virtual UID					PreConvertExtractData( GridAddress cell, const CellType destType ) = 0;

	/** Called after converting the type of cell
	The content managers can preserve data with appropriate conversion, if possible.
	After converting cell type, the preserved object need to be push into the cell.

	@param	cell: cell which is going to be converted
	@param	UID: UID of object that needs to be inserted in the cell, if possible, after cell type conversion.
	*/
	virtual void				PostConvertPushData( GridAddress cell, UID data ) = 0;

};


#endif // __ICellContentMgr__
