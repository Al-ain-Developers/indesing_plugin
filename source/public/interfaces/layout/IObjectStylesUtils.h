//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectStylesUtils.h $
//  
//  Owner: Danielle Darling
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
#ifndef __IOBJECTSTYLEUTILS__
#define __IOBJECTSTYLEUTILS__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMString.h"
#include "AttributeBossList.h"
#include "IObjectAttributeList.h"	// for ObjectStyleTarget
#include "IStyleNameTable.h"
#include "ISelectionExtension.h"		// for ProtocolCollection
#include "IObjStylesAttrHandler.h"
#include "LazyNotificationData.h"
#include "IObjStylesAttrHandler.h"
#include "IAnchoredObjectData.h"
#include "Utils.h"

//-----------------------------------
//	Forward References
//
class ICommand;

// ===================================================================================
//	class IObjectStylesUtils 
// ===================================================================================
/** Utility methods for working with object styles.
	@ingroup layout_util
*/
class IObjectStylesUtils : public IPMUnknown 
{

//-----------------------------------
//	API
//
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_IOBJECTSTYLESUTILS};

	/**
	 	FillStyleTargetFromSelection: Gets the attributes from the model and fills in the target
	 	@param modelTargetBoss	The csb representing the selection
	 	@param targetBoss	The style target attribute information we are filling
	 	@param ws			The current workspce
	 	@bool16 fillInCategories	Optional Param -- true by default, fills in the categories with the default values
	 */
	virtual void FillStyleTargetFromSelection(const IPMUnknown* modelTargetBoss, IPMUnknown *targetBoss, IWorkspace *ws, bool16 fillInCategories = kTrue) const = 0;

	/**
		SetStyleTargetOnDefaultSelection: Sets the attributes in the default selection state
	 	@param targetBoss	The style target (kObjectStylesTargetBoss)
	 	@param ws			The current workspce
	 	@param categoriesToOverride	This of categories we are overriding attributes in
	 */
	virtual void SetStyleTargetOnDefaultSelection(const IPMUnknown* targetBoss, IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride) = 0;

	/**
		SetStyleAttrsInUIDList: Sets the attributes in the model and from the target
	 	@param list			The UIDList of the pageitems to change
	 	@param targetBoss	The style target (kObjectStylesTargetBoss)
	 	@param ws			The current workspce
	 	@param categoriesToOverride	This of categories we are overriding attributes in
	 */
	virtual void SetStyleTargetOnUIDList(const UIDList& list, const IPMUnknown* targetBoss, IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride) = 0;
	
	/**
		GetAttrsFromObjectStyle: Get the attributes from object style and set it into targetBoss
	 	@param objectStyleUIDRef	The style we are pulling from
	 	@param target	The style target attribute information we are filling
	 	@param fillInUncheckedCategoriesWithThisUID		optional param -- Usually the root style if we are filling in the missing categories
	 */
	virtual void GetTargetFromObjectStyle(const UIDRef& objectStyleUIDRef, IPMUnknown* target, UID fillInUncheckedCategoriesWithThisUID = kInvalidUID) = 0;
	/**
		SetTargetIntoObjectStyle: Get the attributes from object style and set it into targetBoss

		NOTE: MUST BE CALLED FROM A COMMAND OR IN A DATABASE TRANSACTION

	 	@param objectStyleUIDRef	The style we are putting the attriubtes on
	 	@param target				The style target (kObjectStylesTargetBoss)
		@param howToUseCat			The flag indicates if we should ignore categories status when setting attributes, use only the attributes in the checked
									categories or use only the attributes in the unchecked categories
	 */
	virtual void SetTargetIntoObjectStyle(const UIDRef& objectStyleUIDRef, const IPMUnknown* target, const IObjStylesAttrHandler::HowToUseCategories howToUseCat = IObjStylesAttrHandler::kApplyOnlyCheckedCategoriesFromSource) = 0;

	/**
		CopyAttrsBetweenObjectStyles: 	Get the attributes from object style and set it into targetBoss
									Convert them if necessary

		NOTE: MUST BE CALLED FROM A COMMAND OR IN A DATABASE TRANSACTION

	 	@param sourceWS			The source style workspce
	 	@param sourceObjectStyle	The source style we are pulling from
	 	@param targetWS			The target style workspce
	 	@param targetObjectStyle	The target style we are pushing the attriubtes to
	 */
	virtual void CopyTargetBetweenObjectStyles(IWorkspace *sourceWS, const UID& sourceObjectStyle, 
										  IWorkspace *targetWS, const UID& targetObjectStyle) = 0;
	/**
		MergeAttrsIntoObjectStyle: Only adds the attributes which are in the source, but not in the target

		NOTE: MUST BE CALLED FROM A COMMAND OR IN A DATABASE TRANSACTION

	 	@param sourceObjectStyle	The source style we are pulling from
	 	@param targetWS			The target style workspce
	 	@param targetObjectStyle	The source style we are mergring the attriubtes to
	 */
	virtual void  MergeAttrsIntoObjectStyle(const IPMUnknown* sourceObjectStyle, IWorkspace *targetWS, const UID& targetObjectStyle) = 0;

	/**
		FillInDefaultGraphicStyle: Gets the default attribute and fills in the target for the default graphic frame style
	 	@param ws			The current workspce
	 	@param target		The style target attribute information we are filling
		@param isRootStyle  The flag indicates if we fill default graphic attributes for root style.
	 */
	virtual void FillInDefaultGraphicStyle(IWorkspace *ws, IPMUnknown* target, bool16 isRootStyle = kFalse) = 0;
	/**
		FillInDefaultTextStyle: Gets the default attribute and fills in the target for the default text frame style
	 	@param ws			The current workspce
	 	@param target		The style target attribute information we are filling
	 */
	virtual void FillInDefaultTextStyle(IWorkspace *ws, IPMUnknown* target) = 0;

	/**
		FillInDefaultFrameGridStyle: Gets the default attribute and fills in the target for the default frame grid style
	 	@param ws			The current workspce
	 	@param target		The style target attribute information we are filling
	 */
	virtual void FillInDefaultFrameGridStyle(IWorkspace *ws, IPMUnknown* target) = 0;

	/**
		GetUniqueDuplicateName: Gets a unique duplicate string for the new style
	 	@param ws			The current workspce
	 	@param baseName		The base name to start from
	 	@return	PMString	The unique name
	 */
	virtual PMString GetUniqueDuplicateName(IWorkspace* ws, const PMString& baseName) = 0;

	/**
		CreateSetDefaultStyleCmd: Creates a command to change the default style for the workspace
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param clearOverrides True if we want to clear overrides, otherwise kFalse.
		@return ICommand	The command to set the default graphics style
	 */
	virtual ICommand* CreateSetDefaultStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, bool16 clearOverrides = kFalse) = 0;
	/**
		CreateSetDefaultStyleCmd: Same as above except it takes a list of overrides instead of just a bool
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param categoriesToOverride A list of  categories to clear overrides in
		@return ICommand	The command to set the default graphics style
	 */
	virtual ICommand* CreateSetDefaultStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, K2Vector<ClassID>& categoriesToOverride) = 0;

	/**
		CreateSetDefaultTextStyleCmd: Creates a command to change the default style for the workspace
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param clearOverrides True if we want to clear overrides, otherwise kFalse.
		@param bDefaultFrameGridCmd True if this command is for set the default frame grid style, otherwise kFalse(set default text style)
		@return ICommand	The command to set the default text style
	 */
	virtual ICommand* CreateSetDefaultTextStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, bool16 clearOverrides = kFalse, bool16 bDefaultFrameGridCmd = kFalse) = 0;

	/**
		CreateSetDefaultTextStyleCmd: Same as above except it takes a list of overrides instead of just a bool
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param categoriesToOverride A list of  categories to clear overrides in
		@param bDefaultFrameGridCmd True if this command is for set the default frame grid style, otherwise kFalse(set default text style)
		@return ICommand	The command to set the default text style
	 */
	virtual ICommand* CreateSetDefaultTextStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, K2Vector<ClassID>& categoriesToOverride, bool16 bDefaultFrameGridCmd = kFalse) = 0;

	/**
		CreateSetDefaultFrameGridStyleCmd: Creates a command to change the default frame grid style for the workspace
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param clearOverrides True if we want to clear overrides, otherwise kFalse.
		@param bDefaultFrameGridCmd True if this command is for set the default frame grid style, otherwise kFalse(set default text style)
		@return ICommand	The command to se the default frame grid style
	 */
	virtual ICommand* CreateSetDefaultFrameGridStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, bool16 clearOverrides = kFalse, bool16 bDefaultFrameGridCmd = kTrue) = 0;

	/**
		CreateSetDefaultFrameGridStyleCmd: Same as above except it takes a list of overrides instead of just a bool
	 	@param ws			The current workspce
	 	@param newDefaultStyleName		The new default style name
		@param applyAttrs	True if we should apply the attrs from the style, this is not true when creating the style
	 	@param target		The style target (kObjectStylesTargetBoss)
		@param categoriesToOverride A list of  categories to clear overrides in
		@param bDefaultFrameGridCmd True if this command is for set the default frame grid style, otherwise kFalse(set default text style)
		@return ICommand	The command to se the default frame grid style
	 */
	virtual ICommand* CreateSetDefaultFrameGridStyleCmd(IWorkspace *ws, const PMString& newDefaultStyleName, bool16 applyAttrs, const IPMUnknown *target, K2Vector<ClassID>& categoriesToOverride, bool16 bDefaultFrameGridCmd = kTrue) = 0;

	/**
		IsStyleOverridenBySelection: Checks to see if its portion of the object style is overriden on the selection
	 	@param modelTargetBoss	The csb representing the selection
	 	@param ws			The current workspce
	 	@param style		The boss with the style data
	 	@param categories	Optional parameter to indicate which categories to check for overrides -- when nil we assume all
	 	@return bool16		true if the style is overriden
	*/
	virtual bool16	IsStyleOverridenBySelection(const IPMUnknown* modelTargetBoss, const IWorkspace*ws, const IPMUnknown* style, const K2Vector<ClassID> *categories = nil) = 0;

	/**
		GetSelectionOverridesToStyle: Returns a list of the current overrides in the selection
	 	@param modelTargetBoss	The csb representing the selection
	 	@param ws			The current workspce
	 	@param styleUID		The style UID we are checking
	 	@param categoryNameMap	Out -- category name list
	 	@param categories	Optional parameter to indicate which categories to check for overrides -- when nil we assume all
	 	@return ObjStyleCategoryAttrMap	represents the overrides
	*/
	virtual ObjStyleCategoryAttrMap	GetSelectionOverridesToStyle(const IPMUnknown* modelTargetBoss, const IWorkspace*ws, const UID styleUID, ObjStyleCategoryNameMap& categoryNameMap, const K2Vector<ClassID> *categories = nil) = 0;

	/**
		SelectionContainsMixedOverrides: Checks to see if current selection has mixed overrides or not.
	 	@param modelTargetBoss	The csb representing the selection
		@param ws			The current workspce
	 	@param categories	Optional parameter to indicate which categories to check for overrides -- when nil we assume all
		@return	bool16 True if the selection contains mixed overrides
	*/
	virtual bool16	SelectionContainsMixedOverrides(const IPMUnknown* modelTargetBoss, const IWorkspace* ws, const K2Vector<ClassID> *categories = nil) = 0;

	/**
		SetAttrsInTarget: Applies attributes from the first target to the second target based on the override rules
				     	     May not have a full set of attributes when done

		NOTE: MUST BE CALLED FROM A COMMAND OR IN A DATABASE TRANSACTION

	 	@param fillTargetBoss		The style target we are filling
	 	@param applyTargetBoss	The style target attribute information we would like to apply (that we are
	 	@param oldTargetBoss		The style target attribute information from the old style
	 	@param clearOverrides	True if we are clearing overrides (attributes which are different then the current style)
	 */
	virtual void            SetAttrsInTarget(IPMUnknown* fillTargetBoss, const IPMUnknown* applyTargetBoss, const IPMUnknown* oldTargetBoss, const IWorkspace *ws, bool16 clearOverrides) = 0;

	/**
	 	FillStyleTargetWithAllSupportedCategories: Fills in the IObjStylesAttrCategoriesList interface on the object style to have all supported categories
	 	@param targetBoss		The style target (kObjectStylesTargetBoss)
	 */
	virtual void FillStyleTargetWithAllSupportedCategories(IPMUnknown *targetBoss) const = 0;

	/**
	 	FillStyleTargetCategoriesFromStyle: Fills in the IObjStylesAttrCategoriesList interface on the object style to have all supported categories 
											of the style passed in.
		@param styleUIDRef  The style we get category information from
	 	@param targetBoss	The style target attribute information we are filling
	 */
	virtual void FillStyleTargetCategoriesFromStyle(const UIDRef& styleUIDRef, IPMUnknown *targetBoss) = 0;

	/**
		Check if the passed in items has non-root object style embedded.
		@param ws			The current workspce
		@param itemList		The item list that we are going to check.
		@return bool16      kTrue indicates there is at least one item has non-root object style embedded.
		                    kFalse indicates there is either no items at all or all items has root object style.
	*/
	virtual bool16 CanItemsBreakLinkFromObjectStyles(IWorkspace* ws, const UIDList& itemList) = 0;

	/**
		Returns true if no circular reference is creating when basing style 1 on style 2
		@param ws			The current workspce
		@param style1		The style we are changing the based on info for
		@param style2		The style to base style1 on
		@return bool16      kTrue if there is no circular reference is creating when basing style 1 on style 2
	*/
	virtual bool16 CanBaseStyleOnStyle(IWorkspace* ws, UID style1, UID style2) const = 0;

	/**
		Query the workspace by passing the database.
		@param db           The database used by querying workspace.
		@return IWorkspace  The result workspace. Caller should be responsible for releasing the interface.
	*/
	virtual IWorkspace* QueryWorkspaceFromDataBase(IDataBase* db) const = 0;

	/**
		Remove the attributes that are not supported anymore.
		@param styleUIDRef  The UIDRef of the style.
	*/
	virtual void RemoveStyleAttributes(const UIDRef& styleUIDRef) const = 0;

	/**
		Get all the categories we supported in object style.
		@return K2Vector<ClassID>	the category list
	*/
	virtual K2Vector<ClassID> GetCateogryList() const = 0;

	/**
		Get observer protocol list see @IObjStylesAttrHandler::GetNotificationProtocolList.
		@param	ws	The workspace containing the styls
		@return ProtocolCollection	protocols to observer
	*/
	virtual ProtocolCollection GetNotificationProtocolListForObjectStyles(IWorkspace* ws) const = 0;

	/**
		Called from the commands, notifys when a object style info changes
		@param itemList	item list to notify -- expected, first item is the workspace
		@param cmd	calling command
		@param cmdClassID	class of calling command
	*/
	virtual void NotifyObjectStyleInfoChanged(const UIDList* itemList, ICommand *cmd, ClassID cmdClassID, const LazyNotificationData* data = nil) const = 0;

	/**
		Called from the commands, notifys when a object style name table changes
		@param itemList	item list to notify -- expected, first item is the workspace
		@param cmd	calling command
	*/
	virtual void NotifyObjectStyleNameTableChanged(const UIDList* itemList, ICommand *cmd, ClassID cmdClassID = kInvalidClass, const LazyNotificationData* data = nil) const = 0;

	/**
		Returns a list of categories which affect the text defaults
		@return	K2Vector<ClassID> the category list for text frame defaults
	*/
	virtual K2Vector<ClassID> GetCategoriesThatAffectTextFrameDefaults() const = 0;
	
	/**
		Returns a list of categories which affect the graphic defaults
		@return K2Vector<ClassID>	the category list for graphic defaults
	*/
	virtual K2Vector<ClassID> GetCategoriesThatAffectGraphicFrameDefaults() const = 0;

	/**
		Check if the styleName passed in is a reserved style name or not.
		@param styleName IN the style name to be checked.
		@return bool16 kTrue indicates that the style name is reserved, otherwise, return kFalse.
	*/
	virtual bool16 IsReservedObjectStyleName(const PMString& styleName) const = 0;

	/**
		TEMPORARY
	*/
	virtual void GetFormattedString(const PMReal& value, const bool16& bHorizontal, const IWorkspace* ws, PMString& outString) = 0;

	/**
		INTERNAL USE ONLY
		Must call within database transaction, will much with your default object styles
		@param ws	The workspace containing the styles
	*/
	virtual void FixTextStylesInDefaultObjectStyles(IWorkspace *ws) = 0;

	/**
		Check if the item has object style or not and the attributes within the passed in category has been applied to it or not.
		@param item [IN] the item to check.
		@param categoryClass [IN] the category ID related to the attributes we are going to check.
		@param objectStyleUIDRef [OUT] if the item has object style, it will be set as the object style's UIDRef.
		@return bool16 kTrue indicates that the item has object style and the passed in category attributes are applied.
	*/
	virtual bool16 IsItemWithCategoryAppliedByObjectStyle(const UIDRef& item, const ClassID& categoryClass, UIDRef& objectStyleUIDRef) const = 0;

	/**
		Query the object style handler with the passed in handler ID. The caller will take the ownship.
		@param handlerClass [IN] the ID of handler.
		@return IObjStylesAttrHandler* the handler interface.
	*/
	virtual IObjStylesAttrHandler* QueryObjectStyleHandler(const ClassID& handlerClass) const = 0;

	/**
		Check if the given item has the same text attributes or not comparing with the given object style's category applied to it.
		@param item [IN] the given item.
		@param category [IN] the given category.
		@bool16 kTrue indicates the attributes are same; otherwise return kFalse.
	*/
	virtual bool16 DoesItemHaveSameTextAttrsWithObjectStyle(const UIDRef& item, const ClassID& category) const = 0;

	/**
		Apply the attributes which need to be applied only after the page item is added to hierarchy. Relevant for size and position attributes in object styles.
	 
		@param list	The UIDList of the pageitems to change
		@param styleTarget	The style target attribute information
		@param ws			The current workspce
		@param categoriesToOverride	A list of the categories to override
	*/
	
	virtual void SetStyleAttrsInUIDListPostAddToHierarchy(const UIDList& list, const IPMUnknown* styleTarget, const IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride)= 0;

};

#endif // define




