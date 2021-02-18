//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateXMLTags.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IApplication.h"
#include "IDocument.h"
#include "ISelectionManager.h"
#include "IStyleInfo.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "IWorkspace.h"
#include "IXMLCreateStyleToTagCmdData.h"
#include "IXMLMappingCommands.h"
#include "IXMLStyleToTagMap.h"
#include "IXMLTagCommands.h"
#include "IXMLTagList.h"
#include "IXMLTagToStyleMap.h"
// General
#include <map>
#include "Utils.h"
#include "XMLReference.h"
#include "PMRect.h"
#include "ErrorUtils.h"
#include "Utils.h"
#include "SDKFileHelper.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "ISnipRunSuite.h"
#include "SnpXMLSampleHelper.h"

/**  \li How to acquire one or all tags (kXMLTagBoss)in a document (kDocBoss)
	\li How to create, and apply, a style to tag mapping (IXMLStyleToTagMap)
	\li How to create, and apply, a style to tag mapping (IXMLStyleToTagMap)
	\li How to create a tag
	\li How to load tags from an existing tags file
	\li How to save the set of tags
	\li How to unmap styles from tags
	\li How to unmap tags from styles

	@ingroup sdk_snippet
	@ingroup sdk_xmedia
	@see _SnpRunnerManipulateXMLTags::Run

	<h2>Exercising</h2>
	
	<h3>AcquireTag</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option AcquireTag.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see information about all tags being listed, and an attempt to acquire one by name

	<h3>CreateAndApplyStyleToTagMap</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option CreateAndApplyStyleToTagMap.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see  some new para styles and char styles were created (Paragraph Styles and Character Styles panels)
		-# You should see  some new tags were created, via the Tags panel
		-# You should see a page item created, with styled text. The styled text should be tagged systematically.
		-# Try scrolling down through the text and seeing how the style changes, and note associated tag. Story editor view is useful for this.

	<h3>CreateAndApplyTagToStyleMap</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option CreateAndApplyTagToStyleMap.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see new info when you open the Map Tags to Styles dialog. This is available from structure-view popout

	<h3>CreateTags</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option CreateTags.
		-# If all is well, there should be no asserts (if in debug build).
		-# Open or inspect Tags panel.
		-# You should see some new tags have been created.

	<h3>LoadTags</h3>
		-# Be sure you have run SaveTags first.
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option LoadTags.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see some tags have been loaded in.

	<h3>SaveTags</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option SaveTags.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a message about a file being created. 
		-# Save snippet runner log, grab the path to the file and inspect in XML or text editor if you wish
	
	<h3>UnmapStylesFromTags</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option UnmapStylesFromTags.
		-# If all is well, there should be no asserts (if in debug build).
		-# Inspect the  Map Styles To Tags dialog. This is available from structure-view popout. All mappings should be gone.

	<h3>UnmapTagsFromStyles</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLTags
		-# Choose the option UnmapTagsFromStyles.
		-# If all is well, there should be no asserts (if in debug build).
		-# Inspect the  Map Tags to Styles dialog. This is available from structure-view popout. All mappings should be gone.
	
		
*/
class SnpManipulateXMLTags {
public:

	/**	Constructor
 
	 */
	SnpManipulateXMLTags() {}

	/**	Destructor
 
	 */
	virtual ~SnpManipulateXMLTags() {}

	/**	Obtain a reference to a tag (kXMLTagBoss), creating one if named tag doesn't exist already in specified document.
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document (kDocBoss) in which tag is to be found (or created)
		@param tagName specifies name of tag to acquire
		@return UIDRef of tag (kXMLTagBoss) created, from which IXMLTag can be instantiated
	 */
	UIDRef AcquireTag(const UIDRef& documentUIDRef,const PMString& tagName);

	/**	List all the tags in a document, with information about them
		@param docUIDRef specifies document of interest
	 */
	void InspectAllDocumentTags(const UIDRef& docUIDRef);

	/**	Update style to tag map (IXMLStyleToTagMap) in document workspace (kDocWorkspaceBoss) of
		specified document (kDocBoss) with supplied mappings.

		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param paraStyleTagMapping specifies how paragraph styles should map to tagnames
		@param charStyleTagMapping specifies how character styles should map to tagnames
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode CreateStyleToTagMap(const UIDRef& documentUIDRef,
					const std::map<PMString,PMString>& paraStyleTagMapping,
					const std::map<PMString,PMString>& charStyleTagMapping
					);

	/**	Update tag to style map (IXMLStyleToTagMap) in document workspace (kDocWorkspaceBoss) of
		specified document (kDocBoss) with supplied mappings.

		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param tagToParaStyleMapping specifies how tagnames should map to paragraph styles
		@param tagToCharStyleMapping specifies how tagnames should map to character styles
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode CreateTagToStyleMap(const UIDRef& documentUIDRef, 
					const std::map<PMString,PMString>& tagToParaStyleMapping,
					const std::map<PMString,PMString>& tagToCharStyleMapping
					);


	/**	Create set of tags with given tagnames (most of work done in AcquireTag).
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document in which tags to be created
		@param tagNames list of name sof tags
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode CreateTags(const UIDRef& documentUIDRef, const K2Vector<PMString>& tagNames);

		

	/**	Load tags from file into document
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param file 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode LoadTags(const UIDRef& documentUIDRef, const IDFile& file);


	/**	Save tags from document to file
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param file 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode SaveTags(const UIDRef& documentUIDRef, const IDFile& file);


	/**	Apply a style-to-tag map (IXMLTagToStyleMap)
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param tagNameForUntaggedStories 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ApplyStyleToTagMap(const UIDRef& documentUIDRef, const PMString& tagNameForUntaggedStories);

	/**	Apply a style-to-tag map (IXMLStyleToTagMap)
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode ApplyTagToStyleMap(const UIDRef& documentUIDRef);


	/**	Obtain reference to a paragraph style by name; create if it doesn't already exist.
		Delegates to SnpXMLSampleHelper method.
		
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param name specifies name of style we're looking for
	
		@return UIDRef from which IStyleInfo can be instantiated
		*/
	UIDRef AcquireParaStyle(const UIDRef& documentUIDRef, const PMString& name);

	/**	Obtain reference to a character style by name; create if it doesn't already exist
		Delegates to SnpXMLSampleHelper method.

		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param name specifies name of style we're looking for
		@return UIDRef from which IStyleInfo can be instantiated
		*/
	UIDRef AcquireCharStyle(const UIDRef& documentUIDRef, const PMString& name);


	/** Remove tag to style mappings in given document.
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode UnmapTagsFromStyles(const UIDRef& documentUIDRef);

	/**  Remove style to tag mappings in the specified document.
	
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@return ErrorCode kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode UnmapStylesFromTags(const UIDRef& documentUIDRef);

	/** Typedef we use within this class to reduce duplicated code relating to char/para style queries. */
	typedef UIDRef (SnpManipulateXMLTags::*PMemberFn)(
											const UIDRef& documentUIDRef,
											const PMString& name);

private:

	/**	Iterate through the tag-to-style specification and add entries to the 
		document's tag-to-style map (IXMLTagToStyleMap)
		@precondition  documentUIDRef should allow IDocument to be instantiated
		@precondition mapUIDRef should allow IXMLTagToStyleMap to be instantiated
		@param documentUIDRef document of interest
		@param mapUIDRef reference to object with IXMLTagToStyleMap we're going to adorn
		@param tagStyleMapping our specification for desired mapping
		@param acquireStylePtr ptr to member function to acquire para or char style
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode iterTagStyleMap(const UIDRef& documentUIDRef, 
											const UIDRef& mapUIDRef, 
											const std::map<PMString,PMString>& tagStyleMapping,
											PMemberFn acquireStylePtr);



	/**	terate through the style-to-tag specification and add entries to the 
		document's style-to-tag map (IXMLStyleToTagMap)
		@precondition  documentUIDRef should allow IDocument to be instantiated
		@precondition mapUIDRef should allow IXMLStyleToTagMap to be instantiated
		@param documentUIDRef document of interest
		@param mapUIDRef reference to object with IXMLStyleToTagMap we're going to add to
		@param styleTagMapping our specification for the mapping desired
		@param acquireStylePtr ptr to member function to acquire para or char style
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode iterStyleTagMap(const UIDRef& documentUIDRef,
						const UIDRef& mapUIDRef, 
						const std::map<PMString,PMString>& styleTagMapping,
						PMemberFn acquireStylePtr);


};


/*
*/
void SnpManipulateXMLTags::InspectAllDocumentTags(const UIDRef& docUIDRef)
{
	do {
		InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		IDataBase* db = ::GetDataBase(document);
		UIDRef docWorkspaceUIDRef = document->GetDocWorkSpace ();
	
		InterfacePtr<IXMLTagList> xmlTagList(docWorkspaceUIDRef, UseDefaultIID());
		ASSERT(xmlTagList);
		if(!xmlTagList) {
			break;
		}
		SnpXMLHelper xmlHelper;
		for(int32 i=0; i < xmlTagList->GetNumberOfTags(); i++) {
			UIDRef tagUIDRef(db, xmlTagList->GetNthTag(i));
			SNIPLOG("=== Tag (%d) === %s \n=========\n", i,
				xmlHelper.AsString(tagUIDRef).GetPlatformString().c_str());
			
		}
	} while(kFalse);

}

/*
*/
UIDRef SnpManipulateXMLTags::AcquireTag(const UIDRef& documentUIDRef,
									  const PMString& tagName
									  )
{
	UIDRef retTagUIDRef;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		InterfacePtr<IXMLTagList> tagList(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(tagList);
		if(!tagList) {
			break;
		}

		WideString tagNameWide(tagName);
		UID existingTagUID  = tagList->GetTag(tagNameWide);
		if(existingTagUID == kInvalidUID) {
			UID createdTagUID = kInvalidUID;
			ErrorCode err = Utils<IXMLTagCommands>()->CreateTag (::GetUIDRef(tagList), 
															tagNameWide,
															kInvalidUID, 
															&createdTagUID);

			ASSERT(err == kSuccess);
			ASSERT(createdTagUID != kInvalidUID);
			retTagUIDRef = UIDRef(documentUIDRef.GetDataBase(), createdTagUID);

		} else {
			retTagUIDRef = UIDRef(documentUIDRef.GetDataBase(), existingTagUID);
		}

	} while(kFalse);

	return retTagUIDRef;
}



/*
*/
UIDRef SnpManipulateXMLTags::AcquireParaStyle(const UIDRef& documentUIDRef, const PMString& name)
{
	SnpXMLSampleHelper helper;
	return helper.AcquireStyle(documentUIDRef, name, IID_IPARASTYLEGROUPMANAGER, kCreateParaStyleCmdBoss);
}

/*
*/
UIDRef SnpManipulateXMLTags::AcquireCharStyle(const UIDRef& documentUIDRef, const PMString& name)
{
	SnpXMLSampleHelper helper;
	return helper.AcquireStyle(documentUIDRef, name, IID_ICHARSTYLEGROUPMANAGER, kCreateCharStyleCmdBoss);
}

/*
*/
ErrorCode SnpManipulateXMLTags::iterStyleTagMap(const UIDRef& documentUIDRef,
												const UIDRef& mapUIDRef, 
												const std::map<PMString,PMString>& styleTagMapping,
												PMemberFn acquireStylePtr)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		SnpXMLHelper xmlHelper;
		
		std::map<PMString,PMString>::const_iterator iter;
		for(iter = styleTagMapping.begin(); iter != styleTagMapping.end(); ++iter) {
			PMString styleName = iter->first;
			PMString tagName = iter->second;
			UIDRef styleUIDRef = (this->*acquireStylePtr)(documentUIDRef, styleName);
			UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagName);
			bool16 validCondition = styleUIDRef.GetUID() != kInvalidUID && tagUIDRef.GetUID() != kInvalidUID;
			ASSERT(validCondition);
			if(!validCondition) {
				break;
			}
			err = Utils<IXMLMappingCommands>()->MapStyleToTag(mapUIDRef, styleUIDRef.GetUID(), tagUIDRef.GetUID());
			if(err != kSuccess) {
				break;
			}
			SNIPLOG("Mapped style %s to tag %s", styleName.GetPlatformString().c_str(), tagName.GetPlatformString().c_str());
		}
	} while(kFalse);

	return err;
}


/*
*/
ErrorCode SnpManipulateXMLTags::CreateTags(const UIDRef& documentUIDRef, const K2Vector<PMString>& tagNames)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		SnpXMLHelper xmlHelper;
		K2Vector<PMString>::const_iterator iter;
		for(iter = tagNames.begin(); iter != tagNames.end(); ++iter) {
			PMString currTagName = *iter;
			ASSERT(currTagName.CharCount()>0);
			UIDRef acquiredTagUIDRef = xmlHelper.AcquireTag(documentUIDRef,currTagName);
			bool16 validTag = acquiredTagUIDRef.GetUID() != kInvalidUID; 
			ASSERT(validTag);
			if(!validTag) {
				break;
			}
		}
		err = kSuccess;
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLTags::CreateStyleToTagMap(const UIDRef& documentUIDRef, 
											const std::map<PMString,PMString>& paraStyleTagMapping,
											const std::map<PMString,PMString>& charStyleTagMapping
						)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		InterfacePtr<IXMLStyleToTagMap> styleToTagMap(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(styleToTagMap);
		if(!styleToTagMap) {
			break;
		}
		UIDRef styleToTagMapUIDRef = ::GetUIDRef(styleToTagMap);

		err = this->iterStyleTagMap(documentUIDRef, styleToTagMapUIDRef, 
						paraStyleTagMapping, 
						&SnpManipulateXMLTags::AcquireParaStyle);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
		this->iterStyleTagMap(documentUIDRef, styleToTagMapUIDRef, 
						charStyleTagMapping, 
						&SnpManipulateXMLTags::AcquireCharStyle);
		ASSERT(err == kSuccess);
	
		
	} while(kFalse);

	return err;
}

/*
*/
ErrorCode SnpManipulateXMLTags::CreateTagToStyleMap(const UIDRef& documentUIDRef, 
													const std::map<PMString,PMString>& tagToParaStyleMapping,
													const std::map<PMString,PMString>& tagToCharStyleMapping)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		
		InterfacePtr<IXMLTagToStyleMap> tagToStyleMap(document->GetDocWorkSpace(), 
			UseDefaultIID());
		ASSERT(tagToStyleMap);
		if(!tagToStyleMap) {
			break;
		}
		UIDRef tagToStyleMapUIDRef = ::GetUIDRef(tagToStyleMap);
		err = this->iterTagStyleMap(documentUIDRef, tagToStyleMapUIDRef, 
						tagToParaStyleMapping, 
						&SnpManipulateXMLTags::AcquireParaStyle);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
		err = this->iterTagStyleMap(documentUIDRef, tagToStyleMapUIDRef, 
						tagToCharStyleMapping, 
						&SnpManipulateXMLTags::AcquireCharStyle);
		ASSERT(err == kSuccess);
	
	} while(kFalse);

	
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLTags::iterTagStyleMap(const UIDRef& documentUIDRef, 
												const UIDRef& mapUIDRef, 
												const std::map<PMString,PMString>& tagStyleMapping,
												PMemberFn acquireStylePtr)
{
	ErrorCode err = kFailure;

	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		SnpXMLHelper xmlHelper;

		
		std::map<PMString,PMString>::const_iterator iter;
		for(iter = tagStyleMapping.begin(); iter != tagStyleMapping.end(); ++iter) {
			PMString tagName = iter->first;
			PMString styleName = iter->second;
			UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagName);
			UIDRef styleUIDRef = (this->*acquireStylePtr)(documentUIDRef, styleName);
			bool16 validCondition = styleUIDRef.GetUID() != kInvalidUID && tagUIDRef.GetUID() != kInvalidUID;
			ASSERT(validCondition);
			if(!validCondition) {
				break;
			}
			err = Utils<IXMLMappingCommands>()->MapTagToStyle(mapUIDRef, tagUIDRef.GetUID(), styleUIDRef.GetUID());
			if(err != kSuccess) {
				break;
			}
			SNIPLOG("Mapped tag %s to style %s", tagName.GetPlatformString().c_str(), styleName.GetPlatformString().c_str());
		}
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLTags::LoadTags(const UIDRef& documentUIDRef, const IDFile& file)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		InterfacePtr<IXMLTagList> xmlTagList(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(xmlTagList);
		if(!xmlTagList) {
			break;
		}
		
		err = Utils<IXMLTagCommands>()->LoadTagList(::GetUIDRef(xmlTagList), file);
		ASSERT(err == kSuccess);
	} while(kFalse);

	return err;
}

/*
*/
ErrorCode SnpManipulateXMLTags::SaveTags(const UIDRef& documentUIDRef, const IDFile& file)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		InterfacePtr<IXMLTagList> xmlTagList(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(xmlTagList);
		if(!xmlTagList) {
			break;
		}
		
		err = Utils<IXMLTagCommands>()->SaveTagList(::GetUIDRef(xmlTagList), file);
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLTags::ApplyStyleToTagMap(const UIDRef& documentUIDRef, const PMString& tagNameForUntaggedStories)
{
	ErrorCode err = kFailure;

	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		
		IDataBase *dataBase = documentUIDRef.GetDataBase();
	    // Warning: naming isn't what you'd expect:
		// kXMLCreateStyleToTagElementsCmdBoss rather than Apply...
		InterfacePtr<ICommand> applyCmd(CmdUtils::CreateCommand(kXMLCreateStyleToTagElementsCmdBoss));    
		ASSERT(applyCmd);
		if(!applyCmd) {
			break;
		}

		InterfacePtr<IXMLCreateStyleToTagElementsCmdData > cmdData(applyCmd, UseDefaultIID());
		ASSERT(cmdData);
		if(!cmdData) {
			break;
		}
		SnpXMLHelper xmlHelper;
		UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagNameForUntaggedStories);
		cmdData->Set(tagUIDRef.GetUID());
		applyCmd->SetItemList(UIDList (dataBase));
		err = CmdUtils::ProcessCommand(applyCmd); 
		ASSERT(err == kSuccess);
	} while(kFalse);

	return err;
}


/*
*/
ErrorCode SnpManipulateXMLTags::ApplyTagToStyleMap(const UIDRef& documentUIDRef)
{
	ErrorCode err = kFailure;

	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		IDataBase *dataBase = documentUIDRef.GetDataBase();
	    
		InterfacePtr<ICommand> applyCmd(CmdUtils::CreateCommand(kXMLApplyTagToStyleMappingCmdBoss));    
		ASSERT(applyCmd);
		if(!applyCmd) {
			break;
		}
		applyCmd->SetItemList(UIDList (dataBase));
		err = CmdUtils::ProcessCommand(applyCmd); 
		ASSERT(err == kSuccess);
	} while(kFalse);

	return err;
}


ErrorCode SnpManipulateXMLTags::UnmapTagsFromStyles(const UIDRef& documentUIDRef)
{
	ErrorCode result = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		Utils<IXMLMappingCommands> mappingCommandsFacade;
		ASSERT(mappingCommandsFacade);
		if(!mappingCommandsFacade) {
			break;
		}
		// Iterate the tags in the document, and for each tag we discover,
		// remove its entry in tag to style map
		InterfacePtr<IXMLTagList> xmlTagList(document->GetDocWorkSpace(),
														UseDefaultIID());
		ASSERT(xmlTagList);
		if(!xmlTagList) {
			break;
		}
		
		InterfacePtr<IXMLTagToStyleMap> tagToStyleMap(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(tagToStyleMap);
		if(!tagToStyleMap) {
			break;
		}
		UIDRef tagToStyleMapUIDRef = ::GetUIDRef(tagToStyleMap);
		for(int32 i=0; i < xmlTagList->GetNumberOfTags(); i++) {
			UID nextUID = xmlTagList->GetNthTag(i);
			ASSERT(nextUID != kInvalidUID);
			result = mappingCommandsFacade->UnMapTagToStyle (tagToStyleMapUIDRef, nextUID);
			ASSERT(result == kSuccess);
			if(result != kSuccess) {
				break;
			}
		}
		result = kSuccess;
	} while(kFalse);
	return result;
}


ErrorCode SnpManipulateXMLTags::UnmapStylesFromTags(const UIDRef& documentUIDRef)
{
	ErrorCode result = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		
		Utils<IXMLMappingCommands> mappingCommandsFacade;
		ASSERT(mappingCommandsFacade);
		if(!mappingCommandsFacade) {
			break;
		}
		// Iterate the para and char style mappings in the document, and for each style we discover,
		// remove its entry
		InterfacePtr<IStyleGroupManager> paraStyleNameTable(document->GetDocWorkSpace(),
														IID_IPARASTYLEGROUPMANAGER);
		ASSERT(paraStyleNameTable);
		if(!paraStyleNameTable) {
			break;
		}
		InterfacePtr<IStyleGroupManager> charStyleNameTable(document->GetDocWorkSpace(),
														IID_ICHARSTYLEGROUPMANAGER);
		ASSERT(charStyleNameTable);
		if(!charStyleNameTable) {
			break;
		}
		
		InterfacePtr<IXMLStyleToTagMap> styleToTagMap(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(styleToTagMap);
		if(!styleToTagMap) {
			break;
		}
		UIDRef styleToTagMapUIDRef = ::GetUIDRef(styleToTagMap);

		UIDList paraStyles(::GetDataBase(paraStyleNameTable));
		paraStyleNameTable->GetRootHierarchy()->GetDescendents(&paraStyles,IID_ISTYLEINFO);

		for(int32 i=0; i < paraStyles.Length(); i++) {
			UID nextUID = paraStyles[i];
			ASSERT(nextUID != kInvalidUID);
			result = mappingCommandsFacade->UnMapStyleToTag (styleToTagMapUIDRef, nextUID);
			ASSERT(result == kSuccess);
			if(result != kSuccess) {
				break;
			}
		}
		
		// TODO factor a little better

		UIDList charStyles(::GetDataBase(charStyleNameTable));
		charStyleNameTable->GetRootHierarchy()->GetDescendents(&charStyles,IID_ISTYLEINFO);

		for(int32 j=0; j < charStyles.Length(); j++) {
			UID nextUID = charStyles[j];
			ASSERT(nextUID != kInvalidUID);
			result = mappingCommandsFacade->UnMapStyleToTag (styleToTagMapUIDRef, nextUID);
			ASSERT(result == kSuccess);
			if(result != kSuccess) {
				break;
			}
		}
		
		result = kSuccess;
	} while(kFalse);
	return result;
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateXMLTags available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateXMLTags : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateXMLTags();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateXMLTags();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateXMLTags::_SnpRunnerManipulateXMLTags() : SnpRunnable("ManipulateXMLTags")
{
	this->SetDescription("Manipulate XML tags and style/tag mappings");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");
}

/* Destructor.
*/
_SnpRunnerManipulateXMLTags::~_SnpRunnerManipulateXMLTags()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateXMLTags::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		ASSERT(runnableContext->GetActiveContext()); 
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		return document != nil;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateXMLTags::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode err = kCancel;
	SNIPLOG("---- Start SnpManipulateXMLTags::Run ---\n");
	IActiveContext* activeContext = runnableContext->GetActiveContext();
	UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
	SnpManipulateXMLTags instance;
	SnpXMLSampleHelper xmlHelper;
	XMLReference rootXMLRef = xmlHelper.GetRootXMLReference(documentUIDRef);
	do {

		PMString acquireTag("AcquireTag");
		PMString createAndApplyStyleToTagMap("CreateAndApplyStyleToTagMap");
		PMString createAndApplyTagToStyleMap("CreateAndApplyTagToStyleMap");
		PMString createTags("CreateTags");
		PMString loadTags("LoadTags (from a SaveTags)");
		PMString saveTags("SaveTags");
		PMString unmapStylesFromTags("UnmapStylesFromTags");
		PMString unmapTagsFromStyles("UnmapTagsFromStyles");

		K2Vector<PMString> choices;
		choices.push_back(acquireTag); //0
		choices.push_back(createAndApplyStyleToTagMap); //1
		choices.push_back(createAndApplyTagToStyleMap); //2
		choices.push_back(createTags); //3
		choices.push_back(loadTags); //4
		choices.push_back(saveTags); //5
		choices.push_back(unmapStylesFromTags); //6
		choices.push_back(unmapTagsFromStyles); //7
		choices.push_back(PMString("UnitTest")); //8

		
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		switch(choice) {
			case 0:		
			{
				SNIPLOG("AcquireTag");
				instance.InspectAllDocumentTags(documentUIDRef);
				UIDRef rootTagUIDRef =instance.AcquireTag(documentUIDRef, PMString("Root"));
				if(rootTagUIDRef.GetUID() != kInvalidUID) {
					SNIPLOG("Acuired tag by name (UID=%d) %s\n", 
								rootTagUIDRef.GetUID().Get(),
								xmlHelper.AsString(rootTagUIDRef).GetPlatformString().c_str());
				} else {
					SNIPLOG("No Root tag in this context's tag-list");
				}
						
				SNIPLOG("\nThis scenario showed inspecting all tags and obtaining the root tag by name");
				err = kSuccess;
			}
			break;

			case 1:
			{
				SNIPLOG("CreateAndApplyStyleToTagMap");
				std::map<PMString, PMString> paraMap;
				std::map<PMString, PMString> charMap;
				int32 numberIters=4;
				
				for(int32 i=0; i < numberIters; i++) {
					PMString p("para-style-");
					PMString c("char-style-");
					p.AppendNumber(i+1);
					c.AppendNumber(i+1);
					PMString tp("tag-p-");
					tp.AppendNumber(i+1);
					PMString tc("tag-c-");
					tc.AppendNumber(i+1);
					paraMap.insert(std::pair<PMString,PMString>(p,tp));
					charMap.insert(std::pair<PMString,PMString>(c,tc));
					
				}
				err = instance.CreateStyleToTagMap(documentUIDRef,paraMap, charMap);
				ASSERT(err == kSuccess);
				SNIPLOG("\nSee Tags panel and para/char styles.");
			
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef storyRef = xmlHelper.CreateStoryThroughFrame(documentUIDRef,
																	rect,0,0);
				
				TextIndex nextIndex = 0;
				for(int32 i=0;i  < numberIters; i++) {
					PMString pstr("Line-");
					pstr.AppendNumber(i+1);
					PMString paraName("para-style-");
					paraName.AppendNumber(i+1);
					UIDRef styleUIDRef = 
						instance.AcquireParaStyle(documentUIDRef, paraName);
					TextIndex insertIndex = nextIndex;
					err = xmlHelper.InsertStyledLine(storyRef,pstr, insertIndex, styleUIDRef, nextIndex);
					ASSERT(err == kSuccess);
				}
				SNIPLOG("ApplyStyleToTagMap");

				err = instance.ApplyStyleToTagMap(documentUIDRef, PMString("article"));
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario involved creating and applying a mapping from styles to tags,");
			}
			break;
		
			case 2:
			{
				SNIPLOG("CreateAndApplyTagToStyleMap");
				std::map<PMString, PMString> tagToParaStyleMap;
				std::map<PMString, PMString> tagToCharStyleMap;
				int32 nIterations =12;
				for(int32 i=0; i < nIterations; i++) {
					PMString p("para-style-");
					PMString c("char-style-");
					p.AppendNumber(i+1);
					c.AppendNumber(i+1);
					PMString tp("tag-p-");
					PMString tc("tag-c-");
					tp.AppendNumber(i+1);
					tc.AppendNumber(i+1);
					tagToParaStyleMap.insert(std::pair<PMString,PMString>(tp,p));
					tagToCharStyleMap.insert(std::pair<PMString,PMString>(tc,c));
				}
				err = instance.CreateTagToStyleMap(documentUIDRef,tagToParaStyleMap, tagToCharStyleMap);
			
				ASSERT(err == kSuccess);
				SNIPLOG("ApplyTagToStyleMap");

				err = instance.ApplyTagToStyleMap(documentUIDRef);

			} 
			break;

			case 3:
			{
				SNIPLOG("CreateTags");
				K2Vector<PMString> tagNames;
				const int32 cTagsToCreate = 12;
				for(int32 i=0; i < cTagsToCreate; i++) {
					PMString pstr("created-tag-");
					pstr.AppendNumber(i+1);
					tagNames.push_back(pstr);
				}

				err = instance.CreateTags(documentUIDRef, tagNames);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario created some new tags, see the Tags panel");
			}
			break;

	

			case 4:
			{
				SNIPLOG("LoadTags");
				IDFile file = xmlHelper.GetSampleFile("-tags.xml");
				SDKFileHelper fileHelper(file);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: Tags file to import does not yet exist; create by SaveTags gesture!");
					break;
				}

				err = instance.LoadTags(documentUIDRef, file);
				ASSERT(err == kSuccess);
			
				SNIPLOG("\nThis loads tags that should have been created by prior save-tags (file %s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			} 
			break;

			case 5:
			{
				SNIPLOG("SaveTags");
				IDFile file = xmlHelper.GetSampleFile("-tags.xml");
				err = instance.SaveTags(documentUIDRef, file);
				ASSERT(err == kSuccess);
				SDKFileHelper fileHelper(file);
				SNIPLOG("\nThis snippet saved all context tags to %s", fileHelper.GetPath().GetPlatformString().c_str());
			} 
			break;
		
			case 6:
			{
				SNIPLOG("UnmapStylesFromTags");
				err = instance.UnmapStylesFromTags(documentUIDRef);

			}
			break;
			
			case 7:
			{
				SNIPLOG("UnmapTagsFromStyles");
				err = instance.UnmapTagsFromStyles(documentUIDRef);
			
			}
			break;
			
			case 8:
			{
				PMString snippetName("ManipulateXMLTags");
				InterfacePtr<ISnipRunSuite> suite(activeContext->GetContextSelection(), UseDefaultIID());
				ASSERT(suite);
				if (!suite)
					break;

				if (suite->CanRun(snippetName))
				{
					// Check names above
					suite->Run(snippetName, acquireTag);
					suite->Run(snippetName, createAndApplyStyleToTagMap);
					suite->Run(snippetName, createAndApplyTagToStyleMap);
					suite->Run(snippetName, createTags);
					suite->Run(snippetName, saveTags);
					suite->Run(snippetName, loadTags);
					suite->Run(snippetName, unmapStylesFromTags);
					suite->Run(snippetName, unmapTagsFromStyles);
				
					// If we got here without crashes or asserts, consider
					// that a success
					err = kSuccess;
				} else {
					SNIPLOG("Can't run snippet self");
				}
			}
			break;
		} // end of switch

	} while(kFalse);

	// ==============
	SNIPLOG("---- End SnpManipulateXMLTags::Run ---\n");
	return err;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateXMLTags instance_SnpRunnerManipulateXMLTags;
DEFINE_SNIPPET(_SnpRunnerManipulateXMLTags) 	
