//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationFacade.h $
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

#include "IAnimationCmdData.h"
#include "WideString.h"
#include "Utils.h"

class IAnimationAttributeData;
class IAnimationData;
class ISubject;
class IDocument;

namespace Facade
{
	/** This facade provides services for obtaining and modifying the animation setting
		for the page items. For CS5, only one animation per page item is supported.
		The main data interface is IAnimationAttributeData.
		@see IAnimationAttributeData.h

		The animation settings include the followings:
			- motion preset - this is a flash motion preset. 
				@see IMotionPresetMgr.h
				@see IMotionPresetData.h
			- animation duration
			- number of time the animation plays
			- transform offset point
			- motion path
			- opacity
			- rotation
			- scale x and y

		This facade doesn't attempt to cover everything related to animation. For services
		related to motion preset, there's a IMotionFacade.
		@see IMotionFacade.h
			
	*/

class IAnimationFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANIMATIONFACADE };
		
	/** Return true if this page item has animation.
		@param pageItemRef is the page item.
		@return true if page item has animation; otherwise false.
	*/
	virtual bool PageItemHasAnimation (const UIDRef& pageItemRef) const = 0;

	/** Return true if this page item has custom animation settings.
		@param pageItemRef is the page item.
		@return true if page item has custon animation; otherwise false.
	*/
	virtual bool PageItemHasCustomAnimationSettings (const UIDRef& pageItemRef) const = 0;
	
	/** Return true if this page item or one of its children has animation.
		@param pageItemRef is the page item.
		@param pAnimationList, a list of animation items is returned in pAnimationList if it is not nil.
		@return true if at least one item has animation; otherwise false.
	*/
	virtual bool PageItemAndChildrenHaveAnimation (const UIDRef& pageItemRef, UIDList* pAnimationList = nil) const = 0;

	/** Apply a motion preset to page item's animation.
		@param pageItemRef is the page item.
		@param presetRef is the motion preset to apply.
		@param skipTargeting is true if not to add this object to its default triggering event.
		@param doForceCreateNew is true if to create new preset in the document even if a preset with the
		same name one already exist. The default is false.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode SetPageItemMotionPreset (const UIDRef& pageItemRef, const UIDRef& presetRef, bool skipTargeting = false, bool doForceCreateNew = false) = 0;
		
	/** Gets the motion preset applied to page item's animation.
		@param pageItemRef is the page item.
		@return UIDRef of the motion preset applied..
	*/
	virtual UIDRef GetPageItemMotionPreset (const UIDRef& pageItemRef) const = 0;

	/** Gets animation duration from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@return animation duration.
	*/
	virtual PMReal GetPageItemAnimationDuration (const UIDRef& pageItemRef) const = 0;

	/** Sets animation duration for the page item..
		@param pageItemRef is the UIDRef of the page item.
		@param duration is the new duration to apply to the selection.
	*/
	virtual bool SetPageItemAnimationDuration (const UIDRef& pageItemRef, const PMReal& duration) = 0;

	/** Gets animation transform offset point.
		@param pageItemRef is the UIDRef of the page item.
		@return animation transform offset point.
	*/
	virtual PMPoint GetPageItemAnimationTransformOffsetPoint (const UIDRef& pageItemRef) const = 0;

	/** Sets the animation transform offset point.
		@param pageItemRef is the UIDRef of the page item.
		@param animation transform offset point to apply to the selection.
	*/
	virtual bool SetPageItemAnimationTransformOffsetPoint (const UIDRef& pageItemRef, const PMPoint& offsetPoint) = 0;

	/** Gets the animation option from the page item.
		@return the animation option.
	*/
	virtual AnimationOptions GetPageItemAnimationOption (const UIDRef& pageItemRef) const = 0;

	/** Sets the animation option for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param animateOption the animation option to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationOption (const UIDRef& pageItemRef, const AnimationOptions& animateOption) = 0;

	/**	Returns true if page item is hidden until animated.
		@param pageItemRef is the UIDRef of the page item.
		@return true if page item is hidden until animated.
	*/
	virtual bool GetPageItemAnimationHideInitially(const UIDRef& pageItemRef) const = 0;

	/**	Sets the page item's run-time visibility to be hidden until animated.
		@param pageItemRef is the UIDRef of the page item.
		@param setHiddenTillAnimated is true if to set object to be hidden till animated.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationHideInitially (const UIDRef& pageItemRef, bool setHiddenTillAnimated) = 0;

	/**	Returns true if page item is hidden after animated.
		@param pageItemRef is the UIDRef of the page item.
		@return true if page item is hidden after animated.
	*/
	virtual bool GetPageItemAnimationHideAfter (const UIDRef& pageItemRef) const = 0;

	/**	Sets the page item's run-time visibility to be hidden after animated.
		@param pageItemRef is the UIDRef of the page item.
		@param setHiddenAfterAnimated is true if to set object to be hidden after animated.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationHideAfter (const UIDRef& pageItemRef, bool setHiddenAfterAnimated) = 0;

	/** Gets number of times animation plays from the page item.
		@return number of times the animation plays.
	*/
	virtual uint32 GetPageItemAnimationPlays (const UIDRef& pageItemRef) const = 0;

	/** Sets number of times animation plays for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param numPlays the number to time the animation should play.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationPlays (const UIDRef& pageItemRef, uint32 numPlays) = 0;

	/** @return true if page item animation is set to loop.
	*/
	virtual bool GetPageItemAnimationPlaysLoop (const UIDRef& pageItemRef) const = 0;

	/** Sets page item animation to loop.
		@param pageItemRef is the UIDRef of the page item.
		@param setToLooop is true if animation is set to loop.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationPlaysLoop (const UIDRef& pageItemRef, bool setToLoop) = 0;

	/** Gets the simple animation ease type from the page item.
		@return simple ease type.
	*/
	virtual AnimationEaseType GetPageItemAnimationSimpleEaseType (const UIDRef& pageItemRef) const = 0;

	/** Sets the simple animation ease type for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param easeType the simple ease type to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationSimpleEaseType (const UIDRef& pageItemRef, const AnimationEaseType& easeType) = 0;

	/** Gets animation motion path from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param path is the motion path.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationMotionPath (const UIDRef& pageItemRef, AnimationPathDataList& path) const = 0;

	/** Sets animation path for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param path is the animation path to apply.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationMotionPath (const UIDRef& pageItemRef, const AnimationPathDataList& path) = 0;

	/** Gets animation motion path point list without the keyframes from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param path is the motion path.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationMotionPath (const UIDRef& pageItemRef, PMPathPointList& path) const = 0;

	/** Sets animation path for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param path is the animation path to apply. Path is applied evenly over the duration.
		If the page item has an old path, it is removed first.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationMotionPath (const UIDRef& pageItemRef, const PMPathPointList& path) = 0;

	/** Sets animation path for the page item from another page item.
		@param pageItemRef is the UIDRef of the page item to apply to.
		@param sourcePageItemRef is the UIDRef of the source page item from which to extract the 0th path. Then sourcePageItemRef will be deleted if specified, see next parameter.
		@param bDeleteItem if kTrue the sourcePageItemRef is deleted, if kFalse it is not.
		@return true if successful otherwise returns false
		@see CreateAnimationMotionPathPageItem
	*/
	virtual bool SetPageItemAnimationMotionPath (const UIDRef& pageItemRef, const UIDRef& sourcePageItemRef, bool bDeleteItem) = 0;

	/** Given an interface for an item with a motion path, create a new page item from the motion path points and select it.
		@param pageItemRef is the UIDRef of the page item to created a motion path item from.
		@return the UIDRef of the created item.
		@see SetPageItemAnimationMotionPath
	 */
	virtual UIDRef CreateAnimationMotionPathPageItem(const UIDRef& pageItemRef) = 0;

	/** Given an interface for an item with a motion path (uses IID_ISPLINESTATEMOTIONPAGEITEMDATA), delete the page item (optionally) and remove data reference for it from the document.
		@param IDocument, the document to delete the motion page item from.
		@param bDeleteItem, kTrue to delete the motion path item. kFalse will just remove the reference for it from the document (IID_ISPLINESTATEMOTIONPAGEITEMDATA)
		@return kSuccess otherwise an error code.
		@see CreateAnimationMotionPathPageItem
	 */
	virtual ErrorCode DeleteAnimationMotionPathPageItemData(IDocument* document, bool16 bDeleteItem) = 0;

	/** Given a page item ref and a motion path page item ref, translate the page item (pageItemRef) to be aligned
		with the motion path page item. Used after the motion path item is edited (e.g. moved, resized, path points altered)
		so the page item is "synced" up to the upper left of the motion path page item (taking into account the offset point).
		@param pageItemRef is the UIDRef of the page item with animation applied.
		@param motionPathPageItemRef is the UIDRef of the motion path.
		@return true if successful otherwise returns false
	 */
	virtual bool SyncPageItemWithMotionPath(const UIDRef& pageItemRef, const UIDRef& motionPathPageItemRef) = 0;
	
	/**	Return true if page item is a special animation motion path page item.
		This object is used to manimupate page item's motion path only and cannot be edited otherwise.
		@param pageItemRef is the UIDRef of the animation motion path page item.
		@return true if page item is a special animation motion path page item.
	*/
	virtual bool IsPageItemMotionPathPageItem (const UIDRef& pageItemRef) const = 0;

	/** Gets number of keyframes for the animation's property.
		@param pageItemRef is the UIDRef of the page item.
		@param propType is the property to get
		@return number of keyframes.
	*/
	virtual uint32 GetPageItemAnimationOpacityKeyFrameCount (const UIDRef& pageItemRef) const = 0;

	/** Gets animation property nth keyframe and value from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param which is the nth keyframe.
		@param keyframe is the keyframe returned.
		@param value is the value at keyframe.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationOpacityKeyFrame (const UIDRef& pageItemRef, int32 which, uint32& keyframe, PMReal& value) const = 0;

	/** Gets animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetPageItemAnimationOpacityValueAtKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, PMReal& value) const = 0;
	
	/** Sets animation property value at the specified keyframe for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationOpacityKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, const PMReal& value = 0) = 0;

	/** Removes animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemovePageItemAnimationOpacityKeyFrame (const UIDRef& pageItemRef, uint32 keyframe) = 0;

	/** Removes all animation property keyframes from the page item.
		@param pageItemRef is the UIDRef of the page item.
	*/
	virtual bool RemovePageItemAnimationOpacityAllKeyFrames (const UIDRef& pageItemRef) = 0;
	
	/** Gets number of keyframes for the animation's property.
		@param pageItemRef is the UIDRef of the page item.
		@return number of keyframes.
	*/
	virtual uint32 GetPageItemAnimationRotationKeyFrameCount (const UIDRef& pageItemRef) const = 0;

	/** Gets animation property nth keyframe and value from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param which is the nth keyframe.
		@param keyframe is the keyframe returned.
		@param value is the value at keyframe.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationRotationKeyFrame (const UIDRef& pageItemRef, int32 which, uint32& keyframe, PMReal& value) const = 0;

	/** Gets animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetPageItemAnimationRotationValueAtKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, PMReal& value) const = 0;
	
	/** Sets animation property value at the specified keyframe for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationRotationKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, const PMReal& value = 0) = 0;

	/** Removes animation property value at the specified keyframe ifrom the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemovePageItemAnimationRotationKeyFrame (const UIDRef& pageItemRef, uint32 keyframe) = 0;

	/** Removes all animation property keyframes from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@return true if successful otherwise returns false,
	*/
	virtual bool RemovePageItemAnimationRotationAllKeyFrames (const UIDRef& pageItemRef) = 0;

	/** Gets number of keyframes for the animation's property.
		@param propType is the property to get
		@return number of keyframes.
	*/
	virtual uint32 GetPageItemAnimationScaleXKeyFrameCount (const UIDRef& pageItemRef) const = 0;

	/** Gets animation property nth keyframe and value from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param which is the nth keyframe.
		@param keyframe is the keyframe returned.
		@param value is the value at keyframe.
	*/
	virtual bool GetPageItemAnimationScaleXKeyFrame (const UIDRef& pageItemRef, int32 which, uint32& keyframe, PMReal& value) const = 0;

	/** Gets animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationScaleXValueAtKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, PMReal& value) const = 0;
	
	/** Sets animation property value at the specified keyframe for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationScaleXKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, const PMReal& value = 0) = 0;

	/** Removes animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe to remove.
		@return true if successful otherwise returns false,
	*/
	virtual bool RemovePageItemAnimationScaleXKeyFrame (const UIDRef& pageItemRef, uint32 keyframe) = 0;

	/** Removes all animation property keyframes from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@return true if successful otherwise returns false,
	*/
	virtual bool RemovePageItemAnimationScaleXAllKeyFrames (const UIDRef& pageItemRef) = 0;

	/** Gets number of keyframes for the animation's property.
		@param pageItemRef is the UIDRef of the page item to get.
		@return number of keyframes.
	*/
	virtual uint32 GetPageItemAnimationScaleYKeyFrameCount (const UIDRef& pageItemRef) const = 0;

	/** Gets animation property nth keyframe and value from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param which is the nth keyframe.
		@param keyframe is the keyframe returned.
		@param value is the value at keyframe.
	*/
	virtual bool GetPageItemAnimationScaleYKeyFrame (const UIDRef& pageItemRef, int32 which, uint32& keyframe, PMReal& value) const = 0;

	/** Gets animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe.
		@return true if successful otherwise returns false,
	*/
	virtual bool GetPageItemAnimationScaleYValueAtKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, PMReal& value) const = 0;
	
	/** Sets animation property value at the specified keyframe for the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe.
		@param value is the value at keyframe to set.
		@return true if successful otherwise returns false,
	*/
	virtual bool SetPageItemAnimationScaleYKeyFrame (const UIDRef& pageItemRef, uint32 keyframe, const PMReal& value = 0) = 0;

	/** Removes animation property value at the specified keyframe from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@param keyframe is the keyframe to remove.
		@return true if successful otherwise returns false,
	*/
	virtual bool RemovePageItemAnimationScaleYKeyFrame (const UIDRef& pageItemRef, uint32 keyframe) = 0;

	/** Removes all animation property keyframes from the page item.
		@param pageItemRef is the UIDRef of the page item.
		@return true if successful otherwise returns false,
	*/
	virtual bool RemovePageItemAnimationScaleYAllKeyFrames (const UIDRef& pageItemRef) = 0;

	/** Update page item's which animation data from the which animation data of iNewAnimaData.
		@param pageItemRef is the page item.
		@param iNewAnimaData is the new animation data.
		@param flags is the data flags indicating set to set.
		@param skipTargeting is true if not to add this object to its default triggering event.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode UpdatePageItemAnimationData (const UIDRef& pageItemRef, const IAnimationData* iNewAnimaData, const uint32& dataSetFlags, bool skipTargeting = false) = 0;
	
	/** Add a new animation to the page item.
		@param pageItemRef is the page item.
		@param iNewAnimaData is the new animation data to add.
		@param flags is the data flags indicating set to set.
		@param skipTargeting is true if not to add this object to its default triggering event.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode AddPageItemAnimation (const UIDRef& pageItemRef, const IAnimationData* iNewAnimaData, const uint32& dataSetFlags, bool skipTargeting = false) = 0;
	
	/** Remove page item's animation.
		@param pageItemRef is the page item.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode RemovePageItemAnimation (const UIDRef& pageItemRef) = 0;

	/** Remove page item's and its children's animation.
		@param pageItemRef is the page item.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode RemovePageItemAndChildrenAnimation (const UIDRef& pageItemRef) = 0;

	/** Save page item's animation as custom preset.
		@param pageItemRef is the page item.
		@param newPresetName is the new custom preset name.
		@param newCustomRef contains the new custom preset UIDRef.
		@param doApply if true will apply the new custom preset to the page item.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode SavePageItemAnimation (const UIDRef& pageItemRef, const PMString& newPresetName, UIDRef& newCustomRef, bool doApply = true) = 0;

	/** Save page item's animation as a copy of motion preset file.
		@param pageItemRef is the page item.
		@param newPresetFile is the new preset file name.
		@return kSuccess otherwise an error code.
	*/
	virtual ErrorCode SaveACopyPageItemAnimation (const UIDRef& pageItemRef, const IDFile& newPresetFile) = 0;
};

};	// namespace