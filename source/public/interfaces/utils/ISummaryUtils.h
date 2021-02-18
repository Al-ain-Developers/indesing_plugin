//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/ISummaryUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ISummaryUtils__
#define __ISummaryUtils__

#include "GenericSettingsID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class IGenericSettings;
class IGenericSettingsGroup;
#include "IGenericSettingsAttribute.h"
#include "IGenericSettingsOutput.h"


/**	A helper interface for use with IGenericSettings.
	@see also IGenericSettings
*/
class ISummaryUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISUMMARYUTILS };

	/**	Generates a human text summary from the specified settings.
		@param pSettings specifies the settings from which to generate the summary text.
		@param strResult is where the resulting summary text string is returned.
	*/
	virtual void GenerateHumanTextSummary( IGenericSettings* pSettings, PMString& strResult ) = 0;

	/**	Export the specified settings to a text file.
		@param pSettings specifies the settings from which to generate the summary text for export.
		@param strDefaultFilename specifies the default filename to use.
		@param strExportDialogTitle specifies the title for the export dialog.
		@param strFileType specifies the string representing the default file type.
		@param strFileExtension specified the file extension string.
	*/
	virtual void ExportHumanTextSummary( IGenericSettings* pSettings,
										const PMString&   strDefaultFilename,
										const PMString&   strExportDialogTitle,
										const PMString&   strFileType,
										const PMString&   strFileExtension ) = 0;

	/**	Write the settings to a file.
		@param pSettings specifies the settings to write.
		@param pStrategy the output strategy to use
		@see also IGenericSettingsOutputStragegy
		@param fileTarget specifies a IDFile to write to.
	*/
	virtual void WriteToFile( IGenericSettings* pSettings, IGenericSettingsOutputStrategy* pStrategy, IDFile& fileTarget ) = 0;

	//________________________________________________________________________________________
	// Followings are methods for Building Generic Settings Objects
	//________________________________________________________________________________________
	
	/**	Add an integer number specified by nValue to the settings group.
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param nValue specifies the value to add as number.
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddNumber( IGenericSettingsGroup* pGroup, const char* pszName, int32 nValue, bool16 bRelevant = kTrue ) = 0;

	/**	Add a floating-point number specified by nValue to the specified settings group.
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param nValue specifies the floating-point value to add as number.
		@param nDigits specifies the desired number of digits for format the number.
		@param bRound if true the nValue is rounded.
		@param bEliminateZeros if true trailing zeros are eliminated
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddNumber( IGenericSettingsGroup* pGroup, const char* pszName, const PMReal& nValue, int32 nDigits = -1, bool16 bRound = kFalse, bool16 bEliminateZeros = kFalse, bool16 bRelevant = kTrue ) = 0;

	/**	Add a number specified by nValue with unit to the specified settings group. 
		The unit is specified with unitString and should be translated.
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param unitString is the unit string.
		@param nValue specifies the floating-point value to add as number.
		@param nDigits specifies the desired number of digits to format the number.
		@param bRound if true the nValue is rounded.
		@param bEliminateZeros if true trailing zeros are eliminated
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddNumberUnit( IGenericSettingsGroup* pGroup, const char* pszName, const PMString& unitString, const PMReal& nValue, int32 nDigits = -1, bool16 bRound = kFalse, bool16 bEliminateZeros = kFalse, bool16 bRelevant = kTrue ) = 0;

	/**	Add "On" or "Off" value to the specified settings group. 
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param bOn if true "On" is added otherwise "Off" is added.
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddOnOff( IGenericSettingsGroup* pGroup, const char* pszName, bool16 bOn, bool16 bRelevant = kTrue ) = 0;

	/**	Add "Yes" or "No" value to the specified settings group. 
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param bYes if true "Yes" is added otherwise "No" is added.
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddYesNo( IGenericSettingsGroup* pGroup, const char* pszName, bool16 bYes, bool16 bRelevant = kTrue ) = 0;

	/**	Add a string data to the specified settings group. 
		@param pGroup specifies the settings group to add string to.
		@param pszName specifies the name for this value.
		@param bFirst if true pszStr1 is used. Otherwise pszStr2 is used.
		@param pszStr1 specifies string 1
		@param pszStr2 specifies string 2
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddString( IGenericSettingsGroup* pGroup, const PMString& pszName, bool16 bFirst, const PMString& pszStr1, const PMString& pszStr2 ) = 0;

	/**	Add a string data to the specified settings group. 
		@param pGroup specifies the settings group to add string to.
		@param pszName specifies the name for this value.
		@param pszValue is the string
		@param bTranslate true if the string should be translated.
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddString( IGenericSettingsGroup* pGroup, const PMString& pszName, const PMString& pszValue, bool16 bRelevant = kTrue ) = 0;

	/**	Add a string with default value to the settings group. 
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param strValue
		@param pszDefault
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@param bTranslateNonDefault
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddStringDefault( IGenericSettingsGroup* pGroup, const PMString& pszName, const PMString& strValue, const PMString& pszDefault, bool16 bRelevant = kTrue, bool16 bTranslateNonDefault = kTrue ) = 0;

	/**	Add a floating-point value with unit to the specified setting group.
		Converts units as appropriate.
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param nValue
		@param nWidgetBoss
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddRealUnit( IGenericSettingsGroup* pGroup, const char* pszName, const PMReal& nValue, ClassID nWidgetBoss, bool16 bRelevant = kTrue ) = 0;

	/**	Add a percent value to the specified settings group.
		@param pGroup specifies the settings group to add number to.
		@param pszName specifies the name for this value.
		@param nValue specifies the percent value.
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddPercent( IGenericSettingsGroup* pGroup, const char* pszName, const PMReal& nValue, bool16 bRelevant = kTrue ) = 0; 

	/**	Convert from a value to a unit string.
		@param widgetBoss the unit widget class to use for the conversion
		@param value specifies the value to convert
		@return a formatted unit string.
	*/
	virtual PMString ValueToUnitString(ClassID widgetBoss, const PMReal& value) = 0;

	//________________________________________________________________________________________
	// Higher-level summarization utilties.
	//________________________________________________________________________________________

	/** Add summary text for the mark weight to the specified settings group
		@param pGroup specifies the settings group to add number to.
		@param pszLabel specifies the name of the mark weight
		@param nWeight is the value
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddMarkWeight( IGenericSettingsGroup* pGroup, const char* pszLabel, const PMReal& nWeight ) = 0;

	/** Add summary text for bleeds to the specified group
		@param pGroup specifies the settings group to add number to.
		@param bSpreads controls the name of the bleeds
		@param nTop specifies the top bleed amount
		@param nBottom specifies the bottom bleed amount
		@param nLeft specifies the left bleed amount
		@param nRight specifies the right bleed amount
		@param bRelevant if true the specified value is used as given. If false, the value is ignored.
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual void AddBleeds( IGenericSettingsGroup* pGroup, bool16 bSpreads, const PMReal& nTop, const PMReal& nBottom, const PMReal& nLeft, const PMReal& nRight, bool16 bRelevant = kTrue ) = 0;

	/** Add summary text for the specified flattener style for the settings group.
		@param pGroup specifies the settings group to add number to.
		@param flattenerStyleUID is the flattener style UID
		@return a interface pointer to IGenericSettingsAttribute that is added to the pGroup
		for this value.
	*/
	virtual IGenericSettingsAttribute* AddFlattenerStyle(IGenericSettingsGroup* pGroup, UID& flattenerStyleUID ) = 0;

	/**	Get Pcompression quality from the specified compression type.
		@param nCompression specifies the type of compression.
		@param bUsingMono if true monochrome image type is used.
		@return the compression quality. 
	*/
	virtual int32 QualityFromCompression( int32 nCompression, bool16 bUsingMono = kFalse ) = 0;

	/**	Get compression type from the specified compression quality
		@param nCompression is the compression quality
		@param bUsingMono if true monochrome image type is used
		@return the compression type.
	*/
	virtual int32 TypeFromCompression( int32 nCompression, bool16 bUsingMono = kFalse ) = 0;
};


#endif	// __ISummaryUtils__
