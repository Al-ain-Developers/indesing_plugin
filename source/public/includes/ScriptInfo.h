//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptInfo.h $
//  
//  Owner: Jonathan W. Brown
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
//  Note: Changes to these classes must be reflected in ScriptInfoTypes.fh
//  to ensure ReadWrite from the core scripting resources works correctly.
//  
//========================================================================================

#pragma once
#ifndef __SCRIPTINFO__
#define __SCRIPTINFO__

#include "ScriptInfoDefs.h"
#include "GUID.h"
#include "ScriptData.h"
#include "ScriptingDefs.h"
#include "IDThreading.h" // for spin_mutex

namespace ScriptInfo
{

/** A variable-length array is designated by a length of zero */
const int32 kVariableLength = 0x0 ;

class TypeInfo ;
/** A list of TypeInfos */
typedef K2Vector<TypeInfo> TypeInfoList ;

/**
	TypeInfo represents the type of a property, method parameter, or method return value
	in a scripting DOM. Base types are defined in ScriptingID.h. Objects and Enums 
	defined in a scripting document object model (DOM) may also be valid types.
*/
class PUBLIC_DECL TypeInfo
{
	public:
		typedef object_type data_type ;

		/** Base type constructor */
		TypeInfo( const ScriptElementID& siid = kInvalidScriptElementID, int32 length = 1 ) :
			fType( siid ), fLength( length ), fMin(), fMax(), fDefault(), 
			fSubtypes(), fStructFieldName(), fFormatted( kFalse ) {}

		/** Variable type constructor */
		TypeInfo( const TypeInfoList& variableTypes, int32 length = 1 ) :
			fType( kScriptInfoVariableType ), fLength( length ), fMin(), fMax(), fDefault(), 
			fSubtypes( variableTypes ), fStructFieldName(), fFormatted( kFalse ) {}

		/** Add an additional subtype (making this a variable type) */
		void						AddType( const TypeInfo& subType ) ;
		/** Change the length */
		void						SetLength( int32 length )		{ fLength = length ; }

		/** Get the type */
		const ScriptElementID&		GetType() const					{ return fType ; }
		/** Get the length */
		int32						GetLength() const				{ return fLength ; }
		/** Get the minimum value */
		const ScriptData&			GetMinimum() const				{ return fMin ; }
		/** Get the maximum value */
		const ScriptData&			GetMaximum() const				{ return fMax ; }
		/** Get the default value */
		const ScriptData&			GetDefault() const				{ return fDefault ; }
		/** Get the subtypes in a variable type */
		const TypeInfoList&			GetVariableTypes() const ;
		/** Get the subtypes in a struct type */
		const TypeInfoList&			GetStructFields() const ;
		/** Get the name of a struct field */
		const PMString&				GetStructFieldName() const		{ return fStructFieldName ; }
		/**
			Get the formatted name
			@param context the request context in which to format the name
		*/
		PMString					GetFormattedStructFieldName( const RequestContext& context ) const ;
		/**
			For a record type, get the object that governs the property ids
			@param context for the query
			@return the governing object's element
		*/
		const ObjectScriptElement*	GetRecordTypeObject( const RequestContext& context ) const ;

		/** Returns kTrue if the type has a max and/or min value */
		bool16						HasRangeData() const			{ return ( !fMin.IsEmpty() || !fMax.IsEmpty() ) ; }
		/** Returns kTrue if the type has a default value */
		bool16						HasDefault() const				{ return !fDefault.IsEmpty() ; }

		/** Returns kTrue if the type is valid and not an object or enum type */
		bool16						IsBaseType() const				{ return ( kScriptInfoFirstBaseType <= fType && fType <= kScriptInfoLastBaseType ) ; }
		/** Returns kTrue if the length is not 1 (could be a record type) */
		bool16						IsArrayType() const				{ return ( fLength != 1 ) ; }
		/** Returns kTrue if the type is a variable type */
		bool16						IsVariableType() const			{ return ( fType == kScriptInfoVariableType ) ; }
		/** Returns kTrue if the type is a struct type */
		bool16						IsStructType() const			{ return ( fType == kScriptInfoStructType ) ; }
		/** Returns kTrue if the type is a record type (doesn't check variable subtypes) */
		bool16						IsRecordType() const			{ return ( fType == kScriptInfoRecordType ) ; }
		/** Returns kTrue if the type is a valid object type (doesn't check variable subtypes)
			@param context for the query
		*/
		bool16						IsObjectType( const RequestContext& context ) const ;
		/**
			Returns kTrue if the type is a valid enum type (doesn't check variable subtypes)
			@param context for the query
		*/
		bool16						IsEnumType( const RequestContext& context ) const ;
		/**
			Returns kTrue if the type is a valid type def (doesn't check variable subtypes)
			@param context for the query
		*/
		bool16						IsTypeDef( const RequestContext& context ) const ;
		/**
			Returns kTrue if the type is valid or, if a variable or struct type, if ALL of its subtypes are valid
			@param context for the query
		*/
		bool16						IsValidType( const RequestContext& context ) const ;
		/**
			Returns kTrue if this type is valid or, if a variable type, if ANY of its subtypes is valid
			@param context for the query
		*/
		bool16						HasAnyValidType( const RequestContext& context ) const ;
		/**
			Returns kTrue if the value is valid for this type
			@param value is the value to test
			@param the object context for the test (must not be nil)
		*/
		bool16						IsValidValue( const ScriptData& value, const ObjectScriptElement* ) const ;

		/**
			Revise the type in the context of the supplied object (i.e., if the specified 
			type is kContainerObjectScriptElement or kContainerParentScriptElement).
			@param the object context (may be nil)
		*/
		void						FormatType( const ObjectScriptElement* ) ;

		/**
			Convert this type into a string representation. This is the preferred overload.
			@param the object context for the conversion (must not be nil)
			@param includeInfo options are defined in enum TypeFormattingInfo
			@return the string representation
		*/
		PMString					GetTypeAsString( const ObjectScriptElement*, int32 includeInfo = kIncludeRangeData ) const ;

		/**
			Convert this type into a string representation. Use this overload only if no ObjectScriptElement is relevant.
			@param context for the conversion
			@param includeInfo options are defined in enum TypeFormattingInfo
			@return the string representation
		*/
		PMString					GetTypeAsString( const RequestContext& context, int32 includeInfo = kIncludeRangeData ) const ;

		/** */
		bool16						operator==( const TypeInfo& ) const ;
		/** Persist this object */
		void						ReadWrite( IPMStream* s ) ;

	private:
		ScriptElementID				fType ;				//either a base type (from ScriptingID.h), an object type, an enum type, or a typedef
		int32						fLength ;			//if != 1, this is an array; if == 0, this is a variable length array
		ScriptData					fMin ;				//minimum value (empty, if none)
		ScriptData					fMax ;				//maximum value (empty, if none)
		ScriptData					fDefault ;			//default value (empty, if none)
		TypeInfoList				fSubtypes ;			//the list of subtypes for a variable type, fields for a struct type, or governing object for a record type
		PMString					fStructFieldName ;	//field name for a struct type
		bool16						fFormatted ;		//whether FormatType has been called
} ;

DEFINEK2READWRITE( TypeInfo )

//----------------------------------------------------------------------------
/**
	The base class for sub-elements in a scripting DOM.
*/
class PUBLIC_DECL BaseScriptInfo
{
	public:
		typedef object_type data_type ;

		/** */
		BaseScriptInfo() : fScriptID(), fName( new PMString() ), fDescription( new PMString() )
		{
		#ifdef ID_ENABLE_DEBUGGING
			fWhoAmI = nil ;
		#endif
		}
		/** */
		BaseScriptInfo(  const ScriptID& id, const PMString& name, const PMString& desc ) : 
			fScriptID( id ), fName( new PMString( name ) ), fDescription( new PMString( desc ) )
		{
		#ifdef ID_ENABLE_DEBUGGING
			fWhoAmI = nil ;
		#endif
		}
		/** */
		BaseScriptInfo( const BaseScriptInfo& other ) { *this = other ; }
		/** */
		virtual ~BaseScriptInfo();

		/** Get the ScriptID */
		const ScriptID&				GetScriptID() const					{ return fScriptID ; }

		/** Get the name */
		const PMString&				GetName() const						{ return *fName ; }
		/** Set the name */
		void						SetName( const PMString& name ) ;
		/**
			Get the formatted name
			@param policy indicates how to format the name
		*/
		const PMString&				GetFormattedName( const FormatNamePolicy& policy ) const ;
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as ) const ;

		/** Get the description */
		virtual PMString			GetDescription() const			{ return BaseScriptInfo::GetFormattedDescription( nil ) ; }

		/** */
		BaseScriptInfo&				operator=( const BaseScriptInfo& ) ;
		/** */
		bool16						operator==( const BaseScriptInfo& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	protected:
		/** Get the formatted description in the context of the supplied object */
		PMString					GetFormattedDescription( const ObjectScriptElement* ) const ;
		/** Format a description in the context of the supplied object */
		static void					FormatDescription( PMString& desc, const ObjectScriptElement* ) ;
		mutable IDThreading::spin_mutex		fMutex;
	
		typedef IDThreading::lock_guard<IDThreading::spin_mutex> LockGuard;

	private:
		ScriptID					fScriptID ;
		boost::shared_ptr<PMString>	fName ;
		boost::shared_ptr<PMString>	fDescription ;

		mutable FormatNamePolicy	fLastFormatNamePolicy ;
		mutable PMString			fLastFormattedName ;

#ifdef ID_ENABLE_DEBUGGING
	public:
		/** Get a string describing this object (debug-only) */
		virtual ConstCString		WhoAmI() const ;
		mutable char *				fWhoAmI ;
#endif
} ;

//----------------------------------------------------------------------------
/**
	The base class for elements in a scripting DOM.
*/
class PUBLIC_DECL ScriptElement : public BaseScriptInfo
{
	public:
		/** */
		ScriptElement() {}
		/** */
		ScriptElement( const ScriptElementID& siid, const ScriptID& id, const PMString& name, const PMString& desc ) :
			BaseScriptInfo( id, name, desc ), fScriptElementID( siid ) {}
		/** */
		virtual ~ScriptElement() {}

		/** Get the context */
		const ElementContext&		GetContext() const				{ return fContext ; }
		/** Get the ScriptElementID */
		const ScriptElementID&		GetScriptElementID() const		{ return fScriptElementID ; }
		/** Get the PluginID in which this element was defined */
		const PluginID&				GetPluginID() const				{ return fPluginID ; }
		/** Get all the metadata */
		const ScriptRecordData&		GetMetadata() const				{ return fMetadata ; }
		/** Get all the metadata */
			  ScriptRecordData&		GetMetadata()					{ return fMetadata ; }
		/** Check this element for metadata by key, and, if found, retrieve its value
			@param id is the metadata key IN
			@param value is filled in with the value associated with the key, if the key is found OUT
			@return kTrue if the key is found, else kFalse
		*/
			  bool16				HasMetadata( const ScriptID& key, ScriptData& value ) const ;
		/** Check this element for metadata by key and value
			@param m is the metadata key/value pair to match IN
			@return kTrue if the key/value pair is found, else kFalse
		*/
			  bool16				HasMetadata( const ScriptIDValuePair& kvp ) const ;

		/** */
		bool16						operator==( const ScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

		/** Set the context */
		void						SetContext( const ElementContext& context ) { fContext = context ; }
		/** Set the PluginID in which this element was defined */
		void						SetPluginID( const PluginID& ) ;

	private:
		ElementContext				fContext ;
		ScriptElementID				fScriptElementID ;
		PluginID					fPluginID ;
		ScriptRecordData			fMetadata ;

#ifdef ID_ENABLE_DEBUGGING
	public:
		/** Get a string describing this object (debug-only) */
		virtual ConstCString		WhoAmI() const ;
#endif
} ;

//----------------------------------------------------------------------------
/**
	TypeDefScriptElement represents a named type definition in a scripting DOM.
*/
class PUBLIC_DECL TypeDefScriptElement : public ScriptElement
{
	public:
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kTypeDefElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }

		/** Get the underlying type in the context of the supplied object */
		TypeInfo					GetDefinedType( const ObjectScriptElement* ) const ;

		/** */
		bool16						operator==( const TypeDefScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	private:
		TypeInfo					fType ;
} ;

//----------------------------------------------------------------------------
/**
	SuiteScriptElement represents a suite in a scripting DOM.
*/
class PUBLIC_DECL SuiteScriptElement : public ScriptElement
{
	public:
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kSuiteElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
} ;

//----------------------------------------------------------------------------
/**
	ObjectScriptElement represents an object in a scripting DOM.
*/
class PUBLIC_DECL ObjectScriptElement : public ScriptElement
{
	public:
		/** */
		ObjectScriptElement() ;
		/** */
		ObjectScriptElement( const ObjectScriptElement&, const RequestContext& ) ;

		/** Returns kTrue if this object has a singular form */
		bool16						HasSingular() const				{ return GetScriptID() != kInvalidScriptID ; }
		/** Returns kTrue if this object has a collection form */
		bool16						HasCollection() const				{ return fCollection.GetScriptID() != kInvalidScriptID ; }

		/**
			Get the formatted name
			@param as which type of script element
		*/
		const PMString&				GetFormattedName( ScriptElementType as = kObjectElement ) const ;
		/** Get the GUID */
		const GUID&					GetGUID() const					{ return fGUID ; }
		/** Get the suite */
		const ScriptElementID&		GetSuite() const				{ return fSuite ; }

		/** Get the collection object info */
		const BaseScriptInfo*		GetCollectionInfo() const			{ return &fCollection ; }
		/** Get the collection object info */
			  BaseScriptInfo*		GetCollectionInfo()					{ return &fCollection ; }
		/**
			Return the formatted collection name
			@param as which kind of element
		*/
		PMString					GetCollectionFormattedName( ScriptElementType as = kObjectElement ) const ;
		/** Get the collection GUID */
		const GUID&					GetCollectionGUID() const			{ return fCollectionGUID ; }

		/**
			Returns kTrue if the property is read-only on this object
			@param propertyID - the property to check
			@param obsoleteArg - ignored
		*/
		bool16						IsPropertyReadOnly( const ScriptElementID& propertyID, bool16 obsoleteArg = kTrue ) const ;
		/**
			Returns kTrue if the property is read-only on this object
			@param propertyID - the property to check
			@param obsoleteArg - ignored
		*/
		bool16						IsPropertyReadOnly( const ScriptID& propertyID, bool16 obsoleteArg = kTrue ) const ;

		/**	Get the id of the base object */
		const ScriptElementID&		GetBaseObject() const			{ return fBaseObject ; }
		/** Get the base object (or nil, if none) */
		const ObjectScriptElement*	FindBaseObject() const ;
		/**
			Returns kTrue if this object is or is based on the specified object
			@param id - the base object to test
		*/
		bool16						IsObjectType( const ScriptElementID& id ) const ;
		/**
			Returns kTrue if this object is or is based on the specified object type
			@param type - the base type to test
		*/
		bool16						IsObjectType( const ScriptID& type ) const ;
		/** Returns kTrue if this object is a preferences object */
		bool16						IsPreferencesObject() const { return IsObjectType( ScriptID( c_PrefsObject ) ) ; }
		/** Returns kTrue if this object is a singleton child object */
		bool16						IsSingletonChild() const { return !HasCollection() ; }

		/** Return an iterator of objects for which this object is a base object */
		ObjectElementIterator		Subclasses() const ;

		/** Find provider information for a parent of this object */
		const ParentProviderPacket*			FindParent( const ScriptElementID& id ) const ;
		/** Find provider information for a parent of this object */
		const ParentProviderPacket*			FindParent( const ScriptID& id ) const ;
		/** Find provider information for a parent of this object */
		const ParentProviderPacket*			FindParent( const PMString& name, ScriptElementType as = kObjectElement ) const ;

		/** Find provider information for a child of this object */
		const ChildProviderPacket*			FindChild( const ScriptElementID& id ) const ;
		/** Find provider information for a child of this object */
		const ChildProviderPacket*			FindChildBySingularID( const ScriptID& id ) const ;							//the ScriptID of the singular object
		/** Find provider information for a child of this object */
		const ChildProviderPacket*			FindChildByCollectionID( const ScriptID& id ) const ;							//the ScriptID of the collection object
		/** Find provider information for a child of this object */
		const ChildProviderPacket*			FindChildBySingularName( const PMString& name, ScriptElementType as = kObjectElement ) const ;	//the name of the singular object
		/** Find provider information for a child of this object */
		const ChildProviderPacket*			FindChildByCollectionName( const PMString& name, ScriptElementType as = kObjectElement ) const ;	//the name of the collection object

		/** Find provider information for a method of this object */
		const MethodProviderPacket*			FindMethod( const ScriptElementID& id ) const ;
		/** Find provider information for a method of this object */
		const MethodProviderPacket*			FindMethod( const ScriptID& id ) const ;
		/** Find provider information for a method of this object */
		const MethodProviderPacket*			FindMethod( const PMString& name, ScriptElementType as = kMethodElement ) const ;

		/** Find provider information for a collection method on a particular parent of this object */
		const CollectionMethodProviderPacket*	FindCollectionMethod( const ObjectScriptElement* parent, const ScriptElementID& id ) const ;
		/** Find provider information for a collection method on a particular parent of this object */
		const CollectionMethodProviderPacket*	FindCollectionMethod( const ObjectScriptElement* parent, const ScriptID& id ) const ;
		/** Find provider information for a collection method on a particular parent of this object */
		const CollectionMethodProviderPacket*	FindCollectionMethod( const ObjectScriptElement* parent, const PMString& name, ScriptElementType as = kMethodElement ) const ;

		/** Find provider information for a property of this object */
		const PropertyProviderPacket*		FindProperty( const ScriptElementID& id ) const ;
		/** Find provider information for a property of this object */
		const PropertyProviderPacket*		FindProperty( const ScriptID& id ) const ;
		/** Find provider information for a property of this object */
		const PropertyProviderPacket*		FindProperty( const PMString& name, ScriptElementType as = kPropertyElement ) const ;

		/** Find provider information for properties of this object associated with a particular attribute */
		PropertyProviderIterator			FindProperties( const ClassID& attributeID ) const ;

		/** Find provider information for an event of this object */
		const EventProviderPacket*		FindEvent( const ScriptElementID& id ) const ;
		/** Find provider information for an event of this object */
		const EventProviderPacket*		FindEvent( const ScriptID& id ) const ;
		/** Find provider information for an event of this object */
		const EventProviderPacket*		FindEvent( const PMString& name, ScriptElementType as = kEventElement ) const ;

		/**
			Retrieve an iterator for parents of this object
		*/
		ParentProviderIterator				Parents() const ;
		/**
			Retrieve an iterator for children of this object
		*/
		ChildProviderIterator				Children() const ;
		/**
			Retrieve an iterator for methods of this object
			@param iterateBaseObjects - whether to include elements from base object(s)
		*/
		MethodProviderIterator				Methods( bool16 iterateBaseObjects = kTrue ) const ;
		/**
			Retrieve an iterator for collection methods of this object
			@param parent - pass valid parent to limit iteration to collection methods on a particular parent
		*/
		CollectionMethodProviderIterator	CollectionMethods( const ObjectScriptElement* parent = nil ) const ;
		/**
			Retrieve an iterator for properties of this object
			@param iterateBaseObjects - whether to include elements from base object(s)
		*/
		PropertyProviderIterator			Properties( bool16 iterateBaseObjects = kTrue ) const ;

		/**
			Retrieve an iterator for events of this object
			@param iterateBaseObjects - whether to include elements from base object(s)
		*/
		EventProviderIterator				Events( bool16 iterateBaseObjects = kTrue ) const ;

		/** Add a subclass object of this object */
		void						AddSubclass(	const ObjectScriptElement* subclass ) ;
		/** Add a parent to this object */
		void						AddParent(		const ParentProviderPacket& pp ) ;
		/** Add a child to this object */
		void						AddChild(		const ChildProviderPacket& pp ) ;
		/** Add a method to this object */
		void						AddMethod(		const MethodProviderPacket& pp ) ;
		/** Add a collection method to this object */
		void						AddCollectionMethod(	const CollectionMethodProviderPacket& pp ) ;
		/** Add a property to this object */
		void						AddProperty(	const PropertyProviderPacket& pp ) ;
		/** Add an event to this object */
		void						AddEvent(		const EventProviderPacket& pp ) ;

		/** */
		bool16						operator==( const ObjectScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

		/** Get the request context */
		const RequestContext&		GetRequestContext() const ;

		/** Sort children */
		void						SortChildren(PacketComp func);

	private:
		/** Internal use only; use ObjectScriptElement::Parents() instead */
		const ParentProviderLookup&			GetElements( AccessParents* ) const			{ return fParents ; }
		/** Internal use only; use ObjectScriptElement::Children() instead */
		const ChildProviderLookup&			GetElements( AccessChildren* ) const		{ return fChildren ; }
		/** Internal use only; use ObjectScriptElement::Methods() instead */
		const MethodProviderLookup&			GetElements( AccessMethods* ) const			{ return fMethods ; }
		/** Internal use only; use ObjectScriptElement::CollectionMethods() instead */
		const CollectionMethodProviderLookup&	GetElements( AccessCollectionMethods* ) const	{ return fCollectionMethods ; }
		/** Internal use only; use ObjectScriptElement::Properties() instead */
		const PropertyProviderLookup&		GetElements( AccessProperties* ) const		{ return fProperties ; }
		/** Internal use only; use ObjectScriptElement::Events() instead */
		const EventProviderLookup&			GetElements( AccessEvents* ) const			{ return fEvents ; }
		friend class ProviderPacketIterator<ObjectScriptElement, ParentProviderPacket, AccessParents> ;
		friend class ProviderPacketIterator<ObjectScriptElement, ChildProviderPacket, AccessChildren> ;
		friend class ProviderPacketIterator<ObjectScriptElement, MethodProviderPacket, AccessMethods> ;
		friend class ProviderPacketIterator<ObjectScriptElement, CollectionMethodProviderPacket, AccessCollectionMethods> ;
		friend class ProviderPacketIterator<ObjectScriptElement, PropertyProviderPacket, AccessProperties> ;
		friend class ProviderPacketIterator<ObjectScriptElement, EventProviderPacket, AccessEvents> ;

		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kObjectElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }

	private:
		GUID						fGUID ;
		BaseScriptInfo				fCollection ;
		GUID						fCollectionGUID ;
		ScriptElementID				fBaseObject ;
		mutable const ObjectScriptElement*	fBaseObjectCache ;
		ScriptElementID				fSuite ;

		//the following data is not read from the resource nor persisted; it is constructed at run-time
		const RequestContext*		fRequestContext ;			//request context of this object
		ParentProviderLookup		fParents ;					//parents of this object
		ChildProviderLookup			fChildren ;					//objects of which this object is a parent
		MethodProviderLookup		fMethods ;					//methods on this object
		CollectionMethodProviderLookup	fCollectionMethods ;	//methods on a collection of this object
		PropertyProviderLookup		fProperties ;				//properties on this object
		EventProviderLookup			fEvents ;					//events on this object

		ObjectScriptElementList		fSubclasses ;				//subclasses of this object

		//the following vectors are used to cache a sorted list of previously found properties for performance reasons
		mutable K2Vector<KeyValuePair<ScriptID, const PropertyProviderPacket*> >		fPropertiesByScriptID ;
		mutable K2Vector<KeyValuePair<ScriptElementID, const PropertyProviderPacket*> >	fPropertiesByScriptElementID ;
		mutable K2Vector<const PropertyProviderPacket *>								fPropertiesByFormattedName ;
} ;


//----------------------------------------------------------------------------
/**
	MethodParam represents a method parameter in a scripting DOM.
*/
class PUBLIC_DECL MethodParam : public BaseScriptInfo
{
	public:
		/** */
		MethodParam() : fOptional(kFalse) {}
		/** */
		MethodParam( const ScriptID& id, const PMString& name, const PMString& desc, const TypeInfo& type, bool16 optional ) :
			BaseScriptInfo( id, name, desc ), fType( type ), fOptional( optional ) {}

		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kMethodParameterElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
		/** Get the description in the context of the supplied object */
		PMString					GetFormattedDescription( const ObjectScriptElement* se ) const { return BaseScriptInfo::GetFormattedDescription( se ) ; }
		/** Get the type in the context of the supplied object */
		TypeInfo					GetParamType( const ObjectScriptElement* ) const ;
		/** Get whether the parameter is optional */
		bool16						IsOptional() const				{ return fOptional ; }
		/** Get the default value for the parameter */
		const ScriptData&			GetDefault() const				{ return fType.GetDefault() ; }

		/** */
		bool16						operator==( const MethodParam& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

		/** Set the parameter's type */
		void						SetParamType( const TypeInfo& type ) { fType = type ; }

	private:
		TypeInfo					fType ;
		bool16						fOptional ;
} ;

typedef K2Vector<MethodParam> MethodParamList ;
DEFINEK2READWRITE( MethodParam )

/**
	MethodScriptElement represents a method in a scripting DOM.
*/
class PUBLIC_DECL MethodScriptElement : public ScriptElement
{
	public:
		/** */
		MethodScriptElement() {}
		/** */
		MethodScriptElement( const ScriptElementID& siid, const ScriptID& id, const PMString& name, const PMString& desc, const TypeInfo& type, const PMString& returnDesc ) :
			ScriptElement( siid, id, name, desc ), fReturnType( type ), fReturnDescription( returnDesc ), fParameters() {}

		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kMethodElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
		/** Get the description in the context of the supplied object */
		PMString					GetFormattedDescription( const ObjectScriptElement* se ) const { return BaseScriptInfo::GetFormattedDescription( se ) ; }
		/** Get the type in the context of the supplied object */
		TypeInfo					GetReturnType( const ObjectScriptElement* ) const ;
		/** Get the description in the context of the supplied object */
		PMString					GetReturnDescription( const ObjectScriptElement* ) const ;
		/** Get the method's parameters using the supplied object's request context to validate parameter types */
		MethodParamList				GetParameters( const ObjectScriptElement* ) const ;
		/** Get the method's parameters */
		MethodParamList&			GetParameters()					{ return fParameters ; }
		/** Get the matching method parameter in the context of the supplied object */
		const MethodParam*			FindParameter( const ObjectScriptElement*, const ScriptID& id ) const ;

		/** */
		bool16						operator==( const MethodScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	private:
		TypeInfo					fReturnType ;
		PMString					fReturnDescription ;
		MethodParamList				fParameters ;
} ;


//----------------------------------------------------------------------------
/**
	PropertyScriptElement represents a property in a scripting DOM.
*/
class PUBLIC_DECL PropertyScriptElement : public ScriptElement
{
	public:
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kPropertyElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
		/** Get the description formatted in the context of the supplied object */
		PMString					GetFormattedDescription( const ObjectScriptElement* se ) const { return BaseScriptInfo::GetFormattedDescription( se ) ; }
		/** Get the type in the context of the supplied object */
		TypeInfo					GetStorageType( const ObjectScriptElement*, bool16 includeAssignableTypes = kFalse ) const ;
		/** Get any additional types that may be used to set the property */
		const TypeInfoList&			GetAssignableTypes() const		{ return fAssignableTypes ; }
		TypeInfoList&				GetAssignableTypes()			{ return fAssignableTypes ; }
		/** Get the associated text, graphic, or table attribute id */
		const ClassID&				GetAttributeID() const			{ return fAttributeID ; }

		/** */
		bool16						operator==( const PropertyScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	private:
		TypeInfo					fStorageType ;
		TypeInfoList				fAssignableTypes ;
		ClassID						fAttributeID ;
} ;


//----------------------------------------------------------------------------
/**
	EventScriptElement represents an attachable event in a scripting DOM.
*/
class PUBLIC_DECL EventScriptElement : public ScriptElement
{
	public:
		EventScriptElement() : ScriptElement(), fBubbles(kFalse), fCancelable(kFalse)
		{}
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kEventElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
		/** Get the description formatted in the context of the supplied object */
		PMString					GetFormattedDescription( const ObjectScriptElement* se ) const { return BaseScriptInfo::GetFormattedDescription( se ) ; }
		/** Get whether this event propagates up through the targets ancestors */
		bool16						GetBubbles() const { return fBubbles ; }
		/** Get whether the default action of this event may be suppressed by an event handler */
		bool16						GetCancelable() const { return fCancelable ; }
		/** */
		ClassID						GetEventClassID() const { return fEventClassID ; }
		/** */
		ScriptID					GetEventScriptID() const { return fEventScriptID ; }

		/** */
		bool16						operator==( const EventScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	private:
		bool16						fBubbles ;
		bool16						fCancelable ;
		ClassID						fEventClassID ;
		ScriptID					fEventScriptID ;
} ;


//----------------------------------------------------------------------------
/**
	EnumValue represents an enumerated value in a scripting DOM.
*/
class PUBLIC_DECL EnumValue : public BaseScriptInfo
{
	public:
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kEnumValueElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }
} ;

typedef K2Vector<EnumValue> EnumValueList ;
DEFINEK2READWRITE( EnumValue )

/**
	EnumScriptElement represents an enumeration in a scripting DOM.
*/
class PUBLIC_DECL EnumScriptElement : public ScriptElement
{
	public:
		/**
			Get the formatted name
			@param context the request context in which to format the name
			@param as which type of script element
		*/
		virtual const PMString&		GetFormattedName( const RequestContext& context, ScriptElementType as = kEnumElement ) const { return BaseScriptInfo::GetFormattedName( context, as ) ; }

		/** Get the enumerators */
		const EnumValueList&		GetValues() const					{ return fValues ; }
		/** Get the enumerators */
			  EnumValueList&		GetValues()							{ return fValues ; }

		/** */
		bool16						operator==( const EnumScriptElement& ) const ;
		/** Persist this object */
		virtual void				ReadWrite( IPMStream* s ) ;

	private:
		EnumValueList				fValues ;
} ;

//----------------------------------------------------------------------------
/**
	Controls how parents are iterated.
	@see ProviderPacketIterator
*/
class AccessParents
{
	public:
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const ParentProviderPacket* ) const { return kFalse ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const ParentProviderPacket* p1, const ParentProviderPacket* p2 )
			{ return p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ; }
		static bool16 SortByName( const ParentProviderPacket* p1, const ParentProviderPacket* p2 )
			{ return p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 ; }
} ;

/**
	Controls how children are iterated.
	@see ProviderPacketIterator
*/
class AccessChildren
{
	public:
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const ChildProviderPacket* ) const { return kFalse ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const ChildProviderPacket* p1, const ChildProviderPacket* p2 )
			{ return p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ; }
		static bool16 SortByName( const ChildProviderPacket* p1, const ChildProviderPacket* p2 )
			{ return p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 ; }
} ;

/**
	Controls how methods are iterated.
	@see ProviderPacketIterator
*/
class AccessMethods
{
	public:
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const MethodProviderPacket* ) const { return kFalse ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const MethodProviderPacket* p1, const MethodProviderPacket* p2 )
			{ return p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ; }
		static bool16 SortByName( const MethodProviderPacket* p1, const MethodProviderPacket* p2 )
			{ return p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 ; }
} ;

/**
	Controls how collection methods are iterated.
	@see ProviderPacketIterator
*/
class AccessCollectionMethods
{
	public:
		/**
			Constructor
			@param parent - skip all packets without this parent object
		*/
		AccessCollectionMethods( const ObjectScriptElement* parent ) : fParent( parent ) {} ;	//nil parent is OK
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const CollectionMethodProviderPacket* p ) const { return ( fParent && fParent != p->Parent() ) ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const CollectionMethodProviderPacket* p1, const CollectionMethodProviderPacket* p2 )
			{ return ( p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ) && ( p1->Parent() == p2->Parent() ) ; }
		static bool16 SortByName( const CollectionMethodProviderPacket* p1, const CollectionMethodProviderPacket* p2 )
			{
				int32 x = p1->Parent()->GetName().Compare( kFalse, p2->Parent()->GetName() ) ;
				if ( x < 0 )
					return kTrue ;
				if ( x == 0 && p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 )
					return kTrue ;
				return kFalse ;
			}

	private:
		const ObjectScriptElement* fParent ;
} ;

/**
	Controls how properties are iterated.
	@see ProviderPacketIterator
*/
class AccessProperties
{
	public:
		/**
			Constructor
			@param attributeID - skip all packets without this attribute id
		*/
		AccessProperties( const ClassID& attributeID = kInvalidClass ) : fAttrID( attributeID ) {} ;
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const PropertyProviderPacket* p ) const { return ( fAttrID != kInvalidClass && fAttrID != p->Element()->GetAttributeID() ) ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const PropertyProviderPacket* p1, const PropertyProviderPacket* p2 )
			{ return p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ; }
		static bool16 SortByName( const PropertyProviderPacket* p1, const PropertyProviderPacket* p2 )
			{ return p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 ; }
	private:
		ClassID fAttrID ;
} ;

/**
	Controls how events are iterated.
	@see ProviderPacketIterator
*/
class AccessEvents
{
	public:
		/** Returns kTrue if this packet should be skipped */
		bool16 SkipPacket( const EventProviderPacket* ) const { return kFalse ; }
		/** Returns kTrue if the packets are equivalent */
		static bool16 Matches( const EventProviderPacket* p1, const EventProviderPacket* p2 )
			{ return p1->Element()->GetScriptID() == p2->Element()->GetScriptID() ; }
		static bool16 SortByName( const EventProviderPacket* p1, const EventProviderPacket* p2 )
			{ return p1->Element()->GetName().Compare( kFalse, p2->Element()->GetName() ) < 0 ; }
	private:
		ClassID fAttrID ;
} ;

}	// End namespace ScriptInfo

#endif //__SCRIPTINFO__
