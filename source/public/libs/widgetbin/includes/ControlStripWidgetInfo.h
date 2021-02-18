//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/ControlStripWidgetInfo.h $
//  
//  Owner: Paul Sorrick
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
//  Purpose:	Defines classes used in Control Strip.
//  
//========================================================================================

#pragma once
#ifndef __CONTROLSTRIPWIDGETINFO__
#define __CONTROLSTRIPWIDGETINFO__


class ControlStripWidgetInfo
{
	public:
		typedef object_type data_type;

		ControlStripWidgetInfo() {}

		ControlStripWidgetInfo
			(
				const RsrcID& rsrcID,		// RsrcID of resource widget to create via CreateObject (kViewRsrcType)
				const PluginID& pluginID,	// PluginID where this resource lives
				const PMReal& priority,		// Priority for position along Control Strip. 0 is at left, increasing to right.
				const PMString& name,		// Name of this control set, used for a menu item for controlling which sets are visible.
				const PMString& menuName,	// Name of the menu item that controls visibility of this control set. Usually same as name, could be different if two control sets map to same menu entry
				const PMString& categoryName,	// Name of the category this menu item goes into
				const PMReal& categoryOrder		// Category order of this control set, used for grouping the menu items. See ControlStripDefs.h
			) :
			  fRsrcID(rsrcID),
			  fPluginID(pluginID),
			  fPriority(priority),
			  fName(name),
			  fMenuName(menuName),
			  fCategoryName(categoryName),
			  fCategoryOrder(categoryOrder) { }
	
		bool16 operator==(const ControlStripWidgetInfo& other) const
		{ 
			// For comparison purposes, don't worry about priority, category and actionID. Name is what matters.
			return ( (fRsrcID == other.fRsrcID) && (fPluginID == other.fPluginID) && (fName == other.fName) /* (fPriority == other.fPriority) && (fCategoryName == other.fCategoryName) && (fCategoryOrder == other.fCategoryOrder) */ );
		}

		RsrcID		fRsrcID;	// RsrcID of resource widget to create via CreateObject (kViewRsrcType)
		PluginID	fPluginID;	// PluginID where this resource lives
		PMReal		fPriority;	// Priority for position along Control Strip. 0 is at left, increasing to right.
		PMString	fName;		// Name of this control set, used for a menu item for controlling which sets are visible.
		PMString	fMenuName;	// Name of the menu item that controls visibility of this control set. usually same as name, could be different if two control sets map to same menu entry
		PMString	fCategoryName;// Category name of this control set. See ControlStripDefs.h
		PMReal		fCategoryOrder;	// Category order of this control set for sort order. See ControlStripDefs.h
};

#endif //__CONTROLSTRIPWIDGETINFO__

