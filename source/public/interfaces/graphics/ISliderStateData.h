//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISliderStateData.h $
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
#ifndef __ISliderStateData__
#define __ISliderStateData__

#include "widgetid.h"

/**	A helper interface on the slider widget to indicate the state of the slider widget.
*/
class ISliderStateData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ISLIDERSTATEDATA};

	/**	Type definition for the slider widget state.
	*/
	enum SliderStateType
		{
		/**	kSliderState_None indicates no state information.
		*/
		kSliderState_None 	= 0,
		/**	kSliderState_Indeterminant indicates the slider widget is in a mixed state.
		*/
		kSliderState_Indeterminant,
		/**kSliderState_Normal indicates a normal state.
		*/
		kSliderState_Normal,
		/**	kSliderState_Inactive indicate the slider widget is inactive.
		*/
		kSliderState_Inactive
		};

	/**	Sets the current state to a new state.
		@param value specificies the new state to set. value should be one of SliderStateType.
	*/
	virtual void					SetState	( const SliderStateType& value ) = 0;

	/**	Returns the current state.
		@return the current slider state.
	*/
	virtual const SliderStateType&	GetState	( void ) const = 0;

};

#endif	// __ISliderStateData__
