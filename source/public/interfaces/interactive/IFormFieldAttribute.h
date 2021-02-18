//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IFormFieldAttribute.h $
//  
//  Owner: Tim Wright
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
#ifndef _IFormFieldAttribute_
#define _IFormFieldAttribute_

/** This interface identifies a graphic attribute boss as being
a form field attribute.  For example, this allows a
form field style to include form field attributes, but not graphic attributes.

When a form field style is applied, all the graphic attributes with this interface
are copied over from the style to the applied form field.
*/
class IFormFieldAttribute : public IPMUnknown
{
	enum { kDefaultIID = IID_IFORMFIELDATTRIBUTE };
};
			
#endif //
