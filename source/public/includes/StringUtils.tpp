//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StringUtils.tpp $
//  
//  Owner: Mat Marcus and Jesse Jones
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

#ifndef __StringUtilsTPP__
#define __StringUtilsTPP__

#include "StringUtils.h"

namespace StringUtils
{
//	template<> PUBLIC_DECL back_insert_iterator<PMString>& back_insert_iterator<PMString>::operator=(UTF32TextChar val);
//	template<> PUBLIC_DECL back_insert_iterator<WideString>& back_insert_iterator<WideString>::operator=(UTF32TextChar val);

	// Specialization for PMString
	template<>
		back_insert_iterator<PMString>& back_insert_iterator<PMString>::operator=(UTF32TextChar val)
	{
		// Push value into container
		// No need to grow capacity here; now it is handled in UniCodeSavvyString
		fContainer.AppendW(val);
		return (*this);
	}

	// Specialization for WideString
	template<>
		back_insert_iterator<WideString>& back_insert_iterator<WideString>::operator=(UTF32TextChar val)
	{
		// Push value into container
		// No need to grow capacity here; now it is handled in UniCodeSavvyString
		fContainer.Append(val);
		return (*this);
	}

}
#endif 

