//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMenuCustomizationData.h $
//  
//  Owner: lance bushore
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
#ifndef __IMenuCustomizationData__
#define __IMenuCustomizationData__

#include "AppUIID.h"
#include "IPMUnknown.h"
#include "ActionID.h"
#include "K2Vector.h"
#include "BravoForwardDecl.h"

class IXMLOutStream;

/** This interface is used to get and set menu customization info, on the workspace boss, or on the kSetMenuCustomizationPrefsCmdBoss */ 
class IMenuCustomizationData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMENUCUSTOMIZATIONDATA };
		
	typedef enum {
			kNoMenuColor = -1,
			kBlueMenuColor = 0,
			kGrayMenuColor = 1,
			kGreenMenuColor = 2,
			kOrangeMenuColor = 3,
			kRedMenuColor = 4,
			kVioletMenuColor = 5,
			kYellowMenuColor = 6,
			
			kNumberOfMenuColors = 7		// It's intentional that the number of colors is 7 and not 8.  "kNoMenuColor" isn't considered a real color.
		} tMenuColor;
		
		typedef enum {
			kNormal = 0,
			kSelected,
			kDisabled,
			
			kNumberOfStates
		} tMenuState;
		
		/** structure describing a submenu */
		struct CustomizedSubMenuPath
		{	
			typedef object_type data_type;
			PMString		fSubMenuPath;
		};
		
		/** structure describing a colorized menu item */
		struct MenuColorStruct
		{
			typedef base_type data_type;
			MenuColorStruct(ActionID id,  tMenuColor index) : fActionID(id), fColorIndex(index){}
			
			ActionID  	fActionID;
			tMenuColor	fColorIndex;
		};
		
		/** structure to describe a colorized submenu */
		struct SubMenuColorStruct
		{
			typedef object_type data_type;
			SubMenuColorStruct(IMenuCustomizationData::CustomizedSubMenuPath menuPath,  tMenuColor index) : fColorizedSubMenuPath(menuPath), fColorIndex(index){}
			
			IMenuCustomizationData::CustomizedSubMenuPath fColorizedSubMenuPath;
			tMenuColor		fColorIndex;
		};

		/** Get the name of the default menu customization set. */
		virtual const PMString& GetDefaultMenuSetName() const = 0;
		
		/** Set the menu set info - name, modified state, whether or not this set is a preset(as opposed to user-created), and indicate if the file should be read from disk */
		virtual bool16		SetCurrentMenuSetInfo(const PMString& menuSetName,bool16 isModified,bool16 isPreset,bool16 readShortcutSetFromDisk)= 0;

		/** Get the name of the current menu customization set */
		virtual const PMString&	GetCurrentMenuSetName() const= 0;
		
		/** Check if the current menu customization set is modified from the version on disk */
		virtual bool16		IsCurrentMenuSetModified() const= 0;
		
		/** Check if the current menu customization set is a preset(as opposed to user-created) */
		virtual bool16		IsCurrentMenuSetPreset() const= 0;

		/** Hides a submenu with the specified path */
 		virtual void		HideSubMenu(const PMString& menuPath) = 0;
		
		/** Shows a submenu with the specified path */
		virtual void		ShowSubMenu(const PMString& menuPath) = 0;
		
		/** Check if submenu with the given path is hidden.*/
		virtual bool16		IsSubMenuHidden(const PMString& menuPath) const= 0;

		/** Get the list of all the currently hidden submenus.*/
		virtual const K2Vector<CustomizedSubMenuPath>& 		GetHiddenSubMenus() const = 0;
		
		/** Set the list of the currently hidden submenus.*/
		virtual void		SetHiddenSubMenus(const K2Vector<CustomizedSubMenuPath>& hiddenSubMenuList) = 0;

		/** Clear the list of the currently hidden submenus.*/
		virtual void		ClearAllHiddenSubMenus() = 0;
		
		/* Hides a menu by action id. This may hide multiple menu items that share an ActionID */
		virtual void		HideMenuAction(const ActionID action) = 0;
		
		/** Show a menu by action id. */
		virtual void		ShowMenuAction(const  ActionID action) = 0;
		/** Check if menu item with given ActionID is hidden.*/
		virtual bool16		IsMenuActionHidden(ActionID action) const = 0;

		/** Get the list of all the currently hidden menu items.*/
		virtual const K2Vector<ActionID>& 		GetHiddenMenuActions() const = 0;

		/** Set the list of the currently hidden menu items.*/
		virtual void		SetHiddenMenuActions(const K2Vector<ActionID>& hiddenActionList) = 0;

		/** Clear the list of the currently hidden menu items.*/
		virtual void		ClearAllHiddenActions() = 0;
		
		/** Set the color for a submenu */
		virtual void		SetSubMenuColor(const PMString& menuPath,  tMenuColor colorIndex) = 0;
		
		/** Get color of submenu with given path */
		virtual  tMenuColor		GetSubMenuColor(const PMString& menuPath) const = 0;

		/** Get the list of all the currently colored submenus.*/
		virtual const K2Vector<SubMenuColorStruct>& 		GetColoredSubMenus() const = 0;

		/** Set the list of the currently colored submenus.*/
		virtual void		SetColoredSubMenus(const K2Vector<SubMenuColorStruct>& coloredSubMenuList) = 0;

		/** Clear the list of the currently colored submenus.*/
		virtual void		ClearAllColoredSubMenus() = 0;


		virtual void		SetMenuActionColor(const  ActionID action,  tMenuColor colorIndex) = 0;
		/** Get color of menu item with given ActionID */
		virtual tMenuColor		GetMenuActionColor(ActionID action) const = 0;

		/** Get the list of all the currently colored menu items.*/
		virtual const K2Vector<MenuColorStruct>& 		GetColoredMenuActions() const = 0;

		/** Set the list of the currently colored menu items.*/
		virtual void		SetColoredMenuActions(const K2Vector<MenuColorStruct>& coloredActionList) = 0;

		/** Clear the list of the currently colored menu items.*/
		virtual void		ClearAllColoredMenuActions() = 0;

		/** Return kTrue if any menus, submenus are hidden or colored, kFalse otherwise. */
		virtual bool16		GetMenusAreHiddenOrColorized() const = 0;

		/** Clear all hidden menus, submenus, and colorization on menus and submenus */
		virtual void		ClearAllMenusAndColorization() = 0;

		/** Write menu customization to XML. Returns kTrue if successful. */
		virtual bool16 WriteXMLMenuFile(IXMLOutStream* s) const = 0;

		/** Save current customization to a file. Returns kTrue if successful. */
		virtual bool16 SaveCurrentMenuSetToFile(const PMString& menuSetName) const = 0;
		typedef enum {
			/** kMenuFileNoError success*/
			kMenuReadFileNoError = 0, 
			/** kMenuFileNotFound File was not found*/
			kMenuFileNotFound, 
			/** kMenuFileWrongPlatform File appears to be from wrong platform(i.e. trying to open windows shortcut set on mac)*/
			kMenuFileWrongPlatform, 
			/** kMenuFileFormatWrongOrCorrupt File isn't a known type of shortcut set*/
			kMenuFileFormatWrongOrCorrupt, 
			/** kMenuFileFormatIncompatible File isn't a version that can be understood*/
			kMenuFileFormatIncompatible
		} MenuSetReadFileError; 

		/** Reads menu customization from stream */
		virtual MenuSetReadFileError ReadXMLMenuFile(IPMStream* s) = 0;
};

#endif // __IMenuCustomizationData__
		