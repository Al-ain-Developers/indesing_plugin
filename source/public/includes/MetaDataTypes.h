//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MetaDataTypes.h $
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
#ifndef __MetaDataTypes_h__
#define __MetaDataTypes_h__

#include "PMString.h"
#include "K2Vector.h"
#if defined WINDOWS && !defined(WIN_ENV)
#define WIN_ENV
#elif defined(MACINTOSH) && !defined(MAC_ENV)
#define MAC_ENV
#endif
#include "XMP_Const.h"

#if PUBLIC_BUILD
#pragma export on
#endif

/* Standard schema namespace URI constants */

/** XMP Basic Schema */
extern PUBLIC_DECL const char* const kNS_xmp;		

/** XMP Rights Management Schema */
extern PUBLIC_DECL const char* const kNS_xmpRights;		 

/** XMP Media Management Schema */
extern PUBLIC_DECL const char* const kNS_xmpMM;			 

/** XMP Basic Job Ticket Schema */
extern PUBLIC_DECL const char* const kNS_xmpBJ;			 

/** XMP text document schema */
extern PUBLIC_DECL const char* const kNS_xmpT ;			 

/** XMP Paged-Text Schema */
extern PUBLIC_DECL const char* const kNS_xmpTPg;		 

/** XMP Image Graphic Schema */
extern PUBLIC_DECL const char* const kNS_xmpGImg;		  

/** XMP IPTC Core Schema */
extern PUBLIC_DECL const char* const kNS_xmpIPTCCore;		  

/** Adobe PDF Schema */
extern PUBLIC_DECL const char* const kNS_pdf;			 

/** Photoshop Schema */
extern PUBLIC_DECL const char* const kNS_photoshop;		 

/** EXIF Schema */
extern PUBLIC_DECL const char* const kNS_exif;			 

/** aux Schema */
extern PUBLIC_DECL const char* const kNS_aux;			 

/** TIFF Schema */
extern PUBLIC_DECL const char* const kNS_tiff;			 

/** Adobe Stock Photo Schema */
extern PUBLIC_DECL const char* const kNS_stockPhoto;	 

/* XML namespace constants from outside Adobe */
/** Dublin Core Schema */
extern PUBLIC_DECL const char* const kNS_dc;			 

/** RDF namespace */
extern PUBLIC_DECL const char* const kNS_rdf;			 

/** XML namespace */
extern PUBLIC_DECL const char* const kNS_xml;			 


/* namespace constants for structured property fields*/
/** namespace for fields of the ResourceRef type */
extern PUBLIC_DECL const char* const kNS_xmpRscRef;		 

/** namespace for fields of the ResourceEvent type */
extern PUBLIC_DECL const char* const kNS_xmpRscEvent;	 

/** namespace for fields of the JobRef type */
extern PUBLIC_DECL const char* const kNS_xmpSTJob;		 

/** namespace for fields of the manifest type */
extern PUBLIC_DECL const char* const kNS_xmpSTMfs;		 

// other constants
/** empty value */
extern PUBLIC_DECL const char* const kXMP_NoValue;		 

/** XMP namespace */
namespace metadata {

/** metadata URI typedef */
typedef PMString URI;

/** metadata MIMEType typedef */
typedef PMString MIMEType;

/** metadata AgentName typedef */
typedef PMString AgentName;


/** This class is used for metadata date time generation */
class PUBLIC_DECL Clock
{
public:
	/** Fills the XMP_DateTime passed with the current date and time.
		@param dt	OUT	Current date and time is returned.
	*/
    virtual void timestamp(XMP_DateTime& dt);

	/** */
	virtual ~Clock();

private:
	static long ts_SequenceNumber;
};

/** AdobeARM agent name. */
#define kARMName AgentName("AdobeARM", PMString::kEncodingASCII)

/** Link forms */
typedef enum {
	/** Unknown link form */
	kUnknown = 0,

	/** Reference Content*/
	kRefContent,

	/** Reference Stream */
	kRefStream,

	/** Direct Content */
	kDirContent,

	/** Direct Stream */
	kDirStream
} LinkForm;

// A multiple part reference to a resource.
// If the referenced resource doesn't have XMP data, its file URL is used to generate the reference.
// Otherwise, its XMP data are used.

/** This class is used to store and manipulate reference to a XMP Media Management Properties */
class ResourceRef
{
public:
	/** Data type for the ResourceRef */
	typedef object_type data_type;

	/** Constructor 
		@param instanceID		IN	A Unique Instance Id of the document.
		@param documentID		IN	The common identifier for all versions and renditions of a document.
		@param origDocumentID	IN	The common identifier for the original document.
		@param versionID		IN	This property should be used primarily by a media management system.
		@param renditionClass	IN	Rendition class name for this resource.
		@param renditionParams	IN	May be used to provide additional rendition parameters that are too complex or verbose to encode in RenditionClass.
		@param manageTo			IN	A URI identifying the managed resource to the asset management system.
		@param manageUI			IN	A URI that can be used to access information about the managed resource through a webbrowser.
		@param manager			IN	Name of the asset management system that manages this resource.
		@param managerVariant	IN	Specifies a particular variant of the asset management system.
		@param fileURL			IN	URL for the file.
	*/
	ResourceRef(const PMString& instanceID = "", const metadata::URI& documentID = "", const metadata::URI& origDocumentID = "", const PMString& versionID = "", const PMString& renditionClass = "", const PMString& renditionParams = "",
		const PMString& manageTo = "", const PMString& manageUI = "", const PMString& manager = "", const PMString& managerVariant = "", const PMString& fileURL = "") :
		fInstanceID(instanceID), fDocumentID(documentID), fOrigDocumentID(origDocumentID), fVersionID(versionID), fRenditionClass(renditionClass), fRenditionParams(renditionParams),
		fManageTo(manageTo), fManageUI(manageUI), fManager(manager), fManagerVariant(managerVariant), fFileURL(fileURL)
		{ }

	/** Copy Constructor.
		@param	other	IN	Another resourceRef from which to create this resourceRef.
	*/
	ResourceRef(const ResourceRef& other) :
		fInstanceID(other.fInstanceID), fDocumentID(other.fDocumentID), fOrigDocumentID(other.fOrigDocumentID), fVersionID(other.fVersionID), fRenditionClass(other.fRenditionClass), fRenditionParams(other.fRenditionParams),
		fManageTo(other.fManageTo), fManageUI(other.fManageUI), fManager(other.fManager), fManagerVariant(other.fManagerVariant), fFileURL(other.fFileURL)
		{ }
	
	/** Assignment operator. 
		@param	other	IN	Another resourceRef from which to set this resourceRef.
		@return Reference to self.
	*/
	ResourceRef& operator=(const ResourceRef& other)
	{
		if (this != &other)
		{
			fInstanceID = other.fInstanceID;
			fDocumentID = other.fDocumentID;
			fOrigDocumentID = other.fOrigDocumentID;
			fVersionID = other.fVersionID;
			fRenditionClass = other.fRenditionClass;
			fRenditionParams = other.fRenditionParams,
			fManageTo = other.fManageTo;
			fManageUI = other.fManageUI;
			fManager = other.fManager;
			fManagerVariant = other.fManagerVariant;
			fFileURL = other.fFileURL;
		}
		
		return *this;
	};
	
	/** Equality operator.
		@param other	IN	Another resourceRef to compare from.
		@return	true if both are equal, false otherwise.
	*/
	bool operator==(const ResourceRef& other)
	{
		return fInstanceID == other.fInstanceID && fDocumentID == other.fDocumentID && fOrigDocumentID == other.fOrigDocumentID && fVersionID == other.fVersionID && fRenditionClass == other.fRenditionClass && fRenditionParams == other.fRenditionParams && 
				fManageTo == other.fManageTo && fManageUI == other.fManageUI && fManager == other.fManager && fManagerVariant == other.fManagerVariant && fFileURL == other.fFileURL;
	}
	
	/** Returns kTrue if any XMP Media Management Properties is not blank. 
		@return kTrue if any of the following
			Instance ID, Document ID, Version ID, RenditionClass, RenditionParams, ManageTo, ManageUI, Manager or ManagerVariant
			is not blank. kFalse otherwise.
	*/
	bool16 HasXMPReference() const
	{
		return !fInstanceID.empty() || !fDocumentID.empty() || !fOrigDocumentID.empty() || !fVersionID.empty() || !fRenditionClass.empty() || 
				!fRenditionParams.empty() || !fManageTo.empty() || !fManageUI.empty() || !fManager.empty() || !fManagerVariant.empty();
	}

	/** Clears all the resource references. */
	void Clear()
	{
		fInstanceID.clear();
		fDocumentID.clear();
		fOrigDocumentID.clear();
		fVersionID.clear();
		fRenditionClass.clear();
		fRenditionParams.clear();
		fManageTo.clear();
		fManageUI.clear();
		fManager.clear();
		fManagerVariant.clear();
		fFileURL.clear();
	}

	/** Sets the instance id of the XMP resource. 
		@param	instanceID	IN	Instance id.
	*/
	void SetInstanceID(const PMString& instanceID) { fInstanceID = instanceID; }

	/** Returns the instance id of the XMP resource. 
		@return		Instance Id.
	*/
	PMString GetInstanceID() const { return fInstanceID; }

	/** Sets the document id of the XMP resource.
		@param	documentID	IN	Document id.
	*/
	void SetDocumentID(const metadata::URI& documentID) { fDocumentID = documentID; }

	/** Returns the document id of the XMP resource.
		@return		Document id.
	*/
	metadata::URI GetDocumentID() const { return fDocumentID; }
	
	/** Sets the  common identifier for the original document (should stay the same for all derivatives, conversions, versions, and renditions of the document).
	 @param	origDocumentID	IN	The common identifier for the original document.
	 */
	void SetOrigDocumentID(const metadata::URI& origDocumentID) { fOrigDocumentID = origDocumentID; }
	
	/** Returns the common identifier for the origianl document from which all deriviatives, conversions, versions, and renditions came from.
	 @return		The common identifier for the original document (should stay the same for all derivatives, conversions, versions, and renditions of the document).
	 */
	metadata::URI GetOrigDocumentID() const { return fOrigDocumentID; }
	
	/** Sets the version id of the XMP resource.
		@param	versionID	IN	Version id.
	*/
	void SetVersionID(const PMString& versionID) { fVersionID = versionID; }

	/** Returns the version id of the XMP resource.
		@return		Version id.
	*/
	PMString GetVersionID() const { return fVersionID; }
	
	/** Sets the rendition class name of the XMP resource.
		@param	renditionClass	IN	The rendition class name.
	*/
	void SetRenditionClass(const PMString& renditionClass) { fRenditionClass = renditionClass; }

	/** Returns the rendition class name of the XMP resource.
		@return		The rendition class name.
	*/
	PMString GetRenditionClass() const { return fRenditionClass; }
	
	/** Sets the rendition parameters that are too complex or verbose to encode in RenditionClass. 
		@param	renditionParams	IN	The rendition parameters.
	*/
	void SetRenditionParams(const PMString& renditionParams) { fRenditionParams = renditionParams; }

	/** Returns the rendition parameters that are too complex or verbose to encode in RenditionClass. 
		@return		The rendition parameters.
	*/
	PMString GetRenditionParams() const { return fRenditionParams; }

	/** Sets the URI identifying the managed resource to the asset management system.
		@param	manageTo	IN	The URI identifying the managed resource to the asset management system.
	*/
	void SetManageTo(const PMString& manageTo) { fManageTo = manageTo; }

	/** Returns the URI identifying the managed resource to the asset management system.
		@return		The URI identifying the managed resource to the asset management system.
	*/
	PMString GetManageTo() const { return fManageTo; }

	/** Sets the URI that can be used to access information about the managed resource through a webbrowser.
		@param	manageUI	IN	The URI that can be used to access information about the managed resource through a webbrowser.
	*/
	void SetManageUI(const PMString& manageUI) { fManageUI = manageUI; }
	
	/** Returns URI that can be used to access information about the managed resource through a webbrowser. 
		@return		The URI that can be used to access information about the managed resource through a webbrowser.
	*/
	PMString GetManageUI() const { return fManageUI; }

	/** Sets the name of the asset management system that manages this resource.
		@param	manager	IN	The name of the asset management system.
	*/
	void SetManager(const PMString& manager) { fManager = manager; }

	/** Returns the name of the asset management system that manages this resource.
		@return		The name of the asset management system.
	*/
	PMString GetManager() const { return fManager; }

	/** Sets the name of a particular variant of the asset management system.
		@param	managerVariant	IN	The name of a particular variant of the asset management system.
	*/
	void SetManagerVariant(const PMString& managerVariant) { fManagerVariant = managerVariant; }

	/** Returns the name of a particular variant of the asset management system.
		@return		The name of a particular variant of the asset management system.
	*/
	PMString GetManagerVariant() const { return fManagerVariant; }

	/** Sets the URL for the file. 
		@param	fileURL	IN	The URL for the file.
	*/
	void SetFileURL(const PMString& fileURL) { fFileURL = fileURL; }

	/** Returns the URL for the file. 
		@return		The URL for the file.
	*/
	PMString GetFileURL() const { return fFileURL; }

private:
	PMString fInstanceID;
	metadata::URI fDocumentID;
	metadata::URI fOrigDocumentID;
	PMString fVersionID;
	PMString fRenditionClass;
	PMString fRenditionParams;
	PMString fManageTo;
	PMString fManageUI;
	PMString fManager;
	PMString fManagerVariant;
	PMString fFileURL;
};


/** These constants correspond to those defined in "XMP_Const.h". */
enum {  /* Values used as special cases. */
    /** Used as index meaning last existing item, "[last()]" in XPath. */
	kArrayLastItem      = -1,  
    /** Used as parse input buffer length. */
	kUseNullTermination = -1,  
    /** Used to read a BIB stream to EoS. */
	kMaxStreamLen       = -1   
};

/** PropertyOptions typedef */
typedef int32 PropertyOptions;

/** XMP property types, values and masks. */
enum 
{
	/** Is used for passing default values for PropertyOptions. */
	kNoOptions				= 0UL,
	
	//--- Option bits returned from the CXMPMeta::GetXyz functions.
    /* Options relating to the XML string form of the property value. */
    /** The value contains XMP markup. */
	kPropValueIsXML         = 0x00000001UL,   
    /** The value is a URI, use RDF's resource attribute. */
	kPropValueIsURI         = 0x00000002UL,   

    /* Options relating to qualifiers attached to a property. */
    /** The property has qualifiers, includes rdf:type and xml:lang. */
	kPropHasQualifiers      = 0x00000010UL,   
    /** This is a qualifier, includes rdf:type and xml:lang. */
	kPropIsQualifier        = 0x00000020UL,   
    /** Implies kXMP_PropHasQualifiers, property has xml:lang. */
	kPropHasLang            = 0x00000040UL,   
    /** Implies kXMP_PropHasQualifiers, property has rdf:type. */
	kPropHasType            = 0x00000080UL,   

    /* Options relating to the data structure form. */
    /** The value is a structure with nested fields. */
	kPropValueIsStruct      = 0x00000100UL,   
    /** The value is an array (RDF alt/bag/seq). */
	kPropValueIsArray       = 0x00000200UL,   
    /** Implies kXMP_PropValueIsArray, item order matters. */
	kPropArrayIsOrdered     = 0x00000400UL,   
    /** Implies kXMP_PropArrayIsOrdered, items are alternates. */
	kPropArrayIsAlternate   = 0x00000800UL,   

    /* Additional array options. */
    /** Implies kXMP_PropArrayIsAlternate, items are localized text. */
	kPropArrayIsAltText     = 0x00001000UL,   
    /* kInsertBeforeItem    = 0x00004000UL,   *** Used by SetXyz functions. */
    /* kInsertAfterItem     = 0x00008000UL,   *** Used by SetXyz functions. */

    /* Other miscellaneous options. */
    /** This property is an alias name for another property. */
	kPropIsAlias            = 0x00010000UL,   
    /** This property is the base value for a set of aliases. */
	kPropHasAliases         = 0x00020000UL,   
    /** This property is an "internal" property, owned by applications. */
	kPropIsInternal         = 0x00040000UL,   
    /** This property is not derived from the document content. */
	kPropIsStable           = 0x00100000UL,   
    /** This property is derived from the document content. */
	kPropIsDerived          = 0x00200000UL,   
    /** This property is in the stale properties list. */
	kPropIsStale            = 0x00400000UL,   

     /* kUI_AllowCommas       = 0x10000000UL,   *** Used by CXMPUtils::CatenateArrayItems and ::SeparateArrayItems. */

    /** This is a schema node. */
	kSchemaNode             = 0x80000000UL,   /* Returned by iterators. */

    /* Masks that are multiple flags. */
    /** Mask for array form (Array, Ordered, Alternate or AltText). */
	kPropArrayFormMask		= kPropValueIsArray | kPropArrayIsOrdered | kPropArrayIsAlternate | kPropArrayIsAltText,
    /** Is it simple or composite (array or struct)? */
	kPropCompositeMask      = kPropValueIsStruct | kPropArrayFormMask,	
    /** Reserved for transient use by the implementation. */
	kImplReservedMask       = 0x70000000UL,   
		
	//--- Option bits for the CXMPMeta::SetXyz functions.

    /* Options shared with GetXyz functions. */
    /*
    kPropValueIsXML         = 0x00000001UL,
    kPropValueIsURI         = 0x00000002UL,
    kPropValueIsStruct      = 0x00000100UL,
    kPropValueIsArray       = 0x00000200UL,
    kPropArrayIsOrdered     = 0x00000400UL,
    kPropArrayIsAlternate   = 0x00000800UL,
    kPropArrayIsAltText     = 0x00001000UL,
    */

    /* Options for array item location. */
    /** Insert a new item before the given index. */
	kInsertBeforeItem       = 0x00004000UL,   
    /** Insert a new item after the given index. */
	kInsertAfterItem        = 0x00008000UL,   

    /* Masks that are multiple flags. */
	/** Mask for property value (XML or URI). */
	kPropValueOptionsMask	= (kPropValueIsXML | kPropValueIsURI),
    /** Mask for array location (Insert Before Item or Insert After Item). */
	kPropArrayLocationMask	= kInsertBeforeItem | kInsertAfterItem
};

}

#ifndef TXMP_STRING_TYPE
#define TXMP_STRING_TYPE	std::string
#endif
#include "XMP.hpp"


#if PUBLIC_BUILD
#pragma export off
#endif

#endif // __MetaDataTypes_h__
