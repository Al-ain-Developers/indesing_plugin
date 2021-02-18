//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ToolInfo.h $
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
//========================================================================================

#pragma once
#ifndef __TOOLINFO__
#define __TOOLINFO__

/**
   ToolInfoPriority is used to decide which panel should be loaded if one tool has tool panels. 
   If two panels are defined as the same priority, the first one loaded in runtime will win.
   All InDesign's tool panel are defined as kLowPriority. kNonePriority is just for testing.
*/
typedef enum { kNonePriority = -1, kLowPriority = 0, kMediumPriority, kHighPriority } ToolInfoPriority;

/**
   Helper class for cache non selection tool information. This is primary used for InfoPalette. 
*/
class NonSelectionToolInfo
{
	public:
		typedef object_type data_type;

		/** Default constructor.
		*/
		NonSelectionToolInfo() : fPriority(kNonePriority) {}

		/* Contruct object with given values.
		   @param toolType IN ClassID for tool.
		   @param protocol IN protocol when there is no selection.
		   @param widgetID IN widgetID for the panel when there is no selection.
		   @param priority IN determine which panel should be loaded if one tool has multiple panels associated with. 
		*/
		NonSelectionToolInfo
			(
				const ClassID& toolType,	
				const PMIID& protocol,		
				const WidgetID& widgetID,	
				const ToolInfoPriority priority
			):fToolType(toolType),
			  fProtocol(protocol),
			  fWidgetID(widgetID), 
			  fPriority(priority) { }
	
		/** Equal operator to compare objects.
		    @param other IN the object to be compared with.
			@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const NonSelectionToolInfo& other) const
		{ 
			return ( (fToolType == other.fToolType) && 
				     (fProtocol == other.fProtocol) && 
				     (fWidgetID == other.fWidgetID) && 
					 (fPriority == other.fPriority) ); 
		}

		/**
		   class ID for tool that the panel is associated with
		*/
		ClassID   fToolType;

		/**
		   protocol that the tool is interested in when it is activated
		*/
		PMIID     fProtocol;

		/**
		   widgetID for the panel when this tool is activated
		*/
		WidgetID  fWidgetID;

		/**
		   See the definition of ToolInfoPriority
		*/
		ToolInfoPriority fPriority;
};

/**
   Helper class for cache selection tool information. This is primary used for InfoPalette. 
*/
class SelectionToolInfo
{
	public:
		typedef object_type data_type;

		/** Default constructor.
		*/
		SelectionToolInfo() : fSelectionPriority(kNonePriority), fNonSelectionPriority(kNonePriority) {}

		/** Construct object with given values.
		    @param toolType IN ClassID for tool.
		    @param protocol IN protocol when there is selection.
		    @param widgetID IN widgetID for the panel when there is selection.
		    @param priority IN determine which panel should be loaded if one tool has multiple panels associated with. 
		*/
		SelectionToolInfo
			(
				const ClassID& toolType,				// class ID for tool
				const PMIID& selectionProtocol,			// protocol when there is selection
				const PMIID& nonSelectionProtocol,		// protocol when there is no selection
				const WidgetID& selectionWidgetID,		// widgetID for the panel when there is selection
				const WidgetID& nonSelectionWidgetID,	// widgetID for the panel when there is no selection
				const ToolInfoPriority selectionPriority,	// priority as to display the panel when there is selection
				const ToolInfoPriority nonSelectionPriority // priority as to display the panel when there is no selection
			):fToolType(toolType),
			  fSelectionProtocol(selectionProtocol),
			  fNonSelectionProtocol(nonSelectionProtocol),
			  fSelectionWidgetID(selectionWidgetID),
			  fNonSelectionWidgetID(nonSelectionWidgetID), 
			  fSelectionPriority(selectionPriority),
			  fNonSelectionPriority(nonSelectionPriority) { }
	
		/** Equal operator to compare objects.
		    @param other IN the object to be compared with.
			@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const SelectionToolInfo& other) const
		{ 
			return ( (fToolType == other.fToolType) && 
					 (fSelectionProtocol == other.fSelectionProtocol) &&
				     (fNonSelectionProtocol == other.fNonSelectionProtocol) && 
					 (fSelectionWidgetID == other.fSelectionWidgetID) && 
				     (fNonSelectionWidgetID == other.fNonSelectionWidgetID) && 
					 (fSelectionPriority == other.fSelectionPriority) && 
					 (fNonSelectionPriority == other.fNonSelectionPriority) ); 
		}

		ClassID   fToolType;
		PMIID     fSelectionProtocol;
		PMIID     fNonSelectionProtocol;
		WidgetID  fSelectionWidgetID;
		WidgetID  fNonSelectionWidgetID;
		ToolInfoPriority fSelectionPriority;
		ToolInfoPriority fNonSelectionPriority;
};

#endif //__TOOLINFO__