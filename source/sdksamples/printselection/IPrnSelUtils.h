//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/IPrnSelUtils.h $
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

#ifndef __IPrnSelUtils_h__
#define __IPrnSelUtils_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:
#include "Utils.h"

// Project includes
#include "PrnSelID.h"

// forward declarations
class UIDList;
class IDocument;
class IDatabase;

/** Utility methods for manipuating the print selection flag.
 
	@ingroup printselection
 */
class IPrnSelUtils: public IPMUnknown
{
public:
	/** Specifies the default IID for this interface */
	enum { kDefaultIID = IID_IPRNSELUTILS };

	/** Can the print selection flag be retrieved? 
	 * 	@param itemList IN The item list to test, to see if they are valid selections.
	 * 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanGetPrintSelectionFlag(const UIDList& itemList) = 0;

	/** Can the print selection flag be retrieved from the specified document? 
	 * 	@param doc IN The document to test.
	 * 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanGetPrintSelectionFlag(IDocument* doc) = 0;

	/** Get the print selection flag
	 * 	@param db IN The database to check. This should be a document database.
	 * 	@return The current status of the flag.
	*/
	virtual bool16 _GetPrintSelectionFlag(IDataBase* db) = 0;

	/** Get the print selection flag on the specified document
	* 	@param doc IN The document to check.
	* 	@return The current status of the flag.
	*/
	virtual bool16 _GetPrintSelectionFlag(IDocument* doc) = 0;

	/** Can the print selection flag be set? 
	* 	@param itemList IN The item list to test, to see if they are valid selections.
	* 	@return kTrue if the print selection flag can be retrieved, kFalse otherwise.
	*/
	virtual bool16 _CanSetPrintSelectionFlag(const UIDList& itemList) = 0;

	/** Can the print selection flag be set on the specified document? 
	* 	@param doc IN The document to test.
	* 	@return kTrue if the print selection flag can be set, kFalse otherwise.
	*/
	virtual bool16 _CanSetPrintSelectionFlag(IDocument* doc) = 0;

	/** Set the print selection flag
	 * 	@param db IN The database on which to set the flag. This should be a document database.
	 * 	@param printSelection IN the flag's new value.
	 * 	@return kSuccess if success, other value if otherwise. 
	*/
	virtual ErrorCode _SetPrintSelectionFlag(IDataBase* db, const bool16 printSelection) = 0;

	/** Set the print selection flag on the specified document
	 * 	@param doc IN The document on which to set the flag.
	 * 	@param printSelection IN the flag's new value.
	 * 	@return kSuccess if success, other value if otherwise. 
	 */
	virtual ErrorCode _SetPrintSelectionFlag(IDocument* doc, const bool16 printSelection) = 0;

};

#endif 

// End, IPrnSelUtils.h.
