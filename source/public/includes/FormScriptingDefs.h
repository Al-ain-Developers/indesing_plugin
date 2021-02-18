//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FormScriptingDefs.h $
//  
//  Owner: Mark VerMurlen
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
//  Contains defines used throughout scripting architecture
//  
//========================================================================================

#pragma once
#ifndef __FORMSCRIPTINGDEFS__
#define __FORMSCRIPTINGDEFS__

#define kFormScriptingStringsRsrcID 7000
#define kFormScriptingStringsNoTransRsrcID 7100
#define kFormScriptErrorStringTableRsrcID 7002

// ------------------------------------------------------------------

//
// Please make sure any id's you add are unique !!!
//

enum InteractiveElementsScriptSuites
{
	s_InteractiveElementsSuite =		'InES',

	enLastFormScriptSuite
};

// ------------------------------------------------------------------

// Script Misc
enum FormScriptMisc
{
	//These are used for inheritance in the AETE
	FormItemProperties =	'FPrp'
};

// ------------------------------------------------------------------

enum FormDefs 
{
	c_FormField =		'Ffld',	// cRectangle in AERegistry.h
	c_FormFields =		'Ffds',

	c_PushButton =		'Push',
	c_PushButtons =		'Pshs',
	c_RadioButton =		'Rdio',
	c_RadioButtons =	'Rdos',
	c_CheckBox =		'Chkb',
	c_CheckBoxes =		'Chbs',
	c_EditTextField =	'Edtx',
	c_EditTextFields =	'Edts',
	c_ListBox =			'Lisb',
	c_ListBoxes =		'Lsbs',
	c_ComboBox =		'Cmbo',
	c_ComboBoxes =		'Cmbx',
	c_SignatureField =	'Sigf',
	c_SignatureFields =	'Sigs',

	c_FieldChoice =		'CHoc',
	c_FieldChoices =	'CHcs',
	c_FieldAppearance =	'APrc',
	c_FieldAppearances = 'APrs',
	
	c_ButtonPref = 		'btnp',

	c_MultiStateObject =  'Msob',
	c_MultiStateObjects = 'Msos',
	
	e_ApplyAppearance = 'AApr',
	e_ConvertButtonToObject = 'bToO',
	e_ReleaseStateAsObject = 'Srls',
	e_ReleaseAllStatesAsObjects = 'Srss',
	e_ResetAllMultiStateObjects = 'rstM',
	e_ResetAllButtons = 'rstB',
	
	e_AddItemsAsState	= 'aias',
	e_AddItemsToState	= 'aits',
	
	en_FieldVisibilityInPDF	= 'FVIP',
	en_PDFVisible			= 'FVis',
	en_PDFHidden			= 'Fhid',
	en_PDFVisibleNoPrint	= 'FVNP',
	en_PDFHiddenButPrint	= 'FHBP',

	en_AppearanceState 		= 'FStt',
	en_StateNormal			= 'Fstn',
	en_StateOver			= 'Fstv',
	en_StateDown			= 'Fstd',
	en_StateNormalOn		= 'Fsno',
	en_StateNormalOff		= 'Fsnf',
	en_StateOverOn			= 'Fsvo',
	en_StateOverOff			= 'Fsvf',
	en_StateDownOn			= 'Fsdo',
	en_StateDownOff			= 'Fsdf',
	en_StateCustom			= 'Fcss',

	en_FieldTextAlign		= 'ATxx',

	p_FormExportMapping =	'Fexm',
	p_FormValue 		=	p_Value,
	p_FormDefaultValue 	=	'Fdvl',
	p_FormVisibilityInPDF =	'Fvip',
	p_FormExport 		=	'Fexp',
	p_FormExportRequired =	'Fexr',
	p_FormAppearanceStyle =	p_StyleName,

	p_FieldTextFont 	=	'Ffnt',
	p_FieldTextFontStyle =	'Ffsy',
	p_FieldTextSize 	=	'Ffsz',
	p_FieldTextFillColor 	=	'Ffcl',
	p_FieldTextFillTint 	=	'Fftt',
	p_FieldTextOverprint	=	'Ffov',
	p_FieldTextLineColor 	=	'Ffsc',
	p_FieldTextLineTint 	=	'Ffst',
	p_FieldTextStrokeOverprint = 'Ffso',
	p_FieldTextLineWeight	=	'Ffsw',
	p_FieldTextLineMiterLimit	=	'Ffml',
	p_FieldTextLineJoin	=	'Ffsj',
	p_FieldTextLineAlign	=	'Ffsa',

	p_ExportValue = 	'Fexv',
	
	p_DefaultChecked =	'Cdfc',
	
	p_TextMultiline 	=	'Txml',
	p_TextPassword 		=	'iSpw',
	p_TextScroll 		=	'Txds',
	p_TextHasMaxLength 	=	'Txhm',
	p_FormSpellCheck 	=	'Fnsc',
	p_TextUseForFileSel =	'Tufs',
	p_TextMaxLength 	=	'Txmx',
	p_FieldTextAlignment 	=	'Txal',
	
	p_ChoiceAllowMultiSel =	'Cham',
	p_ChoiceEditable 	=	'Ched',
	p_ChoiceSort 		=	'Chst',
	p_ChoiceList 		=	'Chlt',
	
	p_FormActiveState = 	'Favt',
	p_AppearanceState = 	'APst',
	p_AppearanceIsActive =	'APav',

	p_ChoicePositionIndex = 'CHps',

	p_CalculationOrder = 	'COpp',
	p_TabOrder = 			'TOpp',
	
	p_ButtonPref = 			'bnpp',

	p_NewPosition =			'APnp',
	p_ActiveStateIndex =	'Aase',

	p_InitiallyHidden =		'Minh',
	p_PageItems	=			'pGpI',

	p_FormMERTL =			'MRTL',
	p_PrintableInPDF =		'PPDF',
	p_HiddenUntilTriggered =	'HiTr'
};

#endif	//#ifndef __FORMSCRIPTINGDEFS__
