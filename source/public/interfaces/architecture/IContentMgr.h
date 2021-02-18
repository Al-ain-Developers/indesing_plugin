//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IContentMgr.h $
//  
//  Owner: Robin Briggs
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
//  Purpose:
//  Manages all content added to the document. Keeps track of what classes
//  and tags are in the document, what plug-ins added them, etc.
//  
//========================================================================================

#pragma once
#ifndef __IContentMgr__
#define __IContentMgr__

// ----- Interfaces -----

#include "IPMUnknown.h"
#include "ITagRegistry.h"
#include "PluginMetadata.h"

// ----- Includes -----

#include "K2Vector.h"


class PMString;
class FormatID;
class IDocument;
class IGatherIDStreamData;

/** Manages all content added to the document. Keeps track of what classes
	and tags are in the document, what plug-ins added them, etc.
*/
class IContentMgr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICONTENTMGR };
			
		/** This struct gives the application information about a given plug-in
			The information allows the app to perform conversions and allow users
			to turn off only plug-ins that the app can be run without.
		*/
		struct PluginInfo	{
			/** name of the plug-in */
			PMString					fPluginName;		// name of the plug-in
			/** version number of the plug-in (app version number) */
			int32 						fDocMajorVersion;	// version number of the plug-in
			/** version number of the plug-in (plug-in rev in this app version) */
			int32						fDocMinorVersion;
			/** kTrue if the plugin is not running. */
			bool16						fIsMissing;			// kTrue if the plugin is not running.
			/** The priority of the plug-in
				@see ITagRegistry::TagPriority
			*/
			ITagRegistry::TagPriority	fPriority;			// default, critical, or ignore
			
			PluginMetadata				fMetadata;			// extra plug-in info: company name, url, alert
			PluginID					fPluginID;
		};

		typedef K2Vector<PluginID> PluginIDList;
		
		/** ----- Conversion of the content manager bybasses the regular conversion manager because
			the content manager is required for conversion. This means that conversion must happen
			from the its ReadWrite method, which can be triggered either by instantiating the 
			interface in the case of a read, or by flushing the interface from the object model
			cache in the case of a write.
			We must be able to convert the content manager from older versions to the current
			version. 
			The following methods deal with interagating the content manager for status of
			conversions.
		*/
		
		/** Return the current Content Manager status. It either failed or succeeded while reading
			its persistent state or while trying to convert state on output.
			@return - kSuccess = succeeded
		*/
		virtual ErrorCode GetStatus() const = 0;
				
		/** If there are plug-ins missing, put up an alert asking 
			user if they want to continue with the open.
			FOR INTERNAL USE ONLY
			@param *sourcePub - The file we are checking the status on
			@param alertOnList - the list of the plug-ins to show in the alert
			@return - kTrue if the open should be continued (or if no plug-ins are missing) otherwise false.
		*/
		virtual bool16 AlertMissingPlugins(const IDFile *sourcePub, const PluginIDList& alertOnList) = 0;

		virtual void GatherMissingPlugins(PluginIDList* alertOnList) = 0;

		/** Figure out if document contains plug-ins that were missing
			last time document was edited.
			@param *removedPlugins - Plug-ins in this list will be removed by the current conversion
			@param *ignoredPlugins - Plug-ins in this list will be marked as ignorable by the current conversion
		*/
		virtual void CheckForMissingPlugins(const K2Vector<PluginID> *removedPlugins = nil, const K2Vector<PluginID> *ignoredPlugins = nil) = 0;
		
		/** If a missing plugin is now present, call it's FixUpData function to inform it.
			Mark the plugin as no longer missing; this information will be saved
			with the document if the document is saved.
			@param *doc - The document we are fixing plug-ins in
			@param &list - The list of plug-ins last known to be missing.
		*/
		virtual void FixupMissingPlugins(IDocument *doc, const K2Vector<PluginID> &list) = 0;

         /** Returns true if warning for missing plug-ins is turned off for this document.
             For internal use only.
         */
        virtual bool16 IgnoreAllMissingPlugins() const = 0;

         /** Allows the client to set whether or not we should warn on missing plug-in data
         */
        virtual void SetIgnoreAllMissingPlugins() = 0;

		/** Mark all the Content Manager's plugins as "untouched" */
		virtual void MarkAllPluginsUntouched() = 0;
  		/** Used by the Conversion Manager to strip unused plugins from the list */
  		virtual void RemoveUntouchedPlugins() = 0;
 		
		/**	Declares that the tag has been written into the
			document. This is usually called from IPMPersist
			at the time the tag is first written out
			@param newTag - The implementation ID to add
			@param context - The class that owns the tag being written
		*/
		virtual void AddTag(ImplementationID newTag, ClassID context) = 0;
		
		/** Declares that the tag has been written into the
			document. This is usually called from the database
			when a UID is allocated.
			@param clsID - The classID to be added.
		*/
		virtual void AddClass(ClassID clsID) = 0;
		
		/** Returns the number of missign plug-ins 
			@return - The number of missing plug-ins
		*/
		virtual int32 GetMissingPluginCount() const = 0;
		
		/** Returns the ID of the Nth missing plug-in
		`	@param n - The index value of the plug-in you want
			@param *info - This optional parameter will be filled with the PluginInfo for the returned plug-in
			@return - The iD of the plugin
		*/
		virtual PluginID GetNthMissingPlugin(int32 n, PluginInfo *info) const = 0;

		/** Returns a list of all of the missing plugins
			@param &list - The list of PluginIDs that are missing
		*/
		virtual void GetMissingPlugins(K2Vector<PluginID> &list) const = 0;
		
		/** returns the number of plugins */
		virtual int32 GetPluginCount() const = 0;

		/** Used in cooperation with GetNextPlugin to iterate through the set of plug-ins
			@param *info - This optional parameter will be filled with the PluginInfo for the returned plug-in
			@return - The iD of the first plugin
			@see GetNextPlugin
		*/
		virtual PluginID GetFirstPlugin(PluginInfo *info = nil) const = 0;

		/** Used in cooperation with GetFirstPlugin to iterate through the set of plug-ins
			@param plugin - The plug-in in the iterator you already have. (The next plugin will be returned)
			@param *info - This optional parameter will be filled with the PluginInfo for the returned plug-in
			@return - The iD of the next plugin (kInvalidPlugin if at the end of the list)
			@see GetFirstPlugin
		*/
		virtual PluginID GetNextPlugin(PluginID plugin, PluginInfo *info = nil) const = 0;
			
		/** Returns information about a plug-in
			@param plugin - Plug-in for which you want information
			@param *info - Will be filled with the plug-ins information
			@return - kTrue if the plug-in was found, kFalse if not
		*/
		virtual bool16 GetPluginInfo(PluginID plugin, PluginInfo *info) const = 0;
			
		/** Are there any missing plug-ins that are critical?
			@return - kTrue if there are critical plug-ins missing
		*/
		virtual bool16 IsMissingCriticalPlugins() const = 0;
			
		/** Are there any missing plug-ins that are default plug-ins?
			@return - kTrue if there are default plug-ins missing
		*/
		virtual bool16 IsMissingDefaultPlugins() const = 0;

		/** Find the ID of the plug-in that owned the specified class when it was written to the database
			@param clsID - The class that you are looking for a plug-in for
			@param &plugin - Will be filled with the appropriate PluginID
			@return - Returns an error code if an answer cannot be found, kSuccess otherwise.
		*/
		virtual ErrorCode GetPluginForClass(ClassID clsID, PluginID &plugin) const = 0;

		/** Find the ID of the plug-in that owned the specified implementation when it was written to the database.
			@param implID - The Implementation that you are looking for a plugin for
			@param &plugin - Will be filled with the appropriate PluginID
			@return - Returns an error code if an answer cannot be found, kSuccess otherwise.
		*/
		virtual ErrorCode GetPluginForImplementation(ImplementationID implID, PluginID &plugin) const = 0;
		
		/** This method along with GetCheckUIDsOnNextOpen allows support for document recovery.
			Call this method to indicate that UIDs should be checked next time this document is opened.
			@param doIt - kTrue will cause the UIDs to be checked next time this file is opened.
			@see GetCheckUIDsOnNextOpen
		*/
		virtual void SetCheckUIDsOnNextOpen(bool16 doIt) = 0;

		/** This method along with SetCheckUIDsOnNextOpen allows support for document recovery.
			@return - kTrue means that we should check UIDs next time we open this file
			@see SetCheckUIDsOnNextOpen
		*/
		virtual bool16 GetCheckUIDsOnNextOpen() const = 0;
					
		/** Update the plig-in's format number, if it changed
			@param plugin - The plugin ID we are currently dealing with
			@param &format - The most recent format number for the plugin
		*/
		virtual void VerifyPluginFormatNumber(PluginID plugin, const FormatID &format) = 0;

		/** Remove all information associated with the caller's plugin.
			@param plugin - The PluginID which you want to remove
		*/
		virtual void RemovePlugin(PluginID plugin) = 0;

		/** Set the plugin's priority to "Ignore".
			@param plugin - The PluginID to be changed.
		*/
		virtual void IgnorePlugin(PluginID plugin) = 0;

		/** Add plug-in content to the document
		*/
		virtual void ProcessDeferredContent() = 0;

		/** Clear internal data for this class
		*/
		virtual void Clear() = 0;

		/** Returns the name of the application that the file was created in. When a file
			is first opened, the application name of the file may be different than the 
			application name of the running program while conversion is taking place. 
			Once the file has been converted, the content mgr application name and the 
			running application will always be the same.
			@return - A string containing the name of the application
		*/
		virtual const PMString& GetApplicationName() const = 0;

		/** For internal Use only! Set the name of the application
			@param &newName - The new name for the app to use
		*/
		virtual void SetApplicationName(const PMString& newName) = 0;

#ifdef DEBUG
		/** Run internal checks to make sure that there are no unreferenced UIDs */
		virtual void VerifyContentMgr(IGatherIDStreamData *data) = 0;
		
		/** Dump the data about missing plug-ins to a file */
		virtual void DumpMissingPluginData() = 0;
		
		/** Dump data about the content manager to a file */
		virtual void DumpContentMgrData() = 0;
#endif
};


#endif // __IContentMgr__