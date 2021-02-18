//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationData.h $
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
#ifndef __IAnimationData__
#define __IAnimationData__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"
#include "PMPathPoint.h"
#include "AnimationTypes.h"

#include <map>

class IPathGeometry;
class PMMatrix;
class PMRect;
class PMPathPoint;


/** This is a transient data interface for one animation data.
	It is used to represent the memoery-based animation data, e.g.
	animation script data object. It is also used as command
	data interface to update page item animation data.
	It does not provide direct access to the page item's persistent animation data.

	@see also IAnimationAttributeData.h
*/
class IAnimationData : public IPMUnknown
{
public:

	enum {kDefaultIID = IID_IANIMATIONDATA};

	/**	@return the animation preset UID.
	*/
	virtual UID GetPresetUID () const = 0;

	/**	Sets the animation preset UID.
		@param presetUID is the motion preset UID to set.
		@return true if successful.
	*/
	virtual bool SetPresetUID (UID presetUID) = 0;

	/**	@return the number ot times the animation plays.
	*/
	virtual uint32 GetNumPlays () const = 0;

	/**	Sets the number of time the animation plays.
		@param numPlays is the number ot times the animation plays.
		numPlays must be at least 1.
	*/
	virtual bool SetNumPlays (uint32 numPlays) = 0;

	/**	@return true if animation is set to loop
	*/
	virtual bool GetPlaysLoop () const = 0;

	/**	Sets animation to plays loop.
		@param setToLoop is true if to set animation to loop.
		@return true if successful.
	*/
	virtual bool SetPlaysLoop (bool setToLoop) = 0;

	/**	@return true if object is hidden until animated.
	*/
	virtual bool GetHideInitially () const = 0;

	/**	Sets object run-time visibility to be hidden until animated.
		@param setHidden is true if to set object to be hidden till animated.
		@return true if successful.
	*/
	virtual bool SetHideInitially (bool setHideInitially) = 0;

	/**	@return true if object is hidden after animated.
	*/
	virtual bool GetHideAfter() const = 0;

	/**	Sets object run-time visibility to hide after animated.
		@param setHideAfter is true if to set object to be hidden after animated.
		@return true if successful.
	*/
	virtual bool SetHideAfter (bool setHideAfter) = 0;

	/**	@return the animate option.
	*/
	virtual AnimationOptions GetAnimateOption () const = 0;
	
	/**	Sets the animate option.
		@param animateOption is the animate option to set.
		@return true if successful.
	*/
	virtual bool SetAnimateOption (const AnimationOptions& animateOption) = 0;

	/**	Sets the duration.
		@param durationInSecond is the duration.
		@return true if successful.
	*/
	virtual bool SetDuration (const PMReal& durationInSecond) = 0;

	/**	Gets the duration for whichAnimation.
	*/
	virtual PMReal GetDuration () const = 0;

	/**	Sets the frame rate.
		@param frameRatePerSecond is number of frames per second.
	*/
	virtual bool SetFrameRate (int32 frameRatePerSecond) = 0;
	
	/**	@return the frame rate
	*/
	virtual int32 GetFrameRate () const = 0;

	/**	@return the simple ease strength.
	*/
	virtual AnimationEaseType GetSimpleEaseType () const = 0;
	
	/**	Sets the simple ease type.
		@param easeType is ease type to set.
	*/
	virtual bool SetSimpleEaseType (const AnimationEaseType& easeType) = 0;

	/**	Sets the transform point. The transform point specified the offset percentage (0.0 to 1.0)
		relative to the target object the animation path motion starts.
		@param offsetPoint is the offset percent point to set.
		@return true if successful.
	*/
	virtual bool SetTransformOffsetPoint (const PMPoint& offsetPoint) = 0;
	
	/**	@return the transform offset point.
	*/
	virtual PMPoint GetTransformOffsetPoint () const = 0;
	
	/**	Gets the 2D motion path and keyframes.
		@param pathFrames is the keyframe path to get.
		@return true if successful.
	*/
	virtual bool Get2DKeyFramePath (AnimationPathDataList& pathFrames) const = 0;

	/**	Gets the 2D motion path.
		@param path is the path to get.
		@param isRoving is true if path is roving path.
		@return true if successful.
	*/
	virtual bool Get2DPathPoints (PMPathPointList& path, bool& isRoving) const = 0;
	
	/**	Sets the 2D motion path and keyframes.
		@param pathFrames is the keyframe path to get.
		@return true if successful.
	*/
	virtual bool Set2DKeyFramePath (const AnimationPathDataList& path) = 0;
	
	/**	Sets the 2D motion path. This path replaces the
		existing path at the already specified keyframes.
		@param path is the path to set.
		@param isRoving is true if the path to set is roving path.
		@return true if successful.
	*/
	virtual bool Set2DPathPoints (const PMPathPointList& path, bool isRoving) = 0;

	/**	Gets the total number of key frames.
	*/
	virtual uint32 GetOpacityKeyFrameCount () const = 0;

	/*	Gets the nth keyframe and opacity value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetOpacityKeyFrame (uint32 nth, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the opacity at specified key frame. 
		@param keyframe is the keyframe to get.
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetOpacityKeyFrame (uint32 keyframe, PMReal& value) const = 0;
		
	/**	Sets the opacity at specified key frame. 
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool SetOpacityKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/*	Removes the specified opacity key frame
		@param keyframe is the keyframe to remove.
		@return true if successful.
	*/
	virtual bool RemoveOpacityKeyFrame (uint32 keyframe) = 0;

	/**	Gets the total number of key frames.
	*/
	virtual uint32 GetRotationKeyFrameCount () const = 0;
	/*	Gets the nth keyframe and rotation value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetRotationKeyFrame (uint32 nth, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the rotation at specified key frame. 
		@param keyframe is the keyframe to get.
		@param value is the value at keyframe.
	*/
	virtual bool GetRotationKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the rotation at specified key frame. 
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool SetRotationKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified rotation key frame
		@param keyframe is the keyframe to remove.
		@return true if successful.
	*/
	virtual bool RemoveRotationKeyFrame (uint32 keyframe) = 0;

	/**	Gets the total number of key frames.
	*/
	virtual uint32 GetScaleXKeyFrameCount () const = 0;
	/*	Gets the nth keyframe and scale x value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetScaleXKeyFrame (uint32 nth, uint32& keyframe, PMReal& value) const = 0;
	/*	Gets the nth keyframe and scale x value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetScaleXKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the scale x at specified key frame. 
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool SetScaleXKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified scale x key frame
		@param keyframe is the keyframe to remove.
		@return true if successful.
	*/
	virtual bool RemoveScaleXKeyFrame (uint32 keyframe) = 0;

	/**	Gets the total number of key frames.
	*/
	virtual uint32 GetScaleYKeyFrameCount () const = 0;
	/**	Gets the nth keyframe and scale y value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetScaleYKeyFrame (uint32 nth, uint32& keyframe, PMReal& value) const = 0;
	/**	Gets the nth keyframe and scale y value.
		@param nth is the nth keyframe value pair to get.
		@param keyframe is the keyframe
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool GetScaleYKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Sets the scale y at specified key frame. 
		@param keyframe is the keyframe to set.
		@param value is the value at keyframe.
		@return true if successful.
	*/
	virtual bool SetScaleYKeyFrame (uint32 keyframe, const PMReal& value) = 0;
	/**	Removes the specified scale y key frame
		@param keyframe is the keyframe to remove.
		@return true if successful.
	*/
	virtual bool RemoveScaleYKeyFrame (uint32 keyframe) = 0;

	/**	Copy from another animation data.
		@param iOtherData is the animation data to copy from.
	*/
	virtual void Copy (const IAnimationData* iOtherData) = 0;
	/**	Compare with another animation data.
		@param iOtherData is the animation data to compare with.
		@return true if completely equals
	*/
	virtual bool Equals (const IAnimationData* iOtherData) const = 0;
};

#endif	// __IAnimationData__
