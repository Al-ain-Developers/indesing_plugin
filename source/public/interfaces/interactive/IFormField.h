//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IFormField.h $
//  
//  Owner: Tim Wright
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
#ifndef __IFormField_h__
#define __IFormField_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "PMPoint.h"
#include "FormFieldTypes.h"
#include "FormFieldID.h"

//=============================================================================

class IGraphicsPort;
class IFontInstance;
class IGraphicStyleAttributeBossList;
class IFormFieldFactory;

/**  
  
  Base type for FormField.
  
  A form page item is identified as a form using this interface.
  IFormField implements behaviors that may be different among
  different form field types (e.g. push buttons, text fields...)
  A form page item supports form-specific graphic attributes,
  and is exported as an widget annotation in a PDF file.
*/
class IFormField : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFORMFIELD };
	
	/** Determine whether this form field supports any of the states in Form::DefinedAppearanceState
		@return kTrue if this form field supports any of the states in Form::DefinedAppearanceState, otherwise kFalse
	*/
	virtual bool16 SupportsDefinedStates() const = 0;

	/** Determine whether this form field supports Form::AppearanceState values other than those defined
		in Form::DefinedAppearanceState - if this is true, all Form::AppearanceState values greater than Form::kStateLast
		are supported states.
		@return kTrue if this form field supports states other than those in Form::DefinedAppearanceState, otherwise kFalse
	*/
	virtual bool16 SupportsUndefinedStates() const = 0;

	/** Determine whether this form field can have an appearance state of a particular type
		Example, push buttons support kStateNormal, kStateOver, kStateDown.
		text fields only support kStateNormal
		@param inState Type of state
		@return kTrue if state is supported on this form field (regardless of whether it exists or not)
	*/
	virtual bool16 SupportsState(Form::AppearanceState inState) const = 0;

	/** Indicates whether you can assign custom names to this item's states.
		@return kTrue if custom names can be assigned, kFalse otherwise
	*/
	virtual bool16 SupportsCustomStateNames( ) const = 0;

	/** Gets Icon to use for icon frame adornment
		@param outRsrcID Points to resource id of icon on exit
	*/
	virtual void GetIconRsrcID( PMRsrcID* outRsrcID ) = 0; 

	/** Get human-readable name for an appearance state type.
		For example, a check box and a radio button have different names for the
		kState*On states ("* Checked" versus "* Selected")
		@param inState state you want the name for
		@return PMString of state name
	*/
	virtual PMString GetStateName( Form::AppearanceState inState ) const = 0;

	/** Sets the human-readable name for the state.
		@param inState state you want the name for
		@param inName the name you would like to assign to the state
		@return kSuccess if the state was renamed, otherwise kFailure
	*/
	virtual ErrorCode SetStateName( Form::AppearanceState inState, const PMString& inName ) = 0;

	/** Get a factory interface that matches the form type.  This factory
	    provides form field utilities that have implementations that are
	    specific to a form field type.  So, for example, if this IFormField
	    is implemented as a PushButtonFormField, the factory returned is
	    PushButtonFormFieldFactory.
		@returns A form field factory that corresponds to this IFormField.
	*/
	virtual IFormFieldFactory* QueryFormFieldFactory() = 0;

	/** Adds all graphic attributes appropriate for the IFormField to outAttrs.
		All properties of a form field are graphic attributes, except the appearance
		states which are IAppearanceLists and page items.  This is used when creating
		a new form field, for example, so that it contains default versions of all
		the attributes of the form field.
		@param outAttrs is a pointer to a attribute list that attributes will be
		@see IGraphicStyleAttributeBossList
	*/
	virtual void  AddDefaultAttributes( IGraphicStyleAttributeBossList* outAttrs ) = 0;
};

//=============================================================================

#endif // __IForm_h__

//  IFormField.h.
