//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/NAMEINFO.H $
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
//  
//  The NameInfo class identifies a link.  File links use it to identify
//  a file in a core way.  It is basically two strings and two longs.
//  
//  void Initialize(PMString *filename, PMString *volname, long dirid, ClassID id);
//  void Initialize(NameInfo *nameinfo);
//  Initialize the class.  Call one of these methods before calling the other
//  methods.
//  
//  PMString *GetFilename();
//  Get the filename.  The actual pointer maintain by the object is returned
//  not a copy.
//  
//  PMString *GetVolume();
//  Get the volume name.  The actual pointer maintain by the object is returned
//  not a copy.
//  
//  long GetDirID() { return fDirID;};
//  Get the dir id.
//  
//  ClassID GetClassID() { return fClassID;};
//  Get the class id associated with this name.  For files it is
//  kDataLinkBoss.
//  
//  void ReadWrite(IPMStream *s);
//  Routine used to stream the data.
//  
//========================================================================================

#ifndef __NAMEINFO__
#define __NAMEINFO__

#include "PMString.h"

#pragma export on

class IPMStream;

class PUBLIC_DECL NameInfo
{
public:
   typedef object_type data_type;
   NameInfo() : fDirID(0), fClassID(0), fVersion(1) {};
	~NameInfo() {};
	
	void Initialize(PMString *filename, PMString *volname, int32 dirid, ClassID id, IDFile* file = nil);
	void Initialize(NameInfo *ni) {
		Initialize(&ni->fFilename, &ni->fVolumeName, ni->fDirID, ni->fClassID, &ni->fFile);
	};
	
	PMString *GetFilename();
	PMString *GetVolume();
	int32 GetDirID() { return fDirID;};
	ClassID GetClassID() { return fClassID;};
	IDFile* GetFile();
	uint8 GetVersion() { return fVersion;};
	
	void ReadWrite(IPMStream *s);
	
	bool16 operator == (NameInfo &ni);
	bool16 operator != (NameInfo &ni) { return (!(*this == ni)); }

private:
	PMString	fFilename;
	PMString	fVolumeName;
	int32		fDirID;
	ClassID		fClassID;
	IDFile		fFile;
	uint8		fVersion;
};

#pragma export off


#endif // __NAMEINFO__
