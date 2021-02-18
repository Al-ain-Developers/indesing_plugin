//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ILoadUserWorkspaceCmdData.h $
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
//  Data interface for LoadUserWorkspaceCmd
//  
//========================================================================================

#pragma once
#ifndef __ILoadUserWorkspaceCmdData__
#define __ILoadUserWorkspaceCmdData__

#include "IPaletteWorkspace.h"

/** This interface is used for accessing command data for loading workspaces. Workspaces may contain palette location data and/or menu customization data.
	@see kLoadUserWorkspaceCmdBoss.
*/

class ILoadUserWorkspaceCmdData : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ILOADUSERWORKSPACECMDDATA };

		/**	Set the data for which workspace file to load.
			@param name - the name of the workspace file to load.
			@param area - indicates if the file to be loaded is expected to be in the user workspace location(usually in a user preferences folder), or the default workspace location(which is generally in the presets folder)
			@param version - indicates if the "current" version of the workspace should be loaded if present.
		*/
		virtual void SetWorkspaceToLoad(const PMString& name, IPaletteWorkspace::WorkspaceArea area = IPaletteWorkspace::kUserWorkspace, IPaletteWorkspace::WorkspaceVersion version = IPaletteWorkspace::kCurrentVersion) = 0;

		/**	Get the location of the workspace file - either default folder or user folder.
			@return enum indicating which area.
		*/
		virtual IPaletteWorkspace::WorkspaceArea GetWorkspaceArea() const = 0;

		/**	Get the workspace file name.
			@return name of workspace file to load.
		*/
		virtual PMString GetWorkspaceName() const = 0;

		/**	Return whether to load "current" version of a workspace (the one with _CurrentWorkspace appended on filename), or the file itself.
			@return whether to load current version of workspace with given name (if present) or to reset to the original version of the workspace.
					Values are IPaletteWorkspace::kCurrentVersion or IPaletteWorkspace::kOriginalVersion
			@see IPaletteWorkspace.h
		*/
		virtual IPaletteWorkspace::WorkspaceVersion GetVersion() const = 0;
};

#endif // __ILoadUserWorkspaceCmdData__
