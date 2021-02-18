//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptingDefs.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __SCRIPTINGDEFS__
#define __SCRIPTINGDEFS__

// The following are items defined in the Universal headers on the Mac
#if MACINTOSH && __clang__
// avoid collisions with the Universal header on the Mac
	#include <Carbon/../Frameworks/OpenScripting.framework/Headers/ASRegistry.h> // OpenScripting
#else // Win or odfrc
//Used by IScriptRequestData::GetRequestedDataType
#ifndef typeChar
#define	typeChar				'TEXT'
#endif
#ifndef typeUnicodeText
#define	typeUnicodeText			'utxt'
#endif

//Used by ScriptInfo::SpecifierForm
#ifndef formAbsolutePosition
#define	formAbsolutePosition	'indx'
#endif
#ifndef formName
#define	formName				'name'
#endif
#ifndef kAEFirst
#define	kAEFirst				'firs'
#endif
#ifndef kAELast
#define	kAELast					'last'
#endif
#ifndef kAEMiddle
#define	kAEMiddle				'midd'
#endif
#ifndef kAEAny
#define	kAEAny					'any '
#endif
#ifndef kAEAll
#define	kAEAll					'all '
#endif
#ifndef formPropertyID
#define	formPropertyID			'prop'
#endif
#ifndef formRange
#define	formRange				'rang'
#endif
#ifndef formRelativePosition
#define	formRelativePosition	'rele'
#endif
#ifndef formTest
#define	formTest				'test'
#endif
#ifndef formUniqueID
#define formUniqueID			'ID  '
#endif
#ifndef kAENext
#define kAENext					'next'
#endif
#ifndef kAEPrevious
#define kAEPrevious				'prev'
#endif

//Used as param ids
#ifndef keyAEFile
#define	keyAEFile				'kfil'
#endif
#ifndef keyAEInsertHere
#define keyAEInsertHere			'insh'
#endif
#ifndef keyAEData
#define keyAEData				'data'
#endif
#ifndef keyAEPropData
#define keyAEPropData			'prdt'
#endif
#ifndef keyDirectObject
#define keyDirectObject			'----'
#endif
#ifndef keyAEObject
#define keyAEObject				'kobj'
#endif
#ifndef keyAEObjectClass
#define keyAEObjectClass		'kocl'
#endif
#ifndef keyAEPosition
#define keyAEPosition			'kpos'
#endif
#ifndef keyASPrepositionWith
#define keyASPrepositionWith	'with'
#endif
#ifndef keyASPrepositionTo
#define keyASPrepositionTo		'to  '
#endif
#ifndef keyASPrepositionGiven
#define keyASPrepositionGiven	'givn'
#endif
#ifndef keyASPrepositionFrom
#define keyASPrepositionFrom	'from'
#endif
#ifndef keyASPrepositionOn
#define keyASPrepositionOn		'on  '
#endif
#ifndef keyASPrepositionAround
#define keyASPrepositionAround	'arnd'
#endif
#ifndef keyASPrepositionBy
#define keyASPrepositionBy		'by  '
#endif
#ifndef keyASPrepositionIn
#define keyASPrepositionIn		'in  '
#endif
#ifndef keyASPrepositionFor
#define keyASPrepositionFor		'for '
#endif
#ifndef keyASPrepositionThru
#define keyASPrepositionThru	'thru'
#endif
#ifndef kAEDoObjectsExist
#define kAEDoObjectsExist		'doex'
#endif

#endif // MACINTOSH && __clang__

//
// Please make sure any id's you add are unique !!!
//

enum ScriptSuites
{
	s_LayoutSuite =				'K2PI',
	s_TextSuite =				'TeXT',
	s_CoreSuite = 				'core',	// kAECoreSuite in AERegistry.h
	s_OurCoreSuite = 			'CoRe',
	s_InDesignBasicSuite =		'K2  ',
	s_Quickdrawsuite =			'Qdrw',
	s_MiscSuite =				'misc', // kAEMiscStandards in AERegistry.h
	s_PreferencesSuite = 		'K2PF',
	s_ColorSuite =				'K2CL',
	s_BookSuite =				'InBK',
	s_TableSuite =				'K2TB',
	s_TableOfContentsSuite = 	'ITOC',
	s_TypeNameSuite =			'tpnm',
	s_LibrariesSuite =			'K2LB',
	s_HyperLinksSuite =			'InHY',
	s_IndexingSuite =			'IDXG',
	s_HiddenSuite =				'Hidn',
	s_UI	= 					'UIUI',
	s_StrokeStyleSuite =			'StSu',
	s_ObjectStylesSuite =		'OSSu',
	s_JobBagSuite =				'JBSu',
	s_GraphicsServerSuite =		'GSSu',
	s_PreflightSuite =			'PFSu'
};

// Class IDs
enum ScriptClasses
{
	c_Null =			'null',
//	c_Application =		c_Null,
	c_Document =		'docu',	// cDocument in AERegistry.h
	c_Documents =		'docs',
	c_Spread =			'sprd',
	c_Spreads =			'prds',
	c_MasterSpread =	'mspr',
	c_MasterSpreads =	'msps',
	p_MasterPageItems =	'mpgs',
	c_Layer =			'layr',
	c_Layers =			'lyrs',
	c_Page =			'page',
	c_Pages =			'pags',
	c_Window =			'cwin',	// cWindow in AERegistry.h
	c_Windows =			'wins',
	c_LayoutWindow =	'Lwin',
	c_LayoutWindows =	'Lwns',
	c_StoryWindow =		'Swin',
	c_StoryWindows =	'Swns',
	c_Color =			'colr',	// keyAEColor in AERegistry.h
	c_Colors =			'clrs',
	c_Swatch =			'swch',
	c_Swatches =		'swcs',
	c_Gradient =		'grad',
	c_AGMBlackBox =		'ctbb',
	c_Gradients =		'grds',
	c_AGMBlackBoxes =   'ctbs',
	c_GradStop =		'gstp',
	c_GradStops =		'gsts',
	c_Tint =			'tint',
	c_Tints =			'tnts',
	c_Path =			'ppth',
	c_Paths =			'pths',
	c_ClippingPath =	'cpth',
	c_GraphicLayerOption = 'glop',
	c_GraphicLayer =	'grlr',
	c_GraphicLayers =	'grls',
	c_Point =			'ppnt',
	c_Points =			'pnts',
	c_TextFrame =		'txtf',
	c_TextFrames =		'txfs',
	c_EndnoteTextFrame = 'entf',
	c_EndnoteTextFrames = 'enfs',
	c_Guide =			'guid',
	c_Guides =			'gids',
	c_LinkMetadata = 	'clxm',
	c_Text =			'ctxt',	// cText in AERegistry.h
	c_Texts =			'txts',
	c_Line =			'clin',	// cLine in AERegistry.h
	c_Lines =			'tlns',
	c_Word =			'cwor',	// cWord in AERegistry.h
	c_Words =			'wrds',
	c_Character =		'cha ',	// cChar in AERegistry.h
	c_Characters =		'chrs',
	c_TextColumn =		'Ccol',	// cColumn in AERegistry.h
	c_TextColumns =		'cols',
	c_Paragraph =		'cpar',	// cParagraph in AERegistry.h
	c_Paragraphs =		'pars',
	c_Story =			'cflo',	// cTextFlow in AERegistry.h
	c_Stories =			'flos',
	c_Change =			'Chng',
	c_Changes =			'Chgs',
	c_Note =			'Note',
	c_Notes	=			'Nots',
	c_TextStyleRange = 	'txsr',
	c_TextStyleRanges = 'tsrs',
	c_TabStop = 		'tstp',
	c_TabStops = 		'tsps',
	c_RunInStyle = 		'rist',
	c_RunInStyles =	 	'riss',
	c_GrepRunInStyle = 	'gris',
	c_RunInLineStyle =	'rils',
	c_GrepRunInStyles = 'grss',
	c_RunInLineStyles =	'rlss',
	c_InsertionPoint =	'cins', // cInsertionPoint in AERegistry.h
	c_InsertionPoints =	'inps',
	c_Group =			'grop',
	c_Groups =			'grps',
	c_CharStyle =		'csty',
	c_CharStyles =		'csts',
	c_ParaStyle =		'psty',
	c_ParaStyles =		'psts',
	c_Language =		'lang',
	c_Languages =		'lngs',
	c_AutoCorrect =		'ACcr',
	c_AutoCorrects =	'ACrs',
	c_AutoCorrectWordPair	=	'ACwp',
	c_AutoCorrectWordPairs	=	'ACws',
	c_VendorLanguage =	'vlng',
	c_VendorLanguages =	'vlgs',
	c_Section =			'sctn',
	c_Sections =		'scns',

	c_CMSSettings =		'CSet',
	p_CMSSettings = 	'cSet',

	c_TrapStyle =		'trSt',
	c_TrapStyles =		'trSs',

	// for preference handling
	c_AutoCorrectPref =	'acrp',
	p_AutoCorrectPref = 'acpp',
	c_SpellPref =		'splp',
	p_SpellPref	= 		'slpp',
	c_DictPref =			'dctp',
	p_DictPref = 		'dtpp',
	c_DocPref =			'docp',
	c_TinDocumentData = 'tinD',
	p_TinDocumentData = 'tinP',
	c_GaijiOwnedItem = 'gaiO',
  	p_GaijiOwnedItemData = 'gaiD',
	p_GaijiOwnedItemKeyData = 'gaiK',
  	c_GaijiOwnedItems = 'gaiS',
	p_GaijiRefMaps = 'gaiM',
	p_DocPref = 		'dcpp',
	c_GridPref =			'grdp',
	p_GridPref = 		'grpp',
	c_GuidePref =		'gudp',
	p_GuidePref = 		'gdpp',
	c_PasteboardPref =	'pbdp',
	p_PasteboardPref = 	'pBDP',
	c_MarginPref =		'imgp',
	p_MarginPref = 		'impp',
	c_ImageIOPref =	'imop',
	p_ImageIOPref = 	'iopp',
	c_ImagePref =		'imcs',
	p_ImagePref = 		'impr',
	c_TextOptPref =		'txtp',
	p_TextOptPref = 		'txpp',
	c_TextEditingPref =	'txep',
	p_TextEditingPref = 'txdp',
	c_MagnifyToolPref =	'mtpc',
	p_MagnifyToolPref =	'mtpr',
	c_ViewPref =		'viwp',
	p_ViewPref = 		'vwpp',
	c_BasePrint =		'bPnt',
	c_PrintPref =		'prnp',
	p_PrintPref = 		'prpp',
	c_PrintStyle =		'cPsy',
	c_PrintStyles =		'cPts',
	c_DocumentStyle =	'cDsy',
	c_DocumentStyles =	'cDcs',
	c_PolygonPref =		'plyp',
	p_PolygonPref = 	'pypp',
	c_PDFExportPref =	'PDFp',
	c_InteractivePDFExportPref =	'iPDF',
	p_PDFPref =			'DFpf',
	p_InteractivePDFPref =			'piPP',
	c_PDFExportStyle =	'PFst',
	c_PDFExportStyles =	'PFss',
	c_PDFPlacePref =	'PDFi',
	p_PDFPlacePref = 	'DFif',
	c_PDFAttribute =		'PDFa',
	p_PDFAttribute = 	'DFaf',
	c_StoryPref =		'SyPf',
	p_StoryPref = 		'pSTP',
	c_TextFramePref =	'TFPf',
	p_TextFramePref = 	'pTFP',
	c_SVGExportPref =	'svPf',
	p_SVGPref =			'psvP',
	c_XPPref =			'xpPf',
	p_XPPref =			'pxpP',
	c_IMEPref =			'cImP',
	p_IMEPref =			'pImP',
	c_FontLockingPrefs = 'cFlP',
	p_FontLockingPrefs = 'pFlP',
	p_FontInputLockingPref = 'pFil',
	p_FontChangeLockingPref = 'pFcl',
	c_GrabberPref =		'cgrp',
	p_GrabberPref = 	'pgrp',

	c_PSDLayerComp =	'cplc',
	p_PSDLayerComp = 	'pplc',

	c_EPSExportPrefs =	'cEEP',
	c_EPSImportPrefs =	'cEIP',
	p_EPSExportPrefs = 'pEEP',
	p_EPSImportPrefs = 'pEIP',

	c_DisplaySetting = 	'cDsp',
	c_DisplaySettings = 'DspS',
	c_DefViewSettingPref = 'cDvs',
	p_DefViewSettingPref = 'Dvsp',
	c_LayoutAdjustPref =		'Ladp',
	p_LayoutAdjustPref =		'pLad',
	c_AdaptiveLayoutPref =		'ALPO',
	p_AdaptiveLayoutPref =		'ALPP',

	c_UserDict =		'usrd',
	c_UserDicts =		'usrs',
	c_HyphException =	'hyfe',
	c_HyphExceptions =	'hyfs',

	c_Font = 	'FonT',
	c_Fonts = 	'FnTs',
	c_FontFamily = 	'fFam',
	c_FontFamilies = 	'FFMs',
	c_CompositeFonts = 	'cfns',
	c_CompositeFont = 	'cfnt',
	c_CompositeFontEntries = 'cfes',
	c_CompositeFontEntry = 'cfen',

	c_WordRTFPref = 	'WRDI',
	p_WordRTFPref = 	'pWRD',
	c_ExcelImportPref = 'XLSI',
	p_ExcelImportPref = 'pXLS',
	c_TextImportPref = 	'TXTI',
	p_TextImportPref = 	'pTXT',
	c_TextExportPref =  'TXEI',
	p_TextExportPref =  'pTXE',
	c_TagTextImportpref = 'TTII',
	p_TagTextImportpref = 'pTTI',
	c_TagTextExportPref = 'TTEI',
	p_TagTextExportPref = 'pTTE',

	c_TextDefault 		= 'cTdf',
	p_TextDefault 		= 'pTdf',
	c_CJKTextDefault 	= 'cJdf',
	p_CJKTextDefault 	= 'pJdf',
	c_AnchoredObjectDefault		= 'cAOd',
	p_AnchoredObjectDefault		= 'pAOd',
	c_AnchoredObjectSettings	= 'cAOs',
	p_AnchoredObjectSettings	= 'pAOs',

	c_CJKGridPreferences 				= 'Jgpf',
	p_CJKGridPreferences				= 'Jppf',
	c_PrintGridPreferences 				= 'Jpgc',
	p_PrintGridPreferences				= 'Jpgp',

	c_ExportForWebPref	= 'ewPf',
	p_ExportForWebPref	= 'pewP',

	// Links prefs
	p_CheckLinksAtOpen =			'clao',
	p_FindMissingLinksAtOpen =		'fmlo',
	c_LinksPref =					'lkpf',
	p_LinksPref =					'lkpp',
	p_HTTPLinksRenditionType =      'hlrt',
	p_HTTPLinksAutoTagAssetPref =	'hlat',

	// Tool Box Panel
	c_Toolbox =						'ctbx',
	p_Toolbox =						'pTul',
	p_CurrentTool =					'Tool',
	p_CurrentToolName =				'tlNm',
	p_CurrentToolHint =				'tlHn',
	p_CurrentToolIcon =				'tlIc',
	en_ToolBoxTools =				'tuLz',
	en_SelectionTool =				'seLt',
	en_DirectSelectTool =			'dsLt',
	en_GapTool =					'gaPt',
	en_AdvancedGapTool =			'agAp',
	en_PenTool =					'peNt',
	en_AddAnchorPointTool =			'aaPt',
	en_DeleteAnchorPointTool =		'daPt',
	en_ConvertDirectionPointTool =	'cdPt',
	en_TypeTool =					'tyPt',
	en_VertTypeTool =				'vtTl',
	en_TypeOnPathTool =				'toPt',
	en_VertTypeOnPathTool =			'vtOp',
	en_METypeTool =					'meTt',
	en_TypeOnPathMETool =			'meTp',
	en_PencilTool =					'pnCl',
	en_SmoothTool =					'smTh',
	en_EraseTool =					'erSe',
	en_LineTool =					'lnTl',
	en_PolygonFrameTool =			'pfTl',
	en_RectangleFrameTool =			'rfTl',
	en_EllipseFrameTool =			'efTl',
	en_PolygonTool =				'plTl',
	en_RectangleTool =				'reTl',
	en_EllipseTool =				'elTl',
	en_RotateTool =					'roTl',
	en_ScaleTool =					'scTl',
	en_ShearTool =					'shTl',
	en_ScissorsTool =				'scZt',
	en_FreeTransformTool =			'ftTl',
	en_GradientSwatchTool =			'gsTl',
	en_GradientFeatherTool =		'gfTl',
	en_NoteTool =					'noTl',
	en_EyeDropperTool =				'edTl',
	en_MeasureTool =				'meTl',
	en_HandTool =					'haTl',
	en_ZoomTool =					'zmTl',
	en_HorizontalGridTool =			'hgTl',
	en_VerticalGridTool =			'vgTl',
	en_PumpkinTool =				'pmpk',
	en_PositionTool =				'posT',
	en_TableTool =					'tbTl',
	en_PlaceCursorTool =			'pcTl',
	en_MotionPathTool =				'mpTl',
	en_PageTool =					'spTl',
	
	// Griddata, LayoutGridData, and StoryGridData are all represented by the same
	// provider, but they need to be distinct types.  That's because the provider
	// needs some way to distinguish between the different members it's supposed
	// to be setting.
	c_CJKGridData 						= 'Jgda',
	p_CJKGridData						= 'Jgrd',
	c_CJKLayoutGridData 				= 'Jcpg',
	p_CJKLayoutGridData					= 'Jpgd',
	c_CJKStoryGridData 					= 'Jcsg',
	p_CJKStoryGridData					= 'Jsgd',

	c_KinsokuTable						= 'Jkst',
	c_KinsokuTables						= 'Jkss',
	c_MojikumiTable						= 'Jmjt',
	c_MojikumiTables					= 'Jmjs',

	c_MojikumiUIPref					= 'Jmui',
	p_MojikumiUIPref					= 'jmui',

	c_NamedGrid							= 'Jngd',
	c_NamedGrids						= 'Jngs',
	p_AppliedNamedGrid					= 'Jang',

	// Book
	c_Book = 'Book',
	c_Books = 'Boks',
	c_BookContent = 'Bkct',
	c_BookContents = 'Bcts',
	c_BookSyncOption = 'Bkso',
	c_BookSyncOptions = 'Bsos',

	//TOC
	c_TOCStyle = 'cTOC',
	c_TOCStyles = 'TOCs',
	c_TOCStyleEntry = 'cTny',
	c_TOCStyleEntrys = 'Tnys',

	// Indexing
	c_Index				= 'pidx',	// pIndex in AERegistry.h Used to be 'cIdx'
	c_Indexes			= 'cIds',
	c_IndexOptions		= 'cOpt',
	c_IndexHeaderSet	= 'cIhs',
	c_PageReference		= 'PgRf',
	c_PageReferences	= 'PgRs',
	c_CrossReference	= 'CRef',
	c_CrossReferences	= 'CRfs',
	c_Topic				= 'cTpc',
	c_Topics			= 'cTps',
	c_Subtopic			= 'cSTp',
	c_Subtopics			= 'cSTs',
	c_IndexSection		= 'iSec',
	c_IndexSections		= 'iScs',
	c_IndexingSortOption	= 'iSOp',
	c_IndexingSortOptions	= 'iSOs',

	c_IndexInstance		= 'InIx',	// for now only INX...
	c_IndexInstances	= 'InIs',

	c_Ink =				'cink',
	c_Inks =			'inks',

	c_FindPref =		'cFnd',
	p_FindPref =		'pFnd',
	c_ChangePref = 		'cChg',
	p_ChangePref =		'pChg',
	c_FindChangeTextOptions			= 'cFCT',
	p_FindChangeTextOptions			= 'pFCT',
	c_FindChangeGrepOptions			= 'cFCG',
	p_FindChangeGrepOptions			= 'pFCG',
	c_FindChangeGlyphOptions		= 'cFCp',
	p_FindChangeGlyphOptions		= 'pFCp',
	c_FindChangeObjectOptions		= 'cFCO',
	p_FindChangeObjectOptions		= 'pFCO',
	c_FindChangeColorOptions		= 'cFCC',
	p_FindChangeColorOptions		= 'pFCC',
	c_FindChangeTransliterateOptions= 'cFCl',
	p_FindChangeTransliterateOptions= 'pFCl',
	c_FindTextPref					= 'cFTP',
	p_FindTextPref					= 'pFTP',
	c_FindGrepPref					= 'cFGP',
	p_FindGrepPref					= 'pFGP',
	c_FindGlyphPref					= 'cFPP',
	p_FindGlyphPref					= 'pFPP',
	c_FindObjectPref				= 'cFOP',
	p_FindObjectPref				= 'pFOP',
	c_FindColorPref					= 'cFCr',
	p_FindColorPref					= 'pFCr',
	c_FindTransliteratePref			= 'cFLP',
	p_FindTransliteratePref			= 'pFLP',
	c_ChangeTextPref				= 'cCTP',
	p_ChangeTextPref				= 'pCxP',
	c_ChangeGrepPref				= 'cCGP',
	p_ChangeGrepPref				= 'pCGP',
	c_ChangeGlyphPref				= 'cCPP',
	p_ChangeGlyphPref				= 'pCPP',
	c_ChangeObjectPref				= 'cCOP',
	p_ChangeObjectPref				= 'pCOP',
	c_ChangeColorPref				= 'cCCP',
	p_ChangeColorPref				= 'pCCP',
	c_ChangeTransliteratePref		= 'cCLP',
	p_ChangeTransliteratePref		= 'pCLP',

    //Font preference
    c_FontSyncPref                  = 'fspf',
	p_FontSyncPref					= 'fspp',	
    p_AutoActivateFontPref          = 'aafp',

	// Hyperlinks
	c_Hyperlinks = 							'HLOS',
	c_Hyperlink =							'HLOB',
	c_HyperlinkTextSources = 				'HLTS',
	c_HyperlinkTextSource =					'HLTs',
	c_HyperlinkPageItemSources =		 	'HLPS',
	c_HyperlinkPageItemSource =				'HLPs',
	c_HyperlinkTextDestinations	=			'HLTD',
	c_HyperlinkTextDestination =			'HLTd',
	c_HyperlinkPageDestinations	=			'HLPD',
	c_HyperlinkPageDestination =			'HLPd',
	c_HyperlinkURLDestinations =			'HLUD',
	c_HyperlinkURLDestination =				'HLUd',
	c_HyperlinkExternalPageDestinations =	'HLEP',
	c_HyperlinkExternalPageDestination =	'HLEp',
	c_Bookmarks =							'Bmks',
	c_Bookmark =							'Bkmk',
	c_XRefFormats=							'XRFs',
	c_XRefFormat = 							'XRFm',
	c_XRefSources = 						'XRSs',
	c_XRefSource = 							'XRSr',
	c_XRefBuildingBlocks = 					'xBBs',
	c_XRefBuildingBlock = 					'xBBk',
	c_ParaDests = 							'PrDs',
	c_ParaDest = 							'ParD',

	// Libraries
	c_Library =			'Libr',
	c_Libraries =		'Lbrs',
	c_LibraryAsset =	'Lass',
	c_LibraryAssets =	'LAss',

	//MetaData
	c_MetaDataPref =	'cMet',
	p_MetaDataPref = 	'pMdp',
	c_MetaDataPacket =  'cMep',
	p_MetaDataPacket =	'pMep',

	//Export as INX
	e_SaveBack	=		'SvBk',
	c_SaveBackPref	=	'cSvB',
	p_SaveBackPref =	'pSvB',
	p_SaveBackFormat =	'SBFm',

	// preflight
	c_PreflightReport	=	'S4PR',
	c_PackageReport	=	'S4PA',
	c_BookPackageReport = 'B4PA',
	c_BookPreflightReport = 'B4PR',
	c_FontDescription	=	'S4FO',
	c_FontDescriptions	=	'S4FS',
	c_LinkDescription	=	'S4LI',
	c_LinkDescriptions	=	'S4LS',
	c_InkDescription	=	'S4IN',
	c_InkDescriptions	=	'S4IS',
	c_JobTicket	=	'S4JT',
	c_ICCProfile	=	'prof',	//-- defined in ColorSync 2.5

	//	Basil preflight
	c_PreflightRule				= 'PFNR',
	c_PreflightRules			= 'PFRS',
	c_ScriptPreflightRule		= 'PFSR',
	c_ScriptPreflightRules		= 'PRSS',
	c_PreflightRuleDataObject	= 'PFRD',
	c_PreflightRuleDataObjects	= 'PFDS',
	c_PreflightProfileRule		= 'PFPR',
	c_PreflightProfileRules		= 'PPRS',
	c_PreflightRuleInstance		= 'PFRI',
	c_PreflightRuleInstances	= 'PFIS',
	c_PreflightScriptRuleInstance	= 'PSRI',
	c_PreflightScriptRuleInstances	= 'PSRS',
	c_PreflightProfile				= 'PLPF',
	c_PreflightProfiles				= 'PLPS',
	c_MemoryPreflightProfile		= 'PMPF',
	c_MemoryPreflightProfiles		= 'PMPS',
	c_PreflightProcess				= 'PrP1',
	c_PreflightProcesses			= 'PrPS',
	c_PreflightProcessTask			= 'PrT1',
	c_PreflightProcessTasks			= 'PrTS',
	c_PreflightRuleResult			= 'PVRt',
	c_PreflightOptions				= 'PFOp',
	c_PreflightBookOptions			= 'FPBO',

	// HighLevel UI
	c_Dialog			=	'uiDL',
	c_Dialogs			=	'uDLs',
	c_Widget			=	'uiWd',
	c_Widgets			=	'uWds',
	c_TextEditbox		=	'utxE',
	c_TextEditboxes		=	'utEs',
	c_IntEditbox		=	'uInE',
	c_IntEditboxes		=	'uIEs',
	c_StaticText		=	'uiSt',
	c_StaticTexts		=	'uSts',
	c_DropDown			=	'uiDD',
	c_DropDowns			=	'uDDs',
	c_Checkbox			=	'uiCb',
	c_Checkboxes		=	'uCbs',
	c_RadioButtonGroup	=	'uRBG',
	c_RadioButtonGroups	=	'uRGs',
	c_RadioButtonControl	=	'uiRB',
	c_RadioButtonControls	=	'uRBs',
	c_IntCombobox			=	'uCIn',
	c_IntComboboxes			=	'uCIs',
	c_EnablingCheckboxPanel	=	'uECP',
	c_EnablingCheckboxPanels	=	'uECs',
	c_ColumnWidget				=	'uiCW',
	c_ColumnWidgets				=	'uCWs',
	c_RowWidget					=	'uiRW',
	c_RowWidgets				=	'uRWs',
	c_AngleCombobox				=	'uCAn',
	c_AngleComboboxes			=	'uCAs',
	c_PercentCombobox			=	'uCPc',
	c_PercentComboboxes			=	'uCPs',
	c_PercentEditbox			=	'uEPc',
	c_PercentEditboxes			=	'uEPs',
	c_AngleEditbox				=	'uEAn',
	c_AngleEditboxes			=	'uEAs',
	c_RealEditbox				=	'uERl',
	c_RealEditboxes				=	'uERs',
	c_RealCombobox				=	'uCRn',
	c_RealComboboxes			=	'uCRs',
	c_MeasureCombobox			=	'uCMu',
	c_MeasureComboboxes			=	'uCMs',
	c_MeasureEditbox			=	'uEMu',
	c_MeasureEditboxes			=	'uEMs',
	c_BorderPanel				=	'uBdP',
	c_BorderPanels				=	'uBPs',

	//Text on a path
	c_TOP						=	'cTOP',
	c_TOPs						=	'TOPs',

	c_GeneralPrefs				=	'cGPr',
	c_ClipboardPrefs			=	'cCPr',
	c_TransformPrefs			=	'cTPr',
	c_ScriptPrefs				=	'cScr',
	c_ScriptArgs				=	'cScp',

	c_StrokeStyle				=	'StSt',
	c_StrokeStyles				=	'StSs',
	c_DashStrokeStyle			=	'DaSt',
	c_DashStrokeStyles			=	'DaSs',
	c_DotStrokeStyle			=	'DoSt',
	c_DotStrokeStyles			=	'DoSs',
	c_StripeStrokeStyle			=	'SpSt',
	c_StripeStrokeStyles		=	'SpSs',

	c_MixedInk					=	'MxSw',
	c_MixedInks					=	'MxSs',
	c_MixedInkGroup				=	'MxSg',
	c_MixedInkGroups			=	'MxGs',

	// object styles
	c_ObjectStyle              	=	'ObSt',
	c_ObjectStyles             	=	'ObSs',
	c_ObjectStyleGroup			=	'Obsg',
	c_ObjectStyleGroups			=	'Obgs',
	c_RootObjectStyleGroup		=	'obrg',
	c_ObjStyleXPPageItemSettingsCategory	=	'ospc',
	c_ObjStyleXPStrokeSettingsCategory		=	'ossc',
	c_ObjStyleXPFillSettingsCategory		=	'osfc',
	c_ObjStyleXPContentSettingsCategory		=	'oscc',
	c_ObjectStyleExportTagMap				=	'oset',
	c_ObjectStyleExportTagMaps				=	'osts',
	p_AllObjectStyles						=	'Paos',
	p_ClearOverridesWhenApplyingObjectStyle =	'cowa',


	// baseline frame grid
	c_BaselineFrameGridOption =	'BfGo',

	// Text Frame Footnote Options
	c_TextFrameFootnoteOptions = 'TfFo',

	// job bag link
	c_SnippetLink = 'jbsl',
	c_SnippetLinks = 'jbss',
	p_SnippetLink = 'psnl',
	p_JBXLinkInfo = 'jbxl',

	//Style sets
	c_RootParagraphStyleGroup	= 'rpsg',
	//c_RootParagraphStyleGroups	= 'rpgs',
	c_ParagraphStyleGroup		= 'Pset',
	c_ParagraphStyleGroups		= 'Psts',
	c_RootCharacterStyleGroup	= 'rcsg',
	//c_RootCharacterStyleGroups	= 'rcgs',
	c_CharacterStyleGroup		= 'Cset',
	c_CharacterStyleGroups		= 'Csts',

	c_TableStyleGroup		= 'Tgrp',
	c_TableStyleGroups		= 'Tgps',
	c_RootTableStyleGroup	= 'Tsrg',
	c_CellStyleGroup		= 'Fgrp',
	c_CellStyleGroups		= 'Fgps',
	c_RootCellStyleGroup	= 'csgr',

	p_AllTableStyles		= 'Pats',
	p_AllCellStyles			= 'Pacs',

	c_FrameFittingOptions = 'FFop',
	p_FrameFittingOptions = 'pFFo',

	c_ImageDocument		= 'iDoc',
	c_ImageDocuments	= 'iDcs',

	c_PrintBooklet		= 'CPrB',
	p_PrintBooklet		= 'PPrB',

	c_PrintBookletPrintPrefs = 'CPBP',
	p_PrintBookletPrintPrefs = 'PPBP',

	c_TransformMatrix			= 'mtrx',
	c_TransformMatrices			= 'mtrc',

	c_SmartGuidePref	= 'cSmt',
	p_SmartGuidePref	= 'pSmt',

	c_MotionPreset	= 'cMpt',
	c_MotionPresets	= 'cMps',
	//c_MotionPresetSettings	= 'cMpS',
	c_Animation		= 'cAnm',
	c_Animations	= 'cAms',
	c_AnimationSettings = 'cAmS',
	p_AnimationSettings = 'pAmS',
	c_TimingSettings = 'cTST',
	p_TimingSettings = 'pTST',
	c_TimingListObject = 'cTmL',
	c_TimingListObjects = 'cTLs',
	c_TimingDataObject = 'cTmD',
	c_TimingDataObjects = 'cTDs',
	c_TimingTargetItem = 'cTmT',
	c_TimingTargetItems = 'cTTs',
	
	// epub and html export
	c_EPubExportPref = 'ebep',
	p_EPubExportPref = 'ebpp',
	c_HTMLExportPref = 'htep',
	p_HTMLExportPref = 'htpp',
	//c_HTMLPGTExportPref = 'hpep',
	//p_HTMLPGTExportPref = 'hppp',
	c_EPubExportFXLPref = 'efep',
	p_EPubExportFXLPref = 	'efxp',
	c_PublishPref		=   'ePep',
	p_PublishPref		=  	'ePxp',

	c_HTMLExportFXLPref = 'hfep',
	p_HTMLExportFXLPref = 'hfpp',

	c_EPubViewingAppsPref = 'EApC',
	e_EPubViewingAppsPref = 'EApM',
	p_EPubViewingAppsPref = 'EApP',

	//p_PublishTitle			= 'pPTi',
	p_PublishExportFormat	= 'pPEf',
	p_DownloadPermission	= 'pPDd',

	p_PublishCover			= 'pPCo',
	p_PublishPageRangeFormat= 'pPRf',
	p_PublishPageRange		= 'pPPr',
	p_PublishFileName		= 'pPfn',
	p_PublishCoverPage		= 'pCoG',
	p_PublishPDFOption		= 'pPPo',

	p_PublishDescription	= 'pPDp',
	en_PublishFormat		= 'pPsf',
	en_Publishcover			= 'EPco',
	p_IsAppSelectedReflow	= 'EASR',
	p_IsAppSelectedFXL		= 'EASX',
	p_AppName				= 'EANp',
	e_AddApp				= 'EAAp',
	e_RemoveApp				= 'ERAp',
	e_CountApp				= 'ECAp',

	e_GetApp				= 'EgAM',
	p_AppIndex				= 'ErmP',

	//shared content
	c_LinkedStoryOptions = 'lsop',
	p_LinkedStoryOptions = 'lspp',

	//Style Mappings
	c_AParaStyleMapping =	'apsm',
	c_ParaStyleMappings =	'pstm',
	c_ACellStyleMapping =	'acsm',
	c_CellStyleMappings =	'csms',
	c_ACharStyleMapping =	'achm',
	c_CharStyleMappings =	'chsm',
	c_ATableStyleMapping =	'atsm',
	c_TableStyleMappings =	'tstm',

	c_SharedContentICC = 'sicc',

	c_LinkedPageItemOptions = 'lpio',
	p_LinkedPageItemOptions = 'lpip',

	// Tagged PDF prefs
	c_TaggedPDFPrefs = 'tPps',

	// Settings in cloud prefs
	c_SettingsInCloudPref = 'SCcc',
	p_SettingsInCloudPref = 'SCpp',
	p_IsSyncEnabled = 'SCse',
	p_WorkspaceSync = 'SCws',
	p_PDFPresetsSync = 'SCps',
	p_KBSCSync = 'SCkt',
	p_GlyphsSync = 'SCgs',
	p_CustMenusSync = 'SCcm',
	en_ConflictResolutionChoice = 'SCec',
	en_ServerWins = 'SCsw',
	en_LocalWins = 'SClw',
	en_AskMe = 'SCam',
	p_ConflictResolutionChoice = 'SCcr',
	e_CreateMissingFontObject = 'cMSF',
	e_GetStyleConflictResolutionStrategy = 'gscr',
	e_TextHasLocalOverrides = 'tHLo',
	e_RemoveFilesFromRecentFiles = 'rMrU',
	c_LayoutAttributeOptions = 'LlOp',
	p_LayoutAttributeOptions = 'plOp',
    p_TransformAttributesX = 'pTaX',
    p_TransformAttributesY = 'pTaY',
    p_TransformAttributesWidth = 'pTaW',
    p_TransformAttributesHeight= 'pTaH',
	p_TransformLeftRefPoint = 'tLRp',
	p_TransformTopRefPoint = 'tTrP',
    p_TransformAttrRefAnchorPoint = 'tARa',
	p_ObjStylesTransformCategory = 'oXFc',
	e_getUserChoiceForCloudTextAddition = 'uCTA',
	en_TextFrameText = 'eTFT',
	en_CompleteStory = 'eCSt',
	en_ThreadedTextFrameTextOptions = 'TTFT'
};

// Event IDs
enum ScriptEvents
{
	e_Activate =			'actv',	// kAEActivate in AERegistry.h
	e_Quit =				'quit',	// kAEQuitApplication in AppleEvents.h
    e_Recover =             'rcvr', // Special recovery method used internally
	e_Open =				'odoc',	// kAEOpen in AERegistry.h
	e_Print =				'pdoc',	// kAEPrint in AERegistry.h
	e_OpenApp =				'oapp',	// kAEOpenApplication in AppleEvents.h
	e_GetDescription =		'gdte',	// kGetAETE in ASRegistry.h
	e_Close =				'clos',	// kAEClose in AERegistry.h
	e_Create =				'crel',	// kAECreateElement in AERegistry.h
	e_Save =				'save',	// kAESave
	e_SaveACopy =			'savc',
	e_Count =				'cnte',	// kAECountElements
	e_Move =				'move',	// kAEMove
	e_Delete =				'delo',	// kAEDelete
	e_ForceDelete =			'fdel',
	e_Duplicate =			'dupe',
	e_Merge =				'merg',
	e_Unmerge = 			'umrg',
	e_Rotate =				'kdrt',	// keyAEDoRotatein AERegistry .h
	e_Resize = 				'scal',	// keyAEDoScalein AERegistry .h
	e_Shear = 				'Sher',
	e_ChangeBounds = 		'tlbr',
	e_Transform = 			'xfrm',
	e_ResolveLocation = 	'wher',
	e_TransformProperty = 	'xfva',
	e_GeometryProperty = 	'bnds',
	e_MatrixScale =			'xfsc',
	  p_MatrixScaleX =		'xfsx',
	  p_MatrixScaleY =		'xfsy',
	e_MatrixSkew =			'xfsk',
	  p_MatrixSkewAngle =	'xfka',
	  p_MatrixSkewSlope =	'xfkm',
	e_MatrixRotate =		'xfro',
	  p_MatrixRotateAngle = 'xfra',
	  p_MatrixRotateCosine ='xfrc',
	  p_MatrixRotateSine =	'xfrs',
	e_MatrixTranslate =		'xftr',
	  p_MatrixTranslateX =	'xftx',
	  p_MatrixTranslateY =	'xfty',
	e_MatrixCatenate =		'xfmu',
	  p_MatrixCatenate =	'xfmm',
	e_MatrixInverse =		'mInv',
	e_MatrixApply =			'ptop',
	  p_XYPoint =			'ptpt',

	e_Place =				'plac',
	e_PlaceCloudAsset =		'plcc',
	e_Update =				'updt',	// kAEUpdatein AERegistry .h
	e_Restore =				'rstr',
	e_Relink =				'rlnk', // Need to differentiate from Window restore
	e_Unembed =				'uneb',
	e_Unlink =				'unlk',
	e_CopyLink =			'cplk',
	e_Override =			'ovrr',
	e_RemoveOverride =		'rmov',
	e_Detach =				'dtch',
	e_Show =				'show',	// keyAEShowWhere in AERegistry .h
	e_EditOriginal =		'edto',
	e_GoToSource =			'gosr',
	e_RevealInOS =			'rvlO',
	e_RevealInBrowser =		'rvlB',
	e_Append =				'Apnd',
	e_Cut = 				'cut ',	// kAECut in AERegistry.h
	e_Copy = 				'copy',	// kAECopy in AERegistry.h
	e_Paste = 				'past',	// kAEPaste in AERegistry.h
	e_PasteUnformatted =	'pauf',
	e_PasteInto =			'pasu',
	e_PasteInPlace =		'PsPl',
	e_Send = 				'send',
	e_Trace = 				'trac',
	e_Group = 				'egrp',
	e_Ungroup =				'ugrp',
	e_TransformGroupContents = 'uxfm',
	e_ResetScaling =		'rxfm',
	e_ClearTransformations = 'cxfm',
	e_ScaleTextAttributes = 'satr',
	e_RedefineScaling =		'pshs',
	e_Flip = 				'flip',
	e_ZoomTo =				'zmto',
	e_Tile =				'tile',
	e_GetSelectedPageItemsToExport = 'gspe',
	e_Cascade =				'casc',
	e_BringToFront =		'btfr',
	e_BringForward =		'brfr',
	e_SendBackward =		'snbw',
	e_SendToBack =			'snbk',
	e_Maximize =			'maxi',
	e_Minimize =			'mini',
	e_Undo = 				'undo',
	e_Redo = 				'redo',
	e_CreateGuides = 		'crgd',
	e_Select = 				'selt',
	e_AsynchronousExport =  'exAs',
	e_Export =				'expt',
	e_ExportPresets =		'ExPs',
	e_Import =				'impt',
	e_ImportStyles =		'imST',
	e_ImportXRefFormats =	'imXF',
	e_UpdateXRefs = 		'udxr',
	e_IsConnected =         'iscn',
	e_Logout =              'logt',
	e_CreateTextFragmentLink = 'ctfl',
	e_RelinkTextFragmentLink = 'rtfl',
	e_Reinitlink			=	'rinl',

	e_ExportStrokeStyles =	'exSS',
	  p_StrokeStyleList =		'SSLs',

	e_JoinPath =			'join',
	e_Reverse =				'revr',
	e_ReversePath =			'revP',
	e_FitContent =			'fitc',
	e_ClearFitOptions =		'cfit',
	e_MakeCompoundPath =    'MCPH',
	e_ReleaseCompoundPath = 'RCPH',
	e_IntersectPath =		'ISPH',
	e_UnionPath =			'UNPH',
	e_DifferencePath =		'DFPH',
	e_ReverseDiffPath =		'RDPH',
	e_XorPath =				'XOPH',
	e_ConvertShape =		'COSH',
	e_Remove =				'ReMv',
	e_Search =				'Find',
	e_ApplyStyle =			'ASty',
	e_ApplyParagraphStyle =	'Xaps',
	e_ApplyCharacterStyle =	'Xacs',
	e_ApplyObjectStyle =    'AOsy',
	e_ObjectStyleClearOverrides = 'osco',
	e_ClearOverrides =		'COvr',
	e_ReleaseAnchoredObject = 'ReAO',
	e_InsertAnchoredObject = 'InAO',
	e_CheckOTFeature =		'COTF',
	e_Recompose =			'Rcmp',
	e_UpdateFonts =			'UpFn',
	e_FindText =			'FndT',
	e_FindGrep =			'FGrp',
	e_FindGlyph =			'FGph',
	e_FindObject =			'FOjt',
	e_FindColor =			'FClr',
	e_FindTransliterate =	'FTlt',
	e_ChangeText =			'ChgT',
	e_ChangeGrep =			'FCGp',
	e_ChangeGlyph =			'FCGh',
	e_ChangeObject =		'FCOt',
	e_ChangeColor =			'FCCl',
	e_ChangeTransliterate = 'FCTl',
	e_SaveFindChangeQuery = 'FCSq',
	e_LoadFindChangeQuery = 'FCLq',
	e_DeleteFindChangeQuery = 'FCDq',
	e_ExportForWeb = 'expw',
	e_GenerateINXSchema = 'grnc',
	p_PackageFormat = 'pkgf',
	e_Subset = 'ssFn',
	p_Characters =		'ssCs',
	p_FontDestination =		'ssFi',

	// User Interface Preferences
	e_ApplyWorkspace =		'ApWS',
	e_ApplyMenuCust =		'ApMC',
	e_ApplyShortcutSet =	'ApSS',
	e_TogglePanelSystemVisibilty =	'TpsV',

	e_LoadMasters =			'LdMP',
	p_MasterPageConflictResolutionStrategy = 'Mpcr',
	
	// Layout rule options p_LayoutRuleOptions (called rule in scripting, policy in our internal API)
	p_LayoutRule =				'LPol',
	en_LayoutRuleOptions =		'LPOp',
	en_ScaleLayoutRule =		'LPSc',
	en_RecenterLayoutRule =		'LPRc',
	en_GuideBasedLayoutRule =	'LPGB',
	en_ObjectBasedLayoutRule =	'LPOB',
	en_UseMasterLayoutRule =	'LPUM',
	en_PreserveLayoutRule =		'LPPr',

	e_SnapshotLayout			=	'LSnw',
	e_DeleteLayoutSnapshot		=	'LSde',
	e_DeleteAllLayoutSnapshots	=	'LSda',
	
	p_SnapshotBlending					= 'SnBl',
	en_SnapshotBlendingModes				= 'SnMo',
		en_IgnoreLayoutSnapshots			= 'SnIg',
		en_UseNearestLayoutSnapshot			= 'SnNe',
		en_UseLimitedLayoutSnapshotBlending	= 'SnLi',
		en_UseFullLayoutSnapshotBlending	= 'SnFu',

	//should these go in GenericScriptIDs in GenericID.h?
	p_HorizontalConstraints		= 'HoCo',
	p_VerticalConstraints		= 'VeCo',
	en_DimensionConstraints		= 'LPdc',
		en_FixedDimension		= 'DCfi',
		en_FlexibleDimension	= 'DCfl',

	// Create Alternate Layout
	e_CreateAlternateLayout = 'cala',
	p_AlternateSpreadItems = 'casi',
	p_CreateTextStyles =	'cats',
	p_LinkTextStories =		'calt',
	e_DeleteAlternateLayout = 'dala',

	e_LoadSwatches =		'LdSw',
	e_SaveSwatches =		'SvSw',
	p_SwatchList =			'SwLs',

	e_AddSwatchBookSpotColor = 'AAsc',
	e_AddSwatchBookProcessColor = 'AApc',

	//	JBX related
	e_ImportResources =		'imRs',
	p_CreateLink =			'crlk',
	c_JobBag =				'JBXo',
	c_JobBags =				'JBXs',
	e_AddFile =				'aJBX',
	e_RemoveFile =			'rJBX',
	e_Extract =				'exJB',
	e_PackageJobBag =		'pJBX',
	p_Files =				'gfJB',
	p_CopyExternal =		'cxJB',
	p_IsPackage =			'ipJB',
	p_Extracted =			'edJB',
	p_ExtractedFile =		'efJB',
	e_UnPackageUCF =		'SVui',
	e_PackageUCF =			'SVpk',
	p_UCFFile =				'SVif',
	p_SourceFolder =		'SVfo',
	p_MIMEType =			'SVmt',

	e_GetScriptArg = 		'Gtsp',
	e_GetValueScriptArg = 	'Gtsv',
	e_SetScriptArg = 		'Stsp',
	e_SetValueScriptArg = 	'Stsv',
	e_ClearScriptArgs = 	'Clsp',
	e_IsDefinedScriptArg = 'Dfsp',

	e_UDAddWord =			'addw',
	e_UDRemoveWord =		'rmvw',
	e_HEAddException =		'adde',
	e_HERemoveException =	'rmve',

	e_Replace =				'erpl',
	e_Sync =				'sync',
	e_Repaginate =			'rpan',
	e_UpdateNumberingInBook = 'unib',
	e_UpdateAllNumberingInBook = 'uanb',
	e_UpdateXRefsInBook =	'uxrb',
	
	// TOC
	e_CreateTOC =			'eTOC',

	// Indexing
	e_ImportTopics		=	'eIpt',
	e_RemoveUnusedTopics=	'eRut',
	e_Capitalize		=	'eCpI',
	e_Generate			=	'eIDX', // Generate and Place an index instance
	e_ChangeHeaderSet	=	'eChS',

	e_AddUnnamedColors =	'aucl',
	e_ConvertMixedInkProcess = 'cmps',

	e_ColorTransform =		'cltr',

	// Hyperlinks
	e_ShowSource =			'shws',
	e_ShowDestination =		'shwd',
	e_ShowBookmark =		'shbk',
	e_FindHyperlinks =		'fdhl',
	
	// Libraries
	e_Store =				'stor',
	e_PlaceAsset =			'PlAs',

	// MetaData
	e_GetXMPProperty =		'gXMP',
	e_SetXMPProperty =		'sXMP',
	e_CreateContainerProperty = 'Mdci',
	e_CountContainerProperty = 'Mdcc',

	e_Preflight	=	'PRS4',
	e_Package	=	'PAS4',
	e_JSONData =	'JSON',

	// Package For GoLive (PFG)
	e_PackageForWeb	=	'PWEB',
	c_PackageForWebPref	=	'cPWP',
	p_PackageForWebPref =	'pPWP',

	p_PFGUseDTD					= 'PDTD',
	p_PFGIncludeHiddenLayers	= 'PIHL',
	p_PFGEncoding				= 'PEnc',
	p_PFGOriginalImages			= 'POIM',
	p_PFGFormattedImages		= 'PFIM',
	p_PFGMoviesAndSounds		= 'PMnS',
	p_PFGViewPackage			= 'PVwP',

	// track changes
	e_Accept	=			'Acpt',
	e_Reject	=			'Rjct',

	e_ConvertToFrame =		'cvtf',

	e_Destroy = 			'dest',

	e_InsertLabel = 		'inLb',
	e_ExtractLabel = 		'exLb',

	// InCopy Bridge
	e_EditInPlace = 		'bEDT',
	e_Submit = 				'bSUB',
	e_Revert = 				'bREV',
	e_UpdateStory = 		'bUpS',
	e_UpdateDesign =		'bUpD',

	e_StoryEdit =			'STed',

	// IDs for Reserved Words
	e_Scale =				'SCAL',

	e_PublishTerminology =	'PubT',
	e_DoScript =			'dosc',	// kAEDoScript in AERegistry.h
	e_param_doscript_language = 'doLg',
	p_WithArguments =		'wArg',
	p_Arguments =			'pArg',

	e_Rename =				'ernm',

	// graphics server
	e_AddLayer =			'gsAL',
	e_AppendMetadata =		'apMD',
	e_ApplyClipPath =		'aplC',
	e_ApplyVariables =		'aplV',
	e_AssignProfile =		'assV',
	e_AutoContrast =		'autC',
	e_AutoLevels =			'autL',
	e_CanvasSize =			'canS',
	e_CanvasSizeRelative =	'cnSR',
	e_ConvertPDFToRaster =	'pd2r',
	e_ConvertProfile =		'cvtP',
	e_ConvertPSToRaster =	'ps2R',
	e_ConvertRasterToEPS =	'r2ep',
	e_ConvertRasterToPDF =	'r2pd',
	e_ConvertSVGToPDF =		's2pd',
	e_ConvertSVGToRaster =	's2ra',
	e_ConvertTo =			'con2',
	e_CreateMetadata =		'crMD',
	e_Crop =				'crop',
	e_DeleteLayer =			'delL',
	e_ExportMetadata =		'exMD',
	e_Flatten =				'flat',
	e_FlipImage =			'flpI',
	e_ImageInfo =			'iInf',
	e_ImageSize =			'iSiz',
	e_ImportMetadata =		'imMD',
	e_LoadContent =			'lCon',
	e_OptimizeToSize =		'optS',
	e_RegisterMetadataNamespace =	'rgMD',
	e_RemoveMetadata =		'rmMD',
	e_ReplacePixels =		'repP',
	e_ReplaceText =			'repT',
	e_RotateImage =			'rotI',
	e_SaveContent =			'svCo',
	e_SaveOptimized =		'sOpt',
	e_Set =					'set ',
	e_SetFileFormat =		'setF',
	e_SetLayerPosition =	'setL',
	e_SetMetadata =			'stMD',
	e_Trim =				'trim',
	e_UnsharpMask =			'unsh',
	e_OpenImage =			'opnI',
	e_CloseImage =			'cloI',

	p_DestinationFolder =	'fldr',

	// Footnotes
	e_ConvertTextToFootnote	= 'CvtF',
	e_ConvertFootnoteToText	= 'Cvtf',

	// vendor languages
	e_NewDictionaryPath =	'Ndcp',
	e_AddDictionaryPath =	'Adcp',
	e_RemoveDictionaryPath ='Rdcp',

	e_PrintBooklet = 'ePrB',

	// Align and distribute events
	e_AlignItems =			'alGN',
	e_DistributeItems =		'dsBT',

	//	Basil Preflight
#ifdef DEBUG
	e_DebugVisitRule =		'VsRl',
#endif
	e_AddRuleData =			'aPRD',
	e_PreflightWaitForProcess = 'PrWP',
	e_Embed =				'emPF',
	e_LoadPreflightProfile = 'ldPP',
	e_SavePreflightReport = 'svPR',
	r_AutoOpen =			'rAop',
	// ME
	e_ChangeComposer =	'chCo',
	e_ReverseLayout =	'rvLo',

	//	Motion preset
	e_LoadMotionPreset =	'imMP',
	e_PlaceAndLink =		'plli',

#ifdef DEBUG
	e_DumpMotionSWFXML =	'dmSX',
#endif

	// Added for ProjectHello
	e_GetHelloJSONData =	'gHJD',
	e_GetCCXJSONData =	'gCJD',
	
	// Added for CloudLibraries
	e_InvokeColorPicker =					'incp',
	e_CreateThumbnailWithProperties =		'ctwp',
	e_OpenCloudAssetForEdit =				'OCAE',
	e_SetCloudLibraryExportOptions =		'SCLO',
	e_ExportForCloudLibrary =			    'E_CL',
	e_ExportSelectionForCloudLibrary =		'ESCL',
	e_ExportPageItemsSelectionToSnippet =	'EPIS',
	e_ExportPageItemsToSnippet =			'EPSN',
	e_IsUserSharingAppUsageData	=			'usAU',
	e_SetCloudLibraryCollection =			'sCLc',
	e_CreateTemporaryCopy =					'crtc',
	e_CreateStyleThumbnailWithProperties =	'cstp',	
	e_IsAppInTouchMode =				'AITM',
	e_OpenPanel =						'OPNl',
	e_SelectedTextDirection =			'STFd',
    e_EnableDisableWhichDimensionField = 'eDDf',
    e_EnableDisableWhichPositionField = 'eDPf',
    e_AdjustLayout = 'eADL',
	e_PublishArtifact = 'ePAF',
	e_GetArtifact = 'eGAF',
	e_DeleteArtifact = 'eDAF',
	e_UpdateArtifact = 'eUAF',
};

#pragma mark Properties
// Property IDs
enum ScriptProperties
{
	p_Length			= 	'leng', // pLength in ASRegistry.h
	p_Class				= 	'pcls', // pClass in AERegistry.h
	p_ObjectSpecifier	=	'posp',
	p_Properties		=  	'qpro', // keyAEProperties in AERegistry.h
	// Since "offset" is an AppleScript event that has been part of the standard scripting addtions
	// for a long time, we are removing this property and replacing it with specific offset properties
	// like "story offset" and "document offset"
	//p_Offset			= 	'ofse',
	p_Index				= 	'pidx',	// pIndex in AERegistry.h
	p_ScriptLabel		= 	'ptag',
	p_DocItem 			=	'docu',
	p_FullName 			=	'fnam',
	p_Path 				=	'path',
	p_Name 				=	'pnam',	// keyAEName in AERegistry .h
	p_Visible 			=	'pvis',	// pVisible in AERegistry .h
	p_ActiveDoc 		=	'pacd',
	p_ActiveWin 		=	'pacw',
	p_ActiveLayer		=	'pacl',
	p_ActiveSpread 		=	'pacs',
	p_ActivePage 		=	'pacp',
	p_Printable 		=	'prta',
	p_UndoName 			=	'unnm',
	p_RedoName 			=	'renm',
	p_UndoHistory		=	'unhs',
	p_RedoHistory		=	'rehs',
	p_EnableUndo		=	'enUn',
	p_Version			=	'vers', // pVersion in AERegistry.h
	p_Locale			=	'Locl',
	p_EnableRedraw		=	'enRe',
	p_FeatureSet		=	'pfst',
	p_PalettesVisible	=	'Pvis',
	p_UnusedSwatches	=	'unsw',
	p_AllPageItems		= 	'aPgi',
	p_AllGraphics		= 	'aGrf',
	p_PageCount			=	'PagC',
	p_BindingLocation	=	'BnLc',
	p_PageSide			=	'PgSd',
	p_Dimensions		=	'Idim',
	p_PageDescriptor	=	'PgDt',

	p_PageTransitionType		=	'PgTT',
	en_PageTransitionType		=	'ptTy',
//	en_NoPageTransition			=	'ptNo', // using en_None
	en_BlindsPageTransition		=	'ptBl',
	en_BoxPageTransition		=	'ptBx',
	en_CombPageTransition		=	'ptCb',
	en_CoverPageTransition		=	'ptCv',
	en_DissolvePageTransition	=	'ptDs',
	en_FadePageTransition		=	'ptFd',
	en_PageTurnPageTransition	=	'ptPT',
	en_PushPageTransition		=	'ptPs',
	en_SplitPageTransition		=	'ptSp',
	en_UncoverPageTransition	=	'ptUc',
	en_WipePageTransition		=	'ptWp',
	en_ZoomInPageTransition		=	'ptZI',
	en_ZoomOutPageTransition	=	'ptZO',
	p_PageTransitionDirection	=	'PgTD',
	en_PageTransitionDirection	=	'ptDr',
	en_PageTransitionDuration	=	'ptDu',
//	en_Fast						=	'ptFT',	// already en_Fast
//	en_Medium					=	'ptMD',	// already en_Medium
	en_Slow						=	'ptSL',
	en_NotApplicable			=	'ptNA',
//	en_Down						=	'ptDw',	// already en_StateDown
//	en_LeftToRight				=	'ptLf',	// already en_LeftToRightBinding
	en_LeftDown					=	'ptLD',
	en_LeftUp					=	'ptLU',
//	en_RightToLeft				=	'ptRf',	// already en_RightToLeftBinding
	en_RightDown				=	'ptRD',
	en_RightUp					=	'ptRU',
//	en_Up						=	'ptUp', // already en_StateNormal
//	en_In						=	'ptIn',	// already keyASPrepositionIn
	en_Out						=	'ptOt',
//	en_Horizontal				=	'ptHr',	// already en_Horizontal
//	en_Vertical					=	'ptVr',	// already en_Vertical
	en_HorizontalIn				=	'ptHI',
	en_HorizontalOut			=	'ptHO',
	en_VerticalIn				=	'ptVI',
	en_VerticalOut				=	'ptVO',
	p_PageTransitionDuration	=	'PgTA',

	p_XPFlattenerPref	=	'pxfP',

	// Performance Display properties
	p_IgnoreLocalSetting = 'pILS',
	p_DefaultDisplaySetting = 'pDDS',
	p_SaveLocalSetting      = 'pSLS',

	p_DisplaySetting = 	'pDsp',
	p_LocalDisplaySetting = 	'pLDs',
	p_RasterDisplay =	'rasD',
	p_VectorDisplay	=	'vecD',
	p_TransparencyDisplay = 'trnD',
	p_AAliasDisplay	=	'aaDy',
	p_GreekBelowDisplay = 'grkD',

	p_Using				=  	'usng',
	p_PrintDialog		= 	'prno',

	p_WithFindPref		=	'wFnd',
	p_WithChangePref	=	'wChg',

	p_Zoom =				'zoom',
	p_CenterPoint =			'cpnt',
	p_DocWinsOnly =			'dwso',

	p_Left =				'marl',
	p_Top =					'mart',
	p_Right =				'marr',
	p_Bottom =				'marb',
	p_Width =				'wdwh',
	p_Height =				'hght',

	p_Binding =				'BinD',
	p_ContentType =			'cntt',

	p_ID =					'ID  ',	// pID in AERegistry .h
	p_IDs =					'pids',
	p_Parent =				'pare',	// pASParent in ASRegistry.h
	p_File =				'file',	// cFile in AERegistry .h
	p_Modified =			'imod',	// pIsModified in AERegistry .h
	p_Saved =				'isvd',
	p_SaveOptions =			'svop',	// only accessible during the e_Close event
	p_SaveFileType =		'saft',
	p_Locked =				'plck',
	p_Overrideable =		'ovbl',
	p_CollectionEnum =		'cenm',
	p_LayerColor =			'lcol', // Used to be p_UIColor
	p_Opacity =				'opaq',
	p_BaseColor =			'clbs',
	p_ColorModel =			'clmd',
	p_ColorSpace =			'clsp',
	p_ColorSpace0 =			'cls0',
	p_ColorSpace1 =			'cls1',
	p_ColorValue =			'clvl',
    p_ConvertToHSB =        'chsb',
	p_Override =			'ovrd',
	p_OverrideList =		'ovrl',
	p_OverridenPageItem =	'ovrp',
	p_OverridenPageItemProps =	'ovpp',
	p_Editable =			'edbl',
	p_Removable =			'rmbl',
	p_TintValue =			'tntv',
	p_GradientType =		'grdt',
	p_StopColor =			'gcls',
	p_MidPoint =			'mids',
	p_Selection =			'sele',	// pSelection in AERegistry.h
	p_SelectionKeyObject = 	'selk',
	p_SelectedPageItems =	'slpi',
	p_InsertionLocation =	'insw',
	p_Replace =				'rplc', // kAEReplace in AERegistry.h

	p_Bounds =				'pbnd',	//keyAEBounds in AERegistry.h - used by Windows
	p_GeometricBounds =		'gbnd',	//used by pageitems
	p_VisibleBounds =		'vbnd',	//used by pageitems
	p_PointList =			'plst',
	p_ZeroPoint =			'zero',
	p_Island =				'ilnd',
	p_PathType =			'ptyp',
	p_PointType =			'qtyp',
	p_LeftDirPoint =		'ldpt',
	p_RightDirPoint =		'rdpt',
	p_AnchorPoint =			'anch',
	p_ReferencePoint =		'rpnt',

	//Style Mappings
	p_SourceStyleName =				'sosn',
	p_DestStyleName =				'dsnm',
	p_RuleType =					'rutp',
	p_LinkedStoryStyleMappings =	'lssm',


	//Layer options
	p_ShowGuides	=		'sogd',
	p_LockGuides	=		'lkgd',
	p_UI			=		'uilr',
	p_Expendable	=		'exlr',

	// HTML Page Item classes and properties
    c_HTMLItem		=		'cHtM',
    c_HTMLItems		=		'cHts', 
	p_PosterImage	=		'PsTr', 
	p_HTMLContent	=		'pHtM',
	p_FixedDimensions	=	'pfxd',
	p_PackageSubPathToHTML = 'rpth',

	// clipping path properties
	p_ClippingPath		=	'pcpt',
	p_ClippingPathType	=	'cptp',
	p_Invert			=	'invt',
	p_IncludeInsideEdges=	'iied',
	p_RestrictToFrame	=	'rtfr',
	p_UseHighResolutionImage='uhri',
    p_Threshold			=	'thhd',
    p_Tolerance			=	'tlrc',
    p_InsetFrame		=	'isfr',
    p_PSPathNames		=	'ptns',
    p_ACPathNames		=	'acpn',
    p_PathName			=	'ptnm',

	// graphic layer info properties
	p_GraphicLayers		=	'grly',
	p_UpdateLinkOption =	'gulo',
	p_OriginalVisibility =	'orvi',
	p_CurrentVisibility =	'crvi',
	p_SeparatorLayer =		'sepl',
	p_AdjustmentLayer =		'adjl',
	p_FXLayer =				'fxlr',
	p_SectionDividerLayer =	'secd',
	p_HasViewState =		'hvws',
	p_ViewState =			'vwst',
	p_HasExportState =		'hest',
	p_ExportState =			'esta',
	p_HasPrintState =		'hpri',
	p_PrintState =			'pris',

	// graphic layer comp properties
	p_PSDLayerCompApplied =	'plca',

	p_FillColor =			'flcl',
	p_FillTint =			'filt',
	p_LineWeight = 			'lnwt',
	p_LineColor =			'lncl',
	p_LineTint =			'lint',
	p_StrokeType =			'stty',
	p_StrokeCornerAdjustment = 'Scaj',
	p_StrokeDashAndGap = 	'Sdag',
	p_RotationAngle =		'kang',	// keyAEAngle in AERegistry .h
	p_Skew	=				'pskw', // the text skew/false italic property

	p_Rotation = 			'trot',	// typeRotation in AERegistry .h This is a record containing the keyAEAngle and the keyAERotPoint
	p_ShearAngle =			'pShr',
	p_ShearAxisAngle =		'pSra',
	p_HorizontalScale =		'phzs',
	p_VerticalScale =		'pvts',
	p_RotationAngleAbsolute =		'Aang',
	p_ShearAngleAbsolute =			'Askw',
	p_HorizontalScaleAbsolute =		'Ahzs',
	p_VerticalScaleAbsolute =		'Avts',
	p_Ppi =							'pppi',

	// For flip (state) or objects or print settings
	p_Flip =						'RpFp',		// What kind of flip: None/Horizontal/Vertical/Horizontal and Vertical
	p_FlipAbsolute =				'flsa',

	p_ItemGeometry =				'IGeo',
	p_ItemTransform =				'ITra',
	p_MasterPageTransform =			'MPxf',
	p_PathGeometry =				'pgeo',
	p_PathBoundingBox =				'pbbx',
	p_ClippingPathGeometry =		'CGeo',
	p_GraphicBounds =				'GrBd',

	p_RelativeRotation	=			'Rrot',
	p_RelativeScale		=			'Rscl',
	p_RelativeShear		=			'Rshr',

	p_RotateParentRelative	=		'PRrt',
	p_ScaleParentRelative	=		'PRsc',
	p_ShearparentRelative	=		'PRsh',

	p_ShouldTransformContent =		'Sscl', //XFIssue
	p_UseVisibleBound =				'AVsb',
	p_RelativeResize =				'Rrsp',
	p_ResizeImageAsProportionalScale = 'Rims',
	p_ConstrainProportion = 		'Cnpr',

	p_BoundsKind					= 'inky',
	  en_BoundsKinds				= 'edge',
	    en_OuterStrokeBounds		= 'ink1',
	    en_GeometricPathBounds		= 'ink0',
	p_ResizeConstraint				= 'rKep',
	  en_ResizeConstraints			= 'rKVP',
	    en_KeepCurrentValue			= 'KepV',
	    en_KeepCurrentProportions	= 'KepP',
	    en_TallProportions			= 'TalP',
	    en_WideProportions			= 'WidP',
	    en_InverseProportions		= 'InvP',
	p_ResizeMethod					= 'rHow',
	  en_ResizeMethods				= 'rMet',
	    en_AddAdditional			= 'HowP',
	    en_MultiplyBy				= 'HowM',
	    en_ResizeTo					= 'HowE',
	    en_ReshapeArea				= 'HowA',
	    en_ReshapeBorder			= 'HowS',
	p_ResizeIndividually			= 'rPer',
	p_BoundingBoxSpecifier			= 'BoxS',
	p_BoundingBoxCorners			= 'BoxC',
	p_BoundingBoxDimensions			= 'BoxD',
	p_CornerRequest					= 'corn',
	  en_CoordinateSpaces			= 'xyxy',
	    en_PasteboardCoordinates	= 'xypb',
	    en_SpreadCoordinates		= 'xysp',
	    en_ParentCoordinates		= 'xypa',
	    en_InnerCoordinates			= 'xyin',
	    en_PageCoordinates			= 'xypg',
	p_TransformOrigin				= 'zpnt',
	p_UseRulerUnits					= 'seeR',
	p_TransformAction				= 'byto',
	  en_TransformActions			= 'xfbt',
	    en_TransformBy				= 'xfby',
	    en_TransformTo				= 'xfto',
	p_TransformMatrix				= '1xfm',
	p_MatrixContent					= 'mxto',
	  en_MatrixComponents			= 'mxco',
	    en_ScaleContent				= 'grow',
		en_SkewContent				= 'slnt',
		en_RotateContent			= 'spin',
		en_TranslateContent			= 'slip',
	p_MatrixValues					= 'mxab',
		p_MatrixScaleXValue				= 'XGRO',
		p_MatrixScaleYValue				= 'YGRO',
		p_MatrixSkewValue				= 'SLNT',
		p_MatrixRotationValue			= 'SPIN',
		p_MatrixTranslateXValue			= 'SLPX',
		p_MatrixTranslateYValue			= 'SLPY',
		p_MatrixMappingValue			= 'MMAP',

	c_PageItemDefault 			= 'cPID',
	p_PageItemDefault 			= 'pPID',

	p_ItemLayer = 			'pilr',	// for guides and page items
	p_DestinationLayer =	'pdlr',	// for place event
	p_DestinationPage =		'dPge',

	p_ItemAbove =			'ibov',
	p_ItemBelow =			'ibel',

	c_TextWrap =			'ctxw',
	p_TextWrap =			'txwr',
	p_TextWrapType =		'txwt',
	p_TextWrapMode =		'txwm',
	p_TextWrapInset =		'ptwi',
	p_TextWrapInverse =		'ptwv',
	p_TextWrapApplyToMasterPageOnly =	'ptwm',
	p_TextWrapSide =		'ptws',
	p_TextWrapUserModified = 'ptwu',
	c_ContourOptions =		'ccos',
	p_ContourOptions =		'pcos',
	p_ContourOptionsType =	'pcot',
	p_ContourName =			'pcnm',

	p_CornerEffect =			'pcef',
	p_CornerOption =			'pcOp',
	p_CornerRadius =			'pcrd',
	p_CornerOptionTopLeft =		'pcO1',
	p_CornerRadiusTopLeft =		'pcr1',
	p_CornerOptionTopRight =	'pcO2',
	p_CornerRadiusTopRight =	'pcr2',
	p_CornerOptionBottomLeft =	'pcO3',
	p_CornerRadiusBottomLeft =	'pcr3',
	p_CornerOptionBottomRight =	'pcO4',
	p_CornerRadiusBottomRight =	'pcr4',

	p_EndCap =				'endc',
	p_EndJoin =				'endj',
	p_ArrowHeadAlignment =	'awha',
	p_LeftArrowHeadScale =	'lahs',
	p_RightArrowHeadScale =	'rahs',

	p_GradientFillStart =	'pgst',
	p_GradientStrokeStart =	'pgss',
	p_GradientFillLength =	'pgfl',
	p_GradientFillAngle =	'pgfa',
	p_GradientStrokeLength = 'pgsl',
	p_GradientStrokeAngle =	'pgsa',
	p_AllCellGradientAttrList = 'pcgl',
	p_GradientFillHiliteLength =	'gfhl',
	p_GradientFillHiliteAngle =		'gfha',
	p_GradientStrokeHiliteLength =	'gshl',
	p_GradientStrokeHiliteAngle =	'gsha',

	p_MiterLimit =			'mitr',
	p_LeftLineEnd =			'llen',
	p_RightLineEnd =		'rlen',

	p_SpanColumnCount =			'scct',
	p_SpanColumnType =			'scte',
	p_KeepWithPrev =			'kwpv',
	p_SplitColumnInsideGutter =		'scig',
	p_SplitColumnOutsideGutter =		'scog',
	p_SpanColumnMinSpaceBefore =		'scmb',
	p_SpanColumnMinSpaceAfter =		'scma',
	
	p_StrokeOverprint =		'sovp',
	p_Overprint =			'ovpr',
	p_NonPrinting =			'nopr',

	p_Overridden =			'Ovrn',

	p_Actualppi =			'Appi',
	p_Effectiveppi =		'Eppi',
	p_ImageTypeName =		'ImTp',
	p_GraphicProxy =		'GrPr',

	// Section properties
	p_PageNumberStyle =		'pnSt',
	p_SectionPrefix =		'spfx',
	p_ContinueSection =		'SnCt',
	p_IncludeSectionPrefix ='SnPx',
	p_SectionPageNumStart = 'SnPn',
	p_SectionMarker =		'SnMk',
	p_SectionPageStart =	'SnPg',
	p_AppliedSection =		'SnAd',
	p_AppliedAlternateLayout = 'SnNl',
	p_AlternateLayoutLength = 'SnLn',
	p_DocumentOffset =		'DCof',
	p_AlternateLayout =		'SnAl',
	p_Pagination =			'SnAp',
		en_PaginationOption = 'SnAO',
			en_AutoPaginate = 'SnAu',
			en_FromLastPage =	'SnAL',
	p_PaginationMaster =	'SnPm',

	p_PageTrapStyle =		'pgTs',

	//Doc Pref Props
	p_DPNumPages =			'nump',
	p_DPPagesPerSpread =	'ppsd',
	p_MasterTextFrame =		'MsTx',	// Pre CS6 name for this property
	p_DPPrimaryTextFrame =	'PrTx',	// CS6 and later name for this property
	p_DPPageHeight =		'phgt',
	p_DPPageWidth =			'pwdt',
	p_PageOrientation =		'pori',
	p_DPPageSize =			'psiz',
	p_DPPageBinding =		'pbin',
	p_ColumnCount =			'colc',
	p_DPColumnGutter =		'colg',
	p_DPColumnDirection =	'cold',
	p_DPColumnColor = 		'cclr',
	p_DPColumnLocked = 		'clok',
	p_HasCustomColumns =	'hccl',
	p_ColumnsPositions =	'cpos',
	p_DPMarginColor	= 		'mclr',
	p_AllowPagesToShuffle = 'Shfl',
	p_PreserveLayoutWhenShuffling = 'PrSl',
	p_IncludePreview = 		'dprv',
	p_SnippetsUseOriginalLoc = 'suol',
	p_PreviewSize =			'PrSi',
	p_PreviewPages =		'PrPa',
	p_OverprintBlack =		'oprb',
	p_DPBleedInside =		'bldi',
	p_DPBleedOutside =		'bldo',
	p_DPBleedTop =			'bldt',
	p_DPBleedBottom =		'bldb',
	p_DPBleedUniform =		'bldu',
	p_DPSlugInside =		'slgi',
	p_DPSlugOutside =		'slgo',
	p_DPSlugTop =			'slgt',
	p_DPSlugBottom =		'slgb',
	p_DPSlugUniform =		'slgu',
	p_DPStartPageNum =		'spno',

	// General Prefs
	p_GeneralPrefs			= 'gprf',
	p_ClipboardPrefs		= 'cPrf',
	p_PreferStyledTextPaste	= 'gpps',
	p_PreferPDFPaste 		= 'gpdf',
	p_CopyPDFToClipboard 	= 'gcpc',
	p_PreservePDFClipAtQuit 	= 'gpcq',
	p_DPPasteRemembersLayers =	'pmly',
	p_UngroupRemembersLayers = 'umly',
	p_PageNumbering			= 'PGnm',
	p_CompleteFontDownloadGlyphLimit			= 'CfDg',
	p_TemporaryFolder		= 'Tfld',
	p_TransformPrefs		= 'tPrf',
	p_TransformContent		= 'TrCt', //XFIssue
	p_DimensionsInclStroke	= 'DiIn',
	p_TransformationAreTotals = 'TrTo',
	p_ShowContentOffset		= 'COff',
	p_ScaleStrokes			= 'ScSt',
	p_WhenScaling			= 'sHow',
	  en_ScalingMethod		= 'sMet',
	    en_ApplyToContent			= 'sIns',
	    en_AdjustScalingPercentage	= 'sOut',
	p_StrokesScale			= 'kStr',
	p_EffectsScale			= 'kEff',
	p_UseIncomingSpotUponConflictProperty	= 'kUIS',
	p_EnableContentAwareFitProperty = 'kCAF',

	// User interface prefs
	p_ToolTips 				= 'Tips',
	p_ToolsPalette			= 'Tplt',
	p_ToolsPanel			= 'Tpan',
	p_PaletteDrawerPref		= 'Pldr',
	p_AutoRevealPref		= 'ARvl',
	p_ApplicationFramePref	= 'AFra',
	p_AppBarPref			= 'ABar',
	p_OpenAsTabPref			= 'ONew',
	p_ThumbnailPlaceCursorPref = 'thmb',
	p_OpenRecentLengthPref	= 'opre',
	p_ShowObjectDimensionsCursorPref = 'dcrs',
	p_FloatingWindowDockingPref	= 'FDoc',
	p_PatientUserPref		= 'pusr',
	p_ContentGrabberPref		= 'cgra',
	p_LiveCornersPref		= 'livc',
	p_AnchorAdornmentPref	= 'anpf',
p_StockAdornmentPref = 'stpf',
	p_ShowMasterPageOverlayPref	= 'mpop',
	p_ObjectsMoveWithPagePref = 'omwp',
	p_MultiTouchGesturesPref	= 'mtgs',
	p_PreventSelectingLockedItemsPref	= 'psli',
	p_ObjectFrameHighlightingPref = 'ofhp',
	p_ScrollAllWindowsPref =		'scra',
	p_ZoomAllWindowsPref =			'zooa',
	p_DrawProxyOnDragPref = 		'dpOD',
	p_ShowRibbonPref =				'shRB',
	p_EnableCreateLinksPref =		'eClP',
	p_EnableMapStylesPref =			'eMsP',
	p_UseCustomMonitorResPref =		'uCmR',
	p_CustomMonitorResValuePref =	'cMrV',
	p_MainMonitorResValuePref =		'mMrV',
	p_UIBrightnessPref = 'uiBP',
	p_PasteboardColorPref = 'pbCP',
	p_ShowWhatsNewOnStartupPref = 'wnSP',
	p_EnablePublishOnlinePref = 'epOP',
	p_AutoAddSwatchToCCLibrariesPref	=	'aSCL',
	p_AutoAddCharStyleToCCLibrariesPref =	'aCCL',
	p_AutoAddParaStyleToCCLibrariesPref =	'aPCL',
p_ShowEnhancedFileOpenPref = 'sEFO',
p_ShowStartWorkspacePref = 'sSWS',
p_ShowLegacyNewDocDlgPref = 'sLND',
p_PanelTabHeightPref = 'pThP',

	//TextOpt Pref Props
	p_TypographersQuotes 		= 'typq',
	p_ShowHJ 					= 'shhj',
	p_ShowKeeps 				= 'shkp',
	p_ShowGlyphSubstitutions	= 'shsb',
	p_ShowCustomSpacing			= 'shcs',
	p_ShowStylePreviewMode		= 'sspm',
	p_ShowKinsoku				= 'shkk',
	p_JustifyTextWrap 			= 'jwrp',
	p_ZOrderTextWrap			= 'zwrp',
	p_AbutTextToTextWrap		= 'awrp',
	p_ShowInvisibles 			= 'sinv',
	p_AntiAliasType 			= 'aaty',
	p_HiliteMissingFonts 		= 'hlmf',
	p_MMOpticalSize				= 'mmos',
	p_UseParagraphLeading		= 'pled',
	p_SuperScriptSize 			= 'sups',
	p_SuperScriptPosition 		= 'supp',
	p_SubScriptSize 			= 'subs',
	p_SubScriptPosition 		= 'subp',
	p_SmallCap 					= 'Smcp',	// Small cap size percentage
	p_PrimaryWritingDirection 	= 'prwd',
	p_KernKeyIncrement			= 'kkbd',
	p_BaseLineKeyIncrement		= 'bkbd',
	p_LeadingKeyIncrement		= 'lkbd',
	p_ScaleAdjustsTextAttrs		= 'sclt',
	p_LinkTextFiles				= 'gplt',
	p_UseNewVerticalScaling 	= 'Jnvs',
	p_UseCIDMojikumi			= 'Jcid',
	p_UseHalfWidthQuotes		= 'Jquo',
	p_OTPositionalForm 			= 'OTPf',
	p_AutoPageInsert 			= 'apin',
	p_EnableDynamicAutoflow 	= 'dflw',
	p_EnableDynamicPageDeletion = 'ddel',
	p_AutoPageInsertRestrictToMasters = 'aprm',
	p_AutoFlowPreserveRectoVerso = 'afrv',
	p_EnableSynchronousSmartTextReflow = 'essf',
	p_ShapeIndicAndLatinWithHarfbuzz = 'silh',

	// Text Editing Pref Props
	p_DragDropTextInLayout		= 'dndl',
	p_DragDropTextInStory		= 'dnds',
	p_TextClickBehavior			= 'tclk',
	p_SmartCutAndPaste			= 'smrt',
	p_TextClickConversionBehavior = 'tClk',

	c_TypeContextualUIPref		= 'ctCu',
	p_TypeContextualUIPref		= 'tcui',
	p_ShowAlternatesUIPref		= 'saui',
	p_ShowFractionsUIPref		= 'faui',

	// Magnify tool prefs
	p_MagnifyZoomPct				= 'mtzp',
	p_MagnifySize					= 'mtsz',
	p_MagnifyRulers					= 'mtru',

	//Grid Pref Props
	p_GridShown					= 'gsho',
	p_GridSnapTo			 	= 'grto',
	p_GridRelativeOption 		= 'grlo',
	p_HorizGridDivision			= 'Hgdv',
	p_VertGridDivision			= 'Vgdv',
	p_HorizGridSubDivisions		= 'Hgsd',
	p_VertGridSubDivisions		= 'Vgsd',
	p_GridColor 				= 'grdc',
	p_GridsinBack				= 'GrDb',
	p_BaselineShown			 	= 'blsn',
	p_BaselineStart		 		= 'blst',
	p_BaselineDivision			= 'bldv',
	p_BaselineViewLimit			= 'blvl',
	p_BaselineColor 			= 'blcl',

	//Grid relative option's enum values
	en_GridRelativeOptionEnum   = 'ENgr',
	en_GridTopOfPage			= 'ENgt',
	en_GridTopOfMargin			= 'ENgm',

	// Layout Adjustment prefs
	p_EnableLayoutAdjust		= 'EnLA',
	p_LASnapZone				= 'LASZ',
	p_LAAllowGraphicsResize		= 'LAGR',
	p_LAAllowRulerGuidesMove	= 'LAGM',
	p_LAIgnoreRulerGuideAlignments = 'LAGA',
	p_LAIgnoreObjectLayerLocks	= 'LAOL',

	// Adaptive Layout prefs
	p_EnableAdaptiveLayout		= 'pEAL',
	p_ALAdjustLockedObjects		= 'pALO',
	p_ALAdjustFontSizeAndLeading	= 'pAFL',
	p_ALFontSizeLimitation		= 'pFSL',
	p_ALMinimumFontSize			= 'pIFS',
	p_ALMaximumFontSize			= 'pMFS',
	p_EnableAutoAdjustMargins	= 'pAAM',

	//Guide Pref Props
	p_GuidePrefsInBack			= 'gdib',
	p_GuidePrefsShown			= 'gdsh',
	p_GuidePrefsLocked			= 'gdlk',
	p_GuidePrefsSnapTo		 	= 'gdto',
	p_GuidePrefsViewThreshold	= 'gvth',
	p_GuidePrefsColor			= 'gudc',

	//Image Pref Props
	//p_DisplayResolution		 	= 'dres',
	p_StoreInternal				= 'stin',
	p_PreviewResolution			= 'pres',
	p_DisplayAntiAlias			= 'daal',
	p_StorageAlertSize			= 'stas',
	p_ImportAntiAlias			= 'imaa',
	p_CreateClippingFrame		= 'clfr',
	p_ExportFormat				= 'exft',
	p_Format					= 'Mdft',
	p_StyleClashResolutionStrategy	= 'scrs',
	p_AllowAutoEmbedding		= 'embd',
	p_AlphaChannelName			= 'alch',
	p_RelinkBehavior			= 'prlb',

	//Tips Pref Props
	p_TipSetting			 	= 'tset',

	//View Pref Props
	p_SnapToZone			 	= 'sntz',
	p_HorzUnits			 		= 'hunt',
	p_VertUnits			 		= 'vunt',
	p_TypographicUnits			= 'tunt',	// added for CJK 7.Feb.2000 %brycem%
	p_TextSizeUnits				= 'tsnt',	// added for CJK 7.Feb.2000 %brycem%
	p_PrintDialogUnits			= 'pdnt',	// added for CJK 7.Feb.2000 %brycem%
	p_LineUnits					= 'lunt',	// added for CJK 5.Jun.2000 %mvogel%
	p_StrokeUnits				= 'sunt',	// New property name as of Rocket for p_LineUnits
	p_KeyNudgeIncrement			= 'keyn',
	p_PointsPerInch				= 'ptin',
	p_ShowMasterItems		 	= 'smsi',
	p_ShowRulers			 	= 'srul',
	p_ShowFrameEdges		 	= 'sfre',
	p_RulerCoordinateType		= 'RCtp',
	p_HorzCustomPoints			= 'hrcp',
	p_VertCustomPoints			= 'vecp',

	//Dictionary Pref Props
	p_DictComposeUsing			= 'dpcu',
	p_DictMergeUD				= 'dpmu',
	p_DictRecompose				= 'dprc',

	//auto correct Pref Props
	p_AutoCorrect				= 'pacr',
	p_AutoCorrectCapitalizationErrors = 'acce',
	p_AutoCorrectWordPairList	= 'acwp',
	p_MisspelledWord			= 'miss',
	p_CorrectedWord				= 'corr',

	//spelling Pref Props
	p_DynamicSpellCheck			= 'pdsc',
	p_MisspelledWordColorIndex	= 'pmwi',
	p_RepeatedWordColorIndex	= 'prwi',
	p_UncapWordColorIndex		= 'puwi',
	p_UncapSentenceColorIndex	= 'pusi',
	p_CheckMisspelledWords		= 'pcmw',
	p_CheckRepeatedWords		= 'pcrw',
	p_CheckCapitalizeWords		= 'pccw',
	p_CheckCapitalizeSentences	= 'pccs',

	//GPU Performance Prefs
	c_GPUPerformancePref = 'GPUp',
	p_GPUPerformancePref = 'pGPU',
	p_EnableGPUPerformancePref = 'eGPU',
	p_EnableAnimatedZoomPref = 'eAZm',

	//Language Props
	p_LanguageProp				= 'plng',
	p_LangDoubleQuotes			= 'ldqu',
	p_LangSingleQuotes			= 'lsqu',
	p_PrimaryLanguageName		= 'pril',
	p_SubLanguageName			= 'subl',
	p_LangICULocaleName			= 'icul',
	p_UntranslatedName			= 'utln',

	//AutoCorrect Props
	p_MisspelledWords			= 'mzpl',
	p_CorrectedWords			= 'crwd',

	//Language + Vendor Props
	p_LangHyphenationVendor		= 'lhyv',
	p_LangSpellingVendor		= 'lspv',
	p_LangThesaurusVendor		= 'lthv',
	p_DictPathList				= 'dpth',
	p_LangHyphenationVendorList	= 'lhyl',
	p_LangSpellingVendorList	= 'lspl',
	p_LangThesaurusVendorList	= 'lthl',

	// Export PDF properties
	// PDF options panel
	p_SubsetFontsBelow			= 'sFbl',
	p_PDFExportColorSpace		= 'eFcs',	// uses 'enFc' enum
	p_IncludeICCProfiles		= 'iICC',
	p_CropImagesToFrames		= 'ictF',
	p_GenerateThumbnails		= 'gTnl',
	p_OptimizePDF				= 'optF',
	p_ViewPDFAfterExport		= 'vaFe',
	p_ViewJDFAfterExport		= 'vaJe',
	p_IncludeStructure			= 'incS',
	p_AcrobatCompatibilityLevel	= 'AcCL',
	p_DstProfile				= 'DstP',
	p_EffDstProfile				= 'EDPr',
	p_PDFXProfile				= 'XDPr',
	p_EffPDFXProfile			= 'EXDP',
	p_IncludeHyperLinks			= 'inHL',
	p_IncludeBookmarks			= 'inBO',
	p_NonprintingObjects		= 'npOB',
	p_VisibleGuidesGrids		= 'vgBG',
	p_IgnoreSpreadOverrides     = 'igSO',
	p_FlattenerStyle            = 'flST',
	p_ExportIncludeLayers       = 'peil',
	p_ExportLayers				= 'pexl',
	p_ContentToEmbed		    = 'pcte',
	p_CompressionType		    = 'cmty',

	p_PDFExportDisplayTitle		= 'Dstl',
	en_PDFExportDisplayTitleOptions = 'DTop',
	en_DisplayFileName			= 'Dsfn',
	en_DisplayDocumentTitle		= 'Dsdt',

	p_PDFExportLanguagePreference = 'PeLp',
	p_PDFExportAsSinglePages		= 'pEsp',
	p_PDFSinglePagesSuffix			= 'pSps',

	// Compression panel
	p_ColorBitmapSampling		= 'Bcsp',	// uses 'enSm' enum
	p_ColorBitmapSampleDPI		= 'Bcsd',
	p_ColorBitmapCompression	= 'Bccm',	// uses 'enBc' enum
	p_ColorBitmapQuality		= 'Bcql',	// uses 'enCq' enum
	p_GrayScaleBitmapSampling	= 'Bgsp',	// uses 'enSm' enum
	p_GrayScaleBitmapSampleDPI	= 'Bgsd',
	p_GrayScaleBitmapCompression= 'Bgcm',	// uses 'enBc' enum
	p_GrayScaleBitmapQuality	= 'Bgql',	// uses 'enCq' enum
	p_MonoBitmapSampling		= 'Bmsp',	// uses 'enSm' enum
	p_MonoBitmapSampleDPI		= 'Bmsd',
	p_MonoBitmapCompression		= 'Bmcm',	// uses 'enMc' enum
	p_CompressTextLineArt		= 'CmTl',
	p_CompressColorAbove		= 'CmCA',
	p_CompressGrayAbove			= 'CmGA',
	p_CompressMonochromeAbove	= 'CmMA',
	p_ColorTileSize			= 'CmTs',
	p_GrayTileSize			= 'CGTs',

	p_StandardsCompliance		= 'XScp',
	p_OutputCondition			= 'OuCo',
	p_EffOutputCondition		= 'EOCo',
	p_OutputConditionHuman		= 'OuCH',
	p_OCRegistry				= 'OCRe',
	p_EffOCRegistry				= 'EReg',
	p_InteractiveElements		= 'IAEl',
	p_InteractiveElementsOption	= 'IAEo',
	p_InteractivePDFInteractiveElementsOption	= 'IPEo',

	// Pages and Page Marks panel
	p_PDFExReaderSpread			= 'rdsF',
	p_PdfPageMarkOffset			= 'pmof',
	p_PrPageInformationMarks	= 'pifo',	/* bool */		// Prints the filename, page number, current date and time and color separation name.
	p_PrColorBarsMarks			= 'colb',	/* bool */		// Adds small squares of color representing the CMKY inks and tints of gray in 10% increments.
	p_PrPageMarkLineWeight		= 'pmlw',	/* long */		// The line weight of page marks
	p_PdfMarkType				= 'pmMt',	/* EnMT */		// The type of page marks to use
	p_PDFUseDocumentBleed		= 'UDoB',	/* bool */		// Whether to use the document bleed area in the PDF.
	p_IncludeSlug				= 'EISl',	/* bool */		// Whether to include the slug area in the PDF.

	// Security panel	Note that the security prefs are part of the PDF prefs object, but are rather
	// specified during the export method/event. This mimics what the UI does, which is not save the security prefs
	// across exports.
	p_UsePDFSecurity			= 'DFsc',
	p_PDFOpenDocPassword		= 'DFop',
	p_PDFChangeDocPassword		= 'DFcp',
	p_PDFAllowPrint				= 'DFap',
	p_PDFAllowDocChange			= 'DFdc',
	p_PDFAllowCopy				= 'DFac',
	p_PDFAllowNoteFormChange	= 'DFan',
	p_PDFDisallowFormFillIn		= 'DFff',
	p_PDFExtractionForAccessibility	= 'DFea',
	p_PDFDisallowDocumentAssembly	= 'DFda',
	p_PDFDisallowPrintHiRes		= 'DFhi',
	p_PDFDisallowPlaintextMetadata	= 'DFpm',

	// new for interactive PDF
	p_PDFExportMagnification	= 'iPEM',
	p_PDFExportPageLayout		= 'iPPL',
	p_PDFExportOpenInFullScreen	= 'iPof',
	p_PDFExportFlipPages		= 'iPfp',
	p_PDFExportFlipPagesSpeed	= 'iPfs',
	p_InteractivePDFPageTransitionOverride	= 'iPpt',
	p_PDFExportRasterCompression = 'iPrc',
	p_PDFExportJPEGQuality		= 'iPjq',
	p_InteractivePDFUseStructureForTabs = 'iPST',

	// Text Frame specific props
	p_ParentStory =				'strp',
	p_ParentTextFrame = 		'pTxF',
	p_ParentTextFrames = 		'pTxS',
	p_FirstTextFrame =			'ftxf',
	p_LastTextFrame =			'ltxf',
	p_NextTextFrame =			'ntxf',
	p_PreviousTextFrame =		'ptxf',
	p_TextFrameIndex =			'itxf',
	p_Overset =					'OVRF',	// same as Xpress' value for 'box overflows'

	// Text Frame Pref props
	p_TextColumnCount =			'ccnt',
	p_TextColumnGutter =		'clgt',
	p_TextColumnFixedWidth =	'clwd',
	p_UseFixedTextColumnWidth =	'ufcw',
	p_InsetSpacing =			'inst',
	p_FirstBaselineOffsetMetric =		'Fbof',
	p_VerticalJustAlign =		'VJal',
	p_VerticalJustMaxInter =	'VJmi',
	p_IgnoreWrap =				'iwrp',
	p_VerticalJustBalanceColumns = 'VJbl',
	p_UseFlexibleTextColumnWidth = 'urcw',
	p_TextColumnFlexibleWidthMax = 'tcmx',
	// Text frame prefs props for auto sizing
	p_AutoSizeDimension = 'asdi',
	p_AutoSizeRefPoint = 'asrp',
	p_AutoSizeHasMinHeight = 'ashm',
	p_AutoSizeMinHeightValue = 'asmh',
	p_AutoSizeHasMinWidth = 'ashw',
	p_AutoSizeMinWidthValue = 'asmw',
	p_AutoSizeNoLineBreak = 'asnl',

	// anchored object props
	p_AOSpineRelative = 	'AOsr',
	p_AOPosition = 			'AOpt',
	p_AOAnchorPoint = 		'AOwp',
	p_AOXOffset = 			'AOxo',
	p_AOYOffset = 			'AOyo',
	p_AOYOffsetAbove =		'AOya',
	p_AOPinPosition =		'AOpp',
	p_AOLockPosition =		'AOlp',
	p_AOContent = 			'AOct',
	p_AOHeight= 			'AOht',
	p_AOWidth = 			'AOwd',
	p_AOHObject = 			'AOHa',
	p_AOVObject = 			'AOVa',
	p_AOHRelative = 		'AHrl',
	p_AOVRelative =			'AOVr',
	p_AOObjectStyle= 		'AOos',
	p_AOParaStyle = 		'AOps',
	en_AOPositionMode = 	'mAOP',
	en_AOHorizontalMode =	'mAOH',
	en_AOVerticalMode =		'mAVA',
	en_AOVReferenceType=	'mAVR',
	en_AOHReferenceType=	'mAVr',
    
	// Story Pref props
	p_OpticalMarginAlignment =	'omAL',
	p_OpticalMarginBaseSize =	'omBZ',
	p_StoryOrient =				'sorn',
	p_FrameType =				'sgON',
	en_FrameTypes =			'Txfs',
	en_FrameType = 			'Txft',
	en_FrameGrid =				'FGtp',

	// ME
	p_StoryDir	=				'sdir',


	//Text properties - reals
	p_TextSize = 			'ptsz',		// keyAEPointSize in AERegistry .h
	p_AutoLeading = 		'alea',
	p_PairKern = 			'pake',		// Amount to kern
	p_SizeLeading = 		'szld',
	p_BaselineShift =		'bshf',
	p_Tracking =			'trak',
	p_Indent1Line = 		'infl',
	p_IndentBLeft = 		'inbl',
	p_IndentBRight = 	'inbr',
	p_IndentLastRight = 	'inlr',
	p_SpaceBefore = 		'spbe',
    p_SpaceAfter = 			'spaf',
    p_SameParaSpacing = 	'spsp',
    p_WordspaceMin = 		'wsmi',
	p_WordspaceMax = 		'wsma',
	p_WordspaceDes = 		'wsde',
	p_LetterspaceMin = 		'lsmi',
	p_LetterspaceMax = 		'lsma',
	p_LetterspaceDes = 		'lsde',
	p_GlyphscaleMin = 		'gsmi',
	p_GlyphscaleMax = 		'gsma',
	p_GlyphscaleDes = 		'gsde',
	p_ILGShift = 			'ilgs',
	p_HyphenZone = 			'hyzo',
	p_PRAStroke = 			'pras',
	p_PRATint = 			'prat',
	p_PRAGapTint = 			'ragt',
	p_PRAOffset =			'paof',
	p_PRAIndentL = 			'pral',
	p_PRAIndentR = 			'pair',
	p_PRAKeepInFrame = 		'prak',
	p_PRBStroke = 			'prbs',
	p_PRBTint = 			'prbt',
	p_PRBGapTint = 			'rbgt',
	p_PRBOffset = 			'pbop',
	p_PRBIndentL = 			'prbl',
	p_PRBIndentR = 			'pbir',
	p_Ascent =				'pAsc',
	p_Descent =				'pDst',
	p_Baseline =			'pBas',
	p_EndBaseline =			'pEBa',
	p_HorizOffset =			'pHOf',
	p_EndHorizOffset =		'pEHo',
	p_UnderlineTint = 		'ultt',
	p_UnderlineGapTint = 	'ulgt',
	p_StrikeThroughTint = 	'sttt',
	p_StrikeThroughGapTint = 'stgt',
	p_UnderlineOffset = 	'ulos',
	p_StrikeThroughOffset = 'stos',
	p_UnderlineWeight = 	'ulwt',
	p_StrikeThroughWeight = 'stwt',
    
    p_DesignAxes       = 'ndxs',
    p_NthAxisIndex     = 'nxsi',
    p_NthAxisValue     = 'nxsv',
    e_SetNthDesignAxis   =  'sndx',
    e_AddFontDirectory   =  'afdy',
    e_RemoveFontDirectory = 'rfdy',
    p_fontDirectory     = 'fndy',
    p_obfuscate         = 'obfs',
    

	//Text properties - booleans
	p_Ligature = 			'ligt',
	p_FigureStyle = 		'Ofst',
	p_HyphenCap = 			'hypc',
	p_HyphenLast = 			'hylw',
	p_CrossFrameHyphen = 	'hycf',
	p_KeepTogether = 		'kept',
	p_StrikeThru = 			'strk',
	p_NoBreak = 			'nobk',
	p_SnapToBaseline = 		'stbl',
	p_KeepLines = 			'kepl',
	p_PRAOverprint = 		'prao',
	p_PRAGapOverprint = 	'rago',
	p_PRARuleOn = 			'prar',
	p_PRBOverPrint = 		'prbo',
	p_PRBGapOverPrint = 	'rbgo',
	p_PRBOverprint = 		'prb2',
	p_PRBGapOverprint = 	'rbg2',
	p_UnderlineOverprint = 			'ulop',
	p_UnderlineGapOverprint = 		'upgo',
	p_StrikeThroughOverprint = 		'Stvp',
	p_StrikeThroughGapOverprint = 	'stgo',
	p_PRBRuleOn = 			'prbr',
	p_Hyphenation = 		'hyph',
	p_Underline = 			'undr',
	p_AutoQuadding = 		'quad',
	p_IgnoreEdgeAlign = 	'igEA',

	p_OTFOrdinal = 			'OTor',
	p_OTFFraction =			'OTfr',
	p_OTFDiscLig =			'OTdl',
	p_OTFTitling = 			'OTti',
	p_OTFContextAlt =		'OTca',
	p_OTFSwash =			'OTsw',
	p_OTFHistorical = 		'OThi',
	p_OTFSlashZero = 		'OTzr',
	p_OTFStylisticSets = 		'OTss',
	p_OTFMark = 			'OTmk',
	p_OTFLocale = 			'OTlc',

	// ME
	p_OTFOverlapSwash =		'OTol',
	p_OTFStylistAlt =		'OTsy',
	p_OTFJustifAlt = 		'OTja',
	p_OTFStretchedAlt = 	'OTsh',

	//Text properties - int16s
	p_DropCapLines = 		'dcli',
	p_DropCapChars = 		'dcca',
	p_DropCapStyle = 		'dcst',
	p_DropcapDetailMode =	'dcdm',
	p_MinAfter = 			'miaf',
	p_MinBefore = 			'mibe',
	p_ShortestWord = 		'swor',
	p_HyphenLadder = 		'hypl',
	p_KeepWithNext = 		'kwnx',
	p_KeepFirstNLines = 		'kfnl',
	p_KeepLastNLines = 		'klnl',
	p_AlternateChar = 		'altc',

//	p_OTFStylisticAlt =		'OTsa',		use p_OTFStylistAlt
	p_HyphenWeight =		'hypw',
	p_SpecialGlyph = 		'SpGl',

	// Style props
	p_StyleKind = 				'sknd',
	p_StyleName = 				'snam',
	p_BasedOn = 				'basd',
	p_PreviewColor = 			'pclr',
	p_KeyboardShortcut = 		'kbsc',
	p_KeyboardShortcutExtended =	'pKBE',
	p_NextParagraph = 			'nxpa',
	p_Imported = 				'smpt',
	p_StyleNameList =          	'snlt',
	p_ExportType =				'exty',
	p_ExportTagDataTag =		'extt',
	p_ExportTagDataClass =		'extc',
	p_ExportTagDataAttributes =	'exta',
	p_ExportBreakHTMLFileInEPUB = 'exbr',
	p_ExportEmitCSSForStyle =	'exem',
	p_ExportIncludeClassInHTMLForStyle = 'exrj',
	c_StyleExportTagMap =		'setm',
	c_StyleExportTagMaps =		'stms',
	p_StyleUniqueId =			'sUnD',

	//Text properties - enumerators
	p_CapitalizeMode =				'capm',
	p_PositionMode =				'posm',
	p_BalanceRaggedLines =			'bala',
	en_BalanceLinesStyle =			'BlSt',
	en_BalanceLinesOff =			'BlOf',
	en_BalanceLinesVee =			'BlVe',
	en_BalanceLinesEqual =			'BlEq',
	en_BalanceLinesPyramid =		'BlPy',

	p_PairKernMethod = 				'pakm',
	p_ParagraphAlignment = 			'paln',
	p_ParagraphAlignLast =			'pall',
	p_ParagraphAlignSingle =		'pals',
	p_BreakBeforeParagraph =		'pbbp',
	p_RuleAboveWidth =				'rawd',
	p_RuleBelowWidth =				'rbwd',

	p_ProviderHyphenationStyle =	'phys',

	//Text properties - string
	p_TextFont = 			'font', // pFont in AERegistry.h
	p_TextFontStyle = 		'ptfs',
	p_Contents =			'pcnt', // pContents in AERegistry.h
	p_TextCompEngine = 		'ptce',

	// Text properties - specific
	p_RuleAboveColor = 		'rlac',
	p_RuleAboveGapColor = 	'ragc',
	p_RuleBelowColor = 		'rlbc',
	p_RuleBelowGapColor = 	'rbgc',
	p_RuleAboveType =		'patp',
	p_RuleBelowType =		'pbtp',
	p_AppliedCharStyle = 	'crst',
	p_AppliedParaStyle = 	'prst',
	p_StyleOverridden =		'stov',
	p_ClearOverrides =		'clov',
	p_UnderlineColor = 		'ulco',
	p_UnderlineGapColor = 	'ulgc',
	p_UnderlineType	 = 		'ultp',
	p_StrikeThroughColor = 	'stco',
	p_StrikeThroughGapColor = 	'stgc',
	p_StrikeThroughType =	'sttp',

	p_OverrideType = 		'ovtp',

	// Tab stop properties
	p_Alignment =			'tsal',
	p_TabStopPosition =		p_PositionMode,
	p_TabStopAlignChar =	'tsac',
	P_TabStopLeader =		'tsld',
	p_AllTabStops =			'alts',

	p_RunInTriggerExp = 	'rite',
	p_RunInCount =			'rict',
	p_RunInInclusive =		'riic',
	p_RunInLineCount = 		'rilc',
	p_RunInLineRepeat =		'rilr',
	p_RunInGrepExpression = 	'rige',
	p_AllRunInStyles =		'alrs',
	p_AllGrepStyles = 		'algs',
	p_AllLineStyles = 		'alls',
	p_EmptyRunInStyles =	'emrs',
	p_EmptyLineStyles =		'emls',
	p_EmptyGrepStyles =		'emgs',

 	// Polygon specific props
 	p_NumSides = 			'nsid',
 	p_InsetPercentage = 	'istp',

 	// Grabber tool specific props
 	p_GrabberPanning =		'grbp',

	en_PanningTypes =		'ePan',
	en_FullDrawPanning =	'eFuP',
	en_FastDrawPanning =	'eFaP',
	en_NoDrawPanning =		'eNoP',

	// Guide props
	p_Orientation =			'gort',
	p_GuideColor =			'gcol',
	p_Location = 			'loca',
	p_PageIndex =			'pgdx',
	p_GuideIsShort = 		'issh',
	p_GuideViewThreshold = 	'vthr',
	p_GuideType = 			'gutp',
	p_GuideGrowZone = 		'gzon',

	// Guide type and guide type enums
	en_GuideType =			'gtpe',
	en_Ruler =				'gsnp',
	en_Liquid =				'gslc',
	en_Magnetic =			'gmag',
	en_GrowZone =			'gzne',

	// Smart Guide props
	p_SmartAlignObjectEdges = 'sAoE',
	p_SmartAlignObjectCenters = 'sAoC',
	p_SmartDimensions =		'sDim',
	p_SmartSpacing =		'sSpa',

	/* for the create guides event */
	p_NumRows =				'nrws',
	p_NumCols =				'ncls',
	p_RowGutter =			'rowg',
	p_ColGutter =			'cclg',
	p_FitMargins =			'fmar',
	p_RemoveExisting =		'rmex',

	/* for the select event */
	p_ExtendSelection =		'exts',

	p_AsStationery =		'asst',

	// for the creation of groups
	p_GroupItems =			'grpi',

	// PDF place pref properties
	p_PageNumber =			'Pgnb',
	p_PDFPlaceCrop =		'DFcr',
	p_TransparentBkgrd =	'TBkg',

	// Frame Fitting Options
	p_FittingOnEmptyFrame =	'ffit',
	p_FittingAlignment =	'faln',
	p_FittingCropLeft =		'fcrl',
	p_FittingCropTop =		'fcrt',
	p_FittingCropRight =	'fcrr',
	p_FittingCropBottom =	'fcrb',
	p_FittingAutoFit =		'fcaf',

	//	print properties

	// Print dialog
	p_PrStyle 							= 'Rsty',	/* EnPs/TEXT */	// Current style. Either en_Default, en_Custom or a print style name
	p_PrDeviceType						= 'Rpdt',	/* long */		// PostScript or non-PostScript device
	p_PrPrintTo							= 'Rppt',	/* long */		// Print to a printer or file
	p_PrPrinters						= 'Rprs',	/* TEXT */		// A list/array of installed printers
	p_PrPrinter							= 'Rprt',	/* EnPr/TEXT */	// Current printer. Either en_PostScriptFile or a printer name
	p_PrPPDs							= 'Rpds',	/* TEXT */		// A list/array of installed PPDs
	p_PrPPD								= 'ppd ',	/* EnPd/TEXT */	// Current PPD. Either en_DeviceIndependent or a PPD model name
	p_PrPPDFile							= 'ppdf',	/* TEXT */		// Current PPD file name
	p_PrFileName						= 'RpFn',	/* File */		// The file name used when printing to disk
	p_PrPrintToDisk						= 'Rptd',	/* bool */		// Whether to print to disk when printing using a printer
	p_PrPrintRecord						= 'Rppr',	/* TEXT */		// Encoded print record stream
	p_PrResolution						= 'Rpre',	/* fixd */		// Output resolution
	p_PrPDFPassthrough					= 'RpPt',	/* bool */		// PDF Passthrough mode

	// General panel
	p_PrCopies							= 'lwcp',	/* long */		// The number of copies, also defined in LW8.7 scriptable printing AppleScript name: "copies"
	p_PrCollate							= 'lwcl',	/* bool */		// Whether to collate, also defined in LW8.7 scriptable printing AppleScript name: "collating"
	p_PrReverseOrder					= 'Rrvr',	/* bool */		// Whether to print in reverse order
	p_PrPageRange						= 'pcty',	/* prng/TEXT */	// The range of pages to print. Either en_PrintAll or one or more ranges
	p_PrSequence						= 'oeb ',	/* EnSq */		// Print odd pages, print even pages, print both
	p_PrSpreads							= 'Rspd',	/* bool */		// Whether to print spreads
	p_PrPrintMasterPages				= 'Rpmp',	/* bool */		// Whether to print master pages
	p_PrPrintNonPrinting				= 'Rpnp',	/* bool */		// Whether to print nonprinting objects
	p_PrPrintBlankPages					= 'Rblk',	/* bool */		// Whether to print blank pages
	p_PrPrintGuidesGrids				= 'Rpgg',	/* bool */		// Whether to print visible guides and baseline grids

	// Setup panel
	p_PrPaperSizes						= 'Rpss',	/* TEXT */		// A list/array of available paper sizes
	p_PrPaperSize						= 'Rpsz',	/* EnPS/TEXT */	// The paper size. Like the UI, just a shortcut of preset paper width and height
	p_PrPaperSizeRect					= 'RpSR',	/* fixd */		// Paper size rect as an array
	p_PrImageablePaperSizeRect			= 'RpIR',	/* fixd */		// Imageable paper size rect as an array
	p_PrPaperSizeSelector				= 'RpSS',	/* TEXT */		// Encoded paper size selector object
	p_PrPaperHeight						= 'Rpht',	/* EnPZ/fixd */	// The custom paper height. Either en_AutoPaperSize or a value
	p_PrPaperHeightRange				= 'RpHR',	/* fixd */		// Custom paper height range as an array
	p_PrPaperWidth						= 'Rpwd',	/* EnPZ/fixd */	// The custom paper width. Either en_AutoPaperSize or a value
	p_PrPaperWidthRange					= 'RpWR',	/* fixd */		// Custom paper width range as an array
	p_PrPaperOffset						= 'Rpof', 	/* fixd */		// The amount of custom paper offset
	p_PrPaperOffsetRange				= 'RpOR', 	/* fixd */		// Custom paper offset range as an array
	p_PrPaperGap						= 'Rpgp',	/* fixd */		// The amount of custom paper gap
	p_PrPaperTransverse					= 'RpTv',	/* bool */		// Whether to transverse the paper
	p_PrPageOrientation					= 'RpOr',	/* EnPO */		// Whether to print portrait, landscape, reverse portrait or reverse landscape
	p_PrPagePosition					= 'RpCt',	/* EnPP */		// How to position the page in the imageable area: none/centered/center horiz/center vert
	p_PrPrintLayers						= 'RpLR',	/* EnLR */		// Which layers to print: all/visible/visible printable
	p_PrScaleMode						= 'RScm',	/* EnSM */		// How to scale the page
	p_PrScaleWidthPercent				= 'swdp',	/* fixd */		// The percentage of scale to apply to the width of a page when printing
	p_PrScaleHeightPercent				= 'shtp',	/* fixd */		// The percentage of scale to apply to the height of a page when printing
	p_PrScaleProportional				= 'RpSP',	/* bool */		// Whether to scale the width and height proportionally
	p_PrThumbnails						= 'RpTn',	/* bool */		// Whether to print thumbnails
	p_PrThumbnailsPerPage				= 'RpTp',	/* EnTP */		// Thumbnails per page
	p_PrTile							= 'RpTt',	/* bool */		// Whether to tile
	p_PrTilingType						= 'tilt',	/* EnTT */		// The type of tiling: auto/auto justified/manual
	p_PrTilingOverlap					= 'tilo',	/* fixd */		// The amount of tiling overlap for Auto or Auto Justified tiling.

	// Marks & Bleeds panel
	p_PrAllPrintersMarks				= 'apm ',	/* bool */		// Whether to print all types of printer's marks
	p_PrCropMarks						= 'crpm',	/* bool */		// Adds fine horizontal and vertical rules that define where the page should be trimmed.
	p_PrBleedMarks						= 'bldm',	/* bool */		// Adds fine rules that define the amount of extra area to image outside the define page size.
	p_PrRegistrationMarks				= 'regm',	/* bool */		// Adds small 'targets' outside the page area for aligning the different separations.
	p_PrColorBars						= 'colb',	/* bool */		// Adds small squares of color representing the CMKY inks and tints of gray in 10% increments.
	p_PrPageInformation					= 'pifo',	/* bool */		// Prints the filename, page number, current date and time and color separation name.
	p_PrMarkType						= 'RpMt',	/* EnMT */		// The type of page marks to use
	p_PrMarkLineWeight					= 'RpMw',	/* EnMW */		// The line weight of page marks
	p_PrMarkOffset						= 'Rpmo',	/* fixd */		// Amount the page marks are offset from the edge of the defined page size.
	p_PrBleedChain						= 'RpBC',   /* bool */      // Whether the bleed chain is on
	p_PrBleedTop						= 'RpBt',	/* fixd */		// Amount of extra area to image on top of the defined page size.
	p_PrBleedBottom						= 'RpBb',	/* fixd */		// Amount of extra area to image at the bottom of the defined page size.
	p_PrBleedInside						= 'RpBi',	/* fixd */		// Amount of extra area to image on inside of the defined page size.
	p_PrBleedOutside					= 'RpBo',	/* fixd */		// Amount of extra area to image on outside of the defined page size.
	p_PrUseDocumentBleed				= 'RpDB',   /* bool */		// Whether to use the document bleed area to print
	p_PrIncludeSlug						= 'RpIS',   /* bool */      // Whether to include slug area when print

	// Output panel
	p_PrColorOutputMode					= 'RpCm',	/* EnCO */		// The mode of the color output: Composite Gray/Composite RGB/Composite CMYK/Separations/In-RIP Separation
	p_PrTextAsBlack						= 'RpTB',	/* bool */		// Whether to print text as black
	p_PrTrapping						= 'trpe',	/* EnTp */		// What kind of trapping: None/Application built-in/Adobe In-RIP
	p_PrNegative						= 'RpNe',	/* bool */		// Whether to print as negative
	p_PrScreenings						= 'RpSL',	/* TEXT */		// A list/array of available ink screenings in the PPD
	p_PrScreening						= 'RpSc',	/* EnSc/TEXT */	// The ink screening to use
	p_PrSeparationScreening				= 'RpSs',	/* TEXT */		// The separation ink screening to use
	p_PrCompositeScreening				= 'RpCs',	/* TEXT */		// The composite ink screening to use
	p_PrCompositeAngle					= 'RpCA',	/* fixd */		// The angle of the composite gray ink
	p_PrCompositeFrequency				= 'RpCF',	/* fixd */		// The frequency of the composite gray ink
	p_PrPrintCyan						= 'RPCI',	/* bool */		// Whether to print the cyan ink
	p_PrCyanAngle						= 'RCIA',	/* fixd */		// The angle of the cyan ink
	p_PrCyanFrequency					= 'RCIF',	/* fixd */		// The frequency of the cyan ink
	p_PrPrintMagenta					= 'RPMI',	/* bool */		// Whether to print the magenta ink
	p_PrMagentaAngle					= 'RMIA',	/* fixd */		// The angle of the magenta ink
	p_PrMagentaFrequency				= 'RMIF',	/* fixd */		// The frequency of the magenta ink
	p_PrPrintYellow						= 'RPYI',	/* bool */		// Whether to print the yellow ink
	p_PrYellowAngle						= 'RYIA',	/* fixd */		// The angle of the yellow ink
	p_PrYellowFrequency					= 'RYIF',	/* fixd */		// The frequency of the yellow ink
	p_PrPrintBlack						= 'RPBI',	/* bool */		// Whether to print the black ink
	p_PrBlackAngle						= 'RBIA',	/* fixd */		// The angle of the black ink
	p_PrBlackFrequency					= 'RBIF',	/* fixd */		// The frequency of the black ink
	p_PrSpotAngle						= 'RSIA',	/* fixd */		// The angle of spot inks
	p_PrSpotFrequency					= 'RSIF',	/* fixd */		// The frequency of spot inks
	p_PrSimulateOverprint				= 'RpSO',	/* bool */		// Simulate Overprint.

	// Graphics panel
	p_PrSendImageData					= 'simd',	/* EnID */		// Controls how much image data to send to the printer.
	p_PrFontDownloading					= 'fndl',	/* EnFD */		// Control how fonts are downloaded to the printer.
	p_PrDownloadPPDFonts				= 'RpPF',	/* bool */		// Whether to download PPD fonts
	p_PrPSLevel							= 'RpPL',	/* EnPL */		// PostScript level:Level 123/Level 23/Level 3
	p_PrDataFormat						= 'RpDF',	/* EnDF */		// The data format: ASCII/Binary

	// Color Management panel
	p_PrSourceSpace						= 'RCSP',	/* EnSS */		// Either document profile or proof profile
	p_PrProfile							= 'RpPr',	/* EnPf/TEXT */	// The color profile to use
	p_PrCRD								= 'RpCr',	/* EnCr/TEXT */	// The color-rendering dictionary to use
	p_Intent							= 'RCin',	/* ECIn */		// The CMS intent
	p_PreserveColorNumbers				= 'RpCn',	/* bool */		// Preserve color numbers

	// Advanced panel
	p_PrBitmapPrinting					= 'bmpr',	/* bool */		// Whether to use bitmap printing or not.
	p_PrBitmapResolution				= 'bmrz',	/* long */		// The bitmap resolution to use for bitmap printing.
	p_PrOPIImageReplacement				= 'odir',	/* bool */		// Whether to print graphics that are either linked using OPI comments or OPI comments stored in imported EPS files.
	p_PrOmitEPS							= 'omte',	/* bool */		// Replace EPS images with OPI links.
	p_PrOmitPDF							= 'omtp',	/* bool */		// Replace PDF images with OPI links.
	p_PrOmitBitmaps						= 'omtb',	/* bool */		// Replace bitmap images with OPI links.
	p_PrFlattenerStyleName				= 'RpFS',	/* TEXT */		// The transparency flattener style name

	// CMS: Document Properties
	p_PrCMSRGBProfile                   = 'DCrp',   /* TEXT */      // The name of the current rgb profile.
	p_PrCMSRGBProfileList               = 'DCrl',   /* TEXT */      // The list of valid rgb profile names.
	p_PrCMSCMYKProfile                  = 'DCcp',   /* TEXT */      // The name of the current CMYK profile.
	p_PrCMSCMYKProfileList              = 'DCcl',   /* TEXT */      // The list of valid CMYK profiles.
	p_PrCMSSolidColorIntent             = 'DCci',   /* EnRI */      // An enumeration value specifying the intent for solid colors
	p_PrCMSDefaultImageIntent           = 'DCii',   /* EnRI */      // An enumeration value specifying the intent for images
	p_prCMSAfterBlendingIntent          = 'DCbi',   /* EnRI */      // An enumeration value specifying the intent after blending
	p_prCMSIdealizedBlackScreen			= 'DCks',	/* bool */		// True to use idealized CMYK->RGB black conversion, false to use accurate
	p_prCMSIdealizedBlackExport			= 'DCkx',	/* bool */		// True to use idealized CMYK->RGB black conversion, false to use accurate
	p_prCMSUseLABSpotAlts				= 'DCsa',	/* bool */		// True to use accurate spot alts when available, false to use legacy cmyk

	// CMS: Window Properties
	p_PrCMSProofingType                 = 'WCpt',   /* EnPT */      // An enumeration specifying how to proof the document.
	p_PrCMSProofingProfile              = 'WCpp',   /* TEXT */      // A string specifying the current proofing profile.
	p_PrCMSSimulatePaperWhite           = 'WCpw',   /* bool */      // True if white point should be adjusted
	p_PrCMSSimulateInkBlack             = 'WCpb',   /* bool */      // True if black point should be adjusted

	// CMS: Image Properties
	p_PrCMSImageIntent                  = 'ICii',   /* EnRI */      // a rendering intent enumeration value.
	p_PrCMSImageProfileList             = 'ICpl',   /* TEXT */      // an array of strings listing valid profiles for the image.
	p_PrCMSDLItemGrayPolicy             = 'ICpg',   /* Dpie */      // Whether to ignore all profiles, just output intent, or none
	p_PrCMSDLItemRGBPolicy              = 'ICpr',   /* Dpie */      // Whether to ignore all profiles, just output intent, or none
	p_PrCMSDLItemCMYKPolicy             = 'ICpc',   /* Dpie */      // Whether to ignore all profiles, just output intent, or none

	// CMS: ColorSettings properties
	p_prCMSSettingsOn                   = 'CSon',   /* bool */      // whether color mgmt is enabled or not.
	p_prCMSSettingsName                 = 'CSsn',   /* TEXT */      // The name of the color settings file currently selected.
	p_prCMSSettingsPath                 = 'CSpt',   /* TEXT */      // The path of a color settings file to use.
	p_prCMSSettingsList                 = 'CSsl',   /* TEXT */      // The list of names of available settings configurations.
	p_prCMSWorkingSpaceRGB              = 'CSrg',   /* TEXT */      // The name of the working space rgb color profile.
	p_prCMSWorkingSpaceRGBList          = 'CSrl',   /* TEXT */      // The set of valid RGB profiles
	p_prCMSWorkingSpaceCMYK             = 'CScm',   /* TEXT */      // The name of the working space cmyk profile.
	p_prCMSWorkingSpaceCMYKList         = 'CScl',   /* TEXT */      // The set of valid CMYK profiles
	p_prCMSRGBPolicy                    = 'CSrp',   /* EnPo */      // The policy for handling inconsistent profiles
	p_prCMSCMYKPolicy                   = 'CScp',   /* EnPo */      // The policy for handling inconsistent profiles
	p_prCMSMismatchAskWhenOpening       = 'CSmo',   /* bool */      // Whether to ask about color settings when pasting w/ inconsitent profiles.
	p_prCMSMismatchAskWhenPasting       = 'CSmp',   /* bool */      // Whether to ask about color settings when pasting w/ inconsitent profiles.
	p_prCMSMissingAskWhenOpening        = 'CSmi',   /* bool */      // Whether to ask about color settings when pasting w/ missing profile.
	p_prCMSEngine                       = 'CSen',   /* TEXT */      // The name of the color management engine to use.
	p_prCMSEngineList                   = 'CSel',   /* TEXT */      // The set of valid engine names
	p_prCMSBlackPointConversion         = 'CSbp',   /* bool */      // Whether black point is compensated for during conversion.

	//	end print properties

	// user dictionary
	p_UserDictAndWords					= 'andw',	/* TEXT */
	p_UserDictNotWords					= 'notw',	/* TEXT */

	// hyphenation exceptions
	p_HyphExceptionAndWords				= 'andh',	/* TEXT */
	p_HyphExceptionNotWords				= 'noth',	/* TEXT */

	// for the add/remove word/exception events
	p_NotList		 					= 'notl',

	// Find/Change
	p_FindWholeWord						= 'FHWd',
	p_FindCaseSensitive					= 'FCsS',
	p_FindText							= e_FindText,
	p_ChangeText						= e_ChangeText,
	p_FindWhat							= 'FndW',
	p_ChangeTo							= 'Chgo',
	p_ReplacingWith						= 'FRpT',
	p_FindKanaSensitive					= 'FKnS',
	p_FindWidthSensitive				= 'FWdS',
	p_FindIncludeLockedStories			= 'FILS',
	p_FindIncludeLockedLayers			= 'FILL',
	p_IncludeHiddenLayers				= 'FIHL',
	p_IncludeMasterPages				= 'FIMP',
	p_IncludeFootnotes					= 'FIFN',
	p_SearchMode						= 'Fsmd',
	p_SearchBackwards					= 'FSSB',
	p_ObjectType						= 'FOTe',
	p_FCReverseOrder					= p_PrReverseOrder,
	p_QueryName							= 'fcqn',
	p_FindCharacterType					= 'FCTy',
	p_ChangeCharacterType				= 'CCTy',
	p_FindColorTint						= c_Tint,
	p_FindColorTintLowerLimit			= 'FCLL',
	p_FindColorTintUpperLimit			= 'FCUL',
	p_ChangeColorTint					= c_Tint,
	// ME
	p_FindIgnoreKashidas				= 'FIKa',
	p_FindIgnoreDiacritics				= 'FIDi',

	// Properties added for CJK character and paragraph attributes
	// %brycem% 18.Jan.00
	p_CharacterAlignment				='jcal',
	p_Tsume								='tsum',
	p_LeadingAki						='jmbs',
	p_TrailingAki						='jmas',
	p_CharacterRotation					='crot',
	p_Jidori							='jjid',
	p_GlyphForm							='jgfm',
	p_OTFeatureList						='jofl',
	p_ShataiMagnification				='jshp',
	p_ShataiAngle						='jsha',
	p_ShataiAdjustRotation				='jshr',
	p_ShataiAdjustTsume					='jsht',
	p_Tatechuyoko						='jtcy',
	p_TatechuyokoXOffset				='jtax',
	p_TatechuyokoYOffset				='jtay',
	p_AutoTCY							='jatc',
	p_AutoTCYInclRoman					='jatr',
	p_KentenFillColor					='jkfc',
	p_KentenStrokeColor					='jksc',
	p_KentenTint						='jktn',
	p_KentenStrokeTint					='jkst',
	p_KentenWeight						='jkwt',
	p_KentenOverprint					='jkof',
	p_KentenStrokeOverprint				='jkos',
	p_KentenKind						='jktp',
	p_KentenPlacement					='jkpl',
	p_KentenAlignment					='jkal',
	p_KentenPosition					='jkp2',
	p_KentenFont						='jkfn',
	p_KentenFontStyle					='jkfs',
	p_KentenFontSize					='jkfz',
	p_KentenXScale						='jkcm',
	p_KentenYScale						='jkpt',
	p_KentenCustomCharacter				='jkcc',
	p_KentenCharacterSet				='jset',
	p_RubyFlag							='jrfg',
	p_RubyString						='jrsg',
	p_RubyFill							='jrfl',
	p_RubyStroke						='jrsk',
	p_RubyTint							='jrti',
	p_RubyWeight						='jrwt',
	p_RubyOverprintFill					='jrof',
	p_RubyOverprintStroke				='jros',
	p_RubyStrokeTint					='jrst',
	p_RubyFont							='jrfn',
	p_RubyFontStyle						='jrft',
	p_RubyFontSize						='jrfs',
	p_RubyOTPro							='jpro',
	p_RubyXScale						='jrwd',
	p_RubyYScale						='jrpt',
	p_RubyType							='jrtp',
	p_RubyAlignment						='jral',
	p_RubyPosition						='jrpz',
	p_RubyXOffset						='jrxo',
	p_RubyYOffset						='jryo',
	p_GridAlignment						='jgal',
	p_GridAlignFirstLineOnly			='jga1',
	p_GridGyoudori						='jggy',
	p_ParaGyoudori						='jpgd',
	p_KinsokuSet						='jkin',
	p_KinsokuType						='jkit',
	p_KinsokuHangType					='jkht',
	p_BunriKinshi						='jbki',
	p_IdeoSpaceBehavior					='jisb',
	p_WordWrapOff						='jwro',
	p_Mojikumi							='jmoj',
	p_MojikumiUISettings				='jmus',
 	p_Rensuuji							='jren',
	p_RotateSingleByte					='jro1',
	p_RubySpacing						='jrsp',
	p_RubyAutoAlign						='jraa',
	p_RubyOverhang						='jrov',
	p_RubyAutoScaling					='jras',
	p_RubyScalingPercent				='jrsc',
	p_RubyOverhangAmount				='jrva',
	p_RubyAutoTCYNumDigits				='jrtd',
	p_RubyAutoTCYIncludeRoman			='jrtr',
	p_RubyAutoTCYAutoScale				='jrts',
	p_Warichu							='jwar',
	p_WarichuSize						='jwas',
	p_WarichuLines						='jwli',
	p_WarichuLineSpacing				='jwls',
	p_WarichuAlignment					='jwal',
	p_WarichuAutoResizeParen			='jwpr',
	p_WarichuMinCharsAfterBreak			='jmab',
	p_WarichuMinCharsBeforeBreak		='jmbb',
	p_ScaleAffectLineHeight				='jslh',
	p_CJKGridTracking					='jgrt',

	p_DefaultMojikumiTbl1				= 'jm01',
	p_DefaultMojikumiTbl2				= 'jm02',
	p_DefaultMojikumiTbl3				= 'jm03',
	p_DefaultMojikumiTbl4				= 'jm04',
	p_DefaultMojikumiTbl5				= 'jm05',
	p_DefaultMojikumiTbl6				= 'jm06',
	p_DefaultMojikumiTbl7				= 'jm07',
	p_DefaultMojikumiTbl8				= 'jm08',
	p_DefaultMojikumiTbl9				= 'jm09',
	p_DefaultMojikumiTbl10				= 'jm10',
	p_DefaultMojikumiTbl11				= 'jm11',
	p_DefaultMojikumiTbl12				= 'jm12',
	p_DefaultMojikumiTbl13				= 'jm13',
	p_DefaultMojikumiTbl14				= 'jm14',
	p_DefaultMojikumiTbl15				= 'jm15',
	p_DefaultMojikumiTbl16				= 'jm16',

	p_CharacterAki						='Jcak',	// Grid char aki, that is
	p_LineAki							='Jlak',	// Grid line aki, that is

	p_GridView					='Jgdv',

	p_GridLineCount					='Jglc',
	p_GridCharCountLoc				='Jgcc',
	p_GridCharCountSize			='Jgcz',

	p_ShowAllLayoutGrids				='Jgsa',
	p_ShowAllFrameGrids					='Jgsf',
	p_CJKGridMinimumScale				='Jgms',
	p_SnapToLayoutGrid					='Jstp',
	p_LayoutGridColorIndex				='Jgci',
	p_ColorEveryNthCell					='Jcen',
	p_SingleLineColorMode				='Jslc',
	p_ICFMode							='Jicf',
	p_UseCircularCells					='Jucc',
	p_CJKGridShowCharacterCount			='Jscc',

	p_GridStartingPoint					= 'Jgsp',
	p_UseMasterGrid						= 'Jumg',

	p_InlineInput						='jInl',
	p_NativeDigitsPref					='ndPr',

	p_WithGrids							='Jpwg',
	p_PrintLayoutGrids					='Jppg',
	p_PrintFrameGrids					='Jpfg',
	p_PrintText							='Jptx',
	p_PrintPageItems					='Jppi',
	p_LayoutGridStrokeWeight			='Jpgw',
	p_FrameGridStrokeWeight				='Jfgw',

	p_CompositeFontEntrySize			='jcfs',
	p_CompositeFontCustomCharacters		='jcfc',
	p_CompositeFontScaleAdjustment		='jcfa',

	p_LeadingModel						='Jled',

	p_OTFProportionalMetrics			='palt',
	p_OTFHVKana							='hkna',
	p_OTFRomanItalics					='ital',

	// SVG Export properties
	p_SVGExpEmbedImages			= 'svEI',
	p_SVGExpFontSubsetting		= 'svFS',
	p_SVGExpReadersSpreads		= 'svRS',
	p_SVGExpRealPrecision		= 'svRP',
	p_SVGExpRenderingStyle		= 'svRs',
	p_FileEncoding		= 'svFE',
	p_SVGExpStyleFormat			= 'svSF',

	p_Value =  'Xatv',

	// Book Properties
	p_MasterDoc = 'mdoc',
	p_RepaginateOption = 'repg',
	p_InsertBlankPage = 'ibpg',
	p_AutomaticPagination = 'atpg',
	p_StyleGroupName = 'gpsn',
	p_TurnOn = 'tnon',
	p_PageRange = 'pgrg',
	p_AutomaticConversion = 'atcv',
	p_MergeLayers = 'mrgl',
	p_ActiveBook = 'atbk',

	// Book synchronization properties
	p_SyncOptionTOCStyle =		'sotc',
	p_SyncOptionTextVariable =	'sotv',
	p_SyncOptionTableStyle =	'sots',
	p_SyncOptionParagraphStyle ='sops',
	p_SyncOptionCharacterStyle ='socs',
	p_SyncOptionTrapStyle =		'sotr',
	p_SyncOptionMasterPage =	'somp',
	p_SyncOptionObjectStyle =	'soos',
	p_SyncOptionSwatch =		'sosw',
	p_SyncOptionCellStyle =		'soce',
	p_SyncOptionBulletNumberingList = 'sobn',
	p_SyncOptionMojikumiStyle = 'soms',
	p_SyncOptionCompositeFont = 'socf',
	p_SyncOptionKinsokuStyle =	'soks',
	p_SyncOptionNamedGrid =		'song',
	p_SyncOptionConditionalText = 'soct',
	p_SyncOptionStyleMatchingStrategy	= 'sosm', //Uses en_kStyleMatchingStrategyOptions
	p_SyncOptionXReferenceFormat = 'soxf',
	
    en_kStyleMatchingStrategyOptions = 'smse',
    en_MatchStyleFullPath = 'smfp',
    en_MatchStyleName = 'smsn',

	// TOC Style properties
	p_TitleName = 'tlnm',
	p_TitleStyle = 'tlsl',
	p_ReplaceExisting = 'rpxt',
	p_IncludeHidden = 'ichd',
	p_CreateBookmarks = 'crbk',
	p_BookName = 'bknm',
	p_RunIn	= 'runn',
	p_StoryDirection = 'styd',
	p_AppliedTOCStyle = 'ATOC',
	p_MakeTextAnchor = 'mkta',
	p_RemoveForcedLineBreak = 'rflb',

	// TOC Style entry settings
	p_FormatStyle = 'fmsl',
	p_PageNumPos = 'pnmp',
	p_Separator = 'sepr',
	p_SeparatorStyle = 'seps',
	p_SortAlphabet = 'stab',
	p_Level = 'lvel',

	// Indexing properties
	p_IndexCapitalizationOptions = 'ICpO',
	p_IndexOptions			= 'IdxO',
	p_IndexHeaderSet		= 'IdHS',
	p_InstanceList			= 'InLi',
	p_IndexInstance			= 'InTc',

	// Indexing sort option properties
	p_Include				= 'incl',
	p_Priority				= 'prty',
	p_HeaderType			= 'hdty',

	p_ReplaceExistingIndex	= 'ReIx',
	p_IncludeBookDocuments	= 'iBkD',
	p_IncludeHiddenEntries	= 'iHEs',

	// IndexOptions properties
	p_IndexFormat				= 'IdxF',
	p_IncludeSectionHeadings	= 'iSHs',
	p_IncludeEmptyIndexSections	= 'iEiS',
	p_Level1Style				= 'lOst',
	p_Level2Style				= 'lTws',
	p_Level3Style				= 'lThs',
	p_Level4Style				= 'lFst',
	p_SectionHeadingStyle		= 'sHst',
	p_CrossReferenceStyle		= 'crSt',
	p_CrossReferenceTopicStyle	= 'crTS',
	p_FollowingTopicSeparator	= 'ftSp',
	p_BetweenEntriesSeparator	= 'beSp',
	p_PageRangeSeparator		= 'prSp',
	p_BetweenPageNumbersSeparator	= 'pnSp',
	p_BeforeCrossReferenceSeparator	= 'crSp',
	p_EntryEndSeparator				= 'eeSp',
	p_IndexSeparator			= 'IdSp',

	// IndexHeaderSet properties
	p_HeaderSetName				= 'HSnm',
	p_HeaderSetLanguage			= 'HSlg',
	p_HeaderSetHandlerClass		= 'HShc',
	p_HeaderSetGroupValue		= 'HSgv',
	p_HeaderSetGroupOptionValue	= 'HSov',
	p_HeaderSetGroupList		= 'HSgl',

	// Topic/PageReference/CrossReference properties
	p_Topic			= 'Tpic',
	p_SortOrder		= 'SOdr',

	p_PageReferenceType		= 'PrTp',
	p_PageReferenceLimit	= 'PrLm',
	p_PageNumberStyleOverride	= 'StOv',
	p_CrossReferenceType	= 'CrTp',
	p_XRefCustomTypeString	= 'CrLm',
	p_AllTopics				= 'AllT',

	//	Inks properties
	p_InkNeutralDensity			= 'inND',
	p_InkType					= 'inTp',
	p_InkSolidity				= 'inSd',
	p_InkPlateOrder				= 'inPo',
	p_InkIsProcess				= 'inIP',
	p_InkToProcess				= 'inCP',
	p_InkAlias					= 'inAs',
	p_InkFrequency				= 'inFr',
	p_InkAngle					= 'inAn',
	p_InkPrintInk				= 'inPI',

	// Separations preview window settings
	p_SepPrvOPP					= 'xpOP', // note: for backward compatibility
	p_SepPrvMode				= 'spMd', // uses enum en_SepPrvMode
	p_SepPrvInkLimit			= 'spIL',

	// Flattener Settings
	p_FlattenerLevel			= 'fsLl',
	p_FlattenerOverride			= 'fsSo',
	// p_Level already defined
	p_FlattenerFlattenerRes		= 'fsFr',
	p_FlattenerGradientRes		= 'fsGr',
	p_FlattenerUseTextOutlines	= 'fsTo',
	p_FlattenerConvertStrokesToOutlines	= 'fsSf',
	p_FlattenerClipComplexRegions		= 'fsCr',

	//shared content
	p_LinkResourceId						= 'lrid',
	p_LinkedStoryUpdateDuringSave			= 'lsus',
	p_LinkedStoryWarnOnUpdateOfEditedStory	= 'lswu',
	p_LinkedStoryRemoveForcedLineBreaks		= 'lsrf',

	p_SharedContentParentICC = 'picc',
	p_SharedContentTargetICC = 'ticc',
	p_SharedContentLastUpdatedICC = 'licc',
	p_SharedContentUIDMap = 'scum',

	p_LinkedPageItemUpdateDuringSave = 'lpus',
	p_LinkedPageItemWarnOnUpdateOfEditedPageItem = 'lpwu',
	p_LinkedPageItemOverridePathgeometry = 'lppg',
	p_LinkedPageItemOverrideGraphicAttributes = 'lpga',
	p_LinkedPageItemOverrideInteractiveAttributes = 'lpia',
	p_LinkedPageItemOverrideContent = 'lpoc',
	p_LinkedPageItemOverrideOtherAttributes = 'lpoa',


	// Hyperlinks
	p_Hidden						= 'hddn',
	p_HyperlinkSource				= 'hlsc',
	p_HyperlinkDestination			= 'hlds',
	p_HyperlinkDestinationURL		= 'hURL',
	p_HyperlinkDestinationPage		= 'hPag',
	p_HyperlinkDestinationTextItem	= 'hTxt',
	p_HyperlinkDestUniqueKey		= 'hduk',
	p_HyperlinkDestPageSetting		= 'hSet',
	p_HyperlinkViewRectangle		= 'hRct',
	p_HyperlinkZoomPercentage		= 'hZom',
	p_HyperlinkDestinationPageIndex = 'hPin',
	p_DocPath						= 'hDPT',
	p_HyperLinkColor				= 'clr ', // Used to be p_Color

	p_HyperlinkSourceType			= 'hlst',
	p_HyperlinkSourcePageItem		= 'hPgI',
	p_SourceTextItem				= 'hsTx',
	
	p_IndentLevel					= 'bidt',

	// Hyperlink Appearance
	p_Highlight						= 'hHlt',
	p_Style							= 'hSty',

	// Hyperlink Page Destinations
	p_ManualName					= 'mnam',

	// Hyperlink alternate destination type
	p_AlternativeDest = 'alde',

	// x-ref formats
	p_XRefFormat					='xrfm',
	p_Type							='Type',
	p_CustomText					='CtTx',
	p_Delimiter						='Dlmt',
	p_IncludeDelim					='IncD',

	// Library props
	p_AssetType =					'Atyp',
	p_Description =					'pdes',

	// MetaData Pref
		//	MetaData properties
	p_MDTitleName						= 'Mdtn',	// TEXT
	p_MDAuthor							= 'Mdau',	// TEXT
	p_MDJobName							= 'Mdjn',	// TEXT
	p_MDCopyrighted						= 'Mdcr',	// ENUM
	p_MDCopyRightNotice					= 'Mdcn',	// TEXT
	p_MDOwnerURL						= 'Mdou',	// TEXT
	p_MDKeywords						= 'Mdkw',	// TEXT
	p_MDServerURL						= 'Mdsu',	// TEXT
	p_MDAllData							= 'MdAd',	// TEXT
	p_MDFormat							= p_Format,	// TEXT
	p_MDAffectAll						= 'Mdal',	// bool
	p_MDNameSpace						= 'Mdns',	// TEXT
	p_MDPath							= 'Mdpt',	// TEXT
	p_MDValue							= 'Mdvl',	// TEXT
	p_MDCreator							= 'Mdct',	// TEXT

	p_ShowInWindow = 'psiw',

	p_PasteboardBorder = 'PBbr',
	p_PasteboardMargins = 'PBmg',
	p_PasteboardColor = 'PBcr',
	p_PreviewBackgroundColor ='PBbk',
	p_BleedGuideColor =	'PBbc',
	p_SlugGuideColor =	'PBsc',
	p_MatchPreviewToThemeColor = 'PMtc',

	// High Level UI properties
	p_CanCancel 			= 'uiCn',
	p_CheckedState 		= 'uiCS',
	p_WidgetStrings		= 'uiDs',
	p_DropDownIndex 		= 'uiDi',
	p_StaticLabel 			= 'uiSL',
	p_EditContents		= 'uiEC',
	p_RadioButtonIndex		= 'urbi',
	p_MinValue				= 'ebMn',
	p_MaxValue				= 'ebMx',
	p_EditUnits				= 'ebMU',
	p_LargeNudge			= 'eLNa',
	p_SmallNudge			= 'eSNa',
	p_MinWidth				= 'uMnW',
	p_EditValue				= 'uEdV',
	p_StaticAlignment		= 'uiSA',

	en_StaticAlignment		= 'uiAl',

	p_PreventAllFormattingOfText	= 'pAFT',
	p_PreventChangesToTextSpacing	= 'pCTP',
	p_PreventAllUsageOfTextStyles	= 'pUTS',
	p_PreventCreationOfTextStyles	= 'pCTS',
	p_PreventEditingOfTextStyles	= 'pETS',
	p_PreventUsageOfTransparency	= 'pUTr',

	// EPS export preferences
	p_EPSPreview			= 'pEPV',
	p_SpotOverprint			= 'pSOP',
	p_EPSColorSpace			= 'pECS',
	p_EPSFontEmbedding		= 'pFEB',
	p_EPSSpreads			= 'pESD',
	p_EPSSendImageData		= 'pSID',

	// EPS import preferences
	p_EIAddProcessColors	= 'pIAC',
	p_EIDCS				= 'pDCS',
	p_EIReadOPI				= 'pOPI',
	p_EIFrame			= 'pIFR',
	p_EIProxy				= 'pIPX',
	p_EIDisplayRes			= 'pIDR',

	//path type
	p_StartBracket			= 'sbkt',
	p_CenterBracket			= 'cbkt',
	p_EndBracket			= 'ebkt',
	p_PathEffect			= 'effc',
	p_FlipPathEffect		= 'flpe',
	p_TextAlignment			= 'ttln',
	p_PathAlignment			= 'ptln',
	p_PathSpacing			= 'pspc',

	// New page item attributes
	p_GapColor				= 'gapC',
	p_GapTint				= 'gapT',
	p_OverprintGap			= 'gapO',
	p_StrokeAlignment		= 'strA',

	// Stroke style attributes
	p_StrokeStyleType		= 'strT',
	p_DotArray				= 'dotA',
	p_DashArray				= 'dshA',
	p_StripeArray			= 'stpA',

	//	mixed ink swatch creation
	p_MixedInkItems			= 'mxim',
	p_MixedInkInkNames		= 'mxnm',
	p_MixedInkValues		= 'mxtt',
	p_InitialValues			= 'mxiv',
	p_RepeatValues			= 'mxrv',
	p_StepValues			= 'mxsv',

	//	INX only spot related properties
	p_MixedInkSpotColorNames= 'mxsn',
	p_MixedInkSpotColors	= 'mxsp',
	p_AliasSpotColor		= 'assp',
	p_AltColorSpace			= 'atcs',
	p_AltColorValue			= 'atvl',
	p_CreatorID				= 'swID',

	p_SpotColorList         = 'spcl',
	p_AGMBlackBoxType       = 'bbtp',
	p_AGMBlackBoxVersion    = 'pvrs',
	p_AGMBlackBoxMatrix     = 'bbmx',
	p_BinaryBlobEncoding    = 'bben',

	p_ScriptLabelKey		= 'sKey',
	p_ScriptLabelValue		= 'sVal',

	p_CantBeginLineChars		= 'jcbl',
	p_CantEndLineChars			= 'jcel',
	p_HangingPunctuationChars	= 'jhgp',
	p_CantBeSeparatedChars		= 'jcbs',

	p_BasedOnMojikumi			= 'jbsm',
	p_OverrideAkiList			= 'joam',

	p_CurrentScriptProperty		= 'Csct',

	p_DefaultTextFrameObjStyle	= 'dtos',
	p_DefaultObjectStyle		= 'dfos',
	p_DefaultFrameGridObjectStyle = 'dffg',
	p_ObjectStyleFillCategory	= 'obfc',
	p_ObjectStyleStrokeCategory = 'obsc',
	p_ObjectStyleStrokeAndCornerEffectCategory = 'obcc',
	p_ObjectStyleStrokeAndCornerOptionCategory = 'obCc',
	p_ObjectStyleDropShadowAndFeatherCategory  = 'obdc',
	p_ObjectStyleParagraphCategory			   = 'obpc',
	p_ObjectStyleTextFrameGeneralCategory	   = 'obtf',
	p_ObjectStyleTextFrameBaselineCategory	   = 'obbc',
	p_ObjectStyleTextFrameAutoSizeCategory	   = 'obas',
	p_ObjectStyleStoryOptionsCategory          = 'oboc',
	p_ObjectStyleTextWrapAndOthersCategory	   = 'obtw',
	p_ObjectStyleAnchoredObjectOptionsCategory = 'obao',
	p_ObjectStyleFrameFittingOptionsCategory   = 'obff',

	p_ObjStyleXPPageItemSettingsCategory		= 'osps',
	p_ObjStyleXPStrokeSettingsCategory			= 'osss',
	p_ObjStyleXPFillSettingsCategory			= 'osfs',
	p_ObjStyleXPContentSettingsCategory			= 'oscs',
	p_ObjectStyleTransparencyCategory			= 'obtc',
	p_ObjectStyleDropShadowCategory				= 'obds',
	p_ObjectStyleVignetteCategory				= 'obvg',
	p_ObjectStyleInnerShadowCategory			= 'obis',
	p_ObjectStyleOuterGlowCategory				= 'obog',
	p_ObjectStyleInnerGlowCategory				= 'obig',
	p_ObjectStyleBevelEmbossCategory			= 'obbe',
	p_ObjectStyleSatinCategory					= 'obsa',
	p_ObjectStyleDirectionalFeatherCategory		= 'obdf',
	p_ObjectStyleGradientFeatherCategory		= 'obgf',
	p_ObjectStyleExportTaggingCategory			= 'obet',
	p_ObjectStyleObjectExportAltTextCategory     = 'osea',
	p_ObjectStyleObjectExportTaggedPDFCategory  = 'osep',
	p_ObjectStyleObjectExportEPUBCategory       = 'osee',
	p_ObjectStyleTextFrameFootnoteOptionsCategory = 'osfo',
	p_ObjectStyleTextFrameColumnRuleCategory	= 'oscr',

	p_AppliedObjectStyle						= 'aobs',
	p_AppliedGraphicObjectStyle					= 'agos',
	p_AppliedTextObjectStyle					= 'atos',
	p_AppliedGridObjectStyle					= 'aGos',
	p_ClearOverridesThroughRoot					= 'cotr',
	p_ObjectStyleApplyNextParaStyle 			= 'osnp',
	p_FCObjectStyle								= 'fcos',
	// Footnotes
	p_FootnoteOptions						= 'FNoo',
	//p_FootnoteStoryOffset					= 'FNso',
	p_FootnoteTextFrame					= 'FNtf',

	p_FootnoteNumberingStyle 				= 'FNns',
	p_FootnoteStartAt						= 'FNsa',
	p_FootnoteRestartNumbering			= 'FNrn',

	p_FootnoteShowPrefixSuffix			= 'FNps',
	p_FootnotePrefix							= 'FNpr',
	p_FootnoteSuffix						= 'FNsu',

	p_FootnoteApplyParagraphStyle		= 'FNap',
	p_FootnoteApplyCharacterStyle		= 'FNac',

	p_FootnoteApplyMarkerPositioning		= 'FNmp',

	p_FootnoteSeparator 					= 'FNsp',
	p_FootnoteSpaceBetween				= 'FNsb',
	p_FootnoteSpacerHeight				= 'FNsh',
	p_FNFirstBaselineOffsetMetric		= 'FNfm',
	p_FNMinFirstBaselineOffset			= 'FNfo',
	p_FootnoteEOSPlacement				= 'FNpl',
	p_FootnoteNoSplitting					= 'FNds',
	p_FootnoteEnableStraddling           = 'FNes',

	p_FootnoteNewRuleOn					= 'FNn0',
	p_FootnoteNewRuleType				= 'FNty',
	p_FootnoteNewRuleStrokeWeight		= 'FNsw',
	p_FootnoteNewRuleColor 				= 'FNnc',
	p_FootnoteNewRuleGapColor			= 'FNrg',
	p_FootnoteNewRuleTint					= 'FNrt',
	p_FootnoteNewRuleGapTint				= 'FNgt',
	p_FootnoteNewRuleOverprint 			= 'FNnv',
	p_FootnoteNewRuleGapOverprint		= 'FNgo',
	p_FootnoteNewRuleLeftIndent			= 'FNli',
	p_FootnoteNewRuleWidth				= 'FNri',			// was right indent
	p_FootnoteNewRuleOffset				= 'FNro',

	p_FootnoteContinuingRuleOn				= 'FNc0',
	p_FootnoteContinuingRuleType				= 'FNcy',
	p_FootnoteContinuingRuleStrokeWeight	= 'FNcw',
	p_FootnoteContinuingRuleColor 				= 'FNcc',
	p_FootnoteContinuingRuleGapColor			= 'FNcg',
	p_FootnoteContinuingRuleTint				= 'FNct',
	p_FootnoteContinuingRuleGapTint			= 'FNc4',
	p_FootnoteContinuingRuleOverprint 		= 'FNcv',
	p_FootnoteContinuingRuleGapOverprint	= 'FNc3',
	p_FootnoteContinuingRuleLeftIndent		= 'FNci',
	p_FootnoteContinuingRuleWidth				= 'FNcr',			// was right indent
	p_FootnoteContinuingRuleOffset			= 'FNco',

	// baseline frame grid property
	p_BaselineFrameGridOption			= 'BLfg',
	p_UseCustomBaselineGridFlag			= 'BFuc',
	p_BaselineFrameGridStartingOffset	= 'BFso',
	p_BaselineFrameGridRelativeOption	= 'BFro',
	p_BaselineFrameGridIncrement		= 'BFic',
	p_BaselineFrameGridColor			= 'BFcl',

	// Obsolete text frame footnote option property
	p_TextFrameFootnoteOptions = 'TFft',
	p_TextFrameFootnoteOptionsEnableOverrides = 'TFeo',
	p_TextFrameFootnoteOptionsSpanFootnotesAcross = 'TFsf',
	p_TextFrameFootnoteOptionsMinimumSpacing = 'TFms',
	p_TextFrameFootnoteOptionsSpaceBetweenFootnotes = 'TFsb',
	
	// New text frame footnote option property
	p_TFFootnoteOptionsEnableOverrides = 'TFEO',
	p_TFFootnoteOptionsSpanFootnotesAcross = 'TFSF',
	p_TFFootnoteOptionsMinimumSpacing = 'TFMS',
	p_TFFootnoteOptionsSpaceBetweenFootnotes = 'TFSB',

	p_Master =				'pmas',
	p_PrimaryTextFrame =	'ptxt',
	p_PageColor =			'pgcl',
	p_OptionalPage =		'OpPg',
	p_NamePrefix =			'npfx',
	p_NameBase =			'nmbs',

	p_ScriptArgs =			'sprm',

	p_AppModalState = 	'apMS',


	//Style sets
	p_AllParagraphStyles	= 'pAps',
	p_AllCharacterStyles	= 'pAcs',

	// Graphics server properties:
	p_Info =					'info',
	p_GraphicsServerVersion =	'gsVr',
	p_Namespace	=				'gsNS',
	p_Prefix =					'NSPf',
	p_AppendExtension =			'apEx',
	p_EXIF =					'EXIF',
	p_XMP =						'XMP ',
	p_IPTC =					'IPTC',
	p_MetadataProperty =		'metD',
	p_ImageFormat = 			'imFt',
	p_XBase =					'xBas',
	p_YBase =					'yBas',
	p_TrimBasedOn				= 'pTrm',
	p_TrimLeft					= 'tLft',
	p_TrimTop					= 'tTop',
	p_TrimRight					= 'tRgt',
	p_TrimBottom				= 'tBot',
	p_Radius					= 'radi',
	p_Amount					= 'amnt',

	// find/change glyph properties
	p_GlyphID =					'Fgid',
	p_FindGlyphROSFontGroup =	'Fros',

	// Print Booklet properties
	p_PBPrintPreset =			'BPrP',		/* EnPs/TEXT */	// Current style. Either en_Default, en_Custom, en_PBCurrDocSettings, or a print style name
	//p_PBPageRange =				'BPgR',		/* EnBR/TEXT */	// The range of pages to print. Either en_PBPrintAll or one or more ranges
	p_PBBookletType =			'BBTy',		/* EnBT/TEXT */ // Booklet Type. One of en_PB2UpSaddleStitch, en_PB2UpPerfectBound, en_PB2UpConsecutive, en_PB2UpConsecutive, or en_PB2UpConsecutive
	p_PBSpaceBetPages =			'BSBP',		/* fixd */		// Space Between Pages.
	p_PBBleedBetweenPages =		'BBBP',		/* fixd */		// Bleed Between Pages.
	p_PBCreep =					'BCrp',		/* fixd */		// Creep.
	p_PBSignatureSize =			'BSgS',		/* EnBS/TEXT */ // Signature Size. One of en_PBSigSize4, en_PBSigSize8, en_PBSigSize12, en_PBSigSize16, or en_PBSigSize32
	p_TopMargin =				'dmTM',		/* fixd */		// Top Margin
	p_BottomMargin =			'dmBM',		/* fixd */		// Bottom Margin
	p_LeftMargin =				'dmLM',		/* fixd */		// Left Margin
	p_RightMargin =				'dmRM',		/* fixd */		// Right Margin
	p_PBAutoAdjustMargins =		'BAAM',		/* bool */		// Auto adjust margins to fit marks and bleeds
	p_PrintBookletDialog =		'BPBD',		/* bool */		// Show UI
	p_PBChainMargins =			'BChM',		/* bool */		// Chain margins so that all equal the top margin
	p_PBPrintBlankPrinterSpreads = 'BPBS',		/* bool */		// Chain margins so that all equal the top margin

	// TOC Style Entries for Advanced Numbering
	p_TOCNumberedParagraphs	=	'tnup',		// Numbered Paragraphs Property for TOC
	p_StoryType =				'trty',		// enum (en_TOCStory, en_IndexingTOC or en_RegularStory...)
	p_StoryTextContainers =		'stcs',

	p_StoryList = 				'stls',

	// Align and distribute page items properties
	c_AlignDistPref = 			'dDSp',
	p_AlignDistPref = 			'aDSp',

	p_AlignDistributeItemsBounds =		'aDsT',
	p_AlignDistributeItems =			'adIT',
	p_AlignOptions = 					'lGPn',
	p_DistributeOptions = 				'dBOs',
	p_UseAbsoluteDistributeValue = 		'uALv',
	p_AbsoluteDistributeValue = 		'aDSv',
	p_DistributeAbsoluteActive = 		'dBAc',
	p_DistributeAbsoluteValue = 		'dBAv',
	p_DistributeBySpaceBetweenAbsoluteActive = 'dSBa',
	p_DistributeBySpaceBetweenAbsoluteValue = 'dSBv',

	// user text
	p_UserText = 'usrt', 

	// anirudh, fix for bug# 1206196.
	// Export Book Parameter.
	p_BookExportDocs =			'bewd',	//One or more files indicating Docs of the Book to be exported.

	// Window management

	// ME
	p_TileOrientation =			'wtor',
	p_KeyboardDirection		=	'kdir',

	p_CharacterDirection		=	'cdir',
	p_Digits					=	'digi',
	p_Kashidas				=	'kash',
	p_DiacriticPosition		=	'diap',
	p_DiacriticXOffset		=	'diax',
	p_DiacriticYOffset		=	'diay',

	p_ParagraphDirection	=	'pdir',
	p_ParagraphJustification	=	'pjus',
	p_ParagraphKashidaWidth	=	'pkas',

	//	Basil preflight properties
	//p_RuleID			= 'ruID',	//	We now use default scriptID, p_ID
	//p_RuleDescription	= 'ruDt',	//	We now use default scriptID, p_Description
	p_RulePluginDescription	= 'ruPD',
	p_RuleObjectTypes	= 'ruOT',
	p_RuleAlertStatus	= 'ruAs',
	p_RuleCanFixup		= 'ruCF',	//	Might not need this.
	p_RuleIsFullFeature	= 'ruFF',	//	Might not need this.
	p_RuleCheckHandler	= 'ruCk',
	p_RuleFixupHandler	= 'ruFp',
	p_RuleUIHandler		= 'ruUI',
	p_RuleVisitObject	= 'ruVO',
	p_PreflightRuleResult	= 'rsVS',
	p_RuleVisitResultCode	= 'ruSC',
	p_RuleVisitResultDescription = 'ruSD',
	p_RuleDataType		= 'ruDT',
	p_RuleDataValue		= 'ruDV',
	p_PreflightProcessTarget	= 'PFTt',
	p_PreflightDocActiveProcess	= 'PDAp',
	p_PreflightAggResult	= 'PAgR',
	p_PreflightProfile		= 'PFPr',
	p_PreflightAllObjectTypes = 'PFAO',
	p_PreflightAllRuleCategories = 'PFAC',
	p_PreflightAllRuleIDs	= 'PFAR',
	p_PreflightResults		= 'PprR',
	p_PreflightInventory	= 'PprI',
	p_PreflightWaitTime		= 'PfWT',
	p_PreflightOptions		= 'pfOp',
	p_PreflightBookOptions	= 'pfBO',
	p_PreflightScope		= 'pfSc',
	//p_PreflightPageRanges	= 'pfPg',
	p_PreflightLayersOption	= 'pfLy',
	p_PreflightObjsOnPB		= 'pfPB',
	p_PreflightNonPrintObjs	= 'pfNp',
	p_PreflightProfilePolicy= 'pfDc',
	p_PreflightOff			= 'pfOf',
	p_PreflightEmbedNew		= 'pfem',
	p_PreflightWorkingProfile = 'pfWP',

	//	Preflight type def
	t_PreflightErrorInfoType =	'tPIT',
	t_PreflightErrorNodeType =	'tPET',
	t_PreflightResultsType =	'tPRT',
	t_PreflightRuleDataBaseListType = 'tRLB',
	t_PreflightRuleDataListType = 'tRLT',

	p_ProfileDescription= 'prPD',

	// Character attribute on Para CR. Only visible to INX-Alt
	p_GotoNextX			= 'gtnx',

	// PageNumber type
	p_PageNumberType	= 'pgnt',

	p_IDMLComponentName = 'imcn',

	//	Animation
	//p_MotionPresetSettings =	'mpSS',
	p_MotionPreset =			'mpID',
	p_MPEditLocked =			'mpEL',
	p_MPDeleteLocked =			'mpDL',
	p_MPNameLocked =			'mpNL',

	t_AnimationDataPathKeyFrameType = 'tAPt',
	t_AnimationDataKeyFrameType = 'tKFt',
	p_AnimationPreset =			'Amps',
	p_AnimationEaseType =		'AmEz',
	p_AnimationPlays =			'AmPl',
	p_AnimationDuration =		'AmDn',
	p_AnimationTransformOffsets = 'AmTx',
	p_AnimationPath =			'AmPh',
	p_AnimationPathPoints =		'AmPp',
	p_AnimationOpacityArray =	'AmOp',
	p_AnimationRotationArray =	'AmRt', 
	p_AnimationScaleXArray =	'AmSx',
	p_AnimationScaleYArray =	'AmSy', 
	p_AnimationPlaysLoop =		'AmPL',
	p_AnimationDesignOption =	'AmAO',
	p_AnimaitonHideAfter =		'AmHa',
	p_AnimationHasCustom =		'AmCm',

	p_TimingTimeDelay =			'TmDl',
	p_TimingTriggerEvent =		'TgEt',
	p_TimingPosition =			'TgPn',
	p_TimingTarget =			'TgTg',
	p_TimingReverseAnimation =	'TgRA',
	p_UnassignedTargets =		'TgUn',
	p_TimingTargetRole =		'TgTr',
	p_TimingTargetAction =		'TgTa',
#ifdef DEBUG
	p_MotionPresetSWFXML =		'mpSX',
#endif

	// epub and html
	p_IncludeCSSDefinition	=	'ebId',
	p_PreserveLocalOverride =	'eblo',
	p_HTMLExportSelection	=	'htes',
	p_ExportOrder			=	'ebeo',
	p_BulletOption			=	'ebbo',
	p_NumberedListOption	=	'ebno',
	p_CSSOption				=	'ebcs',
	p_IncludeDocMetadata	=	'ebim',
	p_Publisher				=	'ebpb',
	p_ViewDocAfterExport	=	'vdae',
	p_PreserveLayoutAppearence= 'ebla',
	p_IgnorePIImageSettings	=	'ebio',
	p_UseTOCStyle			=	'ebut',
	p_TOCStyleName			=	'ebtn',
	p_BreakDocument			=	'ebbd',
	p_BreakDocParaStyleName	=	'ebpn',
	p_FootnoteAfterParagraph=	'ebfp',
	p_FootnotePlacement		=	'ebft',
	p_StripSoftReturn		=	'ebsr',
	p_EmbedFont				=	'ebef',
	p_ImageExportOption		=	'ebie',
	p_ServerPath			=	'ebsp',
	p_Extension				=	'fext',
	p_LinkToJavascript		=	'eblj',
	p_JavascriptURL			=	'ebju',
	p_MarginUnit			=	'ebmu',
	p_ApplyImageASToAOSettings=	'ebas',
	p_EPubCover				=	'ebco',
	p_CoverImage			=	'ebci',
	p_ExternalCSSPath		=	'ebec',
	p_StyleSheets			=	'ebss',
	p_Javascripts			=	'ebjs',
	p_GenerateCSS			=	'ebgs',
	p_IncludeClassesInHTML =	'ebzs',
	p_OriginalImage			=   'ebuo',
	p_EPubTitle				=	'ebtl',
	p_EPubCreator			=	'ebcr',
	p_EPubDate				=	'ebdt',
	p_EPubDescription		=	'ebds',
	p_EPubRights			=	'ebrg',
	p_EPubSubject			=	'ebsb',
	p_EPubPageRange			=	'erng',
	p_EPubPageRangeFormat	=	'efmt',
	p_EPubNavigationStyle	=	'envg',
	p_EPubSpreadControlOption =	'ecnt',
	p_ExistingImage			=	'ebue',
	// htmlgpt
	//p_CopyStdPGTScript		=	'pgtc',

	// Tagged PDF prefs
	p_TaggedPDFPrefs		=	'pTpP',
	p_PDFStructureOrder		=	'pPSo',

	// Active user's AdobeID and GUID
	p_UserAdobeID			=	'pUAI',
	p_UserGUID				=	'pGID',
    
	// Added for CloudLibraries
	p_SampleText			=	'pstx',
	p_CloudLibraryCollectionInfo =	'pcLC',
	p_CCAssetType = 'c_AT',

	// 
	p_SwatchColorMember = 'pscm',
    p_whichAttributes = 'pWDa',
    p_attributeState =  'PaTr',
	p_AdoptTo = 'PadT',
	p_PagesAffected = 'PpfT',

	// text frame vertical column rule option property
	p_TFVerticalRuleEnableOverrides = 'VREo',
	p_TFVerticalRuleOffset = 'VROf',
	p_TFVerticalRuleTopInset = 'VRTi',
	p_TFVerticalRuleInsetChainOverrides = 'VRIc',
	p_TFVerticalRuleBottomInset = 'VRBi',
	p_TFVerticalRuleWidth = 'VRWi',
	p_TFVerticalRuleStrokeColor = 'VRSc',
	p_TFVerticalRuleStrokeType = 'VRTy',
	p_TFVerticalRuleStrokeTint = 'VRSt',
	p_TFVerticalRuleOverprintOverrides = 'VROo',
	p_GetHomeScreenVisibility  = 'GHSv',
};

enum TableDefs
{
	// objects
	c_BaseTableObject =	'TbBs',

	c_Table =			'ctbl',	// cTable in AERegistry.h
	c_Tables =			'Tbls',

	c_Cell =				'ccel',	// cCell in AERegistry.h
	c_Cells = 			'Cels',

	c_TableRow =		'crow',	// cRow in AERegistry.h
	c_TableRows =		'Trws',

	c_TableColumn =	'ccol',	// cColumn in AERegistry.h
	c_TableColumns =	'Tcls',

	c_TableStyle =		'tsty',
	c_TableStyles =		'Tsts',

	// For cell styles
	c_CelSty =			'ccst', // registered with adobe already
	c_CelStys =			'ccsl', // registered with adobe already

	// Events
	e_Redistribute =	'Rdst',
	e_Split =			'Splt',
	e_ConvertToText =	'ToTx',
	e_ConvertToTable =	'ToTb',
	e_ClearCellStyleOverrides =		'CcSO',
	e_ClearTableStyleOverrides =	'CtSO',
	e_ShowText = 		'shtx',

	//For Endnotes
	e_AppendTextInEndnote 						= 'atie',
	e_InsertEndnoteText							= 'ient',
	p_EndnoteOptions							= 'eopp',
	p_EndnoteTitle								= 'ENti',
	p_EndnoteApplyTitleParagraphStyle			= 'ENtp',
	p_EndnoteNumberingStyle						= 'ENns',
	p_EndnoteStartAt							= 'ENsa',
	p_EndnoteRestartNumbering					= 'ENrn',
	p_EndnoteApplyMarkerPositioning				= 'ENmp',
	p_EndnoteApplyMarkerCharacterStyle			= 'ENmc',
	p_EndnoteApplyParagraphStyle				= 'ENap',
	p_EndnoteSeparator							= 'ENsp',
	p_EndnoteScope								= 'ENsv',
	p_EndnoteFrameCreate						= 'ENfc',
	p_EndnoteShowPrefixSuffix					= 'ENps',
	p_EndnotePrefix								= 'ENpr',
	p_EndnoteSuffix								= 'ENsu',
	p_RangeTextItem                             = 'enTx',
	p_EndnoteAnchorObject						= 'enAo',
	p_EndnoteRangeObject						= 'enRo',
	p_IsEndnoteStory							= 'enSt',
	e_CreateEndnote                             = 'cren',
	e_DeleteEndnoteAnchor                       = 'dena',
	e_DeleteEndnoteRange                        = 'denr',
	e_InsertTextInEndnote                       = 'itie',
	p_EndnoteRangeStartIndex                    = 'ensi',
	p_EndnoteRangeEndIndex                      = 'enei',
	p_IsAnEndnoteStory                          = 'iens',
	p_EndnoteRangeContent                       = 'enrc',

	
	// Properties
	// tables
	p_RowCount =			'RwCt',
	p_HeaderRowCount =		'HRCt',
	p_FooterRowCount =		'FRCt',

	// table borders
	p_TopBorderStrokeWeight = 'TBsw',
	p_TopBorderStrokeType = 'TBss',
	p_TopBorderStrokeColor = 'TBsc',
	p_TopBorderStrokeTint = 'TBst',
	p_TopBorderStrokeOverprint = 'TBso',
	p_TopBorderStrokeGapColor = 'TBgc',
	p_TopBorderStrokeGapTint = 'TBgt',
	p_TopBorderStrokeGapOverprint = 'TBgo',

	p_LeftBorderStrokeWeight = 'LBsw',
	p_LeftBorderStrokeType = 'LBss',
	p_LeftBorderStrokeColor = 'LBsc',
	p_LeftBorderStrokeTint = 'LBst',
	p_LeftBorderStrokeOverprint = 'LBso',
	p_LeftBorderStrokeGapColor = 'LBgc',
	p_LeftBorderStrokeGapTint = 'LBgt',
	p_LeftBorderStrokeGapOverprint = 'LBgo',

	p_BottomBorderStrokeWeight = 'BBsw',
	p_BottomBorderStrokeType = 'BBss',
	p_BottomBorderStrokeColor = 'BBsc',
	p_BottomBorderStrokeTint = 'BBst',
	p_BottomBorderStrokeOverprint = 'BBso',
	p_BottomBorderStrokeGapColor = 'BBgc',
	p_BottomBorderStrokeGapTint = 'BBgt',
	p_BottomBorderStrokeGapOverprint = 'BBgo',

	p_RightBorderStrokeWeight = 'RBsw',
	p_RightBorderStrokeType = 'RBss',
	p_RightBorderStrokeColor = 'RBsc',
	p_RightBorderStrokeTint = 'RBst',
	p_RightBorderStrokeOverprint = 'RBso',
	p_RightBorderStrokeGapColor = 'RBac',
	p_RightBorderStrokeGapTint = 'RBat',
	p_RightBorderStrokeGapOverprint = 'RBao',

	// ruling
	p_SkipFirstStrokeRows = 'Sfsr',
	p_SkipLastStrokeRows = 'Slsr',

	p_SkipFirstStrokeColumns = 'Sfsc',
	p_SkipLastStrokeColumns = 'Slsc',

	p_RowStrokePatternFirstCount = 'RSfc',
	p_RowStrokePatternFirstColor = 'RScf',
	p_RowStrokePatternFirstWeight = 'RSwf',
	p_RowStrokePatternFirstStyle = 'RSsf',
	p_RowStrokePatternFirstTint = 'RStf',
	p_RowStrokePatternFirstOverprint = 'RSof',
	p_RowStrokePatternFirstGapColor = 'RSgc',
	p_RowStrokePatternFirstGapTint = 'RSgt',
	p_RowStrokePatternFirstGapOverprint = 'RSgo',

	p_RowStrokePatternSecondCount = 'RSsc',
	p_RowStrokePatternSecondColor = 'RScs',
	p_RowStrokePatternSecondWeight = 'RSws',
	p_RowStrokePatternSecondStyle = 'RSss',
	p_RowStrokePatternSecondTint = 'RSts',
	p_RowStrokePatternSecondOverprint = 'RSos',
	p_RowStrokePatternSecondGapColor = 'RSgs',
	p_RowStrokePatternSecondGapTint = 'RSas',
	p_RowStrokePatternSecondGapOverprint = 'RSps',

	p_ColumnStrokePatternFirstCount = 'CSfc',
	p_ColumnStrokePatternFirstColor = 'CScf',
	p_ColumnStrokePatternFirstWeight = 'CSwf',
	p_ColumnStrokePatternFirstStyle = 'CSsf',
	p_ColumnStrokePatternFirstTint = 'CStf',
	p_ColumnStrokePatternFirstOverprint = 'CSof',
	p_ColumnStrokePatternFirstGapColor = 'CSgc',
	p_ColumnStrokePatternFirstGapTint = 'CSgt',
	p_ColumnStrokePatternFirstGapOverprint = 'CSgo',

	p_ColumnStrokePatternSecondCount = 'CSsc',
	p_ColumnStrokePatternSecondColor = 'CScs',
	p_ColumnStrokePatternSecondWeight = 'CSws',
	p_ColumnStrokePatternSecondStyle = 'CSss',
	p_ColumnStrokePatternSecondTint = 'CSts',
	p_ColumnStrokePatternSecondOverprint = 'CSos',
	p_ColumnStrokePatternSecondGapColor = 'CSgs',
	p_ColumnStrokePatternSecondGapTint = 'CSas',
	p_ColumnStrokePatternSecondGapOverprint = 'CSps',

	// shading
	p_ColumnFillsPriority = 'CFPr',
	p_SkipFirstFillRows = 'Sffr',
	p_SkipLastFillRows = 'Slfr',

	p_SkipFirstFillColumns = 'Sffc',
	p_SkipLastFillColumns = 'Slfc',

	p_RowFillPatternFirstCount = 'RFfc',
	p_RowFillPatternFirstColor = 'RFcf',
	p_RowFillPatternFirstTint = 'RFtf',
	p_RowFillPatternFirstOverprint = 'RFof',

	p_RowFillPatternSecondCount = 'RFsc',
	p_RowFillPatternSecondColor = 'RFcs',
	p_RowFillPatternSecondTint = 'RFts',
	p_RowFillPatternSecondOverprint = 'RFos',

	p_ColumnFillPatternFirstCount = 'CFfc',
	p_ColumnFillPatternFirstColor = 'CFcf',
	p_ColumnFillPatternFirstTint = 'CFtf',
	p_ColumnFillPatternFirstOverprint = 'CFof',

	p_ColumnFillPatternSecondCount = 'CFsc',
	p_ColumnFillPatternSecondColor = 'CFcs',
	p_ColumnFillPatternSecondTint = 'CFts',
	p_ColumnFillPatternSecondOverprint = 'CFos',

	p_StoryOffset = 'STof',
	p_TextFrame = 'TXfr',

	// rows and columns
	p_MinimumHeight = 'Mnht',
	p_MaximumHeight = 'Mxht',
	p_KeepWithNextRow = 'Kwnr',
	p_StartRow = 'Strw',
	p_SingleRowHeight = 'MFHo',		//#1096978
	p_SingleColumnWidth = 'klwd',	//#1096978

	// cells
	p_ParentRow					= 'PRow',
	p_ParentColumn				= 'PCol',
	p_AutoGrow =			'AuGw',
	p_RowType = 			'RwTp',
	p_RowSpan =				'RSpn',
	p_ColumnSpan =			'CSpn',
	p_AppliedCellStyle =	'pcst', // "CellStyle" is now "applied cell style"
	p_AppliedTableStyle = 'ptzz', // was p_TableStyle in CS2
	p_AppliedCellStylePriority = 'ppcs',
	// This was defined in Teacup's CS-2 plug-ins for cell styles
	p_ParagraphStyle	=	'csps',

	// convert text to from table
	p_ColSeparator = 'CSep',
	p_RowSeparator = 'RSep',

	// stroke and fills
	p_DefaultRowStrokeWeight = 'DRlw',
	p_DefaultRowStrokeType = 'DRls',
	p_DefaultRowStrokeColor = 'DRlc',
	p_DefaultRowStrokeTint = 'DRlt',
	p_DefaultRowStrokeOverprint = 'DRop',
	p_DefaultRowStrokeGapColor = 'DRlg',
	p_DefaultRowStrokeGapTint = 'DRla',
	p_DefaultRowStrokeGapOverprint = 'DRlp',

	p_DefaultColStrokeWeight = 'DClw',
	p_DefaultColStrokeType = 'DCls',
	p_DefaultColStrokeColor = 'DClc',
	p_DefaultColStrokeTint = 'DClt',
	p_DefaultColStrokeOverprint = 'DCop',
	p_DefaultColStrokeGapColor = 'DClg',
	p_DefaultColStrokeGapTint = 'DCla',
	p_DefaultColStrokeGapOverprint = 'DClp',

	p_TopEdgeStrokeWeight = 'TBlw',
	p_TopEdgeStrokeType = 'TBls',
	p_TopEdgeStrokeColor = 'TBlc',
	p_TopEdgeStrokeTint = 'TBlt',
	p_TopEdgeStrokeOverprint = 'TBop',
	p_TopEdgeStrokeGapColor = 'TBlg',
	p_TopEdgeStrokeGapTint = 'TBla',
	p_TopEdgeStrokeGapOverprint = 'TBlp',
	p_TopEdgeStrokePriority = 'TBpr',

	p_LeftEdgeStrokeWeight = 'LBlw',
	p_LeftEdgeStrokeType = 'LBls',
	p_LeftEdgeStrokeColor = 'LBlc',
	p_LeftEdgeStrokeTint = 'LBlt',
	p_LeftEdgeStrokeOverprint = 'LBop',
	p_LeftEdgeStrokeGapColor = 'LBlg',
	p_LeftEdgeStrokeGapTint = 'LBla',
	p_LeftEdgeStrokeGapOverprint = 'LBlp',
	p_LeftEdgeStrokePriority = 'LBpr',

	p_BottomEdgeStrokeWeight = 'BBlw',
	p_BottomEdgeStrokeType = 'BBls',
	p_BottomEdgeStrokeColor = 'BBlc',
	p_BottomEdgeStrokeTint = 'BBlt',
	p_BottomEdgeStrokeOverprint = 'BBop',
	p_BottomEdgeStrokeGapColor = 'BBlg',
	p_BottomEdgeStrokeGapTint = 'BBla',
	p_BottomEdgeStrokeGapOverprint = 'BBlp',
	p_BottomEdgeStrokePriority = 'BBpr',

	p_RightEdgeStrokeWeight = 'RBlw',
	p_RightEdgeStrokeType = 'RBls',
	p_RightEdgeStrokeColor = 'RBlc',
	p_RightEdgeStrokeTint = 'RBlt',
	p_RightEdgeStrokeOverprint = 'RBop',
	p_RightEdgeStrokeGapColor = 'RBlg',
	p_RightEdgeStrokeGapTint = 'RBla',
	p_RightEdgeStrokeGapOverprint = 'RBlp',
	p_RightEdgeStrokePriority = 'RBpr',

	p_InnerRowStrokeWeight = 'IRlw',
	p_InnerRowStrokeType = 'IRls',
	p_InnerRowStrokeColor = 'IRlc',
	p_InnerRowStrokeTint = 'IRlt',
	p_InnerRowStrokeOverprint = 'IRop',
	p_InnerRowStrokeGapColor = 'IRlg',
	p_InnerRowStrokeGapTint = 'IRla',
	p_InnerRowStrokeGapOverprint = 'IRlp',

	p_InnerColumnStrokeWeight = 'IClw',
	p_InnerColumnStrokeType = 'ICls',
	p_InnerColumnStrokeColor = 'IClc',
	p_InnerColumnStrokeTint = 'IClt',
	p_InnerColumnStrokeOverprint = 'ICop',
	p_InnerColumnStrokeGapColor = 'IClg',
	p_InnerColumnStrokeGapTint = 'ICla',
	p_InnerColumnStrokeGapOverprint = 'IClp',

	// Diagonal lines
	p_DiagonalLineInFront = 'DLib',
	p_TopLeftDiagonalLine = 'DLTl',
	p_TopRightDiagonalLine = 'DLTr',
	p_DiagonalLineStrokeWeight = 'DLsw',
	p_DiagonalLineStrokeType = 'DLsy',
	p_DiagonalLineStrokeColor = 'DLsc',
	p_DiagonalLineStrokeTint = 'DLst',
	p_DiagonalLineStrokeOverprint = 'DLso',
	p_DiagonalLineStrokeGapColor = 'DLgc',
	p_DiagonalLineStrokeGapTint = 'DLgt',
	p_DiagonalLineStrokeGapOverprint = 'DLgo',

	//EPSText properties
	p_EPSTextData = 'ETFC',
	p_EPSAttributeBounds = 'ETSC',

	// Text
	p_TopInset = 'NstT',
	p_LeftInset = 'NstL',
	p_BottomInset = 'NstB',
	p_RightInset = 'NstR',

	// Aliases for Text
	p_TextTopInset = 'Ttxt',
	p_TextLeftInset = 'Ltxt',
	p_TextBottomInset = 'Btxt',
	p_TextRightInset = 'Rtxt',
	p_ClipContentsToTextCell = 'Cltt',

	p_ParagraphSpacingLimit = 'PSsl',
	p_MinFirstBaselineOffset =	'Fboa',
	p_RotationFollowsStory = 'Rfst',
	p_RotationRunsAgainstStory = 'Rast',
	p_ClipContentsToCell =	'ClcC',

	p_LineAlignment		=	'laln',

	// Table Stroke Drawing Order
	p_StrokeOrder = 'tsdo',
	en_kStrokeOrderEnum		= 'sdot',
	en_RowOnTop	= 'srot',
	en_ColumnOnTop	= 'scot',
	en_BestJoins		= 'sbej',
	en_InDesign2Compatibility	= 'sidc',

	en_StrokeTypes =	'LnSt',
	en_ThickThick = 'Thkk',
	en_ThinThin = 'Thnn',
	en_ThickThin = 'Thkn',
	en_ThinThick = 'Thnk',
	en_ThickThinThick = 'Tknk',
	en_ThinThickThin = 'Tnkn',

	en_RowTypes		= 'ERts',
	en_BodyRow		= 'EBrw',
	en_HeaderRow	= 'EHrw',
	en_FooterRow	= 'EFrw',
	en_MixedState	= 'EMrw',

	// Headers and Footers attributes
	p_HeadersBreakType	= 'HdBt',
	p_FootersBreakType	= 'FtBt',
	p_HeadersSkip		= 'HdSk',
	p_FootersSkip		= 'FtSk',
	en_HFBreakTypes		= 'HFBt',

	en_InAllTextColumns	= 'IaTc',
	en_OnePerTextFrame	= 'OpTf',
	en_OnePerPage		= 'OpPa',

	p_AlternatingFills	= 'TaFl',
	en_kAlternatingFillsEnum = 'TAFE',
	en_AltNone = 'AlNo',
	en_AltRows	= 'AlRw',
	en_AltColumns		= 'AlCl',

	en_StoryType = 'estt',
	en_RegularStory = 'rgst',
	en_TOCStory = 'tost',
	en_IndexingStory = 'idst',
    en_EndnoteStory = 'enst',
	// regional styles in table styles
	p_HeaderRegionUsesBodyRegionCellStyle	= 'BrHd',
	p_FooterRegionUsesBodyRegionCellStyle	= 'BrFt',
	p_LeftRegionUsesBodyRegionCellStyle		= 'BrLc',
	p_RightColRegionUsesBodyRegionCellStyle = 'BrRc',
	p_HeaderRegionCellStyle					= 'RsHd',
	p_FooterRegionCellStyle					= 'RsFt',
	p_LeftColRegionCellStyle					= 'RsLc',
	p_RightColRegionCellStyle				= 'RsRc',
	p_BodyRegionCellStyle					= 'RsBr',
	p_TableDirection		=	'tdir',

	// story and galley table properties
	p_TableCollapsed = 'tCsp',
	p_TableCellDisplayOrder = 'tCDo',

	en_CellDisplayOrderTypes = 'cDOt',
	en_ByRows = 'byRW',
	en_ByColumns = 'byCN',

	// Cell type : Text or Graphic
	p_CellType = 'CTyp',

	// Cell type enums
	en_CellType = 'eCTP',
	
	en_TextCellType = 'enXT',
	en_GraphicCellType = 'enPI',

	// Convert Cell Type method enums
	p_ToCellType = 'toCT',
	p_PreserveData = 'pDat',

	e_ConvertCellType = 'coCT',

	// Graphic Cell inset properties
	p_PageItemLeftInset = 'piIL',  // page item Inset Left
	p_PageItemTopInset = 'piIT',
	p_PageItemRightInset = 'piIR',
	p_PageItemBottomInset = 'piIB',

	p_ClipContentsToPageItemCell = 'cLPI' // clip content of graphic cell
};

enum ImportFilterPrefProps
{
	// Import filter prefs props
	p_ConvertPageBreaks =	'wPAG',
	p_ImportNotes =			'wFOO',
	p_ImportTOC =			'wTOC',
	p_ImportIndex =		'wENT',
	p_RemoveFormatting =	'wrRF',
	p_ConvertTablesTo =		'wCTT',
	p_ConvertBNToText =		'wCBT',

	p_CharacterSet =		'Tchs',
	p_Platform =			'Tplf',
	p_Dictionary =		    	'Tdic',
	p_RemoveCR_EndOfLine =	'TCRl',
	p_RemoveCR_BetweenPara =	'TCRp',
	p_KeepTables =			'TCRt',
	p_SpacesToTab =		'Ts2t',
	p_NumSpacesToTab =	'Tmsp',

	p_TagDefinition =		'TTtd',
	p_UseTypographersQuotes = 'TTtq',
	p_TTRemoveFormatting	= 'TTrf',
	p_TagForm =			    'TTtf',

	p_XLSViewName			=	'PXvn',
	p_XLSViewIndex			=	'PXvi',
	p_XLSSheetName		=	'PXsn',
	p_XLSSheetIndex		=	'PXsi',
	p_XLSRangeName		=	'PXrn',
	p_XLSRangeIndex		=	'PXri',
	p_XLSApplyDefaultStyle	=	'PXds',
	p_XLSAlignmentStyle		=	'PXas',
	p_DecimalPlaces			=	'PXdp',
	p_XLSHiddenCells		=	'PXhc',
	p_XLSErrorCode			=	'PXer',
	p_XLSTableFormat		=	'PXtf',

	// Font Properties
	p_PostScriptName		=	'fPSN',
	p_FontFamily			=	c_FontFamily,
	p_FontStyle				=	'fSty',
	p_FontType				=	'fnTp',
	p_AllowOutlines			=	'fPOt',
	p_AllowPrinting			=	'fPpr',
	p_AllowEmbedding		=	'fPem',
	p_AllowPDFEmbedding	=	'fPPD',
	p_RestrictedPrinting		=	'fPRP',
	p_FontPlatformName		=	'fPLT',
	p_WritingScript			=	'WSCR',
	p_FontFullName			=	p_FullName,
	p_FontFullNameNative	=	'fFUN',
	p_FontStyleNameNative	=	'fStN',
	p_FontVersion			=	p_Version,
	p_FontTypekitInfo		=	'ftkd',
	p_Registry				=	'fREG',
	p_Ordering				=	'fORD',
    p_NumDesignAxes         =   'fNDA',
    p_DesignAxesName     =   'NDAN',
    p_DesignAxesRange    =   'NDAR',
    p_DesignAxesValue    =   'NDAV',

	//	Trap styles
	p_TrapDefaultWidth		=	'tpDW',
	p_TrapBlackWidth		=	'tpBW',
	p_TrapJoinStyle			=	'tpJS',
	p_TrapEndStyle			=	'tpES',
	p_TrapImagePlacment		=	'tpIP',
	p_ObjectsToImages		=	'tpOI',
	p_ImagesToImages		=	'tpII',
	p_InternalImages		=	'tpIM',
	p_OneBitImages			=	'tpOB',
	p_StepThreshold			=	'tpST',
	p_BlackColorThreshold	=	'tpBT',
	p_BlackDensity			=	'tpBD',
	p_SlidingTrap			=	'tpSL',
	p_ColorReduction		=	'tpRD',

	p_PlaceableFileExtensions =		'PlEx',
	p_PlaceableFileTypes =		'PlTy',

	en_TrapEndTypes			=	'tpen',		//	trap end types
	en_TrapEndMiter			=	'tpme',		//	miter ends
	en_TrapEndOverlap		=	'tpol',		//	overlap ends

	en_TrapImagePlacementTypes	=	'tpip',	//	Image placement type
	en_ImagePlaceCenter			=	'tpcn',	//	center
	en_ImagePlaceChoke			=	'tpch',	//	choke
	en_ImagePlaceNeutralDensity	=	'tpnd',	//	neutral density
	en_ImagePlaceSpread			=	'tpsp', //	spread

	en_ConvertPageBreaks = 'apbe',
	en_ConvertTablesTo = 'actt',
	en_TableFormatting = 'aptf',
	en_AlignmentStyle = 'apas',
	en_xlsSpreadSheet = 'sprs',

	en_TextImportCharacterSet = 'acse',
	en_ANSI = 'ANSI',
	en_ShiftJIS83pv = 'T83p',
	en_ShiftJIS90pv = 'T90p',
	en_ShiftJIS90ms = 'T90m',
	en_GB2312 =	'Tgb_',
	en_ChineseBig5 = 'Tcb5',
	en_MacintoshCE = 'TmCE',
	en_MacintoshCyrillic = 'TmCy',
	en_MacintoshGreek = 'TmGr',
	en_MacintoshTurkish = 'TmTr',
	en_WindowsCyrillic = 'TwCy',
	en_WindowsEE = 'TwEE',
	en_WindowsGreek = 'TwGr',
	en_WindowsTurkish = 'TwTu',
	en_DOSLatin2 = 'Tdl2',
	en_MacintoshUkrainian =	'TmUk',
	en_MacintoshCroatian =	'TmCr',
	en_MacintoshRomanian =	'TmRo',
	en_MacintoshIcelandic =	'TmIc',
	en_MacintoshRoman =	'TmRm',
	en_CyrillicCP855 =		'Tc85',
	en_Koi8Russian =		'Tk8r', //0x546b3872
	en_Koi8Ukrainian =		'Tk8u', //0x546b3875
	en_ISOCyrillic	=		'TiCy',
	en_ISOGreek =			'TiGk',
	en_ISOCE =				'TiCE',
	en_ISOTurkish =			'TiTu',

	// ME

//	en_WindowsBaltic =		'TwBa',  (commented out from ME during CS3 ME development)
	en_WindowsBaltic =		'TwBt', //from SangamScriptingDefs.h
	en_WindowsCE =			'TwCE', //from SangamScriptingDefs.h
	en_GB18030 =			'Tgb3', //from SangamScriptingDefs.h
	en_KSC5601 =			'TKsc', //from SangamScriptingDefs.h

	en_MacintoshGreekSharedCaps =         'TmG2', //0x54774772

	en_MacintoshArabic =	'TmAr',
	en_WindowsArabic =		'TwAr',
	en_ASMO =				'Tasm',
	en_ASMOTransp =		'Tast',
	en_MacintoshHebrew =	'TmHb',
	en_WindowsHebrew =	'TwHb',

	en_Unknown = 'Unkn',

	en_Platform = 'apfe',
	en_Macintosh = 'MAcs',
	en_PC =	'Wndz',

	en_TextExportCharacterSet = 'ecse',
	en_DefaultEncoding = 'Tdft',

	en_TagDefinition = 'tttd',
	en_PublicationDefinition = 'TTpd',
	en_TaggedFileDefinition = 'TFtd',

	en_TaggedTextExportCharacterSet = 'tten',

	en_TaggedTextForm = 'ttfe',
	en_Verbose = 'TTvb',
	en_Abbreviated = 'TTab',

	// line weights
	en_PDFMarkWeight   = 'pdLW',
	en_125pt           = '125p',
	en_25pt            = '250p',
	en_50pt            = '500p',
	en_10mm            = '10mm',
	en_15mm            = '15mm',
	en_20mm            = '20mm',
	en_30mm            = '30mm'
};

// Create Outlines
enum CreateOutlinesScriptingDefs
{
	e_CreateOutlines =		'cout',
	p_DeleteOriginal =		'dOrg'
} ;

// InCopy definitions
enum InCopyDefs
{
	c_InCopyDocUser			= 'DcUs',
	c_InCopyDocUsers		= 'DcUS',
	c_ICDocStandAlonePref	= 'Isap',

	p_InCopyDocUser			= 'dcuz',
	p_ICDocStandAlonePref	= 'isaz',
	p_StoryLabel			= 'sLbl',
	p_StoryTitle			= 'sTtl',

	// galley window
	p_GalleyView			= 'DcVw',	// uses en_ViewMode enum
	en_ViewMode				= 'enVw',
	en_LayoutView			= 'eLay',
	en_GalleyView			= 'eGal',
	en_StoryView			= 'eSty',

	// galley info
	p_OversetText			= 'OvrT',

	// story properties
	p_GalleyIndex			= 'gInx',

	// Track Changes
	p_ChangeKind			= 'dKin',
	p_UserName				= 'UsrN',
	p_UserColor				= 'UsrC',

	// p_kind enumerations
	en_ChangeKinds			= 'dKin',
	en_InsertedText			= 'kIns',
	en_DeletedText			= 'kDel',
	en_MovedText			= 'kMov',

	// Notes
	p_Collapsed				= 'Clps',
	e_ConvertToNote			= 'CvtN',

	// Notes & Note Prefs
	c_NotePref				= 'Ntep',
	p_NotePref				= 'pNte',
	p_NoteColor				= 'ntCl',
	p_ShowNoteTips			= 'SNTp',
	p_SpellCheckNotes		= 'SCNt',
	p_FindReplaceNotes		= 'FRNt',
	p_NoteBGColor			= 'NBGC',
	p_NoteFont				= 'ntFt',
	p_NoteFontSize			= 'ntFs',
	// these two are from Standard Addition's "file information" record so they don't conflict
	p_CreationDate			= 'ascd',
	p_ModificationDate		= 'asmo',
	p_ShowHideNotes			= 'SHNt',
	p_NoteColorChoice		= 'Ntcc',


	// Changes & Track Changes Prefs
	c_TrackChangesPref		= 'TCHp',
	p_TrackChangesPref		= 'pTCH',
	p_TrackChangesActive	= 'TCAc',
	p_TCColor				= 'tcCl',
	p_ShowAddedText			= 'ShAT',
	p_ShowDeletedText		= 'ShDT',
	p_ShowMovedText			= 'ShMT',
	p_ShowChangeBar			= 'ShCB',
	p_ChangeBarColor		= 'CBCl',
	p_SpellChkDeletedText	= 'SpDT',
	p_PreventDupeColor		= 'pduc',
	p_AddedTextColor		= 'atCl',
	p_AddedBGColor			= 'abCl',
	p_DeletedTextColor		= 'dtCl',
	p_DeletedBGColor		= 'dbCl',
	p_MovedTextColor		= 'mtCl',
	p_MovedBGColor			= 'mbCl',
	p_AddedTextMarking		= 'atMk',
	p_DeletedTextMarking	= 'dtMk',
	p_MovedTextMarking		= 'mtMk',
	p_ChangeBarLocation		= 'CBLc',
	p_AddedTextColorChoice	= 'atCc',
	p_AddedBGColorChoice	= 'abCc',
	p_DeletedTextColorChoice= 'dtCc',
	p_DeletedBGColorChoice	= 'dbCc',
	p_MovedTextColorChoice	= 'mtCc',
	p_MovedBGColorChoice	= 'mbCc',

	en_ChangeBarLocations	= 'eLct',
	en_ChangeMarkings		= 'eMks',
	en_Underline			= 'eUnd',
	en_Strikethrough		= 'eStr',

	en_ChangeTextColorChoices	= 'eCtc',
	en_UseGalleyColor			= 'eUgc',
	en_UseChangePrefColor		= 'eUpc',

	en_ChangeBGColorChoices	= 'eCbc',
	en_UseGalleyColorBG		= 'eUgb',
	en_UseUserColorBG		= 'eUub',
	en_UseChangePrefColorBG	= 'eUpb',

	// Galley Prefs
	c_GalleyPref			= 'GalP',
	p_GalleyPref			= 'pGal',
	p_SmoothText			= 'pSmh',
	p_TextColor				= 'pTCl',
	p_BackgroundColor		= 'pBgC',
	p_CursorType			= 'CrsT',
	p_BlinkCursor			= 'Blnk',
	p_OverrideFont			= 'OvFt',
	p_UseOverrideFont		= 'uOFt',
	p_ShowDepthRuler		= 'dRlr',
	p_StoryAntiAliasType	= 'SalS',
	p_StoryShowFootnotes	= 'fNoS',
	p_ShowParagraphStyleNames = 'sPSn',
	p_ShowParagraphBreakMarks = 'sPBm',
	p_ShowLineNumbers		= 'sLNu',
	p_LineSpaceValue		= 'sLSv',
	p_DisplayFont			= 'gDft',
	p_DisplayFontSize		= 'gDfs',
	p_InfoColumnWidth		= 'giCW',
	p_ShowInfoColumn		= 'giCH',

	en_CursorTypes			= 'eCrs',
	en_StandardCursor		= 'eStd',
	en_BarbellCursor		= 'eBBl',
	en_ThickCursor			= 'eTck',
	en_BlockCursor			= 'eBlo',

	en_StoryAntiAliasTypes	= 'aalS',
	en_GrayDDR				= 'gDDR',
	en_ColorDDR				= 'cDDR',
	en_ThickAlias			= 'tAls',

	en_SpacingTypes			= 'spTy',
	en_SingleSpace			= 'siSp',
	en_OneAndHalfSpace		= 'oAHs',
	en_DoubleSpace			= 'dBSp',
	en_TripleSpace			= 'tRSp',


	// PDF Export Prefs
	c_LayoutPDFExportPref	= 'lPDF',	// clone of c_PDFExportPref
	c_GalleyPDFExportPref	= 'gPDF',	// clone of c_PDFExportPref
	p_LayoutPDFPref			= 'DFpl',
	p_GalleyPDFPref			= 'DFpg',
	p_AccurateLineEndings	= 'pALE',
	p_LineNumbers			= 'pLn#',
	p_IncludeNotes			= 'pINt',
	p_IncludeChanges		= 'pICg',
	p_Columns				= 'pClm',
	p_StoryInfo				= 'pStI',
	p_PageInfo				= 'pPIn',
	p_AllNotes				= 'pANt',
	p_AllStories			= 'Stry',
	p_AllChanges			= 'pACg',
	p_NoteBackground		= 'pNBg',
	p_ChangeBackground		= 'pTCB',
	p_UseParagraphStyles	= 'pPSt',

	p_LineRange				= 'LRng',
	en_LineRange			= 'plrg',
	en_LineAll				= 'plna',

	// Print Prefs
	c_PrintGalleyPref		= 'prGp',
	c_PrintLayoutPref		= 'prLp',
	p_PrintGalleyPref		= 'prGn',
	p_PrintLayoutPref		= 'prLn',
	p_PrintAllStories		= 'prSt',
	p_UseGalleySettings		= 'uGSt',
	p_PrintParaStyles		= 'prPS',
	p_PrintNotes			= 'prNt',
	p_PrintNoteBG			= 'prNb',
	p_PrintChanges			= 'prTC',
	p_PrintChangeBG			= 'prTb',
	p_PrintALE				= 'prAL',
	p_PrintLineNumbers		= 'prLN',
	p_PrintColumns			= 'prCo',
	p_PrintColumnWidth		= 'prCW',
	p_PrintPageInfo			= 'prPI',
	p_PrintStoryInfo		= 'prSI',
	p_PrintContributors		= 'prCn',
	p_PrintImages			= 'prIm',

	en_AllOrVisible			= 'enAV',
	en_Visible				= 'vsbl',

	en_NoteBackgrounds		= 'eNBG',
	en_GalleyBG				= 'eGBG',
	en_UserBG				= 'eUBG',
	en_NoteBG				= 'eTBG',

	en_NoteColorChoices		= 'eNCC',
	en_NoteUseUserColor		= 'eUUC',
	en_NoteUsePrefColor		= 'eUPC',

	en_ICPageOrientation	= 'EnP0',

	// Text Macros
	c_TextMacro				= 'tmcr',
	c_TextMacros			= 'tmcs',
	p_Expansion				= 'pTME',
	p_AutoExpansion			= 'tmae',

	// Export options - INCD
	c_ICExportPref			= 'ICxc',
	p_ICExportPref			= 'ICxp',
	p_IncludeStyleTable		= 'ICxs',
	p_IncludeSwatchList		= 'ICxl',
	p_IncludeXMP			= 'ICxx',
	p_Encoding				= 'ICxe',
	en_InCopyFileEncoding	= 'ICex',

	// Export options - InCopy Interchange
	c_INCXExportOptions	= 'icEo',
	p_INCXExportOptions	= 'ipEo',
	p_IncludeGraphicProxyData		= 'inGP',
	p_IncludeAllResources	= 'inAR',

	// bridge
	p_LockState			= 'lckS',

	en_LockState		= 'BRls',
	en_Unmanaged		= 'BRum',
	en_CheckedIn		= 'BRci',
	en_CheckedOut		= 'BRco',
	en_Locked			= 'BRlk',
	en_Embedded			= 'BRem',
	en_Missing			= 'BRms',
	en_Mixed			= 'BRmx',

	// doc preset prefs
	p_DPTextAreaWidth		= 'ptaw',
	p_DPTextAreaDepth		= 'ptad',
	p_DPTextAreaDepthUnit	= 'ptau',
	p_DPGridCharAki			= 'Jcak',
	p_DPGridLineAki			= 'Jlak',
	p_DPCharPerLine			= 'pcpl',

	en_TextAreaDepthUnit	= 'TAdu',
	en_TextAreaChars		= 'TAcs',
	en_TextAreaWords		= 'TAws',
	en_TextAreaLines		= 'TAls',
	en_TextAreaColumnInches	= 'TAci',
	en_TextAreaPages		= 'TAps',

	// InDesign Server
	p_Port = 				'port',
	p_Configuration = 		'cnfg',

	p_Enabled =				'APse',

	LastScriptPropertyID
};

enum DynamicDocumentsExportPrefs
{

	p_DynamicDocumentJPEGQuality				= 'pdjq',
	p_DynamicDocumentRasterResolution			= 'pder',
	p_DynamicDocumentResamplingType				= 'pdrt',
	p_DynamicDocumentResamplingThreshold		= 'pdet',
	p_DynamicDocumentReadersPerSpread			= 'pdrs',
	p_DynamicDocumentRasterizePages				= 'pdrp',
	p_DynamicDocumentTextExportPolicy			= 'pdte',
	p_DynamicDocumentDynamicMediaHandling		= 'pddm',
	p_DynamicDocumentTransparencyHandling		= 'pdth',
	p_DynamicDocumentFlattenerStyle				= 'pdfs',
	p_DynamicDocumentSizeSelection				= 'pdss',
	p_DynamicDocumentFitToOption				= 'ftop',
	p_DynamicDocumentScaleToFit					= 'dstf',
	p_DynamicDocumentFitToWidthAndHeight		= 'ftwh',

	en_SWFRasterCompressionOptions	= 'esrc',
	en_SWFJPEGCompression			= 'srjc',
	en_SWFLosslessCompression		= 'srlc',
	en_SWFAutomaticCompression		= 'srac',
	en_SWFBackgroundOptions			= 'sbgo',
	en_Transparent					= 'sbgt',
	en_PaperColor					= 'sbpc',

	p_XFLInsertHyphensForTLF = 'ihft',

	en_DynamicMediaHandlingOptions			= 'dmho',
	en_DynamicDocumentJPEGQualityOptions	= 'ddjq',
	en_DynamicDocumentTextExportPolicy		= 'ddte',
	en_LiveText								= 'tepl',
	en_RasterizeText						= 'tepr',
	en_VectorizeText						= 'tepv',
	en_TLFText	 							= 'tept',

	en_DynamicDocumentSizeFitSettings		= 'ddsf',
	en_FitTo								= 'ddfs',
	en_WidthAndHeight						= 'ddwh',
	en_Scale								= 'ddsc',

	en_DynamicDocumentFitToOptions			= 'ddfo',
	en_1280x800								= 'ftoe',
	en_1240x620								= 'fttw',
	en_1024x768								= 'ftof',
	en_984x588								= 'ftnf',
	en_800x600								= 'ftes',
	en_760x420								= 'ftsf',
	en_640x480								= 'ftsi',
	en_600x300								= 'ftst'
};

// Script Enumerations
enum ScriptEnumerations
{
	en_DefaultEnum				= 'Denm',
	en_Default					= 'Dflt',

	en_SearchMode				= 'Fscm',
	 en_TextSearch				= 'Ftxs',
	 en_GrepSearch				= 'Fgrs',
	 en_GlyphSearch				= 'Fgls',
	 en_ObjectSearch			= 'Fobs',
     en_ColorSearch             = 'Fcol',
	 en_TransliterateSearch		= 'Ftrs',		//may be J FS only. 11/14/05

	 //Style Mappings
	 en_MappingRuleType			= 'mrty',
	 en_StyleToStyleRuleType	= 'stsr',
	 en_GroupToGroupRuleType	= 'gtgr',
	 en_StyleToGroupRuleType	= 'stgr',
	 en_GroupToStyleRuleType	= 'gtsr',


	en_ObjectType				= 'FOTy',
	 en_AllFrames				= 'FAFs',
	 en_TextFrames				= 'FTFr',
	 en_GraphicFrames			= 'FGFs',
	 en_UnassignedFrames		= 'FUFs',

	en_FindChangeTransliterateCharacterType = 'FTCt',
	en_HalfWidthKatakana					 = 'FHwK',
	en_HalfWidthRomanSymbols				 = 'FHwR',
	en_FullWidthHiragana					 = 'FFwH',
	en_FullWidthKatakana					 = 'FFwK',
	en_FullWidthRomanSymbols				 = 'FFwR',
	en_WesternArabicDigits					 = 'WAdi',
	en_ArabicIndicDigits					 = 'AIdi',
//	en_DigitsFarsi							='difa',

	p_ChangeConditionsMode	= 'CHcm',
	en_ChangeConditionsMode	= 'Cmod',
	
	en_RetainFormat =	'rtfo',
	en_ConvertQuotes =	'cnqt',
	en_ShowOptionsDialog =	'imot',
	en_ExportOptions = 	'exot',
	en_AutoFlow =		'aflw',

	en_LocationOptions = 'locO',
	en_Before =			'befo', // kAEBefore in AERegistry .h
	en_After =			'afte', // kAEAfter in AERegistry .h
	en_End =			'end ', // kAEEnd in AERegistry .h
	en_Begin = 			'bgng', // kAEBeginning in AERegistry .h
	en_MoveRelative =	'mvre',

	en_None	= 			'none',
	en_Ignore = 		'ignr',
	
	en_ColorSpace =				'clte',
	en_RGBcolor =				'cRGB',	// typeRGBColor in AERegistry .h
	en_CMYKcolor =				'CMYK',
	en_LABcolor =				'cLAB',
    en_HSBcolor =               'cHSB',
	en_HEXcolor =				'cHEX',
	en_MixedInkcolor =			'cMIX',
	en_RepurposeRGBcolor =		'rRGB',
	en_RepurposeCMYKcolor =	'rCMY',
	en_NoAlternateColorSpace =	'nasp',

	en_ColorModel =				'clme',
	en_SpotColor =				'spot',
	en_ProcessColor =			'prss',
	en_RegColor =				'regs',
	en_NoneColor =				en_None,
	en_MixedInk =				'inmx',

	en_GradientType =			'gtyp',
	en_AxialGradient =			'axlg',
	en_RadialGradient =			'radg',

	en_YesNo =					'ysno',
	en_Yes =					'yes ',	// kAEYes in AERegistry .h
	en_No =						'no  ',	// kAENo in AERegistry .h

	en_Document	= 			'uDoc',
	en_Normal =				'norm',

	en_SaveOptions =			'savo',
	en_SaveFileType =			'savf',
	en_NativeFileType =			'naft',
	en_PublicationFileType =		'puft',
	en_TemplateFileType =		'tpft',
	en_ICTemplateFileType =	'ctft',
	en_TEXTFileType =			'teft',
	en_RTFFileType =			'rtft',
	en_MSWordFileType =		'mswf',
	en_AskUserSaveFile =		'ask ',	// kAEAsk in AERegistry .h

	en_UnlinkFrom =				'Unfm',

	// Stroke types
	en_LineStrokeTypes =		'sktp',
	en_Dotted =					'Dott',
	en_Dashed3x2 =				'ds32',
	en_Dashed4x4 =				'ds44',
	en_Dashed =				'dash',
	en_Solid =					'sold',
	en_SingleWavy =			'swvy',
	en_StraightHash =			'shsh',
	en_RightSlantHash =			'rshs',
	en_LeftSlantHash =			'lshs',
	en_WhiteDiamond =			'wtdm',
	en_CustomStroke = 			'cstm',
	en_JapaneseDots =			'jdts',

	en_Triple =					'trpl',
	// Stroke corner adjustment
	en_StrokeCornerAdjustment = 'Escj',
	en_Dashes =				'EDsh',
	en_Gaps =					'Egps',
	en_DashesAndGaps =		'DsGp',

	en_CornerEffects =			'ceff',
	en_CornerOptions =			'coPt',
	en_NoCorner =				en_None,
	en_RoundedCorner =			'cerd',
	en_InverseRoundedCorner =	'cenv',
	en_InsetCorner =			'cens',
	en_BevelCorner =			'cebv',
	en_FancyCorner =			'cefn',

	en_TextWrap = 				'txwe',
	en_NoTextWrap =				en_None,
	en_BandTextWrap =			'band',	// jump object text wrap
	en_NextFrameTextWrap =		'nxfr', // jump to next column text wrap
	en_BoundingBoxTextWrap =	'bsds',	// bounding box text wrap
	en_ManualContourTextWrap =	'mcon',	// object shape/contour text wrap
	en_UserModified =			'usmd',	// user modified text wrap

	en_TextWrapMode = 			'txtm',
		// ... include the same as en_TextWrap EXCEPT for en_UserModified

	// contour type, PhotoshopPath, DetectEdge, Alpha Channel already defined in Clipping path
	en_ContourOptionsType =		'enct',
	en_BoundingBox =			'enbb',
	en_GraphicFrame =			'engf',
	en_SameAsClipping =			'sacp',

	en_TextWrapSide = 			'txws',
	en_TextWrapBothSides =		'twbs',	// both sides text wrap
	en_TextWrapLeftSide =		'twls',	// left side text wrap
	en_TextWrapRightSide =		'twrs',	// right side text wrap
	en_TextWrapToBindingSide =	'twts',	// largets side text wrap
	en_TextWrapAwayBindingSide ='twas',	// largets side text wrap
	en_TextWrapLargest =		'twLs',	// largets side text wrap

	en_LineWeightEnum =		'lnwd',
	en_Hairline =				'hrln',

	// For flipping objects (event)
	en_FlipOptions =				'flpo',

	//path and point types
	en_PathType =				'paty',
	en_Open =					'opnp',
	en_Closed =					'clsd',

	en_ClippingPathType =		'cpat',
	en_DetectEdges		=		'dteg',
	en_DeepCut			=		'dpct',
	en_AlphaChannel	=		'aphc',
	en_PhotoshopPath	=		'pspt',
	en_UserModifiedPath	=		'umpt',

	// graphic layer info
	en_UpdateLinkOption =		'uplo',
	en_UseApplicationSettings =	'loua',
	en_KeepOverrides =			'loko',

	en_PointType =				'poty',
	en_Line =					'line',	// Anchor point with no direction lines (they have degenerated to a single point). Obsolete name.
	en_Smooth =					'smth',	// Anchor point with continuous, parellel left and right direction lines.
	en_Corner =					'crnr',	// Anchor point with either two discontinuous direction lines, or a single direction line.
	en_Symmetrical =			'symm',	// Anchor point with continuous left and right direction lines of equal length. Special case of smooth point.
	en_Plain =					'plan', // Anchor point with no direction lines (they have degenerated to a single point). Renamed in Rocket from en_Line


	en_JoinOptions =			'jono',	// Options for how to join to end points on paths
	en_Combine =				'cmbn',	// Combine two path end points, replace with a single averaged point
	en_Connect =				'cnct',	// Connect two path end points

	en_ArrowHead =				'ahed',
	en_NoArrowHead =			en_None,
	en_SimpleArrowHead =		'simp',
	en_SimpleWideArrowHead =	'swah',
	en_TriangleArrowHead =		'trin',
	en_TriangleWideArrowHead =	'twah',
	en_BarbedArrowHead =		'barb',
	en_CurvedArrowHead =		'cvah',
	en_CircleArrowHead =		'crah',
	en_CircleSolidArrowHead =	'csah',
	en_SquareArrowHead =		'sqah',
	en_SquareSolidArrowHead =	'ssah',
	en_BarArrowHead =			'brah',

	en_EndCap = 				'ecap',
	en_ButtEndCap =				'bcap',
	en_RoundEndCap =			'rcap',
	en_ProjectingEndCap =		'pjcp',

	en_ArrowHeadAlignment =		'eaha',
	en_ArrowHeadAlignInside =	'ahai',
	en_ArrowHeadAlignOutside =	'ahao',

	en_EndJoin =				'ejon',
	en_OutlineJoin =				'ojon',
	en_MiterEndJoin =			'mjon',
	en_RoundEndJoin =			'rjon',
	en_BevelEndJoin =			'bjon',

	en_SpanColumnTypeOption =		'spte',
	en_spancolumnsoption =		'spcn',
	en_splitcolumnsoption =		'stcn',
	en_SpanColumnCountOption =		'spct',

	en_TextWrapForm =			'twfm',
	en_TextWrapRegularForm =	'regu',
	en_TextWrapInvertForm =	'inve',

	en_PageBinding =			'bind',
	en_DefaultBinding = 			en_Default,
	en_LeftToRightBinding = 		'ltrb',
	en_RightToLeftBinding = 		'rtlb',

	en_Orientation =				'orie',
	en_Portrait =				'high',
	en_Landscape =				'wide',

	en_DocumentIntentOptions =		'dint',
	en_PrintIntent =				'intp',
	en_WebIntent =					'intw',
	en_DPSIntent =					'intd',
	en_MobileIntent =				'intm',

	// Performance Display enumerations
	en_DisplaySettings =			'dsps',
	en_DisplayOptimized =		'Popt',
	en_DisplayTypical =			'Ptyp',
	en_DisplayHighQuality =		'PHir',
	en_DisplayMediumQuality =	'XPdm',
	en_ViewDisplaySettings =	'vdsp',

	en_RasterDisplaySettings =	'rDsp',
	en_DisplayGrayOut =			'rGry',
	en_DisplayProxy =			'rPrx',
	en_DisplayHiRes =			'rHiQ',

	en_VectorDisplaySettings =	'vDsp',

	en_XPDisplaySettings = 		'XPds',
	en_XPDisplayNoBlurs =		'XPnb',

	en_ZoomOptions =			'zope',
	en_ZoomIn =				'zmin',
	en_ZoomOut =				'zout',
	en_FitSpread =				'zfts',
	en_FitPage =				'zftp',
	en_ShowPasteboard =		'zspb',
	en_ActualSize =				'zasz',
	en_25percent =				'zftf',
	en_50percent =				'zffp',
	en_75percent =				'zfsf',
	en_100percent =				'zfoh',

	en_HorizontalVertical =		'hzvt',
	en_Vertical =				'vert',
	en_Horizontal =				'horz',
	en_StoryHorizontalVertical =	'shvl',

	//'imgf'
	en_DibFormat =				'dibf',
	en_GifFormat =				'giff',
	en_PcxFormat =				'pcxf',
	en_SctFormat =				'sctf',
	en_TiffFormat =				'tiff',
	en_JpegFormat =			'jpgf',
	en_Jpeg2000Format =		'jpg2',
	en_AutomaticJpeg2000Format ='ajp2',
	en_PngFormat =				'SEpg',

	// PDF export enums
	en_PDFExportColorSpace =	'enFc',
	en_UnchangedColorSpace =	'unFc',

	en_AcrobatCompatibilityLevel = 'enAC',
	en_Acrobat40 = 				'Ac40',
	en_Acrobat50 = 				'Ac50',
	en_Acrobat60 = 				'Ac60',
	en_Acrobat70 = 				'Ac70',
	en_Acrobat80 = 				'Ac80',

	en_SinglePageContinuous =	'pSPc',
	en_TwoUpFacing = 			'pTUF',
	en_TwoUpFacingContinuous =	'pTFc',
	en_TwoUpCoverPage = 		'pTCP',
	en_TwoUpCoverPageContinuous ='pTCc',

	en_PDFContentToEmbed =	'CoTE',
	en_UseObjectSettings =		'EmOS',
	en_LinkAll =					'EmLA',
	en_EmbedAll =				'EmAl',
	en_InteractiveElementsOptions =	'IEOs',
	en_InteractivePDFInteractiveElementsOptions =	'IPEO',
	en_DoNotInclude =			'DNIc',
	en_AppearanceOnly =			'AppO',
	en_IncludeAll =				'IcAl',
	en_PDFPageTransitionOverrideOptions =	'pTOO',
	en_FromDocument =			'frDo',

	en_CompressionType =		'CoTy',
	en_CompressNone =			'CoNo',
	en_CompressStructure =		'CoSt',
	en_CompressObjects =		'CoOb',

	en_PDFProfile =				'Ppro',
	en_NAProfile =				'naDP',
	en_MonitorProfile =			'moDP',
	en_CompositeProfile =		'coDP',
	en_SeparationProfile =		'seDP',

	en_ImportedGraphicResolution = 'egrs',

	en_Sampling =				'enSm',
	en_DownSample =				'dnSm',
	en_SubSample =				'sbSm',
	en_BiCubicDownSample =		'bdSm',

	en_ExportLayers =					'enEl',
	en_ExportAllLayers =				'exal',
	en_ExportVisibleLayers =			'exvl',
	en_ExportVisiblePrintableLayers =	'evpl',

	en_BitmapCompression = 'enBc',
	en_AutoCompression =		'aCmp',
	en_Zip =					'zipC',

	en_MonoBitmapCompression = 'enMc',
	en_CCITT4 =					'CIT4',
	en_CCITT3 =					'CIT3',
	en_RunLengthCompression =	'rnlC',

	en_BitmapQuality = 			'enCq',
	en_Minimum =				'enMn',
	en_Low =					'enLw',
	en_Medium =					'enMd',
	en_High =					'enHi',
	en_Maximum =				'enMx',
	en_4bit =					'en4b',
	en_8bit =					'en8b',

	// PDF place enums
	en_PDFCrop = 				'nFcp',
	en_CropContent =			'CrpC',
	en_CropArt =				'CrpA',
	en_CropCrop =				'CrpP',
	en_CropTrim =				'CrpT',
	en_CropBleed =				'CrpB',
	en_CropMedia =				'CrpM',
	en_CropSlug =				'CrSl',
	en_CropContentVisibleOnly = 'CrVo',
	en_CropContentAllLayers =	'CrAl',

	en_StandardsCompliance =	'XStC',
	en_PDFX1a2001 =				'SC1a',
	en_PDFX32002 =				'SCX3',
	en_PDFX1a2003 =				'S1a3',
	en_PDFX32003 =				'SX33',
	en_PDFX42007 =				'SX47',
	en_PDFX42010 =				'SX4X',

	en_PDFExportICCProfiles =	'IICC',
	en_IncludeICCNone =			'ICCn',
	en_IncludeICCAll =			'ICCa',
	en_IncludeICCTagged =		'ICCt',
	en_IncludeICCRGBAndTagged =	'ICCr',

	en_OutputCondition =		'OutC',
	en_CGATSTR001 =				'OCCG',

	en_OCRegistry =				'OCRg',
	en_Blank =					'OCCt',
	en_ICC =					'Oicc',

	en_PDFExportMagnificationOptions =		'PeMO',
	en_PDFExportPageLayoutOptions =			'PePL',
	en_PDFExportRasterResolutionOptions =	'PeRR',
	en_PDFExportRasterCompressionOptions =	'PeRc',
	en_PDFExportJPEGQualityOptions =		'PeJq',

	en_72ppi =					'stpp',
	en_96ppi =					'nspp',
	en_144ppi =					'ofpp',

	//Text enumerators
	en_CapitalizeMode =			'cape',
	en_CapNormal =				'norm',
	en_CapSmall =				'smcp',	// kAESmallCaps in AERegistry.h
	en_CapAll =					'alcp',	// kAEAllCaps in AERegistry.h
	en_CapToSmallCap =			'c2sc', // same as opentype feature

	e_ChangeCase = 				'ccas',
	en_ChangeCaseMode =			'ccmd',
	en_UpperCase =				'ccuc',
	en_LowerCase =				'cclc',
	en_TitleCase =				'cctc',
	en_SentenceCase =			'ccsc',

	en_PositionMode = 			'pose',
	en_PosNormal =				'norm',
	en_PosSuperscript =			'spsc',	// kAESuperscript in AERegistry.h
	en_PosSubscript =			'sbsc',	// kAESubscript in AERegistry.h
	en_PosOTSuperscript =		'pOTs',
	en_PosOTSubscript =			'pOTb',
	en_PosOTNumerator =		'pOTn',
	en_PosOTDenominator =		'pOTd',

	en_OTPositionalFormMode =	'OTpf',
	en_Initial = 					'init',
	en_Medial = 					'medi',
	en_Final =					'fina',
	en_Isolated = 				'isol',
	en_AutomaticPosForm =		'apfm',

	en_ContentAlignment =		'cnal',
	en_Left =					'left',	// kAELeftJustified in AERegistry.h
	en_Right =					'rght',	// kAERightJustified in AERegistry.h
	en_Center =					'cent',	// kAECentered in AERegistry.h
	en_TextAlignment =			'txal',
	en_BindingAlignment = 		'Balt',

	en_PageSideOptions =		'pgop',
	en_LeftHand =				'lfth',
	en_RightHand =				'rgth',
	en_Unisex =					'usex',

	en_ParagraphAlignment =		'kjst',
	en_FullJustify =			'full',	// kAEFullyJustified in AERegistry.h
	en_LeftJustify = 			'ljst',
	en_RightJustify =			'rjst',
	en_CenterJustify =			'cjst',
	en_ToBindingSideJustify =	'a2bs',
	en_AwayBindingSideJustify =	'aabs',

	en_WarichuAlignment =		'Jwca',
	en_ParagraphAlignSingle =	'sjst',

	en_BreakBeforeParagraph = 	'pbbe',
	en_NoForceBreak =			'nbrk',		// anywhere
	en_ColumnBreak =			'cbrk',		// in next column
	en_NextFrameBreak =			'NFbk',		// in next frame
	en_PageBreak =				'pbrk',		// on next page
	en_OddPageBreak =			'Opbk',		// on next odd page
	en_EvenPageBreak =			'Epbk',		// on next even page
	
	// Provider Hyphenation Style scripting enum
	en_ProviderHyphenationStyle =	'dphs',
	en_HyphAll =					'dall',		// All
	en_HyphAllButUnaesthetic =		'dabu',		// All but unaesthetic
	en_HyphAesthetic =				'daes',		// Aesthetic
	en_HyphPreferredAesthetic =		'dpae',		// Preferred Aesthetic

	en_RuleAboveWidth =			'rlwd',
	en_NoRuleWidth =			en_None,
	en_RuleColumnWidth =		'Klwd',		// column width	//#1096978
	en_RuleTextWidth =			'ptxw',		// text width

	en_TabStopAlignment =		'tsae',
	en_TabAlignLeft =			'left',	// kAELeftJustified in AERegistry.h
	en_TabAlignRight =			'rght',	// kAERightJustified in AERegistry.h
	en_TabAlignCenter =			'cent',	// kAECentered in AERegistry.h
	en_TabAlignCharacter =		'tbac',

	en_OverrideType =			'OvTp',
	en_CharacterOnly =			'chro',
	en_ParagraphOnly =			'paro',

	en_SelectAll =				'Sall',

	// print enums
	en_PrinterStyle				= 'EnPs',

	en_Printer					= 'EnPr',
	en_PostScriptFile			= 'psfl',

	en_PPD						= 'EnPd',
	en_DeviceIndependent		= 'deid',

	en_PrintRange				= 'prng',
	en_PrintAll					= 'prna',
	en_SelectedItems			= 'prns',

	en_PageOrientation			= 'EnPO',
	en_ReversePortrait			= 'orrp',
	en_ReverseLandscape			= 'orrl',

	en_Sequence					= 'EnSq',
	en_All						= 'all ',
	en_Odd						= 'odd ',
	en_Even						= 'even',

	en_PaperSizes				= 'EnPS',
	en_DriverPaperSize			= 'PSDr',

	en_PaperSize				= 'EnPZ',

	en_PrintPosition			= 'EnPP',
	en_UpperLeft				= 'cntN',
	en_CenterHorizontally		= 'cntH',
	en_CenterVertically			= 'cntV',
	en_Centered					= 'cntB',

	en_PrintLayers				= 'EnLR',
	en_AllLayers				= 'allL',
	en_VisibleLayers			= 'visL',
	en_VisiblePrintableLayers	= 'vprL',

	en_ScaleMode				= 'EnSM',
	en_ScaleXAndY				= 'scxy',
	en_ScaleToFit				= 'sctf',

	en_ThumbsPerPage			= 'EnTP',
	en_1x2						= 't1x2',
	en_2x2						= 't2x2',
	en_3x3						= 't3x3',
	en_4x4						= 't4x4',
	en_5x5						= 't5x5',
	en_6x6						= 't6x6',
	en_7x7						= 't7x7',

	en_Leading					= 'enLD',
	en_TilingType				= 'EnTT',
	en_Auto						= 'atil',
	en_AutoJustified			= 'ajst',
	en_Manual					= 'mntl',

	en_MarkType					= 'EnMT',
	en_JMarksWithCircle			= 'jmwc',
	en_JMarksWithoutCircle		= 'jmnc',

	en_MarkLineWeight			= 'EnMW',
	en_05mm						= '05mm',
	en_07mm						= '07mm',

	en_ColorOutputMode			= 'EnCO',
	en_CompositeLeaveUnchanged	= 'cmLU',
	en_CompositeGray			= 'cmpg',
	en_CompositeRGB				= 'cmRB',
	en_CompositeCMYK			= 'cmCK',
	en_BuiltInSeparation		= 'sepa',
	en_InRipSeparation			= 'rips',

	en_Trapping					= 'EnTp',
	en_BuiltInTrap				= 'BiTp',
	en_InRipTrap				= 'ripT',

	en_Flip						= 'EnFp',
	en_HorizontalAndVertical	= 'HzVl',

	en_Screeening				= 'EnSc',

	en_SpotOverPrint			= 'EnSO',
	en_Legacy					= 'SOLe',
	en_SimulatePress			= 'SOSP',
	en_SimulateScreen			= 'SOSS',

	en_SourceSpace				= 'EnSS',
	en_ProofSpace				= 'prsp',

	en_Profile					= 'EnPf',
	en_UsePostScriptCMS			= 'upsc',
	en_Working					= 'Work',
	en_UseNoCMS					= 'usno',

	en_CRD						= 'EnCr',

	en_Intent					= 'ECIn',

	en_SendImageData			= 'EnID',
	en_AllImageData				= 'nsmp',
	en_OptimizedSubSampling		= 'opss',
	en_LowResolution			= 'lorz',	//same as en_DisplayLowRes

	en_FontDownloading			= 'EnFD',
	en_Complete					= 'whle',
	en_Subset					= 'incr',
	en_SubsetLarge				= 'larg',

	en_PostscriptLevel		 	= 'EnPL',
	en_PS2						= 'PSL2',
	en_PS3						= 'PSL3',

	en_DataFormat		 	 	= 'EnDF',
	en_ASCII					= 'ASCI',
	en_Binary					= 'Bnry',

	en_ContentType				= 'cnty',
	en_Unassigned				= 'unas',
	en_GraphicType				= 'grpt',

	en_FitContentOptions		= 'fito',
	en_EmptyFrameFittingOptions = 'effo',
	en_ContentToFrame			= 'ctof',
	en_FrameToContent			= 'ftoc',
	en_CenterContent			= 'cenc',
	en_Proportionally			= 'conp',
	en_FillProportionally		= 'filp',
	en_ApplyFrameFittingOptions = 'affo',
	en_ContentAwareFit			= 'cafi',

	// Autoflow/auto page insertion enumerations
	en_AutoPageInsertOptions	= 'Enpi',
	en_AtEndOfStory				= 'aeos',
	en_AtEndOfSection			= 'aeox',
	en_AtEndOfDocument			= 'aeod',

	// Convert shape enumerations
	en_ConvertShapeOptions		= 'CSOP',	// Options for converted page item shapes
	en_ConvertShapeRect			= 'CSRE',	// Convert shape to rectangle
	en_ConvertShapeRoundedRect	= 'CSRR',	// Convert shape to rounded rectangle
	en_ConvertShapeBeveledRect	= 'CSBR',	// Convert shape to beveled rectangle
	en_ConvertShapeInverseRRect = 'CSIR',	// Convert shape to inverse rounded rectangle
	en_ConvertShapeOval			= 'CSOV',	// Convert shape to oval
	en_ConvertShapeTriangle		= 'CSTR',	// Convert shape to triangle
	en_ConvertShapePolygon		= 'CSPO',	// Convert shape to polygon (using current polygon settings)
	en_ConvertShapeLine			= 'CSLI',	// Convert shape to line
	en_ConvertShapeStraightLine	= 'CSSL',	// Convert shape to straight line (will be horizontal or vertical)
	en_ConvertShapeOpenPath		= 'CSOp',	// Convert shape to open path
	en_ConvertShapeClosedPath	= 'CSCp',	// Convert shape to closed path

	// CJK enumerations
	en_GridAlignment			= 'Jaga',

	en_CharacterAlignment		= 'Jaca', //idCharacterAlignment
	en_AlignBaseline			= 'Jabl',
	en_AlignEmTop				= 'Jatp',
	en_AlignEmCenter			= 'Jact',
	en_AlignEmBottom			= 'Jabm',
	en_AlignICFTop				= 'Jitp',
	en_AlignICFBottom			= 'Jibm',
	en_AlignNone				= en_None,

	en_GlyphForms				= 'Jglf',
	en_TraditionalForm			= 'Jagt',
	en_ExpertForm				= 'Jage',
	en_JIS78Form				= 'Jag7',
	en_JIS83Form				= 'Jag8',
	en_MonospacedHalfWidthForm	= 'Jagm',
	en_ThirdWidthForm			= 'Jagh',
	en_QuarterWidthForm			= 'Jagq',
	en_ProportionalWidthForm	= 'Jagp',
	en_FullWidthForm			= 'Jagf',
	en_NLCForm					= 'Jagn',
	en_JIS04Form				= 'Jag4',
	en_JIS90Form				= 'Jag9',
	en_NoGlyphForm				= en_None,

	en_KentenCharacter			= 'Jkch',
	en_KentenNone				= en_None,
	en_KentenSesameDot			= 'Jkcs',
	en_KentenWhiteSesameDot		= 'Jkcw',
	en_KentenBlackCircle		= 'Jkbc',
	en_KentenWhiteCircle		= 'Jkwc',
	en_KentenBlackTriangle		= 'Jkbt',
	en_KentenWhiteTriangle		= 'Jkwt',	// Not to be confused with 'jkwt'
	en_KentenBullseye			= 'Jkbe',
	en_KentenFisheye			= 'Jkfe',
	en_KentenSmallBlackCircle	= 'Jksc',	// Not to be confused with 'jksc'
	en_KentenSmallWhiteCircle	= 'Jksw',

	en_RubyKentenPosition		= 'Jkps',
	en_RubyKentenAboveRight		= 'Jkar',
	en_RubyKentenBelowLeft		= 'Jkbl',

	en_KentenAlignment			= 'Jekl',
	en_KentenLeft				= 'Jknl',
	en_KentenCenter				= 'Jknc',
	en_KentenRight				= 'Jknr',

	en_KentenCharacterSet		= 'Jest',
	en_CSCharacterInput			= 'Jchi',
	en_CSShiftJIS				= 'Jsjs',
	en_CSJIS					= 'JJIS',
	en_CSUnicode				= 'Juni',
	en_CSKuten					= 'Jkut',

	en_RubyType					= 'Jrty',
	en_GroupRuby				= 'Jrgr',
	en_PerCharacterRuby			= 'Jrpc',

	en_RubyAlignment			= 'Jrua',
	en_RubyLeft					= 'Jrlf',
	en_RubyCenter				= 'Jrct',
	en_RubyRight				= 'Jrrt',
	en_RubyFullJustify			= 'Jrfj',
	en_RubyJIS					= 'Jrjs',
	en_RubyEqualAki				= 'Jrea',
	en_Ruby1Aki					= 'Jr1a',

	en_RubyParentSpacing		= 'Jers',
	en_RubyNoAdjustment			= 'Jrna',
	en_RubyBothSides			= 'Jrbs',
	en_Ruby121Aki				= 'Jr12',
	en_RubyEqualAki2			= 'Jrqa',
	en_RubyFullJustify2			= 'Jrsj',

	en_RubyOverhang				= 'Jruo',
	en_RubyOverhangNone			= en_None,
	en_RubyOverhangOneRuby		= 'Jro1',	// Not the same as jro1
	en_RubyOverhangHalfRuby		= 'Jro2',
	en_RubyOverhangOneChar		= 'Jroc',
	en_RubyOverhangHalfChar		= 'Jrhc',
	en_RubyUnrestricted			= 'Jrou',

	en_KinsokuType				= 'Jknt',
	en_KinsokuPushInFirst		= 'Jkif',
	en_KinsokuPushOutFirst		= 'Jkof',	// Not the same as 'jkof'
	en_KinsokuPushOutOnly		= 'Jkoo',
	en_KinsokuPushInAlways		= 'Jkia',

	en_KinsokuHangType			= 'Jkht',
	en_KinsokuHang_None			= en_None,
	en_KinsokuHang_Regular		= 'Jkhr',
	en_KinsokuHang_Force		= 'Jkhf',

	en_LeadingModel				= 'JLed',
	en_LeadingModel_Roman		= 'JlmR',
	en_LeadingModel_AkiBelow	= 'Jlab',
	en_LeadingModel_AkiAbove	= 'Jlaa',
	en_LeadingModel_Center		= 'Jlmc',
	en_LeadingModel_CenterDown	= 'Jlcd',

	en_MojikumiTable			= 'JMkT',
	en_DefaultMojikumiTbl1		= 'JM01',
	en_DefaultMojikumiTbl2		= 'JM02',
	en_DefaultMojikumiTbl3		= 'JM03',
	en_DefaultMojikumiTbl4		= 'JM04',
	en_DefaultMojikumiTbl5		= 'JM05',
	en_DefaultMojikumiTbl6		= 'JM06',
	en_DefaultMojikumiTbl7		= 'JM07',
	en_DefaultMojikumiTbl8		= 'JM08',
	en_DefaultMojikumiTbl9		= 'JM09',
	en_DefaultMojikumiTbl10		= 'JM10',
	en_DefaultMojikumiTbl11		= 'JM11',
	en_DefaultMojikumiTbl12		= 'JM12',
	en_DefaultMojikumiTbl13		= 'JM13',
	en_DefaultMojikumiTbl14		= 'JM14',
	en_DefaultMojikumiTbl15		= 'JM15',
	en_DefaultMojikumiTbl16		= 'JM16',

	en_KinsokuSet				= 'JKsS',
	en_HardKinsokuSet			= 'Jhks',
	en_SoftKinsokuSet			= 'Jsks',
	en_KoreanKinsokuSet			= 'KRks',
	en_SimpChineseKinsokuSet	= 'SCks',
	en_TradChineseKinsokuSet	= 'TCks',

	// Selection
	en_NothingEnum				= 'senm',
	en_Nothing					= 'nada',
	en_SelectionOptions			= 'enSl',
	en_AddTo					= 'add2',
	en_RemoveFrom				= 'remF',
	en_ReplaceWith				= 'repW',		//used starting with Firedrake #1096978
	en_Replace					= e_Replace,	//used pre-Firedrake
	en_SetKeyObject				= 'setk',

	// "Auto" settings for font, font style, color and size. Used by B&N.
	en_AutoEnum					= 'aenm',
	en_AutoValue				= 'auto',

	// OpenType
	en_FigureStyle				= 'OTfs',
	en_FigureStyle_Tabular		= 'OTft',
	en_FigureStyle_OldstyleProp = 'OTos',
	en_FigureStyle_LiningProp	= 'OTlp',
	en_FigureStyle_OldstyleTabular = 'OTot',
	en_FigureStyle_Default 		= en_Default,

	en_ExportStyleFormat 		= 'eXst', // Export/Import pdf export styles/printer styles enum
	en_PDFStyles				= 'fStl',
	en_PrinterStyles			= 'rStl',
	en_FlattenerStyles			= 'tStl',
	en_DocumentStyles			= 'dStl',

	en_LoadStyleFormat			= 'iXst',
	en_CharacterStyles			= 'CrSt',
	en_ParagraphStyles			= 'phSt',
	en_CharacterAndParagraphStyles = 'cpSt',
	en_TOCStyles				= 'TcSt',
	en_ClashResolutionStrategy	= 'ClRS',
	en_LoadAllWithOverwrite		= 'LAWO',
	en_LoadAllWithRename		= 'LAWR',
	en_Decline					= 'Decl',
	en_CharOrParaStyleType		= 'ChPt',
	en_TreatCharStyleAsOverride	= 'tCSO',
	en_StyleType				= 'sTyT',
	en_CharStyleType			= 'cHSt',
	en_ParaStyleType			= 'pGrt',
	en_NamedGrids				= 'NgSt',
	en_ObjectStyles             = 'OjSt',
	en_StrokeStyles				= 'lStl',
	en_TableStyles				= 'eTst',
	en_CellStyles				= 'eCst',
	en_TableAndCellStyles		= 'eTCs',

	en_MasterPageClashResolutionStrategy = 'MPCL',

	en_FirstBaselineEnum		= 'eFBO',// First Baseline offset enum
	en_AscentOffset				= 'MAso',
	en_CapHeightOffset			= 'MCHo',
	en_LeadingOffset			= 'MLdo',
	en_EmBoxHeightOffset		= 'MEHo',
	en_FixedHeightOffset		= 'NFHo',	//#1096978
	en_xHeightOffset			= 'MxHo',

	en_VerticalJustEnum 		= 'eVJA', //Vertical Justification Aignment enum
	en_Top						= 'top ',
	en_Bottom					= 'botm',
	en_Justify					= 'jstf',

	en_AutoSizeDimensionEnum		= 'eASD', // Auto sizing Dimension enum
	en_ASHeight						= 'heig',
	en_ASWidth						= 'widt',
	en_ASHeightAndWidth				= 'hnwi',
	en_ASHeightAndWidthProportional = 'hnwp',

	en_AutoSizeRefPointEnum		= 'eASR', // Auto Sizing Reference point enum
	en_ASTopLeft				= 'tole',
	en_ASTopCenter				= 'toce',
	en_ASTopRight				= 'tori',
	en_ASLeftCenter				= 'lece', 
	en_ASCenter					= 'cntr',
	en_ASRightCenter			= 'rice',
	en_ASBottomLeft				= 'bole', 
	en_ASBottomCenter			= 'boce',
	en_ASBottomRight			= 'bori',
	en_ASNone					= 'rNon',

	en_PageNumberStyle			= 'ePgN', // page number style enum used in sections
	en_Current					= 'Mcur',	// use current default
	en_RomanUpper				= 'MRmu',
	en_RomanLower				= 'MRml',
	en_LettersUpper				= 'MLru',
	en_LettersLower				= 'MLrl',
	en_Arabic					= 'Marb',
	en_Kanji					= 'MKji',
	en_DoubleLeadingZeros		= 'MDlz',
	en_TripleLeadingZeros		= 'MTlz',
	en_SingleLeadingZeros		= 'MSlz',
	en_FullWidthArabic			= 'MFWa',
	en_Asterisks					= 'Mast',

	// ME
	en_HebrewBiblical			= 'MHbb',
	en_HebrewNonStandard		= 'MHbn',
	en_ArabicAbjad				= 'MAaj',
	en_ArabicAlifBaTah			= 'MAat',

	en_AnchorPoint 				= 'eAnc', // anchor point enumerator used in rotate/scale/shear events
	en_TopLeftAnchor			= 'ANtl',
	en_TopCenterAnchor			= 'ANtc',
	en_TopRightAnchor			= 'ANtr',
	en_LeftCenterAnchor			= 'ANlc',
	en_CenterAnchor				= 'ANct',
	en_RightCenterAnchor		= 'ANrc',
	en_BottomLeftAnchor			= 'ANbl',
	en_BottomCenterAnchor		= 'ANbc',
	en_BottomRightAnchor		= 'ANbr',

	en_Locale 					= 'enLc',	// locale enum for locale property on app
	en_DanishLocale				= 'LCDn',
	en_EnglishLocale			= 'LCEn',
	en_EnglishInternationalLocale = 'LCEi',
	en_FinnishLocale			= 'LCFn',
	en_FrenchLocale				= 'LCFr',
	en_GermanLocale			= 'LCGm',
	en_ItalianLocale				= 'LCIt',
	en_PortugeseLocale			= 'LCPg',
	en_SpanishLocale			= 'LCSp',
	en_SwedishLocale			= 'LCSw',
	en_JapaneseLocale			= 'LCJp',
	en_DutchLocale				= 'LCDt',
	en_NorwegianLocale			= 'LCNw',
	en_KoreanLocale			= 'LCKo',
	en_SimpChineseLocale		= 'LCCn',
	en_TradChineseLocale		= 'LCTw',
	en_CzechLocale				= 'LCCz',
	en_PolishLocale         	    = 'LCPl',
	en_GreekLocale				= 'LCGr',
	en_HungarianLocale			= 'LCHu',
	en_RussianLocale			= 'LCRu',
	en_TurkishLocale			= 'LCTr',
	en_ArabicLocale				= 'LCAr',
   	en_HebrewLocale             = 'LCHb',
   	en_RomanianLocale             = 'LCRo',
   	en_UkrainianLocale             = 'LCUk',

	en_FeatureSet				= 'FSet',
	en_Roman					= 'Romn',
	en_Japanese					= 'Japn',

	// ME
	en_R2L						= 'RToL',

	en_TextFrameContents		= 'nTFc', // text frame contents enum
	en_PlaceHolderText			= 'PHtx',
	en_PlaceHolderTextArabic		= 'PHta',
	en_PlaceHolderTextHebrew		= 'PHth',
	en_PlaceHolderTextCyrillic		= 'PHtc',
	en_PlaceHolderTextGreek			= 'PHtg',

	en_RunInDelimiterElement	= 'RIde',	// nested style delimiter enum
	en_RI_Sentence				= 'RIds',
	en_RI_Word					= 'RIdw',
	en_RI_Character				= 'RIdc',
	en_RI_Letter				= 'RIdl',
	en_RI_Digit					= 'RIdd',
	en_RI_Tab					= 'RIdt',
	en_RI_Inline				= 'RIdi',
	en_RI_Dropcap				= 'RIdC',
	en_RI_RepeatLast			= 'RIrl',

	en_SpecialCharacter 			= 'nSPc', // special characters enum
	en_SC_AutoPageNumber		= 'SApn',
	en_SC_NextPageNumber		= 'SNpn',
	en_SC_PrevPageNumber		= 'SPpn',
	en_SC_SectionMarker			= 'SsnM',
	en_SC_FootnoteMarker		= 'SfnM',
	en_SC_TextVariable			= 'SPtv',
	en_SC_BulletNumbering		= 'SPbn',

	en_SC_BulletCharacter		= 'SBlt',
	en_SC_CopyrightSymbol		= 'SCrt',
	en_SC_DegreeSymbol			= 'SDgr',
	en_SC_EllipsisCharacter		= 'SLps',
	en_SC_ForcedLineBreak		= 'SFlb',
	en_SC_ParagraphSymbol		= 'SPar',
	en_SC_RegisteredTrademark	= 'SRTm',
	en_SC_SectionSymbol			= 'SsnS',
	en_SC_TrademarkSymbol		= 'STmk',

	en_SC_RightIndentTab		= 'SRit',
	en_SC_IndentToHere			= 'SIht',

	en_SC_EmDash				= 'SEmD',
	en_SC_EnDash				= 'SEnD',
	en_SC_DiscretionaryHyphen	= 'SDHp',
	en_SC_NonBreakingHyphen		= 'SNbh',
	en_SC_BreakRunInStyle	= 'SBRS',

	en_SC_DoubleLeftQuote		= 'SDLq',
	en_SC_DoubleRightQuote		= 'SDRq',
	en_SC_SingleLeftQuote		= 'SSLq',
	en_SC_SingleRightQuote		= 'SSRq',

	en_SC_SingleStraightQuote	= 'SSSq',
	en_SC_DoubleStraightQuote	= 'SDSq',

	// white space
	en_SC_EmSpace				= 'SEmS',
	en_SC_EnSpace				= 'SEnS',
	en_SC_FlushSpace			= 'SFlS',
	en_SC_HairSpace				= 'SHrS',
	en_SC_NonbreakingSpace		= 'SNbS',
	en_SC_ThinSpace				= 'STnS',
	en_SC_FigureSpace			= 'SFgS',
	en_SC_PunctuationSpace		= 'SPnS',
	en_SC_ThirdSpace			= 'SThS',
	en_SC_QuarterSpace			= 'SQuS',
	en_SC_SixthSpace			= 'SSiS',
	en_SC_NarrowNoBreakSpace	= 'Snnb',

	// break character
	en_SC_ColumnBreak			= 'SClB',
	en_SC_FrameBreak			= 'SFrB',
	en_SC_PageBreak				= 'SPgB',
	en_SC_OddPageBreak			= 'SOpB',
	en_SC_EvenPageBreak			= 'SEpB',
	en_SC_DiscretionaryLineBreak = 'SPdL',
	en_SC_ZeroWidthNonJoiner = 'SPnj',

	en_SC_xlFormattedTable			= 'xlFT',
	en_SC_xlUnformattedTable		= 'xlUT',
	en_SC_xlUnformattedTabbedText	= 'xUTT',
	en_SC_xlFormattedOnceTable		= 'xFOT',
	en_SC_UnformattedTable			= 'SCUT',
	en_SC_UnformattedTabbedText		= 'SUTT',

	//Special character ME
	en_SC_HebrewSofPasuk		= 'SHbs',
	en_SC_HebrewMaqaf			= 'SHbm',
	en_SC_HebrewGeresh			= 'SHge',
	en_SC_HebrewGershayim		= 'SHgs',
	en_SC_ArabicKashida			= 'SArk',
	en_SC_ArabicComma			= 'SArc',
	en_SC_ArabicSemicolon		= 'SAsc',
	en_SC_ArabicQuestionMark	= 'SAqm',
	en_SC_LeftToRightMark		= 'Slrm',
	en_SC_RightToLeftMark		= 'Srlm',
	en_SC_LeftToRightEmbedding	= 'Slre',
	en_SC_RightToLeftEmbedding	= 'Srle',
	en_SC_PopDirectionalFormatting = 'Spdf',
	en_SC_LeftToRightOverride	= 'Slro',
	en_SC_RightToLeftOverride	= 'Srlo',
	en_SC_DottedCircle			= 'Sdtc',
	en_SC_ZeroWidthJoiner		= 'Szwj',

	en_ImageColorSpace = 		'enIC', 	// Image Color Space

	en_BookRepaginate			= 'Brpo',

	en_BookContentStatus 		= 'BoCS',
	en_DocMising				= 'DocM',
	en_DocOutofDate				= 'DocD',
	en_DocInUse					= 'DocI',
	en_DocOpen					= 'DocO',

	// TOC enumerations
	en_TOCPageNumPostion 		= 'pnpn',
	en_AfterEntry				= 'afen',
	en_BeforeEntry				= 'bfen',

	// Indexing enumerations
	// Index idIndexCapitalizationOptions
	en_IndexCapitalizationOptions	= 'IxCo',
	en_SelectedTopicEntry		= 'STpe',
	en_IncludeSubentries		= 'iSbE',
	en_AllLevel1Entries			= 'ALEt',
	en_AllEntries				= 'AllE',
	en_IncludeOverset			= 'iOvt',
	// Indexing Sort Option Header Types
	en_IndexingSortOptionHeaderTypes = 'soHT',
	en_BasicLatin		= 'HTBL',
	en_SwedishFinnish	= 'HTSF',
	en_DanishNorwegian	= 'HTDN',
	en_Spanish			= 'HTSp',
	en_Croatian			= 'HTCr',
	en_Czech			= 'HTCz',
	en_Estonian			= 'HTEs',
	en_Hungarian		= 'HTHu',
	en_Latvian			= 'HTLa',
	en_Lithuanian		= 'HTLi',
	en_Polish			= 'HTPo',
	en_Romanian			= 'HTRo',
	en_Slovak			= 'HTSk',
	en_Slovenian		= 'HTSn',
	en_Turkish			= 'HTTu',
	// Cyrillic
	en_Belarusian		= 'HTBe',
	en_Bulgarian		= 'HTBu',
	en_Russian			= 'HTRu',
	en_Ukrainian		= 'HTUk',

	// Korean
	en_KoreanConsonant		= 'HTKo',
	en_KoreanConsonantVowel	= 'HTKV',

	// Japanese
	en_HiraAll			= 'HTHA',
	en_HiraCons			= 'HTHC',
	en_KataAll			= 'HTKA',
	en_KataCons			= 'HTKC',

	// Chinese
	en_ChinesePinyin	= 'HTCP',
	en_ChineseStroke	= 'HTCS',

	// ME
	en_CharacterDirection	=	'chdi',
	en_ParagraphDirection	=	'padi',
	en_StoryDirection		=	'stdi',
	en_TableDirection		=	'tadi',
	en_DefaultDirection   	=	'Defd',
	en_L2RDirection			=	'L2Rd',
	en_R2LDirection			=	'R2Ld',
	en_UnknownDirection		=	'Unkd',

	en_DigitsType			=	'dity',
	en_DigitsDefault		=	'dide',
	en_DigitsArabic			=	'diar',
	en_DigitsHindi			=	'dihi',
	en_DigitsFarsi			=	'difa',
#if 1	// qNewDigitSets
	en_DigitsNative			=	'dina',
	en_DigitsFullFarsi		=	'diff',
	en_DigitsThai			=	'dith',
	en_DigitsLao			=	'dila',
	en_DigitsDevanagari		=	'didv',
	en_DigitsBengali		=	'dibe',
	en_DigitsGurmukhi		=	'digm',
	en_DigitsGujarati		=	'digj',
	en_DigitsOriya			=	'dior',
	en_DigitsTamil			=	'dita',
	en_DigitsTelugu			=	'dite',
	en_DigitsKannada		=	'dika',
	en_DigitsMalayalam		=	'dima',
	en_DigitsTibetan		=	'diti',
	en_DigitsKhmer			=	'dikh',
	en_DigitsBurmese		=	'dibu',
#endif

	en_KashidasType			=	'katy',
	en_KashidaDefault		=	'kade',
	en_KashidaOff			=	'kaof',

	en_DiacriticPosType		=	'dipt',
	en_DiacriticPosOff		=	'dpof',
	en_DiacriticPosLoose		=	'dplo',
	en_DiacriticPosMedium	=	'dpme',
	en_DiacriticPosTight		=	'dpti',
	en_DiacriticPosOT		=	'dpot',
	en_DiacriticPosOTFromBaseline	=	'dpob',

	en_ParaJustType		=	'pjut',
	en_ParaJustTypeDefault	=	'pjde',
	en_ParaJustTypeArabic	=	'pjar',
	en_ParaJustTypeNaskh	=	'pjna',
	en_ParaJustTypeTraditionalNaskhTatweel	=	'pjnt',
	en_ParaJustTypeTraditionalNaskhKashida	=	'pjnk',
	en_ParaJustTypeTraditionalNaskhTatweelFrac	=	'pjft',
	en_ParaJustTypeTraditionalNaskhKashidaFrac	=	'pjfk',

	// Index idIndexFormat
	en_IndexFormat				= 'IdFt',
	en_RunInIndexFormat		= 'RiIf',
	en_NestedIndexFormat		= 'NtIf',

	// Index idPageReferenceType
	en_PageReferenceType		= 'PgTp',
	en_SuppressPageNumbers	= 'nprg', // SuppressPageNumber
	en_CurrentPage				= 'crpg',
	en_ToNextStyleChange		= 'tnsc',
	en_ToNextUseOfStyle		= 'tnus', // nextStyleUID must be filled
	en_ToEndOfStory			= 'eost',
	en_ToEndOfDocument		= 'eodc',
	en_ToEndOfSection			= 'eosc',
	en_ForNextNParagraphs		= 'fnpr', // nParOrPage must be filled
	en_ForNextNPages			= 'fnpg',

	// Index idCrossReferenceType
	en_CrossReferenceType		= 'CrfT',
	en_SeeOrAlsoBracket			= 'SoAl',
	en_SeeAlso					= 'SeAl',
	en_See						= 'enSe',
	en_SeeHerein				= 'SHrn',
	en_SeeAlsoHerein			= 'SaHr',
	en_CustomCrossReference		= 'CstC', // customString must be != NULL and not empty
	en_CustomCrossReferenceBefore	= 'Cstb', // customString must be != NULL and not empty
	en_CustomCrossReferenceAfter	= 'Csta', // customString must be != NULL and not empty

	// SVG Export:
	en_FontSubsetting			= 'enFS',
	en_SubsetNone				= en_None, // Prior to 3.0 used to be'svSn',
	en_SubsetGlyphs				= 'svSg',
	en_SubsetEnglish			= 'svSe',
	en_SubsetGlyphsAndEnglish	= 'svSE',
	en_SubsetRoman				= 'svSr',
	en_SubsetGlyphsAndRoman		= 'svSR',
	en_SubsetEntire				= 'svSa',

	// SVG Export:
	en_RenderingStyle			= 'enRs',
	en_Progressive				= 'svRp',
	en_Batch					= 'svRb',

	// SVG Export:
	en_FileEncoding 			= 'enFE',
	en_UTF8						= 'svU8',
	en_UTF16					= 'sv16',

	// SVG Export:
	en_StyleFormat				= 'enSF',
	en_Inline					= 'svFi',
	en_Entity					= 'svFe',
	en_CSS						= 'svFc',
	en_PresentationAttr			= 'svFp',

	// rendering intents
	en_DefaultRenderingIntent   = 'dRIr',
	en_RenderingIntent          = 'RIri',
	en_UseColorSettings         = 'RIcs',
	en_Perceptual               = 'RIpc',
	en_Saturation               = 'RIsa',
	en_RelativeColormetric      = 'RIrc',
	en_AbsoluteColormetric      = 'RIac',

	// DL Item profile policies
	en_DLItemProfilePolicies	= 'Dpie',
	en_DLI_IgnoreAllProfiles	= 'Dpia',
	en_DLI_IgnoreOutputIntent	= 'Dpio',
	en_DLI_HonorAllProfiles		= 'Dpha',

	// Transparency:
	en_BlendMode				= 'enXM',
	en_XPBMNormal				= en_Normal,
	en_XPBMMultiply				= 'xpMb',
	en_XPBMScreen				= 'xpMc',
	en_XPBMOverlay				= 'xpMd',
	en_XPBMSoftLight			= 'xpMe',
	en_XPBMHardLight			= 'xpMf',
	en_XPBMColorDodge			= 'xpMg',
	en_XPBMColorBurn			= 'xpMh',
	en_XPBMDarken				= 'xpMi',
	en_XPBMLighten				= 'xpMj',
	en_XPBMDifference			= 'xpMk',
	en_XPBMExclusion			= 'xpMl',
	en_XPBMHue					= 'xpMm',
	en_XPBMSaturation			= en_Saturation,
	en_XPBMColor				= c_Color,
	en_XPBMLuminosity			= 'xpMp',

	// Transparency: Shadow mode
	en_ShadowMode				= 'enXS',
	en_XPDSOff					= en_None,
	en_XPDSDrop					= 'xpDP',

	// Transparency: Feather mode
	en_FeatherMode				= 'enXF',
	en_XPVGOff					= en_None,
	en_Standard					= 'xpFb',
	en_XPVGStandard				= en_Standard,

	// Transparency: Feather corners
	en_FeatherCornerType		= 'enXC',
	en_XPVGSharp				= 'xpCa',
	en_XPVGRounded				= 'xpCb',
	en_XPVGDiffusion			= 'xpCc',

	// Transparency: Glow technique
	en_GlowTechnique			= 'enX0',
	en_GLTechniqueSofter		= 'xp0a',
	en_GLTechniquePrecise		= 'xp0b',

	// Transparency: Inner glow source
	en_InnerGlowSource			= 'enX1',
	en_IGSourceCenter			= 'xp1a',
	en_IGSourceEdge				= 'xp1b',

	// Transparency: PMBevelEmbossStyle
	en_BevelEmbossStyle			= 'enX2',
	en_BEStyleOuterBevel		= 'xp2a',
	en_BEStyleInnerBevel		= 'xp2b',
	en_BEStyleEmboss			= 'xp2c',
	en_BEStylePillowEmboss		= 'xp2d',

	// Transparency: PMBevelEmbossTechnique
	en_BevelEmbossTechnique		= 'enX3',
	en_BETechniqueSmooth		= 'xp3a',
	en_BETechniqueChiselHard	= 'xp3b',
	en_BETechniqueChiselSoft	= 'xp3c',

	// Transparency: PMBevelEmbossDirection
	en_BevelEmbossDirection		= 'enX4',
	en_BEDirectionUp			= 'Fstn', // borrowed from XML, not defined in this header
	en_BEDirectionDown			= 'Fstd', // borrowed from XML, not defined in this header

	// Transparency: PMFollowShapeMode
	en_FollowShapeMode			= 'enX5',
	en_FollowShapeNone			= en_None,
	en_FollowShapeLeadingEdge	= 'en5a',
	en_FollowShapeAllEdges		= 'en5b',

	// Transparency:
	en_BlendingSpace			= 'enXB',
	en_XPBSDocDefault			= en_Default,
	en_XPBSRGB					= en_RGBcolor,
	en_XPBSCMYK 				= en_CMYKcolor,

	// Separations Preview Mode
	en_SepPrvMode				= 'enSP',
	en_SepPrvModeOff			= 'spm0',
	en_SepPrvModeOPP			= 'spm1',
	en_SepPrvModeComposite		= 'spm2',
	en_SepPrvModeSinglePlate	= 'spm3',
	en_SepPrvModeInkLimit		= 'spm4',

	//	Inks: Ink type
	en_InkTypes					= 'enIT',
	en_InkTypeOpaque			= 'itOp',
	en_InkTypeTransparent		= 'itTr',
	en_InkTypeOpaqueIgnore		= 'itIg',

	// Hyperlink Destination View Settings
	en_HyperlinkDestinationPageSetting	= 'HDSP',
	en_DestinationFixed					= 'HDSf',
	en_DestinationFitView				= 'HDSv',
	en_DestinationFitWindow				= 'HDSw',
	en_DestinationFitWidth				= 'HDSW',
	en_DestinationFitHeight				= 'HDSh',
	en_DestinationFitVisible			= 'HDSV',
	en_DestinationInheritZoom			= 'HDSz',
	en_RangeSortOrder			= 'hrso',
	en_NoSort					= 'nost',
	en_AscendingSort			= 'asds',
	en_DescendingSort			= 'dsst',
	
	// Hyperlink Appearance Highlights
	en_HyperlinkAppearanceHighlight = 'hAhl',
	en_Invert						= 'nvrt',
	en_Outline						= 'otln',
	en_Inset						= 'nset',

	// Hyperlink Appearance Widths
	en_HyperlinkAppearanceWidth = 'hAwd',
	en_Thin						= 'thin',
	en_Thick					= 'thik',

	// Hyperlink Appearance Styles
	en_HyperlinkAppearanceStyle = 'hAst',

	// Hyperlink alternate destination type
	en_HyperlinkSourceAltDestination = 'alde',
	en_IndexMarker = 'didx',
	en_TOCTextAnchor = 'dtan',

	// XRef format building blocks
	en_XRefBuildingBlockType		='xbbt',
	en_XRefBBCustomString			='bbcs',
	en_XRefBBFileName				='bbfn',
	en_XRefBBChapterNumber		='bbcn',
	en_XRefBBPageNumber			='bbpn',
	en_XRefBBFullParagraph			='bbfp',
	en_XRefBBParagraphNumber		='bpgn',
	en_XRefBBParagraphText			='bbpt',
	en_XRefBBBookmarkName		='bbbn',

	en_AssetType 				= 'aste',
	en_ImageType 				= 't_im',
	en_EPSType					= 't_EP',
	en_PDFType					= 't_PD',
	en_InteractivePDFType		= 't_iP',
	en_GeometryType				= 't_ge',
	en_PageType					= 't_pa',
	en_TextType					= 't_te',
	en_StructureType			= 't_st',
	en_InDesignFileType			= 't_id',

	// MetaData Enum
	en_CopyRightType			= 'mdcT',
	en_CopyRightUnknown			= 'mduK',
	en_CopyRightYes				= 'mdyE',
	en_CopyRightNo				= 'mdnO',
	// containter type
	en_ContainerType			= 'mdct',
	en_bag						= 'Mdbg',
	en_seq						= 'Mdsq',
	en_alt						= 'Mdat',

	// proofing types
	en_ProofType                = 'PTpt',
	en_ProofOff                 = 'PTof',
	en_ProofDocumentCMYK        = 'PTdc',
	en_ProofWorkingCMYK         = 'PTwc',
	en_Custom             	 	= 'Cstm',

	// color settings policy
	en_ColorSettingsPolicy      = 'CPcp',
	en_ColorSettingsPolicyOff   = 'CPof',
	en_PreserveEmbeddedProfiles = 'CPpp',
	en_ConvertToWorkingSpace    = 'CPws',
	en_ColorSettingsPolicyPDIL  = 'CPpd',

	// Screen Mode/Layout Preview
	en_ScreenModeOptions		= 'scmo',
	en_PreviewOff				= 'smpo',
	en_PreviewToPage			= 'smpp',
	en_PreviewToBleed			= 'smpb',
	en_PreviewToSlug			= 'smps',
	en_Presentation				= 'smpn',

	// graphics server enums
	en_ImageFileFormat			= 'iffm',
	en_TIFFFileFormat			= 'fTIF',
	en_PhotoshopFormat			= 'fPSD',
	en_EPSFormat				= 'fEPS',
	en_SVGFormat				= 'fSVG',
	en_LayerType				= 'layT',
	en_PixelLayer				= 'pixL',
	en_TextLayer				= 'txtL',
	en_ImageAlignment			= 'iAln',
	en_AlignImageLeft			= 'aLft',
	en_AlignImageRight			= 'aRgt',
	en_AlignImageCenter			= 'aCtr',
	en_AlignImageTop			= 'aTop',
	en_AlignImageBottom			= 'aBot',

// already defined in PrintScriptInfo.fr
//	en_RenderIntent				= 'rInt',
//	en_AbsoluteColorimetric		= 'riAC',
//	en_RelativeColorimetric		= 'riRC',
//	en_Perceptual				= 'riPe',
//	en_Saturation				= 'riSa',

	en_Direction				= 'eDir',
	en_LeftToRight			= 'l2r ',
	en_TopToBottom			= 't2b ',

	en_HorizontalBase			= 'hBas',
	en_LeftEdge					= 'iLft',
	en_RightEdge				= 'iRgt',
	en_HorizontalCenter			= 'hCtr',
	en_CurrentHorizPosition		= 'curH',

	en_VerticalBase				= 'vBas',
	en_TopEdge					= 'iTop',
	en_BottomEdge				= 'bott',
	en_VerticalCenter			= 'vCtr',
	en_CurrentVerticalPosition	= 'curV',

	en_ScalePolicy				= 'scaP',
	en_Free						= 'free',
	en_DoNotEnlarge			= 'noBg',
	en_DoNotShrink				= 'noSm',

	en_TrimBasedOn				= 'trim',
	en_TopLeft					= 'tplf',
	en_TopRight					= 'tprt',
	en_BottomLeft				= 'btlf',
	en_BottomRight				= 'btrt',
	en_Transparency			= 'xp  ',

	p_LayerType				= 'plyT',
	p_ImageHAlignment			= 'iAlH',
	p_ImageVAlignment			= 'iAlV',
	p_CanvasWidth				= 'cWid',
	p_CanvasHeight				= 'cHgt',
	p_RenderIntent				= 'rInt',
	p_X0						= 'pX0 ',
	p_Y0						= 'pY0 ',
	p_Direction					= 'pDir',
	p_ImageWidth				= 'iWid',
	p_ImageHeight				= 'iHgt',
	p_Resolution				= 'iRes',
	p_Resample					= 'resm',
	p_ConstrainProportions		= 'cons',
	p_ScalePolicy				= 'scaP',

	// borrowed terms (can't have name match but ID discrepancy in AS)
	p_XPAngle					= p_InkAngle,
	p_XPSpread					= c_Spread,
	p_XPWidth					= p_Width,
	p_XPSource					= p_HyperlinkSource, // uses enum 'enX1'
	p_XPLength					= p_Length,
	p_XPGradientType			= p_GradientType, // uses enum en_GradientType

	// user dictionaries
	en_ComposeUsing = 'cmpu',
	en_UserDict = 'Usrd',
	en_Both						= 'both',

	// Flattener Level for flattener settings
	en_FlattenerLevel		= 'flFl',
	en_MediumLow				= 'flML',
	en_MediumHigh				= 'flMH',

	// Flattener override flag for flattener settings on spread
	en_FlattenerSpreadOverride	= 'flFs',

	// Kenten/Ruby overprint fill/stroke
	en_AdornmentFill			= 'Jafl',
	en_OverprintOff = 'enof',
	en_OverprintOn = 'enon',

	// Font Status
	en_FontStatus						= 'fSTA',
  	en_FontStatusInstalled				= 'fsIn',
	en_FontStatusNotAvailable			= 'fsNA',
	en_FontStatusFauxed					= 'fsFa',
	en_FontStatusSubstitued				= 'fsSu',

	// Font Type
	en_FontType							= 'fTYP',
  	en_FontTypeType1					= 'ftT1',
	en_FontTypeTrueType					= 'ftTT',
	en_FontTypeCID						= 'ftCI',
	en_FontTypeATC						= 'ftAT',
	en_FontTypeBitmap					= 'ftBi',
	en_FontTypeOCF						= 'ftOC',
	en_FontTypeOpenTypeCFF				= 'ftOF',
	en_FontTypeOpenTypeCID				= 'ftOI',
	en_FontTypeOpenTypeTT				= 'ftOT',
	en_UnknownFontType					= 'ftUn',

	// Open type features
	en_OTFeature						= 'OTFf',
	en_OTFDiscLigFeature				= 'OTdL',
	en_OTFFractionFeature 				= 'OTfR',
	en_OTFOrdinalFeature				= 'OToR',
	en_OTFSwashFeature				= 'OTsW',
	en_OTFTitlingFeature				= 'OTtI',
	en_OTFContextAltFeature			= 'OTcA',
	en_CapToSmallCapFeature 			= 'c2sC',
	en_PosOTSuperscriptFeature			= 'pOTS',
	en_PosOTSubscriptFeature			= 'pOTB',
	en_PosOTNumeratorFeature			= 'pOTN',
	en_PosOTDenominatorFeature 		= 'pOTD',
	en_FigureStyle_TabularFeature		= 'OTfT',
	en_FigureStyle_OldstylePropFeature	= 'OToS',
	en_FigureStyle_LiningPropFeature	= 'OTlP',
	en_FigureStyle_OldstyleTabularFeature = 'OToT',
	en_FigureStyle_DefaultFeature 		= 'OTfD',

	// ME Open type features
	en_OTFOverlapSwashFeature			= 'OToV',
	en_OTFStylisticAltFeature			= 'OTsT',
	en_OTFJustifAltFeature				= 'OTjU',
	en_OTFStretchedAltFeature			= 'OTsR',

	en_ExportImageConversion			= 'eiic',
	en_ImageAutomatic					= 'ibst',

	en_JPEGEncoding					= 'jpge',
	en_JPEGBaseline						= 'jpgb',
	en_JPEGProgressive					= 'jpgp',

	en_JPEGQuality						= 'jpgq',

	en_PaletteType						= 'plty',
	en_AdaptivePalette					= 'plap',
	en_MacPalette						= 'plmp',
	en_WebPalette						= 'plwp',
	en_WinPalette						= 'plwd',

	// EPS export prefs
	en_DIColor							= 'Edic',	// depreciated - use en_UnchangedColorSpace instead
	en_EPSPreviewTIFF					= 'Eptf',
	en_EPSPreviewPICT					= 'Eppt',
	en_EPSPreview						= 'Eprv',
	en_EPSColorSpace					= 'ECSp',
	en_EPSFontEmbedding				= 'Efeb',
	en_EPSSendImageData				= 'Esid',

	// EPS import preferences
	en_EIMode							= 'eImo',
	en_EIProxy							= 'eIpc',
	en_EINever							= 'eInv',
	en_EINeeded						= 'eInd',
	en_EIAlways						= 'eIaw',

	en_ObsoleteEnumerators				= 'obso',

	// Color override
	en_Override					= 'eOvr',
	en_SpecialPaper				= 'eOvP',
	en_SpecialBlack				= 'eOvB',
	en_SpecialRegistration		= 'eOvR',
	en_HiddenReserved			= 'eOvH',
	en_MixedInkParent			= 'eOvM',

	en_PathEffect			= '__pe',
	en_PathEffectRainbow	= '_pfr',
	en_PathEffectSkew		= '_pfs',
	en_PathEffect3DRibbon	= '_pf3',
	en_PathEffectStairStep	= '_pss',
	en_PathEffectGravity		= '_pfg',

	en_PathAlignment			= 'paal',
	en_PathAlignmentTop		= 'pat_',
	en_PathAlignmentBottom		= 'pab_',
	en_PathAlignmentCenter		= 'pac_',

	en_FlipValue				= 'flvl',
	en_NotFlipped				= 'nflp',
	en_Flipped					= 'yflp',
	en_UndefinedFlip			= 'uflp',

	en_TextTypeAlignments		= 'taal',
	en_TextAlignmentAscender	= 'taas',
	en_TextAlignmentDescender	= 'tads',
	en_TextAlignmentCenter		= 'tact',
	en_TextAlignmentBaseline	= 'tabl',
	en_TextAlignmentAboveRightEmbox	= 'tare',
	en_TextAlignmentBelowLeftEmbox	= 'tble',
	en_TextAlignmentAboveRightICFBox	= 'tari',
	en_TextAlignmentBelowLeftICFBox	= 'tbli',

	en_StrokeAlignment			= 'stAm',
	en_TextStrokeAlign			= 'stAl',
	en_StrokeAlignCenter		= 'stAC',
	en_StrokeAlignInside		= 'stAI',
	en_StrokeAlignOutside		= 'stAO',

	en_LineAlignment			= 'lnal',
	en_LeftTopLineAlignment		= 'lalt',
	en_CenterLineAlignment		= 'lacn',
	en_RightBottomLineAlignment	= 'larb',
	en_LeftTopLineJustify		= 'lltj',
	en_CenterLineJustify			= 'lcnj',
	en_RightBottomLineJustify	= 'lrbj',
	en_FullLineJustify			= 'lflj',

	en_GridStartingPoint = 'Gstp',
	en_TopOutside = 'gsto',
	en_TopInside = 'gsti',
	en_BottomOutside = 'gsbo',
	en_BottomInside = 'gsbi',
	en_CenterVertical = 'gscv',
	en_CenterHorizontal = 'gsch',
	en_CenterCompletely = 'gscc',

	en_GridCharCountLocEnum 		= 'Jccl',
	// en_None, en_Top, en_Left, en_Bottom, en_Right

	en_Off = 			'OFF ',
	en_PageNumbering = 'EPgn',
	en_Absolute = 		'Absl',
	en_PreviewSize = 	'EPrS',
	en_Small = 			'SmPr',
	en_Large = 			'LaPr',
	en_ExtraLarge = 	'ELPr',
	en_PreviewPages =	'EPrP',
	en_First2Pages =	'F2Pg',
	en_First5Pages =	'F5Pg',
	en_First10Pages =	'FXPg',
	en_ToolTips = 		'ETip',
	en_Fast = 			'Fast',
	en_ToolsPalette = 	'ETpl',
	en_ToolsPanel = 	'ETpn',
	en_SingleColumn = 	'EScl',
	en_DoubleColumn = 	'EDcl',
	en_SingleRow	= 	'ESrw',
	en_PatientUserDelay = 'EPud',
	en_Never =			'PUNv',
	en_Immediately =	'PUIm',
	en_Delayed =		'PUDe',

	// Measurement units and rulers
	en_MeasurementUnits		= 'mmun',
	en_MeasPoints				= 'zpoi',
	en_MeasInches				= 'zinc',
	en_MeasInchesDecimal		= 'zind',
	en_MeasCM					= 'zcms',
	en_MeasMM					= 'zmms',
	en_MeasPicas				= 'zpic',
	en_MeasCiceros				= 'zcic',
	en_MeasCustom				= en_Custom,
	en_MeasQ					= 'zque',	// CJK "Q" measurement
	en_MeasHa					= 'Zha ',	// CJK "Ha"
	en_MeasAmericanPoints		= 'ZApt',	// CJK American Points
	en_MeasAgates				= 'zAgt',
	en_MeasCubits				= 'zcub',
	en_MeasU					= 'zJU ',	// CJK "U"
	en_MeasBai					= 'zBai',	// CJK "Bai"
	en_MeasMils					= 'zMil',	// CJK "Mils"
	en_MeasPx					= 'zpix',	// Pixels

	en_RulerCoordinate 			= 'MRcd',
	en_SpreadOrigin				= 'RCSo',
	en_PageOrigin				= 'RCPo',
	en_SpineOrigin				= 'RCSp',

	en_FrameGridView			= 'jFGV',
	en_GridView					= 'jGgv',
	en_ZNView					= 'jGzv',
	en_AlignView				= 'jGav',
	en_GridAndZNView			= 'jGgz',

	// baseline frame grid
	en_RelativeOptionEnum = 'ENro',
	en_TopOfPage		  = 'ETor',
	en_TopOfMargin		  = 'ETom',
	en_TopOfFrame		  = 'ETof',
	en_TopOfInset		  = 'EToi',

	//Print Booklet enumerations

	//Booklet Type Enum
	en_PBBookletTypeEnum =	'EnBT',
	en_PB2UpSaddleStitch =	'B2SS',		/* 2-Up Saddle Stitch */
	en_PB2UpPerfectBound =	'B2PB',		/* 2-Up Perfect Bound */
	en_PB2UpConsecutive =	'B2CS',		/* 2-Up Consecutive */
	en_PB3UpConsecutive =	'B3CS',		/* 3-Up Consecutive */
	en_PB4UpConsecutive =	'B4CS',		/* 4-Up Consecutive */

	//Signature Size Enum
	en_PBSigSizeEnum =		'EnBS',
	en_PBSigSize4 =			'BS04',		/* Signature size 4 */
	en_PBSigSize8 =			'BS08',		/* Signature size 8 */
	en_PBSigSize12 =		'BS12',		/* Signature size 12 */
	en_PBSigSize16 =		'BS16',		/* Signature size 16 */
	en_PBSigSize32 =		'BS32',		/* Signature size 32 */

	// Numbered Paragraphs Options for TOC entries
	en_TOCNumberedParagraphsOptions = 'tnpa',		// Numbered Paragraph Option in TOC
	en_IncludeFullParagraph = 'tifp',		// Include the full paragraph
	en_IncludeNumbersOnly = 'tino',			// Include the Numbers Only
	en_ExcludeNumbers = 'tenu',				// Exclude the numbers

	// Alignment and distribute of page items
	en_AlignDistributeBoundsTypeEnum =		'aDeT',
	en_ToItems = 							'ToiT',
	en_ToPage =							'TopA',
	en_ToMargins = 							'TomA',
	en_ToSpread =							'TosP',
	en_ToKeyObject =						'eKey',
	en_AlignOptionsEnum = 					'aOEn',
	en_DistributeOptionsEnum =				'dOEn',
	en_LeftEdges = 							'LfEd',
	en_TopEdges = 							'TpEd',
	en_RightEdges =							'RtEd',
	en_BottomEdges = 						'BtEd',
	en_HorizontalCenters =					'HoZc',
	en_VerticalCenters =					'VeTc',
	en_HorizontalSpace =					'HoZs',
	en_VerticalSpace = 						'Vets',

	en_PreflightRuleAlertStatusEnum =		'rFEn',
	en_RuleDisabled	=						'eRDb',
	en_RuleReturnsError	=					'eREr',
	en_RuleReturnsWarning =					'eRRw',
	en_RuleReturnsInformational	=			'eRRi',

	en_PreflightRuleVisitResultEnum =		'rVRS',
	en_InvalidResult =						'eVIn',
	en_RuleSatisfied =						'eVRs',
	en_RuleFailed =							'eVFl',
	en_InternalError =						'eVIe',
	en_VisitNotComplete =					'eVNc',

	en_PreflightRuleDataTypeEnum =			'rDTE',
	en_RuleData_Int32Type =					'rtIn',
	en_RuleData_RealType =					'rtRl',
	en_RuleData_StringType =				'rtSr',
	en_RuleData_BoolType =					'rtBl',
	en_RuleData_ObjectType =				'rtOb',
	en_RuleData_Int16Type =					'rtSi',
	en_RuleData_ListType =					'rtLt',

	en_PreflightLayersEnum =				'pfLE',
	en_PreflightVisibleLayers =				'plVL',
	en_PreflightAllLayers =					'plAL',
	en_PreflightVisiblePrintableLayers =	'plVP',

	en_PreflightScopeOptionsEnum =			'pfSE',
	en_PreflightScope_AllPages =			'pcAP',
	en_PreflightScope_PageRanges =			'pcPG',
	en_PreflightScope_SelectedDocs =		'pcSD',
	en_PreflightScope_AllDocs =				'pcAD',

	en_PreflightProfilePolicyEnum =			'pfDE',
	en_PreflightProfile_UseEmbedded =		'pdEM',
	en_PreflightProfile_UseProfile =		'pdPF',
	//en_PreflightOpenDoc_Off =				'pdOF'

	en_AnimationEaseTypeEnum =				'EsEm',
	en_AnimationNoEase =					'zNoE',
	en_AnimationEaseIn =					'zEsI',
	en_AnimationEaseOut =					'zEsO',
	en_AnimationEaseInOut =					'zEIO',
	en_AnimationEaseReadOnly =				'zERO',

	en_AnimationDesignOptionsEnum =			'AOEm',
	en_AnimationFrom =						'amFm',
	en_AnimationTo =						'amTo',
	en_AnimationOffset =					'amOf',

	en_TimingTriggerEventEnum =				'tmEm',
	en_noTriggerEvent =						'tmNv',
	en_OnPageLoad =							'tmPL', 
	en_OnPageClick =						'tmPC',
	en_OnStateLoad =						'tmSL',
	en_OnClick =							'tmCl',
	en_OnRelease =							'tmRl',
	en_OnRollover =							'tmRv',
	en_OnRolloff =							'tmRf',
	en_OnSelfClick =						'tSCl',
	en_OnSelfRolloff =						'tSRf',

	// epub and html export
	en_EPubHTMLExportOrder =				'ebeo',
	en_Layout =								'ebly',
	en_ArticlePanel =						'ebap',
	en_XMLStructure =						'ebxs',

	en_EPubCover =							'ebco',
	en_FirstPage =							'ebfP',
	en_ChosenPage =							'ecfP',
	en_ExternalImage =						'ebxi',

	en_EPubPageRangeFormat	=				'ebrf',
	en_kAllPages			=				'ealp',
	en_kUseRange			=				'ebur',

	en_EPubNavigationStyle	=				'epnv',
	en_kNoNavigation		=				'ennv',
	en_kFileNameNavigation	=				'efnv',
	en_kTOCStyleNavigation	=				'etnv',
	en_kBookMarkNavigation	=               'ebnv',
	en_kPages	=							'ebpv',
	en_kSpread	=							'ebsv',

	en_EPubSpreadControlOption	=			'esco',
	en_kSpreadsBasedOnDocument	=			'ebod',
	en_kSpreadsSynthetic		=			'esyn',
	en_kSpreadsPhysical			=			'ephy',
	en_kSpreadsNone				=			'esno',

	en_BulletListOption =		'ebbl',
	en_MapToUnorderedList =		'ebmU',
	en_ConvertToText =			'ebct',

	en_NumberedListOption =		'ebno',
	en_MapToOrderedList =		'ebmo',
	en_MapToStaticOrderedList =	'ebms',

	en_EPubXHTMLCSSOption =		'ebhs',
	en_EmbeddedCSS =			'ebeb',
	en_StyleNameOnly =			'ebsn',
	en_ExternalCSS	=			'ebex',

	en_ImageExportOption =		'ebie',
	en_Original =				'ebor',
	en_Optimized =				'ebop',
	en_LinkToServer =			'ebls',

	en_EPubVersion =			'ever',
	en_EPUB2 =					'eve2',
	en_EPUB3 =					'eve3',
	en_EPUB3PGT =				'ev3p',

	// Tagged PDF structure order
	en_PDFStructureOrder =		'PSOr',
	en_XMLStructureOrder =		'PxSo',
	en_ArticlesOrder =			'PaOr',

	en_FootnotePlacement =		'eftt',
	en_FootnoteAfterStory =		'eftS',
	en_FootnoteAfterParagraph =	'eftp',
	en_FootnoteInsidePopup =	'eft3',

	// Scene7 FXG PlugIn
	en_ExportFormatScene7FXG =	'SFXG',

	//Text direction
	en_TextDirection =			'eTDn',
	en_TextDirectionHorizontal ='etdh',
	en_TextDirectionVertical =	'etdv',
	en_TextDirectionMixed =		'etdm',
	en_TextDirectionUnknown =	'etdu',
};

enum UIColors
{
	en_UIColors				= 'uicl',
	en_UILightBlue 			= 'iLbl',
	en_UIRed				= 'iRed',
	en_UIGreen				= 'iGrn',
	en_UIBlue				= 'iBlu',
	en_UIYellow				= 'iYlw',
	en_UIMagenta			= 'iMgn',
	en_UICyan				= 'iCyn',
	en_UIGray				= 'iGry',
	en_UIBlack				= 'iBlk',
	en_UIOrange			= 'iOrn',
	en_UIDarkGreen			= 'iDgr',
	en_UITeal				= 'iTel',
	en_UITan				= 'iTan',
	en_UIBrown				= 'iBrn',
	en_UIViolet				= 'iVlt',
	en_UIGold				= 'iGld',
	en_UIDarkBlue			= 'iDbl',
	en_UIPink				= 'iPnk',
	en_UILavender			= 'iLvn',
	en_UIBrickRed			= 'iBrd',
	en_UIOlive				= 'iOlv',
	en_UIPeach				= 'iPch',
	en_UIBurgundy			= 'iBrg',
	en_UIGrassGreen		= 'iGgr',
	en_UIOchre				= 'iOcr',
	en_UIPurple				= 'iPrp',
	en_UILightGray			= 'iLgr',

	// Japanese colors
	en_UICharcoal			= 'iChl',
	en_UIGridBlue			= 'iGbl',
	en_UIGridOrange		= 'iGor',
	en_UIFiesta				= 'iFie',
	en_UILightOlive			= 'iLol',
	en_UILipstick			= 'iLip',
	en_UICuteTeal			= 'iCtl',
	en_UISulphur			= 'iSul',
	en_UIGridGreen			= 'iGdg',

	// InCopy Colors
	en_InCopyUIColors		= 'ICUI',
	en_UIWhite				= 'iWht',
	en_UICanary			= 'iCny',
	en_UILemon				= 'iLmn',
	en_UIElectrolyte			= 'iElc',
	en_UILime				= 'iLim',
	en_UIForest				= 'iFst',
	en_UILichen				= 'iLic',
	en_UIOliveGreen			= 'iOlv',	// same as en_UIOlive
	en_UIJade				= 'iJad',
	en_UIAqua				= 'iAqa',
	en_UICirrus				= 'iCir',
	en_UIEther				= 'iEth',
	en_UISlate				= 'iSlt',
	en_UIUltramarine		= 'iUlm',
	en_UIMidnight			= 'iMid',
	en_UIBlueberry			= 'iBlb',
	en_UIEggplant			= 'iEgg',
	en_UIGrape				= 'iGrp',
	en_UIFuchsia			= 'iFus',
	en_UIIris				= 'iIrs',
	en_UICarnation			= 'iCar',
	en_UIMocha				= 'iMoc',
	en_UIWheat				= 'iWhe',
	en_UIMustard			= 'iMus',
	en_UIAmber				= 'iAmb',
	en_UICornstarch			= 'iCrn',
	en_UIPowder			= 'iPow',
	en_UISmoke				= 'iSmk',
	en_UIGraphite			= 'iGph',
	en_UIGunmetal			= 'iGun',

	// black box paint types.
	en_AGMBlackBoxType           = 'bbte',
	en_AGMBlackBoxTypeAxial      = 'bbta',
	en_AGMBlackBoxTypeRadial     = 'bbtr',
	en_AGMBlackBoxTypeMesh       = 'bbtm',
	en_AGMBlackBoxTypeConstant   = 'bbtc',

	en_EncodingType              = 'eten',
	en_EncodingTypeHex           = 'ethx',
	en_EncodingTypeAscii85       = 'eta8',
	en_EncodingTypeAscii64       = 'eta6',

	en_ScriptLanguage			 = 'ScLg',
	en_AppleScript				 = 'ASLg',
	en_VisualBasic				 = 'VBLg',
	en_JavaScript				 = 'JSLg',

	en_AOPInline				= 'AOPi',
	en_AOPAboveLine			= 'AOPa',
	en_AOPAnchored			='AoPa',

	en_AOVEmBoxTop			= 'AVem',
	en_AOVEmBoxMiddle			= 'AVmM',
	en_AOVEmBoxBottom		= 'AVmB',
	en_AOVBaseline				= 'AVba',
	en_AOVBaselineL			= 'AVbl',
	en_AOVBaselineA			= 'AVas',
	en_AOVBaselineX			= 'AVxh',
	en_AOVBaselineC			= 'AVxc',

	en_AORPColumn				= 'APco',
	en_AORAnchor				= 'APan',
	en_AORPMargin				= 'APmg',
	en_AORPPage				= 'APpg',

	en_PageColor			= 'PCen',
	en_PCFollowMaster		= 'PCfm',
	en_TransformPositionRefPoint = 'TprP',
	en_PageEdge = 'PgEg',
	en_PageMargin = 'pGMg',
    en_dimensionAttributes  = 'dMAb',
    en_WidthOnly            = 'eWdO',
    en_HeightOnly           = 'eHtO',
    en_BothHeightWidth      = 'eWhb',
    en_PositionAttributes   = 'ePaB',
    en_XAttributeOnly       = 'eXAo',
    en_YAttributeOnly       = 'eYAo',
    en_BothXAndY            = 'eBxY'
};

// PerformanceMetric Enumerations
enum PerformanceMetric
{
	en_PerformanceMetricsSelector = 'PMSs',
	en_ServerStatisticSelector = 'stat',	// obsolete
	en_CPUTime				= 'cput',
	en_NumberThreads		= 'nthr',
	en_OverallSystemCPU		= 'Scpu',
	en_OverallUserCPU		= 'Ucpu',
	en_CoreAllocations		= 'CAlc',
	en_CoreSize				= 'CSiz',
	en_ResidentSize			= 'RSiz',
	en_VirtualSize			= 'VSiz',
	en_MemoryMark			= 'MMrk',
	en_HandleCount			= 'HCnt',
	en_GDIObjectCount		= 'GDIn',
	en_HeapAlloc =					'HAll',
	en_HeapAllocPeak =				'HAPk',
	en_MemPurgeCount =				'MPCt',
	en_MemPurgeTime =				'MPTm',
	en_BIBAlloc =					'BIBA',
	en_BIBAllocPeak =				'BAPk',
	en_BIBCache =					'BIBc',
	en_BIBCachePeak =				'BCPk',
	en_PDFAlloc =					'PDFA',
	en_PDFAllocPeak =				'PDAk',
	en_ImageCacheAlloc =			'ImCA',
	en_ImageCacheAllocPeak =		'ICAk',
	en_ImageCacheFileBytesRead =	'ImRd',
	en_ImageCacheFileBytesWritten =	'ImWr',
	en_ImageCacheFileReadTime =		'ICRd',
	en_ImageCacheFileWriteTime =	'ICWr',
	en_VXferAlloc =					'VXfA',
	en_VXferAllocPeak =				'VXAk',
	en_VXferBytesRead =				'VXfR',
	en_VXferBytesWritten =			'VXfW',
	en_VXferReadTime =				'VXRt',
	en_VXferWriteTime =				'VXWt',
	en_VXferFileBytesRead =			'VFBr',
	en_VXFerFileBytesWritten =		'VFBw',
	en_ProcessIOBytesRead =			'IORd',
	en_ProcessIOBytesWritten =		'IOWr',
	en_AGMXShowTime =				'AGMt',
	en_DBFileBytesRead =			'DBRd',
	en_DBFileBytesWrite =			'DBWr',
	en_DBFileReadTime =				'DBRt',
	en_DBFileWriteTime =			'DBWt',
	en_DropShadowMemReadTime =		'DSRt',
	en_DropShadowMemReadBytes =		'DSRb',
	en_DropShadowMemWriteTime =		'DSWt',
	en_DropShadowMemWriteBytes =	'DSWb',
	en_DropShadowFileReadTime =		'DFRt',
	en_DropShadowFileReadBytes =	'DFRb',
	en_DropShadowFileWriteTime =	'DFWt',
	en_DropShadowFileWriteBytes =	'DFWb',
	en_ChangeMgrUpdateCallCount =	'CMCt',
	en_ChangeMgrUpdateCallTime =	'CMTm',
	en_SnapshotCount =				'SSCt',
	en_GalleyCompositionTime =		'GCTm',
	en_LayoutCompositionTime =		'LCTm',
	en_GalleyCompositionCount =		'GCCt',
	en_LayoutCompositionCount =		'LCCt',
	en_DrawMgrDrawTime =			'DMTm',
	en_DrawMgrNumInterrupts =		'DMIn',
	en_SnapshotReadWriteTime =		'SRWt',
	en_NewSnapshotTime =			'SNwT',
	en_DBNewUIDCount =				'DBUi',
	en_DBInstantiateCount =			'DBIn',
	en_InstanceCachePurgeCount =	'ICPc',
	en_MinisaveCount =				'MSCt',
	en_XMPFilterTime =				'XMPt',
	en_SnapshotReadWriteByteCount =	'SRWc',
	en_DBFilePageReads =			'DBFr',
};

// document default language / region enums:
enum DocumentDefaults
{
// currently supported languages :
	en_ArabicAE =						'arAE',
	en_Czech_CzechRepublic =			'csCZ',
	en_Danish_Denmark =					'daDK',
	en_German_Germany =					'deDE',
	en_Greek_Greece =					'elGR',
	en_English_UnitedKingdom =			'enGB',
	en_English_UnitedStates =			'enUS',
	en_Spanish_Spain =					'esES',
	en_Finnish_Finland =				'fiFI',
	en_French_France =					'frFR',
	en_Hebrew_Israel =					'heIL',
	en_Hungarian_Hungary =				'huHU',
	en_Italian_Italy =					'itIT',
	en_Japanese_Japan =					'jaJP',
	en_Korean_RepublicOfKorea =			'koKR',
	en_Norwegian_Norway =				'nbNO',
	en_Dutch_Netherlands =				'nlNL',
	en_Polish_Poland =					'plPL',
	en_Portuguese_Brazil =				'ptBR',
	en_Russian_RussianFederation =		'ruRU',
	en_Swedish_Sweden =					'svSV',	// would have preferred svSE, but that is used by SVG export above
	en_Turkish_Turkey =					'trTR',
	en_Ukrainian_Ukraine =				'ukUA',
	en_Chinese_Simplified =				'zhCN',
	en_Chinese_Traditional =			'zhTW',
	en_Indic =							'indi',

// languages not translated into (yet):
	en_Belarusian_Belarus =				'beBY',
	en_Bulgarian_Bulgaria =				'bgBG',
	en_Estonian_Estonia =				'etEE',
	en_Croatian_Croatia =				'hrHR',
	en_Lithuanian_Lituania =			'ltLT',
	en_Latvian_Latvia =					'lvLV',
	en_Romanian_Romania =				'roRO',
	en_Slovak_Slovakia =				'slSK',
	en_Slovenian_Slovenia =				'slSI',
	en_Albanian_Albania =				'sqAL',
	en_Tamil_India =					'taIN',
	en_Thai_Thailand =					'thTH',
	en_Vietnamese_Vietnam =				'viVN',
};

//bullets and numbering scripting definitions
enum BNScriptingDefs
{
	c_BulletCharacter		= 'bnBF',

	p_BNListType			= 'bnlt',
	p_BNNumStyle			= 'bnns',
	p_BNBulletChar			= 'bnbc',
	p_BNFontStyle			= 'bnft',
	p_BNFontUID				= 'bnfn',
	p_BNSize				= 'bnfs',
	p_BNColor				= 'bncl',
	p_BNNumStartAt			= 'bnsa',
	p_BNNumSeparator		= 'bnsp',

	p_BNBulletCharType		= 'bnbt',
	p_BNBulletCharValue		= 'bnbv',

	en_ListType				= 'enLT',
	en_LTNone				= 'LTno',
	en_LTBullet				= 'LTbt',
	en_LTNumber				= 'LTnm',

	en_BulletCharType		= 'enBC',
	en_BCUnicodeOnly		= 'BCuo',
	en_BCUnicodeWithFont	= 'BCuf',
	en_BCGlyphWithFont		= 'BCgf',

	en_NumberingStyle		= 'enNS',

	en_KatakanaModern		= 'Ktkm',
	en_KatakanaTraditional	= 'Ktkt',

	p_BNBulletFontStyle		= 'blft',
	p_BNNumberingFontStyle	= 'nmft',
	p_BNBulletFontUID		= 'blfn',
	p_BNNumberingFontUID	= 'nmfn',
	//the enumerators for page number style are used for numbering style

    // Constants for Alignment
    en_BNAlignment          = 'bueA',
    en_BNHanging            = 'buAH',
    en_BNFlush              = 'buAf',
    en_BNCustom             = 'buAc',

    // Constants for Method Names
    e_ApplyBullets          = 'buAB',
    e_ApplyNumbers          = 'buAN',
    e_RemoveBN              = 'buRB',
	e_ConvertBNToText		= 'buCT',

    // Parameters for ApplyBullets method
    r_BulletChar            = 'buBc',
    r_BulletType            = 'buBT',
    r_BulletFontFamily      = 'buFF',
    r_BulletFontStyle       = 'buFS',
    r_BulletSize            = 'buBS',
    r_BulletColor           = 'buCO',
    r_BulletAlignment       = 'buAL',
    r_BulletLI              = 'buLI',
    r_BulletFLI             = 'buFL',
    r_BulletTab             = 'buTB',

    // Parameters for ApplyNumbers method
    r_NumberingStyle        = 'buNS',
    r_NumberingSeparator    = 'buNP',
    r_NumberingStartAt      = 'buNA',
    r_NumberFontFamily      = 'buFf',
    r_NumberFontStyle       = 'buFs',
    r_NumberSize            = 'buNs',
    r_NumberColor           = 'buNc',
    r_NumberAlignment       = 'buNa',
    r_NumberLI              = 'buLi',
    r_NumberFLI             = 'buFl',
    r_NumberTab             = 'buTb',

    // Obsolete constants for Bullet/Numbering Auto values. Now replaced by en_AutoValue.
    en_BNAutoFontUID        = 'buAU',
    en_BNTextFontUID        = 'buTU',

    en_BNAutoFontStyle      = 'buAF',
    en_BNTextFontStyle      = 'buTF',

    en_BNAutoColor          = 'buAC',
    en_BNTextColor          = 'buTC',

    en_BNAutoSize           = 'buAS',
    en_BNTextSize           = 'buTS',

    // ?Talk to Jonathan about
    e_RealResize			= 'RRes',
    p_AbsoluteVertical		= 'AbVr',
    p_AbsoluteHorizontal	= 'AbHz',
    p_DeltaVertical			= 'DlVr',
    p_DeltaHorizontal		= 'DlHz',
    p_ProportionalVertical	= 'PrVr',
    p_ProportionalHorizontal = 'prHz',

    e_ScaleSkew				= 'Sskw',
    e_TransformAgain		= 'TrAg',
    e_TransformSequenceAgain = 'TrSA',
    e_TransformAgainIndividually		= 'TrAI',
    e_TransformSequenceAgainIndividually = 'TrSI',

	// Bullet Collection
	c_ABulletCharacter		= 'bnoc',
	c_BulletCharacters		= 'bnos',

	// Screen Mode/Layout Preview
	p_ScreenMode		= 'smpr',

	// Advanced Numbering
	p_BulletTextAfter				= 'bnta',
	p_BulletCharStyle				= 'bnbs',
	p_BulletAlignment				= 'bnba',
	p_List							= 'bnnl',
	p_ListLevel						= 'bnle',
	p_NumberFormat					= 'DHnm',
	p_NumberExpresion				= 'bnne',
	p_NumberCharStyle				= 'bnnc',
	p_ContinueFromPreviousNumber	= 'bncp',
	p_NumberStartAt					= 'bnst',
	p_ApplyRestartPolicy			= 'bnar',
	//p_RestartPolicy					= 'bnta',
	p_NumberAlignment				= 'bnna',

	// List Collection
	c_NumberingList					= 'bnli',
	c_NumberingLists				= 'bnls',
	p_ContinueNumbersAcrossStories	= 'bncs',

	c_RestartPolicy					= 'bnrp',
	p_BNRestartPolicy				= 'bnbr',
	p_RestartPolicy					= 'bnnp',
	p_LowerLevel					= 'bnll',
	p_UpperLevel					= 'bnul',

	en_RestartPolicy				= 'enrp',
	en_RPAnyPreviousLevel			= 'enap',
	en_RPAfterSpecificLevel			= 'ensl',
	en_RPRangeOfLevels				= 'enrl',

    en_BNFormat						= 'enfo',
	en_FormatNone					= 'enfn',
	// Chapter Numbering constant
	c_ChapterNumberPreferences		= 'cnpo',
	p_ChapterNumberPreferences		= 'cnpp',
	en_ChapterNumberSources			= 'cntE',
	en_UserDefined					= 'cnud',
	en_ContinueFromPrevDoc			= 'cncp',
	en_SameAsPrevDoc				= 'cnsp',
	p_ChapterNumber					= 'cnpr',
	p_ChapterNumberSource			= 'cnSo',
	p_ChapterNumberFormat			= 'cnfp',

	// Book Numbering
	p_ContinueNumbersAcrossDocuments	=	'bncd',
	p_BulletAndNumberingResultText		=	'bnnr',
	p_NumberingResultNumber				=	'bnrn',
};

// Version Cue definitions
enum VersionCueDefs
{
	// Objects
	c_WGScriptPrefs				= 'vcPR',

	// Enums

	// Version state:
	en_VersionState				= 'vcVS',
	en_VersionUnknown			= 'vcVU',
	en_VersionProjectNewer		= 'vcVP',
	en_VersionLocalProjectMatch	= 'vcVM',
	en_VersionLocalNewer		= 'vcVL',
	en_VersionConflict			= 'vcVC',
	en_VersionNoResource		= 'vcVN',

	// Editing state:
	en_EditingState				= 'vcES',
	en_EditingUnknown			= 'vcEU',
	en_EditingNowhere			= 'vcEN',
	en_EditingRemotely			= 'vcER',
	en_EditingLocally			= 'vcEL',
	en_EditingLocallyLocked		= 'vcEK',
	en_EditingConflict			= 'vcEC',

	// Sync status:
	en_SyncStatus				= 'vcSS',
	en_SyncStatusDownloaded		= 'vcSD',
	en_SyncStatusUploaded		= 'vcSU',
	en_SyncStatusUnlocked		= 'vcSL',
	en_SyncStatusSkipped		= 'vcSK',
	en_SyncStatusNoChange		= 'vcSN',

	// Sync Conflict Resolution
	en_SyncConflictRes			= 'vcCR',
	en_SyncSkipConflicts		= 'vcCS',
	en_SyncAskUser				= 'vcCA',
	en_SyncPreferLocal			= 'vcCL',
	en_SyncPreferProject		= 'vcCP',

	// Properties
	p_VersionState				= 'qver',
	p_EditingState				= 'qedt',
	p_WGScriptPrefs				= 'vcPP',
	p_SyncConflictResolution	= 'vcPC',

	// Events
	e_SaveAVersion				= 'sver',
	e_RevertToProject			= 'rprj',
	e_SyncWithVersionCue		= 'synv',

	// Parameters
	r_VersionComment			= 'vcmt',
	r_ClobberAll				= 'vclb',
	r_SyncConflictResolution	= 'vcPC',

	e_MountProject				= 'mtpj',
	r_Url						= 'vurl',
	r_ProjectName				= 'pjnm'
};

enum S4SPEnums
{
	kS4SPSuite	=	'S4SP',

	r_Location	=	'rLOC',
	r_PreflightFrom	=	'rFRO',
	r_PreflightTo= 'rTO ',
	r_Fonts	=	'rFON',
	r_LinkedGraphics	=	'rLIN',
	r_UpdateGraphics	=	'rUGR',
	r_Profiles	=	'rPRO',
	r_HiddenLayers	=	'rHIL',
	r_IgnorePreflightErrors = 'rIPE',
	r_Report = 'rREP',
	r_IDML = 'rIDM',
	r_PDF = 'rPDF',
	r_PDFStyle = 'rSty',
	r_useDocHyphExceptionsOnly = 'rUHE',

	en_LinkType = 'eLNK',
	enProfileStatus = 'eIST'
};

enum DebugDefs
{
	p_PluginsWithUI				= 'UIPL',
	p_ModelPluginsWithUI		= 'MUPL',
	p_UIPluginsWithModel		= 'UMPL',
	e_TrackPlugins				= 'TKPg'
};

enum WatermarkDefs
{
	c_WatermarkPref				= 'WMpf',

	en_WatermarkVertPosition	= 'pVPe',
	en_WatermarkVPosTop			= 'pVPt',
	en_WatermarkVPosCenter		= 'pVPc',
	en_WatermarkVPosBottom		= 'pVPb',

	en_WatermarkHorzPosition	= 'pHpe',
	en_WatermarkHPosLeft		= 'pHPl',
	en_WatermarkHPosCenter		= 'pHPc',
	en_WatermarkHPosRight		= 'pHPr',

	p_WatermarkPref				= 'pPrf',
	p_WatermarkVisibility		= 'pVis',
	p_WatermarkDoPrint			= 'pPrn',
	p_WatermarkDrawInBack		= 'pDBk',
	p_WatermarkText				= 'pTxt',
	p_WatermarkFontFamily		= 'pFFm',
	p_WatermarkFontStyle		= 'pFSt',
	p_WatermarkFontPointSize	= 'pPtS',
	p_WatermarkFontColor		= 'pCol',
	p_WatermarkOpacity			= 'pOpc',
	p_WatermarkRotation			= 'pRot',
	p_WatermarkHorzPosition		= 'pHps',
	p_WatermarkHorzOffset		= 'pHof',
	p_WatermarkVertPosition		= 'pVPs',
	p_WatermarkVertOffset		= 'pVof'
};


/**
	Specifier forms.
*/
enum SpecifierForm
{
	kFormInvalid			= 0,
	kFormDefault			= en_Default,
	kFormIndex				= formAbsolutePosition,
	kFormUniqueID			= formUniqueID,
	kFormName				= formName,
	kFormPropertyID			= formPropertyID,
	kFormRange				= formRange,
	kFormFirst				= kAEFirst,
	kFormLast				= kAELast,
	kFormMiddle				= kAEMiddle,
	kFormAny				= kAEAny,
	kFormAll				= kAEAll,
	kFormPrevious			= kAEPrevious,
	kFormNext				= kAENext,
	kFormWhose				= formTest
} ;

enum CollectionAccessors
{
	e_Item					= 'item',
	e_ItemByName			= formName,
	e_ItemByID				= 'ByID',
	e_ItemByRange			= formRange,
	e_ItemWhose				= formTest,
	e_FirstItem				= kAEFirst,
	e_LastItem				= kAELast,
	e_MiddleItem			= kAEMiddle,
	e_PreviousItem			= kAEPrevious,
	e_NextItem				= kAENext,
	e_AnyItem				= kAEAny,
	e_EveryItem				= 'evry'
} ;

///////Articles start///////////
// Class ScriptIDs 
enum ArticleScriptClasses
{
	c_Article				= 'cArt',
	c_Articles				= 'cAts',
	c_Member				= 'cMem',
	c_Members				= 'cMbs',
	c_ArticleChild			= 'cAch',
	c_ArticleChildren		= 'cAcn',
};

enum ArticleScriptEvents
{
	e_PopulateArticle		= 'ePaR',
};

// Property ScriptIDs
enum ArticleScriptProperties
{
	p_ItemRef				= 'pItR',
	p_Articles				= 'pAts',
	p_ArticleChildrenList	= 'cAcL',
	p_ExportStatus			= 'pAeS'
};

//////////Articles end///////


///////Color Groups start///////////
// Class ScriptIDs 
enum ColorGroupScriptClasses
{
	c_ColorGroup				= 'cCgp',
	c_ColorGroups				= 'cCgs',
	c_ColorGroupMember			= 'cCMb',
	c_ColorGroupMembers			= 'cCMs',
};

// Property ScriptIDs
enum ColorGroupProperties
{
	p_ParentColorGroup		= 'pPcg',
	p_SwatchItemRef			= 'pSir',
	p_IsRootColorGroup		= 'pRcg',
};


//////////Color Groups end///////

///////Paragraph Border Shading start///////////
// 'ps' stands for Paragraph shading
// Property ScriptIDs 
enum ParaBSScriptProperties
{
	p_PBSFillOn				= 'pfOn',
	//common attributes for border and shading
	p_PBSOffsetL			= 'psOl',
	p_PBSOffsetR			= 'psOr',
	p_PBSOffsetT			= 'psOt',
	p_PBSOffsetB			= 'psOb',
	p_PBSWidth				= 'psWi',
	p_PBSTopOrigin			= 'psTo',
	p_PBSBottomOrigin		= 'psBo',
	p_PBSClipToFrame		= 'psCf',
	p_PBSSuppressPrinting	= 'psSp',

	p_PSCornerOptionTopLeft 	=	'scO1',
	p_PSCornerRadiusTopLeft 	=	'scr1',
	p_PSCornerOptionTopRight 	=	'scO2',
	p_PSCornerRadiusTopRight 	=	'scr2',
	p_PSCornerOptionBottomLeft 	=	'scO3',
	p_PSCornerRadiusBottomLeft 	=	'scr3',
	p_PSCornerOptionBottomRight =	'scO4',
	p_PSCornerRadiusBottomRight =	'scr4',

	// shading (fill) specific
	p_PBSFillOverprint		= 'psFo',
	p_PBSFillTint			= 'psFt',
	p_PBSFillColor			= 'psFc',

	// border (stroke) specific
	p_PBSStrokeOn			= 'psOn',
	p_PBSStrokeOverprint	= 'psSo',
	p_PBSStrokeTint			= 'psSt',
	p_PBSStrokeColor		= 'psSc',
	p_PBSStrokeGapOverprint = 'psGo',
	p_PBSStrokeGapTint		= 'psGt',
	p_PBSStrokeGapColor		= 'psGc',
	p_PBSStrokeType			= 'psSy',
	p_PBSStrokeWeightLeft	= 'psWL',
	p_PBSStrokeWeightTop	= 'psWT',
	p_PBSStrokeWeightRight	= 'psWR',
	p_PBSStrokeWeightBottom	= 'psWB',

	p_PBSStrokeEndCap 		= 'psEc',
	p_PBSStrokeEndJoin			= 'psEj',

	p_PBCornerOptionTopLeft 	=	'bcO1',
	p_PBCornerRadiusTopLeft 	=	'bcr1',
	p_PBCornerOptionTopRight 	=	'bcO2',
	p_PBCornerRadiusTopRight 	=	'bcr2',
	p_PBCornerOptionBottomLeft 	=	'bcO3',
	p_PBCornerRadiusBottomLeft 	=	'bcr3',
	p_PBCornerOptionBottomRight =	'bcO4',
	p_PBCornerRadiusBottomRight =	'bcr4',

	p_PBWidth			= 'pbWi',
	p_PBTopOrigin		= 'pbTo',
	p_PBBottomOrigin	= 'pbBo',
	p_PBOffsetL			= 'pbOl',
	p_PBOffsetR			= 'pbOr',
	p_PBOffsetT			= 'pbOt',
	p_PBOffsetB			= 'pbOb',
	p_PBSStrokeDisplayOnFlow = 'pbDf',
	p_PBSMergeConsecutiveBorders = 'pbMc'

};

enum ParaBSScriptEnum
{
	en_PBSWidth				= 'psWe',

	en_PBSTopOrigin				= 'psTe',
	en_PBSCapHeightTopOrigin	= 'psTc',
	en_PBSAscentTopOrigin		= 'psTa',
	en_PBSBaselineTopOrigin		= 'psTb',
	en_PBSLeadingTopOrigin		= 'pbTl',
	en_PBSxHeightTopOrigin		= 'psTx',
	en_PBSemBoxTopOrigin		= 'psTm',
	en_PBSemBoxCenterTopOrigin	= 'psTn',

	en_PBSBottomOrigin			= 'psBe',
	en_PBSDescentBottomOrigin	= 'psBd',
	en_PBSBaselineBottomOrigin	= 'psBb',
	en_PBSemBoxBottomOrigin		= 'psBm',
	en_PBSemBoxCenterBottomOrigin = 'psBn',

	en_PBWidth 				= 'pbWe',
	en_PBTopOrigin				= 'pbTe',
	en_PBBottomOrigin			= 'pbBe',
};

///////Paragraph Border Shading end///////////

///////PDF Import Comment start///////////

enum PDFImportCommentScriptIDs
{
    s_PDFImportCommentSuite = 'IMCs',
    c_Annotation            = 'ant ',
    c_Annotations           = 'ants',
    c_Reply                 = 'rep ',
    c_Replies               = 'reps',
    c_AnnotationPageDestination = 'pgd ',
    c_AnnotationPageDestinations    = 'pgds',
    c_AnnotationPageItemDestination = 'pmd ',
    c_AnnotationPageItemDestinations    = 'pmds',
    c_AnnotationTextDestination = 'txd ',
    c_AnnotationTextDestinations    = 'txds',
};

enum AnnotationStatusEnum
{
    en_AnnotationStatus     = 'as  ',
    en_OpenStatus           = 'asop',
    en_ResolvedStatus       = 'asre',
};

enum AnnotationTypeEnum
{
    en_AnnotationType       = 'at  ',
    en_StickyNote           = 'atsn',
    en_Highlight            = 'athl',
    en_UnderLine            = 'atul',
    en_Squiggly             = 'atsq',
    en_StrikeThrough        = 'atsr',
    en_ReplaceText          = 'atrt',
    en_InsertText           = 'atit',
    en_TextTypewriter       = 'attt',
    en_TextBox              = 'attb',
    en_FreeformDrawing      = 'atfd',
    en_LineSegment          = 'atls',
    en_Oval                 = 'atov',
    en_Rectangle            = 'atrl',
    en_Polygon              = 'atpl',
    en_Arrow                = 'atar',
    en_TextCallout          = 'attc',
    en_Stamp                = 'atsp',
    en_ConnectedLines       = 'atcn',
    en_Cloud                = 'atcd',
    en_InvalidAnnotationType= 'atin',
};

enum AnnotationProperties
{
    p_AnnotationReviewer    = 'anre',
    p_AnnotationContent     = 'anco',
    p_AnnotationDate        = 'anda',
    p_AnnotationStatus      = 'anst',
    p_AnnotationType        = 'anty',
    p_AnnotationFilePath    = 'anfp',
    p_AnnotationIsOrphan    = 'anio',
    p_AnnotationIsApplied   = 'ania',
    p_AnnotationDestination = 'ande',
    p_AnnotationPathGeometry    = 'anpg',
};

enum AnnotationMethods
{
    e_ChangeStatus          = 'cnst',
};

enum ReplyProperties
{
    p_ReplyReviewer         = 'rere',
    p_ReplyContent          = 'reco',
    p_ReplyDate             = 'reda',
};

enum AnnotationPageDestinationProperties
{
    p_AnnotationPageDestinationPage = 'papa',
    p_AnnotationPageDestinationHighlightRect = 'pahr',
    p_AnnotationPageDestinationTargetPoint  = 'patg',
};

enum AnnotationPageItemDestinationProperties
{
    p_AnnotationPageItemDestinationPageItem = 'pipi',
    p_AnnotationPageItemDestinationHighlightRect    = 'pihr',
    p_AnnotationPageItemDestinationTargetPoint  = 'pitg',
};

enum AnnotationTextDestinationProperties
{
    p_AnnotationTextDestinationStory = 'txst',
    p_AnnotationTextDestinationStartIndex   = 'txsx',
    p_AnnotationTextDestinationEndIndex = 'txex',
};

enum PDFCommentsDocMethods
{
    e_PDFImportComments = 'PDim',
};

///////PDF Import Comment end///////////

#endif	//#ifndef __SCRIPTINGDEFS__


