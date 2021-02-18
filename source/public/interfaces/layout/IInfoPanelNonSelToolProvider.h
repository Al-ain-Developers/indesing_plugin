//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IInfoPanelNonSelToolProvider.h $
//  
//  Owner: Yeming Liu
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
//  Purpose:	This interface is used in panels registered with kInfoWidgetService and 
//  associated with non-selection tool.
//  
//========================================================================================

#pragma once
#ifndef __IINFOPANELNONSELTOOLPROVIDER__
#define __IINFOPANELNONSELTOOLPROVIDER__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "ToolInfo.h"

// ----- ID.h files -----

#include "InfoPanelID.h"

/**
   Provides a mechanism for info palette to determine showing/hiding which panel 
   when non-selection tool is activated. Currently the non-selection tool includes 
   all tools existing in InDesign except pointer tool and direct selection tool. 
   For all non-selection tool, there is only one panel associated with it. 
   And different non-selection tool can have the same panel. 
*/
class IInfoPanelNonSelToolProvider : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINFOPANELNONSELTOOLPROVIDER };

		/**
		   Get the ClassID of the tool that this panel associated with.

		   @return ClassID of tool.
		*/
		virtual ClassID GetToolType() const = 0;

		/**
		   Get the panel's widget id that the tool is associated with.

           @return WidgetID of the panel.
		*/
		virtual WidgetID GetWidgetID() const = 0;

		/**
		   Get the message id that will be sent to InfoPanel if the associated tool 
		   is the current activated tool

	       @return InterfaceID of the message.
		*/
		virtual PMIID    GetProtocolID() const = 0;

		/**
		   Get the priority to display the panel for the current activated tool. 
		   This is designed for third party to override the existing panel that 
		   associated with the tool.

           @return ToolInfoPriority of the panel.
		*/
		virtual ToolInfoPriority GetPriority() const = 0;
};

#endif //__IINFOPANELNONSELTOOLPROVIDER__