//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMFlavorTypes.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Interface definition for the flavor types used in drag and drop and clipboard type negotiation
//  
//========================================================================================

#pragma once
#ifndef __PMFLAVORTYPES__
#define __PMFLAVORTYPES__

#ifdef PUBLIC_BUILD
#pragma export on
#endif

#include "K2Vector.h"

#if MACINTOSH
//preserve these old Carbon constants from Scrap.h
enum {
	kScrapFlavorTypePicture = 'PICT',
	kScrapFlavorTypeText = 'TEXT',
	kScrapFlavorTypeTextStyle = 'styl',
	kScrapFlavorTypeMovie = 'moov',
	kScrapFlavorTypeSound = 'snd ',
	kScrapFlavorTypeUnicode = 'utxt',
	kScrapFlavorTypeUnicodeStyle = 'ustl',
};

//fake flavor OSTypes for file promise UTIs that don't have one
enum {
	kPasteboardTypeFileURLPromise_FakeOSType = 'nDfp',
	kPasteboardTypeFilePromiseContent_FakeOSType = 'nDfc'
};

typedef OSType FlavorType;
#endif

#if defined  MACINTOSH || defined UNIX
	/**	basic type used to represent a data flavor to be used externally, like kTEXTExternalFlavor */
	typedef uint32 ExternalPMFlavor;
	/**	basic type used to represent a native data flavor, like kPageItemFlavor  */
	typedef uint32 PMFlavor;
	
	// To stream a flavor in core code you must use this macro
	// Mac: sizeof(PMFlavor) == sizeof(int32)
	#define XferFlavor(flavor)	XferInt32((int32&) flavor)
#endif
#ifdef WINDOWS
	typedef CLIPFORMAT ExternalPMFlavor;
	typedef CLIPFORMAT PMFlavor;
	//DECLARE_OBJECT_TYPE(CLIPFORMAT); actually an unsigned short

	/**	Win-Only: Use this to register flavor formats (for clipboard and drag drop operations)
	
		@flavorString IN character string describing the flavor, i.e. TEXT("Portable Document Format").
		@returns unsigned short CLIPFORMAT good only within a boot cycle - don't persist to disk.
	*/
	inline ExternalPMFlavor RegisterExternalFlavor(TCHAR* flavorString /*const PMString& flavorString*/) 
	{
		return ::RegisterClipboardFormat(flavorString /*.GrabTString()*/);
	}

	/**	Win-Only: Use this to retrieve the character string describing a flavor format
	
		@flavor IN retrieve the name of this flavor
		@flavorString OUT string describing the flavor, i.e. PMString("Portable Document Format").
	*/
	inline void GetExternalFlavorName(ExternalPMFlavor flavor, PMString& flavorString) 
	{
		TCHAR buffer[512];
		int count = ::GetClipboardFormatName(flavor, buffer, 500);
		(count > 0)? flavorString.SetXString((UTF16TextChar *)buffer, count) : flavorString.clear();
	}
		
	// To stream a flavor in core code you must use this macro
	// Win: sizeof(PMFlavor) == sizeof(int16)
	#define XferFlavor(flavor)	XferInt16((int16&) flavor)
#endif

typedef K2Vector<ExternalPMFlavor> ExternalPMFlavorList;

/**	constant used to represent the empty internal flavor, or to indicate no preference for a particular internal flavor */
const PMFlavor kNoFlavor = static_cast<PMFlavor>(0);
/**	constant used to represent the empty external flavor, or to indicate no preference for a particular external flavor */
const ExternalPMFlavor kNoExternalFlavor = static_cast<ExternalPMFlavor>(0);

/**	basic type used to contain information about a flavor during a data exchange operation*/
typedef uint32 PMFlavorFlags;

/**	@name PMFlavorFlags constants
*/
//@{
/** flavor is available to all*/
const PMFlavorFlags kNormalFlavorFlag = static_cast<PMFlavorFlags>(0);
/** flavor is available to sender only - used for flavors you wish to remain internal only */
const PMFlavorFlags kSenderOnlyFlavorFlag = static_cast<PMFlavorFlags>(1);	
/** (Mac-only) flavor is translated by sender*/
const PMFlavorFlags kSenderTranslatedFlavorFlag = static_cast<PMFlavorFlags>(2);	
/** (Mac-only) flavor should not be saved*/
const PMFlavorFlags kFlavorNotSavedFlag = static_cast<PMFlavorFlags>(4);		
/** (Mac-only) flavor is translated by system*/
const PMFlavorFlags kSystemTranslatedFlavorFlag = static_cast<PMFlavorFlags>(0x00000100);		
/** Mask applied before passing flavor flags to Mac drag manager */
const PMFlavorFlags kMacDragDropFlavorFlagMask = static_cast<PMFlavorFlags>(0x00000107);	
/** Mask applied before passing flavor flags to Mac scrap manager */
const PMFlavorFlags kMacScrapFlavorFlagMask = static_cast<PMFlavorFlags>(0x00000003);			
/** Mask applied before passing flavor flags to Win OLE - which doesn't support flavor flags */
const PMFlavorFlags kWinOLEFlavorFlagMask = static_cast<PMFlavorFlags>(0x00000000);				
//@}

/**	basic type used to contain information about the relative priority of an external flavor in a data exchange operation*/
typedef uint16 PMFlavorPriority;

/**	@name PMFlavorPriority constants
*/
//@{
/** priority of flavor is unknown or unspecified*/
const PMFlavorPriority kUnknownFlavorPriority = static_cast<PMFlavorPriority>(0);

/** flavor is of the highest priorty, first in the list*/
const PMFlavorPriority kHighestFlavorPriority = static_cast<PMFlavorPriority>(250);
/** flavor is of the second highest priorty, second in the list*/
const PMFlavorPriority kSecondFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 1);
/** flavor is of the third highest priorty, third in the list*/
const PMFlavorPriority kThirdFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 2);
/** flavor is of the 4th highest priorty, 4th in the list*/
const PMFlavorPriority kFourthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 3);
/** flavor is of the 5th highest priorty, 5th in the list*/
const PMFlavorPriority kFifthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 4);
/** flavor is of the 6th highest priorty, 6th in the list*/
const PMFlavorPriority kSixthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 5);
/** flavor is of the 7th highest priorty, 7th in the list*/
const PMFlavorPriority kSeventhFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 6);
/** flavor is of the 8th highest priorty, 8th in the list*/
const PMFlavorPriority kEighthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 7);
/** flavor is of the 9th highest priorty, 9th in the list*/
const PMFlavorPriority kNinthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 8);
/** flavor is of the 10th highest priorty, 10th in the list*/
const PMFlavorPriority kTenthFlavorPriority = static_cast<PMFlavorPriority>(kHighestFlavorPriority - 9);

/** Special flavor priorities used to achieve some non-standard behavior. */
//@{
/** This special flavor priority is used by override drop target helpers to reject a drop so that someone higher up the
	target hierarchy can handle the drop.
*/
const PMFlavorPriority kOverrideDropTargetHelper_RejectDrop_FlavorPriority = static_cast<PMFlavorPriority>(300);
/** This special flavor priority is used by override data exchange handler flavor helpers to ignore a flavor 
	so that a lower priority flavor will be used instead...
*/
const PMFlavorPriority kOverrideDEHandlerHelper_IgnoreFlavor_FlavorPriority = static_cast<PMFlavorPriority>(301);
//@}
//@}

/** Class used to represent the response from an IDataExchangeHandler when asked whether external data could be converted to an internal format.

		@see IDataExchangeHandler::CanInternalizeData
*/
class PUBLIC_DECL DataExchangeResponse
{
	public:
		typedef base_type data_type;

		/** Default constructor - creates a negative response */
		DataExchangeResponse() 
			: fCanDo(kFalse), 
			  fFlavor(kNoExternalFlavor), 
			  fFlavorFlags(kNormalFlavorFlag), 
			  fFlavorPriority(kUnknownFlavorPriority) {}
		
		/**	Constructor

			@param canDo IN could the external data be converted to an internal format
			@param flavor IN which external data flavor the handler would convert
			@param flavorFlags IN flags associated with the flavor
			@param priority IN the flavor priority of the flavor the target as decided to accept
		 */
		DataExchangeResponse(bool16 canDo, ExternalPMFlavor flavor, PMFlavorFlags flavorFlags = kNormalFlavorFlag, PMFlavorPriority priority = kUnknownFlavorPriority)
			: fCanDo(canDo), 
			  fFlavor(flavor), 
			  fFlavorFlags(flavorFlags), 
			  fFlavorPriority(priority) {}
		
		/** Copy constructor */
		DataExchangeResponse(const DataExchangeResponse& other) 
			: fCanDo(other.fCanDo), 
			  fFlavor(other.fFlavor), 
			  fFlavorFlags(other.fFlavorFlags), 
			  fFlavorPriority(other.fFlavorPriority) {}

		bool operator==(const DataExchangeResponse&) const { ASSERT_FAIL("appease K2Vector.Location"); return false; }
		
		/** Can the data be converted? */
		bool16 						CanDo() const {return fCanDo;}
		
		// Additional details
		/** Which flavor will be converted? */
		ExternalPMFlavor 	GetFlavor() const {return fFlavor;}
		/** Flavor flags for the flavor to be converted. */
		PMFlavorFlags 			GetFlavorFlags() const {return fFlavorFlags;} 
		/** Priority of flavor to be converted. */
		PMFlavorPriority 		GetFlavorPriority() const {return fFlavorPriority;}

		/** Constant representing an invalid response. */
	static const DataExchangeResponse	kInvalidDataExchangeResponse;

	protected:
		bool16					fCanDo;	
		
		ExternalPMFlavor fFlavor;
		PMFlavorFlags		fFlavorFlags;
		PMFlavorPriority	fFlavorPriority;
};

typedef K2Vector<DataExchangeResponse> OrderedPromiseList;
typedef K2Vector<ExternalPMFlavor> OrderedFlavorList;

/** Helper method to ensure unique promises in AddPromisesForExternalize (unique by flavor) */
PUBLIC_DECL bool16 AppendPromiseIfUnique(OrderedPromiseList& orderedPromiseList, const DataExchangeResponse& promise);
/** Helper method to ensure unique flavors in ImportProviderUtils::GetFlavorsForExport, IDataExchangeHandler::AddExternalizeableFlavorsToList, IDataExchangeHandler::AddInternalizeableFlavorsToList, etc (unique by flavor) */
PUBLIC_DECL bool16 AppendFlavorIfUnique(ExternalPMFlavorList& flavorList, const ExternalPMFlavor& flavor);

// utility to compare indices inside ExternalPMFlavorLists and OrderedFlavorLists
inline int32 minFlavorIndex(int32 a, int32 b)
{
	if (a >= 0 && b >= 0)
		return (a < b) ? a : b;
	else if (a >= 0)
		return a;
	else
		return b;
}

// utility to compare iterators inside ExternalPMFlavorLists and OrderedFlavorLists
inline K2Vector<ExternalPMFlavor>::iterator minFlavorIter(K2Vector<ExternalPMFlavor>::iterator a, K2Vector<ExternalPMFlavor>::iterator b)
{
 	return (a < b) ? a : b;
}

//==================================================================================
// Flavor Constants Declarations
//==================================================================================

/** ExternalPMFlavor constants - data flavors used to represent external data types used to exchange data with external applications. */
//@{
/** Raw ASCII characters */
extern PUBLIC_DECL const ExternalPMFlavor 				kTEXTExternalFlavor;					
/** Raw Unicode characters */
extern PUBLIC_DECL const ExternalPMFlavor				kUNICODETEXTExternalFlavor;		

/** File data from desktop, or elsewhere */
extern PUBLIC_DECL const ExternalPMFlavor 				kDesktopExternalFlavor;

#ifdef MACINTOSH
	/** Macintosh styled Unicode text data */
	extern PUBLIC_DECL const ExternalPMFlavor 			kUNICODESTYLExternalFlavor;		
	/** Macintosh styled text data */
	extern PUBLIC_DECL const ExternalPMFlavor 			kSTYLExternalFlavor;					
	/** Macintosh PICT */
	extern PUBLIC_DECL const ExternalPMFlavor 			kPICTExternalFlavor;

	/** 64-bit desktop file promise and content promise flavors */
	extern PUBLIC_DECL const ExternalPMFlavor			kPasteboardTypeFileURLPromiseExternalFlavor;
	extern PUBLIC_DECL const ExternalPMFlavor			kPasteboardTypeFileURLPromiseContentExternalFlavor;

	/** Private flavor used to tag clipboard data as originating from InDesign/InCopy  */
	extern PUBLIC_DECL const ExternalPMFlavor 			kPMPrivateClipboardMarkerFlavor;

	/** OSType used for file drags on Cocoa, from kUTTypeFileURL UTI ("public.file-url") */
	#define flavorTypeFileURL 'furl'
#endif
#ifdef WINDOWS
	/** Windows BitMap data */
	extern PUBLIC_DECL const ExternalPMFlavor			kBITMAPExternalFlavor;				
	/** Windows Device Independent BitMap data */
	extern PUBLIC_DECL const ExternalPMFlavor			kDIBExternalFlavor;				
	/** Windows Metafile data */
	extern PUBLIC_DECL const ExternalPMFlavor			kMetafileExternalFlavor;				
	/** Windows Enhanced Metafile data */
	extern PUBLIC_DECL const ExternalPMFlavor			kEnhMetafileExternalFlavor;			
#endif

/** Firedrake Snippet-based Pageitem data (for internal use only use with kSenderOnlyFlavorFlag) */
extern PUBLIC_DECL const ExternalPMFlavor 				kPageItemXMLSnippetExternalFlavor;				
/** Firedrake Snippet-based Structure data (for internal use only use with kSenderOnlyFlavorFlag) */
extern PUBLIC_DECL const ExternalPMFlavor 				kStructureXMLSnippetExternalFlavor;				
/** Color data. Note: we don't implement a lossless external format for color data. */
extern PUBLIC_DECL const ExternalPMFlavor 				kPMColorExternalFlavor;				

/** Illustrator Native Clip format (AICB)	 */
extern PUBLIC_DECL const ExternalPMFlavor 				kAICBExternalFlavor;					
/** PDF data */
extern PUBLIC_DECL const ExternalPMFlavor				kPDFExternalFlavor;						
/** TIFF data */
extern PUBLIC_DECL const ExternalPMFlavor				kTIFFExternalFlavor;						

/** Raw RGB Value 	(Used for testing only?) */
extern PUBLIC_DECL const ExternalPMFlavor 				kRGBColorExternalFlavor;				
/** Raw CMYK Value	(Used for testing only?) */
extern PUBLIC_DECL const ExternalPMFlavor 				kCMYKColorExternalFlavor;			

/** RTF data */
extern PUBLIC_DECL const ExternalPMFlavor 				kRTFExternalFlavor;			

/** URL data */
extern PUBLIC_DECL const ExternalPMFlavor 				kURLExternalFlavor;				

/** VersionCue file path data from Bridge application, or elsewhere */
extern PUBLIC_DECL const ExternalPMFlavor 				kVersionCueItemExternalFlavor;		

/** INX data */
extern PUBLIC_DECL const ExternalPMFlavor				kINXExternalFlavor;						

/** OWL Palette drag data */
extern PUBLIC_DECL const ExternalPMFlavor				kOWLExternalFlavor;		

/** Chromium drag data */
extern PUBLIC_DECL const ExternalPMFlavor				kChromiumExternalFlavor;		

//@}


// INTERNAL FLAVORS:
//
/** PMFlavor constants - data flavors that represent native data types internal to the application. Used for clipboard and drag/drop.
*/
//@{
/** deprecated debug only */
extern PUBLIC_DECL const PMFlavor 				 				kTEXTFlavor;
		
/** Internal representation of pageitems */
extern PUBLIC_DECL const PMFlavor 				 				kPageItemFlavor;
/** Internal representation of text data */
extern PUBLIC_DECL const PMFlavor 				 				kPMTextFlavor;
/** Internal representation of color data */
extern PUBLIC_DECL const PMFlavor 				 				kPMColorFlavor;
/** Internal representation of table data */
extern PUBLIC_DECL const PMFlavor 				 				kPMTableFlavor;
/** Internal representation of chromium MIME data */
extern PUBLIC_DECL const PMFlavor 				 				kChromiumFlavor;

/** Layer panel flavors */
//@{
/** layer proxy */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerProxyFlavor;
/** layer order */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerZOrderFlavor;
/** layer visibility */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerEyeFlavor;
/** layer pencil */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerPencilFlavor;
/** layer panel page item z-order */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerPageItemZOrderFlavor;
/** layer panel page item for duplicate and delete */
extern PUBLIC_DECL const PMFlavor 				 				kPMLayerPageItemDupDeleteFlavor;
//@}

/** Char style flavor */
extern PUBLIC_DECL const PMFlavor 				 				kPMCharStyleListFlavor;
/** Paragraph style flavor */
extern PUBLIC_DECL const PMFlavor 				 				kPMParaStyleListFlavor;

/** Swatches panel flavors */
//@{
/** swatch order */
extern PUBLIC_DECL const PMFlavor 				 				kPMSwatchesZOrderFlavor;
/** swatch item data */
extern PUBLIC_DECL const PMFlavor 				 				kPMSwatchesFlavor;
/** swatch lib item data */
extern PUBLIC_DECL const PMFlavor 				 				kPMSwatchLibSwatchesFlavor;
/** stroke color data */
extern PUBLIC_DECL const PMFlavor 				 				kPMStrokeColorFlavor;
/** fill color data */
extern PUBLIC_DECL const PMFlavor 				 				kPMFillColorFlavor;
//@}

/** Pages panel flavors */
//@{
/** page data */
extern PUBLIC_DECL const PMFlavor 				 				kPMPageFlavor;	
/** page range data */
extern PUBLIC_DECL const PMFlavor 				 				kPMPagesFlavor;
/** spread data */
extern PUBLIC_DECL const PMFlavor 				 				kPMSpreadFlavor;	
/** spread range data */
extern PUBLIC_DECL const PMFlavor 				 				kPMSpreadsFlavor;
/** master page data */
extern PUBLIC_DECL const PMFlavor 				 				kPMMasterPageFlavor;
/** master spread data */
extern PUBLIC_DECL const PMFlavor 				 				kPMMasterSpreadFlavor;
/** master spread range data */
extern PUBLIC_DECL const PMFlavor 				 				kPMMasterSpreadsFlavor;
//@}

/** Internal representation of file data, used when importing a dropped file */
extern PUBLIC_DECL const PMFlavor 				 				kPMSysFileFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPMRTFFlavor; /* Unimplemented: should be deleted */

extern PUBLIC_DECL const PMFlavor 				 				kPMBookContentZOrderFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPMIndexSortOptionZOrderFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPMXMLNodeFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPMNamedGridListFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMInkListZOrderFlavor;

extern PUBLIC_DECL const PMFlavor								kPMTrapStyleListFlavor;

/** TOC panel flavors */
//@{
/** toc order */
extern PUBLIC_DECL const PMFlavor 				 				kPMTOCZOrderListFlavor;
/** toc new */
extern PUBLIC_DECL const PMFlavor 				 				kPMTOCZOrderListAddFlavor;
//@}

extern PUBLIC_DECL const PMFlavor 				 				kPMIndexTopicFlavor;

extern PUBLIC_DECL const PMFlavor								kPMHyperlinkListFlavor;
extern PUBLIC_DECL const PMFlavor								kPMBookmarkListFlavor;

/** Structure panel flavors */
//@{
/** structure element data - used within the structure panel */
extern PUBLIC_DECL const PMFlavor 				 				kXMLStructureElementFlavor;
/** structure data - used to drag out of the structure planel */
extern PUBLIC_DECL const PMFlavor 				 				kXMLStructureDragDropFlavor;
/** structure tag data */
extern PUBLIC_DECL const PMFlavor 				 				kXMLTagDragDropFlavor;
//@}

extern PUBLIC_DECL const PMFlavor 				 				kPMURLFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kSepPrvEyeFlavor;

/** Object Style panel flavors */
//@{
extern PUBLIC_DECL const PMFlavor 				 				kPMObjectStyleListFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMDefaultTextObjStyleFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMDefaultGraphicObjStyleFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMDefaultFrameGridObjStyleFlavor;
//@}

extern PUBLIC_DECL const PMFlavor								kPMTimingPanelDragDropFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kStoryListDragDropFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kDictOrderDragDropFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPMJBXContentListFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMJBXLinkListFlavor;

extern PUBLIC_DECL const PMFlavor 				 				kPSDLayerEyeFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kXMLRulesDragDropFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kXPEffectsDDFlavor;

/** Table and Cell Style Panel Flavors */
extern PUBLIC_DECL const PMFlavor								kPMTableStyleListFlavor;
extern PUBLIC_DECL const PMFlavor								kPMCellStyleListFlavor;

extern PUBLIC_DECL const PMFlavor								kPMConditionTagListFlavor;

extern PUBLIC_DECL const PMFlavor								kMSOStateDragDropFlavor;

/** Article Panel Flavor */
extern PUBLIC_DECL const PMFlavor								kArticlePanelDragDropFlavor;

extern PUBLIC_DECL const PMFlavor								kListItemsDragDropFlavor;

extern PUBLIC_DECL const PMFlavor								kPMListBoxZOrderFlavor;

// Buttons and form state list box drag/drop flavors.
extern PUBLIC_DECL const PMFlavor 				 				kPMStateProxyFlavor;
extern PUBLIC_DECL const PMFlavor 				 				kPMStateEyeFlavor;

//@}

#pragma export off

#endif //__PMFLAVORTYPES__
