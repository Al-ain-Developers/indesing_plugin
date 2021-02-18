//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IContentMgrAccess.h $
//  
//  Owner: robin briggs
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
//  Purpose of Interface:
//  Provides a single point of access to the content manager for a document.
//  
//========================================================================================

#pragma once
#ifndef __IContentMgrAccess__
#define __IContentMgrAccess__

#include "ShuksanID.h"

class IContentMgr;

/** This interface is used to locate the Content Manager for a particular database.
*/
class IContentMgrAccess : public IPMUnknown {
public:
		enum { kDefaultIID = IID_ICONTENTMGRACCESS };
		
		/** Get document's content manager (by pointer)
		    @return A referenced interface pointer.
		*/
		virtual IContentMgr *QueryContentMgr() = 0;
	
		/** Get document's content manager (by UID)
		    @return The Content Manager's UIDRef.
		*/
		virtual UIDRef GetContentMgr() = 0;

		/** Create and initialize a Content Manager for the specified database
		    @param db IN The database to initialize
		    @return kTrue if successful, kFalse if not
		*/
		virtual bool16 Initialize(IDataBase *db) = 0;	
};


#endif // __IContentMgrAccess__
