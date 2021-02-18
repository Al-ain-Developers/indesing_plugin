//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttributes.h $
//  
//  Owner: EricK
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
#ifndef __ITextAttributes__
#define __ITextAttributes__

#include "IPMUnknown.h"
#include "TextID.h"

class AttributeBossList;

/** 
	@ingroup text_attr
*/
class ITextAttributes : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRIBUTES };
	
		virtual int32 CountBosses() const = 0;
		virtual ClassID GetClassN(int32 n) const = 0;
		virtual const IPMUnknown* QueryBossN(int32 n, PMIID id) const = 0;

		virtual const IPMUnknown* QueryByClassID(ClassID c, PMIID prop) const = 0;
		
		virtual void ApplyAttribute(const IPMUnknown *newone, ClassID attrCls = kInvalidClass) = 0;
		virtual void ApplyAttributes(const AttributeBossList *other) = 0;

		virtual void ClearOverride(ClassID id) = 0;
		virtual void ClearOverrides(const AttributeBossList *list) = 0;
		virtual void ClearAllOverrides() = 0;

		virtual const AttributeBossList* GetBossList() const = 0;
};



#endif	//  __ITextAttributes__