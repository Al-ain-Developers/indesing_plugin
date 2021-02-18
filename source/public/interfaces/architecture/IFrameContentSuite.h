//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IFrameContentSuite.h $
//  
//  Owner: Shengliu Dai
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IFrameContentSuite_
#define _IFrameContentSuite_

#include "IReferencePointData.h"

//as a return value from GetFittingOptions for the fitting parameter indicating that there is a multiple selection and that
//the elements of the selection have differing fitting settings.
#define kMixedCropAmount -8641.
#define kMixedAutoFit -1

/** IFrameContentSuite interface

	Provide a suite for convert between pageitem frame and its contents
  */

class IFrameContentSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IFRAMECONTENTSUITE };

		/** enumeration of possible persistent fitting options on a graphic frame.
			Note that kMixedFitting is only used as a return value from GetFittingOptions
			for the fitting parameter indicating that there is a multiple selection and that
			the elements of the selection have differing fitting settings.
		*/
		typedef enum {
			kMixedFitting = -1,
			kNoFitting, 
			kFitContents, 
			kFitProportionally, 
			kFillProportionally 
		} PersistentFitOptions;
		
	public:

		/**	Can convert the selected item be to Frame?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanConvertItemToFrame (void) const = 0;	

		/**	Can select "convert the selected item be to Frame" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanSelectConvertItemToFrame (void) const = 0;	
		/**	Can MultiSelect "convert the selected item be to Frame" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanMultiSelectConvertItemToFrame (void) const = 0;	


		/**	Can convert the selected item to text?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanConvertItemToText (void) const = 0;	

		/**	Can Select "convert the selected item to text" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanSelectConvertItemToText (void) const = 0;
		
		/**	Can MultiSelect "convert the selected item to text" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanMultiSelectConvertItemToText (void) const = 0;	

		/**	Can convert the selected frame to page item?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanConvertFrameToItem (void) const = 0;	

		/**	Can Select "convert the selected frame to page item" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanSelectConvertFrameToItem (void) const = 0;	

		/**	Can MultiSelect "convert the selected frame to item" menu?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanMultiSelectConvertFrameToItem (void) const = 0;	

		/**	Can fit frame to its content?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanFitFrameToContent (void) const = 0;	

		/**	Can fit content to its frame?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanFitContentToFrame (void) const = 0;	

		/**	Can fit content proportionally?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanFitContentProp (void) const = 0;	

		/**	Can fit content in the center of the frame?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanCenterContentInFrame (void) const = 0;	

		/**	Can fill frame proportionally?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanFillFrameProp (void) const = 0;	

		/** Can set persistent fitting options on the frame?
			@param none
			@return bool16
		*/
		virtual bool16 CanSetFittingOptions (void) const = 0;

		/** Can clear persistent fitting options on the frame?
			@param none
			@return bool16
		*/
		virtual bool16 CanClearFittingOptions (void) const = 0;

		/** Get persistent fitting options to the frame.
			@param refPoint (OUT): Which of the nine reference points are currently used when aligning or fitting the contents
				to the frames in the target.  Note that kNone indicates a mixed setting.
			@param cropAmounts (OUT): Crop amounts to apply to the graphic contents before aligning or fitting to the frame.
				Note that a value of kMixedCropAmount for any of the coordinates indicates a mixed setting in the target.
			@param fitting (OUT): One of kMixedFitting, kNoFitting, kFitContents, kFitProportionally, kFillProportionally.
			@param autoFit (OUT): if kTrue, fitting options are reapplied when the frame is resized 
			@return kTrue if supported or kFalse if we can't get the options or they don't apply.
		*/
		virtual bool16 GetFittingOptions(IReferencePointData::ReferencePointPosition *refPoint,
					PMRect* cropAmounts,
					PersistentFitOptions *fitting,
					bool16 *autoFit) const = 0;

		/**	Convert the selected item to a Frame
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ConvertItemToFrame (void) = 0;

		/**	Convert the selected item to text
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ConvertItemToText (void) = 0;

		/**	Convert the selected frame to page item
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ConvertFrameToItem (void) = 0;

		/**	Fit frame to its content
			@return Success or Failure 
		 */
		virtual ErrorCode	FitFrameToContent (void) = 0;

		/**	Fit content to its frame
			@return Success or Failure 
		 */
		virtual ErrorCode	FitContentToFrame (void) = 0;

		/**	Fit content proportionally. May leave white space around image.
			@return Success or Failure 
		 */
		virtual ErrorCode	FitContentProp (void) = 0;

		/**	Fit content in the center of the frame
			@return ErrorCode Success or Failure
		 */
		virtual ErrorCode	CenterContentInFrame (void) = 0;

		/**	Fill frame proportionally. Leaves no white space around image.
			@return Success or Failure 
		 */
		virtual ErrorCode	FillFrameProp (void) = 0;

		/** Set persistent fitting options to the frame.
			@param refPoint (IN): Which of the nine reference points should be used when aligning or fitting the contents
				to this frame?
			@param cropAmounts (IN): Crop amounts to apply to the graphic contents before aligning or fitting to the frame.
			@param fitting (IN): One of kNoFitting, kFitContents, kFitProportionally, kFillProportionally.
			@param autoFit (IN): Turn auto-fit on or off.
		*/
		virtual ErrorCode	SetFittingOptions(IReferencePointData::ReferencePointPosition refPoint,
					const PMRect& cropAmounts,
					PersistentFitOptions fitting /*= kNoFitting*/,
					bool16 autoFit /*= kFalse*/) = 0;

		/**	Clear frame fitting options .
			@return Success or Failure 
		 */
		virtual ErrorCode	ClearFittingOptions(void) = 0;
        
		/**	Can apply Content-aware fit to the current selection
		@param none
		@return bool16
		*/
		virtual bool16 	CanApplyContentAwareFit(void) const = 0;

		/**	Apply content aware fit to the current selection. Choose the best area of the image to be shown in the frame.
		@return Success or Failure
		*/
		virtual ErrorCode	ApplyContentAwareFit(void) = 0;

		/**	Can search similar images for the current selection.
		@param none
		@return bool16
		*/
		virtual bool16 	CanSearchSimilar(void) const = 0;

		/**	Search similar images for the current selection.
		@return Success or Failure
		*/
		virtual ErrorCode	SearchSimilar(void) = 0;
	};

#endif // _IFrameContentSuite_
