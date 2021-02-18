//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BravoForwardDecl.h $
//  
//  Owner: Greg St. Pierre
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
//  Global include file for AGM. Any code within InDesign that needs to access
//  CoreTech objects should include this rather than including CoreTech headers
//  directly.
//  
//  Notes:
//  
//  InDesign #defines BIB_NO_THROW to force CoreTech components not to throw
//  exceptions in error situations
//  
//========================================================================================

#pragma once
#ifndef __BravoForwardDecl__
#define __BravoForwardDecl__

#include "ShuksanBravoFlags.h"


class AGMGradient;
class AGMPrintMarks;
class AGMRasterPort;
class AGMRun;
class AGMRun2;
class BIBProgress;

// pre-declare classes which are in the bib namespace.  This prevents
// us from getting ambiguous declaration compiler errors.
BEGIN_BIB_NAMESPACE

	class _t_AGMMaskServer; // AGM4: Not defined (used in inmask).  Need to determine proper replacement. -mjp
	class _t_AGMColorAlpha;
	
	class AGMColorProfile;
	class AGMColorSpace;
	class AGMColorSpaceList;
	class AGMFunction;
	class AGMFunctionList;
	class AGMGStatePort;
	class AGMImage;
	class AGMImageList;
	class AGMOPI;
	class AGMPaint;
	class AGMPath;
	class AGMPort;
	class AGMPrintDeviceController;
	class GPLineSegment;
	class GPLineSegmentList;
	class GPLineMgr;
	
	class CAGMColorSpace;
	class CAGMImage;
	class CAGMOPI;
	class CAGMPaint;
	class CAGMPort;
	class CAGMPrintMarks;
	class CAGMRasterPort;
	class CBIBError;	

	// Cooltype
	class CCTEncoding;
	class CCTText;
	class CCTTextList;
	class CTEncoding;
	class CTFamily;
	class CTFontDict;
	class CTFontInstance;
	class CTFontSet;
	class CTTranslator;
	class CTText;
	class CTTextList;
	
	struct _t_AGMCMYKColorRec;
	struct _t_AGMColorTab;
	struct _t_AGMFloatImageRecord;
	struct _t_AGMFloatPoint;
	struct _t_AGMFloatRect;
	struct _t_AGMImageRecord;
	struct _t_AGMInt16Rect;
	struct _t_AGMPatternFlt;
	struct _t_AGMRunCache;
	struct _t_AGMShading;
	struct _t_AGMTransRec;
	
	typedef struct _t_AGMCMYKColorRec AGMCMYKColorRec;
	typedef struct _t_AGMImageRecord AGMImageRecord;

	typedef struct _t_AGMStrokeParameters AGMStrokeParameters;

	class AGMGraphic;
	class AGMGraphixPort;
	class AGMGraphixCapturePort;
	class AGMCompositor;
	
#if !defined(_H_AIMDictionary)
	#define const_AIMDictionaryContainer void
#endif
END_BIB_NAMESPACE
USING_BIB_NAMESPACE;

class CTServer;
class BIBSharedBuffer;
//Harfbuzz
class HarfbuzzCooltype;

typedef struct _t_SamplingOptions SamplingFilterPortOptions;
typedef struct BRVCoordMatrix BRVMatrix, *BRVMatrixP;

// CoolType Defines for public include files
enum { kDontKnowScript = 0x40000000 };


#endif 
