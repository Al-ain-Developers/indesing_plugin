//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMetaDataAccess.h $
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
#ifndef __IMetaDataAccess_h__
#define __IMetaDataAccess_h__

// ----- Interfaces -----
#include "IPMUnknown.h"

// ----- Includes -----
#include "MetaDataTypes.h"

// ----- ID.h files -----
#include "MetaDataID.h"


class IPMStream;
class IMetaDataIterator;


//========================================================================================
// CLASS IMetaDataAccess
//========================================================================================


/** Container type */
typedef enum
{
  /** Ordered container of alternate items */
  metadata_alt,
  
  /** Unordered container */
  metadata_bag,

  /** Ordered container */
  metadata_seq,

  /** Unknown container type */
  metadata_sct_unknown
} MetaDataStructContainerType;

/**
	This interface is a low level API that encapsulates routines of the XMPToolkit.
	@see IAdobeBasicJobMetaData
	@see IAdobeCoreMetaData
	@see IAdobeMediaMgmtMetaData
	@see IAdobeRightsMgmtMetaData
*/

class IMetaDataAccess : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMETADATAACCESS };

	/** Iterator options */
	typedef enum
	{
		/** Iterate only children */
		kIterJustChildren	= 0x0100UL,

		/** Iterate only leaf nodes */
		kIterJustLeafNodes  = 0x0200UL,

		/** Iterate only leaf names */
		kIterJustLeafName   = 0x0400UL,

		/** Iterate omitting qualifiers */
		kIterOmitQualifiers = 0x0800UL
	} IteratorOptions;

	/** Skip options. These are used by IMetaDataIterator::Skip method
		@see IMetaDataIterator::Skip
	*/
	typedef enum
	{
		/** Skip the subtree below the current node */
		kIterSkipSubtree	= 0x0001UL,

		/** Skip the subtree below and remaining siblings of the current node. */
		kIterSkipSiblings   = 0x0002UL
	} SkipOptions;
	/** MetaData attributes */
	
	/**
		Set the MetaData block's packaged attribute. If packaged is kTrue then whenever
		this MetaData block is saved to a stream it will be packaged in a MetaData package. In
		addition when the data for this interface is saved to the database, if packaged
		is kTrue then the data will be streamed to the contiguous block section of the 
		database, otherwise it will be written into a regular database stream.
		@param	package	IN	The packaged attribute.
	*/
	virtual void 	Package(const bool16& package = kTrue) = 0;

	/**
		Query the MetaData block's packaged attribute.
		@return	kTrue if this MetaData block is packaged. kFalse otherwise.
	*/
	virtual bool16	IsPackaged() const = 0;

	/**
		Set the MetaData block's in place modification attribute.
		If in place modification is allowed it means that external software can modify the
		MetaData block. Next time the publication is opened we will keep changes made externally
		to any external property. The MetaData package mechanism will also indicate that this
		block can be modified in place.
		@param	inPlaceModification	IN	The in place modification attribute.
	*/
	virtual void	AllowInPlaceModification(const bool16& inPlaceModification = kTrue) = 0;

	/**
		Query the MetaData block's in place modification attribute.
		@return	kTrue if this MetaData block allows in place modification. kFalse otherwise.
	*/
	virtual bool16	CanModifyInPlace() const = 0;
	
	/**
		Set the MetaData block's expandable attribute.
		If expandable is kTrue then when the package is written out pad bytes will be included
		so that external entities can add MetaData properties to the packet.
		@param	expandable	IN	The expandable attribute.
	*/
	virtual void 	Expandable(const bool16& expandable = kTrue) = 0;
	
	/**
		Query the MetaData block's expandable attribute.
		@return	kTrue if this MetaData block is expandable. kFalse otherwise.
	*/
	virtual bool16	IsExpandable() const = 0;
	

	/** Persistance operations */
	
	/**
		Load this MetaData block from the given stream.
		@param	stream		IN	The stream that contains medadata (in UTF8 format).
		@param	numOfBytes	IN	Length of the metadata block. Pass -1 if the length is unknown.
		@return	kTrue if succeeded. kFalse otherwise.
	*/
	virtual bool16 	LoadFromStream(IPMStream* stream, int32 numOfBytes = -1) = 0;

	/**
		Save this MetaData block to the given stream.
		@param	stream						IN	The stream where the metadata will be written. The data will be in UTF8 format.
		@param	package						IN	If kTrue, the MetaData block is streamed out in a MetaData package.
		@param	allowInPlaceModification	IN	If kTrue, the writable attribute in the package header is set.
		@param	expandable					IN	if kTrue, padding is added. 
		@param	packetDisabled				IN	If kTrue, a disabled packet id is generated instead of the standard one. This is used internally.
		@return	kTrue if succeeded. kFalse otherwise.
	*/
	virtual bool16 	SaveToStream(IPMStream* stream, const bool16& package = kTrue,
								 const bool16& allowInPlaceModification = kTrue,
								 const bool16& expandable = kTrue,
								 const bool16& packetDisabled = kFalse) const = 0;

	/**
		Appends external properties from the stream.
		@param stream				IN	The stream that contains the metadata (in UTF8 format) to be appended.
		@param replaceOld			IN	If kFalse, a property that exists in current metadata will not be replace by the same property in the stream.
		@param treatAllAsExternal	IN	Optional. If kTrue, all properties are treated as external.
		@return	kTrue if succeeded. kFalse otherwise.
	*/
	virtual bool16 	AppendFromStream(IPMStream* stream, const bool16 replaceOld, const bool16 treatAllAsExternal = kFalse) = 0;

	
	/** Wrappers on the XMPToolkit library */

	/**
		Return an IMetaDataIterator interface which must be released by the caller. 
		IMetaDataIterator enables one to iterate all the paths in this MetaData block. 
		@see IMetaDataIterator
		@param	ns		IN	The namespace to enumerate.
		@param	subPath	IN	Specifies the scope of the enumeration.
		@param	options	IN	The available option flags are:
								kXMP_IterJustChildren - Just visit the immediate children of the root, default is subtree.
								kXMP_IterJustLeafNodes - Just visit the leaf nodes, default visits all nodes.
								kXMP_IterJustLeafName - Return just the leaf part of the path, default is the full path.
								kXMP_IterOmitQualifiers - Omit all qualifiers.

		@return	An interface which iterates properties of the specified subPath. Must be released by the caller.
	*/
	virtual IMetaDataIterator* Enumerate(const PMString& ns, const PMString& subPath, const IMetaDataAccess::IteratorOptions& options = IMetaDataAccess::kIterJustChildren) const = 0;
	/**
		Return an IMetaDataIterator interface which must be released by the caller. 
		IMetaDataIterator enables one to iterate all the paths in this MetaData block. 
		@see IMetaDataIterator
		@return	An interface which iterates properties of all paths. Must be released by the caller.
	*/		
	virtual IMetaDataIterator* Enumerate() const = 0;
	/** General property access */
	/**
		Get the value at the property specified by ns and path.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property..
		@param	value	OUT	The value of the property.
		@param  options OUT Bit flags that describe the property. Default to 0 if the flags are not wanted.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 Get(const PMString& ns, const PMString& path, PMString& value, metadata::PropertyOptions* options = 0) const = 0;
	
    /**
		Set the specified value at the end of the specified path, with the optionally specified features.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	IN	The value of the property.
		@param  options IN  Bit flags that describe the property. Default to metadata::kNoOptions if the flags are not needed.
	*/
	virtual void Set(const PMString& ns, const PMString& path,
        			 const PMString& value, const metadata::PropertyOptions options = metadata::kNoOptions) = 0;
        			 
	/**
		Remove the specifed property and all of its sub-properties.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
	*/
	virtual void Remove(const PMString& ns, const PMString& path) = 0;

	/**
		Get the number of items in the structured container specified by ns and path.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@return Number of items in the container.
	*/
	virtual size_t Count(const PMString& ns, const PMString& path) const = 0;

	/**
		Check if a property exists.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@return	kTrue if the property exists, kFalse otherwise.
	*/
	virtual bool16 PropertyExists(const PMString& ns, const PMString& path) const = 0;
	
	/** Array item access */
	/**
		Append a new item to an array. The array will be automatically created if it doesn't exist.
		@param	ns			IN	The namespace of the array. Must not be an empty string.
		@param	arrayName	IN	The name of the array.
		@param	value		IN	The value of the array item.
		@param	type		IN	The type of the array.
		@param  options 	IN  Bit flags that describe the array item. Default to metadata::kNoOptions if the flags are not needed.
	*/
    virtual void AppendArrayItem(const PMString& ns, const PMString& arrayName, 
								const PMString& value, const MetaDataStructContainerType type,
								const metadata::PropertyOptions options = metadata::kNoOptions) = 0;

	/**
		Modify an array item.
		@param	ns			IN	The namespace of the array. Must not be an empty string.
		@param	arrayName	IN	The name of the array.
		@param	index		IN	The index of the array item. Arrays are indexed from 1. 
								Use metadata::kArrayLastItem for the last item in the array.
		@param	value		IN	The value of the array item.
		@param  options 	IN  Bit flags that describe the array item. Default to metadata::kNoOptions if the flags are not needed.
	*/
    virtual void SetArrayItem(const PMString& ns, const PMString& arrayName, 
								int32 index, const PMString& value,
                    			const metadata::PropertyOptions options = metadata::kNoOptions) = 0;
                    			
	/**
		Get the value of an array item.
		@param	ns			IN	The namespace of the array. Must not be an empty string.
		@param	arrayName	IN	The name of the array.
		@param	index		IN	The index of the array item. Arrays are indexed from 1. 
								Use metadata::kArrayLastItem for the last item in the array.
		@param	value		OUT	The value of the array item.
		@param  options 	OUT  Bit flags that describe the array item.  Default to 0 if the flags are not wanted.
		@return	kFalse if the array item doesn't exist. kTrue otherwise.
	*/
    virtual bool16 GetArrayItem(const PMString& ns, const PMString& arrayName, 
								int32 index, PMString& value,
                    			metadata::PropertyOptions* options = 0) const = 0;
                    			
	/**
		Delete an array item.
		@param	ns			IN	The namespace of the array. Must not be an empty string.
		@param	arrayName	IN	The name of the array.
		@param	index		IN	The index of the array item. Arrays are indexed from 1. 
								Use metadata::kArrayLastItem for the last item in the array.
	*/
    virtual void DeleteArrayItem(const PMString& ns, const PMString& arrayName, int32 index) = 0;
                    			
    /** Structure field access */
	/**
		Set a field within a structure.
		@param	ns			IN	The namespace of the structure. Must not be an empty string.
		@param	structName	IN	The name of the structure.
		@param	fieldNs		IN	The namespace of the field. Maybe be an empty string.
		@param	fieldName	IN	The name of the field.
		@param	value		IN	The value of the field.
		@param  options		IN  Bit flags that describe the property. Default to metadata::kNoOptions if the flags are not needed.
	*/
	virtual void SetStructField(const PMString& ns, const PMString& structName, 
								const PMString& fieldNs, const PMString& fieldName, const PMString& value,
								const metadata::PropertyOptions options = metadata::kNoOptions) = 0;

	/**
		Get a field within a structure.
		@param	ns			IN	The namespace of the structure. Must not be an empty string.
		@param	structName	IN	The name of the structure.
		@param	fieldNs		IN	The namespace of the field. Maybe be an empty string.
		@param	fieldName	IN	The name of the field.
		@param	value		OUT	The value of the field.
		@param  options		OUT Bit flags that describe the property. Default to 0 if the flags are not wanted.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 GetStructField(const PMString& ns, const PMString& structName, 
								const PMString& fieldNs, const PMString& fieldName, PMString& value,
								const metadata::PropertyOptions* options = 0) const = 0;

  	/**
		Delete a field within a structure.
		@param	ns			IN	The namespace of the structure. Must not be an empty string.
		@param	structName	IN	The name of the structure.
		@param	fieldNs		IN	The namespace of the field. Maybe be an empty string.
		@param	fieldName	IN	The name of the field.
	*/
	virtual void DeleteStructField(const PMString& ns, const PMString& structName, 
								const PMString& fieldNs, const PMString& fieldName) = 0;

    /** Localized text in alt-text array */
	/**
		Set the value of an item within an alt-text array.
		@param	ns				IN	The namespace of the structure. Must not be an empty string.
		@param	arrayName		IN	The name of the structure. May be a general XPath expression. Must not be empty.
		@param	genericLang		IN	The name of the generic language as an RFC 1766 string.
								May be an empty string if no generic language is wanted
		@param	specificLang	IN	The name of the specific language as an RFC 1766 string.
								Must not be empty. Maybe "x-default".
		@param	value			IN	The value of the item.
		@param  options			IN  Bit flags that describe the property. Default to metadata::kNoOptions if the flags are not needed.
	*/
	virtual void SetLocalizedText(const PMString& ns, const PMString& arrayName, 
								const PMString& genericLang, const PMString& specificLang, const PMString& value, 
								const metadata::PropertyOptions options = metadata::kNoOptions) = 0;

	/**
		Get the value of an item within an alt-text array.
		@param	ns				IN	The namespace of the structure. Must not be an empty string.
		@param	arrayName		IN	The name of the structure. May be a general XPath expression. Must not be empty.
		@param	genericLang		IN	The name of the generic language as an RFC 1766 string.
								May be an empty string if no generic language is wanted
		@param	specificLang	IN	The name of the specific language as an RFC 1766 string.
								Must not be empty. Maybe "x-default".
		@param	actualLang		OUT	The language of the selected array item, if an appropriate array item is found.
		@param	value			OUT	The value of the field.
		@param  options			OUT Bit flags that describe the property. Default to 0 if the flags are not wanted.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 GetLocalizedText(const PMString& ns, const PMString& arrayName, 
								const PMString& genericLang, const PMString& specificLang,
								PMString& actualLang, PMString& value, 
								const metadata::PropertyOptions* options = 0) const = 0;

	/** XPath composition utilities */
	
	/**
		Compose the XPath expression for an item in an array.
		@param	schemaNs	IN	The namespace of the stream. Must not be empty.
		@param	arrayName	IN	The name of the array. Must not be empty. May be a general XPath expression.
		@param	index		IN	The index of the array item. Arrays in XMP are indexed from 1.
								Use metadata::kArrayLastItem for the last item in the array. 
		@param	path		OUT	The composed path. This will be of the from "arrayName/ *[i]".
								If index is metadata::kArrayLastItem, the path will be "arrayName/ *[last()]".
	*/
	virtual void		ComposeArrayItemPath(const PMString& schemaNs, const PMString& arrayName, int32 index, PMString& path) const = 0;

	/**
		Compose the XPath expression for a field in a struct.
		@param	schemaNs	IN	The namespace of the stream. Must not be empty.
		@param	structName	IN	The name of the struct. Must not be empty. May be a general XPath expression.
		@param	fieldNs		IN	The namespace of the field. May be empty.
		@param	fieldName	IN	The name of the field. Must not be empty.
		@param	path		OUT	The composed path. This will be of the from "structName\fNS:fieldName", where "fNS is the prefix for fieldNs.
	*/
	virtual void		ComposeStructFieldPath(const PMString& schemaNs, const PMString& structName, const PMString& fieldNs, const PMString& fieldName, PMString& path) const = 0;

	/**
		Compose the XPath expression for a qualifier.
		@param	schemaNs	IN	The namespace of the stream. Must not be empty.
		@param	arrayName	IN	The name of the array. Must not be empty. May be a general XPath expression.
		@param	langName	IN	The name of the language. Must not be empty.
		@param	path		OUT	The composed path. This will be of the from "arrayName/ *[@xml:lang='langName']". 
	*/
	virtual void		ComposeLangSelector(const PMString& schemaNs, const PMString& arrayName, const PMString& langName, PMString& path) const = 0;

	/** The following set and get properties from common data types. */
	
	/**
		Set the boolean value of the specified property.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	IN	The value of the property.
	*/
	virtual void SetBoolean(const PMString& ns, const PMString& path, const bool16& value) = 0;

	/**
		Get the boolean value of the specified property.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	OUT	The value of the property.
		@return	kTrue if the property is found, kFalse otherwise.
	*/
	virtual bool16 GetBoolean(const PMString& ns, const PMString& path, bool16& value) const = 0;

	/**
		Set the DateTime value of the specified property.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	IN	The value of the property.
	*/
	virtual void SetDateTime(const PMString& ns, const PMString& path, const XMP_DateTime& value) = 0;

	/**
		Get the DateTime value of the specified property.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	OUT	The value of the property.
		@return	kTrue if the property is found, kFalse otherwise.
	*/
	virtual bool16 GetDateTime(const PMString& ns, const PMString& path, XMP_DateTime& value) const = 0;
	 
	/**
		Set the specified ResourceRef at the end of the specified path, with the optionally specified features.
		@param	ns			IN	The namespace of the properties.
		@param	path		IN	The path of the properties.
		@param	resource	IN	The ResourceRef to be set.
	*/
	virtual void SetResourceRef(const PMString& ns, const PMString& path, const metadata::ResourceRef& resource) = 0;

	/**
		Get ResourceRef specified by ns and path.
		@param	ns			IN	The namespace of the property.
		@param	path		IN	The path of the property..
		@param	resource	OUT	The value of the property.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 GetResourceRef(const PMString& ns, const PMString& path, metadata::ResourceRef& resource) const = 0;

	/**
		Set the instance ID of the document.
		@param	instanceID		IN	The instance ID.
	*/
	virtual void			SetInstanceID(const PMString& instanceID) = 0;

	/**
		Get the instance ID of the document.
		@return	the instance ID.
	*/
	virtual PMString 		GetInstanceID() const = 0;

	/**
		Generate a unique ID.
		@return	the ID.
	*/
	virtual PMString 		GenerateUniqueID() const = 0;

	/** Namespaces */
	/**
		Register a namespacename (which should be a URI) and a suggested prefix for composing qualified names.
		@param	ns		IN	The namespace to be registered.
		@param	suggestedPrefix	IN	The suggested prefix to be used if the URI is not yet registered. Must be a valid XML name.
		@param  registeredPrefix OUT The prefix actually registered for this URI.
		@return kTrue if the registered prefix matches the suggested prefix. kFalse otherwise.
	*/
	virtual bool16 RegisterNamespace(const PMString& ns, const PMString& suggestedPrefix, PMString& registeredPrefix) = 0;

	/**
		Get the prefix of a registered namespacename.
		@param	ns		IN	The URI of the namespace.
		@param	prefix	OUT	The prefix of the namespace.
		@return kTrue if the namespace is registered. kFalse otherwise.
	*/
	virtual bool16 GetNamespacePrefix(const PMString& ns, PMString& prefix) const = 0;

	/**
		Get the URI of a registered namespacename.
		@param	prefix	IN	The prefix of the namespace.
		@param	ns		OUT	The URI of the namespace.
		@return kTrue if the namespace is registered. kFalse otherwise.
	*/
	virtual bool16 GetNamespace(const PMString& prefix, PMString& ns) const = 0;

	/**
		Delete a namespace. Does nothing if the namespace is not registered.
		@param	ns		IN	The URI of the namespace.
	*/
	virtual void DeleteNamespace(const PMString& ns) = 0;
	

	/** Some other useful methods.	*/
	
	/**
		Set the MetaData block back to being empty.
	*/
	virtual void ClearAllProperties() = 0;
	
	/**
	 Duplicates a subtree in the metadata block.
	 
	 Note: As written, this utility does not perform any merging between the source and 
	 destination subtrees. If the destination subtree exists, it will be deleted before
	 the subtree is duplicated. 
	 
	 @param srcNS		IN The namespace for the source subtree
	 @param srcPath		IN The path for the source subtree
	 @param destNS		IN The namespace for the destination subtree
	 @param destPath	IN The path for the destination subtree
	 @return kTrue if the subtree was successfully duplicated, else kFalse
	 */
	virtual bool16 DuplicateSubtree(PMString const &srcNS, PMString const &srcPath, PMString const &destNS, PMString const &destPath) = 0;
//
//	Wrappers on XMP Document Operations Utilities
//
//	 Calls SXMPDocOps::NewXMP. -- FOR INTERNAL USE ONLY
	virtual void NewXMP() = 0;

//	 Calls SXMPDocOps::PrepareForSave -- FOR INTERNAL USE ONLY
	virtual void PrepareForSave(bool16 bIncludePantry = kFalse) = 0;

//	 Calls SXMPDocOps::NoteChange -- FOR INTERNAL USE ONLY
	virtual void NoteChange(PMString const &changeStr) = 0;

//	 Calls SXMPDocOps::NoteChange with "/metadata" -- FOR INTERNAL USE ONLY
	virtual void NoteMetaDataChanged() = 0;

//	 Calls SXMPDocOps::OpenXMP -- FOR INTERNAL USE ONLY
	virtual void OpenXMP() = 0;

//	 Calls SXMPDocOps::BranchXMP -- FOR INTERNAL USE ONLY
	virtual void BranchXMP() = 0;

//	 Tells whether NewXMP or OpenXMP have been called -- FOR INTERNAL USE ONLY
	virtual bool16 XMPDocOpsReady() = 0;

//	Adds an Ingredients List / Pantry entry for a linked file -- FOR INTERNAL USE ONLY
	virtual void AddIngredientXMP(
			std::string* filepath,					// pass nil to omit pantry entry
			const PMString& in_toPart,              // (Text)           The destination "part".
			const PMString& in_fromPart,            // (Text)           The source "part".
			const PMString& in_linkForm,
			const PMString& in_linkCategory,
			const PMString& in_filePath,
			const PMString& in_alternatePaths,
			const PMString& in_fileModTime,
			const PMString& in_placedXResolution,
			const PMString& in_placedYResolution,
			const PMString& in_placedResolutionUnit) = 0;

//	Remove an ingredient
	virtual void RemoveIngredientXMP(int nth) = 0;

//	Clear the Ingredients list
	virtual void ClearIngredientsXMP() = 0;

	/** Structure field access */
	/**
		Set a field within a structure.
		@param	ns			IN	The namespace of the structure. Must not be an empty string.
		@param	structName	IN	The name of the structure.
		@param	fieldNs		IN	The namespace of the field. Maybe be an empty string.
		@param	fieldName	IN	The name of the field.
		@param	value		IN	The value of the field.
		@param  options		IN  Bit flags that describe the property. Default to metadata::kNoOptions if the flags are not needed.
	*/
	virtual void SetStructField(const PMString& ns, const PMString& structName, 
								const PMString& fieldNs, const PMString& fieldName, const std::string& value,
								const metadata::PropertyOptions options = metadata::kNoOptions) = 0;

	/**
		Get a field within a structure.
		@param	ns			IN	The namespace of the structure. Must not be an empty string.
		@param	structName	IN	The name of the structure.
		@param	fieldNs		IN	The namespace of the field. Maybe be an empty string.
		@param	fieldName	IN	The name of the field.
		@param	value		OUT	The value of the field.
		@param  options		OUT Bit flags that describe the property. Default to 0 if the flags are not wanted.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 GetStructField(const PMString& ns, const PMString& structName, 
								const PMString& fieldNs, const PMString& fieldName, std::string& value,
								const metadata::PropertyOptions* options = 0) const = 0;

    /**
		Set the specified value at the end of the specified path, with the optionally specified features.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property.
		@param	value	IN	The value of the property.
		@param  options IN  Bit flags that describe the property. Default to metadata::kNoOptions if the flags are not needed.
	*/
	virtual void Set(const PMString& ns, const PMString& path,
								const std::string& value, const metadata::PropertyOptions options = metadata::kNoOptions) = 0;
        			 
	/** General property access */
	/**
		Get the value at the property specified by ns and path.
		@param	ns		IN	The namespace of the property.
		@param	path	IN	The path of the property..
		@param	value	OUT	The value of the property.
		@param  options OUT Bit flags that describe the property. Default to 0 if the flags are not wanted.
		@return	kFalse if any node along the path doesn't exist. kTrue otherwise.
	*/
	virtual bool16 Get(const PMString& ns, const PMString& path, std::string& value, metadata::PropertyOptions* options = 0) const = 0;

	/**
		Generate a document ID.
		@return	the ID.
	*/
	virtual PMString GenerateDocumentID() const = 0;
	
};


#endif // __IMetaDataAccess_h__
