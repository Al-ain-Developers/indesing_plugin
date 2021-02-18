//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AdobePrefix.h $
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
//  Contains a list of all assigned Adobe prefixes. This is for reference only.
//  
//  Third party prefixes are in DeveloperPrefix.h
//  
//  IDs are 32 bits. That is split 24.8, where the top 24 holds the
//  prefix, and the lower 8 holds the ID within the prefix. All
//  prefixes that have been allocated are in this file. We can have
//  up to 16,777,215 different prefixes. Within each prefix there can
//  be up to 255 different IDs.
//  
//  NOTE: You should not need to include this file. If you would like some
//  debugging info about an ID, see DebugClassUtils.h
//  
//========================================================================================

#ifndef __AdobePrefix__
#define __AdobePrefix__

#ifdef ID_ENABLE_DEBUGGING
const int32 kLastAdobePrefix = 0x400;

typedef struct pluginprefix
{
	int32 prefix;
	const char* name;
} PluginPrefix;


PluginPrefix gPrefixList[] = {
//							{0x00,"UNUSED_PREFIX"},							// Unused
							{0x01,"ShuksanPrefix"},
							{0x02,"TextPrefix"},
							{0x03,"LayerPrefix"},
							{0x04,"GroupPrefix"},
							{0x05,"SpreadPrefix"},
							{0x06,"WidgetPrefix"},
							{0x07,"2nd WidgetPrefix"}, // don't name this WidgetPrefix, else debugging code will be misleading
							{0x08,"LayoutPrefix"},
							{0x09,"RectanglePrefix"},
							{0x0a,"PrintPrefix"},
							{0x0b,"LinePrefix"},
							{0x0c,"PolygonPrefix"},
							{0x0d,"DroverWidgetPrefix"},
							{0x0e,"DocumentPrefix"},
							{0x0f,"PageItemScrapPrefix"},

							{0x10,"CommandPrefix"},
							{0x11,"ToolBoxPrefix"},
							{0x12,"MeasurementSystemPrefix"},
							{0x13,"ColorPanelPrefix"},
							{0x14,"MasterPagesPrefix"},
							{0x15,"DimensionPanelPrefix"},
							{0x16,"GraphicsPrefix"},
							{0x17,"ImagePrefix"},
							{0x18,"PagesPanelPrefix"},
							{0x19,"TextEditorPrefix"},
							{0x1a,"CharPathPrefix"},
							{0x1b,"TextAttrPrefix"},
							{0x1c,"JPEGCodecPrefix"},
							{0x1d,"JPEGFilterPrefix"},
							{0x1e,"ZoomToolPrefix"},
							{0x1f,"ColorSystemPrefix"},

							{0x20,"ParaComposerPrefix"},
							{0x21,"StylePanelPrefix"},
							{0x22,"WorkspacePrefix"},
							{0x23,"OvalPrefix"},
							{0x24,"CJKIMEPrefix"},
							{0x25,"PDFPrefix"},
							{0x26,"ICFFilterPrefix"},
							{0x27,"UNUSED was K2StoryImportPrefix"},
							{0x28,"TextPrefix3"},
							{0x29,"DocumentContextPrefix"},
							{0x2a,"TIFFFilterPrefix"},
							{0x2b,"GraphicPanelsPrefix"},
							{0x2c,"GenericPrefix"},
							{0x2d,"LinguisticPrefix"},
							{0x2e,"ProximityPrefix"},
							{0x2f,"UNUSED was InsoPrefix"},

							{0x30,"UNUSED was SoftArtPrefix"},
							{0x31,"TextOptionsPanelPrefix"},
							{0x32,"HyphenationPanelPrefix"},
							{0x33,"GuidePrefix"},
							{0x34,"RulerPrefix"},
							{0x35,"StandOffPanelPrefix"},
							{0x36,"RosettaStonePrefix"},
							{0x37,"StandOffPrefix"},
							{0x38,"CommandPanelPrefix"},
							{0x39,"ImagePanelPrefix"},
							{0x3a,"SCTFilterPrefix"},
							{0x3b,"GIFFilterPrefix"},
							{0x3c,"DIBFilterPrefix"},
							{0x3d,"PCXFilterPrefix"},
							{0x3e,"FontMgrPrefix"},
							{0x3f,"TextPanelPrefix16"},					// See main body of TextPanelPrefix @ 0xe1

							{0x40,"SwatchesPanelPrefix"},
							{0x41,"NavigatorPrefixObsolete"},			// Obsolete, deleted in Basil
							{0x42,"CJKPrefix"},
							{0x43,"DictionaryPanelPrefix"},
							{0x44,"ColorUIPrefix"},
							{0x45,"PanelEditorPrefix"},
							{0x46,"UNUSED was DialogPrefix"},
							{0x47,"GraphicFramePrefix"},
							{0x48,"LayerPanelPrefix"},
							{0x49,"FindChangePrefix"},
							{0x4a,"UNUSED was ArrowPrefix"},
							{0x4b,"LinksPanelPrefix"},
							{0x4c,"SectionPrefix"},
							{0x4d,"ParaRulesPanelPrefix"},					// TextPanel
							{0x4e,"KeepPanelPrefix"},						// TextPanel
							{0x4f,"UNUSED was LangPanelPrefix"},

							{0x50,"RegPolyPrefix"},
							{0x51,"CJKLayoutPrefix"},
							{0x52,"SpellPanelPrefix"},
							{0x53,"StoryPanelPrefix"},
							{0x54,"GuideMgrPanelPrefix"},
							{0x55,"GradientFillPrefix"},
							{0x56,"DefaultStrokePrefix"},
							{0x57,"KnowledgeBasePrefix"},
							{0x58,"GraphicPanelPrefix"},
							{0x59,"SpreadHistoryPrefix"},
							{0x5a,"InstStrokeFillID"},
							{0x5b,"TextStylePanelPrefix"},					// TextPanel
							{0x5c,"TextColorPanelPrefix"},					// TextPanel
							{0x5d,"SectionUIPrefix"},
							{0x5e,"GradientUIPrefix"},
							{0x5f,"SpreadUIPrefix"},

							{0x60,"UNUSED was MMPanelPrefix"},
							{0x61,"PageSetupPanelPrefix"},
							{0x62,"SplinePrefix"},
							{0x63,"PM65FilterPrefix"},
							{0x64,"TipsPrefix"},
							{0x65,"AlignPanelPrefix"},
							{0x66,"EPSPrefix"},
							{0x67,"TabPanelPrefix"},
							{0x68,"TabPrefix"},
							{0x69,"CharPanelPrefix"},
							{0x6a,"ParaPanelPrefix"},
							{0x6b,"JustPanelPrefix"},
							{0x6c,"DownloadPrefix"},
							{0x6d,"PlaceURLPrefix"},
							{0x6e,"GraphicStylePrefix"},
							{0x6f,"GraphicStylePanelPrefix"},

							{0x70,"AutoLayoutPrefix"},
							{0x71,"AutoLayoutPanelPrefix"},
							{0x72,"ColorPickerPrefix"},
							{0x73,"OpenPlacePrefix"},
							{0x74,"UNUSED was CJKIMEPrefix"},
							{0x75,"kDragDropPrefix"},
							{0x76,"TransformPanelPrefix"},
							{0x77,"ScriptingPrefix"},
							{0x78,"ExportPrefix"},
							{0x79,"BenchmarkPanelPrefix"},
							{0x7a,"OffsetPathPrefix"},
							{0x7b,"SwatchLibPanelPrefix"},
							{0x7c,"ColorMgmtPrefix"},
							{0x7d,"RBColorMgmtPrefix"},
							{0x7e,"ColorMgmtUIPrefix"},
							{0x7f,"ColorSpacePrefix"},

							{0x80,"kCursorPrefix"},
							{0x81,"kWorkflowPrefix"},
							{0x82,"kCJKDialogPrefix"},
							{0x83,"kStrokePanelPrefix"},
							{0x84,"kTextWalkerServiceProviderPrefix"},
							{0x85,"kProgressBarPrefix"},
							{0x86,"LibraryPanelPrefix"},
							{0x87,"kClippingPanelPrefix"},
							{0x88,"kClippingDlgPrefix"},
							{0x89,"BasecampPrefix"},
							{0x8a,"TaggedTextFilters"},						// Adobe India
							{0x8b,"TaggedTextFiltersUI"},						// Adobe India
							{0x8c,"LinksPrefix"},
							{0x8d,"kAdobeOnlinePrefix"},
							{0x8e,"kEPSExportUIPrefix"},
							{0x8f,"kEPSImportUIPrefix"},

							{0x90,"FindChangeFormatPanelPrefix"},
							{0x91, "PDFImportPrefix"},
							{0x92, "PSFilterPrefix"},
							{0x93, "ExtendedAttributesPrefix"},					// Adobe India
							{0x94, "kImageImportUIPrefix"},
							{0x95, "AltGlyphPanelPrefix"},
							{0x96, "PDFPrinterMarksPrefix"},	// was this ever used?
							{0x97, "HelpPrefix"},
							{0x98, "AssetLibrary"},
							{0x99, "kGeneralPrefsDialogPrefix"},
							{0x9a, "PDFLPlugInPrefix"},
							{0x9b, "HistoryPanelPrefix"},
							{0x9c, "Package&Preflight UI"},
							{0x9d, "InScope/Workflow UI"},
							{0x9e, "Workflow UI"},
							{0x9f, "AboutboxPrefix"},

							{0xa0, "GradientTool"},
							{0xa1, "WritingStatsPrefix"},	// Bic
							{0xa2, "WritingMode"},			// Bic
							{0xa3, "CopyEditFilter"},		// Bic
							{0xa4, "InCopyShared"},
							{0xa5, "TrackChangesUI"},
							{0xa6, "DCSPrefix"},
							{0xa7, "PICTFilterPrefix"},
							{0xa8, "WMFFilterPrefix"},				// Adobe India
							{0xa9, "IntegratePrefix"},		// Bic -- depreciated
							{0xaa, "StepRepeatPrefix"},
							{0xab, "InCopyCore"},			// Bic
							{0xac, "obsolete TabStation"},			// InCopy
							{0xad, "TextFrameOptionsPrefix"},
							{0xae, "OpenType"},			// OpenType (type group)
							{0xaf, "FontUsageDialogPrefix"},

							{0xb0, "ScotchRules"},
							{0xb1, "PluginManager"},
							{0xb2, "FreeTransform"},
							{0xb3, "TextOnPath"},
							{0xb4, "QAMenuPrefix"},
							{0xb5, "InCopyWidgetBars"},
							{0xb6, "TableModelPrefix1"},
							{0xb7, "InCopyNoteTrackChanges"},
							{0xb8, "2nd TextEditorPrefix"},
							{0xb9, "ProfilerDataPrefix"},
							{0xba, "EyeDropperTool"},
							{0xbb, "Note"},					// Bic
							{0xbc, "GenericStyleEditorPrefix"},
							{0xbd, "PrinterStylesPrefix"},
							{0xbe, "InCopyFilterTest"},     // InCopy (Bic)
							{0xbf, "XMLPrefix"},

							//K2J
							{0xc0, "CJKPanelPrefix"},
							{0xc1, "MojikumiDialogPrefix"},
							{0xc2, "KinsokuDialogPrefix"},
							{0xc3, "PageGridDlgPrefix"},
							{0xc4, "FrameGridDlgPrefix"},
							{0xc5, "FrameInfoPanelPrefix"},
							{0xc6, "RubiDialogPrefix"},
							{0xc7, "BoutenDialogPrefix"},
							{0xc8, "TatechuyokoDialogPrefix"},
							{0xc9, "CompositeFontDialogPrefix"},

							{0xca, "2nd TextPrefix"}, // 2nd block of Text prefixes

							{0xcb, "CompositeFontMgrPrefix"},

							{0xcc, "ScriptPanelPrefix"},
							{0xcd, "CJKGridPrefix"},
							{0xce, "NamedGridsPanel"},
							{0xcf, "ShataiDlgPrefix"},

							{0xd0, "CJKGridPrefsPrefix"},
							{0xd1, "AlternateGlyph2Prefix"},
							{0xd2, "ActionsPrefix1"},	// need lots of ids because test menus come out of this id space
							{0xd3, "ActionsPrefix#2"},
							{0xd4, "ActionsPrefix#3"},
							{0xd5, "ActionsPrefix#4"},
							{0xd6, "ActionsPrefix#5"},
							{0xd7, "ActionsPrefix#6"},
							{0xd8, "ActionsPrefix#7"},
							{0xd9, "TestPrefix1"},	// need lots of ids because most of the qa menu comes out of this id space
							{0xda, "TestPrefix2"},
							{0xdb, "TestPrefix3"},
							{0xdc, "TestPrefix4"},
							{0xdd, "TestPrefix5"},
							{0xde, "TestPrefix6"},

							{0xe1, "TextPanelPrefix1"},	// why are there so many text panel prefixes?
							{0xe2, "TextPanelPrefix2"}, // because the font menu comes from this plugin.
							{0xe3, "TextPanelPrefix3"}, // it has to have room for action ids for lots of fonts.
							{0xe4, "TextPanelPrefix4"},
							{0xe5, "TextPanelPrefix5"},
							{0xe6, "TextPanelPrefix6"},
							{0xe7, "TextPanelPrefix7"},
							{0xe8, "TextPanelPrefix8"},
							{0xe9, "TextPanelPrefix9"},
							{0xea, "TextPanelPrefix10"},
							{0xeb, "TextPanelPrefix11"},
							{0xec, "TextPanelPrefix12"},
							{0xed, "TextPanelPrefix13"},
							{0xee, "TextPanelPrefix14"},
							{0xef, "TextPanelPrefix15"},

							//Keystone
							{0xf0, "CommandBarPrefix"},
							{0xf1, "ClipArtCatalogPrefix"},
							{0xf2, "CropTool"},
							{0xf3, "ClipArtBrowser"},
							{0xf4, "GalleyPrefs"},
							{0xf5, "IManPrefix"},			// The InfoManager (Word Count)
							{0xf6, "KeystonePrefix7"},
							{0xf7, "KeystonePrefix8"},
							{0xf8, "KeystonePrefix9"},
							{0xf9, "GalleyInfoPrefix"},
							{0xfa, "BulletsAndNumbering"},
							{0xfb, "KeystonePrefix12"},
							{0xfc, "DockBar"},
							{0xfd, "GalleyInfo"},
							{0xfe, "EditorHelper"},
							{0xff, "PathTools"},			// Keystone Path Tools

							{0x100, "Book"},
							{0x101, "BookPanel"},
							{0x102, "IMEPrefsDlgPrefix"},
							{0x103, "MSPublisher Converter"},
							{0x104, "TableModelPrefix2"},
							{0x105, "TablesUIPrefix"},
							{0x106, "2ndTablesUIPrefix"},
							{0x107, "ShuksanID2Prefix"},
							{0x108, "TransparencyPrefix"},
							{0x109, "TransparencyUIPrefix"},
							{0x10A, "OutputMiscUI"},
							{0x10B, "Mojikumi2ndPrefix"},
							{0x10C, "KBSCEditorPrefix"},
							{0x10D, "LibraryConversionPrefix"},
							{0x10E, "MetaDataDB"},
							{0x10F, "XMLParser2"},

							// More CJK stuff
							{0x110, "InDesignConversionPrefix"},
							{0x111, "CJKWariChuPrefix"},
							{0x112, "CJKWariChuDialogPrefix"},
							{0x113, "OnHostTrappingPrefix"},
							{0x114, "MacSimpleTextImportPrefix"},

							{0x115, "ControlStripPrefix"},
							{0x116, "TOC"},
							{0x117, "TOCUI"},
							{0x118, "MeasureTool"},
							{0x119, "OutputPreview"},
							{0x11A, "Package4GL"},
							{0x11B, "Package4GLUI"},
							{0x11C, "2ndPDFPrefix"},
							{0x11D, "Notes"},
							{0x11E, "NotesUI"},

							// More Keystone stuff
							{0x120, "TemplateMgrPrefix"},

							// More Anna stuff
							{0x121, "InDesignExportPrefix"},
							{0x122, "SangamServicerPrefix"},
							{0x123, "SangamUIPreferencesPrefix"},
							{0x124, "RTFExportservicer"},
							{0x125, "XMLPubFormat"},
							{0x126, "MetaData"},
							{0x127, "SVGExport"},
							{0x128, "SVGExportUI"},
							{0x129, "NewLibraryPalette"},
							{0x130, "Indexing"},
							{0x131, "IndexingUI"},
							{0x132, "PerformanceUI"},
							{0x133, "XMediaUI"},
							{0x134, "ScriptTagPanel"},
							{0x135, "HyperLink"},
							{0x136, "HyperLinkUI"},
							{0x137, "MetaDataUIObsolete"},		// no longer in use. Last used for 2.0.
							{0x138, "OpticalKerning"},
							{0x139, "HTML Export"},
							{0x13A, "S4SP-Package&Preflight"},
							{0x13B, "CreateOutline"},
							{0x13C, "PNGImport"},
							{0x13D, "GenericSettingsPrefix"},
							{0x13E, "HTML ExportUI"},
							{0x13F, "Run-in Styles"},

							// BlackDuck plug-ins
							{0x140, "Media"},
							{0x141, "FCHLDialog"},
							{0x142, "HyperlinksReport"},
							{0x143, "PDFPreview"},
							{0x144, "XMLFormExt"},
							{0x145, "FormField"},
							{0x146, "FormFieldUI"},
							{0x147, "OeBExport"},
							{0x148, "Movie"},
							{0x149, "MovieUI"},
							{0x14A, "QTFilter"},
							{0x14B, "AVIFilter"},		// Not used anymore
							{0x14C, "MPEGFilter"},		// Not used anymore
							{0x14D, "SWFFilter"},		// Not used anymore
							{0x14E, "DVFilter"},		// Not used anymore
							{0x14F, "Sound"},			// Not used anymore
							{0x150, "SoundUI"},			// Not used anymore
							{0x151, "AIFFilter"},		// Not used anymore
							{0x152, "WAVFilter"},		// Not used anymore
							{0x153, "AUFilter"},		// Not used anymore
							{0x154, "Mac7SoundFilter"},	// Not used anymore
							{0x155, "InteractivePDF"},
							{0x156, "Behavior"},
							{0x157, "Behaviors2"},
							{0x158, "OEBExportUI"},
							{0x159, "BehaviorUI"},

							{0x15A, "Workgroup"},
							{0x15B, "WorkgroupUI"},
							{0x15C, "InfoPanel"},
							{0x15D, "SaveBack"},
							{0x15e, "ARM"},
							{0x15F, "JavaScript"},

							// Framework Prefixes
							{0x160, "ObjectModel"},
							{0x161, "AppFramework"},
							{0x162, "Utilities"},
							{0x163, "DocFramework"},
							{0x164, "AppUI"},
							{0x165, "TextFrame"},
							{0x166, "TextUI"},
							{0x167, "Framework7"},
							{0x168, "Framework8"},
							{0x169, "Framework9"},
							{0x16A, "Framework10"},
							{0x16B, "Framework11"},
							{0x16C, "Framework12"},
							{0x16D, "Framework13"},
							{0x16E, "Framework14"},
							{0x16F, "ObjectModelPanelObsolete"},	// No longer in use, deleted in Cobalt.

							{0x170, "InCopyExportFilter"},
							{0x171, "InCopyImportFilter"},
							{0x172, "InCopyFileActions"},
							{0x173, "InCopyExportUIFilter"},
							{0x174, "InCopyWorkflow"},
							{0x175, "BookmarkPanel"},
							{0x176, "MediaFilter"},
							{0x177, "RealMediaFilter"},
							{0x178, "WinMediaFilter"},
							{0x179, "MP3Filter"},
							{0x17A, "EBookUnused1"},
							{0x17B, "EBookUnused2"},
							{0x17C, "XMLParser"},
							{0x17D, "InfoPanel2"},
							{0x17E, "DialogLayout"},
							{0x17F, "PrintPrefix2"},

							{0x180, "InCopyNotePref"},
							{0x181, "InCopyTrackChangesPref"},
							{0x182, "InCopyDocumentSetup"},
							{0x183, "InCopyUsernameUI"},
							{0x184, "SING"},
							{0x185, "SplineUI"},
							{0x186, "HighLevelAPI"},
							{0x187, "DocumentActions"},
							{0x188, "DocumentUI"},
							{0x189, "InCopyPrintUI"},
							{0x18A, "AnnaXMLReader"},
							{0x18B, "WorkGroupClient"},
							{0x18C, "ServerErrorMgmt"},
							{0x18D, "ServerErrMgmtUI"},
							{0x18E, "InCopy Bridge"},
							{0x18F, "InCopy Bridge UI"},

							{0x190, "JPEGExport"},
							{0x191, "JPEGExportUI"},
							{0x192, "UpdateManager"},
							{0x193, "XMLParser3"},
							{0x194, "XMLParser4"},
							{0x195, "Snippet"},
							{0x196, "ActionPrefix8"},
							{0x197, "SnippetUI"},
							{0x198, "AppleScript"},
							{0x199, "VisualBasic"},
							{0x19A, "StoryListPanel"},

							// Babushka Prefixes
							{0x19b, "PMCropTool"},
							{0x19c, "PMToolBarObsolete"},			// Obsolete, deleted in Basil
							{0x19d, "PMConverter"},
							{0x19e, "PMTemplatePalette"},
							{0x19f, "PMPublisher2002"},
							{0x1a0, "PMKBSC"},
							{0x1a1, "PMFontPreview"},
							{0x1a2, "PMDataMerge"},
							{0x1a3, "PMHeaders&Footers"},
							{0x1a4, "PMBullets&Numbering"},
							{0x1a5, "PMStartupWizard"},
							{0x1a6, "PMBuffer1"},
							{0x1a7, "PMBuffer2"},

							// Misc
							{0x1a8, "PDFT_PT"},
							{0x1a9, "ScriptProcessor"},
							{0x1aa, "DataServices"},
							{0x1ab, "PreviewPanel"},
							{0x1ac, "TC Dialog"},
							{0x1ad, "TC Cmd"},
							{0x1ae, "TC FGC"},
							{0x1af, "TC FGD"},
							{0x1b0, "VDM"},

							{0x1b1, "HLATestProvider"},
							{0x1b2, "Spy"},
							{0x1b3, "aps_pt"}, // added for Lindbergh (see KittyHawk) no persistent data
							{0x1b4, "INXCore"},
							{0x1b5, "SmarterTags"}, //added for Kitty Hawk
							{0x1b6, "SmarterServer"}, //added for Kitty Hawk
							{0x1b7, "PSImportUI"}, 
							{0x1b8, "LayoutUI2"},
							{0x1b9, "ObjectStyle"},
							{0x1ba, "ObjectStyleUI"},
							{0x1bb, "ImportExportUI"},
							{0x1bc, "XML2"},
							{0x1bd, "ActionsPanel"},
							{0x1be, "Assignments"},
							{0x1bf, "SmarterTagsUI"},
	
							{0x1c0, "ATGReserved"},
							{0x1c1, "ATGReserved"},
							{0x1c2, "ATGReserved"},
							{0x1c3, "ATGReserved"},
							{0x1c4, "ATGReserved"},
							{0x1c5, "ATGReserved"},
							{0x1c6, "ATGReserved"},
							{0x1c7, "ATGReserved"},
							{0x1c8, "ATGReserved"},
							{0x1c9, "ATGReserved"},
							{0x1cA, "Bumpers"},
							{0x1cB, "BumpersUI"},
							{0x1cC, "ATGReserved"},
							{0x1cD, "ATGReserved"},
							{0x1cE, "ATGReserved"},
							{0x1cF, "ATGReserved"},

							{0x1d0, "LayoutUI"},
							{0x1d1, "PathTypeUI"},
							{0x1d2, "PrintUI"},
							{0x1d3, "TextEditor"},
							{0x1d4, "PrintUI2"},
							{0x1d5, "MetaDataUI"},
							{0x1d6, "CoAuthorImport"},
							{0x1d7, "InCopySharedUI"},
							{0x1d8, "InCopyWorkflowUI"},
							{0x1d9, "PNGFilterUI"},
							{0x1dA, "SpellingServices"},
							{0x1dB, "SOAPServer"},
							{0x1dc, "SampleCodeObsolete"},		// No longer in use, deleted in Cobalt.
							{0x1dd, "RestrictedUITool"},
							{0x1de, "WatchFolder"},
							{0x1df, "TextAttr2"},	//2nd Text Attributes prefix

							{0x1e0, "CSAService"},	
							{0x1e1, "SmarterUpdate"}, // KittyHawk
							{0x1e2, "GenericPageItem2"},	// 2nd prefix for Generic
							{0x1e4, "ServerStatistics"}, 
							{0x1e5, "DiagnosticLog"},	// part of ITK
							{0x1e6, "LILO"},
							{0x1e7, "ChangeBar"},
							{0x1e8, "ChangeBarUI"},
							{0x1e9, "SmarterDemo"},	// KittyHawk
							{0x1ea, "LinkHelper"}, // KittyHawk
							{0x1eb, "Transparency2"}, // second prefix for Transparency plug-in
							{0x1ec, "JobBag"},
							{0x1ed, "JobBagUI"},
							{0x1ef, "XMediaUI2"},	// second prefix for XMedia UI plug-in
							{0x1f0, "CorbaGenerator"},
							{0x1f1, "CorbaSupport"},
							{0x1f2, "CorbaUtils"},
							{0x1f3, "FindChangePrefix2"},	// second prefix for FindChange
							{0x1f4, "TransparencyUI2"}, // second prefix for Transparency UI
							{0x1f5, "SDKAATActions"},
							{0x1f6, "JobExecutor"},
							{0x1f7, "GraphicsServer"},
							{0x1f8, "ObjectStylesUI2"},  // second prefix for Object Styles UI
							{0x1f9, "PDFReview"},
							{0x1fA, "PDFReviewUI"},
							{0x1fb, "AWSUI"},
							{0x1fc, "WorkgroupClientUI"},
							{0x1fd, "CameraRaw"},
							{0x1fe, "TablesUIPrefix3"},
							{0x1ff, "TablesStyleUIPrefix2"},
							{0x200, "TextEditorPrefix3"},
							{0x201, "OutputPreviewUI"},
							{0x202, "CellStyles"},
							{0x203, "TableStyles"},
							{0x204, "TableStylesUI"},
							{0x205, "DynamicDocuments"},
							{0x206, "LinksUI"},
							{0x207, "ConditionalText"},
							{0x208, "ConditionalTextUI"},
							{0x209, "CrossingGuard"},
							{0x20A, "CrossingGuardUI"},
							{0x20B, "PackageAndPreflightUI2"},
							{0x20C, "DynamicDocumentsUI"},
							{0x20D, "CSXS"},
							{0x20E, "3rd WidgetPrefix"},
							{0x20F, "GapTool"},
							{0x210, "DynamicDocumentsUI2"},
							{0x211, "EditorHelperUI"},
							{0x212, "InCopyCoreUI"},
							{0x213, "InCopyFileActionsUI"},
							{0x214,	"SpanColumnsPanelPrefix"},
							{0x215,	"BuzzwordBrowserPrefixObsolete"},		// No longer in use, deleted in Athos (CS6)
							{0x216,	"SwitchbackHelperPrefix"},
							{0x217,	"GalleyUI"},
							{0x218, "AppUI 2nd prefix"},
							{0x219, "DigitalPublishing"},
							{0x21A, "EBookExport"},
							{0x21B, "Article"},
							{0x21C, "ArticlePanel"},
							{0x21D, "SharedContent"},
							{0x21E, "GraphicPanelsPrefix2"},
							{0x21F, "SharedContentUI"},
							{0x220, "Scene7FXG"},
							{0x221, "HTMLPGTPrefix"},
							{0x222, "SpreadPrefix2"},
							{0x223, "ContentDropper"},
							{0x224, "ContentDropperTool"},
							{0x225, "DigitalPublishing2"},
							{0x226, "TextPrefix4"},
							{0x227, "kSettingsInCloudPrefix"},
							{0x228, "kCharPanelPrefix1"},
							// For FolioBuilder & Overlay Creator
							{0x229, "kFolioBuilderModel"},
							{0x22A, "kFolioBuilderUI"},
							{0x22B, "kDigitalPublishingUI"},
							//
							{0x22C, "kSavebackService"},
							{0x22D, "kTaggedTextImportExportAttrPrefix3"},
							{0x22E, "TableModelPrefix3"},
							//
							{0x22F, "ImportExportUIPrefix2"},
							{0x230, "OnBoarding"}, // for OnBoarding
							{0x231, "kLinksPrefix2"}, // for Links (prefix2)

							// AEM conn model/ui
							{0x232, "AEMModelPrefix"}, 
							// {0x233, "ContribPanel?"}, //Possibly unused but a header file references it
							{0x234, "AEMUIPrefix"},
							{0x235, "ImportArticle"}, //Not yet used in mainline
							{0x236, "TextOptionsPanelPrefix2"}, //second prefix for text options panel
							{0x237, "kEyeDropperToolPrefix2"}, //second prefix for eye dropper tool
							{0x238, "ParaPanelPrefix2"}, // second prefix for Paragraph Panel
							{0x239, "kSangamPreferencesUIPrefix2"}, // second prefix for Sangam preferences

							//QA Prefixes (we're counting down for QA prefixes now.)
							{0x3cc, "QAINXErrorLogger"},
							{0x3cd, "TestThreading"},
							{0x3ce, "INXSchemaValidator"},
							{0x3cf, "XSnapshot"},
							{0x3d0, "XSnapshotUI"},
							{0x3d1, "EngTestProviderUI"},
							{0x3d2, "CertTestProviderUI"},
							{0x3d3, "AATUI"},
							{0x3d4, "PumpkinAttributes"},
							{0x3d5, "QAInDSProvider"},
							{0x3d6, "PumpkinUI"},
							{0x3d7, "QAThirdPartyTestProviderObsolete"},		// No longer in use, deleted in Cobalt.
							{0x3d8, "QATestProviderUI"},
							{0x3d9, "QAPrivateDataUIObsolete"},		// No longer in use, deleted in Cobalt.
							{0x3da, "QAPreview"},
							{0x3db, "AATArchUI"},
							{0x3dc, "AATArch"},
							{0x3dd, "PrintPDFQETestProvider"},
							{0x3de, "QAPrivateData"},
							{0x3df, "SnapshottingUI"},
							{0x3e0, "QAScriptPrefix"},
							{0x3e1, "QAScriptTestPrefix"},
							{0x3e2, "XMLTestServer"},
							{0x3e3, "QATransparencyObsolete"},		// No longer in use, deleted in Cobalt.
							{0x3e4, "QAPrefab"},
							{0x3e5, "QAComponentInfo"},			// No longer in use, deleted in Cobalt.
							{0x3e6, "Informant"},
							{0x3e7, "Snapshotting"},
							{0x3e8, "CertTestProvider"},
							{0x3e9, "EngTestProvider"},
							{0x3ea, "MakeATestBook"},
							{0x3eb, "QAXMLParser"},
							{0x3ec, "RunTest"},
							{0x3ed, "IndiaTestSuite"},
							{0x3ef, "ScriptGenerator"},
							{0x3f0, "QAFontTestPrefix"},	
							{0x3f1, "QACJKGridPrefix"},
							{0x3f2, "QACJKPrefix"},
							{0x3f3, "QAInCopyPrefix"},
							{0x3f4, "TestImportPanel"},
							{0x3f5,"ImageExporter"},
							{0x3f6,"PrintCodex"},
							{0x3f7,"PrintTestPanel"},
							{0x3f8,"Pumpkin"},
							{0x3f9,"TestPanel"},
							{0x3fa,"PluginPanelPrefixObsolete"},	// No longer in use, deleted in Cobalt.
							{0x3fb,"TestProvider"},
							{0x3fc,"RoboDrePanelObsolete"},	// No longer in use, deleted in Cobalt.
							{0x3fd,"XVBPrefix"},
							{0x3fe,"XScriptPrefix"},
							{0x3ff,"AutoUIPrefix"},
							{kLastAdobePrefix,"Unknown Adobe Prefix"} // last prefix reserved for adobe
							
							// 	{0x50F, "WinSoft"},				// Bertrand Lechevalier - blecheva@adobe.com(8-Mar-00) builds the WorldReady plugin introduced in CS4

}; // gPrefixList



#endif // DEBUG
#endif // __AdobePrefix__
