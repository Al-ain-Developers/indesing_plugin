//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/FilesChanging.cpp $
//  
//  Owner: Steve Flenniken
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

#include "VCPlugInHeaders.h"
#include "IFilesChanging.h"
#include "HelperInterface.h"
#include "LinksUIID.h"
//#include "K2Vector.tpp"

typedef K2Vector<UIDRef> UIDRefList;

class FilesChanging : IFilesChanging 
{
public:
	FilesChanging(IPMUnknown *boss);
	~FilesChanging();

	void Append(UIDRef ref);
	void Remove(int32 index);
	UIDRef GetRef(int32 index);
	int32 Length();
	int32 Location(UIDRef ref);

private:
	UIDRefList fFilesChanging;

	DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(FilesChanging, kFilesChangingImpl)

DEFINE_HELPER_METHODS(FilesChanging)

FilesChanging::FilesChanging(IPMUnknown *boss) : 
	HELPER_METHODS_INIT(boss)
{
}

FilesChanging::~FilesChanging()
{
}

void FilesChanging::Append(UIDRef ref)
{
	fFilesChanging.push_back(ref);
}

void FilesChanging::Remove(int32 index)
{
	fFilesChanging.erase(fFilesChanging.begin() + index);
}

UIDRef FilesChanging::GetRef(int32 index)
{
	return fFilesChanging[index];
}

int32 FilesChanging::Length()
{
	return fFilesChanging.size();
}

int32 FilesChanging::Location(UIDRef ref)
{
	K2Vector<UIDRef>::const_iterator iter = K2find(fFilesChanging, ref);
	return (iter != fFilesChanging.end() ? iter - fFilesChanging.begin() : -1);
}
