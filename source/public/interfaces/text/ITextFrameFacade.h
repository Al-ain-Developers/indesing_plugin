//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameFacade.h $
//  
//  Owner: Jianlan Song
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
#ifndef __ITextFrameFacade__
#define __ITextFrameFacade__

// ----- Interfaces -----
#include "ITextModel.h"
#include "IFrameList.h"
#include "IMultiColumnTextFrame.h"

// ----- ID.h files -----
#include "TextID.h"

namespace Facade
	{
	/** A high level API for dealing with MultiColumnTextFrames.  To use this Facade, include
	    this header file and use the following example syntax:
	    result = Utils<Facade::ITextFrameFacade>()->CreateTextFrame( ... );

	    @author Jianlan Song
	*/
	class ITextFrameFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ITEXTFRAMEFACADE };
		
		/**	Creates a new MultiColumnTextFrame with a new story and a new FrameList.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param newFrame - [OUT] Returns newly created MultiColumnTextFrame if succeeded. Otherwise, returns UIDRef(nil, kInvalidUID).
			@param noGraphicAttr - kTrue if not to set object styles for the new MultiColumnTextFrame. kFalse otherwise. Usually set to kTrue.
			@param boundary - Boundary (in pasteboard coordinates) of the spline where MultiColumnTextFrame will be created.
			@param isHorizontal - kTrue if the new Story should be set horizontal in orientation, kFalse if it is vertical.
			@param isFrameGrid - kTrue if the new Story should have an active FrameGrid. kFalse if not.
			@param isLeftToRight - kTrue if the new Story should be set Left To Right in direction. kFalse if it is left to right.
			@param frameItem - ID of the TextFrameColumns item. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateTextFrame
							(
								UIDRef parent, 
								UIDRef& newFrame,
								const PMRect& boundary, 
								bool16 noGraphicAttr,
								bool16 isHorizontal, 
								bool16 isFrameGrid, 
								bool16 isLeftToRight,
								ClassID frameItem = kFrameItemBoss
							) = 0;


		/**	Creates a new MultiColumnTextFrame with a new story and a new FrameList.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param newFrame - [OUT] Returns newly created MultiColumnTextFrame if succeeded. Otherwise, returns UIDRef(nil, kInvalidUID).
			@param noGraphicAttr - kTrue if not to set object styles for the new MultiColumnTextFrame. kFalse otherwise. Usually set to kTrue.
			@param opposingCorners - Opposing corners (in pasteboard coordinates) of the spline where MultiColumnTextFrame will be created.
			@param isHorizontal - kTrue if the new Story should be set horizontal in orientation, kFalse if it is vertical.
			@param isFrameGrid - kTrue if the new Story should have an active FrameGrid. kFalse if not.
			@param isLeftToRight - kTrue if the new Story should be set Left To Right in direction. kFalse if it is left to right.
			@param frameItem - ID of the TextFrameColumns item. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateTextFrame
							(
								UIDRef parent, 
								UIDRef& newFrame,
								const PMPointList& opposingCorners, 
								bool16 noGraphicAttr,
								bool16 isHorizontal, 
								bool16 isFrameGrid, 
								bool16 isLeftToRight,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Creates a new MultiColumnTextFrame, attaches to an existing story and starts a new FrameList.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param newFrame - [OUT] Returns newly created MultiColumnTextFrame if succeeded. Otherwise, returns UIDRef(nil, kInvalidUID).
			@param noGraphicAttr - kTrue if not to set object styles for the new MultiColumnTextFrame. kFalse otherwise. Usually set to kTrue.
			@param boundary - Boundary of the spline where MultiColumnTextFrame will be created.
			@param story - The existing story to which the new MultiColumnTextFrame will attach.
			@param isHorizontal - kTrue if the Story should be set horizontal in orientation, kFalse if it is vertical.
			@param isFrameGrid - kTrue if the Story should have an active FrameGrid. kFalse if not.
			@param isLeftToRight - kTrue if the Story should be set Left To Right in direction. kFalse if it is left to right.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateTextFrameForStory
							(
								UIDRef parent, 
								UIDRef& newFrame,
								const PMRect& boundary, 
								bool16 noGraphicAttr,
								ITextModel* story,  
								bool16 isHorizontal, 
								bool16 isFrameGrid, 
								bool16 isLeftToRight,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Creates a new MultiColumnTextFrame and insert to the end or beginning of the specified FrameList.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param newFrame - [OUT] Returns newly created MultiColumnTextFrame if succeeded. Otherwise, returns UIDRef(nil, kInvalidUID).
			@param noGraphicAttr - kTrue if not to set object styles for the new MultiColumnTextFrame. kFalse otherwise. Usually set to kTrue.
			@param boundary - Boundary of the spline where MultiColumnTextFrame will be created.
			@param frameList - The existing FrameList into which the new MultiColumnTextFrame will be inserted.
			@param atEnd - kTrue if the new MultiColumnTextFrame will be appended to the end of the FrameList, 
							kFalse if it will be inserted to the beginning of the FrameList. Default is kTrue.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateTextFrameForFrameList
							(
								UIDRef parent, 
								UIDRef& newFrame,
								const PMRect& boundary, 
								bool16 noGraphicAttr, 
								IFrameList * frameList, 
								bool16 atEnd = kTrue,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Creates a new MultiColumnTextFrame and insert into an existing FrameList. The new MultiColumnTextFrame will be inserted before or after
			the specified IMultiColumnTextFrame.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param newFrame - [OUT] Returns newly created frame if succeeded. Otherwise, returns UIDRef(nil, kInvalidUID).
			@param noGraphicAttr - kTrue if not to set object styles for the new MultiColumnTextFrame. kFalse otherwise. Usually set to kTrue.
			@param boundary - Boundary of the spline where MultiColumnTextFrame will be created.
			@param mcFrame - The MultiColumnTextFrame in the existing FrameList before or after which the new MultiColumnTextFrame will be inserted.
			@param insertAfter - kTrue if the new MultiColumnTextFrame will be inserted after mcFrame, 
							kFalse if it will be inserted before mcFrame. Default is kTrue.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateTextFrameForFrameList
							(
								UIDRef parent, 
								UIDRef& newFrame,
								const PMRect& boundary, 
								bool16 noGraphicAttr, 
								IMultiColumnTextFrame * mcFrame, 
								bool16 insertAfter = kTrue,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Converts an existing Spline to a MultiColumnTextFrame with a new story and a new FrameList.
		
			@param parent - Parent page item under which to create the new MultiColumnTextFrame.  parent.GetDataBase() must be non-nil, if parent.GetUID() is set to kInvalidUID then a new kSplineItemBoss will be created.
			@param isHorizontal - kTrue if the new Story should be set horizontal in orientation, kFalse if it is vertical.
			@param isFrameGrid - kTrue if the new Story should have an active FrameGrid. kFalse if not. 
			@param isLeftToRight - kTrue if the new Story should be set Left To Right in direction. kFalse if it is left to right.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertToTextFrame
							(
								UIDRef parent, 
								bool16 isHorizontal, 
								bool16 isFrameGrid,
								bool16 isLeftToRight,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Converts an existing Spline to a MultiColumnTextFrame, attaches to an existing story and starts a new FrameList.
		
			@param parent - Existing Spline which will be converted to MultiColumnTextFrame. 
			@param story - The existing story to which the MultiColumnTextFrame will attach.
			@param isHorizontal - kTrue if the Story should be set horizontal in orientation, kFalse if it is vertical.
			@param isFrameGrid - kTrue if the Story should have an active FrameGrid. kFalse if not.
			@param isLeftToRight - kTrue if the Story should be set Left To Right in direction. kFalse if it is left to right.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertToTextFrameForStory
							(
								UIDRef parent, 
								ITextModel* story,
								bool16 isHorizontal, 
								bool16 isFrameGrid,
								bool16 isLeftToRight,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Converts an existing Spline to a MultiColumnTextFrame and insert at the end or beginning of an existing FrameList.
		
			@param parent - Existing Spline which will be converted to MultiColumnTextFrame. 
			@param frameList - The existing FrameList into which the MultiColumnTextFrame will be inserted.
			@param atEnd - kTrue if the MultiColumnTextFrame will be appened to the end of the FrameList, kFalse if it will be inserted to the beginning of the FrameList. Default is kTrue.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertToTextFrameForFrameList
							(
								UIDRef parent, 
								IFrameList* frameList, 
								bool16 atEnd = kTrue,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/**	Converts an existing Spline to a MultiColumnTextFrame and insert into an existing FrameList. The new MultiColumnTextFrame will be inserted before or after
			the specified IMultiColumnTextFrame.
		
			@param parent - Existing Spline which will be converted to MultiColumnTextFrame. 
			@param mcFrame - The MultiColumnTextFrame in the existing FrameList before or after which the converted Spline will be inserted.
			@param insertAfter - kTrue if the converted Spline will be inserted after mcFrame, 
							kFalse if it will be inserted before mcFrame. Default is kTrue.
			@param frameItem - ID of the TextFrameColumn boss. Default is kFrameItemBoss.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertToTextFrameForFrameList
							(
								UIDRef parent, 
								IMultiColumnTextFrame * mcFrame, 
								bool16 insertAfter = kTrue,
								ClassID frameItem = kFrameItemBoss
							) = 0;

		/** These methods can assist the MultiColumnTextFrame creator to
			determine the final size of the Spline will be after a call to
			create. This is especially useful to trackers which would like to
			show the user what will happen.

			The MultiColumnTextFrame will be the sole determinate as to what
			the final size of the Spline will be - even if the Spline already
			exists. The goal here is to isolate the clients from having to know
			how the policy is calculated and leave it in one place - in the
			MultiColumnTextFrame.

			The MultiColumnTextFrame may decide to accept the current or
			specified size of the Spline but it is under no requirement to do
			so. This policy exists so that both fixed column width, range column width, or
			FrameGrids are always sized appropriately.

			Lastly, we always let the FrameGrid dimensions win - so if the
			TextColumnSizer specifies a fixed column width that is not an even
			number of grid cells the fixed column width will be adjusted up to
			the next grid cell.
		*/

		/** Computes the Spline dimensions for a fixed number of columns and
			no FrameGrid.

			@param splinePathWidth Must be greater or equal to 1.0
			@param splinePathHeight Must be greater or equal to 1.0
			@param strokeWeight
			@param strokeAlignment
			@param leftTextInset
			@param topTextInset
			@param rightTextInset
			@param bottomTextInset
			@param storyIsVertical
			@param mcfNumColumns
			@param mcfGutterWidth
			@param adjSplinePathWidth [Out]
			@param adjSplinePathHeight [Out]
			@param mcfVariableColWidth [Out]
		*/
		virtual void GetSplinePathDimensionsIf
							(
								PMReal splinePathWidth,
								PMReal splinePathHeight,
								PMReal strokeWeight,
								int32 strokeAlignment,
								PMReal leftTextInset,
								PMReal topTextInset,
								PMReal rightTextInset,
								PMReal bottomTextInset,
								bool16 storyIsVertical,
								int32 mcfNumColumns,
								PMReal mcfGutterWidth,
								PMReal& adjSplinePathWidth,
								PMReal& adjSplinePathHeight,
								PMReal& mcfVariableColWidth
							) = 0;

		/** Computes the Spline dimensions for a fixed number of columns and
			a FrameGrid.

			@param splinePathWidth Must be greater or equal to 1.0
			@param splinePathHeight Must be greater or equal to 1.0
			@param strokeWeight
			@param strokeAlignment
			@param leftTextInset
			@param topTextInset
			@param rightTextInset
			@param bottomTextInset
			@param storyIsVertical
			@param textSize
			@param charAki
			@param lineAki
			@param hScale
			@param vScale
			@param mcfNumColumns
			@param mcfGutterWidth
			@param adjSplinePathWidth [Out]
			@param adjSplinePathHeight [Out]
			@param mcfVariableColWidth [Out]
			@param mcfGridColCount [Out]
			@param mcfGridRowCount [Out]
		*/
		virtual void GetSplinePathDimensionsIf
							(
								PMReal splinePathWidth,
								PMReal splinePathHeight,
								PMReal strokeWeight,
								int32 strokeAlignment,
								PMReal leftTextInset,
								PMReal topTextInset,
								PMReal rightTextInset,
								PMReal bottomTextInset,
								bool16 storyIsVertical,
								PMReal textSize,
								PMReal charAki,
								PMReal lineAki,
								PMReal hScale,
								PMReal vScale,
								int32 mcfNumColumns,
								PMReal mcfGutterWidth,
								PMReal& adjSplinePathWidth,
								PMReal& adjSplinePathHeight,
								PMReal& mcfVariableColWidth,
								int32& mcfGridColCount,
								int32& mcfGridRowCount
							) = 0;

		/** Computes the Spline dimensions for a fixed column width and
			no FrameGrid.

			@param splinePathWidth
			@param splinePathHeight
			@param strokeWeight
			@param strokeAlignment
			@param leftTextInset
			@param topTextInset
			@param rightTextInset
			@param bottomTextInset
			@param storyIsVertical
			@param mcfGutterWidth
			@param mcfFixedColumnWidth
			@param adjSplinePathWidth [Out]
			@param adjSplinePathHeight [Out]
			@param mcfNumColumns [Out]
		*/
		virtual void GetSplinePathDimensionsIf
							(
								PMReal splinePathWidth,
								PMReal splinePathHeight,
								PMReal strokeWeight,
								int32 strokeAlignment,
								PMReal leftTextInset,
								PMReal topTextInset,
								PMReal rightTextInset,
								PMReal bottomTextInset,
								bool16 storyIsVertical,
								PMReal mcfGutterWidth,
								PMReal mcfFixedColumnWidth,
								PMReal& adjSplinePathWidth,
								PMReal& adjSplinePathHeight,
								int32& mcfNumColumns
							) = 0;


		/** Computes the Spline dimensions for a fixed column width and
			a FrameGrid.

			@param splinePathWidth Must be greater or equal to 1.0
			@param splinePathHeight Must be greater or equal to 1.0
			@param strokeWeight
			@param strokeAlignment
			@param leftTextInset
			@param topTextInset
			@param rightTextInset
			@param bottomTextInset
			@param storyIsVertical
			@param textSize
			@param charAki
			@param lineAki
			@param hScale
			@param vScale
			@param mcfGutterWidth
			@param mcfFixedColumnWidth
			@param adjSplinePathWidth [Out]
			@param adjSplinePathHeight [Out]
			@param mcfNumColumns [Out]
			@param mcfGridColCount [Out]
			@param mcfGridRowCount [Out]
		*/
		virtual void GetSplinePathDimensionsIf
							(
								PMReal splinePathWidth,
								PMReal splinePathHeight,
								PMReal strokeWeight,
								int32 strokeAlignment,
								PMReal leftTextInset,
								PMReal topTextInset,
								PMReal rightTextInset,
								PMReal bottomTextInset,
								bool16 storyIsVertical,
								PMReal textSize,
								PMReal charAki,
								PMReal lineAki,
								PMReal hScale,
								PMReal vScale,
								PMReal mcfGutterWidth,
								PMReal mcfFixedColumnWidth,
								PMReal& adjSplinePathWidth,
								PMReal& adjSplinePathHeight,
								int32& mcfNumColumns,
								int32& mcfGridColCount,
								int32& mcfGridRowCount
							) = 0;

		/** Computes the Spline dimensions for a flexible column width and
			no FrameGrid.

			@param splinePathWidth
			@param splinePathHeight
			@param strokeWeight
			@param strokeAlignment
			@param leftTextInset
			@param topTextInset
			@param rightTextInset
			@param bottomTextInset
			@param storyIsVertical
			@param mcfGutterWidth
			@param mcfColumnWidthMin
			@param mcfColumnWidthMax
			@param adjSplinePathWidth [Out]
			@param adjSplinePathHeight [Out]
			@param mcfNumColumns [Out]
		*/
		virtual void GetSplinePathDimensionsIf
							(
								PMReal splinePathWidth,
								PMReal splinePathHeight,
								PMReal strokeWeight,
								int32 strokeAlignment,
								PMReal leftTextInset,
								PMReal topTextInset,
								PMReal rightTextInset,
								PMReal bottomTextInset,
								bool16 storyIsVertical,
								PMReal mcfGutterWidth,
								PMReal mcfColumnWidthMin,
								PMReal mcfColumnWidthMax,
								PMReal& adjSplinePathWidth,
								PMReal& adjSplinePathHeight,
								int32& mcfNumColumns
							) = 0;

		/** Calculate the minimum for how wide a column must be for a given number of columns when using flexible column sizing.
			@param numColumns	the number for desired columns
			@param gutterWidth	the gutter width
			@param maxFlexibleWidth	the maximum width of a column
			@param currentColumnWidth the current column width for the text frame
			@param adjustedColumnWidth [OUT] the adjusted size that is the minimum column size in order to achieve that column count
		*/
		virtual void GetMinFlexibleColumnWidthIf
							(
								int32 numColumns, 
								PMReal gutterWidth, 
								PMReal maxFlexibleWidth,
								PMReal currentColumnWidth,
								PMReal& adjustedColumnWidth
							) = 0;
	};

}

#endif // __ITextFrameFacade__

