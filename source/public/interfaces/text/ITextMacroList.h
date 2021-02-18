//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextMacroList.h $
//  
//  Owner: mramme
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
#ifndef __ITextMacroList__
#define __ITextMacroList__

#include "PMString.h"
#include "EditorHelperID.h"
#include "VirtualKey.h"
#include "K2SmartPtr.h"
#include  "VOSSavedData.h"

class IControlView;

/** structure that holds on to the information for each macro */
struct MacroAttribs
{
	typedef base_type data_type;
	int32 fAccessNum;
	bool16 fStyled;

	// We need to stash the Shortcut if there is one - lets just say this is a pain in the rump...
	VirtualKey fVKey;
	int16 fMods;
	
	bool16 operator==(const MacroAttribs&) const;
};


/** Interface responsible for manipulating the macro keys and their associated text
 ** Information is saved to a separate file in the Prefs directory */

class ITextMacroList : public IPMUnknown
{

public:

	enum	{kDefaultIID = IID_ITEXTMACROLIST};

	/** Use these to modify the macros - will create commands 
	 ** @param key specifies name of new macro 
	  */
	virtual void ProcessAddMacro(PMString key, PMString fullString) = 0;
	virtual void ProcessAddMacro(PMString key, UIDRef otherModel, TextIndex start, int32 length) = 0;
	virtual void ProcessAddMacro(PMString key, const boost::shared_ptr<PasteData>& vosData) = 0;
	virtual void ProcessRemoveMacro(PMString key) = 0;
	virtual void ProcessReplaceMacro(PMString oldKey, PMString newKey, PMString fullString) = 0;
	virtual void ProcessReplaceMacro(PMString oldKey, PMString newKey, UIDRef otherModel, TextIndex start, int32 length) = 0;
	virtual void ProcessSetMacroAction(PMString key, VirtualKey vKey, int16 mods) = 0;

	/** These are for direct non-command access */
	/** Add a macro that is just a string */
	virtual void AddMacro(PMString key, PMString fullString) = 0;
	/** Add a macro from another textmodel */
	virtual void AddMacro(PMString key, UIDRef otherModel, TextIndex start, int32 length) = 0;
	/** Add a macro from another textmodel (using PasteData) */
	virtual void AddMacro(PMString key, const boost::shared_ptr<PasteData>& vosData) = 0;
	/** Replace a macro that is just a string */
	virtual void ReplaceMacro(PMString oldKey, PMString newKey, PMString fullString) = 0;
	/** Replace a macro from another textmodel */
	virtual void ReplaceMacro(PMString oldKey, PMString newKey, UIDRef otherModel, TextIndex start, int32 length) = 0;
	/** Replace a macro from another textmodel (using PasteData) */
	virtual void ReplaceMacro(PMString oldKey, PMString newKey, const boost::shared_ptr<PasteData>&vosData) = 0;
	virtual void RemoveMacro(PMString key) = 0;

	/** Add an actionID to this macro, so it can be executed with it's own key command */
	/** Send kInvalidActionID to remove an action from this key */
	virtual void SetMacroAction(PMString key, ActionID actionID) = 0;

	virtual bool16 IsMacro(PMString key) = 0;

	/** Use these methods to get and set whether the macro should be inserted with or without style information */
	virtual bool16 IsStyledMacroInsert(PMString key) = 0;
	virtual void SetStyledMacroInsert(PMString key, bool16 bStyled) = 0;

	/** Get the data for this text macro - caller must delete return saved data  */
	virtual boost::shared_ptr<PasteData> GetMacroBinding(PMString key) = 0;
	virtual boost::shared_ptr<PasteData> GetMacroAt(int32 pos) = 0;
	virtual boost::shared_ptr<PasteData> GetMacroAtAction(ActionID actionID) = 0;
	/** Get a string representation (for tool tips, non-styled inserting, etc) */
	virtual PMString GetStringMacroBinding(PMString key) = 0;
	virtual PMString GetStringMacroAt(int32 pos) = 0;
	virtual PMString GetStringMacroAtAction(ActionID actionID) = 0;

	virtual PMString GetKeyAt(int32 pos) = 0;
	virtual int32 GetKeyPos(PMString key) = 0;

	/** Returns the action associated with this key */
	virtual ActionID GetActionAt(PMString key) = 0;
	virtual int32 GetActionPos(ActionID actionID) = 0;

	virtual int32 GetNumMacros() = 0;
	
	/** These are for loading and unloading the private storage (if applicable) */
	virtual void LoadMacros(UID storageUID = kInvalidUID) = 0;
	virtual void UnloadMacros() = 0;

	/** Seems to be the only way to hook up the dialog's writing widget with a macro 
	 ** This most likely never needs to be called by anybody for data reasons, this is
	 ** only to set up the UI */
	virtual bool16 AttachMacroToEditor(PMString macro, IControlView *editWidget, const boost::shared_ptr<PasteData>& selectedText) = 0;

	// NOTE: Never use this - I tried to make this protected, but the compiler whines...
	virtual void UpdateMacroShortcut(PMString key, VirtualKey vKey, int16 mods) = 0;

	/** These are getting and setting the auto expand flag */
	virtual bool16 GetAutoExpand() const = 0;
	virtual void SetAutoExpand(const bool16 expand) = 0;
};

#endif
