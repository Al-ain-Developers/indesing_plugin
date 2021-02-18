//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLAttributeReference.h $
//  
//  Owner: Daniel Guenther
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __XMLATTRIBUTEREFERENCE__
#define __XMLATTRIBUTEREFERENCE__

#include "IPMUnknown.h"
#include "PMString.h"
#include "XMLReference.h"

/** Wrapper class; for instance, used in IXMLNodeSelectionSuite methods.
*/
class XMLAttributeReference
{
	public:
   		/** Specialised copy semantics for K2Vector, not plain old data type; 
			we should define copy constructor and assignment operator for this class. */
		typedef object_type data_type;

		/**	Constructor
			@param ref specifies object this attribute is associated with
			@param attr names the attribute of interest
		 */
		XMLAttributeReference(const XMLReference& ref, const PMString& attr) :
			fXMLReference(ref), fAttrString(attr)	
			{}

		/**	Constructor
			@param ref specifies object this attribute is associated with
		 */
		XMLAttributeReference(const XMLReference& ref) :
			fXMLReference(ref), fAttrString(PMString())	
			{}

		/**	Copy constructor
			@param node specifies node in logical structure whose XMLReference is to be encapsulated
		 */
	
			XMLAttributeReference(const XMLAttributeReference& node) :
			fXMLReference(node.GetXMLReference()),
			fAttrString(node.GetAttributeString())
			{}

		/** Needed for use in sorted lists.
			@param other - Indicates the object to compare myself to.
		*/
		bool16 operator<(const XMLAttributeReference &other) const
		{ 
			// If the element UID and logical ID is the same... 
			return fXMLReference.GetUID() == other.fXMLReference.GetUID() && fXMLReference.GetLogicalID() == other.fXMLReference.GetLogicalID() ? 
				// ...compare the strings...
				fAttrString < other.fAttrString : 
				// ...otherwise if the UIDs are the same...
				fXMLReference.GetUID() == other.fXMLReference.GetUID() ?
					// ...compare the logical IDs compare the UIDs
					fXMLReference.GetLogicalID() < other.fXMLReference.GetLogicalID() :
					// ...otherwise compare the UIDs
					fXMLReference.GetUID() < other.fXMLReference.GetUID();
			}

		/**	Accessor for encapsulated XMLReference
			@return encapsulated reference
		 */
		const XMLReference& GetXMLReference() const
			{ return fXMLReference; }

		/**	Accessor for attribute name
			@return attribute name
		 */
		const PMString& GetAttributeString() const
			{ return fAttrString; }		

// Don't remove these next two. Even though we are just POD (plain old data) and
// seem unnecessary (and slow). Otherwise Metrowerks will generate horrendous code 
// for the operator! and operator void* below. Yuck.

		/**	Equality operator
			@param other comparand
			@return kTrue if this and comparand are equal by member-wise comparisons, kFalse otherwise 
		 */
 		bool16 operator==(const XMLAttributeReference& other) const
		 	{ return fAttrString == other.fAttrString && fXMLReference == other.fXMLReference; }

		/**	Inequality operator
			@param other comparand
			@return kTrue if this and comparand are not equal by member-wise comparisons, kFalse otherwise
		 */
		bool16 operator!=(const XMLAttributeReference& other) const
		 	{ return ((fAttrString != other.fAttrString) || (fXMLReference != other.fXMLReference)); }

private:
	XMLReference fXMLReference;
	PMString fAttrString;
};

DECLARE_OBJECT_TYPE(XMLAttributeReference);

#endif // __XMLATTRIBUTEREFERENCE__
