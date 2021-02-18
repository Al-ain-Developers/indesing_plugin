//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorPickerPanelHelper.h $
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
//  Helper interface to access the ColorPicker panels.
//  
//========================================================================================

#pragma once
#ifndef __IColorPickerPanelHelper__
#define __IColorPickerPanelHelper__

#include "ColorPickerID.h"
#include "IColorData.h"
#include "ISliderStateData.h"

class	ISubject;
class	IControlView;

/**	An interface that helps to manage the color picker panels. A color picker typically will
	have a stack of color space panels and other related panels.
*/
class IColorPickerPanelHelper : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPICKERPANELHELPER };
	
	// ----- Query -----
	
	/**	Returns a panel index from the specified color space.
		@param colorspace specifies the color space of the picker panel. 
		@return the panel index.
	*/
	virtual int32			GetPickerIndexFromColorSpace(const int32 colorspace) const = 0;
	/**	Returns the clor space of the panel from the specified panel index
		@param pickerIndex specifies the panel index
		@return the panel's color space.
	*/
	virtual int32			GetColorSpaceFromPickerIndex(const int32 pickerIndex) const = 0;

	/**	Return the panel's IColorData interface pointer.
		@return panel's IColorData interface pointer. 
	*/
	virtual IColorData*		QueryPickerMetaData() = 0;

	/**	Return the panel's ISubject interface pointer.
		@return panel's ISubject interface pointer. 
	*/
	virtual ISubject*		QueryPickerPanelSubject() = 0;
	
	/**	Return the control state for the specified panel index.
		@see also ISliderStateData.h for definition of SliderStateType
		@param pickerIndex specifies the panel index
		@return panel's slider state. 
	*/
	virtual ISliderStateData::SliderStateType		GetPickerControlState( const int32 pickerIndex ) const = 0;
	
	/**	Return the control state for the currently visible picker panel.
		@see also ISliderStateData.h for definition of SliderStateType
		@return visible panel's slider state. 
	*/
	virtual ISliderStateData::SliderStateType		GetPickerControlState() const = 0;
	
	/**	Return the specified picker panel's IColorData interface pointer.
		@param colorspace specifies the color space of picker panel
		@return panel's IColorData interface pointer. 
	*/
	virtual IColorData*		QueryColorspaceColorData (const int32 colorspace) = 0;

	/**	Return the ink UID list of the  NChannel picker panel.
		@return panel's ink UID list. A nil pointer is returned if there isn't a NChannel picker panel.
	*/
	virtual	const UIDList*	GetPickerNChannelInkList () = 0;
	
	/**	Sets color values for the specified panel index.
		@param pickerIndex specifies the panel index
		@param components specifies the color values to set
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerMetaData(const int32 pickerIndex, ColorArray& components, bool16 doNotify = kFalse) = 0;

	/**	Sets the new color data for the color picker panel.
		@param iColorData specifies the new color data to set.
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerMetaData(IColorData* iColorData, bool16 doNotify = kFalse) = 0;

	/**	Sets the new color data for the color picker panel.
		@param colorRef specifies the new color data to set.
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerMetaData(const UIDRef& colorRef, bool16 doNotify = kFalse) = 0;

	/**	Sets the new NChannel color data for the color picker panel.
		@param components specifies the new color values to set.
		@param inkUIDList specifies the corresponding ink UID list set.
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerMetaData(const ColorArray& components, const UIDList& inkUIDList, bool16 doNotify = kFalse) = 0;
	
	/**	Sets the new control statefor the picker panel.
		@see also ISliderStateData.h for definition of SliderStateType
		@param pickerIndex specifies the index of the picker panel.
		@param controlState specifies the control state of the picker panel.
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerControlStates(const int32 pickerIndex, const ISliderStateData::SliderStateType controlState, bool16 doNotify = kFalse) = 0;

	/**	Sets the new control statefor the picker panel.
		@see also ISliderStateData.h for definition of SliderStateType
		@param controlState specifies the control state of the picker panel to set.
		@param doNotify will broadcast control change messages if true.
		The default value for doNotify is kFalse.
	*/
	virtual void			SetPickerControlStates(const ISliderStateData::SliderStateType controlState, bool16 doNotify = kFalse) = 0;

	// ----- Miscellaneous ----
	
	/**	Enable the specified picker panel.
		@param pickerIndex specifies picker panel to enable. If index if -1, all panels are enabled.
	*/
	virtual void			EnablePanel( const int32 pickerIndex = -1 ) =0;
	/**	Disable the specified picker panel.
		@param pickerIndex specifies picker panel to disable. If index if -1, all panels are disabled.
	*/
	virtual void			DisablePanel( const int32 pickerIndex = -1 ) =0;

	/**	Update color picker panel's color data based on the currently visible panel.
	*/
	virtual void			UpdatePickerMetaData() = 0;

	/**	Switch color picker's visible view to the picker panel specified by the panel index.
		@param pickerIndex specifies the panel index.
	*/
	virtual void			SwitchPickerPanelByIndex( const int32 pickerIndex ) = 0;

	/**	Switch color picker's visible view to the picker panel specified by he panel's color space.
		@param newColorspace specifies the color space panel to switch to.
	*/
	virtual void			SwitchPickerPanelByColorspace( const int32 newColorspace ) = 0;
	
	/**	Returns panel color change broadcast protocal.
	*/
	virtual PMIID			GetObservedProtocol (void) = 0;

	/**	Force a boadcast of color change
		@param iPickerView specifies the subject view to broadcast on. If nil, broadcast on the
		currently visible picker view's subject.
	*/
	virtual void			BroadcastChange (IControlView* iPickerView = nil) = 0;
	
};

#endif
