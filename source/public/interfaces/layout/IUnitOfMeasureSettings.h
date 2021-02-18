//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IUnitOfMeasureSettings.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IUNITOFMEASURESETTINGS__
#define __IUNITOFMEASURESETTINGS__

/** Some minumum and maximum values for SetPointsPerInch, SetHorzCustomPoints and SetVertCustomPoints
*/
#define kMinPointsPerInch	60.0
#define kMaxPointsPerInch	80.0
#define kMinCustomPoints	4.0
#define kMaxCustomPoints	256.0


#ifndef __ODFRC__   // when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "MeasurementSystemID.h"

//========================================================================================
// CLASS IUnitOfMeasureSettings
//========================================================================================

/** 
	Interface that holds all the unit of measure settings. Installed on kWorkspaceBoss and kDocWorkspaceBoss.

	Measurement systems themselves may be installed via service providers. All of the Get methods in this
	class check for missing service providers and return points as a default.
*/
class IUnitOfMeasureSettings : public IPMUnknown
{
public:
 	enum { kDefaultIID = IID_IUNITOFMEASURESETTINGS };
 
	/**	Sets the class id of all the measurement systems. Used at new document time.
		@param bossId - the classID of the measurement system. e.g. kPointsBoss, kMillimetersBoss, etc.
	 */
	virtual void		Init(const ClassID& xBossId, const ClassID& yBossId, const ClassID& textBossId, 
							 const ClassID& textSizeBossId, const ClassID& printUnitsBossId,
							 const ClassID& lineUnitsBossId, const PMReal customHPoints = 12.0,
							 const PMReal customVPoints = 12.0, const PMReal keyNudgeIncPts = 1.0,
							 const PMReal pointsPerInch = 72.0) = 0;

// ----- Accessors
public:
	/**	Sets the class id of the x measurement system. Used by horizontal rulers and horizontal measurement editboxes (XMeasureEditBoxWidget).
		@param bossId - the classID of the measurement system. e.g. kPointsBoss, kMillimetersBoss
	 */
	virtual void		SetXUnitOfMeasure(const ClassID& bossId) = 0;

	/**	Gets the class id of the x measurement system.
		@return ClassID 
	 */
	virtual ClassID		GetXUnitOfMeasure() const = 0;

	/**	Gets the index of the x unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetXUnitOfMeasureIndex() = 0;
	
	/**	Returns the class id of the y measurement system. Used by vertical rulers and vertical measurement editboxes (YMeasureEditBoxWidget).
		@param bossId - the classID of the measurement system. e.g. kPointsBoss, kMillimetersBoss
	 */
	virtual void		SetYUnitOfMeasure(const ClassID& bossId) = 0;

	/**	Gets the class id of the y measurement system.
		@return ClassID 
	 */
	virtual ClassID		GetYUnitOfMeasure() const = 0;

	/**	Gets the index of the y unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetYUnitOfMeasureIndex() = 0;

	/**	NOTE: This measurement system is used in J feature set only, see SetTextSizeUnitOfMeasure. Sets the class id of the text measurement system. Used by text measurement editboxes (TextMeasureEditBoxWidget).
		@param bossId - the classID of the measurement system. e.g. kPointsBoss
	 */
	virtual void		SetTextUnitOfMeasure(const ClassID& bossId) = 0;

	/**	NOTE: This measurement system is used in J feature set only, see GetTextSizeUnitOfMeasure. Gets the class id of the text measurement system.
		@return ClassID 
	 */
	virtual ClassID		GetTextUnitOfMeasure() const = 0;

	/**	NOTE: This measurement system is used in J feature set only, see GetTextUnitOfMeasureIndex. Gets the index of the text unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetTextUnitOfMeasureIndex() = 0;

	/**	Sets the class id of the text size measurement system. Used by text size measurement menus (TextSizeMeasureEditBoxWidget).
		@param bossId - the classID of the measurement system. e.g. kPointsBoss, kQBoss
	 */
	virtual void		SetTextSizeUnitOfMeasure(const ClassID& bossId) = 0;

	/**	Gets the class id of the text size measurement system.
		@return ClassID 
	 */
	virtual ClassID		GetTextSizeUnitOfMeasure() const = 0;

	/**	Gets the index of the text size unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetTextSizeUnitOfMeasureIndex() = 0;

	/**	NOTE: This measurement system is UNUSED. Sets the class id of the print measurement system. Used by bleed setting for Print dialog?
		@param bossId - the classID of the measurement system. e.g. kPointsBoss, kMillimetersBoss
	 */
	virtual void		SetPrintUnitOfMeasure(const ClassID& bossId) = 0;

	/**	NOTE: This measurement system is UNUSED. Gets the class id of the print measurement system. 
		@return ClassID 
	 */
	virtual ClassID		GetPrintUnitOfMeasure() const = 0;

	/**	NOTE: This measurement system is UNUSED. Gets the index of the print unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetPrintUnitOfMeasureIndex() = 0;
	
	/**	Sets the class id of the line weight measurement system. Used by stroke weight menus and edit boxes (LineWtMeasureEditBoxWidget)
		@param bossId - the classID of the measurement system. e.g. kPointsBoss
	 */
	virtual void		SetLineUnitOfMeasure(const ClassID& bossId) = 0;

	/**	Gets the class id of the line weight measurement system. Typically used by stroke weight controls.
		@return ClassID 
	 */
	virtual ClassID		GetLineUnitOfMeasure() const = 0;

	/**	Gets the index of the line weight unit of measure (measurement systems are service provider based).
	    Useful as the parameter in a call to IUnitOfMeasure->QueryUnitOfMeasure(index).
		@return int16
	 */
	virtual int16		GetLineUnitOfMeasureIndex() = 0;
	
	/**	Sets the value to use for horizontal rulers when using kRulerCustomMSBoss. Typically user would
		set to value of leading grid on the page. Determines where major tickmarks are drawn.
		@param PMReal - Value in points to use for kRulerCustomMSBoss.
	 */
	virtual void        SetHorzCustomPoints(const PMReal customPoints) = 0;

	/**	Returns the value to use for horizontal rulers when using kRulerCustomMSBoss.
		@param PMReal
	 */
	virtual PMReal       GetHorzCustomPoints() const = 0;

	/**	Sets the value to use for vertical rulers when using kRulerCustomMSBoss. Typically user would
		set to value of leading grid on the page. Determines where major tickmarks are drawn.
		@param PMReal - Value in points to use for kRulerCustomMSBoss.
	 */
	virtual void        SetVertCustomPoints(const PMReal customPoints) = 0;

	/**	Returns the value to use for vertical rulers when using kRulerCustomMSBoss.
		@param PMReal
	 */
	virtual PMReal       GetVertCustomPoints() const = 0;

	/**	Sets the amount for keyboard nudging for various action IDs (e.g. kNudgeUpActionID).
		@param PMReal - Value in points to use when nudging objects.
	 */
	virtual void        SetKeyNudgeInc(const PMReal keyNudgeIncPts) = 0;

	/**	Returns the amount (in points) to use for keyboard nudging for various action IDs (e.g. kNudgeUpActionID).
		@return PMReal
	 */
	virtual PMReal      GetKeyNudgeInc() const = 0;

	/**	Sets the value to use for points-based custom points per inch. Typically this is 72.0, 
		but may vary between kMinPointsPerInch and kMaxPointsPerInch.
		@param PMReal - Value in points to use for kPointsBoss, kPicasBoss, and kRulerCustomMSBoss.
	 */
	virtual void		SetPointsPerInch(const PMReal pointsPerInch) = 0;

	/**	Returns the value in use for points per inch used for the points-based measurement systems:
		kPointsBoss, kPicasBoss, and kRulerCustomMSBoss. Typically defaults to 72.0.
		@return PMReal
	 */
	virtual PMReal		GetPointsPerInch() const = 0;
};
#endif

#endif
