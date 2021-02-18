//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SuppressedUIXMLDefs.h $
//  
//  Owner: Matt Joss
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
#ifndef __SuppressedUIXMLDefs__
#define __SuppressedUIXMLDefs__

#include "WideString.h"

namespace SuppressedUIXMLDefs 
{
	static const WideString kSuppressedUIRootXMLTag( "SuppressedUI" );

	// XML Element Tags
	static const WideString kSuppressedWidgetXMLTag( "SuppressedWidget" );
	static const WideString kSuppressedDragDropXMLTag( "SuppressedDragDrop" );
	static const WideString kSuppressedActionXMLTag( "SuppressedAction" );
	static const WideString kSuppressedMenuXMLTag( "SuppressedMenu" );
	static const WideString kSuppressedPlatformDialogControlXMLTag( "SuppressedPlatformDialogControl" );

	// Attribute names
	static const WideString kSuppressionType( "restrictionType" );
	static const WideString kWidgetIDAttributeName( "widgetID" );
	static const WideString kAncestorWidgetIDAttributeName( "ancestorWidgetID" );
	static const WideString kDragDropFlavorAttributeName( "dragDropFlovor" );
	static const WideString kActionAttributeName( "actionID" );
	static const WideString kMenuAttributeName( "menuName" );
	static const WideString kPlatformDialogControlIdentifierName( "PlatformDialogControlIdentifier" );


	// Attribute values
	static const WideString kDisableAttributeValue( "disable" );
	static const WideString kHideAttributeValue( "hide" );
	static const WideString kDisableDragDropAttributeValue( "disableDragDrop" );

	// Identifiers for Platform dialog controls
	// Open Document Dialog
	static const WideString kAllOpenDocDialogCustomControlsValue( "AllOpenDocDialogCustomControls" );
	static const WideString kOpenDocNormalRadioButtonValue( "OpenDocNormalRadioButton" );
	static const WideString kOpenDocOriginalRadioButtonValue( "OpenDocOriginalRadioButton" );
	static const WideString kOpenDocCopyRadioButtonValue( "OpenDocCopyRadioButton" );
		
	// Save Document Dialog
	static const WideString kAllSaveDocDialogCustomControlsValue( "AllSaveDocDialogCustomControls" );
	static const WideString kSaveDocPreviewImages( "SaveDocPreviewImages" );

	// Place Dialog
	static const WideString kAllPlaceFileDialogCustomControlsValue( "AllPlaceFileDialogCustomControls" );
	static const WideString kPlaceFileImportOptionsCheckboxValue( "PlaceFileImportOptionsCheckbox" );
	static const WideString kPlaceFileReplaceSelectedCheckboxValue( "PlaceFileReplaceSelectedCheckbox" );
	static const WideString kPlaceFileGenerateCaptionsCheckboxValue( "PlaceFileGenerateCaptionsCheckbox" );
	static const WideString kPlaceFileApplyGridFormatCheckboxValue( "PlaceFileApplyGridFormatCheckbox" );
	static const WideString kPlaceFilePreviewCheckboxValue( "PlaceFilePreviewCheckbox" );

	// Relink Dialog
	static const WideString kRelinkFileImportOptionsCheckboxValue( "RelinkFileImportOptionsCheckbox" );
	static const WideString kRelinkFileSearchForMissingCheckboxValue( "RelinkFileSearchForMissingOptionsCheckbox" );
	static const WideString kRelinkSkipButtonValue( "RelinkSkipButton" );
	static const WideString kRelinkFilePreviewCheckboxValue( "RelinkFilePreviewCheckbox" );

	// Relink to folder Dialog
	static const WideString kRelinkToFolderExtensionControls( "RelinkToFolderExtensionControls" );

	// Package dialog
	static const WideString kAllPackageDialogCustomControlsValue( "AllPackageDialogCustomControls" );
	static const WideString kPackageCopyFontsCheckboxValue( "PackageCopyFontsCheckbox" );
	static const WideString kPackageCopyGraphicsCheckboxValue( "PackageCopyGraphicsCheckbox" );
	static const WideString kPackageUpdateGraphicLinksCheckboxValue( "PackageUpdateGraphicLinksCheckbox" );
	static const WideString kPackageHyphenationExceptionsCheckboxValue( "PackageHyphenationExceptionsCheckbox" );
	static const WideString kPackageHiddenLayersCheckboxValue( "PackageHiddenLayersCheckbox" );
	static const WideString kPackageViewReportCheckboxValue( "PackageViewReportCheckbox" );
	static const WideString kPackageCreateIDMLCheckboxValue( "PackageCreateIDMLCheckbox" );
	static const WideString kPackageCreatePDFCheckboxValue( "PackageCreatePDFCheckbox" );
	static const WideString kPackagePDFPresetComboValue( "PackagePDFPresetCombo" );
	static const WideString kPackageInstructionsButtonCheckboxValue( "PackageInstructionsButtonCheckbox" );

	// Import XML dialog
	static const WideString kAllImportXMLDialogCustomControlsValue( "AllImportXMLDialogCustomControls" );
	static const WideString kImportXMLShowOptionsCheckboxValue( "ImportXMLShowOptionsCheckbox" );
	static const WideString kImportXMLImportIntoSelectedItemCheckboxValue( "ImportXMLImportIntoSelectedItemCheckbox" );
	static const WideString kImportXMLMergeContentRadioButtonValue( "ImportXMLMergeContentRadioButton" );
	static const WideString kImportXMLAppendContentRadioButtonValue( "ImportXMLAppendContentRadioButton" );

	// Save XML Tags dialog
	static const WideString kAllSaveTagsDialogCustomControlsValue( "AllSaveTagsDialogCustomControls" );
	static const WideString kSaveTagsEncodingValue( "SaveTagsEncoding" );

	// Suppress "Use Adobe Dialog" button
	// These buttons are found on Platform Open and Save File, and Choose Directory, dialogs.  
	//Suppressing the button will cause  the platform dialog to open.  
	//There is no way to suppress the button and show the Adobe dialog.
	static const WideString kAdobeFileDialogOpenDialogButtonValue( "AdobeFileDialogOpenDialogButton" );
	static const WideString kAdobeFileDialogSaveDialogButtonValue( "AdobeFileDialogSaveDialogButton" );
	static const WideString kAdobeFileDialogChooseFolderDialogButton( "AdobeFileDialogChooseFolderButton" );
	
}

#endif // __SuppressedUIXMLDefs__

