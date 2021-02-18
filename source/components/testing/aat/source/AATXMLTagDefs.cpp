//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/source/AATXMLTagDefs.cpp $
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

#include "VCAATLibHeaders.h"
#include "AATArchStrDefs.h"
#include "AATXMLTagDefs.h"
#include "IQATestLog.h"

#ifdef __GNUC__
	#define EXTERNAL __attribute__ ((visibility("default")))
#else
	#define EXTERNAL extern
#endif

const char	kPostingKey('#');
const char	kReceivingKey('$');

EXTERNAL const char* kSessionListToken("SESSION_LIST");
EXTERNAL const char* kSessionToken("SESSION");
EXTERNAL const char* kSequenceToken("SEQUENCE");
EXTERNAL const char* kObjectFinderToken("OBJ_FINDER");
EXTERNAL const char* kAATActionListToken("TESTLETTE_LIST");
EXTERNAL const char* kAATModelToken("TESTLETTE_MODEL");
EXTERNAL const char* kAATActionToken("TESTLETTE");
EXTERNAL const char* kTestFileToken("TEST_FILE");
EXTERNAL const char* kAATFileFormatToken("TESTLETTE_FILE_FORMAT");
EXTERNAL const char* kFileFormatToken("FILE_FORMAT");
EXTERNAL const char* kDialogDescriptionToken("DIALOG_DESCRIPTION");
EXTERNAL const char* kDialogDescriptionListToken("DIALOG_DESCRIPTION_LIST");
EXTERNAL const char* kPanelDescriptionToken("PANEL_DESCRIPTION");
EXTERNAL const char* kWidgetEntryToken("WIDGET");
EXTERNAL const char* kActionListFileToken("ACTION_LIST_FILE");
EXTERNAL const char* kFileListFileToken("FILE_LIST");
EXTERNAL const char* kParamListFileToken("PARAM_LIST_FILE");
EXTERNAL const char* kClassListFileToken("CLASS_LIST_FILE");
EXTERNAL const char* kValueMapFileToken("VALUE_MAP_FILE");
EXTERNAL const char* kUIXformFileToken("DIALOG_TRANSFORMATION");
EXTERNAL const char* kSourceTreeFileToken("SOURCE_TREE_FILE");
EXTERNAL const char* kReadWriteContainerToken("READ_WRITE_CONTAINER");
EXTERNAL const char* kAlertWatcherToken("ALERT_WATCHER");
EXTERNAL const char* kPackageInfoToken("PACKAGE_INFO");
EXTERNAL const char* kSourceInfoToken("SOURCE_INFO");
EXTERNAL const char* kModelSourceInfoToken("MODEL_SOURCE_INFO");
EXTERNAL const char* kUILocationToken("UI_LOCATION");
EXTERNAL const char* kKeyedConditionsListToken("KEYED_CONDITIONS_LIST");
EXTERNAL const char* kSynonymsListToken("SYNONYMS_LIST");

//Xform Tokens
EXTERNAL const char* kMovedWidgetToken("MOVED_WIDGET");
EXTERNAL const char* kReplaceActionToken("REPLACE_ACTION");
EXTERNAL const char* kReplaceToken("REPLACE");
EXTERNAL const char* kWidgetIDChangeToken("ID_CHANGE");
EXTERNAL const char* kParentIDChangeToken("PARENT_ID_CHANGE");
EXTERNAL const char* kParentChainChangeToken("PARENT_CHAIN_CHANGE");
EXTERNAL const char* kResponseToken("RESPONSE");
EXTERNAL const char* kRowColChangeToken("ROW_COL_CHANGE");
EXTERNAL const char* kWidgetXformToken("WIDGET_XFORM");
EXTERNAL const char* kParentXformToken("PARENT_XFORM");
EXTERNAL const char* kIDToken("ID");
EXTERNAL const char* kInsertActionToken("INSERT_ACTION");
EXTERNAL const char* kKeepToken("KEEP");
EXTERNAL const char* kKeyTokenToken("KEY_TOKEN");
EXTERNAL const char* kKeyValueToken("KEY_VALUE");
EXTERNAL const char* kLocationPriorToken("LOC_PRIOR");
EXTERNAL const char* kLocationPostToken("LOC_POST");
EXTERNAL const char* kLocationToken("LOCATION");
EXTERNAL const char* kOldColumnToken("OLD_COLUMN");
EXTERNAL const char* kOldIDToken("OLD_ID");
EXTERNAL const char* kOldParentIDToken("OLD_PARENT_ID");
EXTERNAL const char* kOldRowToken("OLD_ROW");
EXTERNAL const char* kOldWidgetIDToken("OLD_WIDGET_ID");
EXTERNAL const char* kOldInfoToken("OLD_INFO");
EXTERNAL const char* kOldTypeToken("OLD_TYPE");
EXTERNAL const char* kOldTypeCodeToken("OLD_TYPE_CODE");
EXTERNAL const char* kOldValueToken("OLD_VALUE");
EXTERNAL const char* kOldValueEntryToken("OLD_VALUE_ENTRY");
EXTERNAL const char* kNewIDToken("NEW_ID");
EXTERNAL const char* kNewParentIDToken("NEW_PARENT_ID");
EXTERNAL const char* kNewWidgetIDToken("NEW_WIDGET_ID");
EXTERNAL const char* kNewInfoToken("NEW_INFO");
EXTERNAL const char* kNewTypeToken("NEW_TYPE");
EXTERNAL const char* kNewTypeCodeToken("NEW_TYPE_CODE");
EXTERNAL const char* kNewValueToken("NEW_VALUE");
EXTERNAL const char* kNewValueEntryToken("NEW_VALUE_ENTRY");
EXTERNAL const char* kSourcedToken("SOURCED");
EXTERNAL const char* kXformBuildToken("XFORM_BUILD");
EXTERNAL const char* kXformToken("XFORM");


//Session Information
EXTERNAL const char* kEngNameToken("ENG_NAME");
EXTERNAL const char* kQANameToken("QA_NAME");
EXTERNAL const char* kEngEmailToken("ENG_EMAIL");
EXTERNAL const char* kQAEmailToken("QA_EMAIL");
EXTERNAL const char* kKeywordToken("KEYWORDS");
EXTERNAL const char* kBugNumberToken("BUG_NUMBER");

EXTERNAL const char* kFuncAreaToken("FUNC_AREA");
EXTERNAL const char* kProductAreaToken("PROD_AREA");
EXTERNAL const char* kDateToken("DATE");
EXTERNAL const char* kCloseDateToken("CLOSE_DATE");
EXTERNAL const char* kClosedBuildNumberToken("CLOSE_BUILD");

EXTERNAL const char* kReqLocaleToken("REQ_LOCALE");
EXTERNAL const char* kReqFeatureSetToken("REQ_FS");
EXTERNAL const char* kReqProductToken("REQ_PROD");
EXTERNAL const char* kReqFontsToken("REQ_FONTS");
EXTERNAL const char* kReqOSToken("REQ_OS");
EXTERNAL const char* kReqPlatformToken("REQ_PLATFORM");
EXTERNAL const char* kReqFilesToken("REQ_FILES");

//VAATData Params
EXTERNAL const char* kParamExtensionToken("PARAM_EXTENSIONS");
EXTERNAL const char* kParamListToken("PARAMLIST");
EXTERNAL const char* kAATDataToken("T_DATA");
EXTERNAL const char* kValueToken("VALUE");
EXTERNAL const char* kRequiredToken("REQUIRED");
EXTERNAL const char* kTagToken("TAG");
EXTERNAL const char* kTypeToken("TYPE");
EXTERNAL const char* kParentTagToken("PARENT_TAG");
EXTERNAL const char* kParentIDToken("PARENT_ID");

EXTERNAL const char* kIterationKeyToken("ITERATION_KEY");
EXTERNAL const char* kVariableToken("VARIABLE");

EXTERNAL const char* kDeterminateParamToken("DETERMINATE_PARAM");

EXTERNAL const char* kUIParamToken("UI_PARAM");
EXTERNAL const char* kCodeToken("CODE");
EXTERNAL const char* kValueListToken("VALUE_LIST");
EXTERNAL const char* kValueEntryToken("VALUE_ENTRY");

EXTERNAL const char* kVersionToken("VERSION");
EXTERNAL const char* kAATActionVersionToken("T_VERSION");


EXTERNAL const char* kCommonGroupToken("COMMON_DATA_GROUP");
EXTERNAL const char* kSettingsGroupToken("SETTING_DATA_GROUP");
EXTERNAL const char* kInformationGroupToken("INFO_DATA_GROUP");
EXTERNAL const char* kRequirementsGroupToken("REQUIREMENTS_DATA_GROUP");

//None value
EXTERNAL const char* kNoneTokenValue("None");

// Common/generic tokens
EXTERNAL const char* kAdvancedToken("ADVANCED");
EXTERNAL const char* kAlertToken("ALERT");
EXTERNAL const char* kAssignmentNameToken("ASSIGNMENT_NAME");
EXTERNAL const char* kAutoToken("AUTO");
EXTERNAL const char* kAnyToken("Any");
EXTERNAL const char* kFormatToken("FORMAT");
EXTERNAL const char* kAbortOnErrorToken("ABORT_ON_ERROR");
EXTERNAL const char* kApplicationToken("APPLICATION");
EXTERNAL const char* kBoundsToken("BOUNDS");
EXTERNAL const char* kBreakToken("BREAK");
EXTERNAL const char* kBuildNumberToken("BUILD_NUMBER");
EXTERNAL const char* kCancelToken("CANCEL");
EXTERNAL const char* kCharacterStyleGroupToken("CHARACTER_STYLEGROUP");
EXTERNAL const char* kCheckOutToken("CHECK_OUT");
EXTERNAL const char* kClassListToken("CLASS_LIST");
EXTERNAL const char* kClearToken("CLEAR");
EXTERNAL const char* kColumnGutterToken("COLUMN_GUTTER");
EXTERNAL const char* kContainsToken("CONTAINS");
EXTERNAL const char* kCommitToken("COMMIT");
EXTERNAL const char* kCommitIMEInputToken("COMMIT_IME");
EXTERNAL const char* kConflictFlagToken("CONFLICT_FLAG");
EXTERNAL const char* kContextToken("CONTEXT");
EXTERNAL const char* kCountToken("COUNT");
EXTERNAL const char* kCurrentIterationToken("CUR_ITERATION");
EXTERNAL const char* kCommentsToken("COMMENTS");
EXTERNAL const char* kCommentOutToken("COMMENT_OUT");
EXTERNAL const char* kCompNameToken("COMPARE_NAME");
EXTERNAL const char* kConversionEngineToken("CONVERSION_ENGINE");
EXTERNAL const char* kConversionIntentToken("CONVERSION_INTENT");
EXTERNAL const char* kDataChangeToken("DATA_CHANGE");
EXTERNAL const char* kDataTypeToken("DATA_TYPE");
EXTERNAL const char* kDebugReleaseToken("DEBUG_RELEASE");
EXTERNAL const char* kDefaultToken("DEFAULT");
EXTERNAL const char* kDirectionToken("DIRECTION");
EXTERNAL const char* kDOMVersionToken("DOM_VERSION");
EXTERNAL const char* kEditableToken("EDITABLE");
EXTERNAL const char* kEncodingToken("ENCODING");
EXTERNAL const char* kEndToken("END");
EXTERNAL const char* kEqualsToken("EQUALS");
EXTERNAL const char* kErrorNotExpectedToken("ERROR_NOT_EXPECTED");
EXTERNAL const char* kEvaluationToken("EVALUATION");
EXTERNAL const char* kExcludeToken("EXCLUDE");
EXTERNAL const char* kExpectedToken("EXPECTED");
EXTERNAL const char* kExpected2Token("EXPECTED2");
EXTERNAL const char* kExpected3Token("EXPECTED3");
EXTERNAL const char* kErrorMessageToken("ERROR_MSG");
EXTERNAL const char* kExpectErrorToken("EXPECT_ERROR");
EXTERNAL const char* kExportOnErrToken("EXPORT_ON_ERR");
EXTERNAL const char* kFileExtensionToken("EXTENSION");
EXTERNAL const char* kFailureToken("FAILURE");
EXTERNAL const char* kItemToken("ITEM");
EXTERNAL const char* kLogicFailureToken("LOGIC_FAILURE");
EXTERNAL const char* kLogicToken("LOGIC");
EXTERNAL const char* kFeatureSetToken("FEATURE_SET");
EXTERNAL const char* kFileToken("FILE");
EXTERNAL const char* kFileRelativeToToken("FILE_RELATIVE_TO");
EXTERNAL const char* kFlavorToken("FLAVOR");
EXTERNAL const char* kFolderToken("FOLDER");
EXTERNAL const char* kFontFaceToken("FONT_FACE");
EXTERNAL const char* kFontFamilyToken("FONT_FAMILY");
EXTERNAL const char* kGutterToken("GUTTER");
EXTERNAL const char* kHeightToken("HEIGHT");
EXTERNAL const char* kHideToken("HIDE");
EXTERNAL const char* kInCopyToken("INCOPY");
EXTERNAL const char* kInDesignToken("INDESIGN");
EXTERNAL const char* kIndexToken("INDEX");
EXTERNAL const char* kInfoToken("INFO");
EXTERNAL const char* kInitedToken("INITED");
EXTERNAL const char* kInstanceNameToken("INST_NAME");
EXTERNAL const char* kInVariableToken("IN_VARS");
EXTERNAL const char* kIterationToken("ITERATIONS");
EXTERNAL const char* kItemUIDToken("ITEM_UID"); //Obsolete!  Never use this!
EXTERNAL const char* kJapaneseToken("JAPANESE");
EXTERNAL const char* kLocaleToken("LOCALE");
EXTERNAL const char* kLockToken("LOCK");
EXTERNAL const char* kLockGuidesToken("LOCK_GUIDES");
EXTERNAL const char* kLoopKeyToken("LOOP_KEY");
EXTERNAL const char* kLoopTypeToken("LOOP_TYPE");
EXTERNAL const char* kLengthToken("LENGTH");
EXTERNAL const char* kListKindToken("LIST_KIND");
EXTERNAL const char* kMacintoshToken("MACINTOSH");
EXTERNAL const char* kMasterToken("MASTER");
EXTERNAL const char* kMissingToken("MISSING");
EXTERNAL const char* kOperatingSystemToken("OS");
EXTERNAL const char* kOptionsToken("OPTIONS");
EXTERNAL const char* kOutputToken("OUTPUT");
EXTERNAL const char* kOutVariableToken("OUT_VARS");
EXTERNAL const char* kPlatformToken("PLATFORM");
EXTERNAL const char* kParagraphStyleGroupToken("PARAGRAPH_STYLEGROUP");
EXTERNAL const char* kPasteboardToken("PASTEBOARD");
EXTERNAL const char* kPastingToken("PASTING");
EXTERNAL const char* kPathToken("PATH");
EXTERNAL const char* kPrefixToken("PREFIX");
EXTERNAL const char* kPreserveFormattingToken("PRESERVE_FORMATTING");
EXTERNAL const char* kPriorityToken("PRIORITY");
EXTERNAL const char* kProductToken("PRODUCT");
EXTERNAL const char* kProdVersionToken("PRODUCT_VERS");
EXTERNAL const char* kProductAppToken("PRODUCT_APP");
EXTERNAL const char* kPreserveRandSeedToken("PRESERVE_RAND_SEED");
EXTERNAL const char* kRandSeedToken("RAND_SEED");
EXTERNAL const char* kRedrawToken("REDRAW");
EXTERNAL const char* kRemoveToken("REMOVE");
EXTERNAL const char* kReorderToken("REORDERING");
EXTERNAL const char* kResultToken("RESULT");
EXTERNAL const char* kRomanToken("ROMAN");
EXTERNAL const char* kRowGutterToken("ROW_GUTTER");
EXTERNAL const char* kScarfActionsToken("SCARF_ACTIONS");
EXTERNAL const char* kScarfDataToken("SCARF_DATA");
EXTERNAL const char* kSequenceKindToken("SEQ_KIND");
EXTERNAL const char* kSettingsToken("SETTINGS");
EXTERNAL const char* kSizeToken("SIZE");
EXTERNAL const char* kShowToken("SHOW");
EXTERNAL const char* kShowInSourceTreeToken("SHOW_IN_TREE");
EXTERNAL const char* kSnapshotRepsToken("SNAPSHOT_REPS");
EXTERNAL const char* kSourceNameToken("SOURCE_NAME");
EXTERNAL const char* kStartToken("START");
EXTERNAL const char* kStoryToken("STORY");
EXTERNAL const char* kStyleToken("STYLE");
EXTERNAL const char* kStyleNameToken("STYLENAME");
EXTERNAL const char* kSubDataToken("SUB_DATA");
EXTERNAL const char* kSubjectToken("SUBJECT");
EXTERNAL const char* kSubjectParamToken("SUBJECT_PARAM");
EXTERNAL const char* kSuccessToken("SUCCESS");
EXTERNAL const char* kSuppressToken("SUPPRESS");
EXTERNAL const char* kAATActionDescriptionToken("TESTLETTE_DESCRIPTION");
EXTERNAL const char* kTextToken("TEXT");
EXTERNAL const char* kTimesToken("TIMES");
EXTERNAL const char* kToolTipToken("TOOL_TIP");
EXTERNAL const char* kTreeLocationToken("TREE_LOC");
EXTERNAL const char* kTruncateToken("TRUNCATE");
EXTERNAL const char* kTypeNameToken("TYPE_NAME");
EXTERNAL const char* kTypeCodeToken("TYPE_CODE");
EXTERNAL const char* kUnitsToken("UNITS");
EXTERNAL const char* kUIDToken("UID_TOKEN");
EXTERNAL const char* kValidationLevelToken("VALIDATION_LEVEL");
EXTERNAL const char* kValueMapToken("VALUE_MAP");
EXTERNAL const char* kVerificationToken("VERIFICATION");
EXTERNAL const char* kVersionNumberToken("VERSION_NUMBER");
EXTERNAL const char* kWhereToken("WHERE");
EXTERNAL const char* kWidthToken("WIDTH");
EXTERNAL const char* kWindowToken("WINDOW");
EXTERNAL const char* kWindowsToken("WINDOWS");
EXTERNAL const char* kWorkspaceToken("WORKSPACE");
EXTERNAL const char* kXMPToken("XMP");
EXTERNAL const char* kXMLToken("XML");
EXTERNAL const char* kYieldToken("YIELD");
EXTERNAL const char* kZoomLevelToken("ZOOM_LEVEL");
EXTERNAL const char* kInclusiveToken("INCLUSIVE");
EXTERNAL const char* kViewModeToken("VIEW_MODE");
EXTERNAL const char* kImageFormatToken("IMAGE_FORMAT");
EXTERNAL const char* kImageQualityToken("IMAGE_QUALITY");
EXTERNAL const char* kColorSpaceToken("COLORSPACE");
EXTERNAL const char* kResolutionToken("RESOLUTION");
EXTERNAL const char* kDisplayToken("DISPLAY");
EXTERNAL const char* kBleedToken("BLEED");
EXTERNAL const char* kGreekTextToken("GREEK_TEXT");
EXTERNAL const char* kAntiAliasingToken("ANTI_ALIASING");
EXTERNAL const char* kExcludeOpfToken("EXCLUDE_OPF");
EXTERNAL const char* kExcludeNcxToken("EXCLUDE_NCX");
EXTERNAL const char* kExcludeCoverToken("EXCLUDE_COVER");
EXTERNAL const char* kExcludeTocToken("EXCLUDE_TOC");


//UI Tokens
EXTERNAL const char* kClickToken("CLICK");
EXTERNAL const char* kClickBeforeToken("CLICK_BEFORE");
EXTERNAL const char* kCheckEnabledToken("CHECK_ENABLE_STATE");
EXTERNAL const char* kEnabledToken("ENABLED");
EXTERNAL const char* kDisabledToken("DISABLED");
EXTERNAL const char* kDialogSourceInfoToken("DIALOG_SOURCE_INFO");
EXTERNAL const char* kIsDialogToken("IS_DIALOG");
EXTERNAL const char* kDialogPanelToken("DIALOG_PANEL");
EXTERNAL const char* kLabelToken("LABEL");
EXTERNAL const char* kWidgetCodeToken("WIDGET_CODE");
EXTERNAL const char* kWidgetIDToken("WIDGET_ID");
EXTERNAL const char* kAssocWidgetIDToken("ASSOC_WIDGET");
EXTERNAL const char* kWidgetWindowNameToken("WIDGET_WINDOW");
EXTERNAL const char* kActionIDToken("ACTION_ID");
EXTERNAL const char* kMinValueToken("MIN_VALUE");
EXTERNAL const char* kMaxValueToken("MAX_VALUE");
EXTERNAL const char* kMediaDDListToken("MEDIA_DROP_DOWN");
EXTERNAL const char* kInvalidCodeToken("INVALID_UI");
EXTERNAL const char* kQuickApplyListToken("QUICK_APPLY_LIST");
EXTERNAL const char* kRealEditBoxToken("REAL_EDIT_BOX");
EXTERNAL const char* kInt32EditBoxToken("INT32_EDIT_BOX");
EXTERNAL const char* kTextEditBoxToken("TEXT_EDIT_BOX");
EXTERNAL const char* kGalleyFitBarToken("GALLEY_FIT_BAR");
EXTERNAL const char* kMultiLineTextEditBoxToken("MULTI_TEXT_EDIT_BOX");
EXTERNAL const char* kButtonToken("BUTTON");
EXTERNAL const char* kRadioClusterToken("RADIO_CLUSTER");
EXTERNAL const char* kRadioButtonToken("RADIO_BUTTON");
EXTERNAL const char* kCheckBoxToken("CHECK_BOX");
EXTERNAL const char* kFileComboToken("FILE_COMBO");
EXTERNAL const char* kComboBoxToken("COMBO_BOX");
EXTERNAL const char* kDropDownListToken("DROP_DOWN_LIST");
EXTERNAL const char* kColorListDropDownToken("COLOR_LIST_DROP_DOWN");
EXTERNAL const char* kOwnerDrawDropDownToken("OWNER_DROP_DOWN");
EXTERNAL const char* kPathEndStrokeDropDownToken("PATH_END_STROKE_DROP_DOWN");
EXTERNAL const char* kCornerTypeDropDownToken("CORNER_TYPE_DROP_DOWN");
EXTERNAL const char* kStrokeTypeDropDownToken("STROKE_TYPE_DROP_DOWN");
EXTERNAL const char* kStrokeListBoxToken("STROKE_LIST_BOX");
EXTERNAL const char* kTextListBoxToken("TEXT_LIST");
EXTERNAL const char* kRenderListBoxToken("RENDER_LIST_BOX");
EXTERNAL const char* kFormFieldTabListBoxToken("FORMFIELD_TABORDER_LIST_BOX");
EXTERNAL const char* kListBoxToken("LIST_BOX");
EXTERNAL const char* kListBoxContentsToken("LIST_BOX_CONTENTS");
EXTERNAL const char* kListBoxEntryToken("LIST_BOX_ENTRY");
EXTERNAL const char* kTreeViewListBoxToken("TREE_VIEW");
EXTERNAL const char* kTreeViewWidgetInfoToken("TREE_VIEW_WIDGET_INFO");
EXTERNAL const char* kTreeViewBranchToken("TREE_BRANCH");
EXTERNAL const char* kTreeViewLeafToken("TREE_LEAF");
EXTERNAL const char* kCheckBoxTreeViewToken("CHECK_BOX_TREE_VIEW");
EXTERNAL const char* kMeasurementToken("MEASUREMENT");
EXTERNAL const char* kNudgeControlToken("NUDGE_CONTROL");
EXTERNAL const char* kNudgeUpToken("NUDGE_UP");
EXTERNAL const char* kGradientSliderToken("GRADIENT_SLIDER");
EXTERNAL const char* kNudgeDownToken("NUDGE_DOWN");
EXTERNAL const char* kSliderToken("SLIDER");
EXTERNAL const char* kStaticTextToken("STATIC_TEXT");
EXTERNAL const char* kStringIntPairDDListToken("STRING_INT32_DROP_DOWN");
EXTERNAL const char* kStringUIDPairDDListToken("STRING_UID_DROP_DOWN");
EXTERNAL const char* kStrokeFillProxyToken("STROKE_FILL_PROXY");
EXTERNAL const char* kPluginMgrListBoxToken("PLUGIN_MGR_LBOX");
EXTERNAL const char* kClickableTextToken("CLICKABLE_TEXT");
EXTERNAL const char* kStringToken("STRING");
EXTERNAL const char* kGroupPanelWidgetToken("GROUP_WIDGET");
EXTERNAL const char* kSelectableDialogToken("SELECTABLE_DIALOG_PANEL");
EXTERNAL const char* kFittedTextToken("FITTED_TEXT");
EXTERNAL const char* kIconWidgetToken("ICON_WIDGET");
EXTERNAL const char* kUIColorSwatchWidgetToken("UI_COLOR_SWATCH");
EXTERNAL const char* kSaveAsDialogToken("SAVE_AS_DIALOG");
EXTERNAL const char* kChooseFileDialogToken("CHOOSE_FILE_DIALOG");
EXTERNAL const char* kChooseDirDialogToken("CHOOSE_DIR_DIALOG");
EXTERNAL const char* kUIColorListDropDownToken("UI_COLOR_LIST");
EXTERNAL const char* kTreeRepresentationToken("TREE_REPRESENTATION");
EXTERNAL const char* kSaveAsDependentFileToken("SAVE_AS_DEPENDENT_FILE");
EXTERNAL const char* kTreeEntryToken("TREE_ENTRY");
EXTERNAL const char* kTreeDataEntriesToken("TREE_DATA_ENTRIES");
EXTERNAL const char* kTreeActionsToken("TREE_ACTIONS");
EXTERNAL const char* kPointProxyToken("POINT_PROXY");
EXTERNAL const char* kGlyphGridPanelToken("GLYPH_GRID_PANEL");
EXTERNAL const char* kSpreadWidgetToken("SPREAD_WIDGET");
EXTERNAL const char* kLibraryGridToken("LIBRARY_GRID");
EXTERNAL const char* kLibraryListToken("LIBRARY_LIST");

EXTERNAL const char* kMenuProductToken("MENU_PRODUCT_AREA");
EXTERNAL const char* kMenuCommandToken("MENU_COMMAND");
EXTERNAL const char* kPaletteMenuCommandToken("PAL_MENU_COMMAND");

EXTERNAL const char* kWidgetValueToken("WIDGET_VALUE");

EXTERNAL const char* kIndeterminateUIToken("INDETERMINATE_UI");

//Gradient Controls
EXTERNAL const char* kThumbsToken("THUMBS");
EXTERNAL const char* kMidPointThumbToken("MID_THUMB");
EXTERNAL const char* kColorStopThumbToken("COLOR_STOP_THUMB");

//Set/Get
EXTERNAL const char* kGetSetToken("SET_GET");
//If you change these, make sure and update the Strings.fr - GET translates to Downloading
EXTERNAL const char* kSetToken(kSetStrKey);
EXTERNAL const char* kGetToken(kGetStrKey);


// Document specific tokens
EXTERNAL const char* kCustomPageSizeToken("CUSTOM_PAGE_SIZE");
EXTERNAL const char* kFacingPagesToken("FACING_PAGES");
EXTERNAL const char* kIsTemplateToken("IS_TEMPLATE");
EXTERNAL const char* kMasterTextFrameToken("MASTER_TEXT_FRAME");
EXTERNAL const char* kOpenTypeToken("OPEN_TYPE");
EXTERNAL const char* kPageBindingToken("PAGE_BINDING");
EXTERNAL const char* kReadOnlyToken("READ_ONLY");
EXTERNAL const char* kStockPageSizeToken("STOCK_PAGE_SIZE");
EXTERNAL const char* kWideOrientationToken("WIDE_ORIENTATION");

// Hyperlink tokens
EXTERNAL const char* kHyperlinksToken("HYPERLINKS");
EXTERNAL const char* kHyperlinkDestinationTypeToken("HYPERLINK_DESTINATION_TYPE");
EXTERNAL const char* kDestinationToken("DESTINATION");
EXTERNAL const char* kURLToken("URL");
EXTERNAL const char* kHyperlinkNameToken("HYPERLINK_NAME");
EXTERNAL const char* kVisibleToken("VISIBLE");
EXTERNAL const char* kHilightToken("HILIGHT");
EXTERNAL const char* kOutlineStyleToken("OUTLINE_STYLE");

// Operations tokens
EXTERNAL const char* kParam1Token("PARAM_1");
EXTERNAL const char* kParam2Token("PARAM_2");
EXTERNAL const char* kOperatorToken("OPERATOR");
EXTERNAL const char* kX1Token("X_1");
EXTERNAL const char* kY1Token("Y_1");
EXTERNAL const char* kX2Token("X_2");
EXTERNAL const char* kY2Token("Y_2");
EXTERNAL const char* kXOffsetToken("X_OFFSET");
EXTERNAL const char* kYOffsetToken("Y_OFFSET");
EXTERNAL const char* kRectToken("RECT");
EXTERNAL const char* kPointToken("POINT");

// Print and Export tokens
EXTERNAL const char* kPrintPresetToken("PRINT_PRESET");
EXTERNAL const char* kQualityToken("QUALITY");
EXTERNAL const char* kBitmapSamplingToken("BITMAP_SAMPLING");
EXTERNAL const char* kRenderingStyleToken("RENDERING_STYLE");
EXTERNAL const char* kExportingSelectionToken("EXPORTING_SELECTION");
EXTERNAL const char* kExportingFullSpreadToken("EXPORTING_FULL_SPREAD");
EXTERNAL const char* kLaunchAcrobatToken("LAUNCH_ACROBAT");
EXTERNAL const char* kPageRangeToken("PAGE_RANGE");
EXTERNAL const char* kPageRangeFormatToken("PAGE_RANGE_FORMAT");
EXTERNAL const char* kAcrobatCompatibilityToken("ACROBAT_COMPATIBILITY");
EXTERNAL const char* kStandardToken("STANDARD");
EXTERNAL const char* kThumbnailsToken("THUMBNAILS");
EXTERNAL const char* kOptimizeToken("OPTIMIZE");
EXTERNAL const char* kLayersToken("LAYERS");
EXTERNAL const char* kBookmarksToken("BOOKMARKS");
EXTERNAL const char* kObjectsToken("OBJECTS");
EXTERNAL const char* kGuidesToken("GUIDES");
EXTERNAL const char* kEBookToken("EBOOK");
EXTERNAL const char* kInteractiveToken("INTERACTIVE");
EXTERNAL const char* kMultimediaToken("MULTIMEDIA");
EXTERNAL const char* kColorImageSamplingToken("COLOR_IMAGE_SAMPLING");
EXTERNAL const char* kColorImageSamplingXResToken("COLOR_IMAGE_X_RES");
EXTERNAL const char* kColorImageSamplingYResToken("COLOR_IMAGE_Y_RES");
EXTERNAL const char* kColorImageCompressionToken("COLOR_IMAGE_COMPRESSION");
EXTERNAL const char* kColorImageTileSize("COLOR_IMAGE_TILE_SIZE");
EXTERNAL const char* kColorImageQualityToken("COLOR_IMAGE_IMAGE_QUALITY");
EXTERNAL const char* kGrayscaleImageSamplingToken("GRAYSCALE_IMAGE_SAMPLING");
EXTERNAL const char* kGrayscaleImageSamplingXResToken("GRAYSCALE_IMAGE_X_RES");
EXTERNAL const char* kGrayscaleImageSamplingYResToken("GRAYSCALE_IMAGE_Y_RES");
EXTERNAL const char* kGrayscaleImageCompressionToken("GRAYSCALE_IMAGE_COMPRESSION");
EXTERNAL const char* kGrayscaleImageTileSize("GRAYSCALE_IMAGE_TILE_SIZE");
EXTERNAL const char* kGrayscaleImageQualityToken("GRAYSCALE_IMAGE_IMAGE_QUALITY");
EXTERNAL const char* kMonochromeImageSamplingToken("MONOCHROME_IMAGE_SAMPLING");
EXTERNAL const char* kMonochromeImageSamplingXResToken("MONOCHROME_IMAGE_X_RES");
EXTERNAL const char* kMonochromeImageSamplingYResToken("MONOCHROME_IMAGE_Y_RES");
EXTERNAL const char* kMonochromeImageCompressionToken("MONOCHROME_IMAGE_COMPRESSION");
EXTERNAL const char* kCompressTextLineToken("COMPRESS_TEXT_LINE_ART");
EXTERNAL const char* kCropToFramesToken("CROP_TO_FRAMES");

// Import codes
EXTERNAL const char* kShowOptionsToken("SHOW_OPTIONS");
EXTERNAL const char* kRetainFormatToken("RETAIN_FORMAT");
EXTERNAL const char* kConvertQuotesToken("CONVERT_QUOTES");
EXTERNAL const char* kReplaceSelectionToken("REPLACE_SELECTION");
EXTERNAL const char* kApplyCJKGridToken("APPLY_CJK_GRID");

//Transform and PI codes
EXTERNAL const char* kAbsoluteToken("ABSOLUTE");
EXTERNAL const char* kCenterPointToken("CENTER_PT");
EXTERNAL const char* kPasteboardRelativeToken("PASTEBOARD_RELATIVE");
EXTERNAL const char* kRotationToken("ROTATION");
EXTERNAL const char* kSkewToken("SKEW");
EXTERNAL const char* kTransformChildrenToken("TRANSFORM_CHILDREN");
EXTERNAL const char* kUsePathToken("USE_PATH");
EXTERNAL const char* kXScaleToken("X_SCALE");
EXTERNAL const char* kYScaleToken("Y_SCALE");
EXTERNAL const char* kInsetToken("INSET");
EXTERNAL const char* kNumSidesToken("NUM_SIDES");

//Experimental - These might need to be altered
EXTERNAL const char* kIsJapaneseToken("IS_JAPANESE");
EXTERNAL const char* kIsStrokeToken("IS_STROKE");
EXTERNAL const char* kTextStartToken("TEXT_START");
EXTERNAL const char* kTextEndToken("TEXT_END");
EXTERNAL const char* kTextLengthToken("TEXT_LENGTH");
EXTERNAL const char* kActionDescriptionToken("DESCRIPTION");
EXTERNAL const char* kErrorTypeToken("ERROR_TYPE");
EXTERNAL const char* kLogOnlyToken("LOG_ONLY");
EXTERNAL const char* kFontToken("FONT");
EXTERNAL const char* kNumberingStyleToken("NUMBERING_STYLE");

EXTERNAL const char* kPageToken("PAGE");
EXTERNAL const char* kSpreadToken("SPREAD");
// Selection tokens
EXTERNAL const char* kShiftSelectToken("SHIFT_SELECT");

//Extra story tags
EXTERNAL const char* kAfterFrameToken("AFTER_FRAME");
EXTERNAL const char* kFrameNameToken("FRAME_NAME");
EXTERNAL const char* kLinkToFrameToken("LINK_TO_FRAME");
EXTERNAL const char* kLinkFromFrameToken("LINK_FROM_FRAME");
EXTERNAL const char* kLibraryNameToken("LIB_NAME");
EXTERNAL const char* kLibraryToken("LIBRARY");
EXTERNAL const char* kChangeCaseToken("CHANGECASE");

//Swatch tokens
EXTERNAL const char*	kSwatchToken("SWATCH");
EXTERNAL const char*	kSwatchNameToken("SWATCH_NAME");
EXTERNAL const char*	kSwatchListToken("SWATCH_LIST");
EXTERNAL const char*	kColorValOneToken("COLOR_VAL_1");
EXTERNAL const char*	kColorValTwoToken("COLOR_VAL_2");
EXTERNAL const char*	kColorValThreeToken("COLOR_VAL_3");
EXTERNAL const char*	kColorValFourToken("COLOR_VAL_4");
EXTERNAL const char*	kColorModelToken("COLOR_MODE");
EXTERNAL const char*	kIsSpotToken("SPOT_COLOR");
EXTERNAL const char*	kValuesForNameToken("USE_VALS_FOR_NAME");

//Typekit tokens
EXTERNAL const char*	kValueForTypekitToken("TYPEKIT_ON_OR_OFF");

//Color tokens
EXTERNAL const char* kCMYKToken("CMYK");
EXTERNAL const char* kCMYKPolicyToken("CMYK_POLICY");
EXTERNAL const char* kRGBToken("RGB");
EXTERNAL const char* kRGBPolicyToken("RGB_POLICY");

//Table Tokens
EXTERNAL const char*	kRowToken("ROW");
EXTERNAL const char*	kCellToken("CELL");
EXTERNAL const char*	kColumnToken("COLUMN");
EXTERNAL const char*	kTopLeftToken("TOP_LEFT");
EXTERNAL const char*	kBottomRightToken("BOTTOM_RIGHT");
EXTERNAL const char*	kNumRowsToken("NUMBER_OF_ROWS");
EXTERNAL const char*	kHeadersToken("HEADERS");
EXTERNAL const char*	kFootersToken("FOOTERS");

// App Tokens
EXTERNAL const char*	kReplaceExistingListItemToken("REPLACE_ITEM");
EXTERNAL const char*	kDeleteNonImportedListItemToken("DELETE_ITEM");

//OSCommands Tokens
EXTERNAL const char*	kWinCommandsToken("WIN_COMMANDS");
EXTERNAL const char*	kMacCommandsToken("MAC_COMMANDS");

//Invoke AAT Action Tokens
EXTERNAL const char*    kInvokeIOTAATParamToken("INVOKE_PARAM");
EXTERNAL const char*    kInvokeIOTAATEventToken("INVOKE_EVENT");
EXTERNAL const char*    kInvokeIOTAATFile("INVOKE_FILE");
EXTERNAL const char*    kInvokeIOTAATWaitFile("INVOKE_WAITFILE");
EXTERNAL const char*    kInvokeYieldUntilEvent("YIELDUNTILEVENT");


//UI Action Tokens
EXTERNAL const char* kCharToken("CHAR");
EXTERNAL const char* kModifierToken("MODIFIERS");

//Validator tokens
EXTERNAL const char*	kToleranceToken("TOLERANCE");
EXTERNAL const char*	kCompareAllToken("COMPARE_ALL");
EXTERNAL const char*	kCompareElementsToken("COMPARE_ELEMENTS");
EXTERNAL const char*	kCompareCharactersToken("COMPARE_CHARACTERS");
EXTERNAL const char*	kCompareCommentsToken("COMPARE_COMMENTS");
EXTERNAL const char*	kCompareXMLDeclToken("COMPARE_XMLDECL");
EXTERNAL const char*	kCompareXMLPIToken("COMPARE_XMLPI");

// Action Exclusion List Conditions
EXTERNAL const char*	kUserEditableToken("USER_EDITABLE");
EXTERNAL const char*	kConditionsToken("CONDITIONS");
EXTERNAL const char*	kKeyToken("KEY");
EXTERNAL const char*	kEntryToken("ENTRY");

//QA File tokens
#pragma mark QAFile Tag Defs 
EXTERNAL const char* kSessionFileDirectoryToken("session_file_directory");


#pragma mark Default Operator Names
EXTERNAL const char* kGreaterThanEqToStr("Greater Than or Equal To");
EXTERNAL const char* kGreaterThanStr("Greater Than");
EXTERNAL const char* kLessThanEqToStr("Less Than or Equal To");
EXTERNAL const char* kLessThanStr("Less Than");
EXTERNAL const char* kNotEqualStr("Not Equal");
EXTERNAL const char* kEqualStr("Equal");

#pragma mark Logic Types
EXTERNAL const char* kIfStr("if");
EXTERNAL const char* kElseIfStr("else if");
EXTERNAL const char* kElseStr("else");
EXTERNAL const char* kWhileStr("while");
EXTERNAL const char* kDoWhileStr("do while");

#pragma mark Sequence Type Name Strings
//You cannot/should not change these without updating every existing
//reference to the old values.  You will also need to write in support to
//the 2.0-current version reader so that it can properly instantiate sequences.
//In other words, these are used as keys for constructing items in the factory.
EXTERNAL const char*	kStdSeqListStr("Action Sequence");
EXTERNAL const char*	kIterativeLoopStr("Iterative Loop");
EXTERNAL const char*	kFileLoopStr("File Loop");
EXTERNAL const char*	kObjectLoopStr("Object Loop");
EXTERNAL const char*	kPermutationLoopStr("Permutation Loop");
EXTERNAL const char*	kParameterLoopStr("Parameter Loop");
EXTERNAL const char*	kLogicSeqStr("Logic Sequence");
EXTERNAL const char*	kLogicClusterSeqStr("Logic Sequence Cluster");
EXTERNAL const char*	kDoWhileSeqStr("Do/While Loop");
EXTERNAL const char*	kAlertWatchSeqStr("Alert Watcher");

#pragma mark Default AAT Variable Names 
EXTERNAL const char* kApp_PostingStr("#App");
EXTERNAL const char* kApp_ReceivingStr("$App");
EXTERNAL const char* kAssignment_PostingStr("#Assign");
EXTERNAL const char* kAssignment_ReceivingStr("$Assign");
EXTERNAL const char* kBook_PostingStr("#Book");
EXTERNAL const char* kBook_ReceivingStr("$Book");
EXTERNAL const char* kBookmark_PostingStr("#Bookmark");
EXTERNAL const char* kBookmark_ReceivingStr("$Bookmark");
EXTERNAL const char* kDoc_PostingStr("#Doc");
EXTERNAL const char* kDoc_ReceivingStr("$Doc");
EXTERNAL const char* kCharStyle_PostingStr("#CharStyle");
EXTERNAL const char* kCharStyle_ReceivingStr("$CharStyle");
EXTERNAL const char* kCharStyleGroup_PostingStr("#CharStyleGroup");
EXTERNAL const char* kCharStyleGroup_ReceivingStr("$CharStyleGroup");
EXTERNAL const char* kFrameGrid_PostingStr("#FrameGrid");
EXTERNAL const char* kFrameGrid_ReceivingStr("$FrameGrid");
EXTERNAL const char* kLayer_PostingStr("#Layer");
EXTERNAL const char* kLayer_ReceivingStr("$Layer");
EXTERNAL const char* kLibrary_PostingStr("#Library");
EXTERNAL const char* kLibrary_ReceivingStr("$Library");
EXTERNAL const char* kFormField_PostingStr("#FormField");
EXTERNAL const char* kFormField_ReceivingStr("$FormField");
EXTERNAL const char* kGuide_PostingStr("#Guide");
EXTERNAL const char* kGuide_ReceivingStr("$Guide");
EXTERNAL const char* kMaster_PostingStr("#Master");
EXTERNAL const char* kMaster_ReceivingStr("$Master");
EXTERNAL const char* kMovie_PostingStr("#Movie");
EXTERNAL const char* kMovie_ReceivingStr("$Movie");
EXTERNAL const char* kNote_PostingStr("#Note");
EXTERNAL const char* kNote_ReceivingStr("$Note");
EXTERNAL const char* kPageItem_PostingStr("#PageItem");
EXTERNAL const char* kPageItem_ReceivingStr("$PageItem");
EXTERNAL const char* kPage_PostingStr("#Page");
EXTERNAL const char* kPage_ReceivingStr("$Page");
EXTERNAL const char* kParaStyle_PostingStr("#ParaStyle");
EXTERNAL const char* kParaStyle_ReceivingStr("$ParaStyle");
EXTERNAL const char* kParaStyleGroup_PostingStr("#ParaStyleGroup");
EXTERNAL const char* kParaStyleGroup_ReceivingStr("$ParaStyleGroup");
EXTERNAL const char* kSound_PostingStr("#Sound");
EXTERNAL const char* kSound_ReceivingStr("$Sound");
EXTERNAL const char* kSpread_PostingStr("#Spread");
EXTERNAL const char* kSpread_ReceivingStr("$Spread");
EXTERNAL const char* kStory_PostingStr("#Story");
EXTERNAL const char* kStory_ReceivingStr("$Story");
EXTERNAL const char* kStructureElement_PostingStr("#StructureElement");
EXTERNAL const char* kStructureElement_ReceivingStr("$StructureElement");
EXTERNAL const char* kStyle_PostingStr("#Style");
EXTERNAL const char* kStyle_ReceivingStr("$Style");
EXTERNAL const char* kSwatch_PostingStr("#Swatch");
EXTERNAL const char* kSwatch_ReceivingStr("$Swatch");
EXTERNAL const char* kTable_PostingStr("#Table");
EXTERNAL const char* kTable_ReceivingStr("$Table");
EXTERNAL const char* kTableFrame_PostingStr("#Table Frame");
EXTERNAL const char* kTableFrame_ReceivingStr("$Table Frame");
EXTERNAL const char* kTextColumn_PostingStr("#TextColumn");
EXTERNAL const char* kTextColumn_ReceivingStr("$TextColumn");
EXTERNAL const char* kTextFrame_PostingStr("#TextFrame");
EXTERNAL const char* kTextFrame_ReceivingStr("$TextFrame");
EXTERNAL const char* kXMLTag_PostingStr("#XMLTag");
EXTERNAL const char* kXMLTag_ReceivingStr("$XMLTag");
EXTERNAL const char* kFile_PostingStr("#File");
EXTERNAL const char* kFile_ReceivingStr("$File");
EXTERNAL const char* kFolder_PostingStr("#Folder");
EXTERNAL const char* kFolder_ReceivingStr("$Folder");


EXTERNAL const char* kUnknownObj_PostingStr("#Object");
EXTERNAL const char* kUnknownObj_ReceivingStr("$Object");

EXTERNAL const char* kIndex_PostingStr("#Index");
EXTERNAL const char* kIndex_ReceivingStr("$Index");
EXTERNAL const char* kLength_PostingStr("#Length");
EXTERNAL const char* kLength_ReceivingStr("$Length");
EXTERNAL const char* kValue_PostingStr("#Value");
EXTERNAL const char* kValue_ReceivingStr("$Value");
EXTERNAL const char* kRect_PostingStr("#Rect");
EXTERNAL const char* kRect_ReceivingStr("$Rect");
EXTERNAL const char* kPoint_PostingStr("#Point");
EXTERNAL const char* kPoint_ReceivingStr("$Point");
EXTERNAL const char* kBoolean_PostingStr("#Boolean");
EXTERNAL const char* kBoolean_ReceivingStr("$Boolean");
EXTERNAL const char* kString_PostingStr("#String");
EXTERNAL const char* kString_ReceivingStr("$String");
EXTERNAL const char* kWidth_PostingStr("#Width");
EXTERNAL const char* kWidth_ReceivingStr("$Width");
EXTERNAL const char* kHeight_PostingStr("#Height");
EXTERNAL const char* kHeight_ReceivingStr("$Length");

EXTERNAL const char* kTopLeft_PostingStr("#TopLeft");
EXTERNAL const char* kTopLeft_ReceivingStr("$TopLeft");
EXTERNAL const char* kBottomRight_PostingStr("#BotRight");
EXTERNAL const char* kBottomRight_ReceivingStr("$BotRight");
EXTERNAL const char* kStart_PostingStr("#Start");
EXTERNAL const char* kStart_ReceivingStr("$Start");
EXTERNAL const char* kEnd_PostingStr("#End");
EXTERNAL const char* kEnd_ReceivingStr("$End");

EXTERNAL const char* kExpected_PostingStr("#Expected");
EXTERNAL const char* kExpected_ReceivingStr("$Expected");

EXTERNAL const char* kNumRows_PostingStr("#NumRows");
EXTERNAL const char* kNumRows_ReceivingStr("$NumRows");
EXTERNAL const char* kNumColumns_PostingStr("#NumColumns");
EXTERNAL const char* kNumColumns_ReceivingStr("$NumColumns");
EXTERNAL const char* kNumHeaders_PostingStr("#NumHeaders");
EXTERNAL const char* kNumHeaders_ReceivingStr("$NumHeaders");
EXTERNAL const char* kNumFooters_PostingStr("#NumFooters");
EXTERNAL const char* kNumFooters_ReceivingStr("$NumFooters");

EXTERNAL const char* kHyperlinkDest_PostingStr("#HyperlinkDest");
EXTERNAL const char* kHyperlinkDest_ReceivingStr("$HyperlinkDest");
EXTERNAL const char* kHyperlink_PostingStr("#Hyperlink");
EXTERNAL const char* kHyperlink_ReceivingStr("$Hyperlink");

EXTERNAL const char* kWindow_PostingStr("#Window");
EXTERNAL const char* kWindow_ReceivingStr("$Window");
EXTERNAL const char* kWorkspace_PostingStr("#Workspace");
EXTERNAL const char* kWorkspace_ReceivingStr("$Workspace");

EXTERNAL const char* kPrintPreset_PostingStr("#PrintPreset");
EXTERNAL const char* kPrintPreset_ReceivingStr("$PrintPreset");

EXTERNAL const char* kFont_PostingStr("#Font");
EXTERNAL const char* kFont_ReceivingStr("$Font");

EXTERNAL const char* kWidgetValue_PostingStr("#WidgetValue");
EXTERNAL const char* kWidgetValue_ReceivingStr("$WidgetValue");


#pragma mark Std Prod/Target/Val Level Strings
EXTERNAL const char* kSubjectStr("Target");
EXTERNAL const char* kProductStr("Output");

EXTERNAL const char* kExtensiveValidationStr("Extensive");
EXTERNAL const char* kStandardValidationStr("Standard");
EXTERNAL const char* kMinimumValidationStr("Minimum");

EXTERNAL const char* kDefaultValueStr("[Default]");
EXTERNAL const char* kYesStr("Yes");
EXTERNAL const char* kNoStr("No");
EXTERNAL const char* kDontCheckStr("Don\'t Check");

EXTERNAL const char* kHideStr("Hide");
EXTERNAL const char* kShowStr("Show");

EXTERNAL const char* kMenuUnderlinedStr("Underlined");
EXTERNAL const char* kMenuDashedStr("Dashed (multi-checked)");
EXTERNAL const char* kMenuUnselectedStr("Unchecked");
EXTERNAL const char* kMenuSelectedStr("Checked");
EXTERNAL const char* kDisabledStr("Disabled ");
EXTERNAL const char* kEnabledStr("Enabled ");

EXTERNAL const char* kSelectedToken("Selected");
EXTERNAL const char* kUnSelectedToken("Un-Selected");
EXTERNAL const char* kMixedToken("Mixed");

EXTERNAL const char* kAppendActionStr("Append");
EXTERNAL const char* kRemoveActionStr("Remove");
EXTERNAL const char* kSetActionStr("Set");
EXTERNAL const char* kInsertActionStr("Insert");
EXTERNAL const char* kGetCharAtIndexActionStr("Get Character At Index");

EXTERNAL const char* kGetCharIndexStr("Get Index of Character");
EXTERNAL const char* kGetLastCharIndexStr("Get Last Index of Character");
EXTERNAL const char* kContainsStr("Contains Substring");
EXTERNAL const char* kGetNumCharactersStr("Get Num Characters");

EXTERNAL const char* kNotRelativeStr("Not Relative");

EXTERNAL const char* kAutoCaptureStr("AUTO.xml");

EXTERNAL const char*	kUpDownStr("Up-Down");
EXTERNAL const char*	kUpStr("Up");
EXTERNAL const char*	kDownStr("Down");

EXTERNAL const char*	kSingleStr("Single");
EXTERNAL const char*	kDoubleStr("Double");
EXTERNAL const char*	kTripleStr("Triple");
EXTERNAL const char*	kQuadrupleStr("Quadruple");
EXTERNAL const char*	kQuintupleStr("Quintuple");

EXTERNAL const char*	kShiftStr("Shift");
EXTERNAL const char*	kCmdCntrlStr("Command/Ctrl");
EXTERNAL const char*	kMacControlStr("Mac_Control");
EXTERNAL const char*	kOptionAltStr("Option/Alt");

EXTERNAL const char*	kTopLeftStr("Top Left");
EXTERNAL const char*	kTopCenterStr("Top Center");
EXTERNAL const char*	kTopRightStr("Top Right");
EXTERNAL const char*	kLeftCenterStr("Left Center");
EXTERNAL const char*	kCenterStr("Center");
EXTERNAL const char*	kRightCenterStr("Right Center");
EXTERNAL const char*	kBottomLeftStr("Bottom Left");
EXTERNAL const char*	kBottomCenterStr("Bottom Center");
EXTERNAL const char*	kBottomRightStr("Bottom Right");

EXTERNAL const char*	kStrokeStr("Stroke");
EXTERNAL const char*	kFillStr("Fill");

EXTERNAL const char*	kMakeStopThumbStr("Make New Stop Thumb");
EXTERNAL const char*	kGetNumMidpointThumbStr("Get Num Midpoint Thumbs");
EXTERNAL const char*	kGetNumStopThumbStr("Get Num Stop Thumbs");
EXTERNAL const char*	kClickNthMidpointThumbStr("Click Nth Midpoint Thumb");
EXTERNAL const char*	kClickNthStopThumbStr("Click Nth Stop Thumb");
EXTERNAL const char*	kDragNthMidpointThumbStr("Drag Nth Midpoint Thumb");
EXTERNAL const char*	kDragNthStopThumbStr("Drag Nth Stop Thumb");
EXTERNAL const char*	kDragOffNthStopThumbStr("Drag Nth Stop Off Slider");

// File name defs
EXTERNAL const char* kAATLogFileName("AATSessionLog.txt");
EXTERNAL const char* kAATXMLLogFileName("AATSessionLog.xml");
EXTERNAL const char* kAATErrorFileName("QASessionLog.txt");
EXTERNAL const char* kAATErrorXMLLogFile("QASessionLog.xml");
EXTERNAL const char* kAATErrorXMLLogKey(kQASessionXMLLogKeyStr);
EXTERNAL const char* kAATErrorLogKey("QATestletteLog");

//Flavor Defs
EXTERNAL const char* kAcquisitionFlavor("ACQUISITION");
EXTERNAL const char* kCommandFlavor("COMMAND");
EXTERNAL const char* kCustomFlavor("CUSTOM");
EXTERNAL const char* kInformationalFlavor("INFORMATIONAL");
EXTERNAL const char* kOperationalFlavor("OPERATIONAL");
EXTERNAL const char* kUIFlavor("UI");
EXTERNAL const char* kUtilityFlavor("UTILITY");
EXTERNAL const char* kValidationFlavor("VALIDATION");

