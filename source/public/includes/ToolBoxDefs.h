//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ToolBoxDefs.h $
//  
//  Owner: lance bushore
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
//  This file contains defines for our tool groups. gaps are intentional so that 3rd parties
//  can add groups relative to ours.
//  
//========================================================================================

#pragma once
#ifndef __ToolBoxDefs__
#define __ToolBoxDefs__

// Misc
#define kDoesNotApply			0

// Group numbers
#define kFirstAdobeToolsGroup 		5		// Pointer tools
#define kSpecialFirstAdobeToolsGroup	7	// Drawing(gesture) tool
#define kSecondAdobeToolsGroup		10		// Creation tools
#define kThirdAdobeToolsGroup		15		// Transform tools
#define kFourthAdobeToolsGroup		20		// Navigation tools
#define kFifthAdobeToolsGroup		25		// Unused, good place for third-party tools or SDK tools
#define kSixthAdobeToolsGroup		30		// Unused, good place for third-party tools or SDK tools
#define kSeventhAdobeToolsGroup		35		// Stroke/Fill proxy tool, also container/text tools
#define kEighthAdobeToolsGroup		45		// Unused
#define kNinthAdobeToolsGroup		50		// Apply color, gradient, none tools
#define kTenthAdobeToolsGroup		55		// View Options Tool
#define kEleventhAdobeToolsGroup	60		// Normal, preview view mode tools

// Tool numbers within group or subgroup
#define kFirstAdobeTool			5
#define kSecondAdobeTool		10
#define kThirdAdobeTool			15
#define kFourthAdobeTool		20
#define kFifthAdobeTool			25
#define kSixthAdobeTool			30
#define kSeventhAdobeTool		35
#define kEighthAdobeTool		40
#define kNinthAdobeTool			45
#define kTenthAdobeTool			50
#define kEleventhAdobeTool		55
#define kTwelfthAdobeTool		60
// Time for a new tool group?

#endif