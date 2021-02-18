//========================================================================================
//  
//  File: IWRExtensionAttributeList.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWREXTENSIONATTRIBUTELIST__
#define __IWREXTENSIONATTRIBUTELIST__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRAttributes.h"


#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// interface to generic attribute lists
/** 
Attribute lists are lists of free format data chunks, which can be attach to other objects and retrieved with a identifier selector.
This interface is used to access those lists.
They're currently used to store module private data related to individual fonts and shaping context data related to segments.
Selector are WRTags and are defined in the WRAttribute.h header
**/

typedef void (*DeleteAttributeCB)(WRTag,void*);

class WRSERVICES_DECL IWRExtensionAttributeList : public WRClass
{
public:
	virtual ~IWRExtensionAttributeList();
	virtual void* Get(WRTag t, DeleteAttributeCB del = NULL) const = 0;		///< get the value associated with a selector, or NULL if not found
	virtual void* Set(WRTag t, void* d, DeleteAttributeCB del = NULL) = 0;	///< add or change the value associated with a selector
	virtual bool Exists(WRTag t, DeleteAttributeCB del = NULL) const = 0;		///< return true if a given selector exists
};

#endif
