//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageTransition.h $
//  
//  Owner: DBerggren
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
#ifndef __IPageTransition_h__
#define __IPageTransition_h__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"

/**
	This interface is on every page transion object.
	@see kBlindsPageTransitionBoss
	@see kBoxPageTransitionBoss
	@see kCombPageTransitionBoss
	@see kCoverPageTransitionBoss
	@see kDissolvePageTransitionBoss
	@see kFadePageTransitionBoss
	@see kPageTurnPageTransitionBoss
	@see kPushPageTransitionBoss
	@see kSplitPageTransitionBoss
	@see kUncoverPageTransitionBoss
	@see kWipePageTransitionBoss
	@see kZoomInPageTransitionBoss
	@see kZoomOutPageTransitionBoss

	It is used to obtain page transition's properties such as name, duration and direciton.
*/
class IPageTransition : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGETRANSITION };

	/** 
	 Directions for page transitions. Some page transitions support a directional component. 

	 */
	enum PageTransitionDirection
	{
		kNA	= 0,			// Not Applicable

		kDown,				// Top to Bottom
		kLeft,				// Left to Right
		kLeftDown,			// Top Right to Bottom Left
		kLeftUp,			// Bottom Right to Top Left
		kRight,				// Right to Left
		kRightDown,			// Top Left to Bottom Right
		kRightUp,			// Bottom Left to Top Right
		kUp,				// Bottom to Top

		kIn,				// Inward
		kOut,				// Outward

		kHorizontal,		// Horizontal
		kVertical,			// Vertical

		kHorizontalIn,		// Horizontal Inward
		kHorizontalOut,		// Horizontal Outward
		kVerticalIn,		// Vertical Inward
		kVerticalOut,		// Vertical Outward
	};

	/** 
	 The default page transition duration time, in ticks (every second is 60 ticks)

	 */
	static const uint32 kPageTransitionsSlowSpeedTime = 60;		// 1 second * 60 = 60 ticks
	static const uint32 kPageTransitionsMediumSpeedTime = 40;		// 0.6666 second  * 60 = 40 ticks
	static const uint32 kPageTransitionsFastSpeedTime = 20;		// 0.3333 second * 60 = 20 ticks
	static const uint32 kDefaultDurationTime = kPageTransitionsMediumSpeedTime;	// Use the medium speed time

	/** 
	 Gets the name of the page transition. 
	
	 @param bTranslateName		If kTrue, the returned name will be translated
	 @return PMString			Containing the page transition name.
	 */
	virtual PMString GetName(bool bTranslateName = false) const = 0;

	/** 
	 Gets the default duration time of the page transition. 
	
	 @return uint32		The default duration of the page transition in ticks - 60 ticks per seconds.
	 */
	virtual uint32 GetDefaultDuration() const = 0;

	/** 
	 Gets the default direction for the page transition. 
	
	 @return uint32		The default direction of the page transition, as defined in the enum above.
	 */
	virtual uint32 GetDefaultDirection() const = 0;

	/** 
	 Gets the number directions the page transition supports. 
	
	 @return uint32		The number of directions the page transition supports.
	 */
	virtual uint32 GetNumberOfDirections() const = 0;

	/** 
	 Gets the nth direction the page transition supports. 
	
	 @return uint32		The nth direction of the page transition, as defined in the enum above.
	 */
	virtual uint32 GetNthDirection(uint32 index) const = 0;

	/** 
	 Gets an IDFile that is a SWF showing a proxy representation of the page transition. 
	
	 @return IDFile		A SWF proxy representation of the page transition.
	 */
	virtual IDFile GetSWFStaticRepresentation() const = 0;

	/** 
	 Gets an IDFile that is a SWF showing a proxy representation of the page transition based on the given direction and duration. 
	
	 @param direction [IN]: given direction for the page transition.
	 @param duration  [IN]: given duration for the page transtion (duration is represented as kPageTransitionsSlowSpeedTime, kPageTransitionsMediumSpeedTime, kPageTransitionsFastSpeedTime)
	 @param localFile [OUT]: the swf file based on the given direction and duration.
	 */
	virtual void GetSWFDynamicRepresentation(uint32 const &direction, uint32 const &duration, IDFile &localFile) const = 0;

};

//=============================================================================


#endif // __IPageTransition_h__

//  IPageTransition.h.
