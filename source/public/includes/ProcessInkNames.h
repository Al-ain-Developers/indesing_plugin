//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ProcessInkNames.h $
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
//  ABSTRACT:
//  This file defines the process ink names, which are used in the AddInkCmd
//  and in the Print plugin. 
//  
//========================================================================================

#pragma once
#ifndef __PROCESSINKNAMES__
#define __PROCESSINKNAMES__

// Localization Note:	It is important that the process ink name that
// an ink is initialized with (in \source\private\color\AddInkCmd.cpp)
// is the same name that it is compared against when printing - (in
// \source\components\print\PrintInitClientItemsCmd.cpp). As long as 
// these two name match correctly, printing separations will be correct. 

// CMYK space
#define		kProcessCyan			"Process Cyan"
#define		kProcessMagenta			"Process Magenta"
#define		kProcessYellow			"Process Yellow"
#define		kProcessBlack			"Process Black"

// HEX space
#define		kHexachromeCyan			"Hexachrome Cyan"
#define		kHexachromeMagenta		"Hexachrome Magenta"
#define		kHexachromeYellow		"Hexachrome Yellow"
#define		kHexachromeBlack		"Hexachrome Black"
#define		kHexachromeOrange		"Hexachrome Orange"
#define		kHexachromeGreen		"Hexachrome Green"

//	PS ink names
#define		kPSCyan					"Cyan"
#define		kPSMagenta				"Magenta"
#define		kPSYellow				"Yellow"
#define		kPSBlack				"Black"
#define		kPSSeparationAll		"All"

#endif