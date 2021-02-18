//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVSpinningIconWidgetView.h $
//  
//  Owner: Rahul Jain
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
#ifndef __DVSpinningIconWidgetView__
#define __DVSpinningIconWidgetView__

#include "DVIconSuiteView.h"
#include "DVAForwardDeclarations.h" 
#include <cstdint>

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif


/**
	An icon view shows spinning icon
*/

class PMRsrcID;

class DV_WIDGET_DECL DVSpinningIconWidgetView : public DVIconSuiteView
{
	typedef DVIconSuiteView inherited;
public:
	DVSpinningIconWidgetView(IPMUnknown *boss);
	virtual ~DVSpinningIconWidgetView();

	virtual void	Show(bool16 doShow = kTrue);
	virtual void	Hide();
	virtual void	DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;; 
	virtual void	InstallTimer();
	virtual void	RemoveTimer();

protected:
	virtual bool    DoTimerNotify(std::int32_t timer_id);
	virtual void    DV_NodeChanged(int change);
	
private:
	void	LoadIcon(const RsrcID& iconRsrcID, const PluginID& pluginID);
	int32			GetIconCount();
	PMRsrcID		GetNthIcon(int32 n);
	std::int32_t	fTimerId;
	int32			fCurrentIconIndex;
	bool16			fTimerInstalled;
};

#endif