//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLDTDValidationError.h $
//  
//  Owner: Will Lin
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
//  Adobe Patent of Adobe Patent Pending Invention Included Within this File
//  
//========================================================================================

#pragma once
#ifndef __XMLDTDValidationError__
#define __XMLDTDValidationError__


#include "XMLDTDValidateSuggest.h"
#include "XMLReference.h"


//
// Adobe patent application tracking P563, entitled XML DTD Validation With 
// Suggestion For Fixing Validation Errors, inventors: Lin
//

/**	Class for a single error during XML DTD validation. Each error consists of an error code, a
	XMLReference of where the error occurred (or base XMLReference), and a list of correction
	suggestions.

	@see XMLDTDValidateSuggest
*/
class PUBLIC_DECL XMLDTDValidationError
{
	public:
		/** XML DTD validation error codes.
			internal errors:

			kXMLInvalidDTDXMLReferenceErr		invalid DTD XMLReference. Unable to obtain the element that contains the DTD

			kXMLNILDTDErr						NIL DTD


			general errors:

			kXMLInvalidNMTokenErr				REC-xml-20001006, [7]: invalid Nmtoken
			

			kXMLInvalidNameTokenErr				REC-xml-20001006, [5]: invalid name token
			

			element errors:

			kXMLBadRootElementTypeErr			REC-xml-20001006, 2.8: root element tag must match DOCTYPE declaration's element type
			

			kXMLEMPTYElementWithContentErr		REC-xml-20001006, 3: EMPTY element cannot have content
			
			kXMLUnexpectedElementErr			REC-xml-20001006, 3: element that is not part of a content model was found

			kXMLMissingElementErr				REC-xml-20001006, 3: element required by the content model was not found

			kXMLUndeclaredElementErr			REC-xml-20001006, 3: undeclared element found


			attribute errors:

			kXMLMissingRequiredAttributeErr		REC-xml-20001006, 3.3.2: missing required attribute. An attribute declared as #REQUIRED default value is not found

			kXMLExtraAttributeErr				REC-xml-20001006, 3.1: extra attribute. Element contains an attribute that is not declared as part of the element in the DTD

			kXMLNotUnparsedEntityInAttValueErr	REC-xml-20001006, 3.3.1: REC-xml-20001006, 3.3.1: value in an attribute declared as ENTITY type must match an unparsed entity in the DTD. The attribute value does not refer to an unparsed entity

			kXMLUndeclaredEntityInAttValueErr	REC-xml-20001006, 3.3.1: REC-xml-20001006, 3.3.1: value in an attribute declared as ENTITY type must match an unparsed entity in the DTD. An undeclared entity was found

			kXMLUndeclaredNotationInAttValueErr	REC-xml-20001006, 3.3.1: the value of NOTATION attribute must match a declared notation. An undeclared notation was found in an attribute value

			kXMLAttValueNotInEnumErr			REC-xml-20001006, 3.3.1: values of enumerated type must match one of the nmtokens in the declaration. The attribute value does not match one of the values in the enumeration list

			kXMLDuplicateIDAttValueErr			REC-xml-20001006, 3.3.1: an ID name must not appear more than once in a XML document as a value of ID type. Another element was found to have ID attribute type with the same value

			kXMLFixedAttributeDefaultErr		REC-xml-20001006, 3.3.2: if attribute default value declaration is #FIXED, the attribute value must be the same as declared default value. The attribute value is not the same as declared default value

			kXMLIDNotFoundErr					REC-xml-20001006, 3.3.1: value of IDREF must match some ID attribute. The ID referred to by the attribute value was not found

			kXMLNoContentModelErr				no content model found in the DTD. Possibly empty DTD
		*/

		/** constructor
			@param errCode error code
			@xmlReference XMLReference of the element the error occurred at
			@attName attribute name the error occurred at, if applicable
		*/
		XMLDTDValidationError(ErrorCode errCode, const XMLReference& xmlReference, const PMString& attName = PMString());

		/** copy constructor */
		XMLDTDValidationError(const XMLDTDValidationError& src);

		/** destructor */
		virtual ~XMLDTDValidationError();

		bool operator==(const XMLDTDValidationError&) const { ASSERT_FAIL("appease K2Vector.Location"); return false; }

		/** operator= required for vector of this class to work properly in erase() */
		XMLDTDValidationError& operator=(const XMLDTDValidationError& src);

		/** get the error code
			@return ErrorCode XML DTD validation error code
		*/
		ErrorCode GetErrorCode(void) const;

		/** get the XMLReference of the error element
			@return XMLReference the element where the error occurred
			@see XMLReference
		*/
		const XMLReference& GetXMLReference(void) const;

		/** if applicable, this method returns the name of the attribute for element, returned in
			GetXMLReference, which the error occurred at. If empty, then the error is not at an
			attribute
			@return PMString attribute name the error occurred at
		*/
		const PMString& GetAttributeName(void) const;

		/** get the list of suggestions
			@return K2Vector<XMLDTDValidateSuggest*> list of suggestions
			@see XMLDTDValidateSuggest
		*/
		const K2Vector<XMLDTDValidateSuggest*>& GetSuggestions(void) const;

		/** add a suggestion to this error
			@param suggestion suggestion to add. This owns the object
			@see XMLDTDValidateSuggest
		*/
		void AddSuggestion(XMLDTDValidateSuggest *suggestion);

	private:
		ErrorCode fErrCode;
		XMLReference fXMLRef;
		PMString fAttName;
		K2Vector<XMLDTDValidateSuggest*> fSuggestions;
};

DECLARE_OBJECT_TYPE(XMLDTDValidationError);


#endif // __XMLDTDValidationError__

