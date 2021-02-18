//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPaletteWorkspace.h $
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

#pragma once
#ifndef __IPaletteWorkspace__
#define __IPaletteWorkspace__

#include "AppUIID.h"

class ISAXAttributes;


/** Interface for managing Palette Workspaces. Workspaces are saved as XML files
	in the "Workspaces" subfolder of the preferences folder.
	As of CS4, the model for workspaces has changed somewhat. 
	Instead of "bookmarks in a book,"  workspaces are more like rooms in a house. 
	If you rearrange the furniture in your living room, leave and go into your kitchen, 
	and then return to the living room, you would expect the furniture to still be in 
	its new position. 
	
	Under the hood, two versions of each workspace file are managed, and the application
	automatically saves the most recent arrange of palettes and panels as this
	"current" version. By default, whenever a user loads or switches to a workspace, 
	by default the application loads the "current" version of it. 
	There is a notion of an "active" workspace, which is saved as the name of the most 
	recently loaded workspace. The "current" version of this one is the one that gets 
	loaded at start up. The user can "reset" a workspace, in which case the application
	deletes the "current" version and reloads the "original".
*/
class IPaletteWorkspace : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPALETTEWORKSPACE };
	
	// -----------------------------------------------------------
	/**@name Manage workspaces in standard locations */
	//@{

	typedef enum { kUserWorkspace, kDefaultWorkspace } WorkspaceArea;
	/** 
		Gets the number of workspaces in the specified area(user workspace or default workspace)
		Do not call this repeatedly!  Calling GetWorkspaceCount() will gather and cache the workspaces for subsequent
		calls to GetNthWorkspaceName()
		@param type determines whether you want user workspaces or default (application supplied) workspaces
		@return the number of workspaces in the specified area
	*/
	virtual int32			GetWorkspaceCount( WorkspaceArea area = kUserWorkspace ) const = 0;

	/** 
		Gets the name of the nth workspace in the specified area. n is the index.
		@param index of the workspace whose name you want
		@param area determines whether you want user workspaces or default (application supplied) workspaces
		@return name of the specified workspace
	*/
	virtual PMString		GetNthWorkspaceName( int32 n, WorkspaceArea area = kUserWorkspace ) const = 0;

	/** 
		Checks the name passed in to determine if it is a valid name or duplicate name.
		@param name is passed in as the potential workspace name
		@param errorString if method returns kNameInvalid, this string will contain the error msg
		@return kNameValid if the name is fine, kNameDuplicate if this name already exists, kNameInvalid if the name isn't valid
	*/
	typedef enum { kNameValid, kNameInvalid, kNameDuplicate } ValidationCode;
	virtual ValidationCode		ValidateWorkspaceName( const PMString& name, PMString* errorString ) const = 0; 

	typedef enum { kCurrentVersion, kOriginalVersion } WorkspaceVersion;	// TODO kWorkingVersion

	/** 
		Saves the current palette configuration as a user workspace with the specified name. Optionally includes
		palette positions and/or custom menu information. At least one of these two parameters must be true (or
		else workspace would be empty!). 
		Typically a call to SaveWorkspace with is preceded by a called to SaveActiveWorkspace to update the current version of the previous workspace.
		Typically also followed by a call to SetActiveWorkspaceName if you want the newly saved workspace to be the active one.
		@param name of the workspace you are saving
		@param includePalettes whether or not the workspace will include palette positions
		@param includeMenus whether or not the workspace will include custom menu information
		@param version determines whether you want to save the "current" version of a workspace, or to save an "original" version.
	*/
	virtual void			SaveWorkspace(const PMString& name, bool16 includePalettes, bool16 includeMenus, WorkspaceVersion = kOriginalVersion ) const = 0;

	/** 
		Load a workspace from the specified area. This becomes the new name of the "active" workspace.
		@param name The name of the workspace you'd like to load. Should be the base name of the workspace.
		@param area determines whether you want user workspaces or default (application supplied) workspaces
		@param version determines whether you want to load the "current" version of a workspace if present, or to reset to the "original" version.
				The original version is the one either in kDefaultWorkspace area that shipped with the application, or one that the user created
				via the "New Workspace" dialog in the kUserWorkspace. If an "current" version isn't present, the "original" will be loaded instead.
		@return kFalse if the workspace could not be loaded.  Typically because file wasn't found.
		@see GetActiveWorkspaceName
	*/
	virtual bool16			LoadWorkspace( const PMString& name, WorkspaceArea area = kUserWorkspace, WorkspaceVersion = kCurrentVersion) const = 0;

	/** 
		Delete a user workspace 
		@param name The name of the workspace you'd like to delete. Should be the base name of the workspace.
		@param version determines whether to delete the "original" version of a workspace, or just the "current" version. When deleting original,
					any current version that exists is also deleted. Should be the base name of the workspace.
		@return kTrue if a workspace with the specified name was found and deleted.
	*/
	virtual bool16			DeleteWorkspace( const PMString& name, WorkspaceVersion version = kOriginalVersion ) const = 0;


	// -----------------------------------------------------------
	/**@name Load/Save by specifying file */
	//@{

	/** 
		Saves current palette configuration to the specified file.  For Workspaces to show up
		in the UI, they must be saved to the appropriate location.  Use the above methods for convenience
		@param workspaceFile specified a fileSpec that the workspace will be written to.
		@param includePalettes whether or not the workspace will include palette positions
		@param includeMenus whether or not the workspace will include custom menu information
	*/
	virtual	void			SaveWorkspace(IDFile workspaceName, bool16 includePalettes, bool16 includeMenus ) const = 0;

	/** 
		Load palette configuration from the specified file and set the palettes accordingly.  
		To load a standard configuration workspace, use the above methods for convenience
		@param workspaceFile specified a fileSpec that is a Palette Workspace XML file to read in
		@return kFalse if the workspace could not be loaded.  Typically because file wasn't found
	*/
	virtual	bool16			LoadWorkspace(IDFile workspaceFile) const = 0;

	// -----------------------------------------------------------
	/**@name ActiveWorkspace */
	//@{

	/** Called on Shutdown to save the current workspace
		Should only be called by PaletteMgr
	*/
	virtual void			SaveActiveWorkspace() const = 0;

	/** On startup, without SavedData, this is called to arrange the palettes to their most recent configuration
		Should only be called by PaletteMgr
		@return kTrue if an active workspace existed and was loaded, kFalse otherwise
	*/
	virtual bool16			LoadActiveWorkspace() const =  0;

	/** Return the name of the current workspace. This is the last workspace the user chose and is stored in IID_IACTIVEWORKSPACENAMEPREF interface on kWorkspaceBoss
		@return PMString the name (localized) of the current workspace. 
	*/
	virtual PMString		GetActiveWorkspaceName() const = 0;

	/** Sets the name of the current workspace. Called automatically whenever a workspace is loaded,
		so usually not necessary for external callers to use this method.
		Stores name of workspace in IID_IACTIVEWORKSPACENAMEPREF interface on kWorkspaceBoss
		@return PMString the name (localized) of the current workspace. 
	*/
	virtual void			SetActiveWorkspaceName(const PMString& name) const = 0;

	// -----------------------------------------------------------
	/**@name LoadStartupWorkspace */
	//@{

	/** We have a specific default workspace that we load the first time we startup
		Calling this will load that workspace.  
		@param resetMenus if true, menus will be reset also as if choosing menu Window > Workspace > Reset Menus.  If false, menus will not be affected
		@return kFalse if the startup workspace could not be found and loaded.  Typically because file wasn't found
	*/
	virtual bool16			LoadStartupWorkspace(bool16 resetMenus = kTrue) const = 0;

	// -----------------------------------------------------------
	/**@name LoadingWorkspace */
	//@{

	/** Call this to determine whether or not we are in the process of loading a workspace
		@return kTrue if we are in the process of loading a workspace, kFalse if we are not loading a workspace
	*/
	virtual bool16			LoadingWorkspace() const = 0;

	// -----------------------------------------------------------
	/**@name DynamicPanelCreationData */
	//@{
	
	/** Data type sent along with the kPaletteWorkspaceLoadingDynamicPanelMsg, recipient should recreate the panel according to the data
		found in the XML attributes and should return the new panel's widgetID in the struct. */
	typedef struct
	{
		/** panel attributes found in workspace */
		ISAXAttributes* fAttrs;
		/** id of dynamic panel found in workspace (clients can use a range of WidgetID's to determine if panel belongs to them) */
		WidgetID				fOldPanelWidgetID;
		/** id of newly created dynamic panel - client creates the new panel, adds it to the panel manager, and return the new widgetID in this field of the struct */
		WidgetID				fNewPanelWidgetID;
	} DynamicPanelCreationData;

	/** INTERNAL USE ONLY. Return the "current" name of the workspace, w/ the "_CurrentWorkspace" suffix.
		@return the base name of the workspace.
		@see WorkspaceVersion
	*/
	virtual PMString		MakeCurrentVersionName(const PMString& originalVersionName) const = 0;

	/** INTERNAL USE ONLY. Return the base name of the workspace, w/o the "_CurrentWorkspace" suffix.
		@return the base name of the workspace.
		@see WorkspaceVersion
	*/
	virtual PMString		MakeOriginalVersionName(const PMString& currentVersionName) const = 0;

	/** INTERNAL USE ONLY. Called at startup to initialize the workspace manager.
	*/
	virtual void			Initialize() const = 0;

	/** INTERNAL USE ONLY. Used to rename the preferences of Essentials Workspace to Essentials Classic
	*/
	virtual bool16 RenameEssentialsWorkspacePrefs() const = 0;

	// INTERNAL USE ONLY. Return if the New Essentials workspace FTUE is shown once.
	virtual bool16		IsNewEssentialsWorkspaceShown() const = 0;

};

#endif //__IPaletteWorkspace__
