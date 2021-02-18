//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableFrame.h $
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
#ifndef __ITableFrame__
#define __ITableFrame__

#include "PMRect.h"
#include "PMMatrix.h"
#include "TablesID.h"
#include "TableTypes.h"
#include "CellParcelIterator.h"
#include "K2SmartPtr.h"
#include "ParcelKey.h"
#include "ITableLayout.h"

//-----------------------------------
//	Forward References
//
class IParcel;
class IParcelList;
class ITableModel;
class ITextFrameColumn;
class TableLayout;

// ===================================================================================
//	class ITableFrame
// ===================================================================================
/** Maintains geometry information associated with a table frame.
	See kTableModelBoss.
*/
class ITableFrame : public IPMUnknown {
//-----------------------------------
//	API
//
public:

	// ----- Constants -----
	enum {kDefaultIID = IID_ITABLEFRAME};
	/** Identifies Cell areas */
	enum ECellArea {
					/** Parcel bounds, the area content composed into */
					kParcel,
					kContent = kParcel,
					/** path area inset by half the stroke weight */
					kInnerStroke,
					kInnerFrame = kInnerStroke,
					/** center of the stroke */
					kPath,
					kFrame = kPath,
					/** path area ouset by half the stroke weight */
					kOuterStroke,
					kOuterFrame = kOuterStroke
					};

	// ----- Model -----
	/** Query for the associated table model.
		@return reference-incremented interface ptr to the associated table model
	*/
	virtual ITableModel* QueryModel() const = 0;

	/** Accessor for the table model, returning a persistent UIDRef. This can be used to acquire an ITableModel
		interface.
		@return	UIDRef	the model
	*/
	virtual UIDRef 		GetModelRef() const = 0;

	/**
		Sets the modes
		@param	table
		@postcondition self.QueryModel() = this
	*/
	virtual void 		SetModel(const ITableModel* table) = 0;

	//
	// ----- Frame -----

	/** Determine if this is the first frame in the given table model.
		@return kTrue if this is the first frame. kFalse if not.
	*/
	virtual bool16		IsFirstFrame(void) const = 0;

	/** Returns true if the table frame is composed and all of its information
		is still valid. Returns false if the frame is damaged.
	*/
	virtual bool16 		IsValid() const = 0;

	/**
	The TableFrame coordinate system has (0,0) as the value at the top
	left corner of the Stroke Bounds.  Note that this includes
	all of the stroke line around the frame.
	@precondition self.IsValid()
	*/
	virtual PMRect 		GetStrokeBoundingBox() const = 0;

	/**
	In TableFrame coordinates.
	Note that this does not include the stroke line around the frame.
	@precondition self.IsValid()
	*/
	virtual PMRect 		GetPathBoundingBox() const = 0;

	/**
	In TableFrame coordinates.
	Note that this includes all of the stroke line around the frame and the
	union of all the cells InkBounds.
	@precondition self.IsValid()
	*/
	virtual PMRect 		GetInkBounds() const = 0;

	/** Returns true if this table frame contains the give CellParcelAddr

	 	@param		CellParcelAddr element to check
	 	@return		true if elements is contained by the frame
	*/
	virtual bool16		Contains(const CellParcelAddr& element) const = 0;


	/** Acquire a persistent reference to the text frame associated with this table frame.
		@return persistent reference to associated text frame
	*/
	virtual UIDRef		GetFrameRef() const = 0;

	/** Query for the text frame associated with this table frame.
		@return reference-incremented ptr to text frame associated with this table frame
		@precondition self.GetParcelKey().IsValid()
	*/
	virtual ITextFrameColumn* QueryFrame() const = 0;

	/** Returns the Parcel Key for this Table Frame
	*/
	virtual ParcelKey	GetParcelKey() const = 0;

	/** Query for the Parcel associated with this table frame.
		@return reference-incremented ptr to Parcel associated with this table frame
		@precondition self.GetParcelKey().IsValid()
	*/
	virtual IParcel* QueryParcel() const = 0;

	/** Returns the Matrix needed to transform a table frame coord to a Parcel
	coord
	*/
	virtual PMMatrix	GetToParcelMatrix() const = 0;
	
	/** Returns the Matrix needed to transform a table frame coord to a text
	frame coord
	*/
	virtual PMMatrix	GetToFrameMatrix() const = 0;
	
	/** Returns the Matrix needed to transform a table frame coord to a
	pasteboard point
	*/
	virtual PMMatrix	GetToPasteboardMatrix() const = 0;

	// ----- Cells -----
	/**
		Returns a PMRect in TableFrame coordinates corresponding to the selected area depending on what is passed in
		
		@param	anchor	the model anchor of the cell we are trying to get the area of
		@param	area  	kParcel, kInnerStroke, kPath -- what bounds the area returned should have
		
		@precondition self.IsValid()
		@precondition table.IsAnchor(anchor)
		@precondition self.Contains(anchor)
		@postcondition self.GetStrokeBoundingBox().RectIn(result);
		anchor.col > anchor2.col implies <br>
		&nbsp;&nbsp;result.left > self.GetCellArea(anchor2).left<br>
		and anchor.row > anchor2.row implies <br>
		&nbsp;&nbsp;result.top > self.GetCellArea(anchor2).top<br>
	*/
	virtual PMRect 		GetCellBounds(const GridAddress& anchor, ECellArea area = kContent) const = 0;

	/** Nested HitTestData class holds information about where point hit a table frame.
		Created and returned by ITableFrame::HitTest.
	*/
	class HitTestData
	{
	protected:
		PUBLIC_DECL		HitTestData();
		PUBLIC_DECL		HitTestData(const HitTestData&);
	public:
		virtual			~HitTestData() { }

		// cell corners
		enum CNearestCorner
		{
			kTopLeft,
			kBottomLeft,
			kTopRight,
			kBottomRight
		};

		// -- accessors --
		virtual CellParcelAddr GetCellParcelAddr() const = 0;
		/** Returns cell address of the cell element which was hit -- this could be a non-anchor */
		virtual GridAddress	GetElementAddress() const = 0;
		virtual CNearestCorner		GetNearestCorner() const = 0;
		virtual ITableLayout::const_row_iterator GetLayoutRowIter() const = 0;
		virtual bool16	IsInternalCellHit() const= 0;
		virtual bool16	IsTopCellHit() const= 0;
		virtual bool16	IsBottomCellHit() const= 0;
		virtual bool16	IsLeftCellHit() const= 0;
		virtual bool16	IsRightCellHit() const= 0;
		virtual bool16	IsTopLeftCellHit() const= 0;
		virtual bool16	IsTopRightCellHit() const= 0;
		virtual bool16	IsBottomLeftCellHit() const= 0;
		virtual bool16	IsBottomRightCellHit() const= 0;
		virtual bool16	IsElementHit() const = 0;
		virtual bool16	IsTopCellStrokeHit() const = 0;
		virtual bool16	IsBottomCellStrokeHit() const = 0;
		virtual bool16	IsLeftCellStrokeHit() const = 0;
		virtual bool16	IsRightCellStrokeHit() const = 0;
		virtual bool16	IsTopLeftCellStrokeHit() const = 0;
		virtual bool16	IsTopRightCellStrokeHit() const = 0;
		virtual bool16	IsBottomLeftCellStrokeHit() const = 0;
		virtual bool16	IsBottomRightCellStrokeHit() const = 0;
		virtual bool16	IsInternalStrokeHit() const = 0;
		virtual bool16	IsTopFrameSideHit() const = 0;
		virtual bool16	IsBottomFrameSideHit() const = 0;
		virtual bool16	IsLeftFrameSideHit() const = 0;
		virtual bool16	IsRightFrameSideHit() const = 0;
		virtual bool16	IsTopLeftFrameCornerHit() const = 0;
		virtual bool16	IsTopRightFrameCornerHit() const = 0;
		virtual bool16	IsBottomLeftFrameCornerHit() const = 0;
		virtual bool16	IsBottomRightFrameCornerHit() const = 0;

		// where hit in cell
		enum ECellHitArea { kNone = -1, kInCell, kTopStroke, kRightStroke, kBottomStroke,
							kLeftStroke, kTopLeftStroke, kTopRightStroke,
							kBottomLeftStroke, kBottomRightStroke };

 		// sets location hit in cell, used by Frame/CellCallbackPolicy
		virtual void	SetCellHitArea(const ECellHitArea newCellLoc) = 0;

		// sets the nearest cell corner of the hit coordinate
		virtual void SetNearestCorner(CNearestCorner nearCorner) = 0;

	};

	/** Nested call-back class for applying policy to make hitting corners/sides of frame/cell easier.
	*/
	struct HitTestPolicyCallback
	{
		/**
			@param pt			point in tableFrame coords
			@param tableFrame	table frame so can get frame/content/ink bounds
			@param hitData		struct to modify so think hitting corners/sides of frame/cell
		*/
		virtual void operator()(const PMPoint& pt, const ITableFrame* tableFrame, HitTestData* hitData) = 0;
	};

	/** Determine which row/column, parcel, stroke the given point would lie in.

		@param pt location to hit test, is given in inner (text frame) coordinates
		@precondition self.IsValid()
		@precondition self.GetStrokeBoundingBox().PointIn(pt)			-- pt is in inner (text frame) coordinates
		@postcondition result.loc = kHitElement implies <br>&nbsp;&nbsp;self.GetCellArea(table.FindCellAnchor(result.row, result.col), kFrame).Contains(pt)
		@postcondition valid grid address
		@postcondition is parcel address in frame
		@postcondition is valid layout row in frame MCHENG_Unimplemented

	*/
	virtual HitTestData*	HitTest(const PMPoint& pt, HitTestPolicyCallback* framePolicy, HitTestPolicyCallback* cellPolicy) const = 0;

	/** Returns true if the given ITableLayout::Row's top is closed  
	 **
	 ** @param row					layout row to check
	 ** @return bool16					true if the top is closed
	 ** @precondition					this->ContainsRow(row)
	 **/
	virtual bool16	IsRowTopClosed(const ITableLayout::Row& row) const = 0;

	/** Returns true if the given ITableLayout::Row's bottom is closed 
	 **
	 ** @param row					layout row to check
	 ** @return bool16					true if the bottom is closed
	 ** @precondition					this->ContainsRow(row)
	 **/
	virtual bool16	IsRowBottomClosed(const ITableLayout::Row& row) const = 0;

	/** Returns the columns in this table frame
	 **
	 ** @return ColRange				Columns contained by this frame
     **/
	virtual const ColRange	GetColumns() const = 0;

	/** Returns true if the table frame contains this model column
	 **
	 ** @param int32		column to check if it contained by this frame
	 ** @precondition		column is contained by the table model
	 **/
	virtual bool16	ContainsColumn(const int32 col) const = 0; 

	/** Returns true if the table frame contains this layout row
	 **
	 ** @param row		layout row to check if it contained by this frame
	 ** @precondition		this->ContainsModelRow(row->GetModelRow())
	 **/
	virtual bool16	ContainsRow(const ITableLayout::Row& row) const = 0; 

	/** Returns true if the table frame contains this model row
	 **
	 ** @param row		layout row to check if it contained by this frame
	 ** @precondition		row is contained by the table model
	 **/
	virtual bool16	ContainsModelRow(const GridCoord row) const = 0; 

	/** Returns true if the table frame intersects any portion of the area
	 **
	 ** @param area		area to use to check for an intersection
	 ** @precondition		area is contained by the table model
	 **/
	virtual bool16 	IntersectsModelArea(const GridArea& area) const = 0;

	/** Returns true if the table frame intersects any portion of the area
	 **
	 ** @param area		area to use to check if contained by this table frame
	 ** @precondition		area is contained by the table model
	 **/
	virtual bool16 	ContainsModelArea(const GridArea& area) const = 0;

	/** Returns the number of layout rows this frame contains
	 **
	 ** @return int32		number of rows in the frame
	*/ 
	virtual const int32 	GetNumRowsInFrame() const = 0;

	/** Gets the model GridCoord of the first row in the frame
	 **
	 ** @return GridCoord	The model coordinate of the top row in this frame
	 **
	 ** NOTE:  Do not combine this with GetFrameBottomRowModelCoord() and expect to get a
	 **		   contiguous area of all cells in the Table Frame
	*/
	virtual const GridCoord	GetFrameTopRowModelCoord() const = 0;

	/** Gets the model GridCoord of the last row in the frame
	 **
	 ** @return GridCoord	The model coordinate of the bottom row in this frame
	 **
	 ** NOTE:  Do not combine this with GetFrameTopRowModelCoord() and expect to get a
	 **		   contiguous area of all cells in the Table Frame
	*/
	virtual const GridCoord	GetFrameBottomRowModelCoord() const = 0;

	/** Returns kTrue if the new ModelRows composed in this TableFrame are from different Row Ranges (Header/SubHeader/Body/Footer).
	 ** @param mR1 GridCoord of a ModelRow that is composed in this Frame.
	 ** @param mR2 GridCoord of a ModelRow that is composed in this Frame.
	 **/
	virtual bool16	GetAreRowsInSameRange(GridCoord mR1, GridCoord mR2) const = 0;
	
	/** Returns a vector where each entry is contained in a separate section of the TableModel
	   @precondition	IntersectsModelArea(area)
	   @postcondition	Vector's size is > 0 and < 3:  3 is the number of sections in the TableModel (headers,body,footers)
	*/
	virtual K2Vector<GridArea>*  	CreateSectionAreasIntersectingFrame(const GridArea& area) const = 0;


	/** Returns the parcel of the cell that is in this frame (each cell only has one of its parcels in a TableFrame) 
	*/
	virtual ParcelKey	GetParcelInFrame(const GridAddress anchor) const = 0;

	//-------------------------------------------------------------------------------	
	/**@name	Iteration  */
	//@{-----------------------------------------------------------------------------
							/** Used to traverse through the CellParcelAddr contained by
								this table frame */
	typedef CellParcelIterator<ITableFrame>		 const_parcel_iterator;

							/** Use to acquire  an iterator that refers to the parcel at the start of this table frame
							*/
	virtual const_parcel_iterator				begin_parcel_iter() const = 0;

							/** Use to acquire  an iterator that refers to the parcel one more then the 
							    end of this table frame
							*/
	virtual const_parcel_iterator				end_parcel_iter() const = 0;


							/** Used to traverse through the CellParcelAddr contained by
								this table frame */
	typedef ITableLayout::const_row_iterator	const_frame_row_iterator;

							/** Use to acquire  an iterator that refers to the ITableLayout::Row at the 
								beginning of this table frame
							*/
	virtual const_frame_row_iterator			begin_frame_row_iter() const = 0;

							/** Use to acquire  an iterator that refers to the ITableLayout::Row at the 
								given row in this table frame

								@precondition:  Row contained by table frame
							*/
	virtual const_frame_row_iterator			begin_frame_row_iter_at(GridCoord modelRow) const = 0;

							/** Use to acquire  an iterator that is 1+ the end of the TableFrame
							*/
	virtual const_frame_row_iterator			end_frame_row_iter() const = 0;

	/**
		Converts this table frame from the InDesign 2.0 format
		called ONLY during conversion
	*/
	virtual void			ConvertFromAnna(TableLayout* layout) = 0;

};

#endif // __ITableFrame__
