//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PaletteWorkspaceDefs.h $
//  
//  Owner: Dave Burnard
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
#ifndef __PaletteWorkspaceDefs__
#define __PaletteWorkspaceDefs__

namespace PaletteWorkspaceDefs 
{
	// XML Tags
	
	WIDGET_DECL extern const char* kPaletteWorkspaceXMLTag;
	WIDGET_DECL extern const char* kPaletteWorkspaceVersionTag;
	WIDGET_DECL extern const char* kPaletteWorkspaceFeatureSetTag;
	WIDGET_DECL extern const char* kPaletteWorkspaceActiveNameTag;
	WIDGET_DECL extern const char* kDockXMLTag;
	WIDGET_DECL extern const char* kDockedControlBarXMLTag;
	WIDGET_DECL extern const char* kDockedToolbarXMLTag;
	WIDGET_DECL extern const char* kTabPaneXMLTag;
	WIDGET_DECL extern const char* kControlBarPaneXMLTag;
	WIDGET_DECL extern const char* kControlBarXMLTag;
	WIDGET_DECL extern const char* kToolbarXMLTag;
	WIDGET_DECL extern const char* kTabGroupClusterXMLTag;
	WIDGET_DECL extern const char* kTabGroupXMLTag;
	WIDGET_DECL extern const char* kPanelXMLTag;
	WIDGET_DECL extern const char* kControlSetXMLTag;
	WIDGET_DECL extern const char* kDrawerXMLTag;
	WIDGET_DECL extern const char* kOWLWorkspaceBookmarkXMLTag;
	WIDGET_DECL extern const char* kOWLPaletteLeafXMLTag;

	// Attribute names
	WIDGET_DECL extern const char* kNameXMLAttributeName;
	WIDGET_DECL extern const char* kIDXMLAttributeName;
	WIDGET_DECL extern const char* kCSXSExtensionIDAttributeName;
	WIDGET_DECL extern const char* kVisibleXMLAttributeName;
	WIDGET_DECL extern const char* kIsClosedXMLAttributeName;
	WIDGET_DECL extern const char* kNeverShownXMLAttributeName;
	WIDGET_DECL extern const char* kXCoordXMLAttributeName;
	WIDGET_DECL extern const char* kYCoordXMLAttributeName;
	WIDGET_DECL extern const char* kHeightXMLAttributeName;
	WIDGET_DECL extern const char* kWidthXMLAttributeName;
	WIDGET_DECL extern const char* kLocationXMLAttributeName;
	WIDGET_DECL extern const char* kActiveTabXMLAttributeName;
	WIDGET_DECL extern const char* kDetailLevelXMLAttributeName;
	WIDGET_DECL extern const char* kListBoxDetailLevelXMLAttributeName;
	WIDGET_DECL extern const char* kDockLocationXMLAttributeName;
	WIDGET_DECL extern const char* kDockModeXMLAttributeName;
	WIDGET_DECL extern const char* kTabPaneModeXMLAttributeName;
	WIDGET_DECL extern const char* kToolbarShapeXMLAttributeName;
	WIDGET_DECL extern const char* kTabPaneIconModeWidthXMLAttributeName;
	WIDGET_DECL extern const char* kActiveDrawerPanelXMLAttributeName;
	WIDGET_DECL extern const char* kTabPaneIndexXMLAttributeName;
	WIDGET_DECL extern const char* kTabPaneLayoutModeXMLAttributeName;
	WIDGET_DECL extern const char* kMinimizedXMLAttributeName;
	WIDGET_DECL extern const char* kOWLWorkspaceBookmarkDataXMLName;

	WIDGET_DECL extern const char* kConstrainedHeightXMLAttributeName;
	WIDGET_DECL extern const char* kConstrainedWidthXMLAttributeName;

	WIDGET_DECL extern const char* kResizeableXMLAttributeName;

	// Attribute values
	WIDGET_DECL extern const char* kTopLocationXMLAttributeValue;
	WIDGET_DECL extern const char* kBottomLocationXMLAttributeValue;
	WIDGET_DECL extern const char* kLeftLocationXMLAttributeValue;
	WIDGET_DECL extern const char* kRightLocationXMLAttributeValue;
	
	WIDGET_DECL extern const char* kToolbarShape_VerticalWide_AttributeValue;
	WIDGET_DECL extern const char* kToolbarShape_VerticalNarrow_AttributeValue;
	WIDGET_DECL extern const char* kToolbarShape_Horizontal_AttributeValue;

	WIDGET_DECL extern const char* kTabPaneMode_Expanded_AttributeValue;
	WIDGET_DECL extern const char* kTabPaneMode_Icon_AttributeValue;

	WIDGET_DECL extern const char* kTabPaneLayoutMode_AutoFlow_AttributeValue;
	WIDGET_DECL extern const char* kTabPaneLayoutMode_Manual_AttributeValue;

	// Other strings
	WIDGET_DECL extern const char* kWorkspaceFileFilenameExtension;
	WIDGET_DECL extern const char* kCurrentPaletteWorkspaceVersionStr;

	WIDGET_DECL extern const char* kDynamicPanelAttributeName;

	WIDGET_DECL extern const char* kUserWorkspaceXMLTag;
	WIDGET_DECL extern const char* kUserWorkspaceAppVersionTag;
	WIDGET_DECL extern const char* kUserWorkspaceBuildNumberTag;

}

#endif // __PaletteWorkspaceDefs__
