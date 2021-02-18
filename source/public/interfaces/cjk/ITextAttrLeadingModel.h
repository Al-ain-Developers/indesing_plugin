//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ITextAttrLeadingModel.h $
//  
//  Owner: nmccully
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
#ifndef __ITextAttrLeadingModel__
#define __ITextAttrLeadingModel__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "IMojikumiStyle.h"
#include "CTextEnum.h"
#include "TextAttrID.h"


/** Interface for a text attribute whose value is the LeadingModel (how line leading is measured and how it results in line placement).
	@see Text::LeadingModel
	@ingroup text_attr
*/
class ITextAttrLeadingModel : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILEADINGMODEL };

		typedef Text::LeadingModel		ValueType;

		/** */
		ValueType Get() const { return GetLeadingModel(); }
		/** */
		void Set(ValueType val) { SetLeadingModel(val); }

		/** */
		virtual void SetLeadingModel(Text::LeadingModel dq) = 0;
		/** */
		virtual Text::LeadingModel GetLeadingModel() const = 0;
};

#endif
