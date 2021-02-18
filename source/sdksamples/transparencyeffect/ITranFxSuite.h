//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/ITranFxSuite.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef _ITranFxSuite_
#define _ITranFxSuite_

// Interface includes:
#include "IPMUnknown.h"
#include "TranFxID.h"

/** From SDK sample;  abstract suite which extends the selection so that it can
	manipulate this plug-in's transparency effect.

	
	@ingroup transparencyeffect
*/
class ITranFxSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITRANFXSUITE };

	public:
		/** Enumeration indicating whether all the selected objects
			have no value, a common value or a mixed number of different
			values for a given attribute. Several objects can be selected 
			simultaneously and have different values, or a common value,
			for an attribute. This state is normally reflected by 
			client code in user interface controls.
		 */
		typedef enum 		{eNoValue, eCommonValue, eMixedValue} AttrState;

		/**	Checks if objects that are selected have this plug-in's adornment applied.
			@param attrState OUT eCommonValue if all selected objects have the adornment, eMixedValue some objects have the adornment, eNoValue none of the objects have the adornment.
		 */
		virtual	void		HasAdornment(AttrState& attrState) const = 0;

		/** Checks the x offset of objects that are selected.
			@param attrState OUT eCommonValue if all selected objects share the same x offset value (default value 7.0 points).
			@param value OUT the x offset.
		 */
		virtual	void		HasXOffset(AttrState& attrState, PMReal& value) const = 0;

		/** Checks the y offset of objects that are selected.
			@param attrState OUT eCommonValue if all selected objects share the same y offset value (default value 7.0 points).
			@param value OUT the y offset
		 */
		virtual	void		HasYOffset(AttrState& attrState, PMReal& value) const = 0;

		/** Checks the state of the black as opaque flag of objects that are selected.
			@param itemList IN list of objects to be checked.
			@param value OUT kTrue if darker pixels in the page item should be more opaque in the effect, kFalse if transparent (default value kTrue).
			@return enum indicating state of the attribute value.
			@see ITranFxSuite::ApplyUseBlackAsOpaque.
		*/
		virtual	void		HasUseBlackAsOpaque(AttrState& attrState, bool16& value) const = 0;

		/** Checks the state of the alpha flag of objects that are selected.
			@param itemList IN list of objects to be checked.
			@param value OUT kTrue if alpha channel associated with page item should be applied to the effect, kFalse if not (default value kTrue).
			@return enum indicating state of the attribute value.
			@see ITranFxSuite::ApplyUseAlpha.
		*/
		virtual	void		HasUseAlpha(AttrState& attrState, bool16& value) const = 0;

		/** Checks the state of the blur flag of objects that are selected.
			@param itemList IN list of objects to be checked.
			@param value OUT kTrue if the effect should be blurred and reduced in intensity, kFalse if not (default value kTrue).
			@return enum indicating state of the attribute value.
			@see ITranFxSuite::ApplyUseBlur.
		*/
		virtual	void		HasUseBlur(AttrState& attrState, bool16& value) const = 0;

	public:
		/** Return kTrue if adornment can be applied, kFalse otherwise.
			@return kTrue if adornment can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyAdornment() const = 0;

		/** Return kTrue if x offset can be applied, kFalse otherwise.
			@return kTrue if x offset can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyXOffset() const = 0;

		/** Return kTrue if y offset can be applied, kFalse otherwise.
			@return kTrue if y offset can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyYOffset() const = 0;

		/** Return kTrue if black as opaque flag can be applied, kFalse otherwise.
			@return kTrue if black as opaque flag can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyUseBlackAsOpaque() const = 0;

		/** Return kTrue if alpha flag can be applied, kFalse otherwise.
			@return kTrue if alpha flag can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyUseAlpha() const = 0;

		/** Return kTrue if blur flag can be applied, kFalse otherwise.
			@return kTrue if blur flag can be applied, kFalse otherwise.
		 */
		virtual bool16	CanApplyUseBlur() const = 0;

	public:
		/** Add or remove this plug-in's adornment to the objects that are selected.
			@param isAdd IN kTrue to add adornment, kFalse to remove.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode	ApplyAdornment(const bool16 isAdd) = 0;

		/** Change the x offset of the objects that are selected.
			@param value IN the value to be applied.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode	ApplyXOffset(const PMReal& value) = 0;

		/** Change the x offset of the objects that are selected.
			@param value IN the value to be applied.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode	ApplyYOffset(const PMReal& value) = 0;

		/** Change the state of the black as opaque flag of the objects that are selected.
			This controls whether darker pixels
			in the page item are more opaque in the matte effect (kTrue) or more transparent (kFalse).
			@param value kTrue to cause darker pixels in the page item to be more opaque in the matte effect (black is fully opaque) 
				and lighter pixels to be more transparent (white is fully transparent). kFalse to cause darker pixels in the page item 
				to be more transparent in the matte effect (black is fully transparent) and lighter pixels to be more opaque
				(white is fully opaque). For example, if you want black text or a graphic with a black stroke to cast a matte effect, 
				then make this kTrue. For example, if you want white text or a graphic with a white stroke to cast a matte effect, 
				then make this kFalse.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode	ApplyUseBlackAsOpaque(const bool16 value) = 0;
		
		/** Change the state of the alpha flag of the objects that are selected.
			@param value kTrue to apply the alpha channel associated with the page item to the matte effect, kFalse if not.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode	ApplyUseAlpha(const bool16 value) = 0;

		/** Change the state of the blur flag of the objects that are selected.
			@param value kTrue to apply a slight blur to the matte effect and to reduce its intensity compared to the page item, kFalse if not.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode	ApplyUseBlur(const bool16 value) = 0;
};

#endif // _ITranFxSuite_

