//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IEPubViewingAppsPrefs.h $
//  
//  Owner: Vani Sivasankar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IEPubViewingAppsPrefs_h__
#define __IEPubViewingAppsPrefs_h__

#include "EBookExportID.h"
#include "K2Vector.h"

class PreviewApplicationInfo
{
public:
	typedef object_type data_type;

	PreviewApplicationInfo(const PMString& appName, bool16 isSelReflow, bool16 isSelFXL):
	fAppName(appName),
	fIsSelectedReflow(isSelReflow),
	fIsSelectedFXL(isSelFXL)
	{}

	PreviewApplicationInfo():
	fAppName(kNullString),
	fIsSelectedReflow(kTrue),
	fIsSelectedFXL(kTrue)
	{}

	PMString GetAppName()
	{
		return fAppName;
	}

	bool16 GetIsAppSelectedInReflow()
	{
		return fIsSelectedReflow;
	}

	bool16 GetIsAppSelectedInFXL()
	{
		return fIsSelectedFXL;
	}

	void Set(const PMString& appName, bool16 isSelReflow, bool16 isSelFXL)
	{
		fAppName = appName;
		fIsSelectedReflow = isSelReflow;
		fIsSelectedFXL = isSelFXL;
	}

	~PreviewApplicationInfo()
	{
	}

private:
	PMString fAppName;
	bool16 fIsSelectedReflow;
	bool16 fIsSelectedFXL;
};

class IEPubViewingAppsPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEPUBVIEWINGAPPSPREFS };

	/** Preview exported epub if true. Need to specify epub reader in OS.
	*/
	virtual bool16 GetPreview() const = 0;
	virtual void SetPreview(bool16 preview) = 0;

	/** User specified applications for EPub Preview
	*/
	virtual K2Vector<PreviewApplicationInfo> GetApplications() const = 0;
	virtual void SetApplications(const K2Vector<PreviewApplicationInfo>& applications) = 0;

	virtual void AddApplication(const PMString& appName, bool16 isSelReflow, bool16 isSelFXL) = 0;
	virtual void RemoveApplicationByIndex(int32 index) = 0;
	virtual PreviewApplicationInfo ApplicationAtIndex(int32 index) = 0;

	virtual int32 GetApplicationsCount() = 0;

	/** Copies one set of prefs into another
		@param other IN The preferences to copy
	*/
	virtual void Copy(IEPubViewingAppsPrefs const * other) = 0;
};

#endif
