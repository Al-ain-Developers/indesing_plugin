//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrStrokeType.h $
//  
//  Owner: Danielle Darling
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
//  Used for the stroke type used for text attributes like underline/strikethrough/paragraph rules
//  
//========================================================================================

#pragma once
#ifndef __ITextAttrStrokeType__
#define __ITextAttrStrokeType__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"



/**
	@ingroup text_attr
*/
class ITextAttrStrokeType : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRSTROKETYPE };


		typedef ICompositionStyle::StrokeType		ValueType;


		void Set(ValueType flag)
			{ SetStrokeTypeData(flag); }
		ValueType Get() const
			{ return GetStrokeTypeData(); }

		/**
			Gets the UID of the Stroke Type
			@return 		UID
		*/
		virtual UID GetUIDData() const = 0;
		/**
			Sets the UID of the Stroke Type
			@param 		UID
		*/
		virtual void SetUIDData(UID uid) = 0;
		/**
			Gets the ClassID of the Stroke Type
			@return 		ClassID
		*/
		virtual ClassID GetClassIDData() const = 0;
		/**
			Sets the ClassID of the Stroke Type
			@param 		ClassID
		*/
		virtual void SetClassIDData(ClassID classID) = 0;

		/**
			Gets the StrokeType (Class with UID and ClassID which identifies the Stroke Type)
			@return 		StrokeType
		*/
		virtual ICompositionStyle::StrokeType GetStrokeTypeData() const = 0;
		/**
			Sets the StrokeType (Class with UID and ClassID which identifies the Stroke Type)
			@param 		StrokeType
		*/
		virtual void SetStrokeTypeData(ICompositionStyle::StrokeType type) = 0;
};

#endif

