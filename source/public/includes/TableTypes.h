//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TableTypes.h $
//  
//  Owner: Joe Shankar
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
//  Purpose: Base types for tables.
//  
//========================================================================================

#pragma once
#ifndef __TableTypes__
#define __TableTypes__

#include <algorithm>

#include "IPMStream.h"
#include "K2Vector.h"
#include "ParcelKey.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

template <class T>
inline void UNUSED(const volatile T&)	{}		// Note that this generates no code on Mac or Win (if inlining is on).


//-----------------------------------
//	Forward References
//
class GridAddress;
class GridArea;
class GridID;
class RowRange;
class ColRange;
class CellParcelAddr;
//-----------------------------------
//	Types
//
typedef int32 GridCoord;		//	Row or column number

namespace Tables
{
	enum ECellEdge	{eLeft, eRight, eTop, eBottom};

	enum ERowColumn { eRow, eColumn };

	/** Used for InsertRows & InsertColumns in tables API.
	*/
	enum ERelativePosition { eBefore, eAfter };

	/** This enum is used to determine if structure & attributes need
		to be propagated due to insertion of rows and columns. The
		ERelativePosition enum is used in the InsertRow/Column calls
		to pick the row or column the propagation of attributes happens from.*/
	enum EContinuation {
		eStructureAllAttrs,		// content and table attributes
		eStructureTableAttrs,	// no content attributes
		eNoStructureAllAttrs	// content and table attributes, not not struct
	 };

	/** Used in specifying the sides when setting attributes
		like stroke weight/colour for cells.
	*/
	enum ESelectionSides {
			eNoSides		= 0,
			eLeftSide 		= 1,
			eRightSide		= 2,
			eTopSide		= 4,
			eBottomSide		= 8,
			eInteriorRows	= 16,
			eInteriorCols	= 32,
			eAllSides		= 63
	};

	enum ERowStartAtValue {
			eStartAnywhere		= 0,
			eStartNextColumn	= 2,
			eStartNextFrame		= 3,
			eStartNextPage		= 4,
			eStartNextOddPage	= 5,
			eStartNextEvenPage	= 6
	};

	enum EHeaderFootersBreakValues {
			eStartEachTextColumn	= 0,
			eStartEachTextFrame		= 1,
			eStartEachPage			= 2
	};

	enum EStrokeDrawingOrder {
			eBestJoins			= 0,
			eRowOnTop	= 1,
			eColumnOnTop		= 2,
			eInDesign2Compatibility			= 3
	};

	enum EDirection {eLTR, eRTL};

	inline ESelectionSides	operator|(ESelectionSides first, ESelectionSides second)
	{
		ASSERT(first  >= eNoSides && first  <= eAllSides);
		ASSERT(second >= eNoSides && second <= eAllSides);

		ESelectionSides result = (ESelectionSides)((uint32)first | (uint32)second);

		ASSERT(result >= eNoSides && result <= eAllSides);
		return result;
	};
}

typedef K2Vector<uint32>			GridIDCollection;
typedef K2Vector<GridIDCollection*>	GridIDCollectionVector;

typedef ClassID CellType;

//-----------------------------------
//	Constants
//
PUBLIC_DECL extern const GridID		 	kInvalidGridID;
PUBLIC_DECL extern const GridAddress 	kBadGridAddress;
PUBLIC_DECL extern const GridCoord	 	kBadCoord;
PUBLIC_DECL extern const GridArea	 	kZeroGridArea;
PUBLIC_DECL extern const CellParcelAddr	kBadParcelAddr;
PUBLIC_DECL extern const CellType 		kNoContentType;

//===================================================================================
// class GridAddress
/**  Row and column of an element in the underlying grid of the table model. The underlying
	grid provides the co-ordinate system for tables.

	A grid address is specified on the grid underlying a table. The units of the underlying grid
	are grid-elements; table-cells are composites of grid-elements, consisting
	of 1 (if they have a 'trivial' or unit GridSpan)
	or more grid-elements. The grid-address for a cell is specified in terms
	of the grid-address of its anchor or top-left.

	If a single cell is split vertically, then this increases the resolution of the underlying
	grid in the horizontal direction. The grid-lines are not uniformly distributed, although it is a
	rectilinear grid for tables within InDesign 2.0.

	To determine what row a particular cell in can become quite complex in a table with many split
	and merged cells; that is, tables with many non-trivial GridSpans.
	The notional algorithm to determine the GridAddress for a particular cell is straightforward;
	<ol>
	<li>Determine the resolution of the underlying grid. For the horizontal direction, this can be
	calculated by projecting all the vertical edges to the x-axis (top of the table). Similarly for
	the vertical direction, project all the horizontal edges to the y-axis (left of the table).
	<li>Calculate the co-ordinates on this grid.
	</ol>

	<img src="table_structure_example.gif" width="366" height="237">

	@author 	Joe Shankar
	@see		ITableModel
 */
//===================================================================================
class PUBLIC_DECL GridAddress {

public:
	/** Specifies that this is a plain data type for K2Vector and no specialised copy semantics are required.
	*/
	typedef base_type data_type;

					/**
						No-args constructor.
					*/
					GridAddress() : row(kBadCoord), col(kBadCoord)	{}
					/** Constructor.
						@param	inRow specifies row in which top-left of the cell is located
						@param	inCol specifies the column in which top-left of the cell is located
					*/
					GridAddress(GridCoord inRow, GridCoord inCol) : row(inRow), col(inCol)	{}

	/** Mutator.
		@param	inRow specifies the new row.
		@param	inCol specifies the new column.
	 */
	void 			Set(GridCoord inRow, GridCoord inCol)		{row = inRow; col = inCol;}

	/** Overload of addition operator..
		Semantics: results is a new location with 'this' location offset by the location of the second.
		@param	rhs right hand operand.

	*/
	GridAddress 	operator+(const GridAddress& rhs) const		{return GridAddress(row + rhs.row, col + rhs.col);}

	/** Overload of sutraction operator.
		Semantics: would give a new location for 'this' object expressed relative to the rhs operand. Clearly, if
		the '<' operator returns false, then the resulting GridAddress from this '-'
		operation will be outside the real table.
		@param	rhs right hand operand.

	*/
	GridAddress 	operator-(const GridAddress& rhs) const		{return GridAddress(row - rhs.row, col - rhs.col);}

	/** Overload of operator addition assignment.
		Would have effect of offsetting the current GridAddress by specified argument.
		@param	rhs right hand operand.

	*/
	GridAddress& 	operator+=(const GridAddress& rhs)			{row += rhs.row; col += rhs.col; return *this;}

	/** Overload of operator subtraction assignment.
		Would have effect of re-expressing the current location in frame of reference determined by the rhs operand.
		@param	rhs right hand operand.

	*/
	GridAddress&	operator-=(const GridAddress& rhs)			{row -= rhs.row; col -= rhs.col; return *this;}

	/** Overload of equality relational operator. Semantics; this address identical with another iff
		the row and columns represented by each are identical.
		@param	rhs right hand operand.
		@return kTrue if this and the comparand GridAddress refer to the same row and column, kFalse otherwise
	*/
	bool16 			operator ==(const GridAddress& rhs) const	{return row == rhs.row && col == rhs.col;}

	/** Overload of not-equal operator.
		@param	rhs right hand operand.

	*/
	bool16 			operator !=(const GridAddress& rhs) const	{return row != rhs.row || col != rhs.col;}

	/** Overload of less than operator.
		Semantics: allows two GridAddresses
		to be compared to see which is nearer the top of the table, and then if they are in the same
		row, to see which is nearer to the left of the table.
		@param	rhs right hand operand.

	*/
	bool16 			operator < (const GridAddress& rhs) const	{return row < rhs.row || (row == rhs.row  && col < rhs.col);}

	/**
		Overload of less than or equal to operator.
		@param	rhs right hand operand.
		@return kTrue if the comparand (rhs) is below this location, or kTrue if it is in the same row, to the right
				of this cell, kFalse otherwise.
	*/
	bool16 			operator <=(const GridAddress& rhs) const	{return row < rhs.row || (row == rhs.row  && col <= rhs.col);}

	/** Overload of operator greater than.
		Semantics; this grid-address is 'greater' than the rhs if it is in a row that is lower in
		the table than this address, or if in the same row, if it is to the right.
		@param	rhs right hand operand.

	*/
	bool16 			operator > (const GridAddress& rhs) const	{return row > rhs.row || (row == rhs.row  && col >  rhs.col);}

	/** Overload of operator greater than or equal to operator.
		Semantics; this grid-address is gte rhs iff it is in a row below this or if in the same row,
		in a column that is the same or rightmost of the column represented in this address.
		@param	rhs right hand operand.
		@return kTrue if the rhs location is in a row below this object,
				or kTrue if it is in a column to the right of the current location, kFalse otherwise.

	*/
	bool16 			operator >=(const GridAddress& rhs) const	{return row > rhs.row || (row == rhs.row  && col >= rhs.col);}

	/** Used to persist the state of an object of this type.
		@param	stream refers to the stream to/from which the state is serialised or deserialised.

	*/
	void 			ReadWrite(IPMStream* stream)				{stream->XferInt32(row); stream->XferInt32(col);}

public:
	/** Represents the row co-ordinate.
		The rows are zero-based and the row co-ordinate increases from the top of the table downwards.
	*/
	GridCoord row;
	/** Represents the column co-ordinate.
		Columns are zero-based and the column co-ordinate increases from the left hand edge rightwards.
	*/
	GridCoord col;
};


//===================================================================================
// class GridID
/**
	Represents the 'id' of a grid element in the table model.
	The API on ITableModel allows conversion
	between GridAddress and GridID; a GridID for a cell is unique within a particular table.
	It is used in contexts such as the story-thread dictionary as a lookup key to determine the text
	thread associated with a particular cell.

	@author 	Joe Shankar
	@see		ITableModel::GetGridID
 */
//===================================================================================
class PUBLIC_DECL GridID {
public:
	/** Constructor.
		@param id specifies the identifier to associate with this instance
	*/
	explicit GridID(uint32 id = 0) : fGridID(id) 	{}
	/** Overload of a type conversion operator.
		@return the value of this type as an unsigned int32
	*/
	operator uint32() const 						{return fGridID;}
private:
	uint32 fGridID;
};


//===================================================================================
// class GridSpan
/**	Row and column span of cells.

	@author 	Joe Shankar
	@see		ITableModel
 */
//===================================================================================
class PUBLIC_DECL GridSpan {

public:
	/**
		For K2Vector. Specifies that this is a data class that has
        no specialised copy semantics- shallow copy of the fields is enough to copy state of an instance.
	*/
	typedef base_type data_type;

			/**
				No-args constructor.
             */
  			GridSpan() : height(1), width(1)	{}			// $$$ better to initialize to -1?
			/**
				Constructor.
				@param inHeight specifies the rows spanned
				@param inWidth specifies the columns spanned
			 */
			GridSpan(int32 inHeight, int32 inWidth) : height(inHeight), width(inWidth)	{}

	/** Mutator.
		@param inHeight rows spanned
		@param inWidth columns spanned
    */
	void 	Set(int32 inHeight, int32 inWidth)		{height = inHeight; width = inWidth;}

	/**
		Determine if this is a 'trivial' or unit span.
		@return kTrue if unit span(1,1), kFalse otherwise
	 */
	bool16 	IsUnitSpan() const						{return height == 1 && width == 1;}

	/** Query to determine if both the row and column spans are zero.
		@return kTrue if this is an empty span, with both row and column span of zero, kFalse otherwise
	*/
	bool16 	IsEmpty() const							{return height == 0 || width == 0;}

	/**
		Overload of equality comparison operator. Semantics; this and rhs span are identical
		iff the height and width of both are identical.
		@return kTrue if the width and height of this and
		comparand grid-spans are equal, kFalse otherwise
	 */
	bool16	operator ==(const GridSpan& rhs) const	{return height == rhs.height && width == rhs.width;}
	/**
		Overload of not-equal operator. Semantics; if this span and the rhs differ in height or width then
		they are not identical.
		@return kTrue if width or height of this and comparand
			grid-span objects differ, kFalse otherwise
	 */
	bool16 	operator !=(const GridSpan& rhs) const	{return height != rhs.height || width != rhs.width;}

	void 	ReadWrite(IPMStream* stream)			{stream->XferInt32(height); stream->XferInt32(width);}

public:
	/** Represents the count of rows spanned. */
	int32		height;
	/** Represents the count of columns spanned */
	int32		width;
};


//===================================================================================
// class GridArea
/**
	Represents a rectangle of grid elements in the table model.
	The bottom and right elements are not included to allow for an empty GridArea.

	The best way to think of this is that the GridCoord's refer to the vertices
	instead of cells. The cells are the area inside the vertices. For example,
	the first cell's topLeft is (0, 0) and the bottom right is (1, 1).

	@author 	Joe Shankar
	@see		ITableModel
 */
//===================================================================================
class PUBLIC_DECL GridArea {

public:
	/** For K2Vector, specifying that this is a data class that does not
	 *  have specialised copy semantics. A shallow field-wise copy is sufficient to clone an instance of this class.
	 */
	typedef base_type data_type;

	// ----- Constructors -----
				/** No-args constructor */
				GridArea();

				/**
					@param	topRow
					@param	leftCol
					@param	bottomRow
					@param right

				*/
				GridArea(GridCoord topRow, GridCoord leftCol, GridCoord bottomRow, GridCoord right);

				/** Constructor.
					@param	topLeftElement specifies a top left element in the underlying grid for this area
					@param	bottomRightElement specifies the bottom right element in the underlying grid that is
					in the row just below and just right of the area to cover in the underlying grid.

				*/
				GridArea(const GridAddress& topLeftElement, const GridAddress& bottomRightElement);

				/** Constructor.
					@param	anchor specifies location of the top-left of the new area
					@param	span specifies the height and width of the new area

				*/
				GridArea(const GridAddress& anchor, const GridSpan& span);

				/** Constructor.
					@param rows specifies the RowRange that this area should cover
					@param cols specifies the ColRange that the area should cover
				*/
				GridArea(const RowRange& rows, const ColRange& cols);

	void 		Set(GridCoord topRow, GridCoord leftCol, GridCoord bottomRow, GridCoord right);

	// ----- Corners -----
	/** @return co-ordinates of the top left vertex of the area as a GridAddress
	*/
	GridAddress	GetTopLeft() const						{return GridAddress(topRow, leftCol);}

	/** This query can be thought of as either; returning the location of the element in the underlying
		grid that is just below and right of the area covered in the grid, or as the location
		of the lower right vertex of this area.
		@return the co-ordinates of the bottom right vertex of the area as a GridAddress
	*/
	GridAddress	GetBottomRight() const					{return GridAddress(bottomRow, rightCol);}

	/** Location of the top-left element of this area in the underlying grid.
		@return a GridAddress representing the location of the
		top-left element in the
		underlying grid covered by this area.
	*/
	GridAddress	GetTopLeftElem() const					{return this->GetTopLeft();}

	/** Location of the top-right element of this area in the underlying grid.
		@return a GridAddress representing the location
		of the top-right element in the
		underlying grid covered by this area.
	*/
	GridAddress	GetTopRightElem() const					{return GridAddress(topRow, rightCol-1);}

	/** Location of the bottom left element in the underlying grid that is contained within this area.
		@return a GridAddress representing the location of the
		element on the underlying grid that is in the lower left corner of this area.
	*/
	GridAddress	GetBottomLeftElem() const				{return GridAddress(bottomRow-1, leftCol);}

	/** Location of the bottom right element contained in this area
		this area in the underlying grid.
		@return a GridAddress representing the location of the
		element on the underlying grid that is just below and to the right of this area.
	*/
	GridAddress	GetBottomRightElem() const				{return GridAddress(bottomRow-1, rightCol-1);}

	/** Mutator for the top vertex of this region.
		@param tl specifies location for new top left vertex for this area
	*/
	void		SetTopLeft	  (const GridAddress& tl)	{topRow  = tl.row; leftCol = tl.col;}

	/** Mutator for the bottom right vertex of this region.
		@param br specifies the location of the new bottom right vertex for this region.
	*/
	void		SetBottomRight(const GridAddress& br)	{bottomRow = br.row; rightCol  = br.col;}

	/** Query for the rows covered by this area.
		@return rows covered by this area as a RowRange
	*/
	inline RowRange	GetRows() const;

	/** Query for the columns covered by this area.
		@return columns covered as a ColRange
	*/
	inline ColRange	GetCols() const;

	// ----- Dimensions -----
	/** @return the dimension of this area as a GridSpan
	*/
	GridSpan 	GetSpan() const							{return GridSpan(bottomRow - topRow, rightCol - leftCol);}

	/** @return the width of this area in columns spanned
	*/
	int32	 	Width() const							{return rightCol - leftCol;}

	/** @return the height of this area, as a count of the rows spanned
	*/
	int32	 	Height() const							{return bottomRow - topRow;}

	/** @return kTrue if this covers no area within the underlying grid, kFalse if there
		is a finite area covered
	*/
	bool16 		IsEmpty() const							{return leftCol >= rightCol || topRow >= bottomRow;}

	// ----- Operations -----
	/** Overload of operator bitwise-and, to mean 'intersect'.
		@param rhs area to take intersection with
		@return an area that represents the intersection of the given area and this area
	*/
	GridArea 	operator&(const GridArea& rhs) const;
	/** Overload of operator bitwise-or, to mean 'union'.
		@param rhs area to take union with
		@return union of this area and the given area
	*/
	GridArea 	operator|(const GridArea& rhs) const;
				// Intersect and union operators.

	/** Overload of operator bitwise-and assignment. Semantics; perform
		an intersection of this area with rhs, followed by assignment to the result.
		@return reference to self
	*/
	GridArea& 	operator&=(const GridArea& rhs)			{*this = *this & rhs; return *this;}

	/** Overload of operator bitwise-or assignment. Semantics; perform
		union of this area with rhs, followed by assignment to result.
		@return reference to self
	*/
	GridArea& 	operator|=(const GridArea& rhs)			{*this = *this | rhs; return *this;}

	// ----- Relational Operators -----
	/** Overload of equality relational operator.
		Semantics: two GridAreas are equal if and only if they have
		identical vertex locations.
		@param rhs specifies another area to be compared with this
		@return kTrue if the areas have identically located vertices, kFalse otherwise
	*/
	bool16		operator ==(const GridArea& rhs) const	{return topRow == rhs.topRow && bottomRow == rhs.bottomRow && leftCol == rhs.leftCol && rightCol == rhs.rightCol;}

	/** Overload of equality relational operator.
		Semantics: two GridAreas are 'not-equal' if any vertex locations differ.
		@param rhs specifies another area to be compared with this
		@return kTrue if any of the vertex locations between this and the rhs area differ,
		kFalse otherwise
	*/
	bool16 		operator !=(const GridArea& rhs) const	{return !this->operator==(rhs);}

	// ----- Misc -----
	/** Ensures that topRow <= bottomRow and leftCol <= right. Returns true
            if 'this' was changed.
            $$$ does this really make sense?
            @return kTrue if the object was changed by this call
	*/
	bool16 		Normalize();

	/** Query whether this object conforms to rule that the top row is indeed above the bottom row, and the
		left column is indeed to the left of the rightmost column.
		@return kTrue if the area has vertices that have the correct relative disposition to
		one another, kFalse otherwise
	*/
	bool16 		IsNormalized() const					{return topRow <= bottomRow && leftCol <= rightCol;}

	/** Query to see if a particular location is within the area
		covered by this element.
		@param element location of another element
		@return kTrue if element is within 'this', kFalse otherwise.
	*/
	bool16		Contains(const GridAddress& element) const {return element.row >= topRow && element.row < bottomRow && element.col >= leftCol && element.col < rightCol;}


	/** Query whether this area is able to wholly contain the specified area
		@param area specifies area for the query
		@return kTrue if the given area can lie within this area without protruding beyond its bounds, kFalse otherwise
	*/
	bool16 		Contains(const GridArea& area) const	{return area.topRow >= topRow && area.bottomRow <= bottomRow && area.leftCol >= leftCol && area.rightCol <= rightCol;}

	/** Query whether this area has an intersection
		with the specified area
		@return kTrue if the 'this' intersects area, i.e. if there is a non-zero overlap between this area and the given area, kFalse otherwise
	*/
	bool16 		Intersects(const GridArea& area) const	{return leftCol < area.rightCol && rightCol > area.leftCol && topRow < area.bottomRow && bottomRow > area.topRow;}

	/** Persistence-related method for instance to save or read instance data from given stream.
		@param stream stream to read from or write to
		depending on stream's state
	*/	void 		ReadWrite(IPMStream* stream)			{stream->XferInt32(topRow); stream->XferInt32(leftCol); stream->XferInt32(bottomRow); stream->XferInt32(rightCol);}

public:
	/** Represents the row co-ordinate for the top two vertices of this area.
	*/
	GridCoord topRow;
	/** Represents the column co-ordinate for the two lefthand
		vertices of this area.
	*/
	GridCoord leftCol;
	/** Represents the row co-ordinate for the bottom two vertices
		of this area */
	GridCoord bottomRow;

	/** Represents the column co-ordinate for the righmost two vertices
		of this area
	*/
	GridCoord rightCol;
};

//===================================================================================
// class RowRange
/**	A range of rows represented by [start, start+count).

	For instance, a RowRange(0,3) would start at the topmost row
	in the table and include only the first three rows.

	@author 	Joe Shankar
	@see		ITableModel
 */
//===================================================================================
class PUBLIC_DECL RowRange {
public:

	typedef base_type data_type;

				/** No-args constructor.
				*/
				RowRange() : start(0), count(0)	{}
				/** Constuctor.
					@param	start leftmost row to include in this range
					@param	count rows to span
				*/
				RowRange(int32 inStart, int32 inCount) : start(inStart), count(inCount)			  { ASSERT(count >= 0); }
				/** Constructor. The rows spanned by the given GridArea
					used to delimit the constructed range.
					@param	area specifies the area of interest
				*/
	explicit	RowRange(const GridArea& area)     : start(area.topRow), count(area.Height()) { ASSERT(count >= 0); }


	/** Mutator.
		@param	start leftmost row to include in this range
		@param	ccount specifies number of rows this range spans
	*/
	void 	Set(int32 sstart, int32 ccount)			{ start = sstart; count = ccount; ASSERT(count >= 0); }

	/** @return row beyond end of this range, which is the row just below
	*/
	int32	End()	   const						{ return start + count; }

	/** @return kTrue if the count of rows spanned is 0, kFalse otherwise
	*/
	bool16 	IsEmpty()  const						{ return count == 0;	}

	/** Query if the given range can be a subset of this range.
		@param rhs specifies range to test
		@return kTrue if the rows in the given range are a
		subset of the rows in this range, kFalse otherwise
	*/
	bool16 	Contains  (const RowRange& rhs) const	{ return rhs.start >= start && rhs.End() <= this->End();	 }

	/** Query whether a given row lies within this range or not.
		@param row
		@return kTrue if the row is within this row range, kFalse otherwise
	*/
	bool16 	Contains  (int32 row)			const	{ return row	>= start	&& row			< start + count; }

	/** Query whether a given row range intersects with this range or not.
		@param rhs
	*/
	bool16 	Intersects(const RowRange& rhs) const	{ return start  < rhs.End() && this->End()  > rhs.start;	 }

	/**
		Overload of equality comparison operator. Semantically, identity obtains iff the start and span of this and comparand range are identical.
		@return kTrue if the row range is identical in terms of start and rows spanned, kFalse otherwise.
	*/
	bool16	 operator ==(const RowRange& rhs) const	{ return start == rhs.start && count == rhs.count; }

	/** Overload of not-equal comparison operator.
		@return kTrue if the start or span differ, kFalse otherwise
	*/
	bool16 	 operator !=(const RowRange& rhs) const	{ return start != rhs.start || count != rhs.count; }

	/** Overload of bitwise-and operation. The operation
		performs an intersection operation.
		@param rhs range to take intersection with
		@return intersection of this and given row-range
	*/
	RowRange operator&(const RowRange& rhs) const;
	/** Bitwise-or. Takes the union of this and the given row-range.
		@return union of this and the given row range
	*/
	RowRange operator|(const RowRange& rhs) const;

	/** Overload of operator bitwise-and assignment.
		Will have effect of assigning to the intersection of this with the given row-range.
		@param	rhs range to take intersection with
		@return reference to self
	*/
	RowRange&  operator&=(const RowRange& rhs)	{ *this = *this & rhs; return *this; }

	/** Overload of operator bitwise-or assignment.
		Will assign this range to be the union of itself with the given row-range.
		@param	rhs range to take intersection with
		@return reference to self
	*/
	RowRange&  operator|=(const RowRange& rhs)	{ *this = *this | rhs; return *this; }

	/** Persistence-related method.
		@param	stream refers to stream to read from or write to, dependent on stream state.

	*/
	void 	ReadWrite(IPMStream* stream)		{ stream->XferInt32(start); stream->XferInt32(count); }

public:
	/** Represents the first row in this range.
	*/
	int32		start;
	/** Represents the count of rows spanned by this range.
	*/
	int32		count;
};


//===================================================================================
// class ColRange
/**	A range of cols represented by [start, start+count).

	For instance, a ColRange(2,3) would miss out the zeroth and first columns,
	and would include the next three columns (2,3 and 4).

	@author 	Joe Shankar
	@see		ITableModel
 */
//===================================================================================
class PUBLIC_DECL ColRange {

public:
	typedef base_type data_type;

				/** No-args constructor.
				*/
				ColRange() : start(0), count(0)	{}

				/** Constructor.
					@param sstart the first column in the range of interest
					@param ccount the number of columns to include in the range
				*/
				ColRange(int32 sstart, int32 ccount) : start(sstart), count(ccount)		  { ASSERT(count >= 0);}

				/** Constructor. The projection of the GridArea onto the column (horizontal) axis will give
					the column range to span.
					@param area specifies an area, from which the columns spanned will become this column-range.
				*/
	explicit	ColRange(const GridArea& area) : start(area.leftCol), count(area.Width()) { ASSERT(count >= 0);}

	/** Mutator.
		@param sstart the first column in the range of interest
		@param ccount the number of columns to include in the range
	*/
	void 	Set(int32 sstart, int32 ccount)	{ start = sstart; count = ccount; ASSERT(count >= 0); }

	/** Query for column just beyond end of the range spanned.
	*/
	int32	End() const								{ return start + count; }

	/** Query if the range spans any columns at all.
		@return kTrue if the column span is 0, kFalse otherwise
	*/
	bool16 	IsEmpty() const							{ return count == 0;	}

	/** Query whether the given range is subset of this range (can be contained within).
		@param rhs specifies a range of columns
		@return kTrue if the columns in the given range are subset of the columns spanned by this range
	*/
	bool16 	Contains  (const ColRange& rhs) const	{ return rhs.start >= start && rhs.End() <= this->End();	}
	/** Query whether given column lies within this range.
		@param	col specifies column for query
		@return kTrue if the column is within this range, kFalse otherwise
	*/
	bool16 	Contains  (int32 col)			const	{ return col   >= start		&& col			< this->End();	}
	/** Query whether a given range of columns intersects with this range.
		@param	rhs specifies column range for this query
		@return kTrue if there is an intersection in the range of this and the rhs, kFalse otherwise
    */
	bool16 	Intersects(const ColRange& rhs) const	{ return start <  rhs.End() && this->End()  > rhs.start;	}

	/** Overload of the equality relational operator.
		Two ranges are identical iff they have the same start and span the same number of columns.
		@param	rhs specifies the range to compare this against
		@return kTrue if the start column and column span are equal, kFalse otherwise
	*/
	bool16	operator ==(const ColRange& rhs) const	{ return start == rhs.start && count == rhs.count; }
	/** Overload of not-equal operator.
		@param	rhs specifies the range for comparison
		@return kTrue if the ranges have different starting column or column span, kFalse if identical in these instance variables.
    */
	bool16 	operator !=(const ColRange& rhs) const	{ return start != rhs.start || count != rhs.count; }

	/** Overload of bitwise and operator, signifying intersection.
		@param	rhs specifies the range to take intersection of this with
	*/
	ColRange operator&(const ColRange& rhs) const;
	/** Overload of bitwise or operator, signifying a union operation.
		@param	rhs gives a range to take union of this range with
	*/
	ColRange operator|(const ColRange& rhs) const;

	/** Overload of bitwise-and assignment operator, to mean an intersection of this
		with the rhs range, followed by assignment.
		@param	rhs specifies a range to take intersection with
		@return reference to self
	*/
	ColRange&  operator&=(const ColRange& rhs)	{ *this = *this & rhs; return *this; }

	/** Overload of bitwise-or assignment operator, to mean a union followed by assignment.
		@param	rhs specifies range to take a union of this range with
		@return reference to self
	*/
	ColRange&  operator|=(const ColRange& rhs)	{ *this = *this | rhs; return *this; }


	/** Used in persisting the state of an instance.
		@param	stream the stream to read instance data from or write instance data to depending on the stream's state
	*/
	void 	ReadWrite(IPMStream* stream)		{ stream->XferInt32(start); stream->XferInt32(count); }

public:
	/**	Represents the first column in this range.
	*/
	int32		start;
	/** Represents the columns spanned by this range.
	*/
	int32		count;
};

//
// An address to a parcel of a cell
// This contains the gridID of the cell and the parcel identification for the parcel
//
class PUBLIC_DECL CellParcelAddr {
public:
	typedef base_type data_type;

	GridAddress		cellAddr;
	ParcelKey		parcelKey;

public:
	CellParcelAddr() : cellAddr(kBadGridAddress), parcelKey() {}
	CellParcelAddr(GridAddress addr, ParcelKey key)	{cellAddr = addr;  parcelKey = key;}

	bool16	 operator ==(const CellParcelAddr& rhs) const	{ return cellAddr == rhs.cellAddr && parcelKey == rhs.parcelKey; }
	bool16 	 operator !=(const CellParcelAddr& rhs) const	{ return !(*this == rhs); }

};


//===================================================================================
// Inlines
//===================================================================================
inline GridArea::GridArea() :
	topRow(kBadCoord),
	leftCol(kBadCoord),
	bottomRow(kBadCoord),
	rightCol(kBadCoord)
{
}

inline GridArea::GridArea(GridCoord t, GridCoord l, GridCoord b, GridCoord r) :
	topRow(t),
	leftCol(l),
	bottomRow(b),
	rightCol(r)
{
}

inline GridArea::GridArea(const GridAddress& tl, const GridAddress& br) :
	topRow(tl.row),
	leftCol(tl.col),
	bottomRow(br.row),
	rightCol(br.col)
{
}

inline GridArea::GridArea(const GridAddress& tl, const GridSpan& span) :
	topRow(tl.row),
	leftCol(tl.col),
	bottomRow(tl.row + span.height),
	rightCol(tl.col + span.width)
{
}

inline GridArea::GridArea(const RowRange& rows, const ColRange& cols) :
	topRow (rows.start),
	leftCol(cols.start),
	bottomRow(rows.End()),
	rightCol(cols.End())
{
}

inline void GridArea::Set(GridCoord t, GridCoord l, GridCoord b, GridCoord r)
{
	topRow = t;
	leftCol = l;
	bottomRow = b;
	rightCol = r;
}

inline RowRange	GridArea::GetRows() const
{
	return RowRange(topRow, bottomRow - topRow);
}

inline ColRange	GridArea::GetCols() const
{
	return ColRange(leftCol, rightCol - leftCol);
}

#ifdef PUBLIC_BUILD
#pragma export reset
#endif

#endif // __TableTypes__
