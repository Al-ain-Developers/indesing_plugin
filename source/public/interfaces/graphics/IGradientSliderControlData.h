//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientSliderControlData.h $
//  
//  Owner: Thanh Nguyen
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
#ifndef __IGradientSliderControlData__
#define __IGradientSliderControlData__
 
#include "IPMUnknown.h"
#include "PMRect.h"
#include "IControlView.h"
#include "IRenderingObject.h"
#include "IColorData.h"
#include "K2Vector.h"	

class IRenderingObject;
class IControlView;
class PMRect;
class IColorData;
class IGradientFill;

const int32 kMaxGradientStopNum = 100;

/**	This interface manipulates the data and the controls on the gradient slider.
*/
class IGradientSliderControlData : public IPMUnknown
{
	public:
		typedef enum
		{
			/**	kMidPointThumb specifies a midpoint stop on the gradient slider.
			*/
			kMidPointThumb = 0,

			/**	kStopThumb specifies a color stop on the gradient slider.
			*/
			kStopThumb
		}thumbType;
		
		typedef enum
		{
			/**	kNormal specifies a normal update for the gradient stop.
			*/
			kNormal = 0,

			/** kSelectThumb indicates a gradient slider thumb is being selected.
			*/
			kSelectThumb,

			/**	kInsertThumbStop indicates a gradient color stop is being inserted.
			*/
			kInsertThumbStop,

			/**	kDragThumb indicates a gradient slider thumb is being dragged.
			*/
			kDragThumb,

			/**	kDeactivatePanel indicates the gradient slider is being deactivated.
			*/
			kDeactivatePanel,		// Don't use?

			/**	kActivatePanel indicates the gradient slider is being activated.
			*/
			kActivatePanel,			// Don't use?

			/**	kIndeterminate indicates the gradient slider is in an indeterminate state.
			*/
			kIndeterminate,

			/**	kNone indicates the [None] rendering object is being updated.
			*/
			kNone
		}updateType;
		
		/**	Broadcast a gradient data change message. The change is kRealChangeStateMessage
			and the protocol is IID_IGRADIENTSLIDERCONTROLDATA.
		*/
		virtual void		DoNotify() = 0;

		/**	Update the gradient slider data with the new gradient data.
			@param newGradientData is the new gradient data.
		*/
		virtual void UpdateSliderData (const IGradientFill* newGradientData) = 0;

		/**	Set the number of slider thumbs for the gradient slider.
			@param stopNum specifies the number of slider thumbs.
		*/
		virtual void SetNumberOfStop(int16 stopNum) = 0;

		/**	Sets the nth thumb stop at the new position. If nth stop already exists,
			replace it with the new position.
			@param index is nth thumb stop.
			@param thumbPosition is the new position for the thumb stop.
		*/
		virtual void SetNthThumbPosition(int16 index, PMReal thumbPosition) = 0;

		/**	Insert the new thumb location at the specified position.
			@param index is the new thumb stop.
			@param thumbPosition is the new position for the new stop.
		*/
		virtual void InsertThumb(int16 index, PMReal thumbPosition) = 0;

		/**	Set the current selected index to the specified index.
			@param thumbSelectedIndex is the new selected thumb index.
			@param updateBlockIndex is true if this is also the color stop index being updated.
		*/
		virtual void SetSelectedThumbIndex(int16 thumbSelectedIndex, bool16 updateBlockIndex = kTrue) = 0;
		
		/**	Set the target thumb index for the drag and drop.
			@param thumbIndex is the target index.
		*/
		virtual void SetDragDropHitThumbIndex(int16 thumbIndex) = 0;

		/**	Set the last event value. This is the slider position of the last mouse event.
			@param value is the last event value.
		*/
 		virtual void SetLastEventValue(PMReal value) = 0;

		/**	Set the last gradient slider update type.
			@param updateType specifies the update type. This should be one of
			IGradientSliderControlData::updateType.
		*/
		virtual void SetLastUpdateType(int16 updateType) = 0;

		/**	Set the last update boolean.
			@param update specifies the boolean value.
		*/
		virtual void SetLastUpdateBool(bool16 update) = 0;

		/**	Sets the last hit point on the gradient slider.
			@param hitPoint is the hit point.
		*/
 		virtual void SetLastHitPoint(PMPoint hitPoint) = 0;

		/**	Set the nth midpoint thumb stop's ratio.
			@param index is the nth midpoint.
			@param ratio is the midpoint ratio.
		*/
		virtual void SetNthMidPointRatio(int16 index, PMReal ratio) = 0;

		/**	Insert nth midpoint ratio.
			@param index is the nth midpoint.
			@param ratio is the midpoint ratio.
		*/
		virtual void InsertNthMidPointRatio(int16 index, PMReal ratio) = 0;

		/**	Set a boolean indicating that a slider thumb is being dragged.
			@param isDragging is true if a thum is being dragged.
		*/
		virtual void SetIsDragging(bool16 isDragging) = 0;

		/**	Set a boolean indicating the color data should be saved when color stop is removed.
		*/
		virtual void SetRemovedColorSave(bool16 bColorSave)=0;

		/**	Set a boolean indicating the gradient panel is being deactivated.
			@param panelDeactivate true if gradient panel is being deactivated.
		*/
		virtual void SetDeactivatePanel(bool16 panelDeactivate) = 0;

		/**	Set a boolean indicating the gradient slider control is a dailog control.
			@parm inDialog indicates gradient slider is used a dialog control.
		*/
		virtual void SetInGradientDialog(bool16 inDialog) = 0;

		// For pageItem rendering & graphic state interaction

		/**	
		*/
		virtual IRenderingObject* GetGradientRenderingObject() = 0;

		/**	Return the gradient slider gradient rendering object.
		*/
		virtual IRenderingObject* GetSliderRenderingObject() = 0;

		/**	Returns the list of slider thumb positions.
		*/
		virtual K2Vector<PMReal> GetThumbList() = 0;

		/**	Return total number of slider thumbs. This include midpoints and color stops.
		*/
		virtual int16 GetTotalThumbNum() = 0;

		/**	Return the number of slider color stops.
		*/
		virtual int16 GetNumberOfStop() = 0;

		/**	Return the position of the nth slider thumb.
			@param index specifies the nth thumb.
			@return the thumb position.
		*/
		virtual PMReal GetNthThumbPosition(int16 index) = 0;

		/**	Return the thumb type for the nth slider thumb.
			@param index specifies the nth slider thumb.
			@return the thumb type.
		*/
		virtual int16 GetNthThumbType(int16 index) = 0;

		/**	Return the color data of the nth color stop.
			@param index specifies the nth color stop.
			@return the color stop color data.
		*/
		virtual IColorData* QueryNthColorMetaData(int16 index) = 0;

		/**	Return the rectangle that is the gradient slider view area. This includes the
			area below and above the sliders where the color stops and midpoint thumbs are.
			@param sliderView the gradient slider control view.
			@return the gradient slider rectangle.
		*/
		virtual PMRect GetSliderRect(IControlView* sliderView) = 0;

		/**	Remove the slider thumb at the nth position.
			@param index specifies the nth slider thumb.
		*/
		virtual void RemoveThumbStop(int16 index) = 0;

		/**	Return the currently selected thumb index.
		*/
		virtual int16 GetSelectedThumbIndex() = 0;

		/**	Return the current active thumb index hit by drag and drop action.
		*/
		virtual int16 GetDragDropHitThumbIndex() = 0;

		/**	Return the thumb index hit by the specified point within a given tolerance.
			@param view is the gradient slider control view.
			@param hitPoint is the point.
			@param tolerance is the tolerance.
			@return the thumb index hit.
		*/
		virtual int16 GetHitThumb(IControlView* view, PMPoint hitPoint, int16 tolerance) = 0;

		/**	Returns the last event value. This is the slider position of the last mouse event.
		*/
		virtual PMReal GetLastEventValue() = 0;

		/**	Returns the last slider update type.
		*/
 		virtual int16 GetLastUpdateType() = 0;

		/**	Returns the last update boolean.
		*/
		virtual bool16 GetLastUpdateBool() = 0;

		/**	Returns the last update hit point.
		*/
		virtual PMPoint GetLastHitPoint() = 0;

		/**	Returns the list of midpoint ratios.
		*/
		virtual void GetMidPointRatio(K2Vector<PMReal>* thumbList) = 0;

		/**	Get the nth midpoint ratio.
			@param index specifies the nth midpoint.
			@return the midpoint ratio.
		*/
		virtual PMReal GetNthMidPointRatio(int16 index) = 0;

		/**	Return true if a slider thumb is being dragged.
		*/
		virtual bool16 IsDragging() = 0;

		/**	Relocate the Nth thumb to the new location. The midpoint is automatically re-adjusted.
			@param thumbIndex specifies the nth thumb.
			@param toPosition specifies the new position.
		*/
		virtual void RelocateNthThumb(int16 thumbIndex, PMReal toPosition) = 0;
		
		/**	Update the gradient slider
			@param upateType specifies the update type.
			This is one of IGreadientSliderControldata::UpdateType.
			@param hitIndex specifies the thumb index hit.
			@param hitPoint specifies the hit point.
			@param bUpdate is true if the slider data should be updated.
		*/
		virtual void UpdateSlider(int16 updateType, int16 hitIndex, PMPoint hitPoint, bool16 bUpdate = kTrue) = 0;
				
		/**	Given a new thumb position, determine where in the thumb list the new position will fit.
			The return index is the thumb position before the new thumb.
			@param thumbPosition is the new thumb position.
			@return the preceeding thumb index.
		*/
		virtual int16 GetPosibleThumbIndex(PMReal thumbPosition)   = 0;
		
		/**	Return the nth thumb index position relative to the gradient slider frame width.
			@param index specifies the nth thumb.
			@param frame is the gradient slider frame.
			@return the thumb position relative to the frame width.
		*/
		virtual PMReal MapThumbIndexToSliderPosition(int16 index,  PMRect& frame) = 0;

		/**	Return the corresponding thumb position, given a position in the
			coordinates of slider frame. The thumb position is normalized to values between
			0.0 and 1.0.
			@param sliderPosition is the position in the slider frame.
			@return the corresponding normalized thumb position.
		*/
		virtual PMReal MapSliderPositionToThumbPosition(PMReal sliderPosition) = 0;

		/**	Return the corresponding slider position relative to the slider frame, 
			given a point in the parent panel's coordiate.
			@param localPoint is the point in the parent's coordinates.
			@return the corresponding slider position.
		*/
		virtual PMReal MapLocalPointToSliderPosition(const PMPoint& localPoint) = 0;

		/**	Returns true if panel is being deactivated.
		*/
		virtual bool16 IsPanelDeactivate()=0;
		
		/**	Returns true if color data of the removed stop index should be saved..
		*/
		virtual bool16 IsRemovedColorSave()=0;

		/**	Returns true if the gradient slider is used in the dialog.
		*/
		virtual bool16 IsInDialog() = 0;
};

#endif // __IGradientSliderControlData__