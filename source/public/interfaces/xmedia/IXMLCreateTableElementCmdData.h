//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLCreateTableElementCmdData.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLCreateTableElementCmdData__
#define __IXMLCreateTableElementCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "TableTagData.h"


/**
	Data interface for adding table/table cell elements to the logical structure tree;
	if you're writing client code, use IXMLElementCommands and you won't need this
	interface.
*/
class IXMLCreateTableElementCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLCREATETABLEELEMENTCMDDATA };

	/**	Set the data through a text index, naming the tag to apply
		@param tableTagData Information about the tags to use when tagging the table
		@param storyUIDRef UIDRef of the story containing the text index
		@param textIndex TextIndex of an insertion point in any cell of the table
	 */
	virtual void Set(const TableTagData& tableTagData, const UIDRef& storyUIDRef, TextIndex textIndex) = 0;

	/**	Set the data through specifying a table model, naming the tag to apply
		@param tableTagData Information about the tags to use when tagging the table
		@param tableModelUIDRef UIDRef of the table model to tag
	 */
	virtual void Set(const TableTagData& tableTagData, const UIDRef& tableModelUIDRef) = 0;

	/**	Accessor for the table element created, once command executed
		@return the table element that was added (call this after the command is processed without error)
	 */
	virtual const XMLReference& GetCreatedTableElement() const = 0;


	/**	For use by the command only; don't invoke from client code
		@param newItem [INTERNAL] don't set this from client code
	 */
	virtual void SetCreatedTableElement(const XMLReference& newItem) = 0;
	
	/**	Used to get the table tag data for the command	
		@return the class that describes the tags to use when tagging this table
	 */
	virtual const TableTagData &GetTableTagData() const = 0;

	/** For use by the command only
		@return UIDRef of table model to tag
	*/
	virtual const UIDRef& GetTableModelUIDRef(void) const = 0;

	/** For use by the command only
		@see SetTagTableModelOnly()
		@return whether to tag just the table model
	*/
	virtual bool16 TagTableModelOnly(void) const = 0;

	/** For internal use only
		Set whether to tag the table model only (not the cells)
		NOTE: this will leave the table model in an inconsistent state. Do not
		use unless you really know what you are doing
		@param tagTableModelOnly whether to tag just the table model and not the cells
	*/
	virtual void SetTagTableModelOnly(bool16 tagTableModelOnly) = 0;
};

#endif	// __IXMLCreateTableElementCmdData__

