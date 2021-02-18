//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAutoActivateFontPref.h $
//
//  Owner:
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

#include "IPMUnknown.h"
#include "FontUsageDialogID.h"

class IAutoActivateFontPref : public IPMUnknown
{
public:
    enum { kDefaultIID =  IID_IAUTOACTIVATEFONTPREFS};
    
    virtual const bool16 GetAutoActivatePref() = 0;
    virtual void SetAutoActivatePref(const bool16 ) = 0;
    virtual const bool16 GetAutoActivateShowDialog() = 0;
    virtual void SetAutoActivateShowDialog(const bool16 showDialog) = 0;
    virtual const bool16 GetThresholdShowDialog() = 0;
    virtual void SetThresholdShowDialog(const bool16 showDialog) = 0;
};


