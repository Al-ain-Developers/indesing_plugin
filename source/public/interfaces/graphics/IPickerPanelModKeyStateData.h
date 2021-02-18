//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPickerPanelModKeyStateData.h $
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
//  DESC:
//  Keep track of some KBSC key state and states of stroke or fill color data for
//  Color Picker Panel. This is mainly used for processing user action with modifier
//  keys in the Color Picker panel such as shift-click.
//  
//========================================================================================

#pragma once
#ifndef _IPickerPanelModKeyStateData_
#define _IPickerPanelModKeyStateData_
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
#include "ColorPickerID.h"
#include "IColorData.h"

//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________
/**	This is a helper interface which keeps track of some KBSC key state and states of stroke or fill 
	color data for Color Panel. This is mainly used for processing user action with modifier keys
	in the Color Panel such as switching color space using shift-click.
*/
class IPickerPanelModKeyStateData : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICOLORPICKERPANELMODKEYSTATEDATA };

		//___________________________________________________________________________
		//	Set
		//___________________________________________________________________________
			enum 
				{
				/**	Indicates alt-option key has been prressed.
				*/
				kPickerPanel_AltOptKeyPressed = 0x04,
				/**	Indicates cmd key has been prressed.
				*/
				kPickerPanel_CmdKeyPressed = 0x02,
				/**	Indicates shift key has been prressed.
				*/
				kPickerPanel_ShiftKeyPressed = 0x01
				};
				
			/**	Sets the current key state. Key states is one of kPickerPanel_AltOptKeyPressed,
				kPickerPanel_CmdKeyPressed, or kPickerPanel_ShiftKeyPressed.
				@param keyState the current key state.
			*/
			virtual void			SetKeyState 		(int32 keyState) = 0;
			/**	Sets the current stroke color UID. 
				@param strokeColorUID the stroke color UID.
			*/
			virtual void			SetStrokeUID		(UID strokeColorUID) = 0;
			/**	Sets the current stroke tint percent. 
				@param strokeTint the stroke tint percent.
			*/
			virtual void			SetStrokeTint		(PMReal strokeTint) = 0;
			/**	Sets to true to indicate that current stroke color is a global swatch.
				@param isGlobal is set to true to indicate that the current stroke color is a global color swtach.
			*/
			virtual void			SetStrokeIsGlobal	(bool16 isGlobal) = 0;
			/**	Sets the current fill color UID. 
				@param fillColorUID the fill color UID.
			*/
			virtual void			SetFillUID			(UID fillColorUID) = 0;
			/**	Sets the current fill tint percent. 
				@param fillTint the fill tint percent.
			*/
			virtual void			SetFillTint			(PMReal fillTint) = 0;
			/**	Sets to true to indicate that current fill color is a global swatch.
				@param isGlobal is set to true to indicate that the current fill color is a global color swtach.
			*/
			virtual void			SetFillIsGlobal		(bool16) = 0;
			
			/**	Update the current stroke color.
				@param colorspace is the color space to update to.
				@param colorValue is the color values corresponding to the color space.
				@param tint is the tint percent to apply to.
			*/
			virtual void			UpdateStrokeColorspaceColorData (int32 colorspace, const ColorArray& colorValues, const PMReal& tint) = 0;
			/**	Update the current fill color.
				@param colorspace is the color space to update to.
				@param colorValue is the color values corresponding to the color space.
				@param tint is the tint percent to apply to.
			*/
			virtual void			UpdateFillColorspaceColorData (int32 colorspace, const ColorArray& colorValues, const PMReal& tint) = 0;
			
			/**	Reset the cached color values for stroke and fill color.
			*/
			virtual void			ResetCachedColorValues () = 0;
		//___________________________________________________________________________
		//	Acessor
		//___________________________________________________________________________
			/**	Returns the current key state.
				@return the current key state.
			*/
			virtual int32			GetKeyState 		(void) const = 0;
			/**	Returns the current stroke color UID.
				@return the stroke color UID.
			*/
			virtual UID				GetStrokeUID		(void) const = 0;
			/**	Returns the current stroke tint percent.
				@return the stroke tint percent.
			*/
			virtual PMReal			GetStrokeTint		(void) const = 0;
			/**	Returns true if current stroke color UID is a global color swatch.
				@return true if stroke is a global swatch.
			*/
			virtual bool16			StrokeIsGlobal		(void) const = 0;
			/**	Returns the current fill color UID.
				@return the fill color UID.
			*/
			virtual UID				GetFillUID			(void) const = 0;
			/**	Returns the current fill color UID.
				@return the fille color UID.
			*/
			virtual PMReal			GetFillTint			(void) const = 0;
			/**	Returns true if current fill color UID is a global color swatch.
				@return true if fill is a global swatch.
			*/
			virtual bool16			FillIsGlobal		(void) const = 0;
			/**	Returns the cached stroke color value corresponding the specified color space.
				@param colorspace is the color space for the stroke color value being returned.
				@return the stroke color value.
			*/
			virtual ColorArray		GetStrokeColorspaceColorData (int32 colorspace) = 0;
			/**	Returns the cached fill color value corresponding the specified color space.
				@param colorspace is the color space for the fill color value being returned.
				@return the fill color value.
			*/
			virtual ColorArray		GetFillColorspaceColorData (int32 colorspace) = 0;
	};
		
#endif // _IPickerPanelModKeyStateData_
