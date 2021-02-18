//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicMetaDataObject.h $
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
//  Reveiw Date:	9/30/98
//  
//  Purpose:		Common interface for all graphic meta data objects.
//  This interface stores a reference of the meta data object
//  to the rendering object.
//  
//========================================================================================

#pragma once
#ifndef __IGraphicMetaDataObject__
#define __IGraphicMetaDataObject__

#include "GraphicStylesID.h"
#include "IPMUnknown.h"

/**	This interface is obsolete. This is only provided for document phase 2 conversion
	when converting from version 2.x or older documents. 
	All other usages are not supported.
*/
class IGraphicMetaDataObject : public IPMUnknown
{
	public:
		//................................................................................
		//	Data Types
		//................................................................................
		enum { kDefaultIID = IID_IGRAPHICMETADATAOBJECT_OBSOLETE };

public:
	// Get/Set UID of the rendering object
	virtual void SetUID (UID id) = 0;
	virtual UID GetUID () = 0;

	// Indicate whether the rendering object should be global or local
	virtual void SetIsGlobal (bool16 isGlobal) = 0; 
	virtual bool16 GetIsGlobal () = 0; 
	
	//	Called when uidToReplace has changed. The meta data may need to update.
	//	If it does, then it should return a copy of the original meta data, otherwise
	//	return nil
	virtual IPMUnknown* ReplaceMetaData (UID uidToReplace, IPMUnknown *iNewMetaData, ClassID renderingClassID, bool16 dirtyMetaData, IDataBase*) = 0; 
};


#endif
