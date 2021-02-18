//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstUtils.h $
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

#ifndef __PstLstUtils_h__
#define __PstLstUtils_h__



/** Implements some model-specific helper methods shared by different source files
	in this plug-in.
	
	@ingroup persistentlist
*/
class PstLstUtils 
{
public:
	/** Creates new persistent list item data on a page item.
	 * 	@param pageItemListToAddTo IN List of page items (which aggregate IPstLstUIDList) to which you want to add new persistent list items.
	 * 	@param name IN The name of the persistent list item to add to each item in pageItemListToAddTo.
	 * 	@param newItemsList OUT The newly created persistent list items.
	 * 	@return kSuccess if success, non-zero otherwise.
	*/
	static ErrorCode DoCreateNewData(const UIDList& pageItemListToAddTo, 
										const WideString& name, 
										UIDList& newItemsList);
	

	/** Gets the name of the persistent list item. 
	 * 	@param pstLstItemRef IN The persistent list item to examine (not page item).
	 * 	@param name OUT The name in the persistent list item.
	 * 	@return kSuccess if success, non-zero otherwise.
	*/
	static ErrorCode DoGetName(const UIDRef& pstLstItemRef, 
							   WideString& name);
	
	/** Sets the name of the persistent list item. 
	 * 	@param pstLstDataList IN The list of persistent list items to modify (not page item).
	 * 	@param name IN The new name in the persistent list item.
	 * 	@return kSuccess if success, non-zero otherwise.
	*/
	static ErrorCode DoSetName(UIDList& pstLstDataList, 
							   const WideString& name);

	/** Tests whether all items in the itemList are devoid of persistent list items.
	 * 	@param itemList IN List of page items to examine. These page items must aggregate 
	 * 		IPstLstUIDList.
	 *	@return kTrue of all items are devoid of persistent list items, kFalse if one or
	 * 		more items have one or more persistent list item.
	 */
	static bool16 AllPstLstAreEmpty(const UIDList& itemList);

    /** Removes page items that do not have any persistent list items.
	 * 	@param pageItemList IN/OUT A list of page items to examine. This list is modified and returned
	 * 		to the caller via this parameter. 
	 */
	static void RemoveNonPstLstItems(UIDList& pageItemList);

};

#endif // __PstLstUtils_h__

// End, PstLstUtils.h

