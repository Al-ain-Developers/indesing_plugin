//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPMRsrcIDListData.h $
//  
//  Owner: Rahul Jain
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2013 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once 
#ifndef __IPMRSRCIDLISTDATA_h__ 
#define __IPMRSRCIDLISTDATA_h__ 

#include "IPMUnknown.h" 

#include "widgetid.h"

//======================================================================================== 
// CLASS IPMRsrcIDListData 
/** Contains a list of PMRsrcId, usually a list of icon resources
*/ 
//======================================================================================== 

class IPMRsrcIDListData : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IPMRSRCIDLISTDATA };    // for UseDefaultIID() 

	/** Use to add a new resource id
        @param k - the new resource id to be added 
    */ 
    virtual void Append(PMRsrcID k) = 0; 
     
    /** Get the nth resource id
        @param n - the integer you want (must be less than Length - 1) 
        @return - the resource id you requested. (if you request a value that is out of range behavior is undefined) 
    */ 
    virtual PMRsrcID Get(int32 n) = 0; 

    /** Get the number of resource ids currently stored 
        @return - The number of resource id 
    */ 
    virtual uint32 Length() = 0; 

    /** remove all the entries in the array 
    */ 
    virtual void Clear() = 0; 
};

#endif