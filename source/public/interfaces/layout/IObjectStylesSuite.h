//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectStylesSuite.h $
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

#ifndef __IOBJECTSTYLESSUITE__
#define __IOBJECTSTYLESSUITE__

#include "IPMUnknown.h"
#include "IObjectStyleInfo.h"
#include "IObjStylesAttrHandler.h"

#include "StyleClashResolutionTypes.h"
#include "GenericID.h"
#include <map>

class IStyleGroupHierarchy;
/**
	@ingroup layout_suite
*/
class ObjStyleDialogLockStateObj 
{
public:
	ObjStyleDialogLockStateObj() {};
	virtual ~ObjStyleDialogLockStateObj() {};
};		// Used by CreateLocakStateObj
class IObjectStylesSuite : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IOBJECTSTYLESSUITE};

	/**
		True if you can create a new object style from the current selection
	*/
	virtual bool16 CanCreateNewObjectStyleFromSelection() const = 0;

	/**
		Creates a new Object Style which has the attributes of the current selection
		@param styleName [IN] name of new style to being created.
		@param createdStylePath [OUT] full path of created style.
		@param	parentUID	[IN] UID of the parent group where the style is being created. kInvalidUID to create at root level
		@param	position	[IN] position with in the parent, where style is going to be created. -1 to create at the end.
	*/
	virtual ErrorCode CreateNewObjectStyleFromSelection(PMString styleName, PMString& createdStylePath, UID parentUID = kInvalidUID, int32 position = -1) = 0;
	
	/**
		Create new object style.
		@param iObjectStyleInfo IN: the info about this object style.
		@param IPMUnknown IN: the target(attributes) within the object style.
		@param	parentUID	[IN] UID of the parent group where the style is being created. kInvalidUID to create at root level
		@param	position	[IN] position with in the parent, where style is going to be created. -1 to create at the end.
	*/
	virtual ErrorCode CreateNewObjectStyle(IObjectStyleInfo* iObjectStyleInfo, IPMUnknown* target, UID parentUID = kInvalidUID, int32 position = -1) = 0;

		/**
		 Duplicates the Object Style
		 @param iObjectStyleInfo IN: the info about this object style.
		 @param IPMUnknown IN: the target(attributes) within the object style.
		 @param editStyleName IN: the name of the style to be edited.
		@param numApplies IN:		used only by the dialog, set to the number of times we have applied this command
	*/
	virtual ErrorCode EditObjectStyle(IObjectStyleInfo* iObjectStyleInfo, IPMUnknown* target, const PMString& editStyleName, int32 numApplies = 0) = 0;

	/**
		Return true if you can apply an object style to the given selection
	*/
	virtual bool16 CanApplyObjectStyle() const = 0;

	/**
		Apply the object style to the current selection.
		@param name the name of style to be applied.
		@param bApplyDefaultGraphicStyle indicates that we always apply normal graphic frame style.
		@param overrideExistingAttrs indicates that shall we clear override.
		@param applyEmptyCatWithRoot apply unchecked categories with root
		@param affectAppliedItems indicates that we only apply the style to the object with the same style(clear overrdes)
		return ErrorCode.
	*/
	virtual ErrorCode ApplyObjectStyle(const PMString name, const bool16 bApplyDefaultGraphicStyle, bool16 overrideExistingAttrs, bool16 applyEmptyCatWithRoot, bool16 affectAppliedItems = kFalse) = 0;

	/**
		Clears the overrides on the current style
	*/
	virtual ErrorCode ClearObjectStyleOverrides() = 0;

	/**
		Returns true if we can apply the none style to the unchcecked categories and it will change the object (clear non-none attrs)
	*/
	virtual bool16 CanClearUnCheckedOverridesWithNoneStyle() const = 0;
	
	/**
		Apply the attributes from root style which are not defined in the style.
	*/
	virtual ErrorCode ClearOverridesNotDefinedByStyle() = 0;

	/**
		True if you can modify the style list
	*/
	virtual bool16 CanModifyStyleList() const  = 0;

	/**
		True if you can modify the styles associated with these names
	*/
	virtual bool16 CanModifyStyles(const K2Vector<PMString>& styleIndexs) const  = 0;

	/**
		True if you can delete the styles associated with these names
	*/
	virtual bool16 CanDeleteStyles(const K2Vector<PMString>& styleIndexs) const  = 0;

	/**
		Deletes the objects styles from the StyleNameTable for the current selection
	*/
	virtual ErrorCode DeleteObjectStyles(const K2Vector<PMString>& styleIndexs, const PMString& styleToReplaceWith, const bool16& bPerserveFormat = kFalse) = 0;

	/**
		Sorts the Object Style List
	*/
	virtual ErrorCode SortObjectStyles() = 0;


	/**
		Loads the objects styles from the another document.
		@param globalClashResolutionStrategy IN: global clash resolution strategy.
		@param sourceFile IN:    source file which we load from.
		@param importMap IN:	 import styles.
		@param clashMap IN:		 styles that are conflict with existing styles.
		@param resolveMap IN:	 result styles after resolving the conflicts.
	*/
	virtual ErrorCode LoadObjectStyles(const StyleClashResolutionTypes::GlobalClashResolutionStrategy& globalClashResolutionStrategy, const IDFile& sourceFile,
									   const std::map<PMString,bool32>& importMap,
									   const std::map<PMString,bool32>& clashMap,
									   const std::map<PMString,StyleClashResolutionTypes::StyleClashResolutionStrategy>& resolveMap) = 0;

	/**
		Export the objects styles to a document
	*/
	virtual ErrorCode ExportObjectStyles(const IDFile& targetFile, const K2Vector<PMString>& objectStyles) = 0;

	/**
		Import the objects styles from the another document
	*/
	virtual ErrorCode ImportObjectStyles(const IDFile& sourceFile) = 0;

	/**
		Renames the current style
	*/
	virtual ErrorCode RenameObjectStyle(const int32 styleIndex, const PMString& newName ) = 0;

	/**
		Replaces the attrs in a style with new ones
	*/
	virtual ErrorCode ReplaceObjectStyles(const K2Vector<PMString>& styleNames, const PMString& replaceWith) = 0;

	/**  
	    Can the object style of the current selection be redefined based on selected overrides.
        return bool16 = kFalse if the selection contains mixed overrides, no overrides, or mixed styles, otherwise return kTrue.
    */
    virtual bool16 CanRedefineObjectStyle() const = 0;

	/**  
	    Can clear the overrides for the object styles in the current selection.
		return bool16 = kFalse if the selection does NOT contain overrides, otherwise return kTrue.
    */
    virtual bool16 CanClearOverrides() const = 0;


    /**  
		Redefines the style of the current selection based on the text attributes
        of the current selection.  (Any overrides become part of the style.)
        @return kSuccess on success otherwise an error.
    */
    virtual ErrorCode RedefineStyle() = 0;


	/**
		Changes the default text style for the current database
		@param newStyleName
	*/
	virtual ErrorCode ChangeDefaultTextStyle(const PMString& newStyleName) = 0;

	/**
		Returns the default text style
		@return PMString
	*/
	virtual PMString GetDefaultTextStyle() = 0;

	/**
		Changes the default graphic style for the current database
		@param newStyleName
	*/
	virtual ErrorCode ChangeDefaultGraphicStyle(const PMString& newStyleName) = 0;

	/**
		Returns the default graphics style
		@return PMString
	*/
	virtual PMString GetDefaultGraphicStyle() = 0;

	/**
		Changes the default frame grid style for the current database
		@param newStyleName
	*/
	virtual ErrorCode ChangeDefaultFrameGridStyle(const PMString& newStyleName) = 0;

	/**
		Returns the default frame grid style
		@return PMString
	*/
	virtual PMString GetDefaultFrameGridStyle() = 0;

	/**
		 Duplicates the Object Styles
		 @param styleNames IN: the names of the styles to duplicate
		 @param styleNamesCreated OUT: the names of the styles to created
	*/
	virtual ErrorCode DuplicateObjectStyles(const K2Vector<PMString>& styleNames, K2Vector<PMString>& styleNamesCreated) = 0;
	
	/**
		 True if you can move the object style to a new location in the list
		 @param styleNames	vector of the style names to move
		 @param dropBefore	the position you are dropping to, default value = -1 means don't consider this value
	*/
	virtual bool16 CanMoveObjectStyles(const K2Vector<PMString>& styleNames, const int32 dropBefore = -1) = 0;

	/**
		 Moves the Object Styles in the list
		 @param styleNames	vector of the style names to move
		 @param dropBefore	the position you are dropping to
	*/
	virtual ErrorCode MoveObjectStyles(const K2Vector<PMString>& styleNames, const int32 dropBefore) = 0;


	/**
		Get the object style PMStrings of the current selection.
		return K2Vector<PMString> object style UID list.
	*/
	virtual K2Vector<PMString>	GetCurrentObjectStyles() const = 0;

	/**
		Get the object style name of the nth entry in the style table
		returnPMString object style name
	*/
	virtual PMString	GetNameOfNthStyle(const int32 n) const = 0;

	/**
		Get the object style index of the style name passed in
		return int32 object style index
	*/
	virtual int32	GetStyleIndexFromName(const PMString& name) const = 0;

	/**
		Gets the number of object styles in the current list
	*/
	virtual int32	GetNumObjectStyles() const = 0;

	/**
		Get the unique duplicate object style name with the base name provided.
	*/
	virtual PMString	GetUniqueDuplicateName(IStyleGroupHierarchy* hierParent, const PMString& baseName) const = 0;

	/**
		Get the unique object style name.
		// STOLEN FROM TextStyleTargetServer, refactor some year...
	*/
	virtual void		CreateStyleName(IStyleGroupHierarchy* hierParent, PMString * styleName) const = 0;
	

	/**
		Check if we can we disconnect the object styles from the current selection.
		return bool16 = kTrue if there is an object in the selection with object style embeded; 
		otherwise, return kFalse.
	*/
	virtual bool16    CanDoBreakLinkToObjectStyles() const = 0;

	/**
		Break the link between object style and current selection. 
		return ErrorCode = kSuccess if we are done.
	*/
	virtual ErrorCode BreakLinkToObjectStyles() = 0;

	/**
		Break the link of all the page items with the provided object styles.
		return ErrorCode = kSuccess if we are done.
	*/
	virtual ErrorCode BreakLinkFromProvidedObjectStyles(const K2Vector<PMString> styleList) = 0;

	/**
		Returns true if no circular reference is creating when basing style 1 on style 2
		@param style1		The style we are changing the based on info for
		@param style2		The style to base style1 on
		@return bool16      kTrue if there is no circular reference is creating when basing style 1 on style 2
	*/
	virtual bool16 CanBaseStyleOnStyle(PMString& style1, PMString& style2) const = 0;

	/**
		Returns a representation of the information (created from the style named) in the style for the UI to use
		@param name	The name of the style to create from
	*/
	virtual IPMUnknown* QueryStyleTargetFromStyle(const PMString& name) const = 0;

	/**
		Returns a representation of the information in the style (created from the selection) for the UI to use
		@param basedOnStyleName The name of the style we get categories info.
	*/
	virtual IPMUnknown* QueryStyleTargetFromSelection(const PMString& basedOnStyleName) const = 0;

	/**
		Return true if the selection has object style overrides
		@param objecStyleUID	the uid of the object style to check against, if kInvalidUID uses current object style of the selection
	*/
	virtual bool16    SelectionOverridesObjStyle(UID objecStyleUID = kInvalidUID) const = 0;

	/**
		Return true if the selection has object style overrides
		@param name	the name of the object style to check against.
	*/
	virtual bool16    DoesObjectStyleHaveOverride(const PMString& name) const = 0;

	/**
		Return the style which this style is based on
		@param name style's name to find based on style for
	*/
	virtual PMString    GetStylesBasedOnStyleName(const PMString& name) const = 0;
	/**
		Return the style's keyboard shortcut
		@param name style's name to find based on style for
		@param modifiers OUT: the modifiers
	*/
	virtual VirtualKey    GetStylesKeyboardShortcut(const PMString& name, int16* modifiers) const = 0;

	/**
        Returns the list of the current overrides attributes in the selection
    */
    virtual const ObjStyleCategoryAttrMap        GetCurrentOverridesAttributeMap() const = 0;

    /**
        Returns the list of the current overrides names  in the selection
    */
    virtual const ObjStyleCategoryNameMap        GetCurrentOverridesNameMap() const = 0;

	/**
		Check if current selection has [Normal Grid] applied to it or not.
		return bool16 kTrue = there is [Normal Grid] applied; otherwise return kFalse.
	*/
	virtual bool16  SelectionContainsFrameGridStyle() const = 0;

	/**
		Check if selection has mixed overrides or not.
		return bool16 kTrue = there is mixed overrides; otherwise return kFalse.
	*/
	virtual bool16  SelectionWithMixedOverrides() const = 0;

	/**
		INTERNAL USE ONLY
	*/
	virtual ObjStyleDialogLockStateObj* CreateLocakStateObj(const PMString& styleName) const = 0;
};

#endif
