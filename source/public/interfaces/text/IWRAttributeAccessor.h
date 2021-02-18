//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWRAttributeAccessor.h $
//  
//  Owner: prubini
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
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __IWRAttributeAccessor__
#define __IWRAttributeAccessor__

#include "IPMUnknown.h"
#include "WorldReadyID.h"

class IDrawingStyle;

#ifndef _WRDefines__
typedef int WRInt32;
#endif
#ifndef __WRAttributes__
typedef WRInt32 WRTag;
#endif

class IWRAttributeAccessor : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IWRATTRIBUTEACCESSOR };
	//These functions return kTrue if the linguistic plug-in bringing the language is present (appears in the language list)
	virtual WRTag GetOwnerTag(void) = 0;
	virtual WRInt32 GetAttributeValue(WRTag ownerTag, WRTag attrTag, const IDrawingStyle* drawingStyle, void* data, WRInt32 len) = 0;
};

#endif //__IWRAttributeAccessor__
