//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtResDefs.h $
//  
//  Owner: Adobe Developer Technologies
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
//  Defines Resource IDs used by the Goto Text Edit plug-in.
//  
//========================================================================================

#ifndef __GTTxtEdtResDefs_h__
#define __GTTxtEdtResDefs_h__

#include "ControlStripDefs.h"

// See. the platform resource file where these are used!
#define kGTTxtEdtControlStripPanelResId				1500
#define kGTTxtEdtGoToTextButtonIconRsrcID			1600

#define kGTTxtEditControlStripSet	\
	ControlStripWidgetInfo(kGTTxtEdtControlStripPanelResId, \
						kGTTxtEdtPluginID, \
						kGTTxtEdtControlStripPriority, \
						"kGTTxtEdtControlStripName", \
						"kGTTxtEdtControlStripName", \
						kControlStripParagraphCategoryName, \
						kControlStripParagraphCategory)

#endif // __GTTxtEdtResDefs_h__

// End, GTTxtEdtResDefs.h.


