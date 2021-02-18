//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GenStyleListMgr.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __CGenStyleListMgr__
#define __CGenStyleListMgr__

#include "IGenStlEdtListMgr.h"
#include "IGenStyleLockInfo.h"
#include "IGenericSettings.h"
#include "HelperInterface.h"
#include "PersistUIDList.h"
#include "K2Vector.h"
#include "KeyValuePair.h"

#pragma export on

class PUBLIC_DECL CGenStyleListMgr: public IGenStlEdtListMgr
{
public:
	// Constructors and Destructors
	CGenStyleListMgr(IPMUnknown* pBoss);
	virtual ~CGenStyleListMgr();

	virtual int32 			GetNumStyles();
	virtual ErrorCode 	    GetNthStyleName(int32 index, PMString *pName);
	virtual ErrorCode 	    GetNthStyleDescription(int32 index, PMString *pDesc);
	virtual bool32 	        IsNthStyleEditable(int32 index);
	virtual bool32 	        IsNthStyleDeleteable(int32 index);
	virtual int32 			GetStyleIndexByName(const PMString& pName);
	
	virtual ErrorCode 	    AddStyle(PMString& name);
	virtual ErrorCode 	    CopyNthStyle(int32 srcIndex, PMString& newName);
	virtual ErrorCode 	    DeleteNthStyle(int32 index);
	virtual PMString		GetUniqueStyleName(PMString& baseName);
	// Requirements for a conforming style name can be determined from the specific
	// needs of a derived class.  For instance, PDF Export styles are now stored as .joboptions
	// files on disk.  Their names must conform to filesystem constraints such as not containing
	// path segment delimiters.  This gives the derived class a way to make appropriate modifications
	// to the incoming name.
	virtual PMString		GetConformingStyleName(PMString& baseName);
	virtual ErrorCode       SetNthStyleName(int32 index, PMString& name);
	
	virtual bool32			CustomImport(const IDFile* theFile) { return kFalse; }
	virtual bool32			CustomExport(const IDFile* theFile, K2Vector<int32>& indexList) { return kFalse; }
	virtual ErrorCode		ImportStyles(UIDRef uidrefFrom);
	virtual ErrorCode		ExportStyles(UIDRef uidrefTo, K2Vector<int32>& indexList);

	virtual void			GetImportExportFileMagicByte(DBUtils::MagicBytes magicBytes);

	virtual UIDRef			GetNthStyleRef(int32 index);

 	virtual void 			ReadWrite(IPMStream *s, ImplementationID prop);

	virtual void			ListInsert(UID uid, int32 index = -1);
	virtual void			ListRemove(int32 index);
	virtual void			ListReplace(UID uid, int32 index);

	ErrorCode               ImportFlattenerStyle(int32                         nOwningStyle,
												 const PMString&               strOwningStyle,
							 					 IGenStlEdtListMgr*            pStyleMgr );


	ErrorCode                AddFlattenerStyle( int32              nSrcIndex,
											   const PMString&    strNewName,
											   IGenStlEdtListMgr* pSrc,
											   IGenStlEdtListMgr* pDst );


	virtual bool16 ReferencesFlattenerStyle() { return kFalse; }
	virtual UIDRef GetReferencedFlattenerStyle( int32 nIndex ) { ASSERT_UNIMPLEMENTED(); return UIDRef(); }
	virtual PMString GetFlattenerStyleName( int32 nIndex ) { ASSERT_UNIMPLEMENTED(); return ""; }
	virtual void SetFlattenerStyleName( int32 nIndex, const PMString& strName ) { ASSERT_UNIMPLEMENTED(); }

	virtual bool16 EnabledInNoPubState() { return kFalse; }

protected:
	virtual IGenericSettings*  QuerySettings( int32 nIndex ) = 0;
	virtual PMString           GetDefaultName()            = 0;
	virtual ClassID            GetAddStyleCmdBossID()      = 0;
	virtual ClassID            GetSetStyleNameCmdBossID()  = 0;
	virtual ClassID            GetDeleteStyleCmdBossID()   = 0;
	virtual ClassID            GetStyleBossID()            = 0;
	virtual PMIID              GetListMgrIID()             = 0;	
	virtual PMIID              GetLockInfoIID()            { return IID_IGENSTYLELOCKINFO; }

	UIDRef GetSelfUIDRef() const
	{
		return UIDRef(::GetDataBase(this), ::GetUID(this));
	}

	PMString GetNextUniqueStyleName(int32 i, const PMString& baseName);

protected:
	// Member Variables
	PersistUIDList	fStyleUIDList;

DECLARE_HELPER_METHODS()
};

#pragma export off
#endif

// End, GenStyleListMgr.h.

