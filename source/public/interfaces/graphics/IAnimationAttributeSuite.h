//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationAttributeSuite.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IAnimationAttributeSuite__
#define __IAnimationAttributeSuite__

#include "ISelectionMessages.h"
#include "AnimationTypes.h"

#include "DynamicDocumentsID.h"

/**	This is the high level animation attribute suite for the current selection.
	The animation attributes are represented by one data interface, IID_IANIMATIONATTRIBUTEDATA.
	The settings that are allowed are:

		motion preset
		duration of the animation
		number of time the animation plays
		animation path offset
		a list of keyframe properties:
			motion path
			opacity
			rotation
			scale x
			scale y
	
	Additionally, page event triggering the animation can be added or removed.
	Animation can be self-triggered. When it is self-triggered by roll off, the
	animation can bet set to play in reverse.
	
	@see AnimationTypes.h
	@see IAnimationAttributeData.h
	@see IDynamicEventTimingMgr.h
	@see IDynamicEventTimingFacade.h
*/
class IAnimationAttributeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANIMATIONATTRIBUTESUITE };
	
	//________________________________________________________________________________________
	//	Data Types
	//________________________________________________________________________________________
	enum PropertyType {
		kAnimationOpacity = 0,
		kAnimationRotation,
		kAnimationScaleX,
		kAnimationScaleY,
	};

public:

	/** Returns true if current selection contains multiple selections.
s	*/
	virtual bool HasMultipleSelections () const = 0;

	/**	Apply the spcified motion preset to the current selection.
		@param presetRef is the preset to apply
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode ApplyMotionPreset (const UIDRef& presetRef) = 0;
	
	/**	Checks if motion preset can be applied to the selection.
		@return true if selection has at least one item and item can have motion preset applied.
	*/
	virtual bool CanApplyMotionPreset (void) const = 0;

	/**	Gets the motion preset UID applied to the selection.
		@return true if it is an unique preset; return false if mixed.
	*/
	virtual bool GetMotionPresetApplied (UID& presetUID) const = 0;

	/**	Checks if animation can be applied to the selection.
		@return true if selection contains at least one item and item can have attribute applied.
	*/
	virtual bool CanApplyAnimation (void) const = 0;

	/**	Return the name of the app preset applied.
		If mixed selection, an empty string is returned.
		@param the name of the app preset applied before custom settings.
		@return true if selection is unique.
	*/
	virtual bool GetBaseMotionPresetNameApplied (PMString& presetName) const = 0;

	/**	Returns true if selection can be a target of an MSO state timing manager.
		@param pMixed if not nil is set to true if mixed selection.
		@returns true if selection can be a target of an MSO state timing manager.
	*/
	virtual bool HasMSOAsTimingParent (bool* pMixed = nil) const = 0;

	/**	Return true if one of more items in the selection have animation applied.
		@param pMixed if not nil is set to true if mixed selection.
		@return true if selection has animation applied.
	*/
	virtual bool HasAnimationApplied (bool* pMixed = nil) const = 0;

	/**	Returns true if selection has custom animation settings applied.
		@param pMixed if not nil is set to true if mixed selection.
		@return true if selection has custom animation settings applied.
	*/
	virtual bool HasCustomAnimationSettings (bool* pMixed = nil) const = 0;

	/**	Set to true if to show a proxy for end of animation in the layout window when object is selected.
		This is a document view setting and not a selection based setting.
		@param turnOn is true is to show a proxy.
	*/
	virtual void SetShowAnimationProxy (bool turnOn) = 0;

	/**	@return true if to show a proxy for end of animation in the layout window/
	*/
	virtual bool GetShowAnimationProxy () const = 0;

	/**	Get name of page item
		Note that this is the same as setting name through IPageItemNameFacade.h
		@see IPageItemNameFacade.h
		@param name is the page item name returned.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetName (PMString& name) const = 0;

	/**	Set name of page item
		Note that this is the same as setting name through IPageItemNameFacade.h
		@see IPageItemNameFacade.h
		@param newName the new page item name to set.
		@return true if successful.
	*/
	virtual bool SetName (const PMString& newName) = 0;

	/**	Get page item hidden initially setting. 
		@param hideInitially is the page item hidden initially setting.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetAnimationHideInitially (bool& hideInitially) const = 0;

	/**	Set the flag to true if page item should be hidden until animated.
		@param hiddenUntilAnimated is true if hidden until animated.
		@return true if successful, otherwise returns false.
	*/
	virtual bool SetAnimationHideInitially (bool hiddenUntilAnimated) = 0;

	/**	Get page item hidden after setting. 
		@param hideAfter is the page item hidden after animated setting.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetAnimationHideAfter (bool& hideAfter) const = 0;

	/**	Set the flag to true if page item should be hidden after animated.
		@param hideAfter is true if hidden after animated.
		@return true if successful, otherwise returns false.
	*/
	virtual bool SetAnimationHideAfter (bool hideAfter) = 0;

	/** Gets animation duration in the selection.
		@param duration is the animation duration.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetAnimationDuration (PMReal& duration) const = 0;

	/** Sets animation duration in the selection.
		@param duration is the new duration to apply to the selection.
	*/
	virtual bool SetAnimationDuration (const PMReal& duration) = 0;

	/** Sets number of times the animation plays in the selection.
		@param numPlays is the number of times animation plays to apply to the selection.
	*/
	virtual bool SetAnimationPlays (const uint32& numPlays) = 0;

	/** Gets number of times animation plays in the selection.
		@param numPlays is the number of times the animation plays.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetAnimationPlays (uint32& numPlays) const = 0;

	/**	Get the animation's loop setting.
		@param playsLoop is true if animation is set to loop in the selection.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetAnimationPlaysLoop (bool& playsLoop) const = 0;

	/**	Sets animation to loop for the current selection.
		@param setToLoop is true if to set animation to loop.
		@return true if successful, otherwise returns false.
	*/
	virtual bool SetAnimationPlaysLoop (bool setToLoop) = 0;

	/**	Get the applicable trigger events for the current selection.
		@param applicableList is the list of applicable trigger events that can be assigned for the 
		current selection (excluding button events).
		@return true if unique selection otherwise false if mixed or multiple selection.
	*/
	virtual bool GetApplicableTriggerEvents (std::vector<EventTriggerType>& applicableList) const = 0;

	/**	Gets the number of event triggers.
		@param numTriggers is the number of event triggers for this selection.
		@return true if unique selection otherwise false if mixed selection.
	*/
	virtual bool GetNumAnimationTriggerEvents (uint32& numTriggers) const = 0;

 	/** Gets nth animation trigger event in the selection.
		Trigger events can be one of EventTriggerType.
		@see AnimationTypes.h
		@param which is the index in then event triggers list.
		@param triggerEvents is the event trigger to get.
		@return false if there's multiple selection or failed.
	*/
	virtual bool GetNthAnimationTriggerEvent (uint32 which, EventTriggerType& trigger) const = 0;

	/** Adds animation trigger event to the selection. If there's multiple selection, the event
		is added for all items in the selection. If the selection already has the event, it is ignored.
		Animation trigger event can be one of EventTriggerType.
		@see AnimationTypes.h
		@param triggerEvent is the animation trigger events to apply to the selection.
		@return true if seuccessful.
	*/
	virtual bool AddAnimationTriggerEvent (const EventTriggerType& triggerEvent) = 0;

	/** Remove animation trigger events from the selection. If there's mulitple selection, the event
		is removed for all items in the selection. If the selection does not have this event, it is ignored.
		Animation trigger events is one of EventTriggerType.
		@see AnimationTypes.h
		@param triggerEvent is the animation trigger events to remove from the selection.
		@return true if seuccessful.
	*/
	virtual bool RemoveAnimationTriggerEvent (const EventTriggerType& triggerEvent) = 0;

	/** Returns true if animation can be reversed for the specified trigger event in the selection.
		@param triggerEvent is the animation trigger events to reverse animation.
		@return true if animation can be reversed.
	*/
	virtual bool CanReverseAnimationForEvent (const EventTriggerType& triggerEvent) const = 0;

	/** Returns whether or not the animation is reverse for the trigger event in the selection.
		@param triggerEvent is the animation trigger events to reverse animation.
		@param canbeReversed is true if event support reversed animation.
		@return true if to reverse animation.
	*/
	virtual bool GetReverseAnimationForEvent (const EventTriggerType& trigger, bool& canbeReversed) const = 0;

	/** Set animation to reverse for the trigger event in the selection.
		@param triggerEvent is the animation trigger events to reverse animation.
		@setToReverse is true if to reverse animation.
		@return true if successful.
	*/
	virtual bool SetReverseAnimationForEvent (const EventTriggerType& triggerEvent, bool setToReverse) = 0;

	/**	Gets the current animate option from the selection
		@see AnimationTypes.h
		@param animateOption is the current animate option.
		@return false if there's mixed selection or failed.
	*/
	virtual bool GetAnimateOption (AnimationOptions& animateOption) const = 0;
	
	/**	Sets the animate option for the selection.
		@see AnimationTypes.h
		@param animateOption is animation options to set.
		@return true if successful.
	*/
	virtual bool SetAnimateOption (const AnimationOptions& animateOption) = 0;

	/**	Gets the current simple ease type from the selection
		@see AnimationTypes.h
		@param easeType is the current simple ease type.
		@return false if there's mixed selection or failed.
	*/
	virtual bool GetSimpleEaseType (AnimationEaseType& easeType) const = 0;
	
	/**	Sets the simple ease type for the selection.
		@see AnimationTypes.h
		@param easeType is ease type to set.
		@return true if successful.
	*/
	virtual bool SetSimpleEaseType (const AnimationEaseType& easeType) = 0;

	/** Gets animation transform offset point in the selection
		@param offsetPoint is the animation transform offset point.
		@return false if there's mixed selection or failed.
	*/
	virtual bool GetAnimationTranformOffsetPoint (PMPoint& offsetPoint) const = 0;

	/** Sets animation transform offset point.
		@param offsetPoint is the animation offset point to apply.
		@return true if successful.
	*/
	virtual bool SetAnimationTranformOffsetPoint (const PMPoint& offsetPoint) = 0;

	/** Gets animation motion path in the selection
		@param path is the motion path.
		@return false if there's mixed selection or failed.
	*/
	virtual bool GetAnimationMotionPath (AnimationPathDataList& path) const = 0;

	/** Sets animation path in the selection.
		It will not be possible to set animation path when there's multiple items in the selection.
		@param path is the animation path to apply.
	*/
	virtual bool SetAnimationMotionPath (const AnimationPathDataList& path) = 0;

	/** Gets animation motion path in the selection
		@param path is the motion path is a list of path points.
		@return false if there's mixed selection or failed.
	*/
	virtual bool GetAnimationMotionPath (PMPathPointList& path) const = 0;

	/** Sets animation path in the selection. The path is set evenly over the duration.
		If there's an existing path, the old path is removed first.
		It will not be possible to set animation path when there's multiple items in the selection.
		@param path is the animation path to apply. 
		path is specified as a list of path points.
		@return true if successful otherwise returns false.
	*/
	virtual bool SetAnimationMotionPath (const PMPathPointList& path) = 0;

	/** Sets animation path in the selection. There must be two items selected.
		If one item has animation applied, it is
		removed and the path geometry PMPathPointList from the other is used.
		If there's an existing path, the old path is removed first.
		If neither item has animation applied, the top item is used as the source for apply motion
		to the other item.
		@return true if successful otherwise returns false.
	*/
	virtual bool CanSetAnimationMotionPathFromSelection () const = 0;

	/** Sets animation path in the selection. There must be two items selected.
		If one item has animation applied, it is
		removed and the path geometry PMPathPointList from the other is used.
		If there's an existing path, the old path is removed first.
		If neither item has animation applied, the top item is used as the source for apply motion
		to the other item.
		@return true if successful otherwise returns false.
	*/
	virtual bool SetAnimationMotionPathFromSelection () = 0;

	/** Determine if animation motion path be be updated. There must be a motion path item selected.
		@return true if successful otherwise returns false.
	*/
	virtual bool CanUpdateAnimationMotionPathFromSelection () const = 0;

	/** Updates animation path in the selection. There must be a motion path item selected.
		The motion path's path geometry is used to generate a PMPathPointList and then
		update the main item. User is still left in motion editing state with motion item selected.
		@return true if successful otherwise returns false.
	*/
	virtual bool UpdateAnimationMotionPathFromSelection () = 0;

	/**	Short hand to refer to first and last keyframe for the given property.
	*/
	enum {
		kFirstKeyFrame = 0,
		kLastKeyFrame = 0xffffffff
	};

	/** Gets total number of frames for the duration of animation.
		@param numFrames is the total number of frames.
	*/
	virtual bool GetTotalNumFrames (uint32& numFrames) const = 0;

	/** Gets number of keyframes for the animation's property.
		@param propType is the property to get
		@param numKeyFrames is the number of keyframes.
		@return false if there's multiple selection or failed.
	*/
	virtual bool GetNumKeyFrames (const PropertyType& propType, uint32& numKeyFrames) const = 0;

	/** Gets animation property nth keyframe and value in the selection.
		@param propType is the property to get
		@param which is the nth keyframe.
		@param keyframe is the keyframe returned.
		@param value is the value at keyframe.
		@return false if there's multiple selection or failed.
	*/
	virtual bool GetKeyFrame (const PropertyType& propType, int32 which, uint32& keyframe, PMReal& value) const = 0;

	/** Gets animation property value at the specified keyframe in the selection.
		@param propType is the property to get
		@param keyframe is the keyframe. keyframe can also be set to either kFirstKeyFrame or kLastKeyFrame.
		@param value is the value at keyframe.
		@return false if there's multiple selection or failed.
	*/
	virtual bool GetValueAtKeyFrame (const PropertyType& propType, uint32 keyframe, PMReal& value) const = 0;
	
	/** Sets animation property value at the specified keyframe in the selection.
		@param propType is the property to set
		@param keyframe is the keyframe. keyframe can also be set to either kFirstKeyFrame or kLastKeyFrame.
		@param value is the value at keyframe to set.
		@return false if there's multiple selection or failed.
	*/
	virtual bool SetKeyFrame (const PropertyType& propType, uint32 keyframe, const PMReal& value = 0) = 0;

	/** Removes animation property value at the specified keyframe in the selection.
		@param propType is the property to remove.
		@param keyframe is the keyframe to remove. keyframe can also be set to either kFirstKeyFrame or kLastKeyFrame.
		@return false if there's multiple selection or failed.
	*/
	virtual bool RemoveKeyFrame (const PropertyType& propType, uint32 keyframe) = 0;

	/** Removes all animation property keyframes in the selection.
		@param propType is the property to remove.
		@return false if there's multiple selection or failed.
	*/
	virtual bool RemoveAllKeyFrames (const PropertyType& propType) = 0;

	/** Return true if can save current page item animation settings.
		This is possible only if there's an unique selection. Otherwise
		returns false if multiple selection.
		@return true if can save current page item animation settings.
	*/
	virtual bool CanSaveAnimationSettings () const = 0;

	/** Save current selection animation settings and reload as preset.
		@return true if successful otherwise returns false.
	*/
	virtual bool SaveAnimationSettings (const PMString& newPresetName) = 0;
	
	/** 
		This is possible only if there's an unique selection. Otherwise
		returns false if multiple selection.
		@return true if can save a copy of the current animation preset and settings to a file.
	*/
	virtual bool CanSaveACopyAnimationSettings () const = 0;

	/** Save a copy of the current selection animation settings as a preset file.
		@return true if successful otherwise returns false.
	*/
	virtual bool SaveACopyAnimationSettings (const IDFile& newPresetFile) = 0;

	/** 
		@return true if can remove current animation preset.
	*/
	virtual bool CanRemoveAnimationPreset () const = 0;

	/** Remove the animation preset associated with the current selection from the
		preset list and remove animation settings from the current selection.
		If multiple selection, animation is removed from all items in the selection.
		@return true if successful otherwise returns false.
	*/
	virtual bool RemoveAnimationPreset () = 0;
};



#endif	// __IAnimationAttributeSuite__

