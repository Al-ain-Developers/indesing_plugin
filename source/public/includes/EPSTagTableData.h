//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/EPSTagTableData.h $
//  
//  Owner: Scott Chai
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
//  OVERVIEW:	This file contains data types that are used in the EPS tag table.
//  
//========================================================================================

#pragma once
#ifndef __EPSTagTableData__
#define __EPSTagTableData__

typedef double COLORCOMPONENT;	// fraction between 0 and 1

typedef uint16 INFOFLAGS;
enum {
	ECFEmpty			= 0x00u,
	ECFCyanUsed			= 0x01u,
	ECFMagentaUsed		= 0x02u,
	ECFYellowUsed		= 0x04u,
	ECFBlackUsed		= 0x08u,
	ECFDotGainSuppress	= 0x10u,
	ECFHasDCSPlates		= 0x20u
};	// INFOFLAGS

/*------------------------------------------------------------------------------

	CMYK Color Block
		
------------------------------------------------------------------------------*/

typedef struct {
	COLORCOMPONENT c;		// cyan component
	COLORCOMPONENT m;		// magenta component
	COLORCOMPONENT y;		// yellow component
	COLORCOMPONENT k;		// black component
} CMYKApprox;

/*------------------------------------------------------------------------------

	RGB Color Block
	
------------------------------------------------------------------------------*/
typedef struct {
	COLORCOMPONENT r;		// red component
	COLORCOMPONENT g;		// green component
	COLORCOMPONENT b;		// blue component
} RGBApprox;

/*------------------------------------------------------------------------------

	Multiple Ink Color Block
	
------------------------------------------------------------------------------*/

#define PMMAXINKS	8		// max. #of inks allowed in a hifi color

typedef struct {
	int16		inkID;		// id for ink in table of PMINKRECs
	uint16		inkLevel;	// dot area coverage of the ink for this color (0-65535)
} PMINKVAL;

typedef struct {
	uint16		inkCnt;				// #of inks assoc. with this color
	PMINKVAL	inks[PMMAXINKS];	// component values
} PMHIFICOLOR;

typedef struct {
	COLORCOMPONENT r;
	COLORCOMPONENT g;
	COLORCOMPONENT b;
	COLORCOMPONENT c;
	COLORCOMPONENT m;
	COLORCOMPONENT y;
	COLORCOMPONENT k;
	PMHIFICOLOR hifi;
} MultiInkColor;


typedef struct {
	double version;
	uint16 revision;
	uint16 _padding[3];	// padding for Watson 1294448
}  ProcSetInfo;

typedef struct {
	uint16 columns;	// width in pixels
	uint16 rows;	// height in pixels
	uint16 depth;	// bits per channel - 1 or 8
	uint16 mode;	// 1 - bitmap/grayscale, 2 - LAB, 3 - RGB, 4 - CMYK
	uint16 pad;		// other channels
	uint16 blockSize;	// bytes per row per channel
	uint16 format;	// 1 - binary, 2 - hex ASCII
} ImageDataData;

#endif			//__EPSTagTableData__