//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDocFileType.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __DocFileType__
#define __DocFileType__

#include "IPMUnknown.h"
#include "FileTypeRegistry.h"
#include "DocFrameworkID.h"


/** 
	Interface for getting and setting the doc file type
*/
class IDocFileType : public IPMUnknown
{
	public:
		//----------------------------------------------------------------------------------------
		//	Enumerations
		//----------------------------------------------------------------------------------------

		enum { kDefaultIID = IID_IDOCFILETYPE };

		/** Set the doc file type
			@param id		the FileTypeInfoID
		*/
		virtual void SetDocFileType(FileTypeInfoID id) = 0;
		/** Get the doc's FileTypeInfoID
			@return the doc's FileTypeInfoID  
		*/
		virtual FileTypeInfoID GetDocFileType() const = 0;

};

#endif	// __DocFileType__