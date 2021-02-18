//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/layout/AcquireCurrentBook.h $
//  
//  Owner: Matt Phillips
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Helper stack-based object for acquiring and reestablishing the current book.
//  Should probably move this file someplace public.
//  
//========================================================================================

#pragma once

#include "IBookUIUtils.h"
#include "IPanelControlData.h"
#include "UIDList.h"
#include "IBookManager.h"

class IBook;
class IWidget;

class AcquireCurrentBook
{
private:
	UIDList* fSelected;
	int32 fTotalItems, fNumSelected;
	IBook* fBook;
	IBook* fPrevBook;

public:
	AcquireCurrentBook(IPMUnknown* iWidget)
		: fSelected(nil), fTotalItems(0), fNumSelected(0), fBook(nil), fPrevBook(nil)
	{
		InterfacePtr<IBookManager> iBookMgr(GetExecutionContextSession(), IID_IBOOKMANAGER);
		Utils<IBookUIUtils> iBookUIUtils;
		InterfacePtr<IPanelControlData> iPanelData;
		if (Utils<IBookUIUtils>().Exists()) 
		{
			if (iWidget) iPanelData.reset(iBookUIUtils->QueryBookPanelData(iWidget));
			else iPanelData.reset(iBookUIUtils->QueryActiveBookPanel());
		}

		if (iPanelData)
		{
			IDFile bookFile;
			iBookUIUtils->GetBookFileFromBookPanel(bookFile, iWidget);

			fPrevBook = iBookMgr->GetCurrentActiveBook();
			fBook = iBookMgr->FindOpenBookByName(bookFile);

			if (fPrevBook != fBook) 
			{
				ASSERT(iWidget);
				iBookMgr->SetCurrentActiveBook(fBook);
			}
			if (Utils<IBookUIUtils>().Exists()) 
			{
				K2Vector<int32> collection;
				fNumSelected = iBookUIUtils->GetSelectedBookContents(collection, fSelected, iPanelData);
				fTotalItems = iBookUIUtils->GetListItems(iPanelData);

			}
		}
	}

	~AcquireCurrentBook()
	{
		InterfacePtr<IBookManager> iBookMgr(GetExecutionContextSession(), IID_IBOOKMANAGER);
		if (fPrevBook && iBookMgr) iBookMgr->SetCurrentActiveBook(fPrevBook);
		delete fSelected;
	}

	UIDList* GetSelected() const { return fSelected; }
	int32 GetTotalItems() const { return fTotalItems; }
	int32 GetNumSelected() const { return fNumSelected; }
	IBook* GetBook() const { return fBook; }
	bool32 AllOrNoneSelected() const { return fNumSelected == 0 || fNumSelected == fTotalItems; }
};

