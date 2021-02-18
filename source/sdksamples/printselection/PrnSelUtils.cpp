//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelUtils.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IDocument.h"
#include "IDataBase.h"
#include "IHierarchy.h"
#include "IMasterPage.h"

// General includes:
#include "UIDList.h"
#include "CPMUnknown.h"
#include "DocFrameworkID.h" // kNoDocumentOpenError

// Project includes:
#include "IPrnSelData.h"
#include "IPrnSelUtils.h"
#include "PrnSelID.h"


/** Implementation of utility methods for manipuating the print selection flag.
 
	@ingroup printselection
 */
class PrnSelUtils: public CPMUnknown<IPrnSelUtils>
{
public:

	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelUtils(IPMUnknown* boss) : CPMUnknown<IPrnSelUtils>(boss) { }
	
	/** Destructor
	*/
	virtual ~PrnSelUtils(void) {}
	
	/** Can the print selection flag be retrieved? 
	 * 	@param itemList IN The item list to test, to see if they are valid selections.
	 * 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanGetPrintSelectionFlag(const UIDList& itemList);

	/** Can the print selection flag be retrieved from the specified document? 
	 * 	@param doc IN The document to test.
	 * 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanGetPrintSelectionFlag(IDocument* doc);

	/** Get the print selection flag
	 * 	@param db IN The database to check. This should be a document database.
	 * 	@return The current status of the flag.
	*/
	virtual bool16 _GetPrintSelectionFlag(IDataBase* db);

	/** Get the print selection flag on the specified document
	* 	@param doc IN The document to check.
	* 	@return The current status of the flag.
	*/
	virtual bool16 _GetPrintSelectionFlag(IDocument* doc);

	/** Can the print selection flag be set? 
	* 	@param itemList IN The item list to test, to see if they are valid selections.
	* 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanSetPrintSelectionFlag(const UIDList& itemList);

	/** Can the print selection flag be set on the specified document? 
	* 	@param doc IN The document to test.
	* 	@return kTrue if the print selection flag can be set, kFalse otherwise.
	*/
	virtual bool16 _CanSetPrintSelectionFlag(IDocument* doc);

	/** Set the print selection flag
	 * 	@param db IN The database on which to set the flag. This should be a document database.
	 * 	@param printSelection IN the flag's new value.
	 * 	@return kSuccess if success, other value if otherwise. 
	*/
	virtual ErrorCode _SetPrintSelectionFlag(IDataBase* db, const bool16 printSelection);

	/** Set the print selection flag on the specified document
	 * 	@param doc IN The document on which to set the flag.
	* 	@param printSelection IN the flag's new value.
	* 	@return kSuccess if success, other value if otherwise. 
	*/
	virtual ErrorCode _SetPrintSelectionFlag(IDocument* doc, const bool16 printSelection);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelUtils, kPrnSelUtilsImpl)

/* _CanSetPrintSelectionFlag
*/
bool16 PrnSelUtils::_CanGetPrintSelectionFlag(const UIDList& itemList)
{
	// the requirements are the same as setting the flag
	return _CanSetPrintSelectionFlag(itemList);
}

/* _CanSetPrintSelectionFlag
*/
bool16 PrnSelUtils::_CanGetPrintSelectionFlag(IDocument* doc)
{
	// the requirements are the same as setting the flag
	return _CanSetPrintSelectionFlag(doc);
}

/*	_GetPrintSelectionFlag
*/
bool16 PrnSelUtils::_GetPrintSelectionFlag(IDataBase* db)
{
	bool16 printSelection = kFalse;
	do
	{
		if (db == nil)
		{
			ASSERT_FAIL("db is nil");
			break;
		}
		UID rootUID = db->GetRootUID();
		InterfacePtr<IDocument> doc(db, rootUID, UseDefaultIID());
		if (doc == nil)
		{
			ASSERT_FAIL("doc is nil");
			break;
		}
		printSelection = this->_GetPrintSelectionFlag(doc);

	} while (false);
	return printSelection;
}

/*	_GetPrintSelectionFlag
*/
bool16 PrnSelUtils::_GetPrintSelectionFlag(IDocument* doc)
{
	bool16 printSelection = kFalse;
	do
	{
		if (doc == nil)
		{
			ASSERT_FAIL("doc is nil");
			break;
		}
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData == nil)
		{
			ASSERT_FAIL("psData is nil");
			break;
		}
		printSelection = psData->GetIsChecked();

	} while (false);
	return printSelection;
}

/* _CanSetPrintSelectionFlag
*/
bool16 PrnSelUtils::_CanSetPrintSelectionFlag(const UIDList& itemList)
{
	bool16 canSetPrintSelectionFlag = kFalse;
	do
	{
		if (itemList.Length() == 0)
		{
			break;
		}
		IDataBase* db = itemList.GetDataBase();
		if (db == nil)
		{
			break;
		}
		UID docUID = db->GetRootUID();
		InterfacePtr<IDocument> doc(db, docUID, UseDefaultIID());
		canSetPrintSelectionFlag = this->_CanSetPrintSelectionFlag(doc);

	} while (false);

	return canSetPrintSelectionFlag;
}

/* _CanSetPrintSelectionFlag
*/
bool16 PrnSelUtils::_CanSetPrintSelectionFlag(IDocument* doc)
{
	bool16 canSetPrintSelectionFlag = kFalse;
	do
	{
		if (doc == nil)
		{
			break;
		}
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData == nil)
		{
			break;
		}
		canSetPrintSelectionFlag = kTrue;
	} while (false);
	return canSetPrintSelectionFlag;
}

/*	_SetPrintSelectionFlag
*/
ErrorCode PrnSelUtils::_SetPrintSelectionFlag(IDataBase* db, const bool16 printSelection)
{
	ErrorCode status = kNoDocumentOpenError;
	do
	{
		if (db == nil)
		{
			ASSERT_FAIL("db is nil");
			break;
		}
		UID rootUID = db->GetRootUID();
		InterfacePtr<IDocument> doc(db, rootUID, UseDefaultIID());
		if (doc == nil)
		{
			ASSERT_FAIL("doc is nil");
			break;
		}
		
		status = this->_SetPrintSelectionFlag(doc, printSelection);

	} while (false);
	return status;
}

/*	_SetPrintSelectionFlag
*/
ErrorCode PrnSelUtils::_SetPrintSelectionFlag(IDocument* doc, const bool16 printSelection)
{
	ErrorCode status = kNoDocumentOpenError;
	do
	{
		if (doc == nil)
		{
			ASSERT_FAIL("doc is nil");
			break;
		}
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData == nil)
		{
			ASSERT_FAIL("psData is nil");
			break;
		}
		psData->SetIsChecked(printSelection);
		status = kSuccess;

	} while (false);
	return status;
}

// End, PrnSelUtils.cpp
