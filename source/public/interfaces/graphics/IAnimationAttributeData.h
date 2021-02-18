//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationAttributeData.h $
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
#ifndef __IAnimationAttributeData__
#define __IAnimationAttributeData__

#include "IPMUnknown.h"

#include "IAnimationData.h"
#include "PMPathPoint.h"

/** This is the data interface for page item animation attribute data.
	@see also IAnimationData.h
*/
class IAnimationAttributeData : public IPMUnknown
{
public:

	enum {kDefaultIID = IID_IANIMATIONATTRIBUTEDATA};

	/** Return true if we have animation data.
		@return true if we have animation data.
	*/
	virtual bool HasAnimation () const = 0;

	/**	Add an animation with this motion preset. presetUID can be kInvalidUID.
		@param presetUID is the motion preset for the animation.
		@param populateData is set to true if properties from the preset are extracted and set to this animation.
		If this flag is set to true and if there are previously set animation data, 
		they will be replaced with the data from the preset.
		@return true if successful.
	*/
	virtual bool AddAnimation (UID presetUID, bool populateData = true) = 0;

	/**	Remove the animation.
		@return true if successful.
	*/
	virtual bool RemoveAnimation () = 0;

	/**	IAnimationData interface is not persistent data interface. It is to facilitate
		getting animation data for temporary use and setting up animation data for
		applying updates. In particular, it is used mainly in to represent a
		temporary scripting animation data object.
	*/

	/** Returns a copy of the animation data
		@note The IAnimationData returns is a temporary representation
		of this animation data. It does not provide direct access to the actual data.
		To access animation data directly, use the individual get/set methods.

		@return the clone of the animation data.
	*/
	virtual IAnimationData* CloneAnimation () const = 0;

	/** Returns the animation data.
		@note The IAnimationData returns is a temporary representation
		of this animation data. It does not provide direct access to the actual data.
		This data interface is readonly.
		To access animation data directly, use the individual get/set methods.

		@return the animation data.
	*/
	virtual const IAnimationData* QueryAnimation () const = 0;

	/** Returns true if animation has custom changes.
		@return true if animation has changes.
	*/
	virtual bool AnimationHasCustomChanges () const = 0;

	/**	Set the preset UID for the animation.
		@param presetUID is the motion preset UID to set.
		@param populateData is set to true if properties from the preset are extracted and set to this animation.
		If this flag is set to true and if there are previously set animation data, 
		they will be replaced with the data from the preset.
	*/
	virtual bool SetPresetUID (UID presetUID, bool populateData = true) = 0;

	/**	Returns the preset UID associated with the animation.
		@return the preset UID.
	*/
	virtual UID GetPresetUID () const = 0;

	/**	Sets the number of times this animation should play when triggered.
		@return the number plays to set.
	*/
	virtual bool SetNumPlays (uint32 numPlays) = 0;
	
	/**	Returns the number of times this animation should play when triggered.
		@return the number plays.
	*/
	virtual uint32 GetNumPlays () const = 0;

	/**	@return true if animation is set to loop.
		If animation is set to loop, then number of plays is ignored.
	*/
	virtual bool GetPlaysLoop () const = 0;

	/**	Sets animation to loop.
		@param setToLoop is true if to set animation to loop.
		If animation is set to loop, then number of plays is ignored.
	*/
	virtual bool SetPlaysLoop (bool setToLoop) = 0;

	/** An animation by definition occurs over an duration, typically measured in seconds. 
		The frame rate, the speed the animation is played at, is measured in number of frames per second.
		The timeline covers an entire animation can be divided into frames. The total number of frames
		(or key frames) for the duration of animation is eqaul to (frame rate) * (duration in second).
		
		Therefore changing the duration for the animation will change the total number of frames over time.
		Likewise, changing the frame rate will not change the duration but changes the total number of frames.
		
		A keyframe marks a specific point in the animation timeline. A frame rate too slow will make the animation
		appears stop and go. A frame rate too fast blurs the animation details. The default frame rate is 24 fps.
		
		Properties at a specified keyframe can be changed by methods described below. Property keyframe count
		is the number of property keyframes that contains changes for a specified keyframe. These property changes
		defines the details for an animation.

		For this release, these properties can be modified: motion path, opacity, rotation, scale x and y.

	*/

	/**	Sets the duration in second for the animation.
		@param durationInSecond is duration to set.
	*/
	virtual bool SetDuration (const PMReal& durationInSecond) = 0;

	/**	Gets the duration in second for the animation.
		@return the duration.
	*/
	virtual PMReal GetDuration () const = 0;

	/**	Sets the frame rate for the animation. 
		The frame rate is the number of frames per second for this animation.
		Total number of keyfames is equal to (frame rate) * (durationInSecond).
		Therefore, chaning frame rate does not affect the duration but affects only
		total number of frames.
		@param frameRate is the number of frames per second to set.
	*/
	virtual bool SetFrameRate (int32 frameRate) = 0;
	
	/**	Gets the frame rate for the animation.
		@return the frame rate.
	*/
	virtual int32 GetFrameRate () const = 0;

	/**	Animation option allows the control to how the animation is played.
		There are three options. The default is kAnimatefrom where the animation is
		played normally. kAnimateTo is to play the animation in reverse back to the
		position where the object is as designed. kAnimateOffset is to play the animation 
		starting with an offset that is the width and height of the entire motion path such
		that at the of the animation, the object would be at the position it is designed for.
		@see AnimationTypes.h
	*/

	/**	@return the animate option.
	*/
	virtual AnimationOptions GetAnimateOption () const = 0;
	
	/**	Sets the animate option.
		@param animateOption is the animate option to set.
	*/
	virtual bool SetAnimateOption (const AnimationOptions& animateOption) = 0;

	/**	@return true if object is hidden until animated.
	*/
	virtual bool GetHideInitially () const = 0;

	/**	Sets object run-time visibility to be hidden until animated.
		@param setHidden is true if object is hidden till animated.
		@return true if successful.
	*/
	virtual bool SetHideInitially (bool setHideInitially) = 0;

	/**	@return true if object is hidden after animated.
	*/
	virtual bool GetHideAfter() const = 0;

	/**	Sets object run-time visibility to hide after animated.
		@param setHideAfter is true if object is hidden after animated.
		@return true if successful.
	*/
	virtual bool SetHideAfter (bool setHideAfter) = 0;

	/**	Easing is a technique that Flash uses to calculate the property values between property keyframes.
		When no easing is specified, the change to the property value is the same in each frame. 
		With easing, the rate of change to the values is adjusted.
		The simple ease is mapped to a predefined Flash ease type. It is a quadratic curve. 
		The rate of change follows the predefined quadratic function.
		@see AnimationTypes.h
	*/

	/**	@return the simple ease type.
	*/
	virtual AnimationEaseType GetSimpleEaseType () const = 0;
	
	/**	Sets the simple ease type.
		@param easeType is ease type to set.
	*/
	virtual bool SetSimpleEaseType (const AnimationEaseType& easeType) = 0;

	/**	Set the transform point for whichAnimation. The transform point specified the offset percentage (0.0 to 1.0)
		relative to the target object the animation path motion starts.
		@param offsetPoint is the offset percent point to set.
	*/
	virtual bool SetTransformOffsetPoint (const PMPoint& offsetPoint) = 0;
	
	/**	Gets the transform point for the animation.
		@return transform offset point.
	*/
	virtual PMPoint GetTransformOffsetPoint () const = 0;
	
	/**	Returns true if animation motion path is roving path.
		@return true if path is roving path.
	*/
	virtual bool HasRovingPath () const = 0;

	/**	Gets the 2D motion path for the animation.
		The path is a list of keyframe and path point pairs. The path points
		represents the motion path.
		@param pathFrames is the keyframe path to get.
	*/
	virtual bool Get2DKeyFramePath (AnimationPathDataList& pathFrames) const = 0;
	
	/**	Gets the 2D motion path point for the animation.
		The path returns is a list of path points representing the motion path.
		@param path is the path to get.
		@param pathIsRoving is true if roving path; otherwise path points have keyframe association.
	*/
	virtual bool Get2DPathPoints (PMPathPointList& path, bool& pathIsRoving) const = 0;
	
	/**	Sets the 2D motion path for the animation.
		The path specified a list of keyframe and path point pairs. 
		@param pathFrames is the keyframe path to set.
	*/
	virtual bool Set2DKeyFramePath (const AnimationPathDataList& path) = 0;
	
	/**	Sets the 2D motion path point for the animation. path is a list of path points
		representing the new motion path. 
		If path is not a roving path, then this path replaces the existing path at the already specified keyframes. 
		It assumes that the number of path points is the same
		as the keyframe count.
		@param path is the path to set.
		@param pathIsRoving is true if path is roving path.
	*/
	virtual bool Set2DPathPoints (const PMPathPointList& path, bool pathIsRoving) = 0;

	/**	Gets the opacity keyframe count for the animation. The keyframe count is
		the number of opacity keyframes that contain custom values.
		@return the opacity keyframe count.
	*/
	virtual uint32 GetOpacityKeyFrameCount () const = 0;

	/**	Gets the opacity at specified key frame for the animation. 
		@param whichKeyframe is the nth keyframe to get.
		@param keyframe is the keyframe at whichKeyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetOpacityKeyFrame (uint32 whichKeyframe, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the opacity at specified key frame for the animation. 
		@param whichKeyframe is the nth keyframe to get.
		@param keyframe is the keyframe at whichKeyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetOpacityKeyFrame (uint32 keyframe, PMReal& value) const = 0;
		
	/**	Sets the opacity at the specified key frame for the animation.
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe to set.
	*/	
	virtual bool SetOpacityKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified opacity key frame for whichAnimation.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemoveOpacityKeyFrame (uint32 keyframe) = 0;

	/**	Gets the rotation keyframe count for the animation. The keyframe count is
		the number of rotation keyframes that contain custom values.
		@return the total number of rotation keyframes.
	*/
	virtual uint32 GetRotationKeyFrameCount () const = 0;
	/**	Gets the rotation at specified key frame for the animation. 
		@param whichKeyframe is the nth keyframe to get.
		@param keyframe is the keyframe at whichKeyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetRotationKeyFrame (uint32 whichKeyframe, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the rotation at specified key frame for the animation. 
		@param keyframe is the keyframe to get.
		@param value is the value at keyframe.
	*/
	virtual bool GetRotationKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the rotation at the specified key frame for the animation.
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe to set.
	*/	
	virtual bool SetRotationKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified rotation key frame for the animation.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemoveRotationKeyFrame (uint32 keyframe) = 0;

	/**	Gets the total number of key frames for the animation.
		@return the total number of rotation keyframes.
	*/
	virtual uint32 GetScaleXKeyFrameCount () const = 0;
	/**	Gets the scale x keyframe count for the animation. The keyframe count is
		the number of scale x keyframes that contain custom values.
		@param whichKeyframe is the nth keyframe to get.
		@param keyframe is the keyframe at whichKeyframe.
		@param value is the value at keyframe.
	*/
	virtual bool GetScaleXKeyFrame (uint32 whichKeyframe, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the scale x at specified key frame for the animation. 
		@param keyframe is the keyframe to get.
		@param value is the value at keyframe.
	*/
	virtual bool GetScaleXKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the scale x at the specified key frame for the animation.
		@param whichAnimation is the animation to get.
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe to set.
	*/
	virtual bool SetScaleXKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified scale x key frame for the animation.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemoveScaleXKeyFrame (uint32 keyframe) = 0;

	/**	Gets the total number of key frames for the animation.
		@return the total number of rotation keyframes.
	*/
	virtual uint32 GetScaleYKeyFrameCount () const = 0;
	/**	Gets the scale y keyframe count for the animation. The keyframe count is
		the number of scale y keyframes that contain custom values.
		@param whichKeyframe is the nth keyframe to get.
		@param keyframe is the keyframe at whichKeyframe.
		@param value is the value at keyframe.
	*/	
	virtual bool GetScaleYKeyFrame (uint32 whichKeyframe, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the scale y at specified key frame for the animation. 
		@param keyframe is the keyframe to get.
		@param value is the value at keyframe.
	*/	
	virtual bool GetScaleYKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the scale y at the specified key frame for whichAnimation.
		@param whichAnimation is the animation to get.
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe to set.
	*/	
	virtual bool SetScaleYKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified scale y key frame for whichAnimation.
		@param whichAnimation is the animation to get.
		@param keyframe is the keyframe to remove.
	*/
	virtual bool RemoveScaleYKeyFrame (uint32 keyframe) = 0;

	/**	Copy from the specified animation data.
		@param iOther is new data to copy from.
	*/
	virtual void CopyAnimation (const IAnimationData* iOther) = 0;
	/**	Copy from the specified animation attribute data.
		@param iOtherAtr is new data to copy from.
	*/
	virtual void Copy (const IAnimationAttributeData* iOtherAtr) = 0;

	/**	Compare this with the specified animation attribute data.
		@param iOtherAtr is the other data to compare with.
		@return true if completely equals.
	*/
	virtual bool Equals (const IAnimationAttributeData* iOtherAtr) const = 0;

	/**	For internal use only.
	*/
	virtual void SetCustomData (const bool16 customData) = 0;
};

#endif	// __IAnimationAttributeData__
