//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStrokerUIUtils.h $
//  
//  Owner: Lonnie Millett
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPathStrokerUIUtils__
#define __IPathStrokerUIUtils__

#include "GraphicPanelsID.h"
#include "Utils.h"

class IPathStrokerList;
class IDialog;

class IPathStrokerUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKERUIUTILS };

	/** 
	 Queries active IPathStrokerList

	 @return AddRef'd pointer to path stroker list interface, or nil
	 */
	virtual IPathStrokerList *QueryActivePathStrokerList() const = 0;

	/**
	 Creates instance of the Stroke Editor Dialog for Add

	 @return addref'd dialog instance. Caller is responsible for releasing
	 */
	virtual IDialog *CreateStrokeEditorAddDialog() const = 0;

	/**
	 Creates instance of the Stroke Editor Dialog for Edit

	 @return addref'd dialog instance. Caller is responsible for releasing
	 */
	virtual IDialog *CreateStrokeEditorEditDialog() const = 0;

};

#endif
