//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAdobeCoreMetaData.h $
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
#ifndef __IAdobeCoreMetaData_h__
#define __IAdobeCoreMetaData_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "K2Vector.h"
#include "MetaDataTypes.h"

// ----- ID.h files -----

#include "MetaDataID.h"


//========================================================================================
// CLASS IAdobeCoreMetaData
//========================================================================================

/**
	This interface encapsulates routines of the XMPToolkit for accessing XMP Core Properties 
	defined in 'xap' namespace.
	@see IAdobeBasicJobMetaData
	@see IAdobeMediaMgmtMetaData
	@see IAdobeRightsMgmtMetaData
	@see IMetaDataAccess
	@see MetaDataTypes.h
*/

class IAdobeCoreMetaData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IADOBECOREMETADATA };

	//------ xap:Authors 
	/** Sets the 'xap:Authors' property with a list of author names in order of precedence.
		@param	authors	IN	List of author names which is to be set.
	*/
	virtual void				SetAuthors(const K2Vector<PMString>&  authors) = 0;
	
	/** Returns a list of author names in order of precedence defined by 'xap:Authors' property.
		@return List of author names.
	*/
	virtual K2Vector<PMString> 	GetAuthors() const = 0;
	
	//------ xap:BaseURL 
	/** Sets the base URL for relative URLs in the document content defined by 'xap:BaseURL' property.
		@param	baseURL	IN	Base URL to be set.
	*/
	virtual void				SetBaseURL(const metadata::URI& baseURL) = 0;

	/** Returns the base URL for relative URLs in the document content defined by 'xap:BaseURL' property.
		@return	the base URL.
	*/
	virtual metadata::URI 			GetBaseURL() const = 0;

	//------ xap:CreateDate 
	/** Sets the date and time the document was originally created defined by 'xap:CreateDate' property.
		@param date IN	creation date to set.
	*/
	virtual void				SetCreateDate(const XMP_DateTime& date) = 0;

	/** Returns the date and time the document was originally created defined by 'xap:CreateDate' property.
		@param	dt	OUT	Date and time the document was originally created.
		@return	kTrue if 'xap:CreateDate' property exist. kFalse otherwise.
	*/
	virtual bool32		 		GetCreateDate(XMP_DateTime& dt) const = 0;
	
	//------ xap:CreatorTool 
	/** Sets the name of the original tool used to create the resource (at least the first known tool) 
		defined by 'xap:CreatorTool' property. 
		@param	tool	IN The name of the original tool used to create the resource.
	*/
	virtual void				SetCreatorTool(const metadata::AgentName& tool) = 0;

	/** Returns the name of the original tool used to create the resource (at least the first known tool) 
		defined by 'xap:CreatorTool' property.
		@return The name of the original tool used to create the resource.
	*/
	virtual metadata::AgentName 		GetCreatorTool() const = 0;

	//------ xap:Description 
	/** Sets a textual description of the content of the resource defined by 'xap:Description' property.
		@param description	IN	A textual description of the content of the resource.
	*/
	virtual void				SetDescription(const PMString& description) = 0;

	/** Returns a textual description of the content of the resource defined by 'xap:Description' property.
		@return A textual description of the content of the resource.
	*/
	virtual PMString			GetDescription() const = 0;
	
	//------ xap:Format 
	/** Sets the resource format (e.g. video, audio, etc.) defined by 'xap:Format' property.
		@param	format	IN	The resource format to set.
	*/
	virtual void				SetFormat(const metadata::MIMEType& format) = 0;

	/** Returns the resource format (e.g. video, audio, etc.) defined by 'xap:Format' property.
		@return The resource format.
	*/
	virtual metadata::MIMEType		GetFormat() const = 0;

	//------ xap:Keywords 
	/** Returns an unordered list of descriptive phrases or keywords that specify the topic of the content of
		the resource defined by 'xap:Keywords' property.
		@return An unordered list of descriptive phrases or keywords.
	*/
	virtual K2Vector<PMString>	GetKeywords() const = 0;

	/** Sets an unordered list of descriptive phrases or keywords that specify the topic of the content of
		the resource defined by 'xap:Keywords' property.
		@param	keywords	IN	An unordered list of descriptive phrases or keywords.
	*/
	virtual void				SetKeywords(const K2Vector<PMString>& keywords) = 0;
	
	/* xap:Locale */
	
	//------ xap:MetadataDate 
	/** Sets the Date and time that any metadata for this resource was last changed 
		defined by 'xap:MetadataDate' property.
		@param date	IN	The Date and time that any metadata for this resource was last changed.
	*/
	virtual void		 		SetMetadataDate(const XMP_DateTime& date) = 0;

	/** Returns the Date and time that any metadata for this resource was last changed 
		defined by 'xap:MetadataDate' property.
		@param	dt	OUT	The Date and time that any metadata for this resource was last changed.
		@return	kTrue if the 'xap:MetadataDate' property exist. kFalse otherwise.
	*/
	virtual bool32			 	GetMetadataDate(XMP_DateTime& dt) const = 0;

	//------ xap:ModifyDate 
	/** Sets the date and time the resource was last modified defined by 'xap:ModifyDate' property.
		@param	date	IN	The date and time the resource was last modified.
	*/
	virtual void				SetModifyDate(const XMP_DateTime& date) = 0;

	/** Returns the date and time the resource was last modified defined by 'xap:ModifyDate' property.
		@param	dt	OUT	The date and time the resource was last modified.
		@return	kTrue if 'xap:ModifyDate' property exist. kFalse otherwise.
	*/
	virtual bool32 				GetModifyDate(XMP_DateTime& dt) const = 0;

	//------ xap:Nickname 
	/** Sets the short informal name for the resource, specified by 'xap:Nickname' property.
		@param	description	IN	The short informal name.
	*/
	virtual void				SetNickname(const PMString& description) = 0;

	/** Returns the short informal name for the resource, specified by 'xap:Nickname' property.
		@return	The short informal name.
	*/
	virtual PMString			GetNickname() const = 0;

	//------ xap:Title 
	/** Sets the title of the document, or the name given to the resource specified by 'xap:Title' property.
		@param	title	IN	The title of the document.
	*/
	virtual void				SetTitle(const PMString& title) = 0;

	/** Returns the title of the document, or the name given to the resource specified by 'xap:Title' property.
		@return	The title of the document.
	*/
	virtual PMString			GetTitle() const = 0;
};

#endif // __IAdobeCoreMetaData_h__
