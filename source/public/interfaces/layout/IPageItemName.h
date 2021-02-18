//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemName.h $
//  
//  Owner: lance bushore
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IPAGEITEMNAME__
#define __IPAGEITEMNAME__

#include "IPMUnknown.h"
#include "GenericID.h"

class IPageItemName : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPAGEITEMNAME};

		/**	Get the user assigned name of the page item. 
			@return PMString 
		 */
		virtual PMString GetPageItemName() const = 0;

		/**	Get the default name of the page item. 
			@return PMString 
		 */
		virtual PMString GetDefaultNameForObject() const = 0;
		
		/**	Set the user assigned name of the page item. 
			@param newName the new name to assign
		 */
		virtual void SetPageItemName(const PMString& newName) = 0;

		/**	Determine if this page item's name is editable. 
			@return bool16
		 */
		virtual bool16 IsPageItemNameEditable() const = 0;
};

#endif		// __IPAGEITEMNAME__