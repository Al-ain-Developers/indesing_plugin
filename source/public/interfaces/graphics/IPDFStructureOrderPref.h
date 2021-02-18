//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFStructureOrderPref.h $ 
//   
//  Owner: Sameer Manuja
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//   
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2010 Adobe Systems Incorporated. All Rights Reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//   
//======================================================================================== 

#pragma once
#ifndef __IPDFStructureOrderPref__
#define __IPDFStructureOrderPref__

#include "PDFID.h"

class IPDFStructureOrderPref : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFSTRUCTUREORDERPREF };

		/**
			Enumerates the tagged PDF structure order choices.
		*/
		enum StructureOrder
		{
			/** Use XML structure (and layout based heuristic as a fallback). */
			kXMLStructure = 0,
			/** Use Articles. */
			kArticles
		};

		/**
			This method sets the tagged PDF structure order preference.
			@param StructureOrder order: the structure order preference.
		*/
		virtual void Set(StructureOrder order) = 0;

		/**
			This method gets the tagged PDF structure order preference.
			@return StructureOrder: the structure order preference.
		*/
		virtual StructureOrder Get() const = 0;
};

#endif
