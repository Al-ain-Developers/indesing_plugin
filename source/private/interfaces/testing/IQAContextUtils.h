//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/interfaces/testing/IQAContextUtils.h $
//  
//  Owner: Shri Amin
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
	#ifndef _IQAContextUtils_
	#define _IQAContextUtils_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "TestID.h"
	#include <boost/function.hpp>
	
	class IWorkspace;

	class IControlView;
	class IDocumentLayer;
	class IGeometry;
	class IScrapSuite;
	class IDocumentPresentation;

	class PMString;
	class QAFile;
	class QASectionSettings;
	class QATest;
	class UIDList;
	class UIDRef;
	class IDataBase;

//================================================================================================

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IQAContextUtils : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IQACONTEXTUTILS };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		virtual void AppendFSLangLabel(PMString* base, PMLocaleId locale) = 0;

		virtual void AppendFSProdLabel(PMString* base, PMLocaleId locale) = 0;

		virtual void AppendHex(PMString* base, int16 number) = 0;

		virtual void AppendLineBreak(PMString* base) = 0;

		virtual void AppendUILabel(PMString* base, PMLocaleId locale) = 0;

		virtual bool16 AreAllItemsInSameHierarchy(const UIDList& list) = 0;

		virtual bool16 CanRunTestInThisContext(QATest* test) = 0;
		
		virtual bool16 CloseAllDocs(void) = 0;
		
		virtual bool16 CloseDoc(UIDRef doc) = 0;
		
		virtual UIDRef ConvertDoc(const QAFile& doc, PMString expectedAlert = kNullString) = 0;
		
		virtual int32 CountOpenDocs(void) = 0;

		virtual PMPoint DerivePMPoint(IGeometry* geometry, PMPoint reference, PMReal distance,
			PMReal angle) = 0;

		virtual double DeriveStdAngle(PMReal angle) = 0;

		virtual bool16 DoesASectionStartHere(UIDRef page) = 0;
		
		virtual PMString ElapsedTime(const PMReal& startTime) = 0;

		virtual void FindInDesignFilesIn(const PMString& directory,
			K2Vector<PMString>& outFileList) = 0;

		virtual UIDRef GetAnyDoc(void) = 0;

		virtual bool16 GetCommandLineArgument(PMString& value,
			const PMString& key) = 0;

		virtual int16 GetFeatureSetID(void) = 0;

		virtual IDocumentPresentation* GetFrontPresentation(UIDRef doc) = 0;

		virtual UIDRef GetLastSpread(IDataBase* db) = 0;

		virtual UIDRef GetLastSpreadLayer(IDataBase* db) = 0;

		virtual UIDRef GetLayout(UIDRef doc) = 0;

		//Gets the maxmium number of threads to use, if "-nthreads [number]"
		//is on the command line.
		virtual bool16 GetNThreads(uint32 *nthreads) = 0;

		virtual PMString GetScriptLabel(UIDRef object) = 0;

		virtual UIDRef GetSection(UIDRef page) = 0;

		virtual IDataBase* GetSessionWorkspaceDatabase(void) = 0;

		virtual UIDRef GetStartingPageOfSection(UIDRef docRef, int32 sectionIndex) = 0;

		virtual IControlView* GetStructureView(UIDRef doc) = 0;

		virtual IDataBase* GetWorkspaceDatabase(IDataBase* dbAssociated) = 0;
	
		virtual PMPoint InnerToPasteboard(UIDRef spread, PMReal x, PMReal y) = 0;

		//This only checks the filename extension (Windows) or file type and creator (Macintosh) = 0; 
		//It doesn't examine the file's contents
		virtual bool16 IsFileTypeInDesign(IDFile file) = 0;

		virtual bool16 IsFillActive(void) = 0;

		virtual bool16 IsInCopy(void) = 0;

		virtual bool16 IsInDesign(void) = 0;

		virtual bool16 IsInDesignServer(void) = 0;

		virtual bool16 IsJapaneseFeatureSet(void) = 0;

		virtual bool16 IsJapaneseOS(void) = 0;

		//Copied from LayerPanelUtils.cpp, which is not public
		virtual int32 IsLayerUsed(IDocumentLayer* docLayer) = 0;
		

		virtual bool16 IsOSX(void) = 0; 

		virtual bool16 IsHeadless() = 0;

		virtual bool16 IsParentSpreadActive(UIDRef item) = 0;

		virtual bool16 IsTestCompatibleWithCurrentContext(int32 flagsForTest) = 0;

		virtual bool16 IsTestSuiteIdleTaskRunning() = 0;

		virtual UIDRef NewDoc() = 0;

		virtual UIDRef NewPage(UIDRef spread) = 0;

		virtual UIDRef NewSpread(UIDRef doc) = 0;

		virtual UIDRef OpenDoc(IDFile& file) = 0;

		virtual PMPoint PageToPasteboard(int32 pageNumber, UIDRef spread, PMReal x, PMReal y) = 0;

		//Returns the UIDRef of the frame of the placed item
		virtual UIDRef Place(IDFile& file, UIDRef spreadLayer, PMReal left, PMReal top) = 0;

		virtual PMString ProcessID(void) = 0;
		
		virtual IControlView* QueryFrontLayoutViewIfVisible(UIDRef doc) = 0;

		virtual IScrapSuite* QueryScrap(UIDRef doc) = 0;

		virtual IWorkspace* QueryWorkspace(IDataBase* db) = 0;

		virtual bool16 SaveAs(IDFile file, UIDRef doc) = 0;

		virtual bool16 SetScriptLabel(UIDRef object, const PMString& label) = 0;

		virtual bool16 SetFrontSpread(UIDRef spread) = 0;

		virtual bool16 SetSectionOptions(UIDRef page, QASectionSettings settings) = 0;

		virtual bool16 SetTool(ClassID tool) = 0;

		virtual bool16 TestViaUIEvents(void) = 0;

		virtual PMString ThreadID(void) = 0;
		
		virtual PMString TimeAndDate(const PMString& prefix = kNullString,
			const PMString& suffix = kNullString) = 0;
	
		virtual void YieldControl(const PMReal& numSeconds = 0,
			#ifdef WINDOWS
			bool16 atLeastOnce = kTrue) = 0;
			#else
			bool16 atLeastOnce = kFalse) = 0;
			#endif

		virtual void YieldControlAuto(void) = 0;
		
		virtual int32 GetCurrentApplicationCompatibilityFlag() = 0;

		virtual void ExecuteTaskInMainThread(boost::function<void()> func) = 0;
	};
		
#endif // _IQAContextUtils_
