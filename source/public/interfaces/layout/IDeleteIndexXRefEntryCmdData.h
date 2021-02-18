//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDeleteIndexXRefEntryCmdData.h $
//  
//  Owner: Michel Hutinel
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
//  Purpose: Interface data for deleting an Index XRef Entry
//  
//========================================================================================

#pragma once
#ifndef __IDeleteIndexXRefEntryCmdData__
#define __IDeleteIndexXRefEntryCmdData__

#include "IPMUnknown.h"
#include "IndexingID.h"

/** Command data interface used for deleting an index cross-reference entry.
	@ingroup layout_index
*/
class IDeleteIndexXRefEntryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDELETEINDEXXREFENTRYCMDDATA };

		/**	Retrieves the "notify" flag.
			@return the value of the flag.
		 */
		virtual bool16	GetDoNotifyFlag() const = 0;

		/**	Sets the "notify" flag.
			@param notify [IN] - value of the flag.
		 */
		virtual void	SetDoNotifyFlag(bool16 notify) = 0;
};

#endif	// __IDeleteIndexXRefEntryCmdData__