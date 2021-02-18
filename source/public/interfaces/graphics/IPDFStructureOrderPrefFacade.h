//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFStructureOrderPrefFacade.h $ 
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
#ifndef __IPDFStructureOrderPrefFacade__
#define __IPDFStructureOrderPrefFacade__

#include "IPDFStructureOrderPref.h"
#include "PDFID.h"

class IDocument; 

namespace Facade
{
	class IPDFStructureOrderPrefFacade : public IPMUnknown
	{
		public:
			enum { kDefaultIID = IID_IPDFSTRUCTUREORDERPREFFACADE };

			/**
				This method sets the tagged PDF structure order preference for the document.
				If document is nil, the app workspace is targeted.
				@param IDocument* doc: the document to set the preference for.
				@param StructureOrder order: the structure order preference.
			*/
			virtual void SetStructureOrder(const IDocument *doc, IPDFStructureOrderPref::StructureOrder order) = 0;

			/**
				This method gets the tagged PDF structure order preference for the document.
				If document is nil, the app workspace is targeted.
				@param IDocument* doc: the document to get the preference for.
				@return StructureOrder: the structure order preference.
			*/
			virtual IPDFStructureOrderPref::StructureOrder GetStructureOrder(const IDocument *doc) const = 0;
	};
} // namespace Facade

#endif
