//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectStyleAttrInfo.h $
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

#ifndef _IOBJECTSTYLEATTRINFO_
#define _IOBJECTSTYLEATTRINFO_

// ----- Interface files

#include "IPMUnknown.h"

// ----- ID files

#include "GenericID.h"

class PMString;

/** An interface to get object style's attribute information.
*/
class IObjectStyleAttrInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOBJECTSTYLEATTRINFO};
		
		/**	Get the attribute name. Usually subclass should implement this the set it.
			@param name OUT the name of the attribute.
		*/
		virtual void GetAttributeName(PMString& name) = 0;

		/**	Get the category and name which the attribute belongs to.
			@param category OUT the category which this attribute belongs to.
			@param categoryName OUT the name of the category which this attribute belongs to.
		*/
		virtual void GetCategoryInfo(ClassID& category, PMString& categoryName) = 0;
};

#endif // _IOBJECTSTYLEATTRINFO_