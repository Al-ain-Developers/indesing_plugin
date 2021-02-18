//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITrapStyleListMgr.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __ITrapStyleListMgr__
#define __ITrapStyleListMgr__

#if PRAGMA_ONCE
#pragma once
#endif

//#include "IGenStlEdtListMgr.h"

#include "PrintID.h"
#include "K2Vector.h"

class ITrapStyle;
class UIDList;
class RangeProgressBar;

//========================================================================================
// CLASS ITrapStyleListMgr
//========================================================================================
/**	An interface for managing the trap style list in the application or the document
	workspace.
*/
class ITrapStyleListMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRAPSTYLELISTMGR };
	
	enum {kInvalidStyleIndex = -1, kNoStyleIndex = 0, kDefaultStyleIndex };
	
	//___________________________________________________________________________________
	//	Initialize method
	//	NOTE:	This hould be called only if the list is empty. If the list is already populated
	//			this method will assert and do nothing.
	//___________________________________________________________________________________

	/**	Initialize the trap style list.
		@param doCreateBasicStylesOnly if true it only creates the basic styles.
		@return kSuccess if successful otherwise returns an error code.
	*/
	virtual ErrorCode Init					(bool16	doCreateBasicStylesOnly = kTrue) = 0;
	
	//___________________________________________________________________________________
	//	There are basic accessors
	//___________________________________________________________________________________

	/**	Returns the number styles in the list.
	*/
	virtual int32 GetNumStyles				(void) = 0;

	/**	Gets the name of the nth style.
		@param index specifies the nth style to get
		@param pName is the style name
		@return kSuccess if successful otherwise returns an error code.
	*/
	virtual ErrorCode GetNthStyleName		(int32 index, PMString *pName) = 0;

	/**	Return whether or not the nth style is editable.
		@param index specifies the nth style to get
		@return true if editable otherwise false.
	*/
	virtual bool32 IsNthStyleEditable		(int32 index) = 0;

	/**	Return whether or not the nth style can be deleted.
		@param index specifies the nth style to get
		@return true if can be deleted otherwise false.
	*/
	virtual bool32 IsNthStyleDeleteable		(int32 index) = 0;

	/**	Return the index of the given style name.
		@param pName specifies sytle name
		@return style index in the list. 
	*/
	virtual int32 GetStyleIndexByName		(const PMString& pName) = 0;

	/**	Return the index of the given style UID.
		@param styleUID specifies sytle UID
		@return style index in the list. 
	*/
	virtual int32 GetStyleIndexByUID		(UID styleUID) = 0;

	/**	Return an unique style name within the style list based on the specified baseName.
		@param baseName is the base name
		@return an unique style name. 
	*/
	virtual PMString GetUniqueStyleName		(PMString& baseName) = 0;
	
	/**	Obtains the UID of the Nth style object.
		@param index specifies the style index
		@return the UIDRef of the nth style
	*/
	virtual UIDRef GetNthStyleRef			(int32 index) = 0;
	
	/**	Returns the default "No Trap Style" style name.
	*/
	virtual PMString GetNoStyleName	(void) = 0;

	/**	Returns the default "No Trap Style" style UIDRef.
	*/
	virtual UIDRef GetNoStyleUIDRef	(void) = 0;
	
	/**	Returns the style name for the "Default" style.
	*/
	virtual PMString GetDefaultStyleName	(void) = 0;

	/**	Returns the default "Default" style UIDRef.
	*/
	virtual UIDRef GetDefaultStyleUIDRef	(void) = 0;
	
	/**	Get number of reserved styles in the list.
		Currently two default styles are supported: [No Trap Style] and "Default"
		Reserved styles are typically grouped at the beginning of the list.
	*/
	virtual int32 GetNumReservedStyles		(void) = 0;
	
	//___________________________________________________________________________________
	//	These methods process a command to add, copy, delete, and change a style.
	//___________________________________________________________________________________

	/**	Set the style name for the nth style.
		@param index specifies the nth style
		@param name is the new style name
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode SetNthStyleName		(int32 index, PMString& name) = 0;

	/**	Add a style with the specified name .
		@param index specifies the nth style
		@param name is the new style name
		@param nameLocked is true if name can not be edited,
		@param editLocked is true if none of the properties can be edited
		@param deleteLocked is true if style cannot be delete
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode AddStyle				(PMString& name, bool16 nameLocked = kFalse, bool16 editLocked = kFalse, bool16 deleteLocked = kFalse) = 0;
	
	/**	Copy the nth style with the specified new style name.
		@param index specifies the nth style
		@param newName is the new style name
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode CopyNthStyle			(int32 srcIndex, PMString& newName) = 0;

	/**	Delete the nth style .
		@param index specifies the nth style
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode DeleteNthStyle		(int32 index) = 0;

	/**	Edit the nth style with the specified style settings.
		@param index specifies the nth style
		@param iStyleSetting is the new style name
		@param updateLockInfo true if the style's lock properties should be udpated
		@param nameLocked is true if name can not be edited
		@param editLocked is true if none of the properties can be edited
		@param deleteLocked is true if style cannot be delete
		@return kSuccess if successful otherwise returns an error code
	*/
	virtual ErrorCode EditNthStyle			(int32 index, ITrapStyle* iStyleSetting, bool16 updateLockInfo = kFalse, bool16 nameLocked = kFalse, bool16 editLocked = kFalse, bool16 deleteLocked = kFalse) = 0;

	/**	These manipulate the list.  They do NOT do any corresponding maintenance
		of the style object -- they're available for the use of commands which
		manipulate the list. They should not be used out side of a command!
	*/

	/**	Insert a style UID in list.
		@param uid is the style UID to insert
		@index is the position to insert at. If index is -1, then uid is appended at the end.
	*/
	virtual void ListInsert					(UID uid, int32 index = -1) = 0;

	/**	Remove a style UID from the list.
		@param index is the style to remove
	*/
	virtual void ListRemove					(int32 index) = 0;

	/**	Replace nth style with the specified style UID.
		@param uid is the new style UID
		@param index is the style to replace
	*/
	virtual void ListReplace				(UID uid, int32 index) = 0;

	/**	Copy style settings from srcStyle to the dstStyle.
		@param srcStyle is the source style to copy from.
		@param dstStyle is the target style.
	*/
	virtual ErrorCode CopyStyleData			(UIDRef srcStyle, UIDRef dstStyle) = 0;
	
	/**	Import the style list specified by the srcListMgrRef into the current list.
		This method may be processing one or more commands, the caller should enclosed with command
		sequence for redo/undo.
		@param pProgressBase If a RangeProgressBar proc is passed, progress will be updated.
		@return kSucess if successful otherwise returns an error code.
	*/
	virtual ErrorCode ImportStyles			(const UIDRef&, RangeProgressBar* = nil) = 0;

	/**	Export a list of styles specified by indexList in the current list to the
		destination list manager specified by dstListMgrRef.
		@param indexList specifies a list of style to export. If the indexList is empty, export all styles.
		@param pProgressBase If a RangeProgressBar proc is passed, progress will be updated.
		@return kSucess if successful otherwise returns an error code.
	*/
	virtual ErrorCode ExportStyles			(const UIDRef&, K2Vector<int32>& indexList, RangeProgressBar* = nil) = 0;
	
	//___________________________________________________________________________________
	//	These methods facilitate application of styles to the document.
	//___________________________________________________________________________________
	
	/**	kExcludeDefault indicate default styles should be excluded from the search.
	*/
	enum { kExcludeDefault 		= (1L<<0) };
	/**	kExcludeDefault indicate all styles that cannot be edited should be excluded from the search.
	*/
	enum { kExcludeEditLocked 	= (1L<<1) };
	/**	kExcludeDefault indicate all styles that cannot be deleted should be excluded from the search.
	*/
	enum { kExcludeDeleteLocked = (1L<<2) };

	/**	Returns a list style that are used in the database.
		@param styeList is the list of style references to check. If style list is empty,
		then all styles are checked.
		@param flag indicate which style if any to exclude.
		@return a list of referenced styles
	*/
	virtual UIDList GetReferencedStyles (const UIDList& styeList, int32 flag) = 0;
};

#endif // __ITrapStyleListMgr__

// End, ITrapStyleListMgr.h.
