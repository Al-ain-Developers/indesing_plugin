//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/PubConvIDs.h $
//  
//  Owner: Glennm 
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
#ifndef __PUBCONVIDS_H__
#define __PUBCONVIDS_H__

#include "IDFactory.h"

//**********************************************
// Plugin Prefixes for parts of the Publications Converter
#define kPubConvPrefix		RezLong(0x47100)
#define kPubConvUIPrefix	(kPubConvPrefix + 0x40)
//#define kPubConvUIPrefix	RezLong(0x47200) Value for when the UI was in it's own plugin
#define kPM65ReaderPrefix	RezLong(0x47300)
#define kQX3ReaderPrefix	RezLong(0x47400)
#define kQX4ReaderPrefix    RezLong(0x47200)

// Since the ReaderTestHarness and MapperTestHarness are non shipping 
// plugins, they didn't get their own prefix.
// They'll occupy the high end of PubConv's range
#define kRdrTHPrefix                (kPubConvPrefix + 0x80)
#define kXMLReaderPrefix            (kPubConvPrefix + 0xC0)


//**********************************************
// We need Plugin Names and IDs for the version resource
#define kPubConvPluginName 			"Publications Converter"
#define kPubConvPluginID 			kPubConvPrefix + 1

//#define kPubConvUIPluginName 		"PublicationsConverterUI"
//#define kPubConvUIPluginID 		kPubConvPrefix + 2

#define kPM65ReaderPluginName 		"PageMaker 6.5 Reader"
#define kPM65ReaderPluginID 		kPM65ReaderPrefix + 3

#define kQX3ReaderPluginName 		"QuarkXPress 3.3 Reader"
#define kQX3ReaderPluginID 			kQX3ReaderPrefix + 4

#define kQX4ReaderPluginName        "QuarkXPress 4.0 Reader"
#define kQX4ReaderPluginID          kQX4ReaderPrefix + 4

#define kReaderTHPluginName 		"ReaderTH"
#define kReaderTHPluginID 			kRdrTHPrefix + 1

#define kXMLReaderPluginName 		"XMLReader"
#define kXMLReaderPluginID 			kXMLReaderPrefix + 1



//**********************************************
// Interface IDs for our custom interfaces
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLICATIONREADER, kPubConvPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOMELEMENT, kPubConvPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOMHIERARCHY, kPubConvPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOMATTR, kPubConvPrefix + 4 															)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOMIDGENERATOR, kPubConvPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERSIONLOGGER, kPubConvPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERSIONWARNINGSDLG, kPubConvPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPUBCONVSAVEFILEDIALOG, kPubConvPrefix + 8)


//**********************************************
// Boss ID's of subparts that the Servicer and Mapper need

DECLARE_PMID(kClassIDSpace, kConversionWarningsDlgBossID, kPubConvUIPrefix + 1)

	// Reader ClassIDs
	// NOTE: k_unReaderIDs in Servicer\PubReaderManager.cpp is
	// an array used to store these values. If you add a reader,
	// add the ID to this array if you want it to get acknowledged
DECLARE_PMID(kClassIDSpace, kPM65ReaderBoss, kPM65ReaderPrefix + 1)
DECLARE_PMID(kClassIDSpace, kQX3ReaderBoss, kQX3ReaderPrefix + 1)
DECLARE_PMID(kClassIDSpace, kQX4ReaderBoss, kQX4ReaderPrefix + 1)
DECLARE_PMID(kClassIDSpace, kXMLReaderBoss, kXMLReaderPrefix + 1)

#define kReaderBossCount			4

// if we exceed 10 readers a new Servicer build is required





#endif	// __PUBCONVIDS_H__


/*****************************************************************************
 * $Log: /Dev/Source/Components/Filters/PubConv/Shared/Includes/PubConvIDs.h $
 * 
 * 21    10/5/98 7:28 PM Glennm
 * Change for Build 317: made plugin IDs numeric.
 * 
 * 20    9/28/98 5:12 PM Glennm
 * Changed the PubConvUI prefix to share the PubConv prefix range (because
 * the UI is getting merged into PubConv)
 * 
 * 19    7/17/98 1:27 PM Glennm
 * Changed to new prefixes. No longer share 0x40B00 amongst the
 * components.
 * 
 * 18    7/16/98 6:18 PM Glennm
 * Added a few plugin name and ID constants
 * 
 * 17    6/5/98 4:34 PM Glennm
 * Deleted old IID_IPOMXXX accessor interfaces and added some stuff from
 * PubConvUI
 * 
 * 16    6/04/98 4:07p Patricka
 * Changed the PubConvUI prefix id to avoid a collision.
 * 
 * 15    6/02/98 6:54p Patricka
 * Changed kExampleReader2Prefix to kPubConvUIPrefix
 * 
 * 14    5/22/98 4:04 PM Glennm
 * Added some BADLY needed brackets to the kReaderBossCount definition (it
 * was 311 previously instead of 11)
 * 
 * 13    4/8/98 4:56 PM Glennm
 * Introduced IID_IPOMATTR, shifted the ReaderBoss constants.
 * 
 * 12    4/3/98 3:06 PM Glennm
 * Added interface constants for IID_IPOMIDGENERATOR and
 * IID_ICONVERSIONLOGGER
 * 
 * 11    4/01/98 12:08p Trevora
 * changed QX33 to QX3 and made the QX3 and QX4 ids unique
 * 
 * 10    4/01/98 1:23a Jeremys
 * defined xml reader boss
 * 
 * 9     3/31/98 10:35p Jeremys
 * Added XML reader prefix
 * 
 * 8     3/27/98 9:27a Trevora
 * group and irregualrpolygon bosses implemented
 * 
 * 7     3/26/98 11:21 AM Glennm
 * Added more prefixes. Added ReaderBoss constants.
 * 
 * 6     3/20/98 12:09p Trevora
 * changes made to files necessary to force naming conformity for
 * PageFormat and TableOfContents
 * 
 * 5     3/18/98 2:03 PM Glennm
 * Added IDs for the rest of the Accessors
 * 
 * 4     3/16/98 5:13 PM Glennm
 * Changed IID_IPOMPUBACCESSOR to IID_IPOMPUBLICATIONACCESSOR
 * 
 * 3     3/05/98 10:33a Peterh
 * Added  kRdrTHPrefix
 * 
 * 2     2/23/98 4:15 PM Glennm
 * Changed "Generic" to "Example"
 * 
 * 1     2/23/98 3:05 PM Glennm
 * Adding 'PubConvIDs.h' to
 * '$/Dev/Source/Components/Filters/PubConv/Common/'
 *****************************************************************************/
