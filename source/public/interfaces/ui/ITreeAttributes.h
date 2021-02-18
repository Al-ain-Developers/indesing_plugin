//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeAttributes.h $
//  
//  Owner: Dave Burnard (was Matt Joss)
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
#ifndef __ITreeAttributes__
#define __ITreeAttributes__

#include "widgetid.h"
#include "IPMUnknown.h"

class ITreeNode;

//========================================================================================
// CLASS ITreeAttributes
/** Interface for maintaining Tree display attributes, part of kTreeViewWidgetBoss
*/
//========================================================================================
class ITreeAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEATTRIBUTES };

	
	// -----------------------------------------------------------
	/**@name Root Node Display */
	//@{
	/** Should the root node be displayed in the tree?
	*/
	virtual	bool16						IsRootNodeDisplayed() const = 0;
	/** Sets display of the root node
		@param displayRoot kTrue to display root node, kFalse to not display root node
	*/
	virtual	void						DisplayRootNode(bool16 displayRoot) = 0;
	//@}

	// -----------------------------------------------------------
	/**@name Scroll Bar */
	//@{

	typedef enum { kVerticalScrollBar, kHorizontalScrollBar} ScrollBarType;

	/** Determine if the specified scroll bar is to be used
		@param scrollType specifies which scroll bar we are targetting, kVerticalScrollBar or kHorizontalScrollBar
	*/
	virtual	bool16						IsScrollBarUsed( ScrollBarType scrollType ) const = 0;	

	/** Sets whether we want to use the specified scroll bar
		@param scrollType specifies which scroll bar we are targetting, kVerticalScrollBar or kHorizontalScrollBar
	*/
	virtual	void						UseScrollBar( ScrollBarType scrollType, bool16 useScrollBar ) = 0;

	/** The scroll button increment is the number of pixels that will scroll when you click on either of the scroll buttons.
	The thumb scroll increment is the smallest number of pixels that will scroll when you use the scroll bar thumb.  For
	instance, you can have the scroll button move 20 pixels, but have the thumb scroll 1 pixel for greater accuracy.  The
	thumb scroll increment must be a factor of the scroll button increment.	

		Gets the setting for Thumb Scroll Increment
		@param scrollType specifies which scroll bar we are targetting, kVerticalScrollBar or kHorizontalScrollBar
	*/
	virtual	int16						GetThumbScrollIncrement(  ScrollBarType scrollType ) const = 0;
	/** Gets the setting for Button Increment
		@param scrollType specifies which scroll bar we are targetting, kVerticalScrollBar or kHorizontalScrollBar
	*/
	virtual	int16						GetScrollButtonIncrement(  ScrollBarType scrollType ) const = 0;

	/** Change the values for the scroll thumb and scroll button
	 This will cause a call to ChangeRoot() on the ITreeViewMgr
		@param scrollType specifies which scroll bar we are targetting, kVerticalScrollBar or kHorizontalScrollBar
		@param scrollButtonIncrement specifies the button increment for the scroll bar
		@param thumbScrollIncrement specifies the thumb scroll increment
	*/
	virtual	void						SetScrollAmount( ScrollBarType scrollType, int16 scrollButtonIncrement, int16 thumbScrollIncrement ) = 0;
	//@}


	// -----------------------------------------------------------
	/**@name Attributes */
	//@{

	/** Set whether or not the tree draws a black line after the last element.  See list panels like Layers
	 
		@param willDrawEndLine boolean value specifing if the line is to be drawn(true) for not(false)
	*/
	virtual	void						SetDrawEndLine( const bool16 willDrawEndLine ) = 0;

	/** returns whether or not the tree draws a black line after the last element.  See list panels like Layers
	*/
	virtual	bool16						DrawsEndLine(  ) const = 0;

	/** Set whether or not the tree draws a black line border around itself

		@param willDrawBorder boolean value specifing if the border is to be drawn(true) for not(false)
	 */
	virtual	void						SetDrawBorder( const bool16 willDrawBorder ) = 0;
	
	/** returns whether or not the tree draws a black line border around itself
	 */
	virtual	bool16						DrawsBorder(  ) const = 0;
	//@}
};


#endif
