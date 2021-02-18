//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVGIFPlayerView.h $
//  
//  Owner: Atishay Jain
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2020 Adobe Inc.
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Inc. and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Inc. and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Inc.
//  
//========================================================================================

#pragma once
#ifndef __DVGIFPlayerView__
#define __DVGIFPlayerView__

#include "DVControlView.h"

/*
DVGIFPlayerView is Wrapper over UI_GIFPlayer.
Added to create and manage view for GIF workflows in the application.
For More details see DVControlView in DVControlView.h
Sample Usage:
InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
std::string path = "~/eglite.gif";
PMString gifPath(path.c_str());
ControlView*  gifView = iPanelControlData->FindWidget(kGIFPlayerWidgetID);
DVGIFPlayerView* view = dynamic_cast<DVGIFPlayerView*>(gifView);
view->SetGIFPath(gifPath);

*/
class DV_WIDGET_DECL DVGIFPlayerView : public DVControlView
{
	typedef DVControlView inherited;
public:
    /** 
        Instantiates and create DVA control for GIF View
   	*/
	DVGIFPlayerView(IPMUnknown *boss);
    /**
        cleanup
    */
	virtual ~DVGIFPlayerView();
    /** 
        Called after this widget is created. Can be
        overriden to do initialization that may need to perform.
   	*/
    virtual void DoPostCreate();
    /** 
        Create GIF view with appropriage underlined DVA control nodes
   	*/
    virtual void							CreateDVAControl();
    /** 
        Flush and again Create DVA Controls with CreateDVAControl
   	*/
    virtual void                            ReCreateDVAControlWithGIFPlayer();
    /**
        Get GIF Path 
    */
    virtual PMString                      GetGIFPath();
    /**
        Set GIF Path with PMString
    */
    virtual void                      SetGIFPath(PMString path);
    /**
        Set This UI widet as active like SetActiveWindow <Win>
    */
    virtual void                      Activate();
protected:
    /**
        Associate DVA node with an empty view
    */
	virtual void							ResetWithDummyDVAControl();
	class ID_GIFView_Impl; 
};

#pragma export off

#endif
