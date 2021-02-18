//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IStrokeAttributeSuite.h $
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
//  This is a high level attribute suite specifically to faciliate getting/setting of simple
//  stroke attributes. It uses the IGraphicAttributeSuite to get/set appropriate data.
//  
//========================================================================================

#pragma once
	#ifndef _IStrokeAttributeSuite_
	#define _IStrokeAttributeSuite_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
	#include "K2Vector.h"
	
	#include "IGraphicAttributeSuite.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/** This is a high level attribute suite interface specifically to faciliate 
	getting/setting of various stroke attributes. It uses the 
	IGraphicAttributeSuite to get/set appropriate data.
	Each attribute type has four methods:
	1.	Get__Count.
		Get the number of unique value for that attribute. A zero count means this attribute
		does not exist in the selection. A value of one means there's exactly one unique
		value representing this attribute. A value greater than one implies a mixed selection.
	2.	Get__ValueCount.
		Get the number of nth value for this attribute. If there are more than one value in
		the selection, then use this method to determine the number of occurrences for each
		of the attribute value.
	3.	Get__.
		Get the attribute value specified by the given index.
	4.	Is__Enabled.
		Returns kTrue/kFalse to indicate if this attribute is enabled.
*/
class IStrokeAttributeSuite : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ISTROKEATTRIBUTESUITE };
		
	//____________________________________________________________________________________
	//	Stroke Weight Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of unique stroke weight count in the selection.
		*/
		virtual uint16 				GetStrokeWeightCount			(void) const = 0;
		/** Returns the number of nth stroke weight value count specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetStrokeWeightValueCount 		(uint32 whichAttribute) const = 0;
		/** Returns the nth stroke weight in the selection specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetStrokeWeight					(uint32 whichAttribute) const = 0;
		/** Returns kTrue if the stroke weight attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsStrokeWeightEnabled			(void) = 0;
		
		/** Returns the number of none-zero stroke weight in the selection.
		*/
		virtual uint16				GetVisibleStrokeWeightCount		(void) = 0;
		/** Returns the nth visible stroke weight in the selection specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetVisibleStrokeWeight			(uint32 whichAttribute) = 0;
		
	//____________________________________________________________________________________
	//	Stroke Type Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of line implementation classes.
		*/
		virtual uint16 				GetLineImplCount			(void) const = 0;
		/** Returns the number of nth line implementation classes specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetLineImplValueCount 		(uint32 whichAttribute) const = 0;
		/** Returns the nth line implementation class and the associated UID for a custom line style.
			implUID is kInvalidUID for a predefined line implementation class.
			@param whichAttribute the nth attribute index starting from 0.
			@param implClass the nth line implementation class ID.
			@param implUID the nth line implemenation UID.
		*/
		virtual void				GetLineImpl					(uint32 whichAttribute, ClassID &implClass, UID &implUID) const = 0;
		/** Returns kTrue if the given line implementation is currently enabled.
			Otherwise returns kFalse.
			@param line implementation class to query.
		*/
		virtual bool16				IsLineImplEnabled			(ClassID = kInvalidClass) = 0;

	//____________________________________________________________________________________
	//	Line Cap Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of line caps.
		*/
		virtual uint16 				GetLineCapCount					(void) const = 0;
		/** Returns the number of nth line caps specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetLineCapValueCount 			(uint32 whichAttribute) const = 0;
		/** Returns the nth line cap specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int32				GetLineCap						(uint32 whichAttribute) const = 0;
		/** Returns kTrue if the line cap is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsLineCapEnabled				(void) = 0;

	//____________________________________________________________________________________
	//	Join Type Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of join types.
		*/
		virtual uint16 				GetJoinTypeCount				(void) const = 0;
		/** Returns the number of nth join types specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetJoinTypeValueCount 			(uint32 whichAttribute) const = 0;
		/** Returns the nth join type specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int32				GetJoinType						(uint32) const = 0;
		/** Returns kTrue if the join type is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsJoinTypeEnabled				(void) = 0;

	//____________________________________________________________________________________
	//	Arrow Head Alignment Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of arrow head alignments.
		*/
		virtual uint16 				GetArrowHeadAlignmentCount					(void) const = 0;
		/** Returns the number of nth arrow head alignments specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetArrowHeadAlignmentValueCount 			(uint32 whichAttribute) const = 0;
		/** Returns the nth arrow head alignment specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int32				GetArrowHeadAlignment						(uint32 whichAttribute) const = 0;
		/** Returns kTrue if the arrow head alignment is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsArrowHeadAlignmentEnabled				(void) = 0;

	//____________________________________________________________________________________
	//	Line Start Start Type Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of line start implmentation classes.
		*/
		virtual uint16 				GetLineStartImplClassCount		(void) const = 0;
		/** Returns the number of nth line start implmentation classes specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetLineStartImplClassValueCount (uint32 whichAttribute) const = 0;
		/** Returns the nth line start implmentation class specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual ClassID				GetLineStartImplClass			(uint32 whichAttribute) const = 0;
		/** Returns kTrue if the line start attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsLineStartImplClassEnabled		(void) = 0;

	//____________________________________________________________________________________
	//	Line End End Type Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of line end implmentation classes.
		*/
		virtual uint16 				GetLineEndImplClassCount		(void) const = 0;
		/** Returns the number of nth line end implmentation classes specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetLineEndImplClassValueCount 	(uint32 whichAttribute) const = 0;
		/** Returns the nth line end implmentation class specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual ClassID				GetLineEndImplClass				(uint32) const = 0;
		/** Returns kTrue if the line end attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsLineEndImplClassEnabled		(void) = 0;

	//____________________________________________________________________________________
	//	Line Corner Type Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of corner implmentation classes.
		*/
		virtual uint16 				GetCornerImplClassCount			(void) const = 0;
		/** Returns the number of nth corner implmentation classes specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetCornerImplClassValueCount 	(uint32 whichAttribute) const = 0;
		/** Returns the nth corner implmentation class specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual ClassID				GetCornerImplClass				(uint32) const = 0;
		/** Returns kTrue if the corner type attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsCornerImplClassEnabled		(void) = 0;

	//____________________________________________________________________________________
	//	Line Corner Radius Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of corner radius.
		*/
		virtual uint16 				GetCornerRadiusCount			(void) const = 0;
		/** Returns the number of nth corner radius specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetCornerRadiusValueCount 		(uint32 whichAttribute) const = 0;
		/** Returns the nth corner radius specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetCornerRadius					(uint32) const = 0;
		/** Returns kTrue if the corner radius attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsCornerRadiusEnabled			(void) = 0;

	//____________________________________________________________________________________
	//	Line Miter Limit Utilities 
	//____________________________________________________________________________________
	public:
		/** Returns the number of miter limits.
		*/
		virtual uint16 				GetMiterLimitCount				(void) const = 0;
		/** Returns the number of nth miter limits specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetMiterLimitValueCount 		(uint32 whichAttribute) const = 0;
		/** Returns the nth miter limit specified by whichAttribute.
			@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetMiterLimit					(uint32) const = 0;
		/** Returns kTrue if the miter limit attribute is currently enabled.
			Otherwise returns kFalse.
		*/
		virtual bool16				IsMiterLimitEnabled				(void) = 0;

	//____________________________________________________________________________________
	//	Line Stroke Alignment Utilities 
	//____________________________________________________________________________________
	public:
		/**
		 Returns the number of stroke alignments in the selection.

		 @return The number of stroke alignments
		*/
		virtual uint16 				GetStrokeAlignmentCount			() const = 0;

		/**
		 Returns the number of nth stroke alignment specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The number of nth stroke alignment specified by whichAttribute
		*/
		virtual int16				GetStrokeAlignmentValueCount 	(uint32 whichAttribute) const = 0;

		/**
		 Returns the nth stroke alignment specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The nth stroke alignment specified by whichAttribute
		*/
		virtual int32				GetStrokeAlignment				(uint32 whichAttribute) const = 0;

		/**
		 Returns kTrue if the stroke alignment attribute is currently enabled. Otherwise returns kFalse.
		 3 parameters returns if each alignment (center, inside and outside) is enabled. 
		 For most cases we don't care as they are in the same state as stroke alignment attribute.

		 @param centerAlign - When non-nil, returns kTrue if center alignment is enabled, otherwise kFalse.
		 @param insideAlign - When non-nil, returns kTrue if center alignment is enabled, otherwise kFalse.
		 @param outsideAlign - When non-nil, returns kTrue if center alignment is enabled, otherwise kFalse.

		 @return Boolean value indicating if stroke alignment is enabled
		*/
		virtual bool16				GetStrokeAlignmentsEnabledFlags		(bool16* centerAlign = nil, bool16* insideAlign = nil, bool16* outsideAlign = nil) const = 0;

		/**
		Returns default stroke alignment.
		*/
		virtual int32				GetDefaultStrokeAlignment		() const = 0;

	//____________________________________________________________________________________
	//	Gap Color Utilities 
	//____________________________________________________________________________________
	public:
		/**
		 Returns the number of gap colors in the selection.

		 @return The number of gap colors
		*/
		virtual uint16 				GetGapColorCount			() const = 0;

		/**
		 Returns the number of nth gap color specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The number of nth gap color specified by whichAttribute
		*/
		virtual uint16				GetGapColorValueCount 	(uint32 whichAttribute) const = 0;

		/**
		 Returns the nth gap colors specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The nth gap color UID specified by whichAttribute
		*/
		virtual UID					GetGapColor				(uint32 whichAttribute) const = 0;

		/**
		 Returns kTrue if the gap color attribute is currently enabled.
		 Otherwise returns kFalse.

		 @return Boolean value indicating if gap color is enabled
		*/
		virtual bool16				IsGapColorEnabled		() const = 0;

	//____________________________________________________________________________________
	//	Gap Tint Utilities 
	//____________________________________________________________________________________
	public:
		/**
		 Returns the number of gap tints in the selection.

		 @return The number of gap tints
		*/
		virtual uint16 				GetGapTintCount			() const = 0;

		/**
		 Returns the number of nth gap tints specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The number of nth gap tint specified by whichAttribute
		*/
		virtual uint16				GetGapTintValueCount 	(uint32 whichAttribute) const = 0;

		/**
		 Returns the nth gap tint specified by whichAttribute.

		 @param whichAttribute	The nth attribute index starting from 0.
		 @return The nth gap tint specified by whichAttribute
		*/
		virtual PMReal				GetGapTint				(uint32 whichAttribute) const = 0;

		/**
		 Returns kTrue if the gap tint attribute is currently enabled.
		 Otherwise returns kFalse.

		 @return Boolean value indicating if gap tint is enabled
		*/
		virtual bool16				IsGapTintEnabled		() const = 0;

		//____________________________________________________________________________________
		//	Arrow Head Start Scale Utilities...
		//____________________________________________________________________________________
	public:
		/** Returns the number of unique arrowheadstartscale attribute count in the selection.
		*/
		virtual uint16 				GetArrowHeadStartScaleCount(void) const = 0;

		/** Returns the number of nth arrowheadstartscale value count specified by whichAttribute.
		@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetArrowHeadStartScaleValueCount(uint32 whichAttribute) const = 0;

		/** Returns the arrow head start scale for the nth arrowheadstartscale attribute
		@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetArrowHeadStartScale(uint32 whichAttribute) const = 0;

		/** Returns kTrue if the arrow head start scale attribute is currently enabled.
		Otherwise returns kFalse.
		*/
		virtual bool16				IsArrowHeadStartScaleEnabled(void) = 0;

		//____________________________________________________________________________________
		//	Arrow Head End Scale Utilities...
		//____________________________________________________________________________________
	public:
		/**  Returns the number of unique arrow head end scale count in the selection.
		*/
		virtual uint16 				GetArrowHeadEndScaleCount(void) const = 0;

		/** Returns the number of nth arrow head end scale value count specified by whichAttribute.
		@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual int16				GetArrowHeadEndScaleValueCount(uint32 whichAttribute) const = 0;

		/** Returns the arrow head end scale for the nth arrowheadendscale attribute
		@param whichAttribute the nth attribute index starting from 0.
		*/
		virtual PMReal				GetArrowHeadEndScale(uint32 whichAttribute) const = 0;
		/** Returns kTrue if the arrow head end scale attribute is currently enabled.
		Otherwise returns kFalse.
		*/
		virtual bool16				IsArrowHeadEndScaleEnabled(void) = 0;

	//____________________________________________________________________________________
	//	Other Utilities 
	//____________________________________________________________________________________
	public:
		/** Apply the specified strokeWeight to the selection.
			@param strokeWeight stroke to apply.
		*/
		virtual	ErrorCode			ApplyStrokeWeight				(const PMReal& strokeWeight) = 0;
		/** Apply the specified line impelementation class and UID to the selection.
			@param implClass line impelmentation class ID to apply.
			@param implUID line impelmentation UID to apply. implUID should not be kInvalidUID for
			custom line implementation class.
		*/
		virtual	ErrorCode			ApplyLineImpl					(const ClassID &implClass, UID const &implUID = kInvalidUID) = 0;
		/** Apply the specified line cap to the selection.
			@param lineCap the line cap to apply.
		*/
		virtual	ErrorCode			ApplyLineCap					(const int32& lineCap) = 0;
		/** Apply the specified join type to the selection.
			@param joinType the join type to apply.
		*/
		virtual	ErrorCode			ApplyJoinType					(const int32& joinType) = 0;
		/** Apply the specified line cap to the selection.
			@param arrowHeadAlignment the arrow head alignment to apply.
		*/
		virtual	ErrorCode			ApplyArrowHeadAlignment			(const int32& arrowHeadAlignment) = 0;
		/** Apply the specified line start implementation class to the selection.
			@param implClass the line start implementation class to apply.
		*/
		virtual	ErrorCode			ApplyLineStartImplClass			(const ClassID& implClass) = 0;
		/** Apply the specified line end implementation class to the selection.
			@param implClass the line end implementation class to apply.
		*/
		virtual	ErrorCode			ApplyLineEndImplClass			(const ClassID& implClass) = 0;
		/** Apply the specified corner type to the selection.
			@param implClass the corner type to apply.
		*/
		virtual	ErrorCode			ApplyCornerImplClass			(const ClassID& implClass) = 0;
		/** Apply the specified corner radius to the selection.
			@param radius the corner radius to apply.
		*/
		virtual	ErrorCode			ApplyCornerRadius				(const PMReal& radius) = 0;
		/** Apply the specified miter limit to the selection.
			@param miterLimit the miter limit to apply.
		*/
		virtual	ErrorCode			ApplyMiterLimit					(const PMReal& miterLimit) = 0;

		/**
		 Apply the specified stroke alignment to the selection

		 @param strokeAlignment		The alignment to apply.
		 @return kSuccess if successful, else an error code
		 */
		virtual ErrorCode			ApplyStrokeAlignment			(int32 strokeAlignment) = 0;

		/**
		 Apply the specified gap color UID to the selection

		 @param gapColorUID			The UID for the swatch to apply
		 @return kSuccess if successful, else an error code
		 */
		virtual ErrorCode			ApplyGapColor					(UID const &gapColorUID) = 0;

		/**
		 Apply the specified gap color tint to the selection

		 @param tint				The tint to apply (0%..100%)
		 @return kSuccess if successful, else an error code
		 */
		virtual ErrorCode			ApplyGapTint					(PMReal const &tint) = 0;

		/**
		Apply the specified arrow head scale factor to the start arrow head

		@param arrowHeadScaleFactor		The scaling to be applied to the start arrow head (1%..1000%)..Default scaling is 100%
		@return kSuccess if successful, else an error code
		*/
		virtual	ErrorCode			ApplyArrowHeadStartScale		(const PMReal& arrowHeadScaleFactor) = 0;

		/**
		Apply the specified arrow head scale factor to the end arrow head

		@param arrowHeadScaleFactor		The scaling to be applied to the end arrow head (1%..1000%)..Default scaling is 100%
		@return kSuccess if successful, else an error code
		*/

		virtual	ErrorCode			ApplyArrowHeadEndScale			(const PMReal& arrowHeadScaleFactor) = 0;

	};

#endif // _IStrokeAttributeSuite_
