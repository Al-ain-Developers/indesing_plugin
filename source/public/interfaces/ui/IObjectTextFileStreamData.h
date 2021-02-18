//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IObjectTextFileStreamData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IObjectTextFileStreamData__
#define __IObjectTextFileStreamData__

#include "ShuksanID.h"

/** Interface used to associate a database with a write stream, used only by the panel editor.

		@see StreamUtil, IResourceStreamData
*/
class IObjectTextFileStreamData : public IPMUnknown
{
	public:
		/** Set the associated database */
		virtual void Set(IDataBase* db) = 0;
		/** Get the associated database */
		virtual IDataBase* GetDataBase() const = 0;
};


#endif // IObjectTextFileStreamData
