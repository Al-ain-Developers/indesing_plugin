//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStrokeFillControlData.h $
//  
//  Owner: Michael_Martz
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
	#ifndef _IStrokeFillControlData_
	#define _IStrokeFillControlData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ToolboxProxyTypes.h"
	#include "ColorSystemID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

	/**	A widget data interface for the stroke/fill proxy widget.
		For rendering the stroke/fill proxy, two strategies are used: UID and metadata.
		The metadata object here could be any object that the client use for rendering the
		stroke/fill proxy view.
	*/
	class IStrokeFillControlData : public IPMUnknown
		{				
		//________________________________________________________________________________
		//	Widget Layout
		//________________________________________________________________________________
		public:
			enum { kDefaultIID = IID_ISTROKEFILLCONTROLDATA };

			/**	Returns the stroke/fill proxy widget's width.
			*/
			virtual int16		GetStrokeFillWidth		(void) = 0;
			/**	Sets the stroke/fill proxy widget's width.
				@param width the stroke/fill proxy widget's width.
			*/
			virtual void		SetStrokeFillWidth		(int16 width) = 0;

			/**	Returns the stroke/fill proxy widget's height.
			*/
			virtual int16		GetStrokeFillHeight		(void) = 0;
			/**	Sets the stroke/fill widget's proxy height.
				@param height the stroke/fill proxy widget's height.
			*/
			virtual void		SetStrokeFillHeight		(int16 height) = 0;

			/**	Returns the amount to overlapp the stroke and fill proxy. -1 means fill only, -2 means stroke only.
			*/
			virtual int16		GetStrokeFillOverlap	(void) = 0;
			/**	Sets the amount to overlapp the stroke and fill proxy.
				Use a value < 0 to draw the widget in just one mode, e.g. just draw the fill or the stroke widget, but not both
				@param overlapAmount the stroke/fill proxy overlap amount.
			*/
			virtual void		SetStrokeFillOverlap	(int16 overlapAmount) = 0;

			/**	Returns the border width to draw around the fill and stroke proxy.
				If it is set to 0, then border is not drawn.
				@return the stroke/fill proxy border width.
			*/
			virtual int16		GetStrokeFillHiliteBorder(void) = 0;
			/**	Sets the border width to draw around the fill and stroke proxy.
				@param border the stroke/fill proxy border width.
			*/
			virtual void		SetStrokeFillHiliteBorder(int16 border) = 0;

			/**	Returns the width of the stroke proxy.
			*/
			virtual int16		GetStrokeWidth			(void) = 0;
			/**	Sets the width of the stroke proxy.
				@param strokeWidth the stroke proxy width.
			*/
			virtual void		SetStrokeWidth			(int16 strokeWidth) = 0;

			/**	Returns true if the stroke/fill proxy is draggable.
			*/
			virtual bool16		GetDraggable			(void) = 0;
			/**	Set to true if the stroke/fill proxy is draggable.
				@param isDraggable is true if the stroke/fill proxy is draggable.
			*/
			virtual void		SetDraggable			(bool16 isDraggable) = 0;

			/**	DisplayOptionType specifies what to do when user double-click on the stroke/fill proxy.
			*/
			typedef enum
			{
				/** kNoOption indicates don't do anything.
				*/
				kNoOption = 0,
				/**	kOptionDialog brings up the swatch option dialog.
				*/
				kOptionDialog,
				/**	kRenderObjectPanel brings up either the color picker or the gradient panel.
				*/
				kRenderObjectPanel
			} DisplayOptionType;
			
			/**	Returns the type of display option when double-click on the stroke/fill proxy widget.
				@return the type of display option. This would be one of @DisplayOptionType
			*/
			virtual IStrokeFillControlData::DisplayOptionType	GetDisplayOption		(void) = 0;
			/**	Sets the type of display option when double-click on the stroke/fill proxy widget.
				@param displayOption the type of display option. This would be one of @DisplayOptionType
			*/
			virtual void		SetDisplayOption		(IStrokeFillControlData::DisplayOptionType displayOption) = 0;

			/**	Returns whether the widget can toggle between fill and stroke modes.
				When not switchable, only fill or only stroke will be drawn depending on GetActive
			*/
			virtual bool16		GetSwitchable			(void) = 0;

			/**	Sets whether the widget can toggle between displaying fill or stroke in the front.
				@param isSwitchable kTrue to allow switchability, kFalse to disallow.
			*/
			virtual void		SetSwitchable			(bool16 isSwitchable) = 0;

		//________________________________________________________________________________
		//	Active Item
		//________________________________________________________________________________
		public:
			/**	Returns the current active proxy type.
				@return either kStrokeActive or kFillActive.
				@see ToolboxProxyTypes.h
			*/
			virtual ToolboxProxy::ActiveProxyType	GetActive				(void) = 0;
			/**	Sets the current active proxy type to the one specified.
				@param activeProxy is the new active proxy.
			*/
			virtual void		SetActive				(ToolboxProxy::ActiveProxyType activeProxy) = 0;

		//________________________________________________________________________________
		//	Format of Data (either UID or meta data)
		//________________________________________________________________________________
		public:
			/**	Returns true if using metadata to draw the stroke/fill proxy.
				Otherwise returns false if using UIDs.
				@return true if drawing stroke/fill proxy with metadata
			*/
			virtual bool16		UseMetaData				(void) = 0;
			/**	Sets to true if using metadata to draw the stroke/fill proxy.
				Otherwise sets to false if using UIDs.
				@param usingMetaData is true if drawing stroke/fill proxy with metadata
			*/
			virtual void		SetUseMetaData			(bool16 usingMetaData) = 0;

			/**	Returns true if using metadata to draw the fill proxy.
				Otherwise returns false if using UIDs.
				@return true if drawing fill proxy with metadata
			*/
			virtual bool16		UseFillMetaData			(void) = 0;
			/**	Sets to true if using metadata to draw the fill proxy.
				Otherwise sets to false if using UIDs.
				@param usingMetaData is true if drawing fill proxy with metadata
			*/
			virtual void		SetFillUseMetaData		(bool16 usingMetaData) = 0;

			/**	Returns true if using metadata to draw the stroke proxy.
				Otherwise returns false if using UIDs.
				@return true if drawing stroke proxy with metadata
			*/
			virtual bool16		UseStrokeMetaData		(void) = 0;
			/**	Sets to true if using metadata to draw the stroke proxy.
				Otherwise sets to false if using UIDs.
				@param usingMetaData is true if drawing stroke proxy with metadata
			*/
			virtual void		SetStrokeUseMetaData	(bool16) = 0;
		//________________________________________________________________________________
		//	Meta Data format
		//________________________________________________________________________________
		public:
			/**	Returns the metadata object we are using to draw the fill proxy.
				@return the fill metadata object.
			*/
			virtual IPMUnknown*	GetFillMetaData			(void) = 0;
			/**	Sets the fill metadata for drawing the fill proxy.
				@param fillMetaData the fill metadata
			*/
			virtual void		SetFillMetaData			(IPMUnknown* fillMetaData) = 0;

			/**	Returns the metadata object we are using to draw the stroke proxy.
				@return the stroke metadata object.
			*/
			virtual IPMUnknown*	GetStrokeMetaData		(void) = 0;
			/**	Sets the stroke metadata for drawing the stroke proxy.
				@param strokeMetaData the fill metadata
			*/
			virtual void		SetStrokeMetaData		(IPMUnknown* strokeMetaData) = 0;

		//________________________________________________________________________________
		//	UID format
		//________________________________________________________________________________
		public:
			/**	Returns the swatch UID we are using to draw the fill proxy.
				@return the fill UID.
			*/
			virtual UID			GetFillUID				(void) = 0;
			/**	Sets the fill UID for drawing the fill proxy.
				@param fillUID the fill UID.
			*/
			virtual void		SetFillUID				(UID fillUID) = 0;

			/**	Returns the swatch UID we are using to draw the stroke proxy.
				@return the stroke UID.
			*/
			virtual UID			GetStrokeUID			(void) = 0;
			/**	Sets the stroke UID for drawing the stroke proxy.
				@param strokeUID the stroke UID.
			*/
			virtual void		SetStrokeUID			(UID strokeUID) = 0;

			/**	Returns the database associated with the stroke and fill UID.
				@return the fill/stroke database.
			*/
			virtual IDataBase*	GetDataBase				(void) = 0;
			/**	Sets the database associated with the stroke/fill UID.
				@param iDataBase the database.
			*/
			virtual void		SetDataBase				(IDataBase* iDataBase) = 0;

			/**	Returns the true if fill is indeterminant.
			*/
			virtual bool16		IsFillIndeterminate		(void) = 0;
			/**	Sets the to true if fill is indeterminant.
				@param setInderminant is true if fill is indeterminat.
			*/
			virtual void		SetFillIndeterminate	(bool16 setInderminant) = 0;

			/**	Returns the true if stroke is indeterminant.
			*/
			virtual bool16		IsStrokeIndeterminate	(void) = 0;
			/**	Sets the to true if stroke is indeterminant.
				@param setInderminant is true if stroke is indeterminat.
			*/
			virtual void		SetStrokeIndeterminate	(bool16 setInderminant) = 0;
			
			/**	Returns the current fill tint percent.
			*/
			virtual PMReal		GetFillTint				(void) = 0;
			/**	Sets the current fill UID and tint percent.
				@param fillUID the current fill UID.
				@param fillTint the current fill tint percent.
			*/
			virtual void		SetFillUIDAndTint		(UID fillUID, const PMReal& fillTint = kInvalidTintPercent) = 0;


			/**	Returns the current stroke tint percent.
			*/
			virtual PMReal		GetStrokeTint			(void) = 0;
			/**	Sets the current stroke UID and tint percent.
				@param strokeUID the current stroke UID.
				@param strokeTint the current stroke tint percent.
			*/
			virtual void		SetStrokeUIDAndTint		(UID strokeUID, const PMReal& strokeTint = kInvalidTintPercent) = 0;

		//________________________________________________________________________________
		//	Updating
		//________________________________________________________________________________
		public:
			/**	Invalidate the stroke/fill proxy view.
			*/
			virtual void		InvalidateView			(void) = 0;
			/**	Invalidate the stroke proxy view.
			*/
			virtual void		InvalidateStroke		(void) = 0;
			/**	Invalidate the fill proxy view.
			*/
			virtual void		InvalidateFill			(void) = 0;
			
			typedef enum
			{
				/**	kNone specifies the current mouse location is outside of stroke/fill proxy widget.
				*/
				kNone			= -1,
				/**	kStroke specifies the current mouse location is in the stroke proxy widget.
				*/
				kStroke,
				/**	kFill specifies the current mouse location is in the fill proxy widget.
				*/
				kFill
			} PartCode;
			
			/**	Returns the position of the mouse relative to the stroke/fill proxy.
				@param localPoint the mouse position.
				@return one of @PartCode.
			*/
			virtual IStrokeFillControlData::PartCode	GetPartCode (const PMPoint& localPoint) const = 0;
		};
		
#endif // _IStrokeFillControlData_
