//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateFrame.h $
//  
//  Owner: ???
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

#ifndef __SnipCreateFrame_h__
#define __SnipCreateFrame_h__

/** 
	\li How to to create frames(IGraphicFrameData) of various types on a spread 
		positioned relative to the current page,
	\li rectangle frame, text frame and various styled graphics are created,
	\li how to use ILayoutControlData to find the active spread layer and page.

  	@ingroup sdk_snippet
	@ingroup sdk_layout
	
	@see IGraphicFrameData
	@see ILayoutControlData
	@see SDKLayoutHelper
	@see SnpGraphicHelper
*/
class SnpCreateFrame
{
	public:
		/** Create a rectangle frame.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateRectangleFrame(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/** Create a text frame.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateTextFrame(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/** Create a rectangular graphic.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateRectangleGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/** Create a square parented inside a rectangular graphic with a fancy border.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateSquareInFancyGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/** Create a spline in the shape of an arrow with various graphic attributes 
			applied so that it is drawn as a dashed line with an arrow head at one end.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateArrowGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/**	If the frame is a text frame activate the text editor and make a text selection
			to set the text caret at the start of the story, otherwise make a layout selection
			of the frame.
			@param selectionManager 
			@param frameUIDRef 
			@return kTrue on success, kFalse otherwise.
		 */
		bool16	SelectFrame(ISelectionManager* selectionManager, const UIDRef& frameUIDRef);

		/** Activate kIBeamToolBoss if a text tool is not already active.
			@return kTrue on success, kFalse otherwise.
		 */
		bool16	ActivateTextEditor();
};




#endif // __SnipCreateFrame_h__

//End, SnipCreateFrame.h


