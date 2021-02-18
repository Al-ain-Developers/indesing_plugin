//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/QuickApplyFindListNode.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __QUICKAPPLYFINDLISTNODE__
#define __QUICKAPPLYFINDLISTNODE__

#include "IPMUnknown.h"
#include "FindChangeID.h"
#include "K2Vector.h"
#include "WidgetDefs.h"
#include "widgetid.h"
#include "SysControlIds.h"

class PMString;

/**
 Defines the items that are displayed in the QuickApplyDialog
 @see IQuickApplyService
*/
class QuickApplyFindListNode
{
	public:
		typedef object_type data_type;
				
		/**
		 Default Constructor
		 Constructs an QuickQpplyFindListNode object with default values.
		*/
		QuickApplyFindListNode() :
					fName(""), 
					fType(kStandardTreeNodeChildWidgetIconRsrcID), 
					fPluginID(kApplicationRsrcPluginID), 
					fIconRsrcID(kStandardTreeNodeChildWidgetIconRsrcID),
					fReference(0),
					fEllipseStyle(kEllipsizeEnd) {}
		
		/**
		 Constructor
		 Constructs a QuickQpplyFindListNode from another QuickQpplyFindListNode.
		 @param node node to copy data from
		*/
		QuickApplyFindListNode(const QuickApplyFindListNode &node)
		{
			this->fName = node.fName;
			this->fType = node.fType;
			this->fPluginID = node.fPluginID;
			this->fIconRsrcID = node.fIconRsrcID;
			this->fReference = node.fReference;
			this->fEllipseStyle = node.fEllipseStyle;
		}
		
		/**
		 Constructor
		 Constructs a QuickQpplyFindListNode with passed in parameter values
		 @param name this string will be used as a display and search name in the dialog
		 @param type identifier to identify which service provider owns this node (See IQuickApplyService)
		 @param pluginID id of the plug in which defines the icon resource id (next parameter)
		 @param iconRsrcID id of the resource of with the icon to display in the quick apply list next to this item
		 @param reference can be anything really it's user data
		 @param ellipseStyle type of dot dot dot style to use middle, end, beginning see EllipsizeStyle style definition
		*/
		QuickApplyFindListNode(PMString name, uint32 type, PluginID pluginID, RsrcID iconRsrcID, uint32 reference, EllipsizeStyle ellipseStyle) 
						{ fName = name; fType = type; fPluginID = pluginID; fIconRsrcID = iconRsrcID; 
							fReference = reference; fEllipseStyle = ellipseStyle; }
		
		/**
		 Destructor
		*/
		virtual ~QuickApplyFindListNode() {}
		
		/**
		 Assignment operator copies one QuickApplyFindListNode to another
		*/
		QuickApplyFindListNode operator = (const QuickApplyFindListNode &node) 
		{
			this->fName = node.fName;
			this->fType = node.fType;
			this->fPluginID = node.fPluginID;
			this->fIconRsrcID = node.fIconRsrcID;
			this->fReference = node.fReference;
			this->fEllipseStyle = node.fEllipseStyle;
			
			return *this;
		}
		
		/**
		 Equality operator definition of when two QuickApplyFindListNode are considered equal
		*/
		inline bool16 operator == (const QuickApplyFindListNode &node) { return (this->fName == node.fName && this->fType == node.fType && 
																	   this->fPluginID == node.fPluginID &&  this->fIconRsrcID == node.fIconRsrcID &&
																	   this->fReference == node.fReference && this->fEllipseStyle == node.fEllipseStyle); }
		
		/**
		 fName this string will be used as a display and search name in the dialog
		*/
		PMString fName;
		
		/**
		 fType identifier to identify which service provider owns this node (See IQuickApplyService)
		*/		
		uint32 fType;
		
		/**
		 fPluginID id of the plug in which defines the icon resource id
		*/				
		PluginID fPluginID;
		
		/**
		 fIconRsrcID id of the resource of with the icon to display in the quick apply list next to this item
		*/						
		RsrcID fIconRsrcID;
		
		/**
			fReference user data not used by quick apply dialog itself may be useful to service providers
		*/
		uint32 fReference;
		
		/**
			fEllipseStyle type of dot dot dot style to use middle, end, beginning see EllipsizeStyle style definition
		*/
		EllipsizeStyle fEllipseStyle;
};



#endif // __QUICKAPPLYFINDLISTNODE__
