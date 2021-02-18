//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFrameContentFacade.h $
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
#ifndef _IFrameContentFacade_
#define _IFrameContentFacade_

#include "IFrameContentSuite.h"
#include "GenericID.h"

class AutomationContext;
/** IFrameContentFacade interface

	Provide a suite for convert between pageitem frame and its contents
  */

namespace Facade
	{
	class IFrameContentFacade : public IPMUnknown
		{
		public:
			enum { kDefaultIID = IID_IFRAMECONTENTFACADE };

		public:

			/**	Can convert the selected item be to Frame?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanConvertItemToFrame (UIDList& items) const = 0;	

			/**	Can select "convert the selected item be to Frame" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanSelectConvertItemToFrame (UIDList& items) const = 0;	
			/**	Can MultiSelect "convert the selected item be to Frame" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanMultiSelectConvertItemToFrame (UIDList& items) const = 0;	


			/**	Can convert the selected item to text?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanConvertItemToText (UIDList& items) const = 0;	

			/**	Can Select "convert the selected item to text" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanSelectConvertItemToText (UIDList& items) const = 0;
			
			/**	Can MultiSelect "convert the selected item to text" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanMultiSelectConvertItemToText (UIDList& items) const = 0;	


			/**	Can convert the selected frame to page item?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanConvertFrameToItem (UIDList& items) const = 0;	

			/**	Can Select "convert the selected frame to page item" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanSelectConvertFrameToItem (UIDList& items) const = 0;	

			/**	Can MultiSelect "convert the selected frame to item" menu?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanMultiSelectConvertFrameToItem (UIDList& items) const = 0;	


			/**	Can fit frame to its content?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanFitFrameToContent (UIDList& items) const = 0;	

			/**	Can fit content to its frame?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanFitContentToFrame (UIDList& items) const = 0;	

			/**	Can fit content proportionally?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanFitContentProp (UIDList& items) const = 0;	

			/**	Can fit content in the center of the frame?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanCenterContentInFrame (UIDList& items) const = 0;	

			/**	Can fill frame proportionally?
				@param none
				@return bool16 
			 */
			virtual bool16 	CanFillFrameProp (UIDList& items) const = 0;	

			/** Can set persistent fitting options on the frame?
				@param items (IN): list of inputs to which the query pertains.
				@return bool16
			*/
			virtual bool16 CanSetFittingOptions (UIDList& items) const = 0;

			/** Get persistent fitting options to the frame.
				@param items (IN): list of inputs to which the query pertains.  Any item which cannot have fitting options applied
					will be ignored.
				@param refPoint (OUT): Which of the nine reference points are currently used when aligning or fitting the contents
					to the frames in the target.  Note that kNone indicates a mixed setting, or if Frame Fitting Option attributes have never been applied to the frame.
				@param cropAmounts (OUT): Crop amounts to apply to the graphic contents before aligning or fitting to the frame.
					Note that a value of kMixedCropAmount for any of the coordinates indicates a mixed setting in the target. 
					kZeroRect is returns if Frame Fitting Option attributes have never been applied to the frame.
				@param fitting (OUT): One of kMixedFitting, kNoFitting, kFitContents, kFitProportionally, kFillProportionally. 
				    Returns kNoFitting if Frame Fitting Option attributes have never been applied to the frame.
				@param autoFit (OUT): kTrue if auto-fit is on. This applies the Fitting Options to the frame whenever the frame changes size or shape.
				@return kTrue if supported or kFalse if we can't get the options or they don't apply.
			*/
			virtual bool16 GetFittingOptions(UIDList& items,
						IReferencePointData::ReferencePointPosition *refPoint,
						PMRect* cropAmounts,
						IFrameContentSuite::PersistentFitOptions *fitting,
						bool16 *autoFit) const = 0;

			/**	Convert the selected item to a Frame
				@param void 
				@return Success or Failure 
			 */
			virtual ErrorCode	ConvertItemToFrame (UIDList& items) = 0;

			/**	Convert the selected item to text
				@param void 
				@return Success or Failure 
			 */
			virtual ErrorCode	ConvertItemToText (UIDList& items) = 0;

			/**	Convert the selected frame to page item
				@param void 
				@return Success or Failure 
			 */
			virtual ErrorCode	ConvertFrameToItem (UIDList& items) = 0;

			/**	Fit frame to its content
				@param items (IN): UIDList of the page items to which to apply the fitting.
				@return Success or Failure 
			 */
			virtual ErrorCode	FitFrameToContent (UIDList& items) = 0;

			/**	Fit content to its frame
				@param items (IN): UIDList of the page items to which to apply the fitting.
				@return Success or Failure 
			 */
			virtual ErrorCode	FitContentToFrame (UIDList& items) = 0;

			/**	Fit content proportionally. May leave white space around image.
				@param items (IN): UIDList of the page items to which to apply the fitting.
				@return Success or Failure 
			 */
			virtual ErrorCode	FitContentProp (UIDList& items) = 0;

			/**	Fit content in the center of the frame
				@param items (IN): UIDList of the page items to which to apply the fitting.
				@return ErrorCode Success or Failure
			 */
			virtual ErrorCode	CenterContentInFrame (UIDList& items) = 0;

			/**	Fill frame proportionally. Leaves no white space around image.
				@param items (IN): UIDList of the page items to which to apply the fitting.
				@return Success or Failure 
			 */
			virtual ErrorCode	FillFrameProp (UIDList& items) = 0;

			/** Set persistent fitting options to the frame.
				@param items (IN): UIDList of the page items to which to set the fitting options.
				@param refPoint (IN): Which of the nine reference points should be used when aligning or fitting the contents
					to this frame?
				@param cropAmounts (IN): Crop amounts to apply to the graphic contents before aligning or fitting to the frame.
				@param fitting (IN): One of kNoFitting, kFitContents, kFitProportionally, kFillProportionally.
				@param autoFit (IN): kTrue to turn auto-fit on. This applies the Fitting Options to the frame whenever the frame changes size or shape.
				@param reApplyFitting (IN): Whether to apply auto-fit now.
			*/
			virtual ErrorCode	SetFittingOptions(UIDList& items,
						IReferencePointData::ReferencePointPosition refPoint,
						const PMRect& cropAmounts,
						IFrameContentSuite::PersistentFitOptions fitting /*= IFrameContentSuite::kNoFitting*/,
						bool16 autoFit /*= kFalse*/,
						bool16 reApplyFitting /*= kTrue*/) = 0;

			/** Apply current fitting options, which are stored on a graphic frame, to the contents of
				those frames.
				@param items (IN): UIDList of the page items to which to apply the fitting options.
			*/
			virtual ErrorCode	ApplyFittingOptionsToContent(UIDList& items, bool16 listenerTriggered = kFalse) = 0;

			/** Removes all the frame fitting attributes from a list of frames. This restores it to it's initial state.
				@param items (IN): UIDList of the page items to which to clear the fitting options.
			*/
			virtual ErrorCode	ClearFittingOptions(UIDList& targetItemList) = 0;

			/**	Returns kTrue if any item in the list can be converted to a text frame
				@param items IN UIDList of items to check for convertibility. 
				@return kTrue (can convert one or more items) or kFalse (can't convert any items).
			 */
			virtual bool16 CanEnableConvertToText( const UIDList* items ) const = 0;

			/**	Returns kTrue if any item in the list can be converted to a graphic frame
				@param items IN UIDList of items to check for convertibility. 
				@return kTrue (can convert one or more items) or kFalse (can't convert any items).
			 */
			virtual bool16 CanEnableConvertToFrame( const UIDList* items ) const = 0;

			/**	Returns kTrue if any frame in the list can be converted to a page item
				@param items IN UIDList of items to check for convertibility. 
				@return kTrue (can convert one or more items) or kFalse (can't convert any items).
			 */
			virtual bool16 CanEnableConvertToItem( const UIDList* items ) const = 0;

			/**	Determine if Fit Frame to Content menu item should be enabled for given list of items. Used
				by CanFitFrameToContent suite functions in IFrameContentSuite.
				@param items IN UIDList of items to examine. 
				@return Enable state (kTrue for enabled, kFalse otherwise). 
			 */
			virtual bool16 CanEnableFitFrameToContent(const UIDList* items) const = 0;

			/**	Determine if Fit Frame to Content menu item should be enabled for given list of items. Used
				by CanFitContentToFrame (and CanFitContentProp and CanCenterContentInFrame) suite functions in IFrameContentSuite.
				@param items IN UIDList of items to examine. 
				@return enable state (kTrue for enabled, kFalse otherwise). 
			 */
			virtual bool16 CanEnableFitContentToFrame(const UIDList* items) const = 0;

			/**	Record a Fit Option action, the caller is responsible for calling ShouldRecord()
				@param automationContext - automation context in which the event is recorded,
				@param fitType - the type of fitting
				@return ErrorCode 
			 */
			virtual ErrorCode RecordFitOption (AutomationContext* ac, ScriptID fitType) = 0;

			/**	Record a Fit Option action atom
				@param automationContext - automation context in which the event is recorded,
				@param fitType - the type of fitting
				@return ErrorCode 
			 */
			virtual ErrorCode AddFitOptionActionAtom(AutomationContext* ac, ScriptID fitType) = 0;

			/** Tell AutoFit to temporarily ignore content changes for the duration of a command sequence. If a dialog is active you 
			    call this before every command within a sequence that changes content of an autofit frame. 
				@param frames - a list of frames to ignore content changes from.
			*/
			virtual void				TellListenerUserTriggered(const UIDList& frames) = 0;

			/**	Determine if Content-aware Fit can be applied for a given list of items. Used by IFrameContentSuite::CanApplyContentAwareFit
			@param items IN UIDList of items to examine.
			@return kTrue is the Content-aware fit can be applied, kFalse otherwise).
			*/
			virtual bool16 CanApplyContentAwareFit(const UIDList& listOfFrames) = 0;

			/**	Applies Content-aware Fit for a given list of items. Used by IFrameContentSuite::ApplyContentAwareFit
			@param items IN UIDList of items to examine.
			@return ErrorCode
			*/
			virtual ErrorCode ApplyContentAwareFit(const UIDList& listOfFrames) = 0;

			/** Global preference for Enabling Content-Aware Fit as default while placing items.
			@param enable IN kTrue value depicts enabling the preference, kFalse otherwise.
			@return ErrorCode
			*/
			virtual ErrorCode EnableContentAwareFitAsDefault(bool16 enable = kTrue) = 0;

			/** Returns the value of Global preference for Enabling Content-Aware Fit as default while placing items.
			@return kTrue - the preference is enabled, kFalse otherwise.
			*/
			virtual bool16 IsContentAwareFitAsDefaultEnabled() = 0;

			/**	Determine if similar images can be found for a given list of items. Used by IFrameContentSuite::CanSearchSimilar
			@param items IN UIDList of items to examine. Currently only a single page item is supported.
			@return kTrue if the similar images can be searched, kFalse otherwise).
			*/
			virtual bool16 CanSearchSimilar(const UIDList& listOfFrames) = 0;

			/**	Searches similar image for a given list of items. Used by IFrameContentSuite::SearchSimilar
			@param items IN UIDList of items to examine. Currently only a single page item is supported.
			@return ErrorCode
			*/
			virtual ErrorCode SearchSimilar(const UIDList& listOfFrames) = 0;
		};
	}
#endif // _IFrameContentFacade_