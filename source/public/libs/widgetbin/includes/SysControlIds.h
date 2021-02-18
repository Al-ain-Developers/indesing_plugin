//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/SysControlIds.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __SysControlIds_h__
#define __SysControlIds_h__

#ifndef kPluginID_None
	#define	kPluginID_None	""
#endif

// BP 07/07/01: kApplicationRsrcPluginID points to the plug-in that contains the resources for icons, cursor, and dialogs.
#define kApplicationRsrcPluginID 		RezLong(0x16401)	// kAppUIPrefix +1, see AppUIID.h.

#define kSysGenericSeparatorRsrcId		  4
#define kSysGenericSeparatorPMRsrcId	kSysGenericSeparatorRsrcId, kApplicationRsrcPluginID

#define kSysPictureRsrcId				100
#define kSysStaticTextRsrcId			101
#define kSysEditBoxRsrcId				102
#define kSysGroupBoxRsrcId				103
#define kSysButtonRsrcId				104
#define kSysCheckBoxRsrcId				105
#define kSysRadioButtonRsrcId			106
//#define kSysComboBoxRsrcId				107
#define kSysListBoxRsrcId				108
#define kSysVScrollBarRsrcId			109
#define kSysHScrollBarRsrcId			110
#define kSysAnimateRsrcId				111
#define kSysTabControlRsrcId			112
#define kSysTreeControlRsrcId			113
#define kSysListControlRsrcId			114
#define kSysHotKeyRsrcId				115
#define kSysSliderRsrcId				116
#define kSysProgressBarRsrcId			117
#define kSysOwnerDrawListBoxRsrcId		119
#define kSysDropDownRsrcId				120
#define kSysOwnerDrawDropDownRsrcId		121
#define kSysOwnerDrawStringListBoxRsrcId	122
#define kSysMultilineEditBoxRsrcId			123

#define kSysNewDropDownRsrcId			130

#define kSysPicturePMRsrcId				kSysPictureRsrcId, 			kApplicationRsrcPluginID
#define kSysStaticTextPMRsrcId			kSysStaticTextRsrcId, 		kApplicationRsrcPluginID
#define kSysEditBoxPMRsrcId				kSysEditBoxRsrcId, 			kApplicationRsrcPluginID
#define kSysGroupBoxPMRsrcId			kSysGroupBoxRsrcId, 		kApplicationRsrcPluginID
#define kSysButtonPMRsrcId				kSysButtonRsrcId, 			kPluginID_None
#define kSysCheckBoxPMRsrcId			kSysCheckBoxRsrcId, 		kPluginID_None
#define kSysRadioButtonPMRsrcId			kSysRadioButtonRsrcId, 		kPluginID_None
#define kSysComboBoxPMRsrcId			kSysComboBoxRsrcId, 		kApplicationRsrcPluginID
#define kSysListBoxPMRsrcId				kSysListBoxRsrcId, 			kApplicationRsrcPluginID
#define kSysVScrollBarPMRsrcId			kSysVScrollBarRsrcId, 		kPluginID_None
#define kSysHScrollBarPMRsrcId			kSysHScrollBarRsrcId, 		kPluginID_None
#define kSysAnimatePMRsrcId				kSysAnimateRsrcId, 			kApplicationRsrcPluginID
#define kSysTabControlPMRsrcId			kSysTabControlRsrcId, 		kApplicationRsrcPluginID
#define kSysTreeControlPMRsrcId			kSysTreeControlRsrcId, 		kApplicationRsrcPluginID
#define kSysListControlPMRsrcId			kSysListControlRsrcId, 		kApplicationRsrcPluginID
#define kSysHotKeyPMRsrcId				kSysHotKeyRsrcId, 			kApplicationRsrcPluginID
#define kSysSliderPMRsrcId				kSysSliderRsrcId, 			kApplicationRsrcPluginID
#define kSysProgressBarPMRsrcId			kSysProgressBarRsrcId, 		kApplicationRsrcPluginID
#define kSysOwnerDrawListBoxPMRsrcId	kSysOwnerDrawListBoxRsrcId, kApplicationRsrcPluginID
#define kSysDropDownPMRsrcId			kSysDropDownRsrcId, 		kApplicationRsrcPluginID
#define kSysOwnerDrawDropDownPMRsrcId	kSysOwnerDrawDropDownRsrcId, kApplicationRsrcPluginID
#define kSysOwnerDrawStringListBoxPMRsrcId	kSysOwnerDrawStringListBoxRsrcId, kApplicationRsrcPluginID

// ----- On the Macintosh there must be an icon that has resource id
//		 of 132. This is the size box icon.

#define kSysWindowSizeBoxRsrcId			132 
#define kSysWindowSizeBoxPMRsrcId		kSysWindowSizeBoxRsrcId, 	kApplicationRsrcPluginID 


#endif // __SysControlIds_h__
