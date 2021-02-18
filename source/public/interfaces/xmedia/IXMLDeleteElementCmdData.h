//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLDeleteElementCmdData.h $
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
#ifndef __IXMLDeleteElementCmdData__
#define __IXMLDeleteElementCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** Data interface for deleting elements from the logical structure tree; from client
	code, use IXMLElementCommands rather than low-level commands.
*/
class IXMLDeleteElementCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLDELETEELEMENTCMDDATA };

	/**	Set up data on this interface
		@param deleteElementXMLRef XML element reference to delete
		@param deleteChildren 	whether to recursively delete the children as well
		@param deleteInSameStoryOnly if deleteChildren, whether to delete only the children that are also in the same story
		@param reconnectChildren	whether to reconnect the children to deleted element's parent (deleteChildren must be kFalse) 
	 */
	virtual void Set(const XMLReference& deleteElementXMLRef, bool16 deleteChildren, bool16 deleteInSameStoryOnly = kFalse, bool16 reconnectChildren = kFalse) = 0;

	/** Set up additional, DTD related data for this interface
		@param ignoreDTD if kTrue, if the deleting element is associated with a DTD, ignore 
		validation and just delete the element. By default, if an element is associated with
		a DTD, the validity is taken into consideration when an element is deleted
	*/
	virtual void SetDTDProperties(bool16 ignoreDTD = kFalse) = 0;

	/** Setup additional table related command parameters
		@param deleteTableWithCell (default = kTrue) if kTrue, deleting a cell in the table will 
		cause the entire table to be deleted. If kFalse, only the cell(s) given will be deleted
	*/
	virtual void SetTableProperties(bool16 deleteTableWithCell = kTrue) = 0;

	// 
	/**	Accessor for the item to be deleted
		@return XMLReference to item be deleted when command processed 
	 */
	virtual const XMLReference& GetDeleteElement(void) const = 0;

	/** Accessor for the list of elements that will actually get deleted. This is best called 
		during pre-notification of the command, after the calculations have been done on which
		elements will actually get deleted
		@return K2Vector<XMLReference> vector of elements that will actually get deleted
	*/
	virtual const K2Vector<XMLReference>& GetElementsToBeDeleted(void) const = 0;

	/**	Accessor for property, specifying whether to delete the children as well
		@return bool16 kTrue if children should be deleted too, kFalse otherwise
	 */
	virtual bool16 DeleteChildren(void) const = 0;
	

	/**	Accessor for property, specifying whether to only delete the children that are also in the same story
		@return bool16 kTrue if children in same story only should be deleted, kFalse for converse
	 */
	virtual bool16 DeleteInSameStoryOnly(void) const = 0;
	
	/**	Accessor for property, specifying whether to reconnect the children to deleted element's parent
		@return bool16 kTrue if children should be reconnected to deleted element's parent, kFalse if the converse
	 */
	virtual bool16 ReconnectChildren(void) const = 0;
	
	/**	Accessor for property, specifying whether to ignore the DTD when deleting the specified element
		@return bool16 kTrue if DTD should be ignored; kFalse if DTD validity should be preserved
	*/
	virtual bool16 IgnoreDTD(void) const = 0;

	/** Accessor for property, specifying whether deleting a table cell will cause the entire 
		table to be deleted as well
		@return whether the table should be deleted if a table cell is deleted
	*/
	virtual bool16 DeleteTableWithCell(void) const = 0;

	/**	Set the number of text markers to be deleted in the process of deleting this element and possibily
		its children.  Useful for adjusting text ranges after a delete.  This is set by the
		command as it deletes elements
		@param numOfMarkersDeleted [INTERNAL] set by the command, not from client code
	 */
	virtual void SetNumOfMarkersDeleted(int32 numOfMarkersDeleted) = 0;


	/**	Accessor for the number of markers that were deleted by the command
		@return int32 giving number of markers deleted
	 */
	virtual int32 GetNumOfMarkersDeleted(void) const = 0;

	/** Set the list of elements that will actually get deleted
		@param elementsList list of elements that will actually get deleted
	*/
	virtual void SetElementsToBeDeleted(const K2Vector<XMLReference>& elementsList) = 0;

	/** Set whether to delete the element markers. If the markers are not deleted, then 
		TextIndexID is still deleted, but the marker itself remains in the text model
		INTERNAL USE ONLY
		@param deleteMarkers whether to delete the markers
	*/
	virtual void SetDeleteMarkers(bool16 deleteMarkers) = 0;

	/** Get whether to delete element markers
		INTERNAL USE ONLY
		@return whether to delete element markers
	*/
	virtual bool16 GetDeleteMarkers(void) const = 0;
};

#endif	// __IXMLDeleteElementCmdData__

