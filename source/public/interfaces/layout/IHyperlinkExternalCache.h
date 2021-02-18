//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkExternalCache.h $
//  
//  Owner: Kaustubh Bansal
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
//  Copyright 2016 Adobe Systems Incorporated
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

#ifndef __IHyperlinkExternalCache_h__
#define __IHyperlinkExternalCache_h__

// ----- Interfaces -----
#include "IPMUnknown.h"
#include "IHyperlink.h"
#include "ILayoutUIUtils.h"

// ----- ID.h files -----
#include "HyperlinkPanelID.h"

class IHyperlinkExternalCache : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IHYPERLINKEXTERNALCACHE};

	virtual bool16 UpdateCache(UID hyperlink, bool16 keepDocumentOpen = kFalse) = 0;
	virtual bool16 GetFromCache(UID hyperlink, PMString &info, ILayoutUIUtils::DestinationSelectionType &destinationType, bool16 keepDocumentOpen = kFalse) = 0;
	virtual bool16 GetDestUIDFromCache(UID hyperlinkUID, UID &destUID, bool keepDocumentOpen = kFalse) = 0;
	virtual void ClearAll() = 0;
	virtual void CloseAllOpenedDocs() = 0;
};

#endif


