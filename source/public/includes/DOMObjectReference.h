//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DOMObjectReference.h $
//  
//  Owner: Steve Pellegrin
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
#ifndef __DOMObjectReference_h__
#define __DOMObjectReference_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 


#include "K2Vector.h"

class WideString;
class IDOMElement;

/** This is a helper class for DOMAttributeValue. It encapsulates information
	about an inter-object reference in INX.
	A reference consists of:
	1. A key that represents the element being referenced.
	2. A pointer to the referenced element.
	3. The position of this reference in its associated ReferenceList.
		Note: Values can contain lists of other values. A reference's position
		value is determined after the hierarchy is flattened.
	@author Steve Pellegrin
	@see DOMAttributeValue
*/
class PUBLIC_DECL DOMObjectReference
{
public:
	typedef object_type data_type;

public:
	/** Constructs an empty reference
	*/
	DOMObjectReference();
	/** Constructs an unresolved reference.
		@param key IN the key that identifies the object being referenced.
		@param position IN the reference's position in its list.
	*/
	DOMObjectReference(const WideString & key, uint32 position);
	/** Constructs a resolved reference.
		@param key IN the key that identifies the object being referenced.
		@param element IN the referenced element.
	*/
	DOMObjectReference(const WideString & key, IDOMElement *element);
	/** Constructs a reference that is a copy of another
		@param other IN the reference to copy.
	*/
	DOMObjectReference(const DOMObjectReference &other);
	/** Destructor
	*/
	~DOMObjectReference();

	/** Get the reference's key
		@return The key.
	*/
	const WideString &GetKey() const;

	/** Get the reference's position
		@return The position.
	*/
	uint32 GetPosition() const;

	/** Get the reference's element
		@return The element (may be nil)
	*/
	IDOMElement *QueryElement() const;

	/** Determine whether the reference is resolved.
		@return kTrue if resolved, kFalse if not.
	*/
	bool16 IsResolved() const;

	/** Sets the reference's element.
		@param element IN The element.
	*/
	void SetElement(IDOMElement *element);

	/** Tests the reference for equality with another.
		@param other IN Another reference.
	*/
	bool16 operator==(const DOMObjectReference &other) const;

	/** Assign the value of another reference to this one.
		@param other IN Another reference.
	*/
	DOMObjectReference &operator=(const DOMObjectReference &other);

private:
	void Copy(const DOMObjectReference &other);

private:
	WideString					fKey;
	uint32						fPosition;
	InterfacePtr<IDOMElement>	fElement;
};

typedef K2Vector<DOMObjectReference>			DOMObjectReferenceList;

#endif	// __DOMObjectReference_h__
