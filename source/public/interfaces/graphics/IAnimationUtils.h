//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationUtils.h $
//  
//  Owner: SusanCL
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#include "DynamicDocumentsID.h"

#include "AnimationTypes.h"
#include "Utils.h"
#include "ISpreadDynamicContentMgr.h"

class IAnimationUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IANIMATIONUTILS };
	
	/** Returns the specified target's name.
		If target is part of MSO, the fully qualified name is returned.
		@param targetRef is the target UIDRef.
		@return target name.
	*/
	virtual PMString GetTargetName (const UIDRef& targetRef) const = 0;

	/** Returns the applicable trigger event list for the specified triggering object
		@param ownerRef is the triggering object.
		@param triggerList is list of applicable triggers.
	*/
	virtual void GetApplicableTriggerEvents (const UIDRef& ownerRef, std::vector<EventTriggerType>& triggerList) const = 0;

	/** Returns the other applicable trigger events for the specified target in the current event trigger.
		@param ownerRef is the triggering object.
		@param targetRef is the target.
		@param triggerList is list of applicable triggers.
	*/
	virtual void GetApplicableTriggerEventsForTarget (const UIDRef& ownerRef, const UIDRef& targetRef, std::vector<EventTriggerType>& triggerList) const = 0;

	/** Returns the event trigger associated with the event trigger string.
		@param triggerString is the trigger string.
		@return the event trigger type.
	*/
	virtual  EventTriggerType GetEventTriggerFromString (const PMString& triggerString) const = 0;

	/** Returns the event trigger string for the specified trigger event
		@param trigger is the event trigger.
		@param type is the dynamic content type. The default is kAnimationItemType. If type is set to kMultiStateItemType, then
		kOnPageLoad is reaturned as kOnStateLoad string.
		@param consolidateButtonEvent is true if to ignore specific button events and return as a generic button event string.
		@return the corresponding event trigger string.
	*/
	virtual  PMString GetStringFromEventTrigger (const EventTriggerType& trigger, const ISpreadDynamicContentMgr::DynamicContentType& type = ISpreadDynamicContentMgr::kAnimationItemType, bool consolidateButtonEvet = false ) const = 0;

	/**	Returns the page item animation's first and last keyframe values.
		@param position the first and last keyframe position of the page item at run-time. The coordinate is the flash coordinate. The default is the (0,0).
		If there no motion path  for this animation, the position vector is empty.
		@param scale is the first and last  keyframe value for scale x and scale y percentages at run-time. The defaullt is 100%
		@param rotationAngle is the first and last  keyframe value for the rotation angle in degree at run-time. The default is 0 degree.
		@param opacity is the first and last  keyframe value for the opacity property at run-time. The default is 100%.
		@return true if successfully.
	*/
	virtual bool GetPageItemAnimationFirstLastKeyframeValues (const UIDRef& pageItemRef, std::vector<PMPoint>& position, std::vector<PMPoint>& scale, std::vector<PMReal>& rotationAngle, std::vector<PMReal>& opacity) const = 0;

	/**	Returns true if animation is allowed for the specified page item.
		@param targetRef is the target page item's UIDRef.
		@return true is animation is allowed.
	*/
	virtual bool AnimationAllowedForPageItem (const UIDRef& targetRef) const = 0;

	/**	Returns the spread UID the target page item is on.
		@param targetRef is the target page item's UIDRef.
		@return the spread UID the target page item is on.
	*/
	virtual UID GetParentSpreadUID (const UIDRef& targetRef) const = 0;

	/**	Returns the timing parent UID that is the also the ancestor for this target page item.
		Timing parent UID could be the spread or a MSO state.
		@param targetRef is the target page item's UIDRef.
		@return the timing parent UID for this target page item.
	*/
	virtual UID GetTimingParentUID (const UIDRef& targetRef) const = 0;

};