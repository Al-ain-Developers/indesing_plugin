//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IAATUtils.h $
//  
//  Owner: Kristina Roberts
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
#ifndef __IAATUtils__
#define __IAATUtils__
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

#include "AATArchID.h"
#include "UnitIDs.h"
#include "IPMUnknown.h"
#include "VAATData.h"

class IReadWriteTest;
class ISequenceItem;
class ITestSession;
class VirtualDataList;
class QADoc;
class QAFile;
class QAPage;
class QARect;
class VAATData;
class IWindow;
class ICoreFilename;
class QA_char_Data;
class QAMeasurement;

//================================================================================================

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IAATUtils : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IAATUTILS };
		

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
		virtual void 		GetFileListUsingExtension(const QAFile *theFolder, ProdString& extension, K2Vector<QAFile> &collection) = 0;
		
		//Sets the build/product settings for an action when those values are kInvalidBuild and kInvalidProductVers.
		//If data points are provided for newBuild and newProdVers, then regardless of current state of build info, the new information
		//will be applied.
		virtual void		UpdateSourceBuildAndProductInfo(ISequenceItem	*item, int32 *newBuild = nil, PMReal *newProdVers = nil) = 0;
		virtual PMString	GetProductString(void) = 0;
		virtual bool16		IsNativeProductType(const PMString &type) = 0;

		// returns true if the two rects are within tolerance of one another's measurements.
		virtual ProdBool		CompareQARects(const QARect& rect1, const QARect& rect2, ProdReal tolerance = .1) = 0;
		// takes in a rect relative to the page, and returns rect relative to the parent spread.
		virtual QARect		PageRectToSpread(const QARect& pageRect, QAPage* page) = 0;
		
		//Measurement mapping
		virtual QAMeasurementType	MapStringToMeasureType(ProdString *str) = 0;
		virtual ProdString	 		MapMeasureTypeToString(QAMeasurementType type) = 0;
		virtual ProdBool				MapStringToMeasurementValue(ProdString textIn, QAMeasurement& valueOut) = 0;
		
		//Given a string value and a key, apply the string to the proper member of the dataList
		virtual void			ApplyTokensToValueList(VirtualDataList *dataList, const ProdString &tag, const ProdString &value) = 0;
		
		//Conversion of AATData Value to String & String to Value
		virtual void		AATDataValueToString(VAATData *dataPtr, ProdString &str) = 0;
		virtual void		StringToAATDataValue(VAATData *dataPtr, const ProdString &str) = 0;
		
		// Compare AATData values
		virtual ProdBool		AATDataEquals(VAATData *param1, VAATData *param2, ProdBool notEquals=kFalse, ProdReal tol = 0.0) = 0;
		virtual ProdBool		AATDataLessThan(VAATData *param1, VAATData *param2, ProdBool orEqualTo=kFalse) = 0;
		virtual ProdBool		AATDataGreaterThan(VAATData *param1, VAATData *param2, ProdBool orEqualTo=kFalse) = 0;
		
		//Load Acceptable Values into a t-data from a param list file - file is relative to qa folder
		virtual void	LoadAcceptableFromFile(VAATData *dataPtr, const ProdString &fileName) = 0;
		
		// Load the Base Session file settings from the saved file
		virtual ProdBool	LoadBaseSessionSettings(ITestSession* applySettingsToMe) = 0;
		
		//Map QADataType to string
		virtual ProdString AATDataTypeToString(VAATData::VirtualType type) = 0;
		virtual VAATData::VirtualType StringToAATDataType(ProdString  &str)  = 0;
		
		//Create a new QADataType from a type String
		virtual VAATData* NewDataFromType(VAATData::VirtualType type) = 0;
		virtual VAATData* NewDataFromTypeString(const ProdString &typeStr) = 0;
		virtual VAATData*	MatchAndConvertData(VAATData::VirtualType type, VAATData *original) = 0;
		
		virtual void		CopyKeyDataList(VirtualDataList* original, IReadWriteTest* destObj) = 0;
		virtual void		CopyKeyDataList(VirtualDataList* original, VirtualDataList* destList) = 0;
		
		//VAATData assignment
		virtual void		AssignValue(VAATData *source, VAATData *dest) = 0;
		
		//String manipulation
		virtual void		FindIndexOfNextNonWhite(const ProdString &input, ProdInt32 &index) = 0;
		virtual void		ParseSeparatedListToVector(K2Vector<ProdString> &destVec, const ProdString& srcStr, PlatformChar sep = ',') = 0;
		virtual ProdString	VectorToSeparatedList(K2Vector<ProdString> sourceVec, PlatformChar sep = ',') = 0;
		virtual void		ReplaceStringSeparator(PMString &sourceStr, PlatformChar sep, PlatformChar newSep) = 0;
		
		virtual ProdBool	ParseEscapeChar(QA_char_Data *charPtr, const ProdString &readStr) = 0;		
		virtual	void		EscapeCharToString(QA_char_Data *charPtr, ProdString &readStr) = 0;
		virtual void		TranslateIfPossible(ProdString &string, PMLocaleId *locale = nil) = 0;
		virtual void		ReplaceAllOfChar(ProdString& string, UTF32TextChar origChar, UTF32TextChar newChar) = 0;
		
		// a simple beep function.
		virtual void		DoBeep() = 0;
		
		// gets app compatiblility flag
		virtual ProdInt32	GetCurrentApplicationCompatibilityFlag() = 0;
		
		//Operations
		virtual ProdReal		PerformMathOperation(const ProdReal param1, const ProdReal param2, const ProdString& theOperator) = 0;
		
		//Verfies that the cfn can be written to...		
		virtual	ProdBool 			CanSave(const IDFile &sysFile) = 0;
		
		//Creates AAT Arch XML Write stream....
		//Caller must release and close the stream
		virtual IXMLOutStream*	CreateXMLOutStream(const IDFile &sysFile, bool16 suppressFailureAlert = kFalse) = 0;

		// All of these Close and Release IXMLOutStream upon success
		// Files of file lists
		virtual ProdBool			WriteTestCaseLibraryFile(IXMLOutStream *s, K2Vector<ProdString> pathList, K2Vector<ProdString> nameList) = 0;
		// File of class list
		virtual ProdBool			WriteClassListFile(IXMLOutStream *s, K2Vector<ClassID> classList) = 0;
		// File of param list
		virtual ProdBool			WriteParamListFile(IXMLOutStream *s, K2Vector<ProdString> paramList) = 0;
		
		virtual bool16			WriteStringKeyValueMap(const QAFile& file) = 0;

		virtual ErrorCode		PackageForPulpo(const QAFile& sessionFile, const QAFile& packageLocation, K2Vector<PMString> &collateralList, bool16 nestedFile = kFalse, PMString saveFolderPath = PMString(""), bool16 collectAllCollateral = kFalse) = 0;
	};


#endif // __IAATUtils__