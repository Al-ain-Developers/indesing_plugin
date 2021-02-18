//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CGraphicAttributeInfo.h $
//  
//  Owner: Yeming Liu
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

#ifndef __CGraphicAttributeInfo__
#define __CGraphicAttributeInfo__

#include "IGraphicAttributeInfo.h"

/**
	This is the default implementation for IGraphicAttributeInfo. In the future, 
	if there are any changes in IGraphicAttributeInfo, it will be less work for 
	client if their implementation derives from this one and likes to take the 
	default behavior.
*/
class PUBLIC_DECL CGraphicAttributeInfo : public CPMUnknown<IGraphicAttributeInfo>
{
	public:
		/** Constructor.
		*/
		CGraphicAttributeInfo(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~CGraphicAttributeInfo(){}

	public:
		virtual PMString*       GetName                         (void) const;

		virtual bool16          IsTextAttribute                 (void) const;
		virtual bool16          IsGraphicAttribute              (void) const;
		virtual bool16          IsTableAttribute                (void) const;
		virtual bool16          IsRequiredGraphicAttr           (void) const;
		virtual bool16          AffectsPageItemGeometry         (void) const;

		virtual bool16          ObservedByGraphicState          (void) const;
		virtual bool16          ObservedByTransparencyAttrSuite (void) const;
		virtual IPMUnknown*     CreateTextAttribute             (void) const;
		virtual IPMUnknown*     CreateTableAttribute            (void) const;

		virtual IPMUnknown*     DuplicateAttribute              (const PMIID& iid) const;

		virtual bool16          IsEqual                         (const IPMUnknown* otherAttr) const;

		virtual ClassID         GetClass                        (void) const;

		virtual PMString        GetValue(const ClassID& attrClass, const IWorkspace* ws) const;

	private:
		int16                   fAttributeKind;
		ClassID                 fClassID; 
		IPMUnknown*             fDataInterface;
};

#endif