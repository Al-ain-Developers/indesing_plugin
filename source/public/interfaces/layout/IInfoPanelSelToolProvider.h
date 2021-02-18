//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IInfoPanelSelToolProvider.h $
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
//  associated with selection tool.
//  
//========================================================================================

#pragma once
#ifndef __IINFOPANELSELTOOLPROVIDER__
#define __IINFOPANELSELTOOLPROVIDER__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "ToolInfo.h"

// ----- ID.h files -----

#include "InfoPanelID.h"

/**
   Provides a mechanism for info palette to determine showing/hiding which panel 
   when selection tool is activated. Currently the selection tool only includes 
   pointer tool and direct selection tool. A selection tool will have two panels 
   associated with it. When there is layout selection, the panel with the selection 
   information will be shown; when there is no layout selection, the other panel with 
   other information will be shown.
*/
class IInfoPanelSelToolProvider : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINFOPANELSELTOOLPROVIDER };

		/**
		   Get the ClassID of the tool that this panel associated with.

		   @return ClassID of tool.
		*/
		virtual ClassID GetToolType() const = 0;

		/**
		   Get the panel's widget id that the tool is associated with when there is a selection.

           @return WidgetID of the panel.
		*/
		virtual WidgetID GetSelectionWidgetID() const = 0;

		/**
		   Get the panel's widget id that the tool is associated with when there is no selection.

           @return WidgetID of the panel.
		*/
		virtual WidgetID GetNonSelectionWidgetID() const = 0;
	
		/**
		   Get the message id that will be sent to InfoPanel if the associated tool 
		   is the current activated tool and there is a selection.

	       @return InterfaceID of the message.
		*/
		virtual PMIID    GetSelectionProtocolID() const = 0;

		/**
		   Get the message id that will be sent to InfoPanel if the associated tool 
		   is the current activated tool and there is no selection.

	       @return InterfaceID of the message.
		*/
		virtual PMIID    GetNonSelectionProtocolID() const = 0;

		/**
		   Get the priority to display the panel for the current activated tool. 
		   This is designed for third party to override the existing panel that 
		   associated with the tool when there is selection.

           @return ToolInfoPriority of the panel.
		*/
		virtual ToolInfoPriority GetSelectionPriority() const = 0;

		/**
		   Get the priority to display the panel for the current activated tool. 
		   This is designed for third party to override the existing panel that 
		   associated with the tool when there no selection.

           @return ToolInfoPriority of the panel.
		*/
		virtual ToolInfoPriority GetNonSelectionPriority() const = 0;
};

#endif //__IINFOPANELSELTOOLPROVIDER__