//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TreeViewDefs.h $
//  
//  Owner: Matt Joss
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
#ifndef __TreeViewDefs__
#define __TreeViewDefs__

// ----- ITreeAttributes

#define kHideRootNode					0x0000
#define kDisplayRootNode				0x0001
#define kDrawEndLine					0x0002
#define kDrawBorder						0x0004


// ----- PreDefined TreeView styles used in ITreeViewWidgetMgr
#define kInvalidTreeStyle				-1
#define kNoTreeStyle					0
#define kSmallPaletteRowsTreeStyle		1
#define kLargePaletteRowsTreeStyle		2
#define kTouchPaletteRowsTreeStyle		3
//New tree node style for large list node in properties panel. The font of swatch name tends to become bigger after editing in popup hosted in properties panel.That was due to the fact that popup is actually a dialog and font in dialog is bigger than that in panel. To fix this, we introduced a new type of node which explicity sets the font of the swatch name in the node.
#define kPropertiesPanelLargePaletteRowsTreeStyle	4						

//----------------------------------------------------------------------------------------
// Resource ID of Tree View widgets
//----------------------------------------------------------------------------------------
#define kStandardLargeTreeNodeRsrcID			1000
#define kStandardSmallTreeNodeRsrcID			2000
#define kStandardStringListBoxTreeNodeRsrcID	3000
#define kStandardSmallStringListBoxTreeNodeRsrcID	3010
#define kStandardViewListBoxTreeNodeRsrcID	4000

//----------------------------------------------------------------------------------------
//	Column header attributes
//----------------------------------------------------------------------------------------
#define	kDontAutoResize				10
#define	kAutoResizeFirstColumn		11
#define	kAutoResizeProportional		12
#define	kColumnsNotUserResizable	13


#endif // __TreeViewDefs__
