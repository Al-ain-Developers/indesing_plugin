//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelDefs.h $
//  
//  Owner: ?
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
//  Definitions for constants used by the layer panel
//  
//========================================================================================

#pragma once
#ifndef __LayerPanelDefs__
#define __LayerPanelDefs__

#include "IconRsrcDefs.h"
#include "StdHeightWidthConstants.h"

// ----- localizable resource IDs

#define kLayerPanelStringsRsrcID			1000
#define kLayerPanelStringsNoTransRsrcID		1100

#define kLayerOptionsDialogRsrcID		1400
#define kLayerMenuResID				1600

#define kLayerPanelActionResID			1700

#define kLayerPanelPanelListRsrcID					1900
#define kLayerPanelRsrcID							2000
#define kLayerPageItemElementPanelRsrcID			2100
#define kLayerElementPanelRsrcID					2200
#define kLayerPageItemElementSmallRowsPanelRsrcID	2300
#define kLayerElementSmallRowsPanelRsrcID			2400
// icon ids
#define kLayerLockedIcon		1512
#define kLayerPenIcon			1514
#define kLayerBlankIcon			1515
#define kLayerNotLockedIcon		kLayerBlankIcon
#define kLayerPenLockedIcon		1516
#define kLayerPenSmallIcon		1517
#define kLayerPenLockedSmallIcon 1518
#define kLayerProxyCantDropIcon 1519
#define kLayerLockedOpaqueIcon	1520
#define kLayerPaletteIconRsrcID 1550

const int kActiveInset = 25;
const int kLayerProxySize = 7;

const int kMinLayerPalWidth = 240;
const int kMaxLayerPalWidth = 10000;
const int kMaxLayerPalHeight = 10000;

#define PAGEITEM_NAME_PANEL_XLOC(contentHeight) (2 * contentHeight + 2 + kLayerProxySize + 1)

#endif
