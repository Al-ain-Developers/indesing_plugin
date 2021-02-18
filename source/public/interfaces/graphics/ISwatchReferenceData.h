//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchReferenceData.h $
//  
//  Owner: SusanCL 
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
//  Provides a method for gathering swatch references on an object.
//  
//========================================================================================

#pragma once
#ifndef __ISwatchReferenceData__
#define __ISwatchReferenceData__

#include "ColorSystemID.h"
#include "IPMUnknown.h"

class UIDList;

/**	This interface provides a method for retrieving swatch references by a specific object.
	It should be implemented on the object boss such as text, tables, page items, styles, graphic
	states, etc., that hold swatch references.
	This interface should not be used to get a list of referenced swatches for the entire document. 
*/
class ISwatchReferenceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISWATCHREFERENCEDATA };

	
	/**	Get all the referenced swatches by this object.
		It is the responsibility of the implementation to check the list for a rendering object before adding a new one.
		@param referencedList The list of swatches referenced.
	*/
	virtual void Get (UIDList& referencedList) const = 0;

};

#endif
