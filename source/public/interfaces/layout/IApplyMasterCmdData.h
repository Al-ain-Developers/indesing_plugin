//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IApplyMasterCmdData.h $
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
//  Data interface for applying master pages.
//  
//========================================================================================

#pragma once
#ifndef __IApplyMasterCmdData__
#define __IApplyMasterCmdData__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "UIDRef.h" 
#include "PMReal.h"
#include "SpreadID.h"
#include "UIDList.h"

/** Data interface for the kApplyMasterSpreadCmdBoss to apply a master to a page, pages (or master pages).
	A master spread is applied to any page in a document, and stored via the IMasterPage interface.
*/
class IApplyMasterCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPLYMASTERCMDDATA };

	enum PageResizeChoice { kResizeToMasterPageSize, kKeepCurrentPageSize, kAskUserForPageResizeChoice};

	/**	Set the UIDRef of the master spread to use for applying to the page (or master pages) in
		the item list of the kApplyMasterSpreadCmdBoss. If a page has an applied master, that master
		will draw before the contents of the page draw on top. Note that a master page may also have
		another master applied to it. Use kInvalidUID to apply the "None" master to a page.
		@param masterSpreadUIDRef the new master spread to apply the pages in the commands item list
		@param resizeChoice  one of kResizeToMasterPageSize, kKeepCurrentPageSize, or kConsultUser
		@see IMasterPage.h
	 */
	virtual void SetApplyMasterCmdData( UIDRef masterSpreadUIDRef, PageResizeChoice resizeChoice) = 0;

	/**	Return the UID of the master spread to be applied.
		@param none
		@return UIDRef return the master spread UIDRef
	 */
	virtual UIDRef GetMasterSpreadUIDRef() const = 0;

	/**	Return the PageResizeChoice passed to SetApplyMasterCmdData.
		@param none
		@return PageResizeChoice
	 */
	virtual PageResizeChoice GetPageResizeChoice() const = 0;

	/**
	 Values for how to reflow text through primary text flow frames when applying master pages.
	 */
	enum FlowChoice { 
		kReflowText, /** Reflow text from primary text frame on old master to new master. This is the default value for the command if not specified. */
		kDontReflowText  /** Don't reflow text. Used during transition states such as duplicating spreads due to order of master page override duplication. */
	};

	/**	Return the FlowChoice passed to command. Defaults to kReflowText if not specified.
		@param none
		@return FlowChoice whether text should be reflowed through primary text frames when a master is applied to a page
	 */
	virtual FlowChoice GetTextFlowChoice() const = 0;

	/**	Return the FlowChoice passed to command. Defaults to 
		@param FlowChoice whether text should be reflowed through primary text frames when a master is applied to a page
		@return void
	 */
	virtual void SetTextFlowChoice(FlowChoice flowChoice) = 0;
};



#endif // __IApplyMasterCmdData__
