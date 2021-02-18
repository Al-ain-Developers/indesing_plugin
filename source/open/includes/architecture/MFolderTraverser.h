//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/MFolderTraverser.h $
//
//  Owner: Matt Joss
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __MFolderTraverser__
#define __MFolderTraverser__

#include "PMString.h"
#include "ObjPtrCollection.h"

class PUBLIC_DECL MFolderTraverser
{
public:
	MFolderTraverser(bool16 returnDirectoryPaths = kFalse, bool16 searchSubDirectories = kTrue, bool16 resolveAliases = kTrue, bool16 excludeInvisibleFiles = kTrue);
	MFolderTraverser(const IDFile& fileSpec, bool16 returnDirectoryPaths = kFalse, bool16 searchSubDirectories = kTrue, bool16 resolveAliases = kTrue, bool16 excludeInvisibleFiles = kTrue);
	~MFolderTraverser();
	
	virtual void AddPath(const IDFile& fileSpec);
	
	virtual void GetFileInfo(SysFileInfo *fileInfo);
	
	virtual void Reset();
	virtual bool16 Next(IDFile *resultFile, bool16* isDirectory = nil);
	virtual void Current(IDFile *resultFile) const;
	
protected:
	virtual bool16 FileMatch(IDFile *resultFile, bool16 isDirectory);
	
private:
	bool16	DoNext(IDFile *resultFile, bool16* isDirectory);
	bool16	AlreadyOnTheList(const IDFile& fileToCheck);
	bool16	StartNextPath(bool16 *isDirectory);
	
	CFMutableArrayRef	fCachedRefList;
	int32				fNumRefsInList;			// numElementsReturned
	int32				fIndex;					// index number on the fCachedRefList
	int32				fPathIndex;				// index number of which path we're on
	bool16				fReturnDirectoryPaths;
	bool16				fSearchSubDirectories;
	bool16				fResolveAliases;
	bool16				fExcludeInvisibleFiles;
	ObjPtrCollection<IDFile*> fPathList;		// List of paths to search
    CFURLEnumeratorRef	fEnumeratorRef;			// Directory Enumerator
};

#endif // __MFolderTraverser__
