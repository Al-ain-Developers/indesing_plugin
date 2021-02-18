//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAutoActivateCmdData.h $
//
//  Owner: nitikban
//
//  $Author: pmbuilder $
//
//  $DateTime: 2020/11/06 13:08:29 $
//
//  $Revision: #2 $
//
//  $Change $
//  ___________________
//
//  ADOBE CONFIDENTIAL
//
//  Copyright 2020 Adobe
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe .
//
//========================================================================================

#pragma once
#ifndef __IAutoActivateCmdData__
#define __IAutoActivateCmdData__

// ----- Includes -----
#include "IPMUnknown.h"

class IAutoActivateCmdData : public IPMUnknown
{
public:
    enum { kDefaultIID = IID_ICOMMANDDATA };
    
    virtual void Set(int32 flag) = 0;
    
    virtual int32 Get() const = 0;
};

#endif
