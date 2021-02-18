//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DVAForwardDeclarations.h $
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
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __DVAForwardDeclarations__
#define __DVAForwardDeclarations__

// Common DVA forward declarations

namespace dvaui {
	
	//Drawbot
	namespace drawbot {
		class Drawbot;
		struct ImageInterface;
		struct SurfaceInterface;
		struct SupplierInterface;
		class PathP;
		class FileImageP;
	}
	
	//UI_Node
	namespace ui {
		class UI_Node;
		class MouseEvent;
		class PointerEvent;
		class KeyboardEvent;
		class OS_Event;
#ifdef MACINTOSH
		class OS_View;
#endif
		class OS_Window;
		class UI_Dialog;
	}
	
	//Controls
	namespace controls {
		class UI_Checkbox;
		class UI_ControlView;
		class UI_PictureButton;
		class UI_Popup;
		class UI_RadioButton;
		class UI_StaticImage;
		class UI_StaticText;
		class UI_TextEdit;

		class UI_PictureSupplyMessage;
		class UI_ControlChangedMessage;
	}
}

#endif
