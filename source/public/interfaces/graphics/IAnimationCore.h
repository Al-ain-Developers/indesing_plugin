//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAnimationCore.h $
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
#ifndef __IAnimationCore_h__
#define __IAnimationCore_h__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"
#include "IAnimationData.h"

/**	This interface is responsible for interacting with flash animation core component.
	@see also IAnimationAttributeData.h
*/
class IAnimationCore : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANIMATIONCORE };

	/**	Sets the XML description representing the animation preset.
	
		@param xmlIn is the xml description.
		@param ustTimescaleFromXml is true if using the animation time scale from the xml description.
	*/
    virtual bool SetXMLDescription (const WideString &xmlIn, bool useTimescaleFromXml = false) = 0;
	
	/**
	 A bitfield of options for driving GetMotionXML and GetXMLDescription.
	 */
	enum MotionXMLOptions
	{
		/**	kDefaultOptions is to include all data.
		*/
		kDefaultOptions = 0x00,
		
		/**	If set, all 3D parameters will be removed.
			If both kStrip3DParameters and kDisable3DParameters are set,
			all 3D parameters will be removed.
		*/
		kStrip3DParameters = 0x01,
		/**	If set, all filters will be removed.
			If both kStripFilters and kDisableFilters are set, all filters will be removed.
		*/
		kStripFilters = 0x02,

		/**	If set, all filters are disabled.
			For GetMotionXML, kDisableFilters is the same as kStripFilters.
		*/
		kDisableFilters = 0x04
	};

	/**	Gets the current XML description representing the animation preset.
	
		@param xmlOut is the xml string representing the current animation.
		@param options are the options to use when retrieving the preset xml description.
	*/
    virtual bool GetXMLDescription (WideString &xmlOut, uint32 options = kDefaultOptions) const = 0;
	
	/**
	 Gets the XML for SWF export. This data uses a custom XML schema to represent the 
	 animation data in a form that can be processed by InDesign's ActionScript code.
	
	 @param size is the buffer size containing the xml string.
	 @param options are the options to use while creating the motion XML data.
	 @return the xml.
	 @see MotionXMLOptions for a list of possible bitfield values to be used.
	*/
	virtual boost::shared_ptr<uint8> GetMotionXML(size_t &size, uint32 options = kDefaultOptions) const = 0;

	/**	Sets the duration for this animation.
		@param durationInSecond is the duration to set.
	*/
	virtual void SetDuration (const PMReal& durationInSecond) = 0;

	/**	@return the duration in second for this animation.
	*/
	virtual PMReal GetDuration () const = 0;

	/**	Sets the frame rate for this animation.
		@param framesPerSecond is the frame rate.
	*/
	virtual bool SetFrameRate (int32 frameRatePerSecond) = 0;

	/**	@return the frame rate in frames per second for this animation.
	*/
	virtual int32 GetFrameRate () const = 0;

	/** Returns the keyframe for the specified time in second.
		@param time is the time.
		@return the keyframe.
	*/
	virtual uint32 GetKeyframeForTime (const PMReal& time) const = 0;

	/**	Returns true if properties has ease applied.
		@return true if properties has ease applied.
	*/
	virtual bool PropertiesUsingFancyEase () const = 0;

	/**	Remove all ease types in the preset.
		@return true if successful; otherwise returns false.
	*/
	virtual bool RemoveAllEase () = 0;

	/**	Apply the specified ease type to all properties in the preset.
		If there's an ease that is different from the specified ease, the existing
		ease will be removed first for all properties.
		@param easeType is the ease to apply.
		@return true if successful; otherwise returns false.
	*/
	virtual bool ApplySimpleEaseToAll (const AnimationEaseType& easeType) = 0;
	
	/**	Sets the transform offset point. This is the offset percent from the left-top
		point of target object's bounding box.
		@param offsetPoint is the transform offset point.
	*/
	virtual void SetTransformOffsetPoint (const PMPoint& offsetPoint) = 0;

	/** @return the transform offset point.
	*/
	virtual PMPoint GetTransformOffsetPoint () const = 0;
	
	/** Sets the 2D keyframe path.
		@param path is the list of keyframe path point pairs.
	*/
	virtual bool Set2DPath (const AnimationPathDataList& path) = 0;
	
	/**	Gets the 2D path point list
		@param path is the list of path points.
		@param pHasRovingPathPoints if not nil returns true if at least one path point is set to roving.
		@return true if successful; otherwise false.
	*/
	virtual bool Get2DPath (PMPathPointList& path, bool* pHasRovingPathPoints = nil) const = 0;

	/**	Gets the 2D keyframe path.
		@param path is the list of keyframe path point pairs.
	*/
	virtual bool Get2DPath (AnimationPathDataList& path) const = 0;

	/**	Replaces the current motion path with the new path.
		This assumes the number of keyframes in the current path matches the number of points.
		@param path is the list of path point to set.
	*/
	virtual void SetNew2DBezierPath (const PMPathPointList &path) = 0;

	/**	Remove all path data.
	*/
	virtual void RemovePath () = 0;

	/**	Offsset motion path by the width and height of the current path so that
		the end of path is where the start of path is before the offset.
	*/
	virtual void OffsetPath () = 0;

	/**	Returns the path offset x and y such that the motion path is shifted by width and height of the
		current path and the new path ends where the current path should starts.
		@param offsetX is the x offset value.
		@param offsetY is the y offset value.
		@return true if successful.
	*/
	virtual bool GetPathOffset (double& offsetX, double& offsetY) const = 0;

	/**	Get the actual 2D motion path for all frames. This path takes into account offset, easing and time map.
		@param xValues is the resulting x values.
		@param yValues is the resutling y values.
	*/
	virtual void GetMotionPath (std::vector<double>& xValues, std::vector<double>& yValues) const = 0;

	/**	Methods for opacity property

	*/
	/**	Get the actual opacity values for all frames. The values returned take into account easing and time map.
		If opacity property does not exist, then resulting vector is emtpy.
		@param alphaValues is the resulting opacity values.
	*/
	virtual void GetOpacityValues (std::vector<double>& alphaValues) const = 0;

	/**	Returns the total number of keyframes with designated opacity values.
		@return total number of opacity keyFrames.
	*/
	virtual uint32 GetOpacityKeyFrameCount () const = 0;

	/**	Returns nth opacity keyframe value.
		@param which the nth keyframe to get.
		@param keyframe the keyframe at which position.
		@param value is the value at keyframe.
	*/
	virtual bool GetOpacityKeyFrame (uint32 which, uint32& keyframe, PMReal& value) const = 0;

	/**	Gets the opacity values at a specified keyframe. 
		If the value does not exist at this keyframe, an interpolated value is returned.
		@param keyframe to get
		@param value is the opacity value at specified keyframe.
	*/
	virtual bool GetOpacityValueAtKeyFrame (uint32 keyframe, PMReal& value) const = 0;

	/**	Removes the designated opacity value at the specified keyframe.
		@keyframe is the keyframe to remove.
	*/
	virtual bool RemoveOpacityValueAtKeyFrame (uint32 keyframe) = 0;

	/**	Removes all opacity keyframes and reset to default condition.
	*/
	virtual void RemoveAllOpacityKeyFrames () = 0;

	/**	Sets a specific opacity value at the specified keyframe.
		@param keyframe to set
		@param value is the opacity value to set.		
	*/
	virtual bool SetOpacityValueAtKeyFrame (uint32 keyframe, const PMReal& value) = 0;

	/**	Methods for Rotation property
	*/

	/**	Get the actual rotation values for all frames. The values returned take into account easing and time map.
		If rotation property does not exist, then resulting vector is emtpy.
		@param rValues is the resulting rotation values.
		If the resulting vector is empty, then there's no rotation component in the animation.
		If the vector has one single entry, then the rotation is constant over the entire duration with this value.
	*/
	virtual void GetRotationValues (std::vector<double>& rValues) const = 0;

	/**	Returns the total number of keyframes with designated rotation values.
		@return total number of rotation keyFrames.
	*/
	virtual uint32 GetRotationKeyFrameCount () const = 0;

	/**	Returns nth rotation keyframe value.
		@param which the nth keyframe to get.
		@param keyframe the keyframe at which position.
		@param value is the value at keyframe.
	*/
	virtual bool GetRotationKeyFrame (uint32 which, uint32& keyframe, PMReal& value) const = 0;
	
	/**	Gets the rotation values at a specified keyframe. 
		If the value does not exist at this keyframe, an interpolated value is returned.
		@param keyframe to get
		@param value is the rotation value at specified keyframe.
	*/
	virtual bool GetRotationValueAtKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Removes the designated rotation value at the specified keyframe.
		@keyframe is the keyframe to remove.
	*/
	virtual bool RemoveRotationValueAtKeyFrame (uint32 keyframe) = 0;

	/**	Removes all rotation keyframes and reset to default condition.
	*/
	virtual void RemoveAllRotationKeyFrames () = 0;

	/**	Sets a specific rotation value at the specified keyframe.
		@param keyframe to set
		@param value is the rotation value to set.		
	*/
	virtual bool SetRotationValueAtKeyFrame (uint32 keyframe, const PMReal& value) = 0;

	/**	Methods for Scale X and Scale Y property
	*/

	/**	Get the actual x an y scale percentage values all frames. The values returned take into account easing and time map.
		If x or y scale property does not exist, then the resulting vector will be empty.
		@param xValues is the resulting scale x values.
		@param yValues is the resutling scale y values.
		If the resulting vector is empty, then there's no scale x or y component in the animation.
		If the vector has one single entry, then the scale is constant over the entire duration with this value.
	*/
	virtual void GetScaleValues (std::vector<double>& xValues, std::vector<double>& yValues) const = 0;

	/**	Returns the total number of keyframes with designated scale x values.
		@return total number of scale x keyFrames.
	*/
	virtual uint32 GetScaleXKeyFrameCount () const = 0;

	/**	Returns nth scale x keyframe value.
		@param which the nth keyframe to get.
		@param keyframe the keyframe at which position.
		@param value is the value at keyframe.
	*/
	virtual bool GetScaleXKeyFrame (uint32 which, uint32& keyframe, PMReal& value) const = 0;

	/**	Gets the scale x values at a specified keyframe. 
		If the value does not exist at this keyframe, an interpolated value is returned.
		@param keyframe to get
		@param value is the scale x value at specified keyframe.
	*/
	virtual bool GetScaleXValueAtKeyFrame (uint32 keyframe, PMReal& value) const = 0;

	/**	Removes the designated scale x value at the specified keyframe.
		@keyframe is the keyframe to remove.
	*/
	virtual bool RemoveScaleXValueAtKeyFrame (uint32 keyframe) = 0;

	/**	Removes all scale x keyframes and reset to default condition.
	*/
	virtual void RemoveAllScaleXKeyFrames () = 0;

	/**	Sets a specific scale x value at the specified keyframe.
		@param keyframe to set
		@param value is the scale x value to set.		
	*/
	virtual bool SetScaleXValueAtKeyFrame (uint32 keyframe, const PMReal& value) = 0;

	/**	Returns the total number of keyframes with designated scale y values.
		@return total number of scale y keyFrames.
	*/
	virtual uint32 GetScaleYKeyFrameCount () const = 0;

	/**	Returns nth scale y keyframe value.
		@param which the nth keyframe to get.
		@param keyframe the keyframe at which position.
		@param value is the value at keyframe.
	*/
	virtual bool GetScaleYKeyFrame (uint32 which, uint32& keyframe, PMReal& value) const = 0;

	/**	Gets the scale y values at a specified keyframe. 
		If the value does not exist at this keyframe, an interpolated value is returned.
		@param keyframe to get
		@param value is the scale y value at specified keyframe.
	*/
	virtual bool GetScaleYValueAtKeyFrame (uint32 keyframe, PMReal& value) const = 0;
	/**	Removes the designated scale y value at the specified keyframe.
		@keyframe is the keyframe to remove.
	*/
	virtual bool RemoveScaleYValueAtKeyFrame (uint32 keyframe) = 0;

	/**	Removes all scale y keyframes and reset to default condition.
	*/
	virtual void RemoveAllScaleYKeyFrames () = 0;

	/**	Sets a specific scale y value at the specified keyframe.
		@param keyframe to set
		@param value is the scale y value to set.		
	*/
	virtual bool SetScaleYValueAtKeyFrame (uint32 keyframe, const PMReal& value) = 0;

	/**	Reverse all properties.
	*/
	virtual void ReverseAllProperties () = 0;

	/**	Internal use only
	*/
	virtual void Initialize () = 0;
};


#endif