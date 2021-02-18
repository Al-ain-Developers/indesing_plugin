//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnimationTypes.h $
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
//  
//  A Generic class that describes a line point or a Bezier knot
//  
//========================================================================================

#pragma once
#ifndef __AnimationTypes__
#define __AnimationTypes__

#include "PMPathPoint.h"
#include <map>

/**	Type definition of the animation motion path. This defines a map of keyframes and Bezier path points.
*/
typedef std::map<uint32, PMPathPoint> AnimationPathDataList;

/** This enum defines the Animation event trigger types.
	An animation can be triggered by one or more of these events.
*/
enum EventTriggerType {

	/** Invalid trigger event type. */
	kNoTriggerEvent =	0,
	/** Specifies that the animaiton is triggered by a page load. */
	kOnPageLoad,
	/** Specifies that the animaiton is triggered by a page click. */
	kOnPageClick,
	
	/** Specifies that the animaiton is triggered by self click. */
	kOnSelfClick,
	/** Specifies that the animaiton is triggered by self rolloever. */
	kOnSelfRollover,

	/** Specifies that the animaiton is triggered by an object click.
		This is mapped to button event, kMouseDownEvt
	*/
	kOnClick,
	/** Specifies that the animaiton is triggered by an object moust down.
		This is mapped to button event, kMouseUpEvt
	*/
	kOnRelease,
	/** Specifies that the animaiton is triggered by an object rollover. 
		This is mapped to button event, kMouseEnterEvt
	*/
	kOnRollover,
	/** Specifies that the animaiton is triggered by an object rolloff.
		This is mapped to button event, kMouseExitEvt
	*/
	kOnRolloff

};

/**	Easing is a technique that Flash uses to calculate the property values between property keyframes.
	When no easing is specified, the change to the property value is the same in each frame. 
	With easing, the rate of change to the values is adjusted.
	This defines the simple predefined ease types. 
	@see also IAnimationAttributeData.h
*/
enum AnimationEaseType {

	/**	Specifies no easing.
	*/
	kNoEase = 0,
	/**	Specifies a simple ease in.
	*/
	kEaseIn,
	/**	Specifies a simple ease out.
	*/
	kEaseOut,
	/**	Specifies a simple ease in and then ease out.
	*/
	kEaseInAndOut,
	/**	Specifies a custom or complex ease.
		This is used to indicate that a preset already has a custom ease type that 
		InDesign will honor.
		This is readonly type and will not be allowed to use to set as an ease type.
	*/
	kEaseCustomReadOnly

};

/**	Animation options provide a non-destructive way to change the way an object's
	animation will be played. The default is to play the animation from the position
	the object is designed on the page.
*/
enum AnimationOptions
{
	/**	Specifies that the animation is played from the position as designed on the page.
	*/
	kAnimateFrom = 0,
	/**	Specifies that the animation is played in reverse from the last frame.
		When the animatoin ends, the object should be in the position as designed on the page.
	*/
	kAnimateTo,
	/**	Specifies that the animation is played offset by the width and height of the entire path
		so that when the animation ends, the object should be in the position as designed on the page.
	*/
	kAnimateOffset
};

#endif
