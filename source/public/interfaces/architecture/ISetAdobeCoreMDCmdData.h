//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISetAdobeCoreMDCmdData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __ISetAdobeCoreMDCmdData_h__
#define __ISetAdobeCoreMDCmdData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "MetaDataTypes.h"
#include "UnspecifiableOf.h"

// ----- ID.h files -----

#include "MetaDataID.h"

//========================================================================================
// INTERFACE ISetAdobeCoreMDCmdData
//========================================================================================

/**
    A data interface used by SetAdobeCoreMetaDataCmd.
*/

class ISetAdobeCoreMDCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISETADOBECOREMDCMDDATA };


	/** Set the command data.
		@param targetObject		IN	The target object of the command. It must have a IID_IADOBECOREMETADATA interface.
		@param title			IN	The title of the document.
		@param authors			IN	List of author names.
		@param description		IN	A textual description of the content of the resource.
		@param keywords			IN	An unordered list of descriptive phrases or keywords.
		@param metadataDate		IN	kTrue if the 'xap:MetadataDate' property exist. kFalse otherwise.
		@param modifyDate		IN	if 'xap:ModifyDate' property exist. kFalse otherwise.
		@param createDate		IN	if 'xap:CreateDate' property exist. kFalse otherwise.
		@param creatorTool		IN	The name of the original tool used to create the resource.
		@param baseURL			IN	The base URL.
		@param nickname			IN	The short informal name.
		@see IID_IADOBECOREMETADATA
	 */
	virtual void 				Set(IPMUnknown* targetObject,
									const UnspecifiableOf<PMString>& title = kUnspecified,
									const UnspecifiableOf< K2Vector<PMString> >& authors = kUnspecified,
									const UnspecifiableOf<PMString>& description = kUnspecified,
									const UnspecifiableOf< K2Vector<PMString> >& keywords = kUnspecified,
									const UnspecifiableOf<XMP_DateTime>& metadataDate = kUnspecified,
									const UnspecifiableOf<XMP_DateTime>& modifyDate = kUnspecified,
									const UnspecifiableOf<XMP_DateTime>& createDate = kUnspecified,
									const UnspecifiableOf<metadata::AgentName>& creatorTool = kUnspecified,
									const UnspecifiableOf<metadata::URI>& baseURL = kUnspecified,
									const UnspecifiableOf<PMString>& nickname = kUnspecified) = 0;

    /** Query an interface on the target object.
        @param		iid    IN    The ID of the interface to query.
		@return		IPMUnknown	pointer to the interface iid or nil, if interface iid doesn't exist.
    */
	virtual IPMUnknown*								QueryTargetObject(const PMIID& iid) const = 0;

	/** Returns the title of the document, or the name given to the resource specified by 'xap:Title' property.
		@return	The title of the document.
	*/
	virtual UnspecifiableOf<PMString>				GetTitle() const = 0;

	/** Returns a list of author names in order of precedence defined by 'xap:Authors' property.
		@return List of author names.
	*/
	virtual UnspecifiableOf< K2Vector<PMString> >	GetAuthors() const = 0;

	/** Returns a textual description of the content of the resource defined by 'xap:Description' property.
		@return A textual description of the content of the resource.
	*/
	virtual UnspecifiableOf<PMString>				GetDescription() const = 0;

	/** Returns an unordered list of descriptive phrases or keywords that specify the topic of the content of
		the resource defined by 'xap:Keywords' property.
		@return An unordered list of descriptive phrases or keywords.
	*/
	virtual UnspecifiableOf< K2Vector<PMString> >	GetKeywords() const = 0;

	/** Returns the Date and time that any metadata for this resource was last changed 
		defined by 'xap:MetadataDate' property.
		@return	kTrue if the 'xap:MetadataDate' property exist. kFalse otherwise.
	*/
	virtual UnspecifiableOf<XMP_DateTime> 	GetMetadataDate() const = 0;

	/** Returns the date and time the resource was last modified defined by 'xap:ModifyDate' property.
		@return	kTrue if 'xap:ModifyDate' property exist. kFalse otherwise.
	*/
	virtual UnspecifiableOf<XMP_DateTime> 	GetModifyDate() const = 0;

	/** Returns the date and time the document was originally created defined by 'xap:CreateDate' property.
		@return	kTrue if 'xap:CreateDate' property exist. kFalse otherwise.
	*/
	virtual UnspecifiableOf<XMP_DateTime> 	GetCreateDate() const = 0;

	/** Returns the name of the original tool used to create the resource (at least the first known tool) 
		defined by 'xap:CreatorTool' property.
		@return The name of the original tool used to create the resource.
	*/
	virtual UnspecifiableOf<metadata::AgentName> 	GetCreatorTool() const = 0;

	/** Returns the base URL for relative URLs in the document content defined by 'xap:BaseURL' property.
		@return	the base URL.
	*/
	virtual UnspecifiableOf<metadata::URI> 			GetBaseURL() const = 0;

	/** Returns the short informal name for the resource, specified by 'xap:Nickname' property.
		@return	The short informal name.
	*/
	virtual UnspecifiableOf<PMString>				GetNickname() const = 0;
};

#endif // __ISetAdobeCoreMDCmdData_h__
