//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkImportLinkConverter.h $
//  
//  Owner: SusanCL
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

#pragma once
#ifndef __CusDtLnkImportLinkConverter__
#define __CusDtLnkImportLinkConverter__

// ----- Includes -----
#include "ILink.h"

#include "CPMUnknown.h"
#include "IDTime.h"
#include "WideString.h"

class IDataLink;

class CusDtLnkImportLinkConverter : public CPMUnknown<ILink>
{
public:
	typedef CPMUnknown<ILink> inherited;

	CusDtLnkImportLinkConverter (IPMUnknown* boss);
	virtual ~CusDtLnkImportLinkConverter();

	virtual LinkType GetLinkType() const { return kImport; }
	virtual LinkClientID GetClientID() const { return fClientId; }

	virtual UID GetResource() const { return kInvalidUID; }
	virtual void SetResource(UID resourceUID) { ASSERT_UNIMPLEMENTED(); }
	virtual ResourceModificationState GetResourceModificationState() const { return fResourceModState; }
	virtual void SetResourceModificationState(ResourceModificationState modState);

	virtual UID GetObject() const { return kInvalidUID; }
	virtual void SetObject(UID objectUID) { ASSERT_UNIMPLEMENTED(); }
	virtual ObjectModificationState GetObjectModificationState() const { return kObjectUnmodified; }
	virtual void SetObjectModificationState(ObjectModificationState modState) { ASSERT_UNIMPLEMENTED(); }

	virtual bool16 GetShowInUI() const { return kTrue; }
	virtual void SetShowInUI(bool16 bShowInUI) { ASSERT_UNIMPLEMENTED(); }

	virtual bool16 GetCanEmbed() const { return kTrue; }
	virtual void SetCanEmbed(bool16 bCanEmbed) { ASSERT_UNIMPLEMENTED(); }

	virtual bool16 GetCanUnembed() const { return kTrue; }
	virtual void SetCanUnembed(bool16 bCanUnembed) { ASSERT_UNIMPLEMENTED(); }

	virtual bool16 GetCanPackage() const { return kTrue; }
	virtual void SetCanPackage(bool16 bCanPackage) { ASSERT_UNIMPLEMENTED(); }

	virtual ImportPolicy GetImportPolicy() const { return kNoAutoImport; }
	virtual void SetImportPolicy(ImportPolicy policy) { ASSERT_UNIMPLEMENTED(); }

	virtual WideString GetImportStamp() const { return fImportStamp; }
	virtual IDTime GetImportModTime() const { return fImportModTime; }
	virtual IDTime GetLastImportTime() const { return fLastImportTime; }

	virtual ExportPolicy GetExportPolicy() const { return kNoAutoExport; }
	virtual void SetExportPolicy(ExportPolicy policy) { ASSERT_UNIMPLEMENTED(); }

	virtual IDTime GetLastExportTime() const { return fLastExportTime; }

	virtual void AddChildren(const UIDList& children) { ASSERT_UNIMPLEMENTED(); return; }
	virtual void DeleteChildren(const UIDList& children) { ASSERT_UNIMPLEMENTED(); return; }
	virtual uint32 GetChildren(UIDList& children) const { ASSERT_UNIMPLEMENTED(); return 0; }
	virtual uint32 GetNumChildren() const { ASSERT_UNIMPLEMENTED(); return 0; }

	virtual UID GetParent() const { ASSERT_UNIMPLEMENTED(); return kInvalidUID; }

	virtual ErrorCode Update(bool bForceUpdate, UIFlags uiFlags, UID& linkUID) { ASSERT_UNIMPLEMENTED(); return kFailure; }
	virtual ErrorCode CopyAttributes (const UIDRef& linkRef) { ASSERT_UNIMPLEMENTED(); return kFailure; }

	virtual ErrorCode Init (IDataLink* iDataLink);

private:
	virtual bool Init(LinkClientID clientId, UID resourceUID, UID objectUID) { ASSERT_UNIMPLEMENTED(); return false; }

	virtual void InitFromINX(IDataBase* db,
							 LinkType type,
							 LinkClientID clientId,
							 const WideString& importStamp,
							 const IDTime& importModTime,
							 const IDTime& lastImportTime,
							 const IDTime& lastExportTime,
							 bool16 isSharedContentLink) { ASSERT_UNIMPLEMENTED(); }

	virtual ErrorCode CopyAttributes(const ILink* pLink) {ASSERT_UNIMPLEMENTED(); return kFailure; }

	// Member variables
	LinkType					fType;
	LinkClientID				fClientId;

	ResourceModificationState	fResourceModState;

	IDTime						fLastExportTime;
	IDTime						fLastImportTime;
	IDTime						fImportModTime;
	WideString					fImportStamp;
};


#endif // __CusDtLnkImportLinkConverter__
