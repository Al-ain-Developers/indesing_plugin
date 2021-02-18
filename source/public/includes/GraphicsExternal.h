//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GraphicsExternal.h $
//  
//  Owner: Greg St. Pierre (for lack of someone better)
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
//  GraphicsExternal.h
//  
//  Data types and structures for use by external developers.
//  
//========================================================================================

#pragma once
#ifndef __BravoExternal__
#define __BravoExternal__

#ifndef _H_AGMTypes
#ifndef _H_AGMPrint

#include "BravoForwardDecl.h"

#define AGMPrintAPIVersion			3		/* API version number */
#define PS_INK_NAME_MAX				32		/* max #of chars in an ink name */

#define kAGMPrintMinNDensity				0.001
#define kAGMPrintMaxNDensity				10.0
#define kAGMPrintMinAngle					0
#define kAGMPrintMaxAngle					360
#define kAGMPrintMinBlkDen					0.001
#define kAGMPrintMaxBlkDen					10.0
#define kAGMPrintMinBlkColor				0.0
#define kAGMPrintMaxBlkColor				100.0
#define kAGMPrintMinTrapWid					0	
#define kAGMPrintMaxTrapWid					8.0
#define kOnHostMaxTrapWid					4.0
#define kAGMPrintMinBlackWidth				0
#define kAGMPrintDefaultBlkWidthScaleFator	1.0
#define kAGMPrintMinDPI						36
#define kAGMPrintMaxDPI						10000

// declare structs in the bib namespace -- this prevents
// us from getting ambiguous declaration compiler errors.
// rcook - below are the structs giving SDK samplecode a problem.
BEGIN_BIB_NAMESPACE

typedef struct _t_AGMFloatRect	{
	float	xMin;
	float	yMin;
	float	xMax;
	float	yMax;
} AGMFloatRect;


typedef struct _t_AGMFloatPoint	{
	float	x;
	float	y;
} AGMFloatPoint;

#define kGrayColorSpace	0
#define kRGBColorSpace	1
#define kCMYKColorSpace	2
#define kLabColorSpace	3

/**
 Encoding flags to be used in the colorSpace field of AGMImageRecords. These are
 bitfield values that should be bitwise-OR'd with one of the above colorspace
 family constants (e.g., kRGBColorSpace | kColorSpaceHasAlpha).
 
 kColorSpaceHasAlpha indicates to AGM that the specified colorspace has an
 alpha channel. This can be used to create a 32-bit per pixel RGB + alpha
 image, for instance. Note that setting the colorspace to include alpha like
 this requires that the bitsPerPixel and byteWidth values be adjusted for the 
 presence of an additional channel.
 
 kColorSpaceSwapAlpha indicates to AGM that the alpha channel occurs as the
 last channel in each pixel. This swaps the channel ordering from its
 default ARGB ordering to its alternate ordering of RGBA.
 
 Note to InDesign Engineering: These flags, like the colorspace family
 enumerated values above, *must* be kept in sync with AGM headers.
 */
#define kColorSpaceHasAlpha			16
#define	kColorSpaceSwapAlpha		0x200

typedef struct _t_AGMInt16Rect {
	int16	xMin;
	int16	yMin;
	int16	xMax;
	int16	yMax;
} AGMInt16Rect;

typedef struct _t_AGMColorTab	{
	int32	numColors;
	void*	theColors;
} AGMColorTab;


typedef struct _t_AGMImageRecord	{
	AGMInt16Rect	bounds;
	void*			baseAddr;
	int32			byteWidth;
	int16			colorSpace;
	int16			bitsPerPixel;
	float*			decodeArray; // can be nil - used to be Fixed*
	AGMColorTab		colorTab;
} AGMImageRecord;

//
// Progress constants
// Possible ProgressProcPtr "process" values and their meanings (see IPrintCmdData.h)
//
enum	{
	kAGMPPopLastProgress,
	kAGMPPushCompilingDocumentResources,
	kAGMPPushCompilingPageResources,
	kAGMPPushStreamingDocumentFont,
	kAGMPPushStreamingDocumentResource,
	kAGMPPushStreamingPageFont,
	kAGMPPushStreamingPageResource,
	kAGMPPushStreamingPageContent,
	kAGMPPushStreamingPageEpilogue,
	kAGMPPushStreamingDocumentEpilogue,
	kAGMPPushStreamingDocumentProcset,
	kAGMPPushStreamingPageSeparation,
	kAGMPPushStreamingPageImage,
	kAGMPPushStreamingPageImageOPI,
	kAGMPPushStreamingPageCSA,
	kAGMPPushStreamingPageCRD,
	kAGMPPushStreamingPageGradient,
	kAGMPPushOnHostTrapBeginPage,
	kAGMPSetOnHostTrapProgressPercent,		
	kAGMPStreamingPageImageProgressPercent	
};
/*
kAGMPPushCompilingDocumentResources:

        This typically happens during the first pass of a two pass
        process.  It is compiling the description of resources that
        are used by the entire document.

kAGMPPushCompilingPageResources

        This typically happens during the first pass of a two pass
        process.  It is compiling the description of resources that
        are used by a particular page.

kAGMPPushStreamingDocumentFont

        It is sending out a description of a font that will be used
        across the entire document.  For this call:

        name = name of font (a C string)

kAGMPPushStreamingDocumentResource

        It is sending out a non-font resource that is used across
        the entire document.  For this call:

        name = name of resource (a C string), or null if no name exists

kAGMPPushStreamingPageFont

        It is sending a description of a font that is used on this
        page only.  For this call:

        name = name of font (a C string)

kAGMPPushStreamingPageResource

        It is sending out a non-font resource that is used for
        this page only.  For this call:

        name = name of resource (a C string), or null if no name exists

kAGMPPushStreamingPageContent

        It is sending out the description of a page.

kAGMPPushStreamingPageEpilogue

        It is sending things that go at the end of a page (like
        showpage stuff).

kAGMPPushStreamingDocumentEpilogue

        It is sending things that go at the end of a document.

kAGMPPushStreamingDocumentProcset

        It is sending out a procset needed by the document. For this call:

        name = 0 or filename (if procset is external)

kAGMPPushStreamingPageSeparation

        It is beginning a separation. For this call:

        name = current plate name (char *, PS_INK_NAME_MAX chars)

kAGMPPushStreamingPageImage

        It is sending out the description of an image.

kAGMPPushStreamingPageImageOPI

        It is sending out the description of an OPI image.

kAGMPPushStreamingPageCSA

        It is sending out the description of a color space.

kAGMPPushStreamingPageCRD

        It is sending out the description of a color rendering dictionary.

kAGMPPushStreamingPageGradient

        It is sending out the description of a color gradient.

			
	return value:

			kTrue if successful (continue processing), or kFalse if cancelled.
*/
	
//
// Error codes
// The errors below will be offsets from the constant kAGMErrorStartNumError (defined in PrintID.h)
//
enum	{
	/** Success */
	kAGMPrtErrSuccess,
	/** A dictionary has failed a validation test against its schema */
	kAGMPrtErrSchema,
	/** General problem initializing system */
	kAGMPrtErrInit,
	/** PPD parsing error */
	kAGMPrtErrPPD,
	/** Not enough memory */
	kAGMPrtErrNoMem,
	/** User cancelled printing */
	kAGMPrtErrUserAbort,
	/** Print loop state invalid */
	kAGMPrtErrEvtOrder,
	/** General configuration error */
	kAGMPrtErrConfig,
	/** Bad paramater passed to an API */
	kAGMPrtErrInvldArg,
	/** Couldn't write to output stream */
	kAGMPrtErrStream,
	/** Expected internal only: current printer type is unsupported */
	kAGMPrtErrUnsprtdDeviceType,
	/** General PS error has occured */
	kAGMPrtErrGenrlPSErr,
	/** Printer is not found, is closed or not selected */
	kAGMPrtErrPrtrNotFound,
	/** Default printer not found, is closed or not selected */
	kAGMPrtErrDfltPrtrNotFound,
	/** No printers available */
	kAGMPrtErrNoPrtrsFound,
	/** Expected internal only: miscelleanous error */
	kAGMPrtErrOther,
	/** Disk full error from OS while writing to disk */
	kAGMPrtErrDiskFull,
	/** Expected internal only: C++ Exception caught */
	kAGMPrtErrCatch,
	/**
		Function not supported in port

		<b>Note:</b> This must remain 0xFFFF as is used
		outside of files which include this header.
	*/
	kAGMPrtErrUnsupported = 0xFFFF
};

END_BIB_NAMESPACE


#endif
#endif

#endif
