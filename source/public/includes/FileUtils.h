//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FileUtils.h $
//  
//  Owner: Robin_Briggs
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
//========================================================================================

#pragma once
#ifndef __FileUtils__
#define __FileUtils__

class IPMStream;
class PMString;
class SysFileList;
#include <string>
#include "AppInfo.h"
#include "LocaleSetting.h"

class PUBLIC_DECL FileUtils {
public:
#ifdef DEBUG
	// in a debug build, get the path to a file in the QA:Logs: folder.
	// will create the QA and Logs folders if none exist.
	static PMString GetLogFilePath(const PMString& fileName);
#endif
		// returns the directory seperator for the system
	static char   GetDirectorySeperator();
		// Set the application directory.
	static bool16 SetAppFolder(SysConnection appResourceHandle = nil);
		// Return the file descriptor of the application directory
	static bool16 GetAppFolder(IDFile *appFolder);
		// Return the pathname for the application directory.
	static bool16 GetAppFolder(PMString *appFolder);
		// Return the full path for the application.
	static bool16 GetAppPath(IDFile *appPath);
		// Find a specified sub-folder of the application folder. 
		// Sub-folder is specified by name.
		// NOTE!  This function will return kTrue with a valid IDFile even
		//   if the folder does not exist.  It does not create the sub-folder for you.
	static bool16 GetAppSubFolder(IDFile *result, const PMString& subFolderName);
        // Return the current user's roaming directory with appended folder paths. It wont create the folder if it doesnt exist
    static bool16 GetUserRoamingFolder(IDFile *result, const PMString& appFolder, const PMString& subFolderName);

	/**
	Finds a specified sub-folder of the local cached application data folder.  Creates the sub-folder
	if it doesn't already exist.  This is designed for large data caches that you would not want to roam from
	machine to machine in a roaming profiles environment on Windows, and for data that can be easily
	regenerated if deleted. 
	On Windows XP, for example, this might return:
	"%USERHOME%\Local Settings\Application Data\Adobe\InDesign\Version x.y\en_US\Caches\subFolderName"
	On Macintosh, for example, this might return:
	"~/Library/Caches/Adobe InDesign/Version x.y/en_US/subFolderName"
	@param  result	OUT IDFile of the sub folder within the local cached data folder.
	@param  subFolderName	IN Subfolder within the local cached data folder to return.
	@see GetAppRoamingDataFolder
	@see AppendLocalizedFolder
	*/
	static bool16 GetAppLocalCachedDataFolder(IDFile *result, const PMString& subFolderName);

	/**
	Finds a specified sub-folder of the roaming application data folder.  Creates the sub-folder
	if it doesn't already exist.  This is designed for "normal" preference data that you would want to roam from
	machine to machine in a roaming profiles environment on Windows.
	On Windows XP, for example, this might return:
	"%USERHOME%\Application Data\Adobe\InDesign\Version x.y\en_US\subFolderName"
	On Macintosh, for example, this might return:
	"~/Library/Preferences/Adobe InDesign/Version x.y/en_US/subFolderName"
	@param  result	OUT IDFile of the sub folder within the roaming data folder.
	@param  subFolderName	IN Subfolder within the roaming data folder to return.
	@see GetAppLocalCachedDataFolder
	@see GetPresetsFolder
	@see AppendLocalizedFolder
	*/
	static bool16 GetAppRoamingDataFolder(IDFile *result, const PMString& subFolderName);

		// Find a specified sub-folder of the application document folder. 
		// Sub-folder is specified by name. User's unnamed files go here.
	static bool16 GetAppDocumentFolder(IDFile *result, const PMString& subFolderName);
		// Find a specified sub-folder of the application document folder. 
		// Sub-folder is specified by name. The Recovery directory goes here
	static bool16 GetRecoveryFolder(IDFile *result, const PMString& subFolderName);
		// Find a specified sub-folder of the user dictionaries folder. 
		// Creates the folder if it doesn't already exist.
		// Sub-folder is specified by name. The user dictionaries files go here.
	static bool16 GetUserDictionariesFolder(IDFile *result, const PMString& subFolderName);

		// Set the current working directory to the target file descriptor
	static bool16 SetCurrentFolder(const IDFile& targetFolder);
		// Return the file descriptor of the current working directory
	static bool16 GetCurrentFolder(IDFile *currentFolder);

		// Append pathToAppend onto the end of originalPath.
	static void AppendPath(IDFile *originalPath, const PMString& pathToAppend);
		// Get the filename out of the IDFile.
	static void GetFileName(const IDFile& fSpec, PMString& fileName);
	static void GetFileName(const PMString& pathStr, PMString& fileName);

		// Compare the two file names for equality.
	static bool16 IsEqual(const IDFile& file1, const IDFile& file2);
	
        // Does not actually swap the files, but simply moves file1 to file2. Returns false if operation fails.
	static bool SwapFiles(const IDFile& file1, const IDFile& file2);
	
	/**
	Converts an IDFile to a system path string.
	@param  file	IN IDFile to convert to a string.
	@param  pathStr	OUT Resulting path string.\\
			On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
			On the mac, the path is an HFS path: "OSX:Applications:Adobe InDesign CS2".
	@see PMStringToIDFile
	*/
	static void IDFileToPMString(const IDFile& file, PMString& pathStr);
	
	/** 
	Converts from a system path string to an IDFile.
	@param  pathStr	IN String containing the path to convert to an IDFile.\\
					   On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
					   On the Mac, the path is an HFS path: "OSX:Applications:Adobe InDesign CS2".
	@param  file	OUT Resulting IDFile object.
	@see IDFileToPMString
	*/
	static void PMStringToIDFile(const PMString& pathStr, IDFile& file);

	/**
	Converts an IDFile to a system path string.
	@param  file	IN IDFile to convert to a string.
	@return Resulting path string.
			On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
			On the mac, the path is an HFS path: "OSX:Applications:Adobe InDesign CS2".
	@see PMStringToSysFile
	*/
	static PMString SysFileToPMString(const IDFile& file);

	/** 
	Converts from a system path string to an IDFile.
	@param  pathStr	IN String containing the path to convert to an IDFile.\\
					   On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
					   On the Mac, the path is an HFS path: "OSX:Applications:Adobe InDesign CS2".
	@return Resulting IDFile object.
	@see SysFileToPMString
	*/
	static IDFile PMStringToSysFile(const PMString& pathStr);
		
	/**
	Convert from a IDFile to a standard file URL.           
	@param  fSpec a IDFile (System specifc file system path on the mac this is a wrapper around the FSSpec on the PC its a standard path).
			The PC can point to eather a local file("c:\mydir\myfile") or a file on a remote host ("\\myhost\mydir\myfile").
			On the Mac all remote files are accessed via mounted volumes so all SysFiles are local
	@return Returns a file url to the sys file.
	@see FileURLToSysFile
	note post dragontail this should be fixed to return a std::string
	*/
	static PMString SysFileToFileURL(const IDFile& fSpec);
	
	/**
		Convert from a fully qualified path name to a standard file URL (file://).
		@param fileName On the PC the filename string will be a system path like "C:\my programs\adobe\indesign.exe" or 
						a UNC path like "\\myServer\mydir\myfile.txt"
						on the mac the string will be a path made up of FSspec path names (31 byte limit), this path might not 
						look quite correct but it should be in platform encodeing
						mac path: "My HD:Applications:Adobe:InDesign CS"	 DON"T PASS RAW UTF16 in here!
		@return a valid file URL.
		@see FileURLToPMString
		note: Post Dragontail this should be fixed to return a std::string
	*/
	static PMString PMStringToFileURL(const PMString& fileName);

	/**
		Converts a string into URL encodeing, basicly does a PMString->UTF8Encodeing->URLEncodeing
		@param str the string to convert into URL encodeing
		@return the string in url encodeing
		@see URLToPMString
		note: Post Dragontail this should be fixed to return a std::string
	*/ 
	static PMString PMStringToURL(const PMString& str);

	/** 
		URLToPMString takes a URL and decodes it and returns the string this function is basilcy
		URLToUTF8Encodeing and then a UTF8EncodeingToWideString.  The second transformation is only done if needed
		Note any part of a URL can be passed in.
		@param URL string to convert from URL encodeing to a string
		@return The string encodeing 
		@see PMStringToURL
	*/
	static PMString URLToPMString (const std::string &URL);
	
	/**
		UTF8ToURL converts from a UTF8 encoded string to a URLencoded string
		@param str is the UTF8 encoded string
		@param kSeparator is file seperator in the UTF8 str, the file seperator will be converted to a url seperator '/'
							if no conversion is desired then '/' should be passed in.  If a PC path was being sent in, in a UTF8 encodeing
							then the seperator would be '\\', if a mac posix path was being sent in the seperator would be '/'
		@return The URL encodeing of the UTF8 string
		@see URLToUTF8
	*/
	static std::string UTF8ToURL(const std::string& str, const char kSeparator);
	
	/**
		URLToUTF8 converts from a URL to UTF8 encoded string 
		@param fileURL is the URL to convert
		@param ContainsUTF16 is a flag set if the returned UTF8 string encodes UTF16 chars
		@return UTF8 version of the URL
		@see UTF8ToURL, FileURLToPosixPath (mac only)
	*/
	static std::string URLToUTF8 (const std::string& fileURL, bool & ContainsUTF16);

	/**
		FileURLToPMString the perfered function call is 
		static PMString FileURLToPMString (const std::string &__fileURL);

		FileURLToPMString converts from a file url to a PMString system path
		on the pc this system path will eather be a UNC path if the url species a
		file not on the local host (file:/// or file://localhost/) and otherwise the encoded system path
		UNC path = \\myhost\mydir\myfile
		System path = c:\mydir\myfile

		On the mac the path returned will be a path made up of 31 char FsSpec file names
		if the Posix path is desired FileURLToPosixPath can be called.
		mac path: "my hd:my folder:my file"
	    
		@param fileURL File URL
		@return system path encoded as a pmstring
		@see    PMStringToFileURL, FileURLToPosixPath (mac only)
	*/
	static PMString FileURLToPMString (const std::string &fileURL);
        
	/**
		FileURLToPMString the perfered function call is 
		static PMString FileURLToPMString (const std::string &__fileURL);

		FileURLToPMString converts from a file url to a PMString system path
		on the pc this system path will eather be a UNC path if the url species a
		file not on the local host (file:/// or file://localhost/) and otherwise the encoded system path
		UNC path = \\myhost\mydir\myfile
		System path = c:\mydir\myfile

		On the mac the path returned will be a path made up of 31 char FsSpec file names
		if the Posix path is desired FileURLToPosixPath can be called.
		mac path: "my hd:my folder:my file"
	    
		@param fileURL File URL
		@return system path encoded as a pmstring
		@see    PMStringToFileURL, FileURLToPosixPath (mac only)
	*/        
	static PMString FileURLToPMString (const PMString &__fileURL);

	/** 
		FileURLToSysFile converts from a file url to a sysfile
		static IDFile FileURLToSysFile(const std::string& __fileURL, bool *isReturingAValidSysFile = NULL); is the prefered function call

		PC:
		on the PC this function should always succeeds aka (isReturingAValidSysFile should always be set to true on exit)
		if the url descibes a UNC path the file returned will obviously be a unc file path
		if the URL isn't unc the sysfile returned will be a standard path/

		file://myhost/mydir/myfile will result in \\myhost\mydir\myfile
		file://localhost/c:/mydir/myfile will result in c:\mydir\myfile
		file:///c:/mydir/myfile will result in c:\mydir\myfile

		MAC:
		On the Mac FSSpec can be made to point to files that don't exist, but the directory heiarchary must exist
		so this function might fail.  if it fails the optional paramater isReturingAValidSysFile will return false
		and the FSSpec returned in the sysfile should be zeroed and it shouldn't have a truename
		The mac also cant take UNC paths so don't even think about them. 

		If the URL decribes a directory which exists but a file which doesn't the function will succeed but 
		the FSSpec will point to a file which doesn't exist.  The TrueName for the FSSpec is set to the Unicode name
		described in the FileURL, the FSSpec name is set to a 31 byte platform char name.  If the URL name is greater
		then 31 characters then it is truncated.
	            
		file:///myfolder/myfile            Valid FSSpec if my folder exists on the default vol
		file://localhost/myfolder/myfile   Valid FSSpec if my folder exists on the default vol
	    
		@param __fileURL 			File URL to convert to a sys file
		@param isReturingAValidSysFile 	optional paramater, if a bool is passed in, the bool will be set to true if a valid IDFile is being returned
											on the PC this is always true, on the mac it can be true or false (see above)
	                                        
		@return IDFile to the File URL, on the PC the sys file might not exist but is a valid description, on the mac the sys file might not be valid
	    
		@see SysFileToFileURL, FileURLToPosixPath (mac only)
	*/

	static IDFile FileURLToSysFile(const std::string& __fileURL, bool *isReturingAValidSysFile = NULL);
        
		/** 
		FileURLToSysFile converts from a file url to a sysfile
		static IDFile FileURLToSysFile(const std::string& __fileURL, bool *isReturingAValidSysFile = NULL); is the prefered function call

		PC:
		on the PC this function should always succeeds aka (isReturingAValidSysFile should always be set to true on exit)
		if the url descibes a UNC path the file returned will obviously be a unc file path
		if the URL isn't unc the sysfile returned will be a standard path/

		file://myhost/mydir/myfile will result in \\myhost\mydir\myfile
		file://localhost/c:/mydir/myfile will result in c:\mydir\myfile
		file:///c:/mydir/myfile will result in c:\mydir\myfile

		MAC:
		On the Mac FSSpec can be made to point to files that don't exist, but the directory heiarchary must exist
		so this function might fail.  if it fails the optional paramater isReturingAValidSysFile will return false
		and the FSSpec returned in the sysfile should be zeroed and it shouldn't have a truename
		The mac also cant take UNC paths so don't even think about them. 

		If the URL decribes a directory which exists but a file which doesn't the function will succeed but 
		the FSSpec will point to a file which doesn't exist.  The TrueName for the FSSpec is set to the Unicode name
		described in the FileURL, the FSSpec name is set to a 31 byte platform char name.  If the URL name is greater
		then 31 characters then it is truncated.
	            
		file:///myfolder/myfile            Valid FSSpec if my folder exists on the default vol
		file://localhost/myfolder/myfile   Valid FSSpec if my folder exists on the default vol
	    
		@param __fileURL 			File URL to convert to a sys file
		@param isReturingAValidSysFile 	optional paramater, if a bool is passed in, the bool will be set to true if a valid IDFile is being returned
											on the PC this is always true, on the mac it can be true or false (see above)
	                                        
		@return IDFile to the File URL, on the PC the sys file might not exist but is a valid description, on the mac the sys file might not be valid
	    
		@see SysFileToFileURL, FileURLToPosixPath (mac only)
	*/
	static IDFile FileURLToSysFile(const PMString & __fileURL, bool *isReturingAValidSysFile = NULL);
	
		// If pathName is a relative path, it is resolved into a full path,
		// based on the application directory. Indirection to parent folder
		// (UNIX "..") is not supported. If the path is already fully resolved,
		// returns nil.
	static PMString *CreateResolvedPathName(const PMString& pathName);
		
		// Returns the amount of free space in K, on the volume or disk
		// that holds the specified directory.
	static uint32 SpaceAvail(const IDFile& diskToCheck);
	
	static bool16 IsDirectory(const IDFile& fileSpec);

	static bool16 CreateFolderIfNeeded(const IDFile& folderFileSpec, bool16 bCreateParent = kFalse);
    static bool16 CopyFile(const IDFile& srcFile, const IDFile& dstFile); 
    static bool16 MoveFile(const IDFile& srcFile, const IDFile& dstFolder, IDFile* dstFile = NULL); 
	static bool16 GetParentDirectory(IDFile const &file, IDFile &parent);
	static bool16 DoesFileExist(const IDFile& fileSpec);
	// get the path, without the filename
	static void GetPathOnly(const IDFile& fileSpec, PMString& pathName, bool16 includeSeparator = kFalse);
	//get the filename, minus any extension
	static void GetBaseFileName(const IDFile& inFile, PMString& outString);
	static void GetBaseFileName(const PMString& inString, PMString& outString);
	// Kinda the opposite of GetBaseFileName - returns only the extension
	static void  GetExtension(const IDFile& inFile, PMString& outString);
	
	//ResourceFork deprecated, function returns data fork size
	static uint32 GetFileSize(const IDFile& fileSpec, bool16 includeResourceFork = kFalse);


	// This function returns the file type(pub, template, book, library etc.) based on the passed in sysFile.
	static bool16 GetOpenFileType(const IDFile& sysFile, SysFileType &type);

	// This function is like the one above, but takes an open stream as its input.
	static bool16 GetStreamFileType(IPMStream *stream, SysFileType &type);
	
	// Get the name of the volume the file or folder is on.
	static void GetVolumeName(const IDFile *fileOrFolderSpec, PMString * volumeName);

	// Compare the two file names for same volume.
	static bool16 OnSameVolume(const IDFile& file1, const IDFile& file2);

	static int32 ShowFile( const IDFile& fileSpec);
	
	typedef enum { kNormal, kOpenNewWindow, kOpenMaximized } ViewMode;
	static ErrorCode BrowseToFile(const IDFile *fileSpec, ViewMode mode = kNormal);
	static ErrorCode OpenFileInEditor(const IDFile& fileToOpen, const AppInfo& appInfo = kNullAppInfo, PMString *errorString = nil);

	static bool16 IsNetworkDrive( const IDFile& sysFile );
	
	// Return the directory where app is installed by user. It should return the same folder as 
	// GetAppFolder on WINDOWS. On MACINTOSH, it should return the folder three level above the 
	// real application file due to mac package folder structure.
	static bool16 GetAppInstallationFolder(IDFile *folder);
	
	/** Return the presets folder with a subfolder appended, and optionally a localized folder appended as well.
		If you need just the Presets directory, you can pass an empty subFolderName and PMLocaleId().
		 @param folder IN/OUT the output path to a location within the Presets folder
		 @param subFolderName IN An optional subfolder with the Presets folder to append to the output path. May pass an empty string if not needed.
		 @param localeId IN Will append a localized folder name (e.g. "en_US") depending on PMLocaleId passed in. Typically LocaleSetting::GetLocale() 
						is passed for this argument. However, you can pass an default PMLocaleId() if you want no localized folder appended.
	 */
	static bool16 GetPresetsFolder(IDFile *folder, const PMString& subFolderName, const PMLocaleId& localeId);

	/** Appends a localized folder name to the passed in folder argument. The folder name that is appended corresponds 
		to the current user interface id in current locale. e.g. if presets folder was passed in, would append "en_US" for English, "fr_FR" for French, etc.
		 @param folder	IN/OUT the output path to modify
		 @param localeId IN Will append a localized folder name (e.g. "en_US") depending on PMLocaleId passed in. Typically LocaleSetting::GetLocale() 
						is passed for this argument. However, you can pass an default PMLocaleId() if you want no localized folder appended.
	  */
	static void AppendLocalizedFolder(IDFile* folder, const PMLocaleId& localeId);

	// NOTE: Just moved this out of the #ifdef MAC section, and put a Windows impl in
	static bool16 GetModificationDate(const IDFile & spec, uint32 *modDate);

	// Return kTrue if the file can be opened with the requested access rights.
	typedef enum { kRead, kWrite, kReadWrite } Access;
	static bool8 CanOpen(const IDFile& spec, Access access = kReadWrite);

	/** PrefixFileURL appends a prefix string
	    after the file:/// or file:// in a file url.  This function 
	    serves really no purpose other then being a helper function to some junky code thrown around
	    PLEASE don't use this.. It should really go away in the next version...
	
		If a file url isn't passed in then this code will assert, and the url will be returned.
		
		Example: PrefixFileURL ("123","file://myfile.jpg")		== file://123myfile.jpg
				 PrefixFileURL ("123","file:///myfile.jpg") 	== file:///123myfile.jpg
				 PrefixFileURL ("123","file:////myfile.jpg")	== file:///123/myfile.jpg	
				 PrefixFileURL ("123","file:/myfile.jpg")		== ASSERT + file:/myfile.jpg
				 PrefixFileURL ("123","http://myfile.jpg")		== ASSERT + http://myfile.jpg 
	
	    @param prefix prefix to append
		@param fileURL file url to add the prefix to. 
	*/
	static void PrefixFileURL (const PMString &prefix,  PMString &fileURL);

	/** 
	 Opens the file.
	 @param file	IN File to open.
	 @param mode	IN Flags denoting type of access permitted (see fopen).
	 @return A pointer to the open file if successful, else NULL.
     */
	static FILE* OpenFile(const IDFile& file, const char* mode);
	
	/** 
	 Opens the file referenced by the path.
	 @param file	IN Path of file to open.
					   An HFS path on Mac.
	 @param mode	IN Flags denoting type of access permitted (see fopen).
	 @return A pointer to the open file if successful, else NULL.
     */
	static FILE* OpenFile(const PMString& path, const char* mode);
	
	/** 
	 Opens the file referenced by the path.
	 @param file	IN Path of file to open.
					   An HFS path on Mac.
	 @param mode	IN Flags denoting type of access permitted (see fopen).
	 @return A pointer to the open file if successful, else NULL.
     */
	static FILE* OpenFile(const char* path, const char* mode);
	
#ifdef MACINTOSH	

	// Append pathToAppend onto the end of originalPath.
	static  void AppendPath(PMString *originalPath, const PMString& pathToAppend);
	
	// Get the dirID of the folder
	static bool16 GetDirID(const IDFile& folder, int32* dirID);

	static void ReplaceResource(SysHandle rsrc, int32 type, int16 id, const PMString& name);
	
	static void GetFileCreatorType(const IDFile& fileSpec, SysOSType* fileType, SysOSType* creator);
	static bool16 GetCreationDate(const IDFile & spec, uint32 *creDate);
	
	// Return the directory where application package is located. It should be two level above the 
	// real application file due to mac package folder structure.
	static bool16 GetPackageFolder(IDFile *folder);
	
	// Create the file using the Unicode file name in the IDFile.
	// Set bCreateParent to kTrue to create parent folders if necessary.
	// If the file cannot be created or already exists, the method returns kFalse.
	static bool16 CreateFileWithUnicodeName(IDFile& fileSpec, bool16 bCreateParent = kFalse);
	
	/** 
            FileURLToPosixPath 
            
            converts from a File URL to the Posix path This obiously isn't much of a transformation.   really
            nothing more then calling URLToUTF8 and not changeing the seperator.
        
            @param fileURL URL to convert to a Posix Path
            @return Posix Path
            
            @see URLToUTF8, FileURLToPMString
        */
	static std::string FileURLToPosixPath (const std::string& fileURL) ;
	
	/**
		Decompose a MAC UnicodeFile Name Back to System Unicode
		
		@param string to decompose
            
        @return decomposed result
	*/
    static PMString DecomposeUnicode (const PMString &str);
    
    /**
		Compose a MAC UnicodeFile Name Back to Compsed Unicode
		
		@param string to compose
    */
   static void NormalizeUnComposedUnicodeChars (PMString &fileName);

	/** 
	Converts from a POSIX path to a IDFile. The file must exist.
	@param posixPath Posix path to convert to a IDFile
	@return IDFile
     */
	static IDFile PosixPathToSysFile(const PMString& posixPath);
	static IDFile PosixPathToSysFile(const std::string& posixPath);

	/**
	 Converts an FSRef to an IDFile object.
	 @param fsRef	IN FSRef to convert.
	 The parent path of file referenced by the FSSpec must exist.
	 @param file	OUT Resulting IDFile object.
	 @return System noErr code if the conversion succeeds and the file exists.\\
	 System fnfErr code if the conversion succeeds and the file doesn't exist.\\
	 Otherwise, the system error code.
     */
	static OSErr FSRefToIDFile(const FSRef& fsRef, IDFile& file);

	/** 
	 Converts an IDFile object to an FSRef.
	 @param file		IN IDFile to convert.
	 The parent path of file must exist.
	 @param fsRef		OUT Resulting FSRef object.
	 @return System noErr code if the conversion succeeds and the file exists.\\
	 System fnfErr code if the conversion succeeds and the file doesn't exist.\\
	 Otherwise, the system error code.
     */
	static OSErr IDFileToFSRef(const IDFile& file, FSRef& fsRef);
		
    /**
     Checks if the file is in TrashFolder
     @param file          IN IDFile to check
     @return              TRUE in case the file is in Trash Folder and FALSE if it does not
     */
	static bool16 IsFileInTrash(const IDFile&  file);
	
    /**
     Encodes a Core Foundation URL into a Apple event descriptor record.
     @param url           IN CFURLRef the input URL to encode
     fURLDesc	  OUT, caller needs to call with non nil reference
     it wil be populated with the encoded Apple event descriptor
     @return			  noErr on success, error code otherwise.
     */
	static OSErr GetURLAppleEventDescFromCFURL(AEDesc* fURLDesc, CFURLRef url);

    /*
     Decodes an Apple event descriptor record
     @param aeDes         IN AEDesc the input Apple Event descriptor to decode
     @return			  CFURLRef on success, NULL if any error occurs.
     Caller needs to release the CFURLRef
     */	
	static CFURLRef CreateCFURLFromURLAppleEventDesc(const AEDesc* aeDesc);

#endif

#ifdef WINDOWS
	// Windows edge code for implementing common dialog that checks
	// for filenames with bad characters

	static IDThreading::ThreadLocal<DWORD>			tl_GOFNCallerFlags;
	static IDThreading::ThreadLocal<LPOFNHOOKPROC>	tl_GOFNCallerHookProc;
	static IDThreading::ThreadLocal<LPOPENFILENAME>	tl_GOFNCallerlpofn;

		// Hook function used by FileUtils::GetOpenFileName()
	static UINT_PTR APIENTRY GOFNHookFunction(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam);

		// Same as ::GetOpenFileName() but catches files with bad names and warns user
		// Uses the AWS GetFileDialog() GUI if AWS is defined and will load the given
		// SysFileList with the result files
		// K2 should use this call in preference to Win32 API ::GetOpenFileName()
	static bool16 GetOpenFileName(LPOPENFILENAME lpofn);
	static bool16 GetOpenFileName(LPOPENFILENAME lpofn, SysFileList& resultFiles);
	static bool16 GetOpenFileName(LPOPENFILENAME lpofn, SysFileList* pResultFiles);

	/** Cover function to call either SHGetFolderPathW or SHGetFolderPathA based on UNICODE compile flag. */
	static int32 CoverSHGetFolderPath(int nFolder, IDFile *path);
#endif

	/*
	 Query if preferences folder was created in current app launch
	 @return			  kFalse, if the roaming data folder existed before app launch, kTrue otherwise
	 */	
	static bool16 IsAppRoamingDataFolderNew();

	/**
	Get the local cached application data folder without the locale sub-folder.
	This function does not create the data folder.
	@param  result	OUT IDFile of the folder.
	@see GetAppLocalCachedDataFolder
	@see GetAppRoamingDataFolder
	@see AppendLocalizedFolder
	*/
	static bool16 GetAppLocalCachedDataFolderSansLocale(IDFile *result);

	static textchar GetDirectorySeparatorTextChar();

	/**
	Checks if the file is an InDesign Template file.
	@return kTrue if the file is InDesign Template, kFalse if it is not.
	*/
	static bool16 IsTemplate(const IDFile & file);

	/**
	Checks if the file is a temporary file.
	@return kTrue if the file is created in temp directory, kFalse if it is not.
	*/
	static bool16 IsTempFile(const IDFile & file);

	/**
	Converts an IDFile to a system path string depending on the flag value.
	@param  file	IN IDFile to convert to a string.
	@param  pathStr	OUT Resulting path string.
	@param  isPosixPath	IN Flag to check and provide POSIX path as string.
	On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
	On the mac, the path is an POSIX path: "OSX/Applications/Adobe InDesign CS2".
	@see PMStringToIDFile
	*/
	static void IDFileToPMString(const IDFile& file, PMString& pathStr, bool16 isPosixPath);

#ifdef MACINTOSH
    /**
     Internal use only
     Converts an IDFile to a system path string depending on the flag value.
     Small variation to above IDFileToPMString, it always looks for POSIX path and only works for files
     and not directories
     @param  file    IN IDFile to convert to a string.
     @param  pathStr    OUT Resulting path string.
     On Windows, the path is a UNC or local path: "C:\My Programs\adobe\indesign.exe".\\
     On the mac, the path is an POSIX path: "OSX/Applications/Adobe InDesign CS2".
     @see PMStringToIDFile
     */
    static void IDFileToPMStringBasedOnPathString(const IDFile& file, PMString& pathStr);
#endif
    
	/**
	Creates a unique file name incorporating the base file name passed in as parameter and appending process and/or thread id and some timestamp info.
	File name generated is not guaranteed to not already exist. This is typically used only for generating unique names for temporary files.
	If the calling code needs to ensure that an existing file is not overwritten, it should check for file existence and retry this function call (only
	the timestamp info will change in subsequent retries).
	@param  fileName	IN/OUT incoming base file name, generated name is returned via this parameter.
	*/
	static void CreateUniqueFileName(PMString & fileName);


#ifdef WINDOWS
	/**
	Converts an IDFile to a system path string - either a local path or a UNC path.
	@param  file	IN IDFile to convert to a string.
	@param  pathStr	OUT Resulting path string.\\
	*/
	static void IDFileToPMStringWithUNCConversion(const IDFile& file, PMString& pathStr);
#endif

private :
	
	
        
        /**
            FileURLToUTF8Path
            
            Converts from a file url to a utf8 path, this is similar to urltoutf8 but this
            function handles the fileurl prefix or really any prefix ("file://, http://, etc")
        
            @param fileURL The File URL to convert
            @param kSeperator The Seperator to convert the URL seperators to (pc: '\\' mac:'/')
            @param ContainsUTF16 true if the resulting UTF8 path contains encoded UTF16 chars
            
            @return UTF8 path to the File URL passed in
        */
	static std::string FileURLToUTF8Path (const std::string& fileURL, const char kSeperator, bool & ContainsUTF16);
	
        /**
            GetHexChar
            
            Returns the hex character encoded in the string passed in at position index.
                    
            Example:   GetHexChar("01FF",2) == 255
            
                	
            @param string string to extract two bytes out of
            @param index position of the first byte
                     
            @return Interger value of the hex char
        */
        static int16 GetHexChar (const std::string & string, int index);

		/**
		IsFirstFilePrefixOfSecond

		Checks if first file path is a prefix of second file path

		@param firstFile The first File
		@param secondFile The second File

		@return kTrue if first path is prefix of second, kFalse if not
		*/
		static bool16 IsFirstFilePrefixOfSecond(const IDFile & firstFile, const IDFile & secondFile);
};

#endif

