//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemNameFacade.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _IPageItemNameFacade_
	#define _IPageItemNameFacade_

#include "GenericID.h"

/**
 	Facade to get/set page item names.
  
*/
namespace Facade
{
	class IPageItemNameFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGEITEMNAMEFACADE };


		/**	Get the current name for the page item assigned by the user. Will return empty string if no name has been assigned.
			@param targetItem - the page item in question
			@return PMString - the name for the page item
		 */
		virtual PMString GetUserAssignedPageItemName(const UIDRef& targetItem) const = 0;

		/**	Get the default name for the page item. 
			@param targetItem - the page item in question
			@return PMString - the default name for the page item
		 */
		virtual PMString GetDefaultPageItemName(const UIDRef& targetItem) const = 0;

		/**	Set the current name for the page item. Setting a name to an empty string will result in the default name being used.
			@param targetItem - the page item in question
			@param newName - the new name for the page item
		 */
		virtual ErrorCode SetUserAssignedPageItemName(const UIDRef& targetItem, const PMString& newName) = 0;

		/**	Determine if this page item supports custom names.
			@return bool16 - whether this page item supports custom names
		 */
		virtual bool16 IsPageItemNameUserAssignable(const UIDRef& targetItem) const = 0;
	};
}
#endif // _IPageItemNameFacade_