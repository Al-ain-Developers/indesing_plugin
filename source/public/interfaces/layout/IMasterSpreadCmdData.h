//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterSpreadCmdData.h $
//  
//  Owner: Brendan O'Shea
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
//  Command data interface for new/delete master spreads.
//  
//========================================================================================

#pragma once
#ifndef __IMasterSpreadCmdData__
#define __IMasterSpreadCmdData__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "UIDRef.h" 
#include "PMRect.h"

class IDataBase;
class PMString;

/** Command data interface associated with commands for manipulating master spreads.

	@ingroup layout_spread
	@see kNewMasterSpreadCmdBoss
	@see kRenameMasterSpreadCmdBoss
*/
class IMasterSpreadCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMASTERSPREADCMDDATA };

	/** Initialization
		@param doc IN document target for this command
		@param pagesPerSpreadCount IN number of pages for this master spread
		@param position IN position in the master spread list for this master spread
	*/
	virtual void Set(const UIDRef& doc, 
									int32 pagesPerSpreadCount, 
									int32 position) = 0;

	/** @return UIDRef of document this command is targeted at */
	virtual const UIDRef& GetDocument() const = 0;

	/** @return number of pages specified for this master spread */
	virtual const int32 GetPagesPerSpreadCount() const = 0;

	/** @return position in the master spread specified */
	virtual const int32 GetPosition() const = 0;

	/** @return base name of the master spread */
	virtual const PMString& GetMasterSpreadBasename() const = 0;

	/** set the base name of the master spread 
		@param newName IN base name for the master spread
	*/
	virtual void SetMasterSpreadBasename(const PMString& newName)= 0;

	/** @return the prefix of the master spread (e.g. 'A', 'B', etc.) */
	virtual const PMString& GetMasterSpreadPrefix() const= 0;

	/** Set the prefix of the master spread (e.g. 'A', 'B', etc.)  
		@param newPrefix IN prefix for the master (maximum 4 characters)
	*/
	virtual void SetMasterSpreadPrefix(const PMString& newPrefix) = 0;

	/** Set the master which will be applied to this master
		@param parent IN UID of master spread to be applied to this master (may be kInvalidUID for 'none')
	*/
	virtual void SetBasedOnMasterUID(UID parent) = 0;

	/** Get the master to be applied to this master
		@return UID of master spread to be applied to this master (may be kInvalidUID for 'none')
	*/
	virtual UID GetBasedOnMasterUID() = 0;
};




#endif //  __IMasterSpreadCmdData__
