//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/testlib/includes/qafile.h $
//  
//  Owner: Kevin Rice
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
#ifndef __QAFile__
#define __QAFile__

#include "FileUtils.h"

#ifndef MACINTOSH
	#define kFolderSep	'\\'
#else
	#define	kFolderSep	':'
#endif

class TESTLIB_DECL QAFile
{	
	public:
		typedef object_type data_type;
	//-----
	//Enum
	enum QAFolderType
	{
		kQAQAFolder,				//Relative to the current QA folder
		kQABenchmark,				//Relative to QA:Benchmark: folder
		kQABenchmarkData,			//Relative to QA:Benchmark:Data: folder
		kQABenchmarkTestFiles,		//Relative to QA:Benchmark:TestFiles: folder
		kQABenchmarkMktgFiles,		//Relative to QA:Benchmark:MktgFiles: folder
		kQATestFileFolder,			//Relative to QA:Testfile: folder
		kQARealLogs,				//Relative to QA:logs: folder
		kQALogs,					//Relative to QA:logs: folder, subject to
										//further nesting to support multiple
										//instances or different applications
		kQAStatus,					//Relative to QA:Status: folder
		kQASnapshots,				//Relative to QA:Snapshots: folder
		kQATrashBase,				//Relative to QA:trash: folder; no support
										//for network or dynamic variants
		kQATrash,					//Relative to QA:trash: folder, subject to
										//further nesting to support multiple
										//instances or threads; includes support
										//for network or dynamic variants
		kQAAppFolder,				//Relative to application folder
		kQAAppInstallationFolder,	//Relative to app installaion folder. On Mac, three level above app folder 
		kQANotRelative,				//Use for completely specified paths
		kQAWorkFlow,				//Relative to QA:workflow: folder - 7/25/01
		kQAAppLocalCachedDataFolder,//Relative to local cached application data folder
		kQAAppRoamingDataFolder,	//Relative to roaming application data folder
		kQATestSetsFolder,			//Relative to QA:Test Sets: folder
		kQARoundTripFolder,			//Relative to QA:qatrash:RoundTrip
		kQAPrefs,					//Relative to QA:Prefs
		kQAScripts,					//Relative to QA:Scripts (for scripts tests,
										//not the Scripts folder for the script palette)
		kQATrashForceLocal,
		kQASharedFolder,
		kQAIDFileLogs				//Relative to the folder where IDFileLogs are created
	};
	
	enum{
	#ifdef WINDOWS
	kLineBreakChar = '\n',
	#else
	kLineBreakChar = '\r'
	#endif
	};
	
	//-----
	//Constructors
	QAFile();
	QAFile(const IDFile& newFile);
	QAFile(const PMString& pathname, QAFolderType relativeTo = kQATestFileFolder);
	QAFile(const QAFile& other);
	QAFile(const PMString& filename, const QAFile& filepath); 
	QAFile(const PMString& filename, const IDFile& filepath); 
	QAFile &operator =(const QAFile& other);
	bool16	operator ==(const QAFile& other);
	bool16	operator !=(const QAFile& other);
	~QAFile();
	
	//-----
	//Accessors
	bool16 Set(const PMString& pathname, QAFolderType relativeTo = kQATestFileFolder,
		bool16 makeFolder = kTrue);
	void	Set(const IDFile& sysFile);
	
	void	Clear(); // clears the QAFile's information
	
	//------
	// File Settings
	QAFolderType	GetRelativeTo(void) const { return fRelativeSetting; }
	
	PMString		GetOriginalPath(void) const { return fOrigPath; }
	
	//-----
	//Util
	bool16 CanOpen(FileUtils::Access access = FileUtils::kReadWrite,
		bool16 bCheckLocalReplica = kFalse) const;
	bool16 Exists(bool16 bCheckLocalReplica = kFalse) const;
	bool16 IsValid() const;
	void   DeleteFile() const;
	
	const IDFile& GetSysFile() const { return (fIDFile); }
	const IDFile& GetIDFile() const { return (fIDFile); } // same as above, but with appropriate new name
	const PMString GetAsPMString() const;
	bool16 CopyFileToPMString( PMString *buffer ) const;
	
	void GetDirectory(IDFile& theDirectory);

	//-----
	//Conversion operators
	operator const IDFile&() const {return(fIDFile);}

	static IDFile GetDefaultQAFolder();

	//------
	//Workgroup methods
	bool16 IsManagedLocation() const; 
	bool16 IsManagedAsset() const;

	//------
	//Public methods for Dynamic QAFile
	static bool16 DynamicQAFileFolderDefined(QAFolderType eFolder);


	private:
	
	bool16 AppendPathName(const PMString& pathName, bool16 makeFolder = kTrue);

	CharCounter FindSeparator(const PMString& path, CharCounter position = 0);
	
	bool16 CreateDirectoriesIfNeeded(void);
	
	void SetAppFolder(const PMString& appRelativePath = PMString(""));
	void SetAppInstallationFolder(const PMString& appRelativePath = PMString(""));
	void SetAppLocalCachedDataFolder(const PMString& appDataRelativePath = PMString(""));
	void SetAppRoamingDataFolder(const PMString& appDataRelativePath = PMString(""));
	void SetIDFileLogsFolder(const PMString& IDFileLogsRelativePath = PMString(""));
	void SetQAFolder(bool16 bAllowNetwork = kTrue);
	void SetLogsFolder();
	void SetBenchmarkDataFolder();
	
	void TranslatePathForPlatform(PMString& path);

	IDFile fIDFile;
	bool16 fCouldConstructPath;
	QAFolderType	fRelativeSetting;
	PMString		fOrigPath;
	

	//Support for dynamically reading QAFile paths from a configuration file.
	static void EnableDynamicQAFile();

	void SetDynamicLocation(QAFolderType relativeTo);

	enum eDynamicQAFile { kNotSet = 0, kDynamicQAFile, kStaticQAFile };
	static eDynamicQAFile ts_fDynamicQAFile;

	static PMString ts_fDynamicTestFilesFolder;
	static PMString ts_fDynamicTrashFolder;
	static PMString ts_fDynamicBenchmark;
	static PMString ts_fDynamicBenchmarkData;
	static PMString ts_fDynamicBenchmarkTestFiles;
	static PMString ts_fDynamicBenchmarkMktgFiles;
	static PMString ts_fDynamicSharedFolder;

	//Support for "special paths."
	static void EnableForceSpecialPathsToNetwork();
	static bool16 IsForceSpecialPathsToNetworkEnabled();

	enum eForceSpecialPathsToNetwork { kUninitialized = 0, kSpecialPaths, kOrdinaryPaths };
	static eForceSpecialPathsToNetwork ts_fForceSpecialPathsToNetwork;
};



#endif //__QAFile__