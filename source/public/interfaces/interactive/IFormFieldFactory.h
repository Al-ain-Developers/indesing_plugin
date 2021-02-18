//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IFormFieldFactory.h $
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

#ifndef __IFormFieldFactory_h__
#define __IFormFieldFactory_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "FormFieldTypes.h"
#include "FormFieldID.h"

//=============================================================================

class IDocument;
class IGraphicStyleAttributeBossList;

/** Abstract Factory and Utility interface for a particular form field type.
	There are Implementations of IFormFieldFactory for each form field type.
	(e.g. kPushButtonFactoryImpl, kCheckBoxFactoryImpl, etc)
	The factory can be used to create new form fields of one type.  Each form
	field has an interface, IFormField, that contains a method, QueryFormFieldFactory,
	to get the IFormFieldFactory that created it.
	IFormFieldFactory is an interface on a service, so that all the form types
	can be enumerated.
*/
class IFormFieldFactory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFORMFIELDFACTORY };
	
	/** @return Human readable name of Form Field type that this Factory creates. e.g. "Push Button" */
	virtual PMString GetFieldTypeName() const = 0;

	/** Create a form field
		@param inParent Form field is created as child of inParent
		@param inBounds dimensions of new form field
		@returns UIDRef of form field page item created*/
	virtual UIDRef CreateFormField (const UIDRef& inParent, const PMRect& inBounds ) const = 0;
	
	
	/** Get name of style library for this form field type.
		@returns name of style library for form field type, or "" if form field type
				doesn't support styles.
	*/
	virtual PMString GetStyleLibName() const = 0;
	
	
	/** Get the built in base default name to be used to name this type of form field object
		@returns the base default name to be used to name this type of form field object
	*/
	virtual PMString GetDefaultBaseObjectName() const = 0;
		
	/** Add default attributes for form field into outAttrs.  Used to add required attributes for new form fields.
		@param defaultAttrs a list of attributes to use for defaults. May be nil.
			Not all attributes need be present in defaultAttrs. If an attribute is missing the implementation of AddDefaultAttributes
			will return a constant default in outAttr.
		@param inDoc is used to generate a unique name.  If nil, name attribute returned in outAttrs is "".
		@param outAttrs return a list default attributes appropriate for form type here
	*/	
	virtual void AddDefaultAttributes( IGraphicStyleAttributeBossList* outAttrs, IGraphicStyleAttributeBossList* defaultAttrs, IDocument* inDoc ) = 0;
	
	
	/** Does AddDefaultAttributes to a new list, using defaultAttrs = 0, inDoc = 0, and returns it.
		Therefore it gets the constant default values, without relying on another list
		for defaults.
		@return List of default graphic attributes for the relevant form field type
	*/
	virtual IGraphicStyleAttributeBossList* QueryDefaultAttributes() = 0;
	
	/** Generate a unique name for IFormFieldFactory's form field type.
		@param inName if this is an empty string, name returned is of the form <Form Type> N, otherwise
				it is <inName> N, where N is a unique number tracked in inDoc
		@param inDoc used to track number appended to returned unique name.
		@returns a unique name. nil if inDoc is nil.
	*/
	virtual PMString GetUniqueName( const PMString& inName, IDocument* inDoc ) = 0;
};

//=============================================================================

#endif //

//  IFormFieldFactory.h.
