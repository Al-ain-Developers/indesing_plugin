//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/MenuNodeID.h $
//  
//  Owner: Matt Joss
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

#ifndef __MENUNODEID__
#define __MENUNODEID__

#include "NodeID.h"
#include "IPMStream.h"
#include "SuppressedUIPanelID.h"

// The MenuNodeID contains the full menu path(including the menu item name) and the ActionID.  There could be 2 menus with the same menu path,
// so we need actionID too to make sure they are unique.  Full menu path is something like Main:File:Print

extern WIDGET_DECL const char* kUICustomizationPopupPrefixString;
extern WIDGET_DECL const char* kSuppressedUIPanelPopupPrefixString;

class WIDGET_DECL MenuNodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kMenuNodeID }; 


		static	NodeID_rv		Create() { return new MenuNodeID(); }
		static	NodeID_rv		Create(const PMString& fullMenuPath, ActionID action) { return new MenuNodeID(fullMenuPath, action); }
		static	NodeID_rv		Create(const PMString& fullMenuPath) { return new MenuNodeID(fullMenuPath); }

		virtual ~MenuNodeID() {}
		
		virtual	NodeType		GetNodeType() const { return kNodeType; } 
		virtual int32			Compare(const NodeIDClass* NodeID) const;
		virtual NodeIDClass*	Clone() const;
		virtual void			Read(IPMStream*	stream);
		virtual void			Write(IPMStream* stream) const;
		virtual PMString		GetDescription() const;
		
		// returns the full path of the menu, e.g. Main:File:Print..., or Tag_PanelPopup:Load Tags...
		// This must be used when calling menu methods in ISuppressedUIWithXMLFileData
		PMString		 		GetRealMenuPath() const;

		// returns the path defined in the panel.  Contains prefixes, etc.  i.e. Popups:Tag_PanelPopup:Load Tags...
		const PMString& 		GetBBPanelMenuPath() const { return fBBPanelMenuPath; }
		
		// just returns the menu item name, e.g. Print...
		PMString 				GetMenuName() const;
		PMString				GetMenuAcceleratorFromPath(PMString menuPath) const;
		ActionID				GetActionID() const { return fActionID; }

		bool16					CanSuppress() const;
		bool16					CanCustomize() const;
		bool16					CanHide() const;

		// Accelerators
		PMString				GetOriginalAccelerator() const { return GetMenuAcceleratorFromPath(fBBPanelMenuPath); }

		PMString				GetAccelerator() const { return fAccelerator; }
		void					SetAccelerator(PMString accelerator){ fAccelerator = accelerator; }

		bool16					GetAcceleratorLock() const { return fAcceleratorLocked; }
		void					SetAcceleratorLock(bool16 lock) { fAcceleratorLocked = lock; }

	private:
		MenuNodeID(): fAcceleratorLocked(kFalse){}
		MenuNodeID(const PMString& fullMenuPath, ActionID action, bool16 lock):fBBPanelMenuPath(fullMenuPath), fActionID(action), fAcceleratorLocked(lock){}
		MenuNodeID(const PMString& fullMenuPath, ActionID action):fBBPanelMenuPath(fullMenuPath), fActionID(action), fAcceleratorLocked(kFalse){}
		MenuNodeID(const PMString& fullMenuPath):fBBPanelMenuPath(fullMenuPath), fActionID(kInvalidActionID), fAcceleratorLocked(kFalse){}

		PMString	fBBPanelMenuPath;
		ActionID	fActionID;
		bool16		fAcceleratorLocked;
		PMString	fOriginalAccelerator;
		PMString	fAccelerator;
};

#endif //__STRINGNODEID__
