//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFrameUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IFrameUtils__
#define __IFrameUtils__

#include "TextID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "UIDRef.h"
#include "PMTypes.h"

class IGraphicsContext;
class IHandleShape;
class ILayoutControlData;
class IMultiColumnTextFrame;
class ITextFrameColumn;
class ITextModel;
class UIDList;
class PMRect;
class PMMatrix;
class GraphicsData;

const PMReal kThreadHandleSize = 8.0;


/**
	Utilities about text frames -- mostly drawing text frames.
	Use: Utils<IFrameUtils>()->GetSelectedFrameLists( ... ) ;
	@ingroup layout_util
*/
class IFrameUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFRAMEUTILS };


	enum { kTF_InLink = 1, kTF_OutLink = 2, kTF_Overset = 4 };


	/**	Given a shape, return the frame threads bounding box in coordinates of the frame
		and its threads transformed by the provided matrix.
		@param shape IN the frame to get the frame thread bounding box for.
		@param theMatrix IN is the transform to apply.
		@param bounds OUT is the resultant bounding box in the frame coordinates.
		@return kTrue if the frame threads exist.
	 */
	virtual bool16	GetFrameThreadBBox(IHandleShape* shape, const PMMatrix& theMatrix, PMRect& bounds) = 0;


	/**	Get the text frame inside a graphic frame
		@param graphicFrame is the pageitem in question.
		@param textflags, if non-nil, is SET to reflect the status of the frame (in, out, overset).
		@return the UID of the text frame.
	 */
	virtual UID GetTextFrameUID(IPMUnknown* graphicFrame, int32 *textflags = nil) = 0;

	/**	Is the item a text frame?
		@param graphicFrame is the pageitem in question.
		@param textflags, if non-nil, is SET to reflect the status of the frame (in, out, overset).
		@return kTrue if graphicFrame is a text frame.
	 */
	virtual bool16	IsTextFrame(IPMUnknown* graphicFrame, int32* textflags = nil) = 0;


	/**	Returns the list of Inlines (kInlineBoss) that are associated with the TextFrame (inside the frame),
		including those that are within WaxAnchorPt owned items (such as tables).
		If the text within the frame isn't composed, the resultList will probably be empty.
		@param frame is which text frame to look at.
		@param doDropCaps NOT USED ANYMORE.
		@param resultList the UIDList containing all of the inlines.
	 */
	virtual void GetUIDListOfInlines(IMultiColumnTextFrame* frame, bool16 doDropCaps, UIDList* resultList) = 0;
	virtual void GetUIDListOfInlines(ITextFrameColumn* frame, bool16 doDropCaps, UIDList* resultList) = 0;

	/**	Returns the list of wrapped page items (Inlines/Cell page items)  that are associated with the TextFrame (inside the frame)
		If the text within the frame isn't composed, the resultList will probably be empty.
		@param frame is which text frame to look at.
		@param doDropCaps NOT USED ANYMORE.
		@param resultList the UIDList containing all of the wrapped page items.
		@param itemClassID	If class Id is provided then it will return list of those items,
				otherwise all the item which support IPageItemAdapter interface

	 */
	virtual void GetUIDListOfPlacedPageItem(IMultiColumnTextFrame* frame, bool16 doDropCaps, UIDList* resultList, ClassID itemClassID = kInvalidClass) = 0;
	virtual void GetUIDListOfPlacedPageItem(ITextFrameColumn* frame, bool16 doDropCaps, UIDList* resultList, ClassID itemClassID = kInvalidClass) = 0;


	/**	Get the frame Threads bounding bos for the list of frames.
		@param gd is the GraphicsData to use.
		@param frameLists is the list of frames.
		@param invalRect is the bounding box of the combined frame threads.
	 */
	virtual void GetFrameThreadsBBox(GraphicsData *gd, const UIDList& frameLists, PMRect& invalRect) = 0;

	/**	Draw the frame edges for the listed frame lists.
		@param gd is the GraphicsData to use.
		@param frameLists are the frame lists to draw edges for.
	 */
	virtual void DrawSelectedFrameEdges(GraphicsData *gd, const UIDList& frameLists) = 0;


	/**	Draw the line from the frame to the anchors.
		@param gd is the GraphicsData to use.
		@param anchors is the list of the anchored objects to draw lines for.
	 */
	virtual void DrawSelectedAnchorThreads(GraphicsData *gd, const UIDList& anchors) = 0;

	/**	Handles 2 cases: 1) if the range contains inline graphics, it will return information about them. If not,
		this routine will see if the textmodel is actually within an anchored object and return information about the container.
		@param model the story to check.
		@param start the index to start looking for inlines at.
		@param end the final index when looking for inlines.
		@param pOtherFrame is set to a contained textframe, or to the CONTAINING text frame if the model in from an inline.
		@param pLocation is the TextIndex of the end of a contained textframe of the index within the container of the model's inline frame.
		@return the list of contained inline graphics or the containing text frame.
	 */
	virtual UIDList CheckForAnchorInText(ITextModel *model, TextIndex start, TextIndex end, UIDRef *pOtherFrame = nil, TextIndex *pLocation = nil) = 0;

	/**	Is the pageItem actually an anchored object?
		@param pageItem is a UIDRef of the pageitem in question.
		@param pOwningFrame will be the UIDRef of the textFrame that contains the pageItem if the pageItem is anchored.
		@param pOwningStory will be the UIDRef of the textmodel that contains the pageItem if it is anchored.
		@param pAnchorLocation will be the TextIndex of the pageItem, if it is anchored.
		@return kTrue if the pageItem is anchored.
	 */
	virtual bool16 IsPageItemAnchoredObject(UIDRef pageItem, UIDRef *pOwningFrame = nil, UIDRef *pOwningStory = nil, TextIndex *pAnchorLocation = nil) = 0;

};


#endif	// __IFrameUtils__
