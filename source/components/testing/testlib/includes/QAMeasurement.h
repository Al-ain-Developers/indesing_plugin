//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/testlib/includes/QAMeasurement.h $
//  
//  Owner: Ben Park
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
//  
//  This was put into place to centralize all measurements made in the QA Classes.
//  
//========================================================================================

#pragma once
#ifndef __QAMeasurement__
#define __QAMeasurement__

#include "IRulerCoordinatePrefs.h"

#include "UnitIDs.h"

#include "PMRect.h"
#include "IDThreading.h"

#include <map>

class ISpread;
class IUnitOfMeasure;
class QASpread;
class UIDRef;
class IControlView;


typedef IRulerCoordinatePrefs::RulerCoordinateType RulerOrigin;
const RulerOrigin kRulerSpread = IRulerCoordinatePrefs::kRulerPerSpread;
const RulerOrigin kRulerPage = IRulerCoordinatePrefs::kRulerPerPage;
const RulerOrigin kRulerSpine = IRulerCoordinatePrefs::kRulerOnBinding;

/////////////////////////////////////////////////////////////////
//! 
//! DON'T USE THESE TYPES TO DEFINE STATIC OR GLOBAL CONSTANTS!
//! 
//! The values for these types are stored as points; therefore,
//! these types rely on Shuksan's dynamic measurement system to
//! convert values from any specified type to points.  Such
//! constants as described above are initialized very early
//! during startup, when the measurement system is not available.
//! Any resulting assertion failures will cause the application
//! to hang.
//! 
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//!
//!	QAMeasurement:
//!
//!	This was an easy way of doing measurements so that any type could be
//!	specified at any time.
//!
//!
//////////////////////////////////////////////////////////////////

class TESTLIB_DECL QAMeasurement
{
	private:
		PMReal fNumber;
		QAMeasurementType fType;

		static IDThreading::ThreadLocalManagedObject<std::map<QAMeasurementType, PMString> > tl_fNameMap;
		static IDThreading::ThreadLocalManagedObject<std::map<PMString, QAMeasurementType> > tl_fTypeMap;
		static IDThreading::ThreadLocalManagedObject<std::map<QAMeasurementType, QAMeasurementUnit> > tl_fUnitMap;

		static void InitializeStatics(void);
		static IUnitOfMeasure* QueryUnitOfMeasure(QAMeasurementType type);

	public:	
		static QAMeasurementType GetCurrentUnitOfMeasure(const UIDRef& docRef, bool16 bVertical);
		static PMString LookupName(QAMeasurementType type);
		static QAMeasurementType LookupType(const PMString& name);

		QAMeasurement();
		QAMeasurement(const PMReal& num, QAMeasurementType type = kQAPoints);

		PMReal GetValue(QAMeasurementType type = kQAPoints) const;

		PMString GetValueAsString(bool16 showUnits = kFalse,
			QAMeasurementType type = kQAPoints) const;

		PMString GetValueAsString(const QAMeasurementUnit& unit, bool16 translateLabel = kTrue) const;

		void SetValue(const PMReal& num, QAMeasurementType type = kQAPoints);
		
		QAMeasurementType GetOriginalMeasurementType(void) { return fType; }
		void			  SetOriginalMeasurementType(QAMeasurementType theType) { fType = theType; }
		
		// methods for getting a measurement in PB coordinates
		PMReal GetActualMeasurement(const QASpread *spread, bool16 bVertical, int32 pageIndex = -1) const;
		PMReal GetActualMeasurement(ISpread *spread, bool16 bVertical, int32 pageIndex = -1) const;
		PMReal GetActualMeasurement(const UIDRef& pageRef, bool16 bVertical) const;
		// methods for getting a PB measurement in Local coordinates
		PMReal GetLocalMeasurement(const QASpread *spread, bool16 bVertical, int32 pageIndex = -1) const;
		PMReal GetLocalMeasurement(ISpread *spread, bool16 bVertical, int32 pageIndex = -1) const;
		PMReal GetLocalMeasurement(const UIDRef& pageRef, bool16 bVertical) const;
		
		void RoundToNthDecimal(int32 numPlaces);

		//Comparison
		bool16 operator==(const QAMeasurement other) const;
		bool16 operator!=(const QAMeasurement other) const;
};

/////////////////////////////////////////////////////////////////
//!
//!	QAPoint:
//!
//!	Derived from PMPoint, uses QAMeasurement to do the conversions
//!
//!
//////////////////////////////////////////////////////////////////

class TESTLIB_DECL QAPoint : public PMPoint
{
	public:	
		QAPoint() : fType(kQAPoints), PMPoint(0,0) {}
		QAPoint(const PMPoint& point) : fType(kQAPoints), PMPoint (point) {}
		QAPoint(const PMReal& X, const PMReal& Y, QAMeasurementType type = kQAPoints);

		PMReal GetX (QAMeasurementType type = kQAPoints) const;
		PMReal GetY (QAMeasurementType type = kQAPoints) const;
		
		void SetX (const PMReal &num, QAMeasurementType type = kQAPoints);
		void SetY (const PMReal &num, QAMeasurementType type = kQAPoints);

		void SetFromPBCoords(const PMPoint& point, const UIDRef& spreadRef);
		void SetFromSysCoords(const SysPoint &sysPt, QASpread *spread);
		
		PMPoint GetPoint() const;
		
		QAMeasurementType GetOriginalMeasurementType(void) { return fType; }
		void			  SetOriginalMeasurementType(QAMeasurementType theType) { fType = theType; }

		// method for getting the Point in PB coordinates
		PMPoint GetActualPoint(const QASpread *spread, int32 pageIndex = -1) const;
		PMPoint GetActualPoint(ISpread *spread, int32 pageIndex = -1) const;
		PMPoint GetActualPoint(const UIDRef& pageRef) const;
		// method for getting the PB Point in local coordinates
		PMPoint GetLocalPoint(const QASpread *spread, int32 pageIndex = -1) const;
		PMPoint GetLocalPoint(ISpread *spread, int32 pageIndex = -1) const;
		PMPoint GetLocalPoint(const UIDRef& pageRef) const;
		//method for getting system point
		SysPoint GetSystemPoint(const QASpread *spread, IControlView *view, int32 pageIndex = -1) const;
		SysPoint GetSystemPoint(ISpread *spread, IControlView *view, int32 pageIndex = -1) const;
		SysPoint GetSystemPoint(const UIDRef& pageRef, IControlView *view) const;
	protected:
		QAMeasurementType fType;

};

/////////////////////////////////////////////////////////////////
//!
//!	QARect:
//!
//!	Derived from PMRect, uses QAMeasurement to do the conversions
//!
//!
//////////////////////////////////////////////////////////////////

class TESTLIB_DECL QARect : public PMRect
{
	public:	
		QARect() : PMRect(0,0,0,0), fType(kQAPoints)  {}
		QARect(const PMRect& rect) : PMRect (rect), fType(kQAPoints)  {}
		QARect(const PMReal& left, const PMReal& top, const PMReal& right, const PMReal& bottom, 
				QAMeasurementType type = kQAPoints);
		
		PMReal GetLeft (QAMeasurementType type = kQAPoints) const;
		PMReal GetTop (QAMeasurementType type = kQAPoints) const;
		PMReal GetRight (QAMeasurementType type = kQAPoints) const;
		PMReal GetBottom (QAMeasurementType type = kQAPoints) const;
		
		void SetLeft (const PMReal &num, QAMeasurementType type = kQAPoints);
		void SetTop (const PMReal &num, QAMeasurementType type = kQAPoints);
		void SetRight (const PMReal &num, QAMeasurementType type = kQAPoints);
		void SetBottom (const PMReal &num, QAMeasurementType type = kQAPoints);
		
		void	InsetRect(const QARect&otherrect);
		PMRect GetRect() const;
		
		QAMeasurementType GetOriginalMeasurementType(void) { return fType; }
		void			  SetOriginalMeasurementType(QAMeasurementType theType) { fType = theType; }
		
		
		// method for getting the Rect in PB coordinates
		PMRect GetActualRect(const QASpread *spread, int32 pageIndex = -1) const;
		PMRect GetActualRect(ISpread *spread, int32 pageIndex = -1) const;
		PMRect GetActualRect(const UIDRef& pageRef) const;
		// method for getting the PB Rect in local coordinates
		PMRect GetLocalRect(const QASpread *spread, int32 pageIndex = -1) const;
		PMRect GetLocalRect(ISpread *spread, int32 pageIndex = -1) const;
		PMRect GetLocalRect(const UIDRef& pageRef) const;

		bool16 operator!= (const QARect compareTo);//, QARect second);
		bool16 operator== (const QARect compareTo);// , QARect second);
		QARect& operator+= (const QARect &otherRect);// , QARect second);
		QARect operator+ (const QARect &otherRect);// , QARect second);
		
		//void 	Exclude(const QARect rectToExclude);
		
	protected:
		PMReal RoundToThousandths(PMReal theReal);
		QAMeasurementType fType;
};



#endif //__QAMeasurement__