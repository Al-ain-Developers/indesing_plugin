//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DOMAttributeValue.h $
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
#ifndef __DOMAttributeValue_h__
#define __DOMAttributeValue_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

#include "ScriptData.h"

class IPMStream;


/** Extends ScriptData to provide additional functionality for working with INX.
    An instance of this class represents the value of a single DOM attribute.
	@author Steve Pellegrin
	@see IDOMElement
*/
class PUBLIC_DECL DOMAttributeValue : public ScriptData
{
public:
	typedef object_type data_type;

public:
	typedef ScriptData::ScriptDataType		AttributeType;

public:
	/** Constructs an empty value
	*/
	DOMAttributeValue();

	/** Constructs a WideString value.
	    @param value IN The string value.
	*/
	DOMAttributeValue(const WideString &value);

	/** Constructs an int32 value.
	    @param value IN The int32 value.
	*/
   	DOMAttributeValue(int32 value);

	/** Constructs a stream value.
	    @param value IN The stream value.
	*/
   	DOMAttributeValue(IPMStream *value);
 
	/** Constructs a value that is a copy of another
		@param other IN the value to copy.
	*/
	DOMAttributeValue(const DOMAttributeValue &other);

	/** Constructs a value that is a copy of a ScriptData.
		Note: if sd is a temporary ScriptData it will be moved in place, eliminating extra copying
	    @param readOnly IN Whether the value is read-only.
		@param sd IN The ScriptData to copy.
		@see ScriptData
	*/
	DOMAttributeValue(bool16 readOnly, ScriptData sd)
	: ScriptData(adobe::move(sd)), fReadOnly(readOnly)
	{
	}
  
	/** Movable constructor - assumes ownership of the remote part
	 */
	DOMAttributeValue(adobe::move_from<DOMAttributeValue> other)
		: ScriptData(adobe::move_from<ScriptData>(other.source)),
		  fReadOnly(adobe::move(other.source.fReadOnly))
	{ }

	/** Destructor
	*/
	virtual ~DOMAttributeValue() {}
 
	/** Determine whether the value is read-only.
	    @return kTrue if this value is read-only, kFalse otherwise.
	*/
	bool16 IsReadOnly() const { return fReadOnly ; }

	/** Sets the value's read-only attribute.
	    @param readOnly IN Whether the value is read-only or not.
	*/
	void SetReadOnly(bool16 readOnly) { fReadOnly = readOnly ; }

	/** Determines whether the value is empty or not.
	    @return kTrue if the value is empty, kFalse otherwise.
	*/
	bool16 IsEmpty() const;

	/** Swaps two DOMAttributeValue objects efficiently.
	*/
	friend inline void swap(DOMAttributeValue &lhs, DOMAttributeValue &rhs)
	{
		swap(static_cast<ScriptData&>(lhs), static_cast<ScriptData&>(rhs));
		std::swap(lhs.fReadOnly, rhs.fReadOnly);
	}

	/** Tests the value for equality with another.
		@param other IN Another value.
	*/
	inline bool16 operator==(const DOMAttributeValue &other) const
	{
		return (*(ScriptData *)this == (ScriptData &)other);
	}

	/** Tests the value for inequality with another.
		@param other IN Another value.
	*/
	inline bool16 operator!=(const DOMAttributeValue &other) const
		{return !(*this == other);}

	/** Operator assignment on a movable type takes the parameter by value and consumes it.
		@param other IN another value
	 */
	inline DOMAttributeValue &operator=(DOMAttributeValue other)
    { swap(*this, other); return *this; }

	/** Assign ScriptData to this one.
		@param other IN ScriptData value. Note that the parameter is passed by value.
	*/
	inline DOMAttributeValue &operator=(ScriptData other)
    { swap(static_cast<ScriptData&>(*this), other); return *this; }
	
private:
	bool16		fReadOnly;
};

#endif	// __DOMAttributeValue_h__
