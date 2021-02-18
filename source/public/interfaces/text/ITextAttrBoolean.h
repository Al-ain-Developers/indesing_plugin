//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrBoolean.h $
//  
//  Owner: eric_kenninga
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
 #ifndef __ITextAttrBoolean__
 #define __ITextAttrBoolean__

#include "IPMUnknown.h"
#include "TextAttrID.h"

/** 
	A boolean text attribute
	@ingroup text_attr
*/
class ITextAttrBoolean : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRBOOLEAN };
		
		typedef bool16		ValueType;

		/**
			Sets the boolean to the param passed in
			@param flag		bool16
		*/
		void Set(ValueType flag)
			{ SetFlag(flag); }
		/**
			Gets the boolean
			@return 	bool16
		*/
		ValueType Get() const
			{ return GetFlag(); }

		/**
			Sets the boolean to the param passed in
			@param flag		bool16
		*/
		virtual void SetFlag(bool16 flag) = 0;
		/**
			Gets the boolean
			@return 	bool16
		*/
		virtual bool16 GetFlag() const = 0;
};

#endif		// __ITextAttrBoolean__
