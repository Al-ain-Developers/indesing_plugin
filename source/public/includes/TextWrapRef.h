//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextWrapRef.h $
//  
//  Owner: dwaterfa
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
#ifndef __TextWrapRef__
#define __TextWrapRef__

#include "IPMUnknown.h"
#include "K2Vector.h"


/**
	This data structure encapsulates information about a reference to a
	boss with an active StandOffData. The X/YOffset represents the adjustment
	in pasteboard coordinates from where the SOD is located to where it
	appears to the Parcel. Only TextWrap which is from MasterPages will have
	non-zero X/YOffsets.

	@ingroup text_story
*/
struct TextWrapRef
{
	TextWrapRef() { }

	TextWrapRef(const TextWrapRef& other) :
		fSODUID(other.fSODUID),
		fSpreadUID(other.fSpreadUID),
		fTransform(other.fTransform)
		{ }

	TextWrapRef(UID sodUID,
				UID spreadUID,
				const PMMatrix& transform) :
		fSODUID(sodUID),
		fSpreadUID(spreadUID),
		fTransform(transform)
		{ }

				// vvv Compiler issue, wants to be const IStandOffData
	TextWrapRef(const IPMUnknown* sod) :
		fSODUID(::GetUID(sod)),
		fSpreadUID(kInvalidUID)	// NATIVE
		{ }
		
	typedef object_type	data_type;

	UID					fSODUID;
	UID					fSpreadUID;
	PMMatrix			fTransform;

	inline bool16 operator==(const TextWrapRef& other) const
		{
		return ((fSODUID == other.fSODUID) && (fSpreadUID == other.fSpreadUID) && (fTransform == other.fTransform));
		}

	inline bool16 operator!=(const TextWrapRef& other) const
		{
		return !(*this == other);
		}

	inline bool16	GetIsNative() const
		{ return (fSpreadUID == kInvalidUID); }

};

typedef K2Vector<TextWrapRef>	TextWrapRefList;


#endif	// __TextWrapRef__

