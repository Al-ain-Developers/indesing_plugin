//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintPageInitializer.h $
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
#ifndef __IPrintPageInitializer__
#define __IPrintPageInitializer__

class IDocument;
class IPrintData;
class IOutputPages;
class IInkList;
class ISwatchList;
class IBook;
class UIDList;
class ITrapStyleListMgr;

/**
 * Part of GatherBookInfo, see below.
 */

class MasterDocumentInfo
{
public:
	MasterDocumentInfo():
	  fMasterUIDRef(UIDRef::gNull),
	  fMasterIDoc(nil),
	  fMasterOriginalOpen(kFalse) {}

public:
	UIDRef     fMasterUIDRef;
	PMString   fBookName;
	IDocument* fMasterIDoc;
	bool16     fMasterOriginalOpen;
};

/**
 * The crux of the situation is that the code that initializes the IOutputPages
 * for books is very difficult to reuse, and needs to be re-used from the preview
 * dialog.  So, this interface allows the preview code to call back to that code.
 */

class IPrintPageInitializer : public IPMUnknown
{
public:
	enum	{	kDefaultIID = IID_IPRINTPAGEINITIALIZER };

public:
	/**
	 * A method which initializes an IOutputPages from the data.
	 */

	virtual bool16 Initialize( IDocument* pDoc, IPrintData* pData, IOutputPages* pResult ) = 0;


	/**
	 * Essentially, we need a way to pre-populate this object
	 * with book information in the book case because of the way the book stuff was designed. 
	 * So, this method only makes sense for the book implementation.
	 * The document implementation asserts unimplemented if this method is called on it.
	 */

	virtual ErrorCode GatherBookInfo(IBook* iBook, UIDList* sourceList, bool16 bOpenAll, IInkList *iDstInkList, ISwatchList *iDstSwatchList, ITrapStyleListMgr* iDstTrapStyleListMgr, MasterDocumentInfo& masterInfo) = 0;
};

#endif

