//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFlowFacade.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IFlowFacade__
#define __IFlowFacade__

#include "MasterPageID.h"
#include "ILayoutObject.h"
#include "PMPageSize.h"

class IGraphicFrameData;
class IDocument;

namespace Flow
{
	//Note the last call wins. So a 'Set' will clear a previous 'Flip' request, 
	//and a 'Flip' will clear a previous 'Set' request. Further a 'Flip' will
	//clear a previous 'Flip' request thus leaving that constraint unchanged
	//during the command.

	/** enum Values for the GetConstraints/SetConstraints methods. */
	enum Constraint { 
		kFlexibleDimension = 0,	/** A spring constraint */
		kFixedDimension = 1,	/** A strut constraint */
		kFlipDimension = 2,		/** Toggle the constraint (from spring to strut or vice versa). */
		kSkipDimension = 3};	/** Leave constraint alone. */

	typedef K2Vector<Constraint> ConstraintList;

	/** If the parent of a page item has an ILayoutObject interface and that ILayoutObject interface
	 * has a layout policy that is the kRepositionLayoutPolicy, then the page item will be moved and/or
	 * resized based on the horizontal and vertical constraints set on the page item. There are three
	 * horizontal constraints and three vertical constraints and this enum is used to index them. Each
	 * of the six constraints has a value that is either kFlexibleDimension or kFixedDimension.
	 */
	enum ConstraintIndex
	{
		/** kLeftConstraint is the area between the left of the ILayoutObject (typically the page) and the left edge of the page item.*/
		kLeftConstraint = 0,
		kFirstConstraint = kLeftConstraint,
		kFirstXConstraint = kLeftConstraint,
		
		/** kWidthConstraint controls whether the width of the page item is flexible or fixed.*/
		kWidthConstraint = 1,
		
		/** kRightConstraint controls the are between the right edge of the page item and the right edge of the ILayoutObject (typically the page). */
		kRightConstraint = 2,
		kLastXConstraint = kRightConstraint,
		
		/** kTopConstraint is the area between the top of the ILayoutObject (typically the page) and the top edge of the page item.*/
		kTopConstraint = 3,
		kFirstYConstraint = kTopConstraint,
		
		/** kHeightConstraint controls whether the height of the page item is flexible or fixed.*/
		kHeightConstraint = 4,
		
		/** kBottomConstraint controls the are between the bottom edge of the page item and the bottom edge of the ILayoutObject (typically the page). */
		kBottomConstraint = 5,
		kLastYConstraint = kBottomConstraint,
		kLastConstraint = kBottomConstraint,
		kNumConstraints = 6
	};
}

namespace Facade
{
	class IFlowFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IFLOWFACADE };
		
		/**	Return the story UID for the spline (containing a MultiColumnTextFrame)
			@param splineFlowFrameRef - the spline (containing a MultiColumnTextFrame) whose story will be the primary text flow
			@return UIDRef - the UIDRef for the story (the text model UID), kInvalidUIDRef if no story associated with spline
		 */
		virtual UIDRef GetStoryFromSpline(const UIDRef& splineFlowFrameRef) const = 0;

		/**	Can the indicated spline's story be set as the primary text flow for the master spread?
			@param masterRef - the master spread target to set the flow
			@param splineFlowFrameRef - the spline (containing a MultiColumnTextFrame) whose story will be the primary text flow
			@return bool16 - kTrue or kFalse
		 */
		virtual bool16 CanSetPrimaryTextFlowSpline
							(
								const UIDRef& masterSpreadRef,
								const UIDRef& splineFlowFrameRef
							) const = 0;

		/**	Can the indicated story be set as the primary text flow for the master spread?
			@param masterRef - the master spread target to set the flow
			@param storyRef - the story that will be the primary text flow
			@return bool16 - kTrue or kFalse
		 */
		virtual bool16 CanSetPrimaryTextFlowStory
							(
								const UIDRef& masterSpreadRef,
								const UIDRef& storyRef
							) const = 0;

		/**	Set the primary text flow for the master spread.
			@param masterRef - the master spread target to set the flow
			@param splineFlowFrameRef - the spline (containing a MultiColumnTextFrame) whose story will be the primary text flow
			@return ErrorCode - kSuccess or kFailure
		 */
		virtual ErrorCode SetPrimaryTextFlowSpline
							(
								const UIDRef& masterSpreadRef,
								const UIDRef& splineFlowFrameRef
							) = 0;

		/**	Return the primary text flow (spline ref) associated with a master spread. 
			kInvalidUIDRef if there isn't one.
			@param masterRef - the master spread to return the spline flow for.
			@param bWalkUpMasters - kFalse to just return the data for that master spread, kTrue to keep walking up applied masters, stopping when a primary text frame is found.
			@return UIDRef - the UIDRef for the spline that is the flow, kInvalidUIDRef if there isn't one.
		 */
		virtual UIDRef GetPrimaryTextFlowStory(const UIDRef& masterSpreadRef, const bool16 bWalkUpMasters = kFalse) const = 0;

		/**	Set the primary text flow story for the master spread.
			@param masterRef - the master spread target to set the flow
			@param storyRef - the story that will be the primary text flow
			@return ErrorCode - kSuccess or kFailure
		 */
		virtual ErrorCode SetPrimaryTextFlowStory
							(
								const UIDRef& masterSpreadRef,
								const UIDRef& storyRef
							) = 0;

		/** Return the list of splines on a page corresponding to the master's primary flow.
			@param pageRef - a UIDRef for the page
			@param masterRef - a UIDRef for the master to get the primary text flow spline from
			@return UIDList - a UIDList of primary text flow splines on that page (1 in typical case, >1 if threaded frames on that page's master)
		 */
		virtual UIDList GetPrimaryTextFlowSplineListForPage(const UIDRef& pageRef, const UIDRef& masterRef) = 0;

		/** Return the list of splines on the given master (spread or page UIDRef) corresponding to the master's primary flow.
			@param masterRef - a UIDRef for the master spread or a master page on the master spread.
			@return UIDList - a UIDList of primary text flow splines on that page (1 in typical case, >1 if threaded frames on that page's master)
		 */
		virtual UIDList GetPrimaryTextFlowSplineListForMaster(const UIDRef& pageOrSpreadMasterRef) = 0;

		/** Returns true if the spline is in the primary text flow story.
			@param masterRef - a UIDRef for the master to get the primary text flow spline from
			@param splineRef - the spline (containing a MultiColumnTextFrame) to check to see if it's in the primary text flow story
			@return bool16 - kTrue if spline is in the primary text flow story for the given master, kFalse otherwise
		 */
		virtual bool16 IsInPrimaryTextFlowStory(const UIDRef& masterRef, const UIDRef& splineRef) const = 0;

		/** Returns true if the story is a primary text flow story.
			@param storyRef - the story to check to see if it's a primary text flow story
			@param fromThisMaster [OUT] - optional pointer receive the master spread the primary text story comes from (defaults to nil)
			@return bool16 - kTrue if story is a primary text flow story, kFalse otherwise
		 */
		virtual bool16 IsAPrimaryTextFlowStory(const UIDRef& storyRef, UIDRef* fromThisMaster = nil) const = 0;
		virtual bool16 IsAnOverriddenPrimaryTextFlowStory(const UIDRef& storyRef, UIDRef* fromThisMaster = nil) const = 0;

		/**	Can the list of spreads be used to create an alternate layout?
			@param spreadList - the list of spreads to use for the alternate layout
			@return bool16 - kTrue or kFalse
		 */
		virtual bool16 CanCreateAlternateLayout(const UIDList& spreadList) const = 0;

		/**	Create an alternate layout for the document based on a set of spreads.
			All the spreads will be duplicated.
			@param spreadList - the list of spreads to generate the new alternate layout of spreads from
			@param name - the name of the alternate layout.
			@param pageSize - the page size to use for the new spreads
			@param bCreateTextStyles - kTrue to create new text styles, kFalse otherwise
			@param bLinkTextStories - kTrue to create link text stories to source spreads, kFalse otherwise
			@param policy - the layout policy to use for the new pages. Do not use ILayoutObject::kUseMasterLayoutPolicy, use ILayoutObject::kPreserveLayoutPolicy instead.
			@return ErrorCode - kSuccess or kFailure
		 */
		virtual ErrorCode CreateAlternateLayout(const UIDList& spreadList,
												const PMString& name, 
												const PMPageSize& pageSize,
												const bool16 bCreateTextStyles,
												const bool16 bLinkTextStories,
												ILayoutObject::LayoutPolicy policy
												) = 0;

		/**	Can the alternate layout containing the given spread be deleted?
		 @param spreadRef - a UIDRef to a spread
		 @return bool16 - kTrue or kFalse
		 */
		virtual bool16 CanDeleteAlternateLayout(const UIDRef& spreadRef) const = 0;
		
		/**	Delete an alternate layout containing the given spread. Associated master spreads and style groups are optionally deleted as well.
		 @param spreadRef - a UIDRef to a spread
		 @param bDeleteMasters - kTrue to delete masters pages applied in this alternate layout, kFalse to not.
		 @param bDeleteMasters - kTrue to delete style group named the same as this alternate layout, kFalse to not.
		 @return ErrorCode - kSuccess or kFailure
		 */
		virtual ErrorCode DeleteAlternateLayout(const UIDRef& spreadRef, bool16 bDeleteMasters = kTrue, bool16 bDeleteStyleGroups = kTrue) = 0;
		
		/**	Remove the primary text flow story for any master spread that uses it.
			Generally for internal use only used in response to a story getting deleted.
			@param storyRef - the story that is being deleted.
			@return ErrorCode - kSuccess or kFailure
		 */
		virtual ErrorCode DeletePrimaryTextFlowStory(const UIDRef& storyRef) = 0;

		/** Set the layout constraints for a list of page items.
			@param itemList - the list of items to set constraints for.
			@param ConstraintList - the constraint values to set.
			@return ErrorCode

			Common usage:
				Flow::ConstraintList constraints(Flow::kNumConstraints, Flow::kSkipDimension);
				constraints[Flow::kRightConstraint] = Flow::kFlipConstraint;
				SetConstraints(itemList, constraints);
		*/
		virtual ErrorCode SetConstraints(const UIDList& itemList, const Flow::ConstraintList& list) = 0;

		/** Return the constraints for an item in a list with Flow::kNumConstraints values.
			Values returned with be Flow::kFlexibleDimension (spring) or Flow::kFixedDimension (strut)
			@see Flow::Constraint and Flow::ConstraintIndex for values.
		*/
		virtual void GetConstraints(const UIDRef& oneItem, Flow::ConstraintList& outList) const = 0;

		/** Return the value for whether we are in the process of creating an alternate layout or not.
			i.e. Within the sequence generated by CreateAlternateLayout.
			@param document, a pointer to the document to return the flag for.
			@return bool16, kTrue if within CreateAlternateLayout, kFalse otherwise.
		*/
		virtual bool16 GetDuringCreateAlternateLayout(IDocument* document) const = 0;

		/** Set the value for whether we are in the process of creating an alternate layout or not.
			i.e. Within the sequence generated by CreateAlternateLayout.
			@param document, a pointer to the document to set the flag for.
			@param flag, the value for the flag, kTrue for within CreateAlternates, kFalse when done.
		*/
		virtual void SetDuringCreateAlternateLayout(IDocument* document, const bool16 flag) = 0;

	};
}

DECLARE_BASE_TYPE(Flow::Constraint);

#endif // __IFlowFacade__
