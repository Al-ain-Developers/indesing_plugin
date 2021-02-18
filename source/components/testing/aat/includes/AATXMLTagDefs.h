//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/AATXMLTagDefs.h $
//  
//  Owner: Gregor Kaplan
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __AATXMLTagDefs__
	#define __AATXMLTagDefs__

#include "QAFileXMLTagDefs.h" // other tokens live here, now.

#pragma export on

extern const char	kPostingKey;
extern const char	kReceivingKey;

extern const char* kSessionListToken;
extern const char* kSessionToken;
extern const char* kSequenceToken;
extern const char* kObjectFinderToken;
extern const char* kAATActionListToken;
extern const char* kAATModelToken;
extern const char* kAATActionToken;
extern const char* kTestFileToken;
extern const char* kAATFileFormatToken;
extern const char* kFileFormatToken;
extern const char* kDialogDescriptionToken;
extern const char* kDialogDescriptionListToken;
extern const char* kPanelDescriptionToken;
extern const char* kWidgetEntryToken;
extern const char* kActionListFileToken;
extern const char* kFileListFileToken;
extern const char* kParamListFileToken;
extern const char* kClassListFileToken;
extern const char* kValueMapFileToken;
extern const char* kUIXformFileToken;
extern const char* kSourceTreeFileToken;
extern const char* kReadWriteContainerToken;
extern const char* kAlertWatcherToken;
extern const char* kPackageInfoToken;
extern const char* kUILocationToken;
extern const char* kSourceInfoToken;
extern const char* kModelSourceInfoToken;
extern const char* kKeyedConditionsListToken;
extern const char* kSynonymsListToken;



//Xform Tokens
extern const char* kMovedWidgetToken;
extern const char* kReplaceActionToken;
extern const char* kReplaceToken;
extern const char* kWidgetIDChangeToken;
extern const char* kResponseToken;
extern const char* kRowColChangeToken;
extern const char* kWidgetXformToken;
extern const char* kParentIDChangeToken;
extern const char* kParentChainChangeToken;
extern const char* kParentXformToken;
extern const char* kIDToken;
extern const char* kInsertActionToken;
extern const char* kLocationPriorToken;
extern const char* kLocationPostToken;
extern const char* kLocationToken;
extern const char* kKeepToken;
extern const char* kKeyTokenToken;
extern const char* kKeyValueToken;
extern const char* kOldRowToken;
extern const char* kOldIDToken;
extern const char* kOldParentIDToken;
extern const char* kOldColumnToken;
extern const char* kOldWidgetIDToken;
extern const char* kOldInfoToken;
extern const char* kOldTypeToken;
extern const char* kOldTypeCodeToken;
extern const char* kOldValueToken;
extern const char* kOldValueEntryToken;
extern const char* kNewIDToken;
extern const char* kNewParentIDToken;
extern const char* kNewWidgetIDToken;
extern const char* kNewInfoToken;
extern const char* kNewTypeToken;
extern const char* kNewTypeCodeToken;
extern const char* kNewValueToken;
extern const char* kNewValueEntryToken;
extern const char* kSourcedToken;
extern const char* kXformBuildToken;
extern const char* kXformToken;


//Session Information
extern const char* kEngNameToken;
extern const char* kQANameToken;
extern const char* kEngEmailToken;
extern const char* kQAEmailToken;
extern const char* kKeywordToken;
extern const char* kBugNumberToken;

extern const char* kFuncAreaToken;
extern const char* kProductAreaToken;
extern const char* kDateToken;
extern const char* kCloseDateToken;
extern const char* kClosedBuildNumberToken;

extern const char* kReqLocaleToken;
extern const char* kReqFeatureSetToken;
extern const char* kReqProductToken;
extern const char* kReqFontsToken;
extern const char* kReqOSToken;
extern const char* kReqPlatformToken;
extern const char* kReqFilesToken;

//VAATData Params
extern const char* kParamExtensionToken;
extern const char* kParamListToken;
extern const char* kAATDataToken;
extern const char* kValueToken;
extern const char* kRequiredToken;
extern const char* kTagToken;
extern const char* kParentTagToken;
extern const char* kParentIDToken;
extern const char* kTypeToken;

extern const char* kIterationKeyToken;
extern const char* kCurrentIterationToken;
extern const char* kVariableToken;

extern const char* kDeterminateParamToken;

extern const char* kUIParamToken;
extern const char* kCodeToken;
extern const char* kValueListToken;
extern const char* kValueEntryToken;
extern const char* kVersionToken;
extern const char* kAATActionVersionToken;

extern const char* kCommonGroupToken;
extern const char* kSettingsGroupToken;
extern const char* kInformationGroupToken;
extern const char* kRequirementsGroupToken;

extern const char* kNoneTokenValue;

// Common/generic tokens
extern const char* kAdvancedToken;
extern const char* kAlertToken;
extern const char* kAssignmentNameToken;
extern const char* kAutoToken;
extern const char* kAnyToken;
extern const char* kBreakToken;
extern const char* kShowInSourceTreeToken;
extern const char* kFormatToken;
extern const char* kAbortOnErrorToken;
extern const char* kApplicationToken;
extern const char* kBuildNumberToken;
extern const char* kBoundsToken;
extern const char* kCancelToken;
extern const char* kClassListToken;
extern const char* kCharacterStyleGroupToken;
extern const char* kCheckEnabledToken;
extern const char* kCheckOutToken;
extern const char* kClearToken;
extern const char* kColumnGutterToken;
extern const char* kConflictFlagToken;
extern const char* kContainsToken;
extern const char* kCommitToken;
extern const char* kCommitIMEInputToken;
extern const char* kContextToken;
extern const char* kCountToken;
extern const char* kCommentsToken;
extern const char* kCommentOutToken;
extern const char* kCompNameToken;
extern const char* kConversionEngineToken;
extern const char* kConversionIntentToken;
extern const char* kDataChangeToken;
extern const char* kDebugReleaseToken;
extern const char* kDataTypeToken;
extern const char* kDefaultToken;
extern const char* kDirectionToken;
extern const char* kDOMVersionToken;
extern const char* kEditableToken;
extern const char* kEncodingToken;
extern const char* kEndToken;
extern const char* kEqualsToken;
extern const char* kFileExtensionToken;
extern const char* kFailureToken;
extern const char* kLogicFailureToken;
extern const char* kLogicToken;
extern const char* kFeatureSetToken;
extern const char* kFlavorToken;
extern const char* kFileToken;
extern const char* kFileRelativeToToken;
extern const char* kFolderToken;
extern const char* kFontFaceToken;
extern const char* kFontFamilyToken;
extern const char* kGutterToken;
extern const char* kHeightToken;
extern const char* kHideToken;
extern const char* kInCopyToken;
extern const char* kInDesignToken;
extern const char* kIndexToken;
extern const char* kInitedToken;
extern const char* kItemToken;
extern const char* kInstanceNameToken;
extern const char* kInVariableToken;
extern const char* kIterationToken;
extern const char* kItemUIDToken;  //Obsolete!  Never use this!
extern const char* kJapaneseToken;
extern const char* kLocaleToken;
extern const char* kLockToken;
extern const char* kLockGuidesToken;
extern const char* kLoopKeyToken;
extern const char* kLoopTypeToken;
extern const char* kLengthToken;
extern const char* kListKindToken;
extern const char* kMacintoshToken;
extern const char* kMasterToken;
extern const char* kMissingToken;
extern const char* kOperatingSystemToken;
extern const char* kOptionsToken;
extern const char* kOutputToken;
extern const char* kOutVariableToken;
extern const char* kParagraphStyleGroupToken;
extern const char* kPasteboardToken;
extern const char* kPastingToken;
extern const char* kPathToken;
extern const char* kPlatformToken;
extern const char* kPrefixToken;
extern const char* kPreserveFormattingToken;
extern const char* kPriorityToken;
extern const char* kProductToken;
extern const char* kProductAppToken;
extern const char* kProdVersionToken;
extern const char* kPreserveRandSeedToken;
extern const char* kRandSeedToken;
extern const char* kRedrawToken;
extern const char* kRemoveToken;
extern const char* kReorderToken;
extern const char* kResultToken;
extern const char* kRomanToken;
extern const char* kRowGutterToken;
extern const char* kErrorNotExpectedToken;
extern const char* kEvaluationToken;
extern const char* kExcludeToken;
extern const char* kExpectedToken;
extern const char* kExpected2Token;
extern const char* kExpected3Token;
extern const char* kErrorMessageToken;
extern const char* kExpectErrorToken;
extern const char* kExportOnErrToken;
extern const char* kScarfActionsToken;
extern const char* kScarfDataToken;
extern const char* kSequenceKindToken;
extern const char* kSettingsToken;
extern const char* kSizeToken;
extern const char* kShowToken;
extern const char* kSnapshotRepsToken;
extern const char* kSourceNameToken;
extern const char* kStartToken;
extern const char* kStoryToken;
extern const char* kStyleToken;
extern const char* kStyleNameToken;
extern const char* kSubDataToken;
extern const char* kSubjectToken;
extern const char* kSubjectParamToken;
extern const char* kSuccessToken;
extern const char* kSuppressToken;
extern const char* kAATActionDescriptionToken;
extern const char* kTextToken;
extern const char* kTimesToken;
extern const char* kToolTipToken;
extern const char* kTreeLocationToken;
extern const char* kTruncateToken;
extern const char* kTypeNameToken;
extern const char* kTypeCodeToken;
extern const char* kUnitsToken;
extern const char* kUIDToken;
extern const char* kValidationLevelToken;
extern const char* kValueMapToken;
extern const char* kVerificationToken;
extern const char* kVersionNumberToken;
extern const char* kWhereToken;
extern const char* kWidthToken;
extern const char* kWindowToken;
extern const char* kWindowsToken;
extern const char* kWorkspaceToken;
extern const char* kXMPToken;
extern const char* kXMLToken;
extern const char* kYieldToken;
extern const char* kZoomLevelToken;
extern const char* kInclusiveToken;
extern const char* kViewModeToken;
extern const char* kImageFormatToken;
extern const char* kImageQualityToken;
extern const char* kColorSpaceToken;
extern const char* kResolutionToken;
extern const char* kDisplayToken;
extern const char* kBleedToken;
extern const char* kGreekTextToken;
extern const char* kAntiAliasingToken;
extern const char* kExcludeOpfToken;
extern const char* kExcludeNcxToken;
extern const char* kExcludeCoverToken;
extern const char* kExcludeTocToken;

//UI Tokens
extern const char* kClickToken;
extern const char* kClickBeforeToken;
extern const char* kEnabledToken;
extern const char* kDisabledToken;
extern const char* kDialogSourceInfoToken;
extern const char* kIsDialogToken;
extern const char* kDialogPanelToken;
extern const char* kLabelToken;
extern const char* kWidgetCodeToken;
extern const char* kWidgetIDToken;
extern const char* kAssocWidgetIDToken;
extern const char* kWidgetWindowNameToken;
extern const char* kActionIDToken;
extern const char* kMinValueToken;
extern const char* kMaxValueToken;
extern const char* kInvalidCodeToken;
extern const char* kRealEditBoxToken;
extern const char* kInt32EditBoxToken;
extern const char* kTextEditBoxToken;
extern const char* kGalleyFitBarToken;
extern const char* kMultiLineTextEditBoxToken;
extern const char* kButtonToken;
extern const char* kRadioClusterToken;
extern const char* kRadioButtonToken;
extern const char* kCheckBoxToken;
extern const char* kFileComboToken;
extern const char* kGradientSliderToken;
extern const char* kComboBoxToken;
extern const char* kDropDownListToken;
extern const char* kColorListDropDownToken;
extern const char* kMediaDDListToken;
extern const char* kOwnerDrawDropDownToken;
extern const char* kPathEndStrokeDropDownToken;
extern const char* kCornerTypeDropDownToken;
extern const char* kQuickApplyListToken;
extern const char* kStrokeTypeDropDownToken;
extern const char* kStrokeListBoxToken;
extern const char* kRenderListBoxToken;
extern const char* kTextListBoxToken;
extern const char* kFormFieldTabListBoxToken;
extern const char* kListBoxToken;
extern const char* kListBoxContentsToken;
extern const char* kListBoxEntryToken;
extern const char* kTreeViewListBoxToken;
extern const char* kTreeViewWidgetInfoToken;
extern const char* kTreeViewBranchToken;
extern const char* kTreeViewLeafToken;
extern const char* kCheckBoxTreeViewToken;
extern const char* kMeasurementToken;
extern const char* kNudgeControlToken;
extern const char* kNudgeUpToken;
extern const char* kNudgeDownToken;
extern const char* kSliderToken;
extern const char* kStaticTextToken;
extern const char* kStringIntPairDDListToken;
extern const char* kStringUIDPairDDListToken;
extern const char* kStrokeFillProxyToken;
extern const char* kPluginMgrListBoxToken;
extern const char* kClickableTextToken;
extern const char* kStringToken;
extern const char* kGroupPanelWidgetToken;
extern const char* kSelectableDialogToken;
extern const char* kFittedTextToken;
extern const char* kIconWidgetToken;
extern const char* kUIColorSwatchWidgetToken;
extern const char* kSaveAsDialogToken;
extern const char* kChooseFileDialogToken;
extern const char* kChooseDirDialogToken;
extern const char* kUIColorListDropDownToken;
extern const char* kTreeRepresentationToken;
extern const char* kSaveAsDependentFileToken;
extern const char* kTreeEntryToken;
extern const char* kTreeDataEntriesToken;
extern const char* kTreeActionsToken;
extern const char* kPointProxyToken;
extern const char* kGlyphGridPanelToken;
extern const char* kSpreadWidgetToken;
extern const char* kLibraryGridToken;
extern const char* kLibraryListToken;

extern const char* kMenuProductToken;
extern const char* kMenuCommandToken;
extern const char* kPaletteMenuCommandToken;

extern const char* kWidgetValueToken;

extern const char* kIndeterminateUIToken;

//Gradient Controls
extern const char* kThumbsToken;
extern const char* kMidPointThumbToken;
extern const char* kColorStopThumbToken;



//Set/Get
extern const char* kGetSetToken;
extern const char* kSetToken;
extern const char* kGetToken;

// Document specific tokens
extern const char* kCustomPageSizeToken;
extern const char* kFacingPagesToken;
extern const char* kIsTemplateToken;
extern const char* kMasterTextFrameToken;
extern const char* kOpenTypeToken;
extern const char* kPageBindingToken;
extern const char* kReadOnlyToken;
extern const char* kStockPageSizeToken;
extern const char* kWideOrientationToken;

// Hyperlink tokens
extern const char* kHyperlinksToken;
extern const char* kHyperlinkDestinationTypeToken;
extern const char* kDestinationToken;
extern const char* kURLToken;
extern const char* kHyperlinkNameToken;
extern const char* kVisibleToken;
extern const char* kHilightToken;
extern const char* kOutlineStyleToken;

// Operations tokens
extern const char* kParam1Token;
extern const char* kParam2Token;
extern const char* kOperatorToken;
extern const char* kX1Token;
extern const char* kY1Token;
extern const char* kX2Token;
extern const char* kY2Token;
extern const char* kXOffsetToken;
extern const char* kYOffsetToken;
extern const char* kRectToken;
extern const char* kPointToken;

// Print and export tokens
extern const char* kPrintPresetToken;
extern const char* kQualityToken;
extern const char* kBitmapSamplingToken;
extern const char* kRenderingStyleToken;
extern const char* kExportingSelectionToken;
extern const char* kExportingFullSpreadToken;
extern const char* kLaunchAcrobatToken;
extern const char* kPageRangeToken;
extern const char* kPageRangeFormatToken;
extern const char* kAcrobatCompatibilityToken;
extern const char* kStandardToken;
extern const char* kThumbnailsToken;
extern const char* kOptimizeToken;
extern const char* kLayersToken;
extern const char* kBookmarksToken;
extern const char* kObjectsToken;
extern const char* kGuidesToken;
extern const char* kEBookToken;
extern const char* kInteractiveToken;
extern const char* kMultimediaToken;
extern const char* kColorImageSamplingToken;
extern const char* kColorImageSamplingXResToken;
extern const char* kColorImageSamplingYResToken;
extern const char* kColorImageCompressionToken;
extern const char* kColorImageTileSize;
extern const char* kColorImageQualityToken;
extern const char* kGrayscaleImageSamplingToken;
extern const char* kGrayscaleImageSamplingXResToken;
extern const char* kGrayscaleImageSamplingYResToken;
extern const char* kGrayscaleImageCompressionToken;
extern const char* kGrayscaleImageTileSize;
extern const char* kGrayscaleImageQualityToken;
extern const char* kMonochromeImageSamplingToken;
extern const char* kMonochromeImageSamplingXResToken;
extern const char* kMonochromeImageSamplingYResToken;
extern const char* kMonochromeImageCompressionToken;
extern const char* kCompressTextLineToken;
extern const char* kCropToFramesToken;

// Import codes
extern const char* kShowOptionsToken;
extern const char* kRetainFormatToken;
extern const char* kConvertQuotesToken;
extern const char* kReplaceSelectionToken;
extern const char* kApplyCJKGridToken;

//Transform and PI codes
extern const char* kAbsoluteToken;
extern const char* kCenterPointToken;
extern const char* kPasteboardRelativeToken;
extern const char* kRotationToken;
extern const char* kSkewToken;
extern const char* kTransformChildrenToken;
extern const char* kUsePathToken;
extern const char* kXScaleToken;
extern const char* kYScaleToken;
extern const char* kInsetToken;
extern const char* kNumSidesToken;

//Experimental - These might need to be altered
extern const char* kIsJapaneseToken;
extern const char* kIsStrokeToken;
extern const char* kTextStartToken;
extern const char* kTextEndToken;
extern const char* kTextLengthToken;
extern const char* kActionDescriptionToken;
extern const char* kErrorTypeToken;
extern const char* kLogOnlyToken;
extern const char* kFontToken;
extern const char* kNumberingStyleToken;

extern const char* kPageToken;
extern const char* kSpreadToken;
// Selection tokens
extern const char* kShiftSelectToken;

//Extra story tags
extern const char* kAfterFrameToken;
extern const char* kFrameNameToken;
extern const char* kLinkToFrameToken;
extern const char* kLinkFromFrameToken;

extern const char* kLibraryNameToken;
extern const char* kLibraryToken;
extern const char* kChangeCaseToken;

//Swatch tokens
extern const char*	kSwatchToken;
extern const char*	kSwatchNameToken;
extern const char*	kSwatchListToken;
extern const char*	kColorValOneToken;
extern const char*	kColorValTwoToken;
extern const char*	kColorValThreeToken;
extern const char*	kColorValFourToken;
extern const char*	kColorModelToken;
extern const char*	kIsSpotToken;
extern const char*	kValuesForNameToken;

//Typekit tokens
extern const char*	kValueForTypekitToken;

//Color tokens
extern const char* kCMYKToken;
extern const char* kCMYKPolicyToken;
extern const char* kRGBToken;
extern const char* kRGBPolicyToken;

//Table Tokens
extern const char*	kRowToken;
extern const char*	kCellToken;
extern const char*	kColumnToken;
extern const char*	kTopLeftToken;
extern const char*	kBottomRightToken;
extern const char*	kNumRowsToken;
extern const char*	kHeadersToken;
extern const char*	kFootersToken;

// App Tokens
extern const char*	kReplaceExistingListItemToken;
extern const char*	kDeleteNonImportedListItemToken;

//OSCommands Tokens
extern const char*	kWinCommandsToken;
extern const char*	kMacCommandsToken;

//InvokeIOTAATAction
extern const char*	kInvokeIOTAATParamToken;
extern const char*	kInvokeIOTAATEventToken;
extern const char*  kInvokeIOTAATFile;
extern const char*  kInvokeIOTAATWaitFile;
extern const char*  kInvokeYieldUntilEvent;

//UI Action Tokens
extern const char* kCharToken;
extern const char* kModifierToken;

//Validator tokens
extern const char*	kToleranceToken;
extern const char*	kCompareAllToken;
extern const char*	kCompareElementsToken;
extern const char*	kCompareCharactersToken;
extern const char*	kCompareCommentsToken;
extern const char*	kCompareXMLDeclToken;
extern const char*	kCompareXMLPIToken;

// Action Exclusion List Conditions
extern const char*	kUserEditableToken;
extern const char*	kConditionsToken;
extern const char*	kKeyToken;
extern const char*	kEntryToken;

//QAFile Tokens
#pragma mark QAFile Tags
extern const char* kSessionFileDirectoryToken;

#pragma mark Default Operator Names
extern const char* kGreaterThanEqToStr;
extern const char* kGreaterThanStr;
extern const char* kLessThanEqToStr;
extern const char* kLessThanStr;
extern const char* kNotEqualStr;
extern const char* kEqualStr;

#pragma mark Logic Types
extern const char* kIfStr;
extern const char* kElseIfStr;
extern const char* kElseStr;
extern const char* kWhileStr;
extern const char* kDoWhileStr;


#pragma mark Sequence Type Name Strings
//You cannot/should not change these without updating every existing
//reference to the old values.  You will also need to write in support to
//the 2.0-current version reader so that it can properly instantiate sequences.
//In other words, these are used as keys for constructing items in the factory.
extern const char*	kStdSeqListStr;
extern const char*	kIterativeLoopStr;
extern const char*	kFileLoopStr;
extern const char*	kObjectLoopStr;
extern const char*	kPermutationLoopStr;
extern const char*	kParameterLoopStr;
extern const char*	kLogicSeqStr;
extern const char*	kLogicClusterSeqStr;
extern const char*	kDoWhileSeqStr;
extern const char*	kAlertWatchSeqStr;


#pragma mark Default AAT Variable Names 
extern const char* kApp_PostingStr;
extern const char* kApp_ReceivingStr;
extern const char* kAssignment_PostingStr;
extern const char* kAssignment_ReceivingStr;
extern const char* kBook_PostingStr;
extern const char* kBook_ReceivingStr;
extern const char* kBookmark_PostingStr;
extern const char* kBookmark_ReceivingStr;
extern const char* kDoc_PostingStr;
extern const char* kDoc_ReceivingStr;
extern const char* kCharStyle_PostingStr;
extern const char* kCharStyle_ReceivingStr;
extern const char* kCharStyleGroup_PostingStr;
extern const char* kCharStyleGroup_ReceivingStr;
extern const char* kFrameGrid_PostingStr;
extern const char* kFrameGrid_ReceivingStr;
extern const char* kFormField_PostingStr;
extern const char* kFormField_ReceivingStr;
extern const char* kLayer_PostingStr;
extern const char* kLayer_ReceivingStr;
extern const char* kLibrary_PostingStr;
extern const char* kLibrary_ReceivingStr;
extern const char* kGuide_PostingStr;
extern const char* kGuide_ReceivingStr;
extern const char* kMaster_PostingStr;
extern const char* kMaster_ReceivingStr;
extern const char* kMovie_PostingStr;
extern const char* kMovie_ReceivingStr;
extern const char* kNote_PostingStr;
extern const char* kNote_ReceivingStr;
extern const char* kPageItem_PostingStr;
extern const char* kPageItem_ReceivingStr;
extern const char* kPage_PostingStr;
extern const char* kPage_ReceivingStr;
extern const char* kParaStyle_PostingStr;
extern const char* kParaStyle_ReceivingStr;
extern const char* kParaStyleGroup_PostingStr;
extern const char* kParaStyleGroup_ReceivingStr;
extern const char* kSound_PostingStr;
extern const char* kSound_ReceivingStr;
extern const char* kSpread_PostingStr;
extern const char* kSpread_ReceivingStr;
extern const char* kStory_PostingStr;
extern const char* kStory_ReceivingStr;
extern const char* kStructureElement_PostingStr;
extern const char* kStructureElement_ReceivingStr;
extern const char* kStyle_PostingStr;
extern const char* kStyle_ReceivingStr;
extern const char* kSwatch_PostingStr;
extern const char* kSwatch_ReceivingStr;
extern const char* kTable_PostingStr;
extern const char* kTable_ReceivingStr;
extern const char* kTableFrame_PostingStr;
extern const char* kTableFrame_ReceivingStr;
extern const char* kTextColumn_PostingStr;
extern const char* kTextColumn_ReceivingStr;
extern const char* kTextFrame_PostingStr;
extern const char* kTextFrame_ReceivingStr;
extern const char* kXMLTag_PostingStr;
extern const char* kXMLTag_ReceivingStr;
extern const char* kFile_PostingStr;
extern const char* kFile_ReceivingStr;
extern const char* kFolder_PostingStr;
extern const char* kFolder_ReceivingStr;

extern const char* kUnknownObj_PostingStr;
extern const char* kUnknownObj_ReceivingStr;

extern const char* kIndex_PostingStr;
extern const char* kIndex_ReceivingStr;
extern const char* kLength_PostingStr;
extern const char* kLength_ReceivingStr;
extern const char* kValue_PostingStr;
extern const char* kValue_ReceivingStr;
extern const char* kRect_PostingStr;
extern const char* kRect_ReceivingStr;
extern const char* kPoint_PostingStr;
extern const char* kPoint_ReceivingStr;
extern const char* kBoolean_PostingStr;
extern const char* kBoolean_ReceivingStr;
extern const char* kString_PostingStr;
extern const char* kString_ReceivingStr;
extern const char* kWidth_PostingStr;
extern const char* kWidth_ReceivingStr;
extern const char* kHeight_PostingStr;
extern const char* kHeight_ReceivingStr;

extern const char* kTopLeft_PostingStr;
extern const char* kTopLeft_ReceivingStr;
extern const char* kBottomRight_PostingStr;
extern const char* kBottomRight_ReceivingStr;
extern const char* kStart_PostingStr;
extern const char* kStart_ReceivingStr;
extern const char* kEnd_PostingStr;
extern const char* kEnd_ReceivingStr;

extern const char* kExpected_PostingStr;
extern const char* kExpected_ReceivingStr;

extern const char* kNumRows_PostingStr;
extern const char* kNumRows_ReceivingStr;
extern const char* kNumColumns_PostingStr;
extern const char* kNumColumns_ReceivingStr;
extern const char* kNumHeaders_PostingStr;
extern const char* kNumHeaders_ReceivingStr;
extern const char* kNumFooters_PostingStr;
extern const char* kNumFooters_ReceivingStr;

extern const char* kHyperlinkDest_PostingStr;
extern const char* kHyperlinkDest_ReceivingStr;
extern const char* kHyperlink_PostingStr;
extern const char* kHyperlink_ReceivingStr;

extern const char* kWindow_PostingStr;
extern const char* kWindow_ReceivingStr;
extern const char* kWorkspace_PostingStr;
extern const char* kWorkspace_ReceivingStr;

extern const char* kPrintPreset_PostingStr;
extern const char* kPrintPreset_ReceivingStr;

extern const char* kFont_PostingStr;
extern const char* kFont_ReceivingStr;

extern const char* kWidgetValue_PostingStr;
extern const char* kWidgetValue_ReceivingStr;

#pragma mark Std Prod/Target/Val Level Strings
extern const char* kSubjectStr;
extern const char* kProductStr;

extern const char* kExtensiveValidationStr;
extern const char* kStandardValidationStr;
extern const char* kMinimumValidationStr;

extern const char* kDefaultValueStr;
extern const char* kYesStr;
extern const char* kNoStr;

extern const char* kHideStr;
extern const char* kShowStr;

extern const char* kDontCheckStr;

extern const char* kMenuUnderlinedStr;
extern const char* kMenuDashedStr;
extern const char* kMenuUnselectedStr;
extern const char* kMenuSelectedStr;
extern const char* kDisabledStr;
extern const char* kEnabledStr;

extern const char* kSelectedToken;
extern const char* kUnSelectedToken;
extern const char* kMixedToken;

extern const char* kAppendActionStr;
extern const char* kRemoveActionStr;
extern const char* kSetActionStr;
extern const char* kInsertActionStr;
extern const char* kGetCharAtIndexActionStr;

extern const char* kGetCharIndexStr;
extern const char* kGetLastCharIndexStr;
extern const char* kContainsStr;
extern const char* kGetNumCharactersStr;

extern const char* kNotRelativeStr;

extern const char* kAutoCaptureStr;

extern const char*	kUpDownStr;
extern const char*	kUpStr;
extern const char*	kDownStr;

extern const char*	kSingleStr;
extern const char*	kDoubleStr;
extern const char*	kTripleStr;
extern const char*	kQuadrupleStr;
extern const char*	kQuintupleStr;

extern const char*	kShiftStr;
extern const char*	kCmdCntrlStr;
extern const char*	kMacControlStr;
extern const char*	kOptionAltStr;

extern const char*	kTopLeftStr;
extern const char*	kTopCenterStr;
extern const char*	kTopRightStr;
extern const char*	kLeftCenterStr;
extern const char*	kCenterStr;
extern const char*	kRightCenterStr;
extern const char*	kBottomLeftStr;
extern const char*	kBottomCenterStr;
extern const char*	kBottomRightStr;

extern const char*	kStrokeStr;
extern const char*	kFillStr;

extern const char*	kMakeStopThumbStr;
extern const char*	kGetNumMidpointThumbStr;
extern const char*	kGetNumStopThumbStr;
extern const char*	kClickNthMidpointThumbStr;
extern const char*	kClickNthStopThumbStr;
extern const char*	kDragNthMidpointThumbStr;
extern const char*	kDragNthStopThumbStr;
extern const char*	kDragOffNthStopThumbStr;

// File name defs
extern const char* kAATLogFileName;
extern const char* kAATXMLLogFileName;
extern const char* kAATErrorFileName;
extern const char* kAATErrorXMLLogFile;
extern const char* kAATErrorXMLLogKey;
extern const char* kAATErrorLogKey;


//Flavor Defs
extern const char* kAcquisitionFlavor;
extern const char* kCommandFlavor;
extern const char* kCustomFlavor;
extern const char* kInformationalFlavor;
extern const char* kOperationalFlavor;
extern const char* kUIFlavor;
extern const char* kUtilityFlavor;
extern const char* kValidationFlavor;

#pragma export off

#endif//__AATXMLTagDefs__




