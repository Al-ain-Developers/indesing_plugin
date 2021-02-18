//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignSetPropsCmdData.h $
//  
//  Owner: Jon Pugh
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
#ifndef __IASSIGNSETPROPSCMDDATA__
#define __IASSIGNSETPROPSCMDDATA__

#include "IPMUnknown.h"
#include "IAssignment.h"
#include "AssignmentID.h"
#include "CommandID.h"
#include "URI.h"

class IAssignedDocument;

/** The data class for the IAssignSetPropsCmd.
	@see IAssignSetPropsCmd
*/
class IAssignSetPropsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IASSIGNSETPROPSCMDDATA };
		
		/**
			Set the data to use for the AssignSetPropsCmd.
			@param name - A pointer to a new name, or nil to not change the name.
			@param file - A pointer to a new file path, or nil to not change the file path.
			@param user - A pointer to a new user name, or nil to not change the user name.
			@param color - A pointer to the new color, or nil to not change the color.
			@param options - A pointer to the new export options, or nil to not change the export options.
			@param dirty - A pointer to the new dirty flag, or nil to not change the dirty state 
			@param includeLinkedWhenPackage - A pointer to the new include linked files when packaging flag, or nil to not change the state 
			@parm uri - A pointer to a new uri, or nil to not change the uri.
			(typically allowing the other changes to dirty the assignment). 
		*/
		virtual void Set(const PMString* name, const PMString* file, 
							const PMString* user, const UID* color, const IAssignment::AssignmentExportOptions* options,
							const bool16* dirty, const bool16* includeLinkedWhenPackage, const URI* uri = nil) = 0;

		/**
			Fetch the specified name
			@return - A PMString pointer which may be nil, do not deallocate
		*/
		virtual const PMString* GetName() = 0;

		/**
			GetFile description
			@return - A PMString pointer which may be nil, do not deallocate
		*/
		virtual const PMString* GetFile() = 0;

		/**
			GetUser description
			@return - A PMString pointer which may be nil, do not deallocate
		*/
		virtual const PMString* GetUser() = 0;

		/**
			GetColor description
			@return - A pointer which may be nil, do not deallocate
		*/
		virtual const UID* GetColor() = 0;

		/**
			GetExportOption description
			@return - A pointer which may be nil, do not deallocate
		*/
		virtual const IAssignment::AssignmentExportOptions* GetExportOption() = 0;

		/**
			GetDirty description
			@return - A pointer which may be nil, do not deallocate
		*/
		virtual const bool16* GetDirty() = 0;

		/**
			GetIncludeLinkedFilesWhenPackage description
			@return - A pointer which may be nil, do not deallocate
		*/
		virtual const bool16* GetIncludeLinkedFilesWhenPackage() = 0;

		/**
			GetURI description
			@return - A URI pointer which may be nil, do not deallocate
		*/
		virtual const URI* GetURI() = 0;
};

typedef InterfacePtr<IAssignSetPropsCmdData> IAssignSetPropsCmdDataPtr;

#endif	// __IASSIGNSETPROPSCMDDATA__
