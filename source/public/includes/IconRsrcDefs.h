//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IconRsrcDefs.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//  Constant definitions for icons in .fr files
//  
//========================================================================================

#ifndef __ICONRSRCDEFS__
#define __ICONRSRCDEFS__

#define kNoIcon							0

// Here are the application icons. The numbers are fixed by the OS.
#define kPCApplicationIcon				1
#define kMacApplicationIcon				128
#ifdef INDESIGNPACKAGE
	#ifdef BUILDING_SERVER
		#define kMacApplicationIconStr			"id_s_appicon_rev.icns"
	#else
		#define kMacApplicationIconStr			"ID_App_Icon.icns"
	#endif
#endif
#ifdef INCOPYPACKAGE
	#define kMacApplicationIconStr			"IC_App_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kMacApplicationIconStr			"128"
#endif

//  ****   ***  *   *    ***  ***** ***** ***** *   * ***** *  ***  *   *   *
//  *   * *   *  * *    *   *   *     *   *     **  *   *   * *   * **  *   *
//  ****  *****   *     *****   *     *   ***   * * *   *   * *   * * * *   *
//  *     *   *   *     *   *   *     *   *     *  **   *   * *   * *  **
//  *     *   *   *     *   *   *     *   ***** *   *   *   *  ***  *   *   *
//
// If you renumber these icons, you need get the install people to change the
// indexes that get written into the registry for the windows icon handler so
// that the registry entries point to the new icon indicies in the .exe file


// Range: 2 - 127
// These should only be used for PC icons that have no
// equivalent on the Mac. This is because this range is
// reserved for the Mac OS.

// <none at this time>


// Range 129 - 255
// This group is for file icons.

#define kMacApplicationFolderIcon		129

#define kPluginFolderIcon				130


#define kTypeRoleViewer	"Viewer"
#define kTypeRoleEditor	"Editor"
#define kTypeRoleNone	"None"

#define kHandlerRankOwner		"Owner"		// app is the creator of files of this type
#define kHandlerRankAlternate	"Alternate"	// app is a secondary viewer of files of this type
#define kHandlerRankNone		"None"		// app must never be used to open files of this type, but it accepts drops of files of this type
#define kHandlerRankDefault		"Default"	// app doesn’t accept drops of files of this type

// Document

#define kAnnaDocumentIcon					131
#ifdef INDESIGNPACKAGE
	#define kAnnaDocumentDescription		"InDesign\U00AE Document"
	#define kAnnaDocumentIconStr			"ID_DocumentGeneric_icon.icns"
	#define kAnnaDocumentMacOSType			"InDd"
#endif
#ifdef NOPACKAGE
	#define kAnnaDocumentIconStr			"131"
#endif


#define kDtailDocumentIcon					132
#ifdef INDESIGNPACKAGE
	#define kDtailDocumentDescription		"InDesign\U00AE CS Document"
	#define kDtailDocumentIconStr			"ID30_Document_Icon.icns"
	#define kDtailDocumentMacOSType			"IDd3"
#endif
#ifdef NOPACKAGE
	#define kDtailDocumentIconStr			"132"
#endif


#define kFireDrakeDocumentIcon				139
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kFireDrakeDocumentDescription	"InDesign\U00AE CS2 Document"
	#define kFireDrakeDocumentIconStr		"ID40_Document_Icon.icns"
	#define kFireDrakeDocumentExtension		"INDD"
	#define kFireDrakeDocumentMacOSType		"IDd4"
#endif
#ifdef NOPACKAGE
	#define kFireDrakeDocumentIconStr		"139"
#endif

#define kCobaltDocumentIcon				140
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kCobaltDocumentDescription	"InDesign\U00AE CS3 Document"
	#define kCobaltDocumentIconStr		"ID50_Document_Icon.icns"
	#define kCobaltDocumentExtension		"INDD"
	#define kCobaltDocumentMacOSType		"IDd5"
#endif
#ifdef NOPACKAGE
	#define kCobaltDocumentIconStr		"140"
#endif

#define kBasilDocumentIcon				141
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kBasilDocumentDescription	"InDesign\U00AE CS4 Document"
	#define kBasilDocumentIconStr		"ID60_Document_Icon.icns"
	#define kBasilDocumentExtension		"INDD"
	#define kBasilDocumentMacOSType		"IDd6"
#endif
#ifdef NOPACKAGE
	#define kBasilDocumentIconStr		"141"
#endif

#define kRocketDocumentIcon				142
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kRocketDocumentDescription	"InDesign\U00AE CS5 Document"
	#define kRocketDocumentIconStr		"ID70_Document_Icon.icns"
	#define kRocketDocumentExtension		"INDD"
	#define kRocketDocumentMacOSType		"IDd7"
#endif
#ifdef NOPACKAGE
	#define kRocketDocumentIconStr		"142"
#endif

#define kOdinDocumentIcon				143
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kOdinDocumentDescription	"InDesign\U00AE CS5.5 Document"
	#define kOdinDocumentIconStr		"ID75_Document_Icon.icns"
	#define kOdinDocumentExtension		"INDD"
	#define kOdinDocumentMacOSType		"IDd2"	// Ideally we could use something like IDd75 here, but we only get four chars, use 2 instead so Athos can use 8
#endif
#ifdef NOPACKAGE
	#define kOdinDocumentIconStr		"143"
#endif

#define kAthosDocumentIcon				205
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAthosDocumentDescription	"InDesign\U00AE CS6.0 Document"
	#define kAthosDocumentIconStr		"ID_Document_Icon.icns"
	#define kAthosDocumentExtension		"INDD"
	#define kAthosDocumentMacOSType		"IDd8"
#endif
#ifdef NOPACKAGE
	#define kAthosDocumentIconStr		"205"
#endif

#define kCitiusDocumentIcon				206
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kCitiusDocumentDescription	"InDesign\U00AE CC.0 Document"
	#define kCitiusDocumentIconStr		"ID_Document_Icon.icns"
	#define kCitiusDocumentExtension	"INDD"
	#define kCitiusDocumentMacOSType	"IDd9"
#endif
#ifdef NOPACKAGE
	#define kCitiusDocumentIconStr		"206"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kSiriusDocumentDescription	"InDesign\U00AE CC 2014.0 Document"
#define kSiriusDocumentIconStr		kCitiusDocumentIconStr
#define kSiriusDocumentExtension	"INDD"
#define kSiriusDocumentMacOSType	"IDdX"
#endif

#ifdef NOPACKAGE
#define kSiriusDocumentIconStr		"206"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR5DocumentDescription	"InDesign\U00AE CC 2015.0 Document"
#define kR5DocumentIconStr		kCitiusDocumentIconStr
#define kR5DocumentExtension	"INDD"
#define kR5DocumentMacOSType	"IDdB"
#endif

#ifdef NOPACKAGE
#define kR5DocumentIconStr		"206"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR10DocumentDescription	"InDesign\U00AE CC 2017.0 Document"
#define kR10DocumentIconStr		kCitiusDocumentIconStr
#define kR10DocumentExtension	"INDD"
#define kR10DocumentMacOSType	"IDdC"
#endif

#ifdef NOPACKAGE
#define kR10DocumentIconStr		"206"
#endif

#define kR12DocumentIcon				207
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR12DocumentDescription	"InDesign\U00AE 2021.0 Document"
#define kR12DocumentIconStr		"ID_Document_Icon.icns"
#define kR12DocumentExtension	"INDD"
#define kR12DocumentMacOSType	"IDdD"
#endif

#ifdef NOPACKAGE
#define kR12DocumentIconStr		"207"
#endif

#define kGenericFileIcon				133
#ifdef INDESIGNPACKAGE
	#define kGenericFileIconStr				"ID_DocumentGeneric_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kGenericFileIconStr				"IC_DocumentGeneric_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kGenericFileIconStr				"133"
#endif


#define kDtailXMLInterchangeIcon			134
#ifdef INDESIGNPACKAGE
	#define kDtailXMLInterchangeDescription		"InDesign\U00AE XML Interchange"
	#define kDtailXMLInterchangeIconStr			"ID_SaveBackwardsInt_Icon.icns"
	#define kDtailXMLInterchangeExtension		"INX"
	#define kDtailXMLInterchangeMacOSType		"IDx3"
#endif
#ifdef NOPACKAGE
	#define kDtailXMLInterchangeIconStr		"134"
#endif

#define kDefaultDocumentIcon			135
#define kK2DocumentIcon					136
#define kSherpaDocumentIcon				137
#define kHotakaDocumentIcon				138

#define kFiredrakeSnippetIcon		144
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kFiredrakeSnippetDescription	"InDesign\U00AE Snippet"
	#define kFiredrakeSnippetIconStr		"ID40_Snippet_Icon.icns"
	#define kFiredrakeSnippetExtension		"INDS"
	#define kFiredrakeSnippetMacOSType		"InDs"
#endif
#ifdef NOPACKAGE
	#define kFiredrakeSnippetIconStr		"144"
#endif

#define kCobaltSnippetIcon		153
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kCobaltSnippetDescription	"InDesign\U00AE Snippet"
	#define kCobaltSnippetIconStr		"ID50_Snippet_Icon.icns"
	#define kCobaltSnippetExtension		"INDS"
	#define kCobaltSnippetMacOSType		"InDs"
#endif
#ifdef NOPACKAGE
	#define kCobaltSnippetIconStr		"153"
#endif

#define kBasilSnippetIcon		155
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kBasilSnippetDescription	"InDesign\U00AE Snippet"
	#define kBasilSnippetIconStr		"ID60_IDMSSecondary_Icon.icns"
	#define kBasilSnippetExtension		"IDMS"
	#define kBasilSnippetMacOSType		"IdMs"
#endif
#ifdef NOPACKAGE
	#define kBasilSnippetIconStr		"155"
#endif

#define kRocketSnippetIcon		156
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kRocketSnippetDescription	"InDesign\U00AE Snippet"
	#define kRocketSnippetIconStr		"ID70_IDMSSecondary_Icon.icns"
	#define kRocketSnippetExtension		"IDMS"
	#define kRocketSnippetMacOSType		"IdMs"
#endif
#ifdef NOPACKAGE
	#define kRocketSnippetIconStr		"156"
#endif

#define kAthosSnippetIcon		157
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAthosSnippetDescription	"InDesign\U00AE Snippet"
	#define kAthosSnippetIconStr		"ID70_IDMSSecondary_Icon.icns"
	#define kAthosSnippetExtension		"IDMS"
	#define kAthosSnippetMacOSType		"IdMs"
#endif
#ifdef NOPACKAGE
	#define kAthosSnippetIconStr		"157"
#endif


// Import types

// PageMaker
#ifdef INDESIGNPACKAGE
	#define kPageMakerDocumentDescription		"PageMaker\U00AE Document"
	#define kPageMakerExtension1				"P65"
	#define kPageMakerExtension2				"T65"
	#define kPageMakerExtension3				"PMD"
	#define kPageMakerExtension4				"PMT"
	#define kPageMakerMacOSType1				"PMD "
	#define kPageMakerMacOSType2				"PMT "
	#define kPageMakerMacOSType3				"AB65"
	#define kPageMakerMacOSType4				"AT65"
#endif

// QuarkXPress
#ifdef INDESIGNPACKAGE
	#define kQuarkXPressDocumentDescription		"QuarkXPress\U00AE Document"
	#define kQuarkXPressExtension1				"QXD"
	#define kQuarkXPressExtension2				"QXT"
	#define kQuarkXPressMacOSType1				"XDOC"
	#define kQuarkXPressMacOSType2				"XTMP"
#endif

// Template

#define kAnnaTemplateIcon					145
#ifdef INDESIGNPACKAGE
	#define kAnnaTemplateDescription		"InDesign\U00AE Template"
	#define kAnnaTemplateIconStr			"ID_StationaryGeneric_icon.icns"
	#define kAnnaTemplateMacOSType			"snDd"
#endif
#ifdef NOPACKAGE
	#define kAnnaTemplateIconStr			"145"
#endif


#define kDtailTemplateIcon				146
#ifdef INDESIGNPACKAGE
	#define kDtailTemplateDescription		"InDesign\U00AE CS Template"
	#define kDtailTemplateIconStr			"ID30_Stationery_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kDtailTemplateIconStr			"146"
#endif


#define kFireDrakeTemplateIcon				151
#ifdef INDESIGNPACKAGE
	#define kFireDrakeTemplateDescription	"InDesign\U00AE CS2 Template"
	#define kFireDrakeTemplateIconStr		"ID40_Stationery_Icon.icns"
	#define kFireDrakeTemplateExtension		"INDT"
#endif
#ifdef NOPACKAGE
	#define kFireDrakeTemplateIconStr		"151"
#endif

#define kCobaltTemplateIcon				152
#ifdef INDESIGNPACKAGE
	#define kCobaltTemplateDescription	"InDesign\U00AE CS3 Template"
	#define kCobaltTemplateIconStr		"ID50_Stationary_Icon.icns"
	#define kCobaltTemplateExtension	"INDT"
	#define kCobaltTemplateMacOSType	"ID5t"
#endif
#ifdef NOPACKAGE
	#define kCobaltTemplateIconStr		"152"
#endif

#define kBasilTemplateIcon				154
#ifdef INDESIGNPACKAGE
	#define kBasilTemplateDescription	"InDesign\U00AE CS4 Template"
	#define kBasilTemplateIconStr		"ID60_Stationary_Icon.icns"
	#define kBasilTemplateExtension		"INDT"
	#define kBasilTemplateMacOSType		"ID6t"
#endif
#ifdef NOPACKAGE
	#define kBasilTemplateIconStr		"154"
#endif

#define kRocketTemplateIcon				157
#ifdef INDESIGNPACKAGE
	#define kRocketTemplateDescription	"InDesign\U00AE CS5 Template"
	#define kRocketTemplateIconStr		"ID70_Stationary_Icon.icns"
	#define kRocketTemplateExtension		"INDT"
	#define kRocketTemplateMacOSType		"ID7t"
#endif
#ifdef NOPACKAGE
	#define kRocketTemplateIconStr		"157"
#endif

#define kOdinTemplateIcon				158
#ifdef INDESIGNPACKAGE
	#define kOdinTemplateDescription	"InDesign\U00AE CS5.5 Template"
	#define kOdinTemplateIconStr		"ID75_Stationary_Icon.icns"
	#define kOdinTemplateExtension		"INDT"
	#define kOdinTemplateMacOSType		"ID2t"	// Ideally we could use something like ID75t here, but we only get four chars, use 2 instead so Athos can use 8
#endif
#ifdef NOPACKAGE
	#define kOdinTemplateIconStr		"158"
#endif

#define kAthosTemplateIcon				159
#ifdef INDESIGNPACKAGE
	#define kAthosTemplateDescription	"InDesign\U00AE CS6.0 Template"
	#define kAthosTemplateIconStr		"ID80_Stationary_Icon.icns"
	#define kAthosTemplateExtension		"INDT"
	#define kAthosTemplateMacOSType		"ID8t"
#endif
#ifdef NOPACKAGE
	#define kAthosTemplateIconStr		"159"
#endif

// kCitiusTemplateIcon (247)  moved to end of list to keep numbers in sequence

#define kDefaultTemplateIcon			147
#define kK2TemplateIcon					148
#define kSherpaTemplateIcon				149
#define kHotakaTemplateIcon				150


// Book

#define kAnnaBookIcon					160
#ifdef INDESIGNPACKAGE
	#define kAnnaBookDescription		"InDesign\U00AE Book"
	#define kAnnaBookIconStr			"ID_BookGeneric_Icon.icns"
	#define kAnnaBookMacOSType			"InDb"
#endif
#ifdef NOPACKAGE
	#define kAnnaBookIconStr				"160"
#endif


#define kDtailBookIcon					161
#ifdef INDESIGNPACKAGE
	#define kDtailBookDescription		"InDesign\U00AE CS Book"
	#define kDtailBookIconStr			"ID30_Book_Icon.icns"
	#define kDtailBookMacOSType			"IDb3"
#endif
#ifdef NOPACKAGE
	#define kDtailBookIconStr				"161"
#endif


#define kFireDrakeBookIcon				163
#ifdef INDESIGNPACKAGE
	#define kFireDrakeBookDescription		"InDesign\U00AE CS2 Book"
	#define kFireDrakeBookIconStr			"ID40_Book_Icon.icns"
	#define kFireDrakeBookExtension			"INDB"
	#define kFireDrakeBookMacOSType			"IDb4"
#endif
#ifdef NOPACKAGE
	#define kFireDrakeBookIconStr			"163"
#endif

#define kCobaltBookIcon				164
#ifdef INDESIGNPACKAGE
	#define kCobaltBookDescription		"InDesign\U00AE CS3 Book"
	#define kCobaltBookIconStr			"ID50_Book_Icon.icns"
	#define kCobaltBookExtension			"INDB"
	#define kCobaltBookMacOSType			"IDb5"
#endif
#ifdef NOPACKAGE
	#define kCobaltBookIconStr			"164"
#endif

#define kBasilBookIcon				165
#ifdef INDESIGNPACKAGE
	#define kBasilBookDescription		"InDesign\U00AE CS4 Book"
	#define kBasilBookIconStr			"ID60_Book_Icon.icns"
	#define kBasilBookExtension			"INDB"
	#define kBasilBookMacOSType			"IDb6"
#endif
#ifdef NOPACKAGE
	#define kBasilBookIconStr			"165"
#endif

#define kRocketBookIcon				166
#ifdef INDESIGNPACKAGE
	#define kRocketBookDescription		"InDesign\U00AE CS5 Book"
	#define kRocketBookIconStr			"ID70_Book_Icon.icns"
	#define kRocketBookExtension			"INDB"
	#define kRocketBookMacOSType			"IDb7"
#endif
#ifdef NOPACKAGE
	#define kRocketBookIconStr			"166"
#endif

#define kOdinBookIcon				167
#ifdef INDESIGNPACKAGE
	#define kOdinBookDescription		"InDesign\U00AE CS5.5 Book"
	#define kOdinBookIconStr			"ID75_Book_Icon.icns"
	#define kOdinBookExtension			"INDB"
	#define kOdinBookMacOSType			"IDb2"	// Ideally we could use something like IDb75 here, but we only get four chars, use 2 instead so Athos can use 8
#endif
#ifdef NOPACKAGE
	#define kOdinBookIconStr			"167"
#endif

#define kAthosBookIcon				168
#ifdef INDESIGNPACKAGE
	#define kAthosBookDescription		"InDesign\U00AE CS6.0 Book"
	#define kAthosBookIconStr			"ID80_Book_Icon.icns"
	#define kAthosBookExtension			"INDB"
	#define kAthosBookMacOSType			"IDb8"
#endif
#ifdef NOPACKAGE
	#define kAthosBookIconStr			"168"
#endif

#define kCitiusBookIcon					169
#ifdef INDESIGNPACKAGE
	#define kCitiusBookDescription		"InDesign\U00AE CC.0 Book"
	#define kCitiusBookIconStr			"ID80_Book_Icon.icns"
	#define kCitiusBookExtension		"INDB"
	#define kCitiusBookMacOSType		"IDb9"
#endif
#ifdef NOPACKAGE
	#define kCitiusBookIconStr			"169"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kSiriusBookDescription		"InDesign\U00AE CC 2014.0 Book"
#define kSiriusBookIconStr			"ID80_Book_Icon.icns"
#define kSiriusBookExtension		"INDB"
#define kSiriusBookMacOSType		"IDbX"
#endif
#ifdef NOPACKAGE
#define kSiriusBookIconStr			"169"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR5BookDescription		"InDesign\U00AE CC 2015.0 Book"
#define kR5BookIconStr			"ID80_Book_Icon.icns"
#define kR5BookExtension		"INDB"
#define kR5BookMacOSType		"IDbB"
#endif
#ifdef NOPACKAGE
#define kR5BookIconStr			"169"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR10BookDescription		"InDesign\U00AE CC 2017.0 Book"
#define kR10BookIconStr			"ID80_Book_Icon.icns"
#define kR10BookExtension		"INDB"
#define kR10BookMacOSType		"IDbC"
#endif
#ifdef NOPACKAGE
#define kR10BookIconStr			"169"
#endif

//moving kR12BookIcon to 253
#define kDefaultBookIcon				162



// Library

#define kLibraryInterchangeIcon				170
#ifdef INDESIGNPACKAGE
	#define kLibraryInterchangeDescription	"InDesign\U00AE Interchange Library"
	#define kLibraryInterchangeIconStr		"ID_LibraryInterchange_icon.icns"
	#define kLibraryInterchangeExtension	"INLX"
	#define kLibraryInterchangeMacOSType	"InLx"
#endif
#ifdef NOPACKAGE
	#define kLibraryInterchangeIconStr		"170"
#endif


#define kAnnaLibraryIcon					171
#ifdef INDESIGNPACKAGE
	#define kAnnaLibraryDescription			"InDesign\U00AE Library"
	#define kAnnaLibraryIconStr				"ID_Library_v02_Icon.icns"
	#define kAnnaLibraryMacOSType			"InDl"
#endif
#ifdef NOPACKAGE
	#define kAnnaLibraryIconStr				"171"
#endif


#define kDtailLibraryIcon					172
#ifdef INDESIGNPACKAGE
	#define kDtailLibraryDescription		"InDesign\U00AE Library"
	#define kDtailLibraryIconStr			"ID30_Library_CS_Icon.icns"
	#define kDtailLibraryMacOSType			"IDl3"
#endif
#ifdef NOPACKAGE
	#define kDtailLibraryIconStr			"172"
#endif

// Library icons have stopped changing since Firedrake, we don't need an BasilLibraryIcon, AthosLibraryIcon, etc.
#define kFireDrakeLibraryIcon				174
#ifdef INDESIGNPACKAGE
	#define kFireDrakeLibraryDescription	"InDesign\U00AE Library"
	#define kFireDrakeLibraryIconStr		"ID_Library_CC_Icon.icns"	// Just use most recent icon here
	#define kFireDrakeLibraryExtension		"INDL"
	#define kFireDrakeLibraryMacOSType		"IDl4"
#endif
#ifdef NOPACKAGE
	#define kFireDrakeLibraryIconStr		"174"
#endif

#define kDefaultLibraryIcon				173

// IDML - INXAltPackage
#define kBasilINXAltPackageIcon				175
#ifdef INDESIGNPACKAGE
	#define kBasilINXAltPackageDescription	"InDesign\U00AE Markup Language"
	#define kBasilINXAltPackageIconStr		"ID60_IDMLFile_Icon.icns"
	#define kBasilINXAltPackageExtension	"IDML"
	#define kBasilINXAltPackageMacOSType	"IDm6"
#endif
#ifdef NOPACKAGE
	#define kBasilINXAltPackageIconStr		"175"
#endif

#define kRocketINXAltPackageIcon				176
#ifdef INDESIGNPACKAGE
	#define kRocketINXAltPackageDescription	"InDesign\U00AE Markup Language"
	#define kRocketINXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
	#define kRocketINXAltPackageExtension	"IDML"
	#define kRocketINXAltPackageMacOSType	"IDm7"
#endif
#ifdef NOPACKAGE
	#define kRocketINXAltPackageIconStr		"176"
#endif

// IDPP - PreflightProfile
#define kBasilPreflightProfileIcon				177
#ifdef INDESIGNPACKAGE
	#define kBasilPreflightProfileDescription	"InDesign\U00AE PreflightProfile"
	#define kBasilPreflightProfileIconStr		"ID60_IDPP_Icon.icns"
	#define kBasilPreflightProfileExtension		"IDPP"
	#define kBasilPreflightProfileMacOSType		"IDp6"
#endif
#ifdef NOPACKAGE
	#define kBasilPreflightProfileIconStr		"177"
#endif

#define kRocketPreflightProfileIcon				178
#ifdef INDESIGNPACKAGE
	#define kRocketPreflightProfileDescription	"InDesign\U00AE PreflightProfile"
	#define kRocketPreflightProfileIconStr		"ID70_IDPP_Icon.icns"
	#define kRocketPreflightProfileExtension		"IDPP"
	#define kRocketPreflightProfileMacOSType		"IDp7"
#endif
#ifdef NOPACKAGE
	#define kRocketPreflightProfileIconStr		"178"
#endif

#define kR12PreflightProfileIcon				209
#ifdef INDESIGNPACKAGE
    #define kR12PreflightProfileDescription     "InDesign\U00AE PreflightProfile"
    #define kR12PreflightProfileIconStr         "ID_IDPP_Icon.icns"
    #define kR12PreflightProfileExtension		"IDPP"
    #define kR12PreflightProfileMacOSType		"IDp7"
#endif
#ifdef NOPACKAGE
    #define kR12PreflightProfileIconStr		"209"
#endif

// Misc
#define kPackageForGoLiveIcon				179
#ifdef INDESIGNPACKAGE
	#define kPackageForGoLiveDescription	"InDesign\U00AE Package For GoLive"
	#define kPackageForGoLiveIconStr		"ID_GoLivePackage_Icon.icns"
	#define kPackageForGoLiveExtension		"IDPK"
	#define kPackageForGoLiveMacOSType		"IDpk"
#endif
#ifdef NOPACKAGE
	#define kPackageForGoLiveIconStr		"179"
#endif

#define kKeyboardShortcutsIcon				180
#ifdef INDESIGNPACKAGE
	#define kKeyboardShortcutsDescription	"InDesign\U00AE Shortcut Set"
	#define kKeyboardShortcutsIconStr		"ID_KeyboardShortcuts_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kKeyboardShortcutsDescription	"InCopy\U00AE Shortcut Set"
	#define kKeyboardShortcutsIconStr		"IC_KeyboardShortcuts_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kKeyboardShortcutsExtension		"INDK"
	#define kKeyboardShortcutsMacOSType		"InDk"
#endif
#ifdef NOPACKAGE
	#define kKeyboardShortcutsIconStr		"180"
#endif


#define kDefaultsIcon					181
#ifdef INDESIGNPACKAGE
	#define kDefaultsIconStr				"ID_Defaults_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kDefaultsIconStr				"IC_Defaults_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kDefaultsIconStr				"181"
#endif


#define kPreferencesIcon					182
#ifdef INDESIGNPACKAGE
	#define kPreferencesDescription			"InDesign\U00AE Defaults"
	#define kPreferencesIconStr				"ID_Prefs_icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kPreferencesDescription			"InCopy\U00AE Defaults"
	#define kPreferencesIconStr				"IC_Prefs_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPreferencesMacOSType			"InDf"
#endif
#ifdef NOPACKAGE
	#define kPreferencesIconStr				"182"
#endif


#define kSavedDataIcon						183
#ifdef INDESIGNPACKAGE
	#define kSavedDataDescription			"InDesign\U00AE SavedData"
	#define kSavedDataIconStr				"ID_SavedData_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kSavedDataDescription			"InCopy\U00AE SavedData"
	#define kSavedDataIconStr				"IC_SavedData_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kSavedDataMacOSType				"InSd"
#endif
#ifdef NOPACKAGE
	#define kSavedDataIconStr				"183"
#endif


#define kRecoverDataIcon					184
#ifdef INDESIGNPACKAGE
	#define kRecoverDataDescription			"InDesign\U00AE Recovery Data"
	#define kRecoverDataIconStr				"ID_RecoverData_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kRecoverDataDescription			"InCopy\U00AE Recovery Data"
	#define kRecoverDataIconStr				"IC_RecoverData_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kRecoverDataMacOSType			"InRd"
#endif
#ifdef NOPACKAGE
	#define kRecoverDataIconStr				"184"
#endif


#define kLockFileIcon						185
#ifdef INDESIGNPACKAGE
	#define kLockFileDescription			"InDesign\U00AE Lock File"
	#define kLockFileIconStr				"ID_LockFile_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kLockFileDescription			"InCopy\U00AE Lock File"
	#define kLockFileIconStr				"IC_LockFile_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kLockFileExtension				"INLK"
	#define kLockFileMacOSType				"InLk"
#endif
#ifdef NOPACKAGE
	#define kLockFileIconStr				"185"
#endif


#define kColorSettingsIcon					186
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kColorSettingsDescription		"Adobe Color Settings File"
	#define kColorSettingsIconStr			"ID_ColorSettings_Icon.icns"
	#define kColorSettingsExtension			"CSF"
	#define kColorSettingsMacOSType			"AsCs"
#endif
#ifdef NOPACKAGE
	#define kColorSettingsIconStr			"186"
#endif


#define kJavaScriptFileIcon					187
#ifdef INDESIGNPACKAGE
	#define kJavaScriptFileDescription		"InDesign\U00AE Javascript File"
	#define kJavaScriptFileIconStr			"ID_JavaScriptFile_Icon.icns"
	#define kJavaScriptFileMacOSType		"InRd"
#endif
#ifdef NOPACKAGE
	#define kJavaScriptFileIconStr			"187"
#endif

#define kSwatchExchangeIcon					188
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kSwatchExchangeDescription		"Adobe\U00AE Swatch Exchange File"
	#define kSwatchExchangeIconStr			"ID_ASE_Icon.icns"
	#define kSwatchExchangeExtension		"ASE"
	#define kSwatchExchangeMacOSType		"ASEF"
#endif
#ifdef NOPACKAGE
	#define kSwatchExchangeIconStr			"188"
#endif

#define kPSColorBookIcon					189
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPSColorBookDescription			"Adobe\U00AE Color Book File"
	#define kPSColorBookIconStr				"PS_ColorBookIcon.icns"
	#define kPSColorBookExtension			"ACB"
	#define kPSColorBookExtensionLegacy		"ACBL"
	#define kPSColorBookMacOSType			"8BCB"
#endif
#ifdef NOPACKAGE
	#define kPSColorBookIconStr				"189"
#endif


// Plugin Icon

#define kPluginIcon							190
#ifdef INDESIGNPACKAGE
	#define kAdobePluginDescription			"InDesign\U00AE Plug-In"
	#define kPluginIconStr					"ID_Plug-InAdobe_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kAdobePluginDescription			"InCopy\U00AE Plug-In"
	#define kPluginIconStr					"IC_Plug-inAdobe_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAdobePluginExtension			"InDesignPlugin"
	#define kAdobePluginMacOSType			"InDa"
#endif
#ifdef NOPACKAGE
	#define kPluginIconStr					"190"
#endif


#define kRequiredPluginIcon					191
#ifdef INDESIGNPACKAGE
	#define kRequiredPluginDescription		"InDesign\U00AE Plug-In"
	#define kRequiredPluginIconStr			"ID_Plug-InRequired_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kRequiredPluginDescription		"InCopy\U00AE Plug-In"
	#define kRequiredPluginIconStr			"IC_Plug-inRequired_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kRequiredPluginExtension		"InDesignPlugin"
	#define kRequiredPluginMacOSType		"InDr"
#endif
#ifdef NOPACKAGE
	#define kRequiredPluginIconStr			"191"
#endif


#define k3rdPartyPluginIcon					192
#ifdef INDESIGNPACKAGE
	#define k3rdPartyPluginDescription		"InDesign\U00AE Plug-In"
	#define k3rdPartyPluginIconStr			"ID_Plug-In3dParty_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define k3rdPartyPluginDescription		"InCopy\U00AE Plug-In"
	#define k3rdPartyPluginIconStr			"IC_Plug-in3dParty_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define k3rdPartyPluginExtension		"InDesignPlugin"
	#define k3rdPartyPluginMacOSType		"InD3"
#endif
#ifdef NOPACKAGE
	#define k3rdPartyPluginIconStr			"192"
#endif


#define kPluginSetIcon						193
#ifdef INDESIGNPACKAGE
	#define kPluginSetDescription			"InDesign\U00AE Plug-In Set"
	#define kPluginSetIconStr				"ID_Plug-InSets_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kPluginSetDescription			"InCopy\U00AE Plug-In Set"
	#define kPluginSetIconStr				"IC_Plug-InSets_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPluginSetExtension				"PSET"
	#define kPluginSetMacOSType				"Pset"
#endif
#ifdef NOPACKAGE
	#define kPluginSetIconStr				"193"
#endif


#define kSangamFilterIcon					194
#ifdef INDESIGNPACKAGE
	#define kSangamFilterDescription		"InDesign\U00AE Filter"
	#define kSangamFilterIconStr			"ID_Filter_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kSangamFilterDescription		"InCopy\U00AE Filter"
	#define kSangamFilterIconStr			"IC_Filter_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kSangamFilterExtension1			"SMRD"
	#define kSangamFilterExtension2			"SMWT"
	#define kSangamFilterMacOSType1			"Smrd"
	#define kSangamFilterMacOSType2			"Smwt"
#endif
#ifdef NOPACKAGE
	#define kSangamFilterIconStr			"194"
#endif




// Dictionary - these two icons are the same right now

#define kLanguageDictIcon					195
#ifdef INDESIGNPACKAGE
	#define kLanguageDictDescription		"InDesign\U00AE Language Dictionary"
	#define kLanguageDictIconStr			"ID_LanguageDict_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kLanguageDictDescription		"InCopy\U00AE Language Dictionary"
	#define kLanguageDictIconStr			"IC_LanguageDict_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kLanguageDictMacOSType			"InDx"
#endif
#ifdef NOPACKAGE
	#define kLanguageDictIconStr			"195"
#endif


#define kUserDictIcon						196
#ifdef INDESIGNPACKAGE
	#define kUserDictDescription			"InDesign\U00AE User Dictionary"
	#define kUserDictIconStr				"ID_LanguageDict_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kUserDictDescription			"InCopy\U00AE User Dictionary"
	#define kUserDictIconStr				"IC_LanguageDict_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kUserDictExtension				"UDC"
	#define kUserDictMacOSType				"InDu"
#endif
#ifdef NOPACKAGE
	#define kUserDictIconStr				"196"
#endif

#define kAthosINXAltPackageIcon             197
#ifdef INDESIGNPACKAGE
	#define kAthosINXAltPackageDescription	"InDesign\U00AE Markup Language"
	#define kAthosINXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
	#define kAthosINXAltPackageExtension	"IDML"
	#define kAthosINXAltPackageMacOSType	"IDm8"
#endif
#ifdef NOPACKAGE
	#define kAthosINXAltPackageIconStr		"197"
#endif

#define kCitiusINXAltPackageIcon			198
#ifdef INDESIGNPACKAGE
	#define kCitiusINXAltPackageDescription	"InDesign\U00AE Markup Language"
	#define kCitiusINXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
	#define kCitiusINXAltPackageExtension	"IDML"
	#define kCitiusINXAltPackageMacOSType	"IDm9"
#endif
#ifdef NOPACKAGE
	#define kCitiusINXAltPackageIconStr		"198"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kSiriusINXAltPackageDescription	"InDesign\U00AE Markup Language"
#define kSiriusINXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
#define kSiriusINXAltPackageExtension	"IDML"
#define kSiriusINXAltPackageMacOSType	"IDmX"
#endif
#ifdef NOPACKAGE
#define kSiriusINXAltPackageIconStr		"198"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR5INXAltPackageDescription	"InDesign\U00AE Markup Language"
#define kR5INXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
#define kR5INXAltPackageExtension	"IDML"
#define kR5INXAltPackageMacOSType	"IDmB"
#endif
#ifdef NOPACKAGE
#define kR5INXAltPackageIconStr		"198"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR10INXAltPackageDescription	"InDesign\U00AE Markup Language"
#define kR10INXAltPackageIconStr		"ID70_IDMLFile_Icon.icns"
#define kR10INXAltPackageExtension	"IDML"
#define kR10INXAltPackageMacOSType	"IDmC"
#endif
#ifdef NOPACKAGE
#define kR10INXAltPackageIconStr		"198"
#endif


#define kR12INXAltPackageIcon			199
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR12INXAltPackageDescription	"InDesign\U00AE Markup Language"
#define kR12INXAltPackageIconStr		"ID_IDMLFile_Icon.icns"
#define kR12INXAltPackageExtension      "IDML"
#define kR12INXAltPackageMacOSType      "IDmD"
#endif
#ifdef NOPACKAGE
#define kR12INXAltPackageIconStr		"199"
#endif

//Presets icon

#define kFlattenerStyleIcon					200
#ifdef INDESIGNPACKAGE
	#define kFlattenerStyleDescription		"InDesign\U00AE Flattener Presets"
	#define kFlattenerStyleIconStr			"ID_FlattenerPresets_Icon.icns"
	#define kFlattenerStyleExtension		"FLST"
	#define kFlattenerStyleMacOSType		"FlSt"
#endif
#ifdef NOPACKAGE
	#define kFlattenerStyleIconStr			"200"
#endif


#define kPrintStyleIcon						201
#ifdef INDESIGNPACKAGE
	#define kPrintStyleDescription			"InDesign\U00AE Printer Presets"
	#define kPrintStyleIconStr				"ID_PrinterPresets_Icon.icns"
	#define kPrintStyleExtension			"PRST"
	#define kPrintStyleMacOSType			"PrSt"
#endif
#ifdef NOPACKAGE
	#define kPrintStyleIconStr				"201"
#endif


#define kPDFStyleIcon						202
#ifdef INDESIGNPACKAGE
	#define kPDFStyleDescription			"InDesign\U00AE PDF Presets"
	#define kPDFStyleIconStr				"ID_PDFPresets_Icon.icns"
	#define kPDFStyleExtension				"PDFS"
	#define kPDFStyleMacOSType				"PdfS"
// The job options presets share the same icon as the PDF presets
	#define kJobOptionStyleDescription		"Adobe\U00AE PDF Settings File"
	#define kJobOptionStyleExtension		"joboptions"
	#define kJobOptionStyleMacOSType		"????"

#endif
#ifdef NOPACKAGE
	#define kPDFStyleIconStr				"202"
#endif


#define kDocumentStyleIcon					203
#ifdef INDESIGNPACKAGE
	#define kDocumentStyleDescription		"InDesign\U00AE Document Presets"
	#define kDocumentStyleIconStr			"ID_DocPresets_Icon.icns"
	#define kDocumentStyleExtension			"DCST"
	#define kDocumentStyleMacOSType			"DcSt"
#endif
#ifdef INCOPYPACKAGE
	#define kDocumentStyleDescription		"InCopy\U00AE Document Presets"
	#define kDocumentStyleIconStr			"IC_DocPresets_Icon.icns"
	#define kDocumentStyleExtension			"ICST"
	#define kDocumentStyleMacOSType			"IcSt"
#endif
#ifdef NOPACKAGE
	#define kDocumentStyleIconStr			"203"
#endif

#define kLinePresetsIcon					204
#ifdef INDESIGNPACKAGE
	#define kLinePresetsDescription			"InDesign\U00AE Line Presets"
	#define kLinePresetsIconStr				"ID_LinePresets_Icon.icns"
	#define kLinePresetsExtension			"LNST"
	#define kLinePresetsMacOSType			"LnSt"
#endif
#ifdef NOPACKAGE
	#define kLinePresetsIconStr				"204"
#endif


//InCopy specific icon

#define kZionDocumentIcon					210

#define kDenaliDocumentIcon					211
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kDenaliDocumentDescription		"InCopy\U00AE Document"
	#define kDenaliDocumentIconStr			"IC30_Document_Icon.icns"
	#define kDenaliDocumentMacOSType		"InCd"
#endif
#ifdef NOPACKAGE
	#define kDenaliDocumentIconStr			"211"
#endif


#define kDenaliTemplateIcon					212
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kDenaliTemplateDescription		"InCopy\U00AE Template"
	#define kDenaliTemplateIconStr			"IC_TemplateGeneric_Icon.icns"
	#define kDenaliTemplateExtension		"INCT"
	#define kDenaliTemplateMacOSType		"snCd"
#endif
#ifdef NOPACKAGE
	#define kDenaliTemplateIconStr			"212"
#endif


#define kMtBlancDocumentIcon				213
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kMtBlancDocumentDescription		"InCopy\U00AE Document"
	#define kMtBlancDocumentIconStr			"IC30_Document_Icon.icns"
	#define kMtBlancDocumentExtension		"INCD"
	#define kMtBlancDocumentMacOSType		"ICD3"
#endif
#ifdef NOPACKAGE
	#define kMtBlancDocumentIconStr			"213"
#endif


#define kMtBlancTemplateIcon				214
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kMtBlancTemplateDescription		"InCopy\U00AE Template"
	#define kMtBlancTemplateIconStr			"IC80_Stationary_Icon.icns"
	#define kMtBlancTemplateExtension		"INCT"
	#define kMtBlancTemplateMacOSType		"sCx4"
#endif
#ifdef NOPACKAGE
	#define kMtBlancTemplateIconStr			"214"
#endif

// This is for the UnInstall for InCopy pluins from InDesign on Windows
#define kInCopyExtraInstallIcon			215


#define kShivanDocumentIcon					216
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kShivanDocumentDescription		"InCopy\U00AE Document"
	#define kShivanDocumentIconStr			"IC30_Document_Icon.icns"
	#define kShivanDocumentExtension		"INCX"
	#define kShivanDocumentMacOSType		"ICx4"
#endif
#ifdef NOPACKAGE
	#define kShivanDocumentIconStr			"216"
#endif

#define kActionsIcon						217
#ifdef INDESIGNPACKAGE
	#define kActionDescription				"InDesign\U00AE Action Set"
	#define kActionIconStr					"ID_SaveBackwardsInt_Icon.icns"
#endif
#ifdef INCOPYPACKAGE
	#define kActionDescription				"InCopy\U00AE Action Set"
	#define kActionIconStr					"IC_SaveBackwardsInt_Icon.icns"
#endif
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kActionExtension				"ATN"
	#define kActionMacOSType				"IDac"
#endif
#ifdef NOPACKAGE
	#define kActionIconStr					"217"
#endif

#define kAssignmentsIcon				218
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAssignmentsDescription			"InCopy\U00AE Assignment"
	#define kAssignmentsIconStr				"IC_AssignGeneric_Icon.icns"
	#define kAssignmentsExtension			"INCA"
	#define kAssignmentsMacOSType			"InCA"
#endif
#ifdef NOPACKAGE
	#define kAssignmentsIconStr			"218"
#endif

#define kJBXContainerIcon				219
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kJBXContainerDescription		"InDesign\U00AE Job Bag"
	#define kJBXContainerIconStr			"ID_JobBagContainer_Icon.icns"
	#define kJBXContainerExtension			"INJB"
	#define kJBXContainerMacOSType			"InJB"
#endif
#ifdef NOPACKAGE
	#define kJBXContainerIconStr			"219"
#endif

#define kResourceFileIcon				220
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kResourceFileDescription		"InDesign\U00AE Resource File"
	#define kResourceFileIconStr			"ID_ResourceFile_Icon.icns"
	#define kResourceFileExtension			"INRS"
	#define kResourceFileMacOSType			"InRs"
#endif
#ifdef NOPACKAGE
	#define kResourceFileIconStr			"220"
#endif

#define kMenuSetFileIcon				221
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kMenuSetFileDescription	"InDesign\U00AE Menu Set"
	#define kMenuSetFileIconStr		"ID_MenuSetFile_Icon.icns"
	#define kMenuSetFileExtension		"INMS"
	#define kMenuSetFileMacOSType		"InMs"
#endif
#ifdef NOPACKAGE
	#define kMenuSetFileIconStr		"221"
#endif

#define kICAssignmentPackageIcon		222
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kICAssignmentPackageDescription		"InCopy\U00AE Assignment Package"
	#define kICAssignmentPackageIconStr			"IC50_DocumentPkg_Icon.icns"
	#define kICAssignmentPackageExtension		"INCP"
	#define kICAssignmentPackageMacOSType		"InCP"
#endif
#ifdef NOPACKAGE
	#define kICAssignmentPackageIconStr			"222"
#endif

#define kIDAssignmentPackageIcon		223
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kIDAssignmentPackageDescription		"InDesign\U00AE Assignment Package"
	#define kIDAssignmentPackageIconStr			"ID_DocumentPkg.icns"
	#define kIDAssignmentPackageExtension		"INDP"
	#define kIDAssignmentPackageMacOSType		"InDP"
#endif
#ifdef NOPACKAGE
	#define kIDAssignmentPackageIconStr			"223"
#endif


#define kKryptonDocumentIcon					224
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kKryptonDocumentDescription		"InCopy\U00AE Document"
	#define kKryptonDocumentIconStr			"IC50_Document_Icon.icns"
	#define kKryptonDocumentExtension		"INCX"
	#define kKryptonDocumentMacOSType		"ICx5"
#endif
#ifdef NOPACKAGE
	#define kKryptonDocumentIconStr			"224"
#endif

#define kKryptonAssignmentsIcon				225
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kKryptonAssignmentsDescription			"InCopy\U00AE Assignment"
	#define kKryptonAssignmentsIconStr				"IC_AssignGeneric_Icon.icns"
	#define kKryptonAssignmentsExtension			"INCA"
	#define kKryptonAssignmentsMacOSType			"ICa5"
#endif
#ifdef NOPACKAGE
	#define kKryptonAssignmentsIconStr			"225"
#endif

#define kKryptonTemplateIcon				226
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kKryptonTemplateDescription		"InCopy\U00AE Template"
	#define kKryptonTemplateIconStr			"IC50_Stationary_Icon.icns"
	#define kKryptonTemplateExtension		"INCT"
	#define kKryptonTemplateMacOSType		"IC5t"
#endif
#ifdef NOPACKAGE
	#define kKryptonTemplateIconStr			"226"
#endif

#define kGenericIDFileIcon					227
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kGenericIDFileIconStr			"ID_DocumentGeneric_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kGenericIDFileIconStr			"227"
#endif

#define kGenericICFileIcon					228
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kGenericICFileIconStr			"IC_DocumentGeneric_Icon.icns"
#endif
#ifdef NOPACKAGE
	#define kGenericICFileIconStr			"228"
#endif

#define kChiveDocumentIcon					229
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kChiveDocumentDescription		"InCopy\U00AE Document"
	#define kChiveDocumentIconStr			"IC60_Document_Icon.icns"
	#define kChiveDocumentExtension		"ICML"
	#define kChiveDocumentMacOSType		"ICx6"
#endif
#ifdef NOPACKAGE
	#define kChiveDocumentIconStr			"229"
#endif

#define kChiveAssignmentsIcon				230
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kChiveAssignmentsDescription			"InCopy\U00AE Assignment"
	#define kChiveAssignmentsIconStr				"IC60_ICMA_Icon.icns"
	#define kChiveAssignmentsExtension			"ICMA"
	#define kChiveAssignmentsMacOSType			"ICa6"
#endif
#ifdef NOPACKAGE
	#define kChiveAssignmentsIconStr			"230"
#endif

#define kChiveTemplateIcon				231
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kChiveTemplateDescription		"InCopy\U00AE Template"
	#define kChiveTemplateIconStr			"IC60_Stationary_Icon.icns"
	#define kChiveTemplateExtension		"ICMT"
	#define kChiveTemplateMacOSType		"IC6t"
#endif
#ifdef NOPACKAGE
	#define kChiveTemplateIconStr			"231"
#endif

#define kChiveICAssignmentPackageIcon		232
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kChiveICAssignmentPackageDescription		"InCopy\U00AE Assignment Package"
	#define kChiveICAssignmentPackageIconStr			"IC60_DocumentPkg_ICAP.icns"
	#define kChiveICAssignmentPackageExtension		"ICAP"
	#define kChiveICAssignmentPackageMacOSType		"IcAP"
#endif
#ifdef NOPACKAGE
	#define kChiveICAssignmentPackageIconStr			"232"
#endif

#define kChiveIDAssignmentPackageIcon		233
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kChiveIDAssignmentPackageDescription		"InDesign\U00AE Assignment Package"
	#define kChiveIDAssignmentPackageIconStr			"ID60_DocumentPkg_IDAP.icns"
	#define kChiveIDAssignmentPackageExtension		"IDAP"
	#define kChiveIDAssignmentPackageMacOSType		"IdAP"
#endif
#ifdef NOPACKAGE
	#define kChiveIDAssignmentPackageIconStr			"233"
#endif

#define kTrollDocumentIcon					234
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kTrollDocumentDescription		"InCopy\U00AE Document"
	#define kTrollDocumentIconStr			"IC70_Document_Icon.icns"
	#define kTrollDocumentExtension		"ICML"
	#define kTrollDocumentMacOSType		"ICx7"
#endif
#ifdef NOPACKAGE
	#define kTrollDocumentIconStr			"234"
#endif

#define kTrollAssignmentsIcon				235
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kTrollAssignmentsDescription			"InCopy\U00AE Assignment"
	#define kTrollAssignmentsIconStr				"IC70_Stationary_Icon.icns"
	#define kTrollAssignmentsExtension			"ICMA"
	#define kTrollAssignmentsMacOSType			"ICa7"
#endif
#ifdef NOPACKAGE
	#define kTrollAssignmentsIconStr			"235"
#endif

#define kTrollTemplateIcon				236
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kTrollTemplateDescription		"InCopy\U00AE Template"
	#define kTrollTemplateIconStr			"IC70_Stationary_Icon.icns"
	#define kTrollTemplateExtension		"ICMT"
	#define kTrollTemplateMacOSType		"IC7t"
#endif
#ifdef NOPACKAGE
	#define kTrollTemplateIconStr			"236"
#endif

#define kTrollICAssignmentPackageIcon		237
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kTrollICAssignmentPackageDescription		"InCopy\U00AE Assignment Package"
	#define kTrollICAssignmentPackageIconStr			"IC70_DocumentPkg_ICAP.icns"
	#define kTrollICAssignmentPackageExtension		"ICAP"
	#define kTrollICAssignmentPackageMacOSType		"IcAP"
#endif
#ifdef NOPACKAGE
	#define kTrollICAssignmentPackageIconStr			"237"
#endif

#define kR12ICAssignmentPackageIcon		255
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
    #define kR12ICAssignmentPackageDescription		"InCopy\U00AE Assignment Package"
    #define kR12ICAssignmentPackageIconStr			"IC_DocumentPkg_ICAP.icns"
    #define kR12ICAssignmentPackageExtension		"ICAP"
    #define kR12ICAssignmentPackageMacOSType		"IcAP"
#endif
#ifdef NOPACKAGE
    #define kR12ICAssignmentPackageIconStr			"255"
#endif

#define kTrollIDAssignmentPackageIcon		238
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kTrollIDAssignmentPackageDescription		"InDesign\U00AE Assignment Package"
	#define kTrollIDAssignmentPackageIconStr			"ID70_DocumentPkg_IDAP.icns"
	#define kTrollIDAssignmentPackageExtension		"IDAP"
	#define kTrollIDAssignmentPackageMacOSType		"IdAP"
#endif
#ifdef NOPACKAGE
	#define kTrollIDAssignmentPackageIconStr			"238"
#endif

#define kR12IDAssignmentPackageIcon		254
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
    #define kR12IDAssignmentPackageDescription		"InDesign\U00AE Assignment Package"
    #define kR12IDAssignmentPackageIconStr			"ID_DocumentPkg_IDAP.icns"
    #define kR12IDAssignmentPackageExtension		"IDAP"
    #define kR12IDAssignmentPackageMacOSType		"IdAP"
#endif
#ifdef NOPACKAGE
    #define kR12IDAssignmentPackageIconStr			"254"
#endif

#define kFreyaDocumentIcon					239
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kFreyaDocumentDescription		"InCopy\U00AE Document"
	#define kFreyaDocumentIconStr			"IC75_Document_Icon.icns"
	#define kFreyaDocumentExtension		"ICML"
	#define kFreyaDocumentMacOSType		"ICx2"	// Ideally we could use something like ICx75 here, but we only get four chars, use 2 instead so Porthos can use 8
#endif
#ifdef NOPACKAGE
	#define kFreyaDocumentIconStr			"239"
#endif

#define kFreyaTemplateIcon				240
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kFreyaTemplateDescription		"InCopy\U00AE Template"
	#define kFreyaTemplateIconStr			"IC75_Stationary_Icon.icns"
	#define kFreyaTemplateExtension		"ICMT"
	#define kFreyaTemplateMacOSType		"IC2t"	// Ideally we could use something like IC75t here, but we only get four chars, use 2 instead so Porthos can use 8
#endif
#ifdef NOPACKAGE
	#define kFreyaTemplateIconStr			"240"
#endif

#define kPorthosDocumentIcon					241
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPorthosDocumentDescription		"InCopy\U00AE Document"
	#define kPorthosDocumentIconStr			"IC_Document_Icon.icns"
	#define kPorthosDocumentExtension		"ICML"
	#define kPorthosDocumentMacOSType		"ICx8"	
#endif
#ifdef NOPACKAGE
	#define kPorthosDocumentIconStr			"241"
#endif

#define kPorthosTemplateIcon				242
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPorthosTemplateDescription		"InCopy\U00AE Template"
	#define kPorthosTemplateIconStr			"IC80_Stationary_Icon.icns"
	#define kPorthosTemplateExtension		"ICMT"
	#define kPorthosTemplateMacOSType		"IC8t"
#endif
#ifdef NOPACKAGE
	#define kPorthosTemplateIconStr			"242"
#endif

#define kPorthosAssignmentsIcon				243
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kPorthosAssignmentsDescription			"InCopy\U00AE Assignment"
	#define kPorthosAssignmentsIconStr				"IC70_ICMA_Icon.icns"
	#define kPorthosAssignmentsExtension			"ICMA"
	#define kPorthosAssignmentsMacOSType			"ICa8"
#endif
#ifdef NOPACKAGE
	#define kPorthosAssignmentsIconStr			"243"
#endif

// kAltiusAssignmentsIcon (246)  moved to end of list to keep numbers in sequence

// CC
#define kAltiusDocumentIcon					244
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAltiusDocumentDescription		"InCopy\U00AE Document"
	#define kAltiusDocumentIconStr			"IC_Document_Icon.icns"
	#define kAltiusDocumentExtension		"ICML"
	#define kAltiusDocumentMacOSType		"ICx9"	
#endif
#ifdef NOPACKAGE
	#define kAltiusDocumentIconStr			"244"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kCanopusDocumentDescription		"InCopy\U00AE Document"
#define kCanopusDocumentIconStr			"IC_Document_Icon.icns"
#define kCanopusDocumentExtension		"ICML"
#define kCanopusDocumentMacOSType		"ICxX"
#endif
#ifdef NOPACKAGE
#define kCanopusDocumentIconStr			"244"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR5InCopyDocumentDescription		"InCopy\U00AE Document"
#define kR5InCopyDocumentIconStr			"IC_Document_Icon.icns"
#define kR5InCopyDocumentExtension		"ICML"
#define kR5InCopyDocumentMacOSType		"ICxB"
#endif
#ifdef NOPACKAGE
#define kR5InCopyDocumentIconStr			"244"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR10InCopyDocumentDescription		"InCopy\U00AE Document"
#define kR10InCopyDocumentIconStr			"IC_Document_Icon.icns"
#define kR10InCopyDocumentExtension		"ICML"
#define kR10InCopyDocumentMacOSType		"ICxC"
#endif
#ifdef NOPACKAGE
#define kR10InCopyDocumentIconStr			"244"
#endif

//moving kR12InCopyDocumentIcon at 249

#define kAltiusTemplateIcon					245
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAltiusTemplateDescription		"InCopy\U00AE Template"
	#define kAltiusTemplateIconStr			"IC80_Stationary_Icon.icns"
	#define kAltiusTemplateExtension		"ICMT"
	#define kAltiusTemplateMacOSType		"IC9t"
#endif
#ifdef NOPACKAGE
	#define kAltiusTemplateIconStr			"245"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kCanopusTemplateDescription		"InCopy\U00AE Template"
#define kCanopusTemplateIconStr			"IC80_Stationary_Icon.icns"
#define kCanopusTemplateExtension		"ICMT"
#define kCanopusTemplateMacOSType		"ICXt"
#endif
#ifdef NOPACKAGE
#define kCanopusTemplateIconStr			"245"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR5InCopyTemplateDescription		"InCopy\U00AE Template"
#define kR5InCopyTemplateIconStr			"IC80_Stationary_Icon.icns"
#define kR5InCopyTemplateExtension		"ICMT"
#define kR5InCopyTemplateMacOSType		"ICBt"
#endif
#ifdef NOPACKAGE
#define kR5InCopyTemplateIconStr			"245"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR10InCopyTemplateDescription		"InCopy\U00AE Template"
#define kR10InCopyTemplateIconStr			"IC80_Stationary_Icon.icns"
#define kR10InCopyTemplateExtension		"ICMT"
#define kR10InCopyTemplateMacOSType		"ICCt"
#endif
#ifdef NOPACKAGE
#define kR10InCopyTemplateIconStr			"245"
#endif


//moving kR12InCopyTemplateIcon to 250


#define kAltiusAssignmentsIcon				246
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kAltiusAssignmentsDescription	"InCopy\U00AE Assignment"
	#define kAltiusAssignmentsIconStr		"IC70_ICMA_Icon.icns"
	#define kAltiusAssignmentsExtension		"ICMA"
	#define kAltiusAssignmentsMacOSType		"ICa9"
#endif
#ifdef NOPACKAGE
	#define kAltiusAssignmentsIconStr		"246"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kCanopusAssignmentsDescription	"InCopy\U00AE Assignment"
#define kCanopusAssignmentsIconStr		"IC70_ICMA_Icon.icns"
#define kCanopusAssignmentsExtension	"ICMA"
#define kCanopusAssignmentsMacOSType	"ICaX"
#endif
#ifdef NOPACKAGE
#define kCanopusAssignmentsIconStr		"246"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR5AssignmentsDescription	"InCopy\U00AE Assignment"
#define kR5AssignmentsIconStr		"IC70_ICMA_Icon.icns"
#define kR5AssignmentsExtension	"ICMA"
#define kR5AssignmentsMacOSType	"ICaB"
#endif
#ifdef NOPACKAGE
#define kR5AssignmentsIconStr		"246"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR10AssignmentsDescription	"InCopy\U00AE Assignment"
#define kR10AssignmentsIconStr		"IC70_ICMA_Icon.icns"
#define kR10AssignmentsExtension	"ICMA"
#define kR10AssignmentsMacOSType	"ICaC"
#endif
#ifdef NOPACKAGE
#define kR10AssignmentsIconStr		"246"
#endif


//moving  kR12AssignmentsIcon to 251

#define kCitiusTemplateIcon				247
#ifdef INDESIGNPACKAGE
	#define kCitiusTemplateDescription	"InDesign\U00AE CC.0 Template"
	#define kCitiusTemplateIconStr		"ID80_Stationary_Icon.icns"
	#define kCitiusTemplateExtension	"INDT"
	#define kCitiusTemplateMacOSType	"ID9t"
#endif
#ifdef NOPACKAGE
	#define kCitiusTemplateIconStr		"247"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kSiriusTemplateDescription	"InDesign\U00AE CC 2014.0 Template"
#define kSiriusTemplateIconStr		"ID80_Stationary_Icon.icns"
#define kSiriusTemplateExtension	"INDT"
#define kSiriusTemplateMacOSType	"IDXt"
#endif
#ifdef NOPACKAGE
#define kSiriusTemplateIconStr		"247"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR5TemplateDescription	"InDesign\U00AE CC 2015.0 Template"
#define kR5TemplateIconStr		"ID80_Stationary_Icon.icns"
#define kR5TemplateExtension	"INDT"
#define kR5TemplateMacOSType	"IDBt"
#endif
#ifdef NOPACKAGE
#define kR5TemplateIconStr		"247"
#endif

// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR10TemplateDescription	"InDesign\U00AE CC 2017.0 Template"
#define kR10TemplateIconStr		"ID80_Stationary_Icon.icns"
#define kR10TemplateExtension	"INDT"
#define kR10TemplateMacOSType	"IDCt"
#endif
#ifdef NOPACKAGE
#define kR10TemplateIconStr		"247"
#endif

//moving kR12TemplateIcon to 252


#define kCitiusSnippetIcon				248
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
	#define kCitiusSnippetDescription	"InDesign\U00AE Snippet"
	#define kCitiusSnippetIconStr		"ID70_IDMSSecondary_Icon.icns"
	#define kCitiusSnippetExtension		"IDMS"
	#define kCitiusSnippetMacOSType		"IdMs"
#endif
#ifdef NOPACKAGE
	#define kCitiusSnippetIconStr		"248"
#endif

#define kR12SnippetIcon				208
//ID and IC use the same icon for snippets
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
    #define kR12SnippetDescription	"InDesign\U00AE Snippet"
    #define kR12SnippetIconStr		"ID_IDMSSecondary_Icon.icns"
    #define kR12SnippetExtension		"IDMS"
    #define kR12SnippetMacOSType		"IdMs"
#endif
#ifdef NOPACKAGE
    #define kR12SnippetIconStr		"208"
#endif

#define kR12InCopyDocumentIcon					249
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR12InCopyDocumentDescription		"InCopy\U00AE Document"
#define kR12InCopyDocumentIconStr			"IC_Document_Icon.icns"
#define kR12InCopyDocumentExtension		"ICML"
#define kR12InCopyDocumentMacOSType		"ICxD"
#endif
#ifdef NOPACKAGE
#define kR12InCopyDocumentIconStr			"249"
#endif

#define  kR12InCopyTemplateIcon				250
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR12InCopyTemplateDescription		"InCopy\U00AE Template"
#define kR12InCopyTemplateIconStr			"IC_Stationary_Icon.icns"
#define kR12InCopyTemplateExtension		"ICMT"
#define kR12InCopyTemplateMacOSType		"ICDt"
#endif
#ifdef NOPACKAGE
#define kR12InCopyTemplateIconStr			"250"
#endif


#define  kR12AssignmentsIcon				251
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kR12AssignmentsDescription	"InCopy\U00AE Assignment"
#define kR12AssignmentsIconStr		"IC_ICMA_Icon.icns"
#define kR12AssignmentsExtension	"ICMA"
#define kR12AssignmentsMacOSType	"ICaD"
#endif
#ifdef NOPACKAGE
#define kR12AssignmentsIconStr		"251"
#endif

#define kR12TemplateIcon				252
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR12TemplateDescription	"InDesign\U00AE 2021.0 Template"
#define kR12TemplateIconStr		"ID_Stationary_Icon.icns"
#define kR12TemplateExtension	"INDT"
#define kR12TemplateMacOSType	"IDDt"
#endif
#ifdef NOPACKAGE
#define kR12TemplateIconStr		"252"
#endif

#define kR12BookIcon					253
// we need to update only description and MAC OS Type, no change on Win. Icons are same as CC
#ifdef INDESIGNPACKAGE
#define kR12BookDescription		"InDesign\U00AE 2021.0 Book"
#define kR12BookIconStr			"ID_Book_Icon.icns"
#define kR12BookExtension		"INDB"
#define kR12BookMacOSType		"IDbD"
#endif
#ifdef NOPACKAGE
#define kR12BookIconStr			"253"
#endif



#if (defined(INDESIGNPACKAGE) || defined(INCOPYPACKAGE))
#define kEPubFileDescription	"Adobe\U00AE Digital Editions Document"
#define kEPubFileExtension		"epub"
#define kEPubFileMacOSType		"EPUB"
#endif

// Range 256 - 999
// This group is for non-file icons that are common to
// both the Mac and PC.
#define kNewObjectButtonIcon			256
#define kDeleteObjectButtonIcon			257
#define kArrowDownPopupIcon				258
#define kTreeBranchCollapsedRsrcID		259
#define kTreeBranchExpandedRsrcID		260
#define kArrowPopupIcon					261
#define kOWLArrowPopupIcon				262
#define kEyeballIcon					263
#define kWarningBigIcon					264
#define kWarningMediumIcon				265
#define kRGBIcon						266
#define kCYMKIcon						267
#define kLockIcon						268
#define kSpotIcon						269
#define kProcessIcon					270
#define kNoPencilIcon					271
#define kQuestionMarkBigIcon			272
#define kQuestionMarkSmallIcon			273
#define kNoneIcon						274
#define kLabColorIcon					275
#define kStopSignBigIcon				276
#define kPalettePopupSliderArrowIcon	277
#define	kRegistrationMarkIcon			279
#define kInformationSignBigIcon			280
#define kInfoAngleIconID				281
#define kInfoShearIconID				282
#define kInfoLocationIconID				283
#define kInfoGeometryIconID				284
#define kInfoFillIconID					285
#define kInfoStrokeIconID				286
#define kInfoHorzScaleIconID			287
#define kInfoVertScaleIconID			288
#define kInfoMoveIconID					289
#define kInformationSignSmallIcon		290

#define kMixedInkIconID					291
#define kMixedInkParentIconID			292
#define kGenericFolderIconID			293
#define kChainIconNotConstrained		296
#define kChainIconConstrained			297
#define kInformationSignMediumIcon		299

#define		kAngleIconID					301
#define		kShearIconID					302
#define		kRotateCWIconID					303
#define		kRotateCCWIconID				304
#define		kFlipVerticalIconID				305
#define		kFlipHorizontalIconID			306

#define		kTreeBranchCollapsedMERsrcID	308
#define		kInfoLocationIconMEID			309

#define		kMigrateToCreativeCloudIcon		310
#define		kMigrateToCreativeCloudMediumIcon		312

#define		kStandardTreeNodeChildWidgetIconRsrcID	314

#define		kStrokePanelButCapIconID				315
#define		kStrokePanelRoundCapIconID				317
#define		kStrokePanelProjectingCapIconID			319

#define		kStrokePanelMiterJoinIconID				330
#define		kStrokePanelRoundedJoinIconID			332
#define		kStrokePanelBevelJoinIconID				334
#define		kStrokePanelAlignCenterIconID			336
#define		kStrokePanelAlignInsideIconID			338
#define		kStrokePanelAlignOutsideIconID			340

#define		kLibraryPanelXMLAssetThumbnailIconID	350

// Killer find ids
#define		kKillerFindButtonPNGRsrcID				352
#define		kClearAllOverridesButtonIconID			353			// Used in Paragraph Styles Panel
#define		kClearAllOverridesButtonSmallIconID		354		// Used in Control Strip
#define		kKillerFindSmallButtonPNGRsrcID			355

#define		kResizePresentationIconID				409

#define		kWarningSmallIconRsrcID					417

#define kArrowUpButtonIcon							418
#define kArrowDownButtonIcon						419

#define kFirstPageIconRsrcID						500
#define kLastPageIconRsrcID							501
#define kForwardPagePlusIconRsrcID					502
#define kBackwardPageMinusIconRsrcID				503

#define kArrowSortUpIconRsrcID						505
#define kArrowSortDownIconRsrcID					506

#define kPageRangeCommonSizeIconRsrcID				507

// gap for 508

#define kGroupLockedOpaqueIconRsrcID				509
#define kPageItemLockedOpaqueIconRsrcID				510
#define kPrimaryTextFlowOnIconRsrcID				511
#define kPrimaryTextFlowOffIconRsrcID				512

#define kRulerGuideIconRsrcID						513
#define kLiquidHGuideIconRsrcID						514
#define kLiquidVGuideIconRsrcID						515
#define kMagneticGuideIconRsrcID					516
#define kGrowZoneGuideIconRsrcID					517

#define kShowMoreArrowIconID						518
#define kHideMoreArrowIconID						519

#define kFavoriteStarSelectedIconRsrcID				520
#define kFavoriteStarUnselectedIconRsrcID			521
#define kTransformHorzScaleIconID					522
#define kTransformVertScaleIconID					523
#define kSettingsInCloudFirstDialogIconRsrcID		524
//gap

// small spinners
#define kProgressSpinner1IconRsrcID					526
#define kProgressSpinner2IconRsrcID					527
#define kProgressSpinner3IconRsrcID					528
#define kProgressSpinner4IconRsrcID					529
#define kProgressSpinner5IconRsrcID					530
#define kProgressSpinner6IconRsrcID					531
#define kProgressSpinner7IconRsrcID					532
#define kProgressSpinner8IconRsrcID					533
#define kProgressSpinner9IconRsrcID					534
#define kProgressSpinner10IconRsrcID				535
#define kProgressSpinner11IconRsrcID				536
#define kProgressSpinner12IconRsrcID				537

// large spinners
#define kLargeProgressSpinner1IconRsrcID			538
#define kLargeProgressSpinner2IconRsrcID			539
#define kLargeProgressSpinner3IconRsrcID			540
#define kLargeProgressSpinner4IconRsrcID			541
#define kLargeProgressSpinner5IconRsrcID			542
#define kLargeProgressSpinner6IconRsrcID			543
#define kLargeProgressSpinner7IconRsrcID			544
#define kLargeProgressSpinner8IconRsrcID			545
#define kLargeProgressSpinner9IconRsrcID			546
#define kLargeProgressSpinner10IconRsrcID			547
#define kLargeProgressSpinner11IconRsrcID			548
#define kLargeProgressSpinner12IconRsrcID			549

// Gap

// Defining an IconRsrc for text question marks. These have to be theme independent.
#define kTextQuestionMarkSmallIcon					571

// Gap

#define kLargeWarningIconRsrcID						600
#define kLargeSuccessIconRsrcID						601

//Arrow Heads icons to be shown in the stroke panel...
#define kAlignArrowheadsAtEndIconResID				602
#define kAlignArrowheadsExtendingIconResID			603
#define kSwapArrowheadsIconResID					604

#define kFakeBigInfoAlertIcon                       611
#define kBigErrorAlertIcon			                612

#define kWarningWithIdBigIcon                       613

// Moved from Swatches Panel, but were originally in Graphic Styles (Graphics)
#define		kSwapStrokeFillIconResID				3000
#define		kDefaultStrokeFillIconResID				3001
#define		kSmallSwapStrokeFillIconResID			3002
#define		kTextStrokeFillIconResID				3003
#define		kLayoupStrokeFillIconResID				3004
#define		kTextSmallStrokeFillIconResID			3006
#define		kLayoutSmallStrokeFillIconResID			3007

////////////////////////////////////////////////////
// AppBar icons here that we provide to OWL Canvas
////////////////////////////////////////////////////
#define		kAppBarFirstRsrcID						3400
#define		kAppBarBridgeIconRsrcID					3400
#define		kAppBarViewOptionsRsrcID				3401
#define		kAppBarCheckmarkRsrcID					3402
#define		kAppBarEmptyCheckmarkRsrcID				3403
#define		kAppBarScreenModeRsrcID					3404
#define     kAppBarHomeIconRsrcID					3405
#define		kAppBarDocLayout1UpRsrcID				3406
#define		kAppBarDocLayout2UpColsRsrcID			3407
#define		kAppBarDocLayout2UpRowsRsrcID			3408
#define		kAppBarDocLayout3Up2RowsLeftRsrcID		3409
#define		kAppBarDocLayout3Up2RowsRightRsrcID		3410
#define		kAppBarDocLayout3UpColsRsrcID			3411
#define		kAppBarDocLayout3UpRowsRsrcID			3412
#define		kAppBarDocLayout4Up2ColsSplitRsrcID		3413
#define		kAppBarDocLayout4Up3ColsSplitFarRsrcID	3414
#define		kAppBarDocLayout4Up3ColsSplitRsrcID		3415
#define		kAppBarDocLayout4UpColsRsrcID			3416
#define		kAppBarDocLayout4UpGridRsrcID			3417
#define		kAppBarDocLayout4UpRowsRsrcID			3418
#define		kAppBarDocLayout5Up2ColsSplitRsrcID		3419
#define		kAppBarDocLayout5Up3ColsSplitRsrcID		3420
#define		kAppBarDocLayout5Up3ColSplitLast2RsrcID	3421
#define		kAppBarDocLayout6Up123RsrcID			3422
#define		kAppBarDocLayout6UpGridRsrcID			3423
#define		kAppBarDocLayoutAllHorizRsrcID			3424
#define		kAppBarDocLayoutAllInGridRsrcID			3425
#define		kAppBarDocLayoutAllVertRsrcID			3426

#define		kAppBarBGTaskVerticalBarIcon_01RsrcID		3428
#define		kAppBarBGTaskVerticalBarIcon_02RsrcID		3429
#define		kAppBarBGTaskVerticalBarIcon_03RsrcID		3430
#define		kAppBarBGTaskVerticalBarIcon_04RsrcID		3431
#define		kAppBarBGTaskVerticalBarIcon_05RsrcID		3432
#define		kAppBarBGTaskVerticalBarIcon_06RsrcID		3433
#define		kAppBarBGTaskVerticalBarIcon_07RsrcID		3434
#define		kAppBarBGTaskVerticalBarIcon_08RsrcID		3435
#define		kAppBarBGTaskVerticalBarIcon_09RsrcID		3436
#define		kAppBarBGTaskVerticalBarIcon_10RsrcID		3437
#define		kAppBarBGTaskVerticalBarIcon_11RsrcID		3438
#define		kAppBarBGTaskVerticalBarIcon_12RsrcID		3439
#define		kAppBarBGTaskVerticalBarIcon_13RsrcID		3440

#define		kAppBarBGTaskVerticalBarWithWarningIcon_01RsrcID		3441
#define		kAppBarBGTaskVerticalBarWithWarningIcon_02RsrcID		3442
#define		kAppBarBGTaskVerticalBarWithWarningIcon_03RsrcID		3443
#define		kAppBarBGTaskVerticalBarWithWarningIcon_04RsrcID		3444
#define		kAppBarBGTaskVerticalBarWithWarningIcon_05RsrcID		3445
#define		kAppBarBGTaskVerticalBarWithWarningIcon_06RsrcID		3446
#define		kAppBarBGTaskVerticalBarWithWarningIcon_07RsrcID		3447
#define		kAppBarBGTaskVerticalBarWithWarningIcon_08RsrcID		3448
#define		kAppBarBGTaskVerticalBarWithWarningIcon_09RsrcID		3449
#define		kAppBarBGTaskVerticalBarWithWarningIcon_10RsrcID		3450
#define		kAppBarBGTaskVerticalBarWithWarningIcon_11RsrcID		3451
#define		kAppBarBGTaskVerticalBarWithWarningIcon_12RsrcID		3452
#define		kAppBarBGTaskVerticalBarWithWarningIcon_13RsrcID		3453
#define		kAppBarStockIconRsrcID									3454
#define		kAppBarPublishOnlineRsrcID								3455
#define		kAppBarProgressSpinRsrcID								3456

/*** NOTE ***
 *** For icons to be used in EVE, also add the new icons in AppUIStrings.fr ***
 *** so that the icons can be loaded during view creation from EVE          ***/
#define		kTouchSaveNIconRsrcID						3457
#define		kTouchSaveNDIconRsrcID						3458
#define		kTouchKBNIconRsrcID							3459
#define		kTouchKBNDIconRsrcID						3460
#define		kTouchHelpNIconRsrcID						3461
#define		kTouchHelpNDIconRsrcID						3462
#define     kSelectedToolFlyoutNRsrcID					3463
#define     kSelectedToolFlyoutNDRsrcID					3464
#define		kTouchCloseNIconRsrcID						3465
#define		kTouchCloseNDIconRsrcID						3466
#define		kTWSStatusBarFitWindowIconRsrcID			3467
#define		kTWSStatusBarActualSizeIconRsrcID			3468
#define		kSwitchToTouchNIconRsrcID					3469
#define		kSwitchToTouchNDIconRsrcID					3470

//gap
#define		kIconTouchUndo								3477
#define		kIconTouchRedo								3478
#define		kIconTouchDelete							3479
#define		kContextMenuIconResID						3480
#define		kContextCopyIconResID						3481
#define		kContextCutIconResID						3482
#define		kContextPasteIconResID						3483
#define		kContextDeleteIconResID						3484
#define		kContextArrangeIconResID					3485
#define		kContextSubContextIconResID					3486
#define		kContextArrangeSendBackIconResID			3487
#define		kContextArrangeBringForwardIconResID		3488

#define		kTouchNudgeUpIconRsrcID						3489
#define		kTouchNudgeDownIconRsrcID					3492

#define		kContextFillTextIconResID					3493

#define		kStyleOverrideHighlightButtonIconPNGRsrcID	3494

#define 	kAppBarGPUOnIconRsrcID						3495
#define 	kAppBarGPUOffIconRsrcID						3496
#define		kAppBarExchangeIconRsrcID					3497
#define 	kAppBarLearnIconRsrcID						3498
#define		kAppBarLastRsrcID							3599	// Update as more app bar icons are added
#define		kTreeBranchCollapsedLightRsrcID				3499
#define		kTreeBranchExpandedLightRsrcID				3500
#define		kGenericFolderLightIconID					3501

#define		kResizeGripperBottomLeftIconID				3502

#define     kInfoIconForPageSetupAdaptiveFTUEIconID		3503
#define		kRedefineStyleButtonIconID					3504
#define		kEditStyleIconRsrcID						3505
#define		kToolBarViewOptionsRsrcID					3506
#define     kBackArrowIconRsrcID                        3507
#define     kShareButtonIconRsrcID                      3508
#define     kShareNotificationBtnRsrcID                 3509

#endif //__ICONRSRCDEFS__
