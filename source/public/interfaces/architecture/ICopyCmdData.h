//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICopyCmdData.h $
//  
//  Owner: robin briggs
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
//  Data interface for copying page items.
//  
//========================================================================================

#pragma once
#ifndef __ICopyCmdData__
#define __ICopyCmdData__

#include "IPMUnknown.h"
#include "PageItemScrapID.h"
#include "UIDRef.h"
#include "PMPoint.h"

class UIDList;
class PMMatrix;
class ICommand;
class IDataExchangeHandler;

/** Data interface for copying and duplicating page items.
 */
class ICopyCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOPYCMDDATA };

	/**	Set up the data need for a copy, paste, or duplicate command.
		@param rootCmd, root command to hold all sub commands, typically is a kCopyCmdBoss, kDuplicateCmdBoss or other command that supports IID_ICOPYCMDDATA. 
		@param inputItems the list of items. This interface takes ownership of the pointer.
		@param parent the destination parent for the command (often the scrap or a spread layer)
		@param destinationHandler Sets the target dataHandler. Defauts to nil, which means the destination is the clipboard.
	 */
	virtual void Set(ICommand *rootCmd, UIDList *inputItems, const UIDRef& parent, IDataExchangeHandler* destinationHandler = nil) = 0;
	
	/**	If the item being copied was a sub item of a frame or group then we
		want to capture the transform of all its parents so that when it is
		pasted it appears correctly oriented.
		@param transform 
	 */
	virtual void SetTransform(const PMMatrix& transform) = 0;

	/**	If the item being copied (pasted) needs to be offset then an offset should be supplied
		@param offset IN the offset in pasteboard coordinates.
	 */
	virtual void SetOffset(const PMPoint& offset) = 0;

	/**	Set the parent for the target of the copied items. Could be the scrap, a spread layer, or other.
		@param the UIDRef of the parent for the target of the copied items.
	 */
	virtual void SetParent(const UIDRef& parent) = 0;	

	/**	Return the parent for the target of the copied items. Could be the scrap, a spread layer, or other.
		@param parent the destination parent for the command (often the scrap or a spread layer)
	 */
	virtual const UIDRef& GetParent() const = 0;	

	/**	Returns the list of items that have been set.
		@return the list of items that have been set.
	 */
	virtual const UIDList *GetInputItems() const = 0;

	/**	Returns the value from SetTransform.
		@return const PMMatrix&
	 */
	virtual const PMMatrix& GetTransform() const = 0;

	/**	Used to determine if SetTransform has been called.
		@return kTrue if SetTransform was called, kFalse otherwise.
	 */
	virtual bool16 GetTransformWasExplicitlySet() const = 0;

	/**	Returns the value from SetOffset. Defaults to 0.0, 0.0
		@return the offset to move the item(s)
	 */
	virtual const PBPMPoint& GetOffset() const = 0;

	/**	Returns the complete list of items, including items from any and all sub-commands.
		@return A UID list of all copied items.
	 */
	virtual const UIDList *GetTotalList() = 0;

	/**	Return the copy command for an item, may return nil.
		@param id UID of item to copy.
		@return The copy command (ICommand*).
	 */
	virtual ICommand *GetCopyCmd(UID id) = 0;

	/**	Returns the command from the Set method above.
		@return ICommand 
	 */
	virtual ICommand *GetRootCmd() const = 0;

	/**	Return a particular sub command
		@param clsID the ClassID of the command you are searching for.
		@param which specify the index of command with the given ClassID you are searching for.
		@param index When called recursively, index should always be non-nil. 
		@return ICommand the requested command, may be nil.
	 */
	virtual ICommand *GetCopyCmd(ClassID clsID, int32 which, int32 *index = nil) = 0;

	/**	Commands often need access to the dataHandler that will be the target of a copy-to-scrap command.
		but the lifetime data handlers is very short because we revert scrap databases frequently.
		ReleaseDestinationHandler should be called soon after the command has completed,
		and definitely before the affected scrap gets reverted.
	 */
	virtual void ReleaseDestinationHandler() = 0;

	/**	Returns the target dataHandler. If nil, this means the destination is the clipboard.
		@return The target data exchange handler.
	 */
	virtual IDataExchangeHandler* GetDestinationHandler() const = 0;	

	/**	If the color profiles from the source document should be copied to the target, set to kTrue.
		@param bCopyProfiles IN Set to kTrue if you need to copy color profiles. Defaults to kFalse.
	 */
	virtual void SetCopySourceCMSProfilesToTarget( bool16 bCopyProfiles ) = 0;

	/**	Retrieve value set in SetCopySourceCMSProfilesToTarget for whether color profiles
		should be copied to target.
		@return kTrue if color profiles should be copied. kFalse otherwise.
	 */
	virtual bool16 CopySourceCMSProfilesToTarget() const = 0;

};


#endif // __ICopyCmdData__
