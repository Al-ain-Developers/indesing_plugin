//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightUtils.h $
//  
//  Owner: Matt Phillips
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
//  General (application-wide) preflight utilities. Note that there are other utility 
//  files such as IPreflightProfileUtils which address specific kinds of objects.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "Utils.h"

#include "IPreflightArtworkShapeContext.h"
#include "IPreflightArtworkTextContext.h"
#include "IPreflightArtworkTableContext.h"
#include "IViewPortAttributes.h"
#include "IGraphicsPort.h"
#include "TransformTypes.h"

class IPreflightManager;
class IPreflightObjectModel;
class IPreflightProfileManager;
class IPreflightRuleManager;
class IPreflightProcessManager;
class IPreflightOptions;
class IDocument;
class IDataBase;
class ISubject;
class IPreflightProcess;
class IPreflightProfile;
class IPreflightBookOptions;
class IShape;
class ISpread;

/**	General (application-wide) preflight utilities. Note that there are other utility 
	files such as IPreflightProfileUtils which address specific kinds of objects.

	You normally get one of these via

		Utils<IPreflightUtils> iPreflightUtils;

	or if you just need a one-off call:

		Utils<IPreflightUtils()->QueryPreflightManager();
*/
class IPreflightUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTUTILS };

public:
	/**	Obtain the application-wide preflight manager interface.
		@return The refcounted interface.
	*/
	virtual IPreflightManager *QueryPreflightManager() const = 0;

	/**	Obtain the application-wide object model information interface.
		@return The refcounted interface.
	*/
	virtual IPreflightObjectModel *QueryObjectModel() const = 0;

	/**	Obtain the application-wide rule manager interface.
		@return The refcounted interface.
	*/
	virtual IPreflightRuleManager *QueryRuleManager() const = 0;

	/**	Obtain the application-wide process manager interface.
		@return The refcounted interface.
	*/
	virtual IPreflightProcessManager *QueryProcessManager() const = 0;

	/**	Obtain the preflight profile manager for the application-level or 
		document-level profiles.
		@param iDoc IN The document to use; or if nil, the application-level manager is returned.
		@return The refcounted preflight manager interface, or nil if unsuccessful.
	*/
	virtual IPreflightProfileManager *QueryProfileManager(IDocument* iDoc) const = 0;

	/**	Obtain the preflight profile manager for the application-level or document-level profiles.
		This version takes a database pointer and will automatically query the document from there.
		(Unless the passed-in pointer is nil, in which case it will always get application-level.)

		@param iDataBase IN The database to use; or if nil, the application-level manager is returned.
		@return The refcounted preflight manager interface, or nil if unsuccessful.
	*/
	virtual IPreflightProfileManager *QueryProfileManager(IDataBase* iDataBase) const = 0;

	/**	Obtain the global preflight nonpersistent subject, ie changes that are messages rather than
		model changes. The following interfaces/messages broadcast on this subject.

			IID_IPREFLIGHTPROCESSMANAGER:
				kPreflightProcessUpdateMsg - Something about a process changed
				kPreflightProcessListChangedMsg - The list of processes changed
			IID_IPREFLIGHTEVENTWATCHER
				kPreflightEventAppResume - Application gained focus

		@return The refcounted ISubject interface, or nil if unsuccessful.
	*/
	virtual ISubject* QueryAppMessageSubject() const = 0;

	/**	Obtain the preflight document-level (or app-level) subject related to persistent data. 
		This subject hosts the following interested-in interfaces:
			IID_IPREFLIGHTPROFILEMANAGER (changes to the profile list) 
			IID_IPREFLIGHTPROFILE (changes to individual profile)
			IID_IPREFLIGHTOPTIONS (changes to the preflight options)
			IID_IPREFLIGHTSETTINGSCHANGEINFO (app only; @see IPreflightSettingsChangeInfo)

		@param iDB The database of the document, or nil to query the app-level subject.
		@return The refcounted ISubject interface, or nil if unsuccessful.
	*/
	virtual ISubject* QueryDocumentSubject(IDataBase* iDB) const = 0;

	/** Obtain the preflight options for the specified database.
		@param iDataBase IN The database to use; or if nil, the application-level preflight options is returned.
		@return The refcounted preflight options interface, or nil if unsuccessful.		
	*/
	virtual IPreflightOptions* QueryPreflightOptions (IDataBase* iDB) const = 0;

	/** Given a document, look for an active preflight process and return it. Note that this ONLY
		finds processes that use the kPreflightContinuousProcessSelectorID selector.

		@param iDocDB IN The document in which you're interested.
		@return A refcounted preflight process, or nil if there is no active process.
	*/
	virtual IPreflightProcess* QueryProcessForDocument(IDataBase* iDocDB) const = 0;

	/** Apply the given options to the document. This is a bit different from simply copying the options:
		The method analyzes the current and new options and determines what changes if any need to be
		made to the active processes. For example if the new setting is preflight-off and there is an
		active preflight process, that process is removed; if the profile name and/or embeddedness changes
		the process is modified accordingly.

		In addition to the above the method also copies all of the options to the doc's preflight settings,
		but not via a command.

		@param iDocDB IN The doucment you want to apply the settings to.
		@param iNewOptions IN The new options to apply.
		@param skipDeltaAnalysis IN True to not consider the current settings (other than reusing an
			existing process) but rather impose the new ones as if the old ones were in a not-necessarily
			accurate state. This should only be passed when setting up options for a newly opened document,
			because otherwise the current status should be up to date.
	*/
	virtual void ApplyOptionsToDocument
		(
			IDataBase* iDocDB, 
			const IPreflightOptions* iNewOptions
		) const = 0;

	/** Get the document's embedded profile, if any. Currently this is just the 0th entry in the
		document's profile manager list, because a document either has zero or one profile. But in
		the future this might be more elaborate, with multiple embedded profiles possible; thus this
		utility method.

		@param iDocDB IN The doc you want the profile for.
		@return A refcounted interface, or nil if the document has no embedded profile.
	*/
	virtual IPreflightProfile* QueryEmbeddedProfile(IDataBase* iDocDB) const = 0;

	/** Get the application-level working profile. Note that this may or may not match the
		default profile, ie the undeletable one called "Default".

		@return A refcounted interface. Should be nil iff an error occurs.
	*/
	virtual IPreflightProfile* QueryWorkingProfile() const = 0;

	/** Get the application-level default profile. This is the one called "Default Profile".
		This method simply asks the application profile manager to get the profile with that
		name and return it.

		@return A refcounted interface. Should be nil iff an error occurs.
	*/
	virtual IPreflightProfile* QueryDefaultProfile() const = 0;

	/** Start a group in the port that marks the scope of a part of an item (eg stroke, fill).
		@param iPort IN The port into which to begin the group.
		@param itemUID IN The UID of the shape object.
		@param subpartID IN The subpart identifier.
	*/
	virtual void BeginShapeGroup(IGraphicsPort* iPort, UID itemUID, ClassID subpartID) const = 0;

	/** End a group in the port that marks the scope of a part of an item (eg stroke, fill).
		@param iPort IN The port into which to begin the group.
		@param itemUID IN The UID of the shape object.
		@param subpartID IN The subpart identifier.
	*/
	virtual void EndShapeGroup(IGraphicsPort* iPort, UID itemUID, ClassID subpartID) const = 0;

	/** Helper class that provides auto stack based declaration of subpart groups. Automatically
		checks the viewport attributes before issuing groups (since they may otherwise confuse
		other kinds of artwork ports).
		@see BeginShapeGroup
		@see EndShapeGroup
	*/
	class AutoShapeGroup
	{
		IGraphicsPort* fPort;
		bool fIssueGroup;
		ClassID fSubPartID;
		UID fUID;

	public:
		/** The ctor passes all the useful information and determines whether a grouup will actually
			be declared based on external and internal evaluation.

			@param iPort IN The port. This is inspected for its vpattrs.
			@param iThing IN The boss being drawn. The UID is extracted and used in the group.
			@param subPart IN The subpart of the thing.
			@param issueGroup IN True to issue the group; false otherwise. Used if the group is 
				conditional on some external condition; this allows the stack object to exist in
				the correct scope (if it's put in an 'if' then the scope is too narrow).
		*/
		AutoShapeGroup
			(
				IGraphicsPort* iPort, 
				IPMUnknown* iThing, 
				ClassID subPartID, 
				bool issueGroup = kTrue
			)
			: fPort(iPort), fUID(kInvalidUID), fIssueGroup(kFalse), fSubPartID(subPartID)
		{
			if (issueGroup)
			{
				InterfacePtr<IViewPortAttributes> iAttr(iPort, UseDefaultIID());
				fIssueGroup = (iAttr && iAttr->GetAttr(kPreflightIssuePortGroupsVPAttr));
				if (fIssueGroup) 
				{
					fUID = ::GetUID(iThing);
					Utils<IPreflightUtils>()->BeginShapeGroup(iPort, fUID, subPartID);
				}
			}
		}

		~AutoShapeGroup()
		{
			if (fIssueGroup) Utils<IPreflightUtils>()->EndShapeGroup(fPort, fUID, fSubPartID);
		}
	};

	/** Selects the page item. This should probably be in some other util, but..
		@param itemRef IN The UIDRef of the item to select.
		@return True if successful, false otherwise.
	*/
	virtual bool SelectPageItem(const UIDRef& itemRef) const = 0;

	/** Gets a description of a page (eg "1" for page 1) via IPageList.
		@param iPageShape IN The page shape.
		@return A string for the description.
	*/
	virtual PMString GetPageDescription(IShape* iPageShape) const = 0;

	/** Gets a description of a spread (eg "2-3" for spread 2/3) via IPageList.
		@param iSpread IN The spread.
		@return A string for the description.
	*/
	virtual PMString GetSpreadDescription(ISpread* iSpread) const = 0;

	/** Get the bounding box of the pages of the spread.
		This function duplicates exactly: r = iSpread->GetPagesBounds( coordSpace)
		Use that instead.
		@param iSpread IN The spread you're interested in.
		@param coordSpace IN The space you want the coords in.
		@param r OUT Receives the bounding box.
	*/
//	virtual void GetSpreadRect(ISpread* iSpread, Transform::CoordinateSpace coordSpace, PMRect& r) const = 0;

	/**	Create a new preflight profile in the specified database.
		This differs from the one in IPreflightFacade in that this method takes a target database.
		
		@param iTargetDB IN the database to create the profile in.
		@param profileName IN The name to use for the new profile. 
			@see IPreflightProfileManager::GetUniqueProfileName to ensure a unique name.
		@param profileDesc IN The longer description of the profile.
		@param prepopulateRules IN kTrue if you want to prepopulate the rule list for the new profile with
			all rules registered with the rule manager; the rules will be disabled but present with
			default settings. If kFalse, the profile will not have any rules and will need to be 
			added 'manually.'
		@param newProfileUID receives the UID of new profile. If profile is not created, kInvalidUID is returned.
		@return kSuccess or an error code from the command.
	*/
	virtual ErrorCode NewProfile 
		(
			IDataBase* iTargetDB,
			const PMString& profileName,
			const PMString& profileDesc,
			bool prepopulateRules,
			UID* pNewProfileUID
		) = 0;

	/**	Update one profile by copying all parameters from another profile. This includes
		everything that is a property of a profile: name, description, the list of rules
		and their settings, and so on. It does not change the relationship of the destination
		profile to its parent profile manager (if any).

		The source profile doesn't need to be in a database, but the destination does since
		this is a command based method. (The data is copied from the source profile into the
		command, which is why the source profile can be memory-based.) The use of UIDRef for
		the destination profile is meant to reinforce this restriction.

		@see IPreflightProfileUtils::CopyProfileData for a utility that can be used to copy
			data to an in-memory profile (of course this is not done through a command).

		@param dstProfileRef is the UIDRef of the destination profile to which parameters 
			will be copied.
		@param iSrcProfile is the source profile from which parameters will be copied.
			This profile can be in memory or in a database.
		@return kSuccess or an error code from the command.
	*/
	virtual ErrorCode CopyProfileData
		(
			const UIDRef& dstProfileRef,
			const IPreflightProfile* iSrcProfile
		) = 0;
		
	/**	Set the name and/or description of a preflight profile.

		@param dstProfileRef is the UIDRef of the destination profile.
		@param setName IN True to set the name; false to leave it alone.
		@param newname IN The new name (if setName is true).
		@param setDesc IN True to set the description; false to leave it alone.
		@param newDesc IN The new descriptino (if setDesc is true).
		@return kSuccess or an error code from the command.
	*/
	virtual ErrorCode SetProfileStrings
		(
			const UIDRef& dstProfileRef,
			bool setName,
			const PMString& newName,
			bool setDesc,
			const PMString& newDesc
		) = 0;


	/** Given a book database, obtain its persistent book options. Returned interface is const
		to reflect the fact that one should not change it except via a command (ie 
		SetPreflightBookOptions). These options are the ones that populate the book preflight
		options dialog by default.

		@param iBookDB IN The database corresponding to the book.
		@return A refcounted book options interface.
	*/
	virtual const IPreflightBookOptions* QueryBookOptions
		(
			IDataBase* iBookDB
		) const = 0;

	/** Given a book database, obtain its active book options, if there are any. The active
		book options are those assigned to the active book preflight. These represent a 
		(possibly modified) version of those that exist at the book level (@see QueryBookOptions).
		Will be nil if there is no active preflight on the book.

		@param iBookDB IN The database corresponding to the book.
		@return A refcounted book options interface.
	*/
	virtual const IPreflightBookOptions* QueryActiveBookOptions
		(
			IDataBase* iBookDB
		) const = 0;

	/** This is a utility method designed to compliment SetPreflightBookOptions. If you want
		to change the options for a book, you can first make a copy of them using this method,
		modify the copy, and set it in via SetPreflightBookOptions. Or, if you want to specify
		all of the settings you can pass nil for the iSrc and you'll get a fully default set 
		of options.

		@param iSrc IN The source interface to copy from, or nil to create a fully default set.
		@return A refcounted in-memory (nonpersistent) options interface. When this is fully
			dereferenced, it simply disappears.
	*/
	virtual IPreflightBookOptions* CloneBookOptions
		(
			const IPreflightBookOptions* iSrc = nil
		) const = 0;

	/**	Set the preflight options for a given book via command.

		@param iBookDB IN The database corresponding to the book.
		@param iPreflightOptions is the new option to set.
		@return kSuccess or an error code from the command.
	*/
	virtual ErrorCode SetPreflightBookOptions
		(
			IDataBase* iBookDB,
			const IPreflightBookOptions* iOptions
		) = 0;

	/**	Set the active preflight options for a book. There must be an active preflight on
		the book for this to be successful. Note that changing the active options will 
		potentially invalidate results for the book preflight since those results were
		based on the previous set of options.

		@param iBookDB IN The database corresponding to the book.
		@param iPreflightOptions is the new option to set.
		@return kSuccess or kFailure.
	*/
	virtual ErrorCode SetActivePreflightBookOptions
		(
			IDataBase* iBookDB,
			const IPreflightBookOptions* iOptions
		) = 0;

	/** Given a document or application database, obtain its active options. Returned 
		interface is const to reflect the fact that one should not change it except via a 
		command (ie UpdateActivePreflightOptions).

		@param iDocumentDB IN The database corresponding to the document. If nil, this obtains
			the options defined at the application level.
		@return A refcounted preflight options interface.
	*/
	virtual const IPreflightOptions* QueryOptions
		(
			IDataBase* iDocumentDB
		) const = 0;

	/** This is a utility method designed to compliment UpdateActivePreflightOptions and
		SetPreflightOptions. If you want to change the options for a document, you can first 
		make a copy of them using this method, modify the copy, and set it in via 
		UpdateActivePreflightOptions or SetPreflightOptions. Or, if you want to specify
		all of the settings you can pass nil for the iSrc and you'll get a fully default set 
		of options.

		@param iSrc IN The source interface to copy from, or nil to create a fully default set.
		@return A refcounted in-memory (nonpersistent) options interface. When this is fully
			dereferenced, it simply disappears.
	*/
	virtual IPreflightOptions* CloneOptions
		(
			const IPreflightOptions* iSrc = nil
		) const = 0;

	/**	Update the active preflight options for a given database.
		The active preflight options are not persistent and the command is not undoable.
		@see CloneOptions
		@see QueryOptions

		@param iDataBase is the database for the options.
		@param iOptions is the new option to set.
		@return kSuccess or an error code.
	*/
	virtual ErrorCode UpdateActivePreflightOptions
		(
			IDataBase* iDataBase,
			const IPreflightOptions* iOptions
		) = 0;

	/**	Set preflight options either in the application default or in the document.
		@see CloneOptions
		@see QueryOptions

		@param iDataBase specifies either the application default or the document database.
		@param iPreflightOptions is the new option to set.
		@return kSuccess or an error code from the command.
	*/
	virtual ErrorCode SetPreflightOptions
		(
			IDataBase* iDataBase,
			const IPreflightOptions* iOptions
		) = 0;
};



