//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/interfaces/testing/UnitIDs.h $
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
#ifndef __UnitIDs__
#define __UnitIDs__

#pragma export on

//If you add a QAMeasurementType, add one or more matching QAMeasurementUnits.
enum QAMeasurementType 
	{
	kQAInvalidType = -1,
	kQAPoints,
	kQAPicas,
	kQAInches,
	kQAMillimeters,
	kQACentimeters,
	kQACiceros,
	kQAHa_Units,
	kQA_Q_Units,
	kQAAgates,
	kQAU_Units,
	kQABai_Units,
	kQAMils_Units,
	kQAInchesDecimal,
	kQAAmericanPoints,
	kQAPixels,
	kQACubits,	// DEBUG only, doesn't ship
	kQACustom,
	kQANumMeasurementTypes
	};

//This class is used to translate between QAMeasurementTypes and IUnitOfMeasure,
//via fBoss, and it is used by one or more tests.
class TESTLIB_DECL QAMeasurementUnit
	{
	public:

   	typedef base_type data_type;
   	
   	ClassID fBoss;
   	
   	bool16 fDebugOnly;

	bool16 fSplitValue; //1p6 vs. 1.5p

	QAMeasurementType fUnitType;

	const char* fUnitLabel;

	QAMeasurementUnit(QAMeasurementType unitType, const char* unitLabel,
			ClassID boss, bool16 splitValue = kFalse, bool16 debugOnly = kFalse) :
			fUnitType(unitType), fUnitLabel(unitLabel), fBoss(boss),
			fSplitValue(splitValue), fDebugOnly(debugOnly)
		{}

	QAMeasurementUnit(void) :
			fUnitType(kQAPoints), fUnitLabel(""), fBoss(kInvalidClass),
			fSplitValue(kFalse), fDebugOnly(kFalse)
		{}
		//This is to allow collections to be built.

	QAMeasurementUnit(const QAMeasurementUnit& other) :
			fUnitType(other.fUnitType), fUnitLabel(other.fUnitLabel),
			fBoss(other.fBoss), fSplitValue(other.fSplitValue),
			fDebugOnly(other.fDebugOnly)
		{}
	};

//Agate
TESTLIB_DECL extern const QAMeasurementUnit kUnitAg;

TESTLIB_DECL extern const QAMeasurementUnit kUnitAgate;

TESTLIB_DECL extern const QAMeasurementUnit kUnitAgates;

//American Point
TESTLIB_DECL extern const QAMeasurementUnit kUnitAmericanPoints;

TESTLIB_DECL extern const QAMeasurementUnit kUnitAPLower;

//Bai
TESTLIB_DECL extern const QAMeasurementUnit kUnitBai;

TESTLIB_DECL extern const QAMeasurementUnit kUnitBaiLower;

//Centimeter
TESTLIB_DECL extern const QAMeasurementUnit kUnitCentimeter;

TESTLIB_DECL extern const QAMeasurementUnit kUnitCentimeters;

TESTLIB_DECL extern const QAMeasurementUnit kUnitCm;

//Cicero
TESTLIB_DECL extern const QAMeasurementUnit kUnitC;

TESTLIB_DECL extern const QAMeasurementUnit kUnitCicero;

TESTLIB_DECL extern const QAMeasurementUnit kUnitCiceros;

//Cubit
TESTLIB_DECL extern const QAMeasurementUnit kUnitCubits;

//Custom
TESTLIB_DECL extern const QAMeasurementUnit kUnitCustom;

//Ha
TESTLIB_DECL extern const QAMeasurementUnit kUnitH;

TESTLIB_DECL extern const QAMeasurementUnit kUnitHa;

//Inch
TESTLIB_DECL extern const QAMeasurementUnit kUnitI;

TESTLIB_DECL extern const QAMeasurementUnit kUnitIn;

TESTLIB_DECL extern const QAMeasurementUnit kUnitInch;

TESTLIB_DECL extern const QAMeasurementUnit kUnitInches;

TESTLIB_DECL extern const QAMeasurementUnit kUnitInchMark;

//Inch Decimal
TESTLIB_DECL extern const QAMeasurementUnit kUnitInchesDecimal;

//Mil
TESTLIB_DECL extern const QAMeasurementUnit kUnitMils;

TESTLIB_DECL extern const QAMeasurementUnit kUnitMilsLower;

//Millimeter
TESTLIB_DECL extern const QAMeasurementUnit kUnitMillimeter;

TESTLIB_DECL extern const QAMeasurementUnit kUnitMillimeters;

TESTLIB_DECL extern const QAMeasurementUnit kUnitMm;

//Pica
TESTLIB_DECL extern const QAMeasurementUnit kUnitP;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPica;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPicas;

//Point
TESTLIB_DECL extern const QAMeasurementUnit kUnitPoint;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPoints;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPt;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPts;

// Pixels

TESTLIB_DECL extern const QAMeasurementUnit kUnitPixels;

TESTLIB_DECL extern const QAMeasurementUnit kUnitPixels;

//Q
TESTLIB_DECL extern const QAMeasurementUnit kUnitQ;

//U
TESTLIB_DECL extern const QAMeasurementUnit kUnitU;

TESTLIB_DECL extern const QAMeasurementUnit kUnitULower;

#pragma export off

#endif 	// __UnitIDs__
