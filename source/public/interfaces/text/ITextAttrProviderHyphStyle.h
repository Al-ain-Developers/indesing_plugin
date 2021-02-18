//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrProviderHyphStyle.h $
//  
//  Owner: Amish Kumar Bedi	
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ITextAttrProviderHyphStyle__
#define __ITextAttrProviderHyphStyle__

#include "IHyphenationStyle.h"
#include "TextAttrID.h"


/** 
	ITextAttrProviderHyphStyle is a simple data interface that is used to hold the
	desired provider hyphenation style mode which influences the hyphenation points for the same provider:
	IHyphenationStyle::kHyph_All, IHyphenationStyle::kHyph_AllButUnaesthetic,
	IHyphenationStyle::kHyph_Aesthetic, IHyphenationStyle::kHyph_PreferredAesthetic.
	@ingroup text_attr
*/
class ITextAttrProviderHyphStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRPROVIDERHYPHSTYLE };
		
		typedef IHyphenationStyle::ProviderHyphenationStyle	ValueType;

		/**
		Set the value
		@param phs specifies the provider hyphenation style
		*/
		void Set(ValueType phs)
			{ SetProviderHyphStyle(phs); }

		/**
		Get the value
		@return the provider hyphenation style
		*/
		ValueType Get() const
			{ return GetProviderHyphStyle(); }

		/**
		Set the value
		@param providerHyphStyle specifies the provider hyphenation style
		*/
		virtual void SetProviderHyphStyle(ValueType providerHyphStyle) = 0;

		/**
		Get the value
		@return the provider hyphenation style
		*/
		virtual ValueType GetProviderHyphStyle() const = 0;

};

#endif
