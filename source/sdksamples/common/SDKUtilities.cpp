//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/common/SDKUtilities.cpp $
//  
//  Owner: Adobe Developer Technologies
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
//  This file contains implementations for SDKUtilities.h.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "SDKUtilities.h"

// InDesign interfaces:
#include "CAlert.h"			// ModalAlert
#include "PMString.h"		// Replace
#include "IPMStream.h"
#include "StreamUtil.h"
#include "ICoreFilename.h"
#include "SDKFileHelper.h"
#include "FileUtils.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif

#ifdef ID_DEPRECATED
 
/*
// Brings up CAlert with kAboutBoxString and OK button.
*/
void SDKUtilities::InvokePlugInAboutBox(const PMString alertStringID)
{
	CAlert::ModalAlert
	(
	   alertStringID,						// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}


// Some #defines for the pathname utility stuff
static const char  k_UNIXDELCHAR = '/';
static const char k_MACDELCHAR = ':';
static const char k_WINDELCHAR = '\\';
static const PMString k_UNIXDELIMETER ("/");
static const PMString k_WINDELIMETER("\\");
static const PMString k_MACDELIMETER (":");
static const PMString k_UNIX_WINPARENTDIR ("..");
static const PMString k_MACPARENTDIR ("::");

/* I have three types of pathname to deal with, relative upwards, relative downwards and absolute:
//  Example of relative downwards would be just a filename. 
//  Example of relative upwards would be any path beginning with a ".." 
//  Example of an absolute pathname would be any beginning with a '/' in unix. 
// I'm not sure what the exact format for the mac is, so the scheme I'm going to use is
// ralative paths begin with ":" and absolute paths don't (of course, a path consiting of just 
// a filename is taken to be relative). If this is a bad assumption to make, I'd be
// pleased to be educated... In the meantime, this makes sense to me.
//
// I have decided not to handle device names (like volume name on mac, or drive name on win).
// I see this as creating complications which outweigh gains. If I wanted to handle this, I'd
// use more robust mechanisms than I do here (I would provide a true abstraction). Here, I merely
// provide mapping routines, there is no internal representation of what a path should be.
*/

/*
// IsUnixPath
*/
bool SDKUtilities::IsUnixPath(PMString thisstring)
{
	// the way I do this is if it has a mac or win delimeter then it can't be a unix path.
	return !(thisstring.Contains(k_WINDELIMETER)||thisstring.Contains(k_MACDELIMETER));
}
	

/*
// IsMacPath
*/
bool SDKUtilities::IsMacPath(PMString thisstring)
{
	// the way I do this is if it has a unix or win delimeter then it can't be a unix path.
	return !(thisstring.Contains(k_WINDELIMETER)||thisstring.Contains(k_UNIXDELIMETER));
}
	

/*
// IsWinPath
*/
bool SDKUtilities::IsWinPath(PMString thisstring)
{
	// the way I do this is if it has a mac or unix delimeter then it can't be a win path
	// I also consider device names here...
	return !(thisstring.Contains(k_UNIXDELIMETER)||(thisstring.Contains(k_MACDELIMETER)));
}
	
	
/*
// IsAbsolutePath
*/
bool SDKUtilities::IsAbsolutePath(PMString thisstring)
{
	// if the path is a unix, win and mac path, it must be a relative filename (current dir)
	if (IsUnixPath(thisstring) && IsMacPath(thisstring)) // two out of three works for me
		return kFalse;
	// this routine determines whether it is an absolute path by looking at the first character.
	if ((IsUnixPath(thisstring)) && (thisstring[0]==k_UNIXDELCHAR))
		return kTrue;
	if ((IsWinPath(thisstring)) && (thisstring[0]==k_WINDELCHAR))
		return kTrue;
	if ((IsMacPath(thisstring)) && (thisstring[0]!=k_MACDELCHAR)) // mac paths are different, they don't start with a  colon
		return kTrue;
	return kFalse;
}


/*
// RemoveLastElement
*/
void SDKUtilities::RemoveLastElement(PMString& fromthis)
{
	// takes off the last element from the path. We search for the last delimeter and knock off the
	// stuff that comes after. We lose this data so beware!
	int lastpos = 0;
	for (int i = 0 ; i< fromthis.CharCount();i++)
		if ((fromthis[i] == k_MACDELCHAR) || (fromthis[i] == k_UNIXDELCHAR) || (fromthis[i] == k_WINDELCHAR))
			lastpos = i;
	// At this point lastpos should point to the last delimeter, knock off the rest of the string.
	fromthis.Truncate(fromthis.CharCount()-lastpos);
}


/*
// RemoveFirstElement
*/
void SDKUtilities::RemoveFirstElement(PMString& fromthis)
{
	// removes the first element of the path passed in.
	// if it is a relative path, we might need to take off two delimeter chars...
	if (fromthis[0] == fromthis[1])
	{	
		if (fromthis[0] == k_MACDELCHAR) // we know we start with a "::"
		{
			fromthis.Remove(0,2);
			return;
		} 
		else 
			if  (fromthis[0] == '.') // we know we start with a ".."
			{
				fromthis.Remove(0,3);
				return;
			}
	}
	// we have a name at the start if the path. Need to remove it...			
	// first of all, count the number of characters to the first delimeter. 
	int delpos = 0;
	for (int i = 0; i<fromthis.CharCount(); i++)
		if ((fromthis[i] == k_MACDELCHAR) || (fromthis[i] == k_UNIXDELCHAR) || (fromthis[i] == k_WINDELCHAR))
		{
			delpos = i;
			break;
		}
	fromthis.Remove(0,delpos);
}


/*
// ToAbsolutePath
*/
ErrorCode SDKUtilities::ToAbsolutePath(PMString base, PMString path, PMString& out)
{
	// this method takes in a base path, and a relative path. It merges the two to give a new absolute path.
	// I want to return the path in the same format as it's in. Success depends on the format of both the base
	// and relative quotients being the same type.
	// the base path must be a directory name, not a filename
	if (IsAbsolutePath(path))
	{	// we don't need to do any real work.	
		out = path;
		return kSuccess;
	}

	if (!((IsUnixPath(base) && IsUnixPath(path)) || (IsMacPath(base) && IsMacPath(path)) || (IsWinPath(base) && IsWinPath(path))))
		// none of the paths match. We cannot convert
		return kFailure;

	// At this point we know that the path types coincide. Need to strip off the elements coinciding with the "..". 
	// take local copies to work over...
	PMString thebase = base;
	PMString thepath = path;
	while (thepath.Contains(k_UNIX_WINPARENTDIR) || thepath.Contains(k_MACPARENTDIR))
	{
		//strip off the last from the base, and the first from the path.
		RemoveFirstElement(thepath);
		RemoveLastElement(thebase);
	}
	// at this point, we need to merge the remaining parts of the path.
	out = thebase;
	if ((IsMacPath(base) && IsMacPath(path)))
		out.Append(k_MACDELIMETER);
	else
		out.Append(k_WINDELIMETER);
	out.Append(thepath);
	return kSuccess;
}

			
/*
// ToAbsolutePath
*/
ErrorCode  SDKUtilities::ToAbsolutePath(IDFile base, PMString path, IDFile& out)
{
    SDKFileHelper baseFile(base);
    out = baseFile.GetAbsoluteFromRelative(path);

	return kSuccess;
}


/*
// GetPathName
// extracts the absolute path in terms of a string from an IDFile
*/
void  SDKUtilities::GetPathName(const IDFile spec, PMString& name)
{
	name.Clear();
    name = FileUtils::SysFileToPMString(spec);    
}


/*
//  convertToMacPath
//	A wee routine to change all '/' to ':' 
//	Allows us to handle macintosh files...
*/
void SDKUtilities::convertToMacPath(PMString& thisstring)
{
	if (IsMacPath(thisstring))
		return;
	// Replace all instances of .. with ::
	int32 position = thisstring.IndexOfString(k_UNIX_WINPARENTDIR);
	while (position!=-1)
	{
		thisstring.Remove(position,2); // remove the ".."
		thisstring.Insert(k_MACPARENTDIR,position);
		position = thisstring.IndexOfString(k_UNIX_WINPARENTDIR);
	}
	// first of all, get all the delimeters sorted.
	for (int32 i = 0; i<thisstring.CharCount(); i++)
		if ((thisstring[i] == k_UNIXDELCHAR) || (thisstring[i] == k_WINDELCHAR)) // want the mac delimeter
		{
			thisstring.Remove(i);
			// only do the insert if the next and previous chars aren't the k_MACDELCHAR!
			if ((i>0) && (thisstring[i-1]!=k_MACDELCHAR) && (thisstring[i+1] !=k_MACDELCHAR))
				thisstring.Insert(k_MACDELCHAR,i);
		}
}


/*
// convertToWinPath
//	A wee routine to change all ':' to '\' 
//	Allows us to handle win files...
*/
void SDKUtilities::convertToWinPath(PMString& thisstring)
{
	if (IsWinPath(thisstring))
		return;
	// Replace all instances of :: with ..
	int32 position = thisstring.IndexOfString(k_MACPARENTDIR);
	while (position!=-1)
	{
		thisstring.Remove(position,2); // remove the "::"
		thisstring.Insert(k_UNIX_WINPARENTDIR,position);
		thisstring.Insert(k_WINDELCHAR,position+2); // replace it with "..\"
		position = thisstring.IndexOfString(k_MACPARENTDIR);
	}

	//  get all the MAC delimeters sorted.
	position = thisstring.IndexOfString(k_MACDELIMETER);
	while (position!=-1)
	{
		thisstring.Remove(position); // remove the ":"
		thisstring.Insert(k_WINDELIMETER,position); // and put in a '\'
		position = thisstring.IndexOfString(k_MACDELIMETER);
	}

	// now get the unix delimeter sorted.
	position = thisstring.IndexOfString(k_UNIXDELIMETER);
	while (position!=-1)
	{
		thisstring.Remove(position); // remove the "/"
		thisstring.Insert(k_WINDELIMETER,position); // and put in a '\'
		position = thisstring.IndexOfString(k_UNIXDELIMETER);
	}
}


/*
// SysFileToPMString: Convert a IDFile to a PMString.
// ICoreFilename interface handles platform-specific issues.
*/
PMString SDKUtilities::SysFileToPMString(const IDFile* sFile)
{
    return FileUtils::SysFileToPMString(*sFile);    
}


/*
// PMStringToSysFile: Convert a PMString to a IDFile.
*/
IDFile SDKUtilities::PMStringToSysFile(PMString* fileName)
{
    return FileUtils::PMStringToSysFile(*fileName);    
}


/*
// Replace
// This routine is a Find and Replace for a single occurrence of an
// item in a PMString.
*/
void SDKUtilities::Replace(
	PMString& original, 		// Original string to search in.
	const PMString& target, 	// Text to search for.
	const PMString& replace		// Text to replace with.
    )
{
	const int32 kTargetFoundPos = original.IndexOfString(target);
	
	if (kTargetFoundPos >= 0)
	{
		original.Remove(kTargetFoundPos, target.CharCount());
		original.Insert(replace, kTargetFoundPos);
	}
}


#ifdef DEBUG

#include "Trace.h"
#include "PersistUtils.h"
#include "IPlugInList.h"
#include "IClassInfo.h"
#include "ISession.h"
#include "IObjectModel.h"

/* 
// DumpBoss
// This routine dumps object model information for the passed in interface. More correctly the information
// pertains to the boss class the interface is on.
*/
void SDKUtilities::DumpBoss(IPMUnknown * for_this_if)
{
	TRACE("************************* SDK::Utilities::DumpBoss() *************************\n");
	if (for_this_if == nil)
	{
		TRACE("Interface pointer is nil!\n");
		return;
	}
	UID uidObj = GetUID(for_this_if);
	if (uidObj == kInvalidUID)
		TRACE("This is not a persistent boss\n");
	else
		TRACE("Boss UID == %d (hex %x)\n",uidObj.Get(),uidObj.Get());
	ClassID id = GetClass(for_this_if);
	InterfacePtr <IPlugInList> iPlugInList(GetExecutionContextSession(),IID_IPLUGINLIST);
	InterfacePtr <IObjectModel> iOM(GetExecutionContextSession(),IID_IOBJECTMODEL);
	TRACE("Boss name is %s. ",iOM->GetIDName(id));
	InterfacePtr<IClassInfo> iCI(iOM->QueryClassInfo(id));
	PluginID pid = iCI->GetOwnerComponent();
	PMString plugInName = iPlugInList->GetPluginName(pid);
	TRACE("It comes from plug-in:- %s\n",plugInName.GetPlatformString().c_str());
	int32 numofif = iCI->CountInterfaces();
	TRACE("--------------------------------------------------------------\n");
	TRACE("Interface		Implementation\n");
	for (int r=0;r<numofif;r++)
	{
		PMIID ifpmid = iCI->GetInterface(r);
		ImplementationID backimpl  = iCI->GetImplementation(ifpmid);
		TRACE("%s(%x)    %s(%x)\n",iOM->GetIDName(ifpmid),ifpmid.Get(),iOM->GetIDName(backimpl),backimpl.Get());
	}
	TRACE("Parent: %s(%d)\n",iOM->GetIDName(iCI->GetParentClass()),iCI->GetParentClass().Get());
	TRACE("******************************************************************************\n");
}

/*
// DumpBoss
// This method dumps obejcts model information about the passed in boss class.
*/
void SDKUtilities::DumpBoss(UIDRef for_this_object)
{
	// I should check that I can instantiate this object first...
	InterfacePtr<IPMUnknown> theIFace(for_this_object, IID_IUNKNOWN);
	SDKUtilities::DumpBoss(theIFace);
}

/*
// DumpMessage
// TRACEs information about an IObserver::Update() method call.
// The names of theChange and protocol are extracted from the
// object model and dumped to TRACE.
*/
void SDKUtilities::DumpMessage(const char* msg, const ClassID& theChange, const PMIID& protocol)
{
	do
	{
		InterfacePtr<IObjectModel> objectModel(GetExecutionContextSession(), IID_IOBJECTMODEL);
		if (objectModel == nil)
			break;
		const char* theObjectModelChangeName = objectModel->GetIDName(theChange);
		const char* theObjectModelProtocolName = objectModel->GetIDName(protocol);

		char theChangeName[128] = "";
		char protocolName[128] ="";
		if (theObjectModelChangeName != nil)
			strcpy(theChangeName, theObjectModelChangeName);
		else
			sprintf(theChangeName, "0x%x", theChange.Get());

		if (theObjectModelProtocolName != nil)
			strcpy(protocolName, theObjectModelProtocolName);
		else
			sprintf(protocolName, "0x%x", protocol.Get());
									
		TRACE("%s theChange=%s, protocol=%s\n", msg, theChangeName, protocolName);	
	} while(false);		
}

#else
/*
// For the release build we leave the empty methods.
*/
void SDKUtilities::DumpBoss(IPMUnknown * for_this_if)
{
}

void SDKUtilities::DumpBoss(UIDRef for_this_object)
{
}

void SDKUtilities::DumpMessage(const char* msg, const ClassID& theChange, const PMIID& protocol)
{
}

#endif


/*
// GetApplicationFolder
*/

ErrorCode SDKUtilities::GetApplicationFolder(PMString& appFolder)
{
	FileUtils::GetAppFolder(&appFolder);
	return kSuccess;

}


/*
// AbsolutePathToSysFile
*/

ErrorCode  SDKUtilities::AbsolutePathToSysFile(PMString path, IDFile& out)
{
    out =  FileUtils::PMStringToSysFile(path);    

	return kSuccess;

}


/*
// CreateFileStreamRead
*/

IPMStream* SDKUtilities::CreateFileStreamRead(const PMString& fullPath, uint32 mode, OSType fileType, OSType creator)
{
	ErrorCode status = kFailure;
	IPMStream* iDataFileStream = nil;
	do
	{
		IDFile dataFile;
		status = SDKUtilities::AbsolutePathToSysFile(fullPath, dataFile);
		if (status == kFailure)
		{
			break;
		}

		iDataFileStream = StreamUtil::CreateFileStreamRead(dataFile, mode, fileType, creator);
		if (iDataFileStream == nil)
		{
			status = kFailure;
			break;
		}

		status = kSuccess;

	} while (false); // only do once

	return iDataFileStream;
}


/*
// CreateFileStreamWrite
*/

IPMStream* SDKUtilities::CreateFileStreamWrite(const PMString& fullPath, uint32 mode, OSType fileType, OSType creator)
{
	ErrorCode status = kFailure;
	IPMStream* iDataFileStream = nil;
	do
	{
		IDFile dataFile;
		status = SDKUtilities::AbsolutePathToSysFile(fullPath, dataFile);
		if (status == kFailure)
		{
			break;
		}

		iDataFileStream = StreamUtil::CreateFileStreamWrite(dataFile, mode, fileType, creator);
		if (iDataFileStream == nil)
		{
			status = kFailure;
			break;
		}

		status = kSuccess;

	} while (false); // only do once

	return iDataFileStream;
}


/*
// FileExistsForRead
*/

ErrorCode SDKUtilities::FileExistsForRead(const PMString& fullPath)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IPMStream> iDataFileStream(SDKUtilities::CreateFileStreamRead(fullPath));
		if (iDataFileStream == nil)
		{
			break;
		}

		iDataFileStream->Close();

		status = kSuccess;

	} while (false); // only do once

	return status;
}

void SDKUtilities::AppendPathSeparator(PMString& path)
{
#ifdef MACINTOSH
	path.Append(":");
#else
	path.Append("\\");
#endif
}


/*
Get the file creator type for the spec. 
*/
void SDKUtilities::GetFileCreatorType(const IDFile spec, SysOSType* fileType, SysOSType* creator)
{
#ifdef MACINTOSH
	ASSERT_MSG(fileType != nil && creator != nil, "SDKUtilities::GetFileCreatorType - fileType != nil && creator != nil");

	if ((void *)&spec != nil)	// on Recovery, 'spec' can be nil
	{
		MacFileUtils::GetCreatorAndType(spec, *creator, *fileType);
	}
#else
	// On Windows, we do nothing. 
#endif
}

/*
Get the file extension.
*/
PMString SDKUtilities::GetExtension(const IDFile spec)
{
	PMString extension;
    FileUtils::GetExtension(spec, extension);
	

	return extension;
}
#endif // ID_DEPRECATED

// End, SDKUtilities.cpp.

