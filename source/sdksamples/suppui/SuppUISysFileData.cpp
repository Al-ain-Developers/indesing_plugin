//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUISysFileData.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----
#include "ISysFileData.h"
#include "IDFile.h"


// ----- Includes -----
#include "CPMUnknown.h"
#include "FileUtils.h"

// ----- Utility files -----

// ----- ID.h files -----
#include "SuppUIID.h"


/** Implements ISysFileData

	This implementation stores an IDFile, which  is initialized to SDKSample-SuppUI.xml.
	It can be changed by calling Set.
  
	@ingroup suppui
*/
class SuppUISysFileData : public CPMUnknown<ISysFileData> 
{
public:

	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
    SuppUISysFileData(IPMUnknown *boss);

    /**  This will copy the passed in IDFile
		@param theFile IN const reference that will be copied.
	*/
	virtual void Set(const IDFile& theFile);
	
	/**  This will return a const reference to the saved IDFile.
		@return the const IDFile reference
	*/
    virtual const IDFile& GetSysFile() const;

protected:

    IDFile      fSysFile;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SuppUISysFileData, kSuppUISysFileDataImpl)

/* SuppUISysFileData Constructor
*/
SuppUISysFileData::SuppUISysFileData(IPMUnknown *boss):
	CPMUnknown<ISysFileData>(boss)
{
	FileUtils::GetAppRoamingDataFolder( &fSysFile, "SDKSample-SuppUI.xml" );
}

/* Set
*/
void SuppUISysFileData::Set(const IDFile& theFile)
{
	fSysFile = theFile;
}

/* GetSysFile
*/
const IDFile& SuppUISysFileData::GetSysFile() const
{
	return fSysFile;
}

