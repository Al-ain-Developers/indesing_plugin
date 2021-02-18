//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrFont.h $
//  
//  Owner: ekenning
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
#ifndef __ITextAttrFont__
#define __ITextAttrFont__

#include "IPMUnknown.h"
#include "TextAttrID.h"

class PMString;


/** This is an attribute for the font style.
	@ingroup text_attr
*/
class ITextAttrFont : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRFONT };

		typedef bool16		ValueType;

		/**
			Get the font style name. Also called font face
		
			@return	font style name
		*/
		virtual const PMString& GetFontName() const = 0;
		/**
			Set the font style name. Also called font face
		
			@param	ss			font style name to set
			@param	clearMM		if kTrue multiple master style are cleared.
		*/
		virtual void SetFontName(const PMString& ss, bool16 clearMM = kTrue) = 0;

		/**
			Set multiple master axes. For a general description of multiple master fonts
			axes see http://partners.adobe.com/asn/tech/type/mmfonts.jsp . If you want
			to set this you can use the value from either IPMFont::GetNumDesignAxes() and
			IPMFont AccessDesignVector or FontGroupIteratorCallBack::OnMMAxes 
		
			@param	num		number of axes
			@param	buffer	buffer with axes
		*/
		virtual void SetMMAxes(int32 num, const Fixed* buffer) = 0;
		/**
			Get number multiple master axes
		
			@return	number of axes
		*/
		virtual int32 GetNumMMAxes() const = 0;
		/**
			Get multiple master axes
		
			@return	Fixed*
		*/
		virtual const Fixed* GetMMAxes() const = 0;
		/**
			Setting inherit axis info to kTrue means that when applying
			this attribute the existing axis info in the text runs will be inherited.
			Make sure that if you call SetInheritAxisInfo with kTrue you do
			not call SetMMAxes. You cannot inherit and set at the same time.
		
			@param	inherit
		*/
		virtual void	SetInheritAxis(bool16 inherit) = 0;
		/**
			Get Inherit Axis
		
			@return	kTrue if inherit axis is set true
		*/
		virtual bool16	GetInheritAxis() const = 0;
};

#endif
