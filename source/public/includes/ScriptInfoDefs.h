//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptInfoDefs.h $
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
//========================================================================================

#pragma once
#ifndef __SCRIPTINFODEFS__
#define __SCRIPTINFODEFS__

#include "K2Vector.h"
#include "K2Pair.h"
#include "RequestContext.h"
#include "ScriptingID.h"

class IScriptProvider ;

namespace ScriptInfo
{

//----------------------------------------------------------------------------
//	Enum definitions
//----------------------------------------------------------------------------

/**
	Script element types
*/
enum ScriptElementType
{
	/** */
	kNoElement =				0x00,
	/** */
	kSuiteElement =				0x01,
	/** */
	kObjectElement =			0x02,
	/** */
	kMethodElement =			0x04,
	/** */
	kMethodParameterElement =	0x08,
	/** */
	kPropertyElement =			0x10,
	/** */
	kEnumElement =				0x20,
	/** */
	kEnumValueElement =			0x40,
	/** */
	kTypeDefElement =			0x80,
	/** */
	kEventElement =				0x100,
	/** Field in a struct type*/
	kStructField =				0x1000
} ;

/**
	Policies for returning errors when handling multiple requests at once
*/
enum ErrorPolicy
{
	/** Always return kSuccess */
	kIgnoreErrors,
	/** Return first error, or kSuccess if none */
	kReturnFirstError,
	/** Return kFailure if all requests fail; otherwise return kSuccess */
	kReturnCompleteFailureOnly
} ;

/**
	What to include when formatting the type as a string
*/
enum TypeFormattingInfo
{
	/** Just the basic type info */
	kIncludeTypeInfo = 0,
	/** Include the range data, if any */
	kIncludeRangeData = 1,
	/** Include the default value, if any */
	kIncludeDefaultValue = 2,
	/** The type is plural (used internally by CScriptManager and its subclasses) */
	kFormatAsPlural = 4,

	/** Output an enum type by name instead of as a list of enumerators */
	kGetEnumTypeByName = 0x10000000,
	/** Don't translate a KeyStringDefaultType */
	kDontTranslateKeyStringDefaultType = 0x20000000,
} ;

/**
	Policies for the order in which to set multiple properties
*/
enum SetPropertiesOrderPolicy
{
	/** Set properties in the order they appear in the object's definition */
	kDefaultOrder = 0,
	/** Set properties in the order they appear in the script request data */
	kCustomOrder = 1
} ;

//----------------------------------------------------------------------------
//	Class definitions
//----------------------------------------------------------------------------

/**
	Different clients have different expectations for how name identifiers are formatted.
	@see IScriptManager
*/
class PUBLIC_DECL FormatNamePolicy
{
	public:
		/** How to capitalize a formatted name */
		enum Capitalization
		{
			/** Don't change capitalization from the way it appears in the resource */
			kUseDefaultCapitalization,
			/** Make first character of each word upper case if it's not already */
			kUpperCaseFirstCharOfWords,
			/** Lower case every character except first character of words after the first one */
			kAllLowerCaseExceptInterCaps,
			/** All characters are upper case */
			kAllUpperCase
		} ;

		/** How to change the spacing when formatting a name */
		enum Spacing
		{
			/** Don't change spacing from the way it appears in the resource */
			kUseDefaultSpacing,
			/** Remove any spaces between words */
			kRemoveSpaces,
			/** Replace all spaces with an underscore */
			kReplaceSpacesWithUnderScore,
			/** Replace all spaces with a dash */
			kReplaceSpacesWithDash
		} ;

		/** */
		FormatNamePolicy() :
			fCapitalization( kUseDefaultCapitalization ), fSpacing( kUseDefaultSpacing ), fPrefix(), fSuffix() {}
		/** */
		FormatNamePolicy( Capitalization c, Spacing s, const PMString& prefix, const PMString& suffix ) :
			fCapitalization( c ), fSpacing( s ), fPrefix( prefix ), fSuffix( suffix ) {}

		/** Get the capitalization */
		Capitalization		GetCapitalization() const	{ return fCapitalization ; }
		/** Get the spacing */
		Spacing				GetSpacing() const			{ return fSpacing ; }
		/** Get the prefix */
		const PMString&		GetPrefix() const			{ return fPrefix ; }
		/** Get the suffix */
		const PMString&		GetSuffix() const			{ return fSuffix ; }

		/** */
		bool16				operator==( const FormatNamePolicy& other ) const { return ( fCapitalization == other.fCapitalization &&
																						fSpacing == other.fSpacing &&
																						fPrefix == other.fPrefix &&
																						fSuffix == other.fSuffix ) ; }

		/** Format a name according to this policy */
		void				FormatName( PMString& name ) const ;

private:
		Capitalization		fCapitalization ;
		Spacing				fSpacing ;
		PMString			fPrefix ;
		PMString			fSuffix ;
} ;

class TypeDefScriptElement ;
class SuiteScriptElement ;
class ObjectScriptElement ;
class MethodScriptElement ;
class PropertyScriptElement ;
class EnumScriptElement ;
class EventScriptElement ;

/** A list of ScriptIDs */
typedef K2Vector<ScriptID> ScriptIDList ;
/** A list of ScriptElementIDs */
typedef K2Vector<ScriptElementID> ScriptElementIDList ;
/** A list of ObjectScriptElements */
typedef K2Vector<const ObjectScriptElement*> ObjectScriptElementList ;
/** A list of MethodScriptElements */
typedef K2Vector<const MethodScriptElement*> MethodScriptElementList ;
/** A list of PropertyScriptElements */
typedef K2Vector<const PropertyScriptElement*> PropertyScriptElementList ;
/** A list of EventScriptElements */
typedef K2Vector<const EventScriptElement*> EventScriptElementList ;
	
/** A ID value for script methods that contains both the suite ID and the method ID */
typedef std::pair<uint32, uint32> ScriptMethodUniqueID;
/** A list of ScriptMethodUniqueID's */
typedef std::vector<ScriptMethodUniqueID> ScriptMethodUniqueIDList;
	
/**
	ScriptElementIterators are used to iterate through the various elements
	in a particular scripting document object model (DOM).
	@see IScriptInfoManager
*/
template <class SI>
class ScriptElementIterator
{
	public:
		/** */
		ScriptElementIterator( const SI* const* inBegin, const SI* const* inEnd ) : fCurrent( inBegin ), fEnd( inEnd ) {}
		/** */
		ScriptElementIterator( const ScriptElementIterator& sei ) : fCurrent( sei.fCurrent ), fEnd( sei.fEnd ) {}

		/** Advance to next element */
		ScriptElementIterator& operator++() { ++fCurrent ; return *this ;}

		/** Get current element */
		operator const SI*() const { return *fCurrent ; }
		/** Get current element */
		const SI* operator->() const { return *fCurrent ; }

		/** Get current element */
		const SI* const* current() const { return fCurrent ; }
		/** Get end of list */
		const SI* const* end() const { return fEnd ; }

	private:
		const SI* const*	fCurrent ;
		const SI* const*	fEnd ;

	private:
		//hide
		ScriptElementIterator operator++(int) ;	//{ ScriptElementIterator tmp(*this) ; ++(*this) ; return tmp ; }
		ScriptElementIterator& operator=( const ScriptElementIterator& ) ;
		bool16 operator==( const ScriptElementIterator& ) const ;
} ;

/** An iterator for typedef elements */
typedef ScriptElementIterator<TypeDefScriptElement>		TypeDefElementIterator ;
/** An iterator for suite elements */
typedef ScriptElementIterator<SuiteScriptElement>		SuiteElementIterator ;
/** An iterator for object elements */
typedef ScriptElementIterator<ObjectScriptElement>		ObjectElementIterator ;
/** An iterator for method elements */
typedef ScriptElementIterator<MethodScriptElement>		MethodElementIterator ;
/** An iterator for property elements */
typedef ScriptElementIterator<PropertyScriptElement>	PropertyElementIterator ;
/** An iterator for enum elements */
typedef ScriptElementIterator<EnumScriptElement>		EnumElementIterator ;
/** An iterator for enum elements */
typedef ScriptElementIterator<EventScriptElement>		EventElementIterator ;

/**
	The context for a scripting element determines whether or not it is available
	in any particular scripting document object model (DOM).
	@see RequestContext
*/
class PUBLIC_DECL ElementContext
{
	public:
		/** */
		ElementContext() : fLocale(), fFirstVersion( kMinimumScriptVersion ), fLastVersion( kMaximumScriptVersion ), fClient( kCoreScriptManagerBoss ) {}
		/** */
		ElementContext( const PMLocaleId& locale, const ScriptVersion& firstVersion, const ScriptVersion& lastVersion, const ScriptClient& client ) :
			fLocale( locale ), fFirstVersion( firstVersion ), fLastVersion( lastVersion ), fClient( client ) {}
		/** */
		ElementContext( const ElementContext& other ) { *this = other ; }
		/** */
		~ElementContext() {}

		/** Get product, feature set, and locale */
		const PMLocaleId&			GetLocale() const			{ return fLocale ; }
		/** Get the first scripting DOM version in which this element is available */
		const ScriptVersion&		GetFirstVersion() const		{ return fFirstVersion ; }
		/** Get the first scripting DOM version in which this element is no longer available */
		const ScriptVersion&		GetLastVersion() const		{ return fLastVersion ; }
		/** Get the client (kCoreScriptManagerBoss indicates "all clients") */
		const ScriptClient&			GetClient() const			{ return fClient ; }

		/** */
		ElementContext&				operator=( const ElementContext& ) ;
		/** */
		bool16						operator==( const ElementContext& other ) const { return ( fLocale == other.fLocale &&
																							fFirstVersion == other.fFirstVersion &&
																							fLastVersion == other.fLastVersion &&
																							fClient == other.fClient ) ; }
		/** Persist this object */
		void						ReadWrite( IPMStream* s ) ;

	private:
		PMLocaleId					fLocale ;		//defined in PMLocaleId.h
		ScriptVersion				fFirstVersion ;	//The first version for which this element applies (minimum is 0.0)
		ScriptVersion				fLastVersion ;	//The first version for which this element is obsolete (maximum is kMaxInt32.kMaxInt32 (0x7FFFFFFF))
		ScriptClient				fClient ;		//kCoreScriptManagerBoss indicates "always match"

#ifdef ID_ENABLE_DEBUGGING
	public:
		/** Get a string describing this object (debug-only) */
		ConstCString				WhoAmI() const ;
		mutable scoped_array<char>	fWhoAmI ;
#endif
} ;

/**
	ProviderPackets are used to associate elements on an object with 
	the script provider boss that handles a request for them.
	@see ProviderPacketIterator
*/
class PUBLIC_DECL ProviderPacket 
{
	public:
		typedef object_type data_type ;

		/** */
		ProviderPacket( const ElementContext& context, const ClassID& provider, const PluginID& pluginID, 
						bool16 surrogate, uint8 inheritance ) :
			fContext( context ), fProvider( provider ), fPluginID( pluginID ), fSurrogate( surrogate ), fInheritance( inheritance ) {}

		/** Get the context of this packet */
		const ElementContext&			GetContext() const			{ return fContext ; }
		/** Get the provider */
		const ClassID&					GetProvider() const			{ return fProvider ; }
		/** Get the PluginID in which this relationship was defined */
		const PluginID&					GetPluginID() const			{ return fPluginID ; }

		/** Query the provider */
		IScriptProvider*				QueryScriptProvider() const ;

		/** Set the PluginID in which this relationship was defined */
		void							SetPluginID( const PluginID& pluginID ) { fPluginID = pluginID ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this object (debug-only) */
		virtual ConstCString			WhoAmI() const = 0 ;
#endif

		/** Get whether this element is a surrogate */
		bool16							IsSurrogate() const		{ return fSurrogate ; }
		/** Get whether this element was added via inheritance */
		bool16							IsInherited() const		{ return fInheritance > 0 ; }
		/** Get the level of inheritance (1 = from parent class, 2 = from grandparent class, etc.) */
		uint8							GetInheritance() const	{ return fInheritance ; }

private:
		ElementContext					fContext ;
		ClassID							fProvider ;		//kInvalidClass for "don't match"
		PluginID						fPluginID ;
		bool16							fSurrogate ;	//A surrogate is not a formal parent/child relationship in the DOM hierarchy
		uint8							fInheritance ;
} ;

/** Information about handling an object's parent */
class PUBLIC_DECL ParentProviderPacket : public ProviderPacket
{
	public:
		/** */
		ParentProviderPacket( const ObjectScriptElement* parent, const ElementContext& context, const ClassID& provider, 
								const PluginID& pluginID, bool16 surrogate, uint8 inheritance ) :
			ProviderPacket( context, provider, pluginID, surrogate, inheritance ), fParent( parent ) {}

		/** Get the parent */
		const ObjectScriptElement*		Element() const				{ return fParent ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this object (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const ObjectScriptElement*		fParent ;
} ;

/** Information about handling an object's child */
class PUBLIC_DECL ChildProviderPacket : public ProviderPacket
{
	public:
		/** */
		ChildProviderPacket( const ObjectScriptElement* child, const ElementContext& context, const ClassID& provider, 
								const PluginID& pluginID, bool16 surrogate, uint8 inheritance ) :
			ProviderPacket( context, provider, pluginID, surrogate, inheritance ), fChild( child ) {}

		/** Get the child */
		const ObjectScriptElement*		Element() const				{ return fChild ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this object (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const ObjectScriptElement*		fChild ;
} ;

/** Information about handling an object's method */
class PUBLIC_DECL MethodProviderPacket : public ProviderPacket
{
	public:
		/** */
		MethodProviderPacket( const MethodScriptElement* method, const ElementContext& context, const ClassID& provider, 
								const PluginID& pluginID ) :
			ProviderPacket( context, provider, pluginID, kFalse, 0 ), fMethod( method ) {}

		/** Get the method */
		const MethodScriptElement*		Element() const				{ return fMethod ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this method (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const MethodScriptElement*		fMethod ;
} ;

/** Information about handling an object's collection method */
class PUBLIC_DECL CollectionMethodProviderPacket : public ProviderPacket
{
	public:
		/** */
		CollectionMethodProviderPacket( const MethodScriptElement* method, const ElementContext& context, const ClassID& provider, 
										const PluginID& pluginID, const ObjectScriptElement* parent, uint8 inheritance ) :
			ProviderPacket( context, provider, pluginID, kFalse, inheritance ), fMethod( method ), fParent( parent ) {}

		/** Get the collection method */
		const MethodScriptElement*		Element() const				{ return fMethod ; }
		/** Get the parent */
		const ObjectScriptElement*		Parent() const				{ return fParent ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this method (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const MethodScriptElement*		fMethod ;
		const ObjectScriptElement*		fParent ;
} ;

/** Information about handling an object's property */
class PUBLIC_DECL PropertyProviderPacket : public ProviderPacket
{
	public:
		/** */
		PropertyProviderPacket( const PropertyScriptElement* property, const ElementContext& context, const ClassID& provider, 
								const PluginID& pluginID, bool16 readonly ) :
			ProviderPacket( context, provider, pluginID, kFalse, 0 ), fProperty( property ), fReadOnly( readonly ) {}

		/** Get the property */
		const PropertyScriptElement*	Element() const				{ return fProperty ; }
		/** Returns kTrue if the property is read/write */
		bool16							IsReadWrite() const			{ return !fReadOnly ; }
		/** Returns kTrue if the property is read-only */
		bool16							IsReadOnly() const			{ return fReadOnly ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this property (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const PropertyScriptElement*	fProperty ;
		bool16							fReadOnly ;
} ;

/** Information about handling an object's property */
class PUBLIC_DECL EventProviderPacket : public ProviderPacket
{
	public:
		/** */
		EventProviderPacket( const EventScriptElement* event, const ElementContext& context, const ClassID& provider, 
								const PluginID& pluginID ) :
			ProviderPacket( context, provider, pluginID, kFalse, 0 ), fEvent( event ) {}

		/** Get the event */
		const EventScriptElement*		Element() const				{ return fEvent ; }

#ifdef ID_ENABLE_DEBUGGING
		/** Get a string describing this event (debug-only) */
		virtual ConstCString			WhoAmI() const ;
#endif

	private:
		const EventScriptElement*		fEvent ;
} ;

/** A list of parent information */
typedef K2Vector<ParentProviderPacket>		ParentProviderLookup ;
/** A list of child information */
typedef K2Vector<ChildProviderPacket>		ChildProviderLookup ;
/** A list of method information */
typedef K2Vector<MethodProviderPacket>		MethodProviderLookup ;
/** A list of collection method information */
typedef K2Vector<CollectionMethodProviderPacket>	CollectionMethodProviderLookup ;
/** A list of property information */
typedef K2Vector<PropertyProviderPacket>	PropertyProviderLookup ;
/** A list of event information */
typedef K2Vector<EventProviderPacket>		EventProviderLookup ;

class AccessParents ;
class AccessChildren ;
class AccessMethods ;
class AccessCollectionMethods ;
class AccessProperties ;
class AccessEvents ;

/**
	ProviderPacketIterators are used to iterate through the various elements
	associated with an object element in the scripting document object model (DOM).
	@see ObjectScriptElement
*/
template <class SI, class PP, class Access>
class ProviderPacketIterator
{
	public:
		typedef PP packet_type ;
		typedef Access access_type ;

		/** */
		ProviderPacketIterator( const SI* pSI, bool16 iterateBaseObjects, Access filter = Access() ) :
			fSI( pSI ),
			fIterateBaseObjects( iterateBaseObjects ),
			fCurrent( nil ),
			fEnd( nil ),
			fAlreadySeen(),
			fFilter( filter )
			{
				Initialize() ;
			}
		/** */
		ProviderPacketIterator( const ProviderPacketIterator& ppi ) ;/*:
			fSI( ppi.fSI ),
			fIterateBaseObjects( ppi.fIterateBaseObjects ),
			fCurrent( ppi.fCurrent ),
			fEnd( ppi.fEnd ),
			fAlreadySeen( ppi.fAlreadySeen ),
			fFilter( ppi.fFilter )
			{}*/

		/** Advance to the next packet */
		ProviderPacketIterator& operator++(){ ++fCurrent ; IterateUntilValid() ; return *this ;}

		/** Get the current packet */
		operator const PP*() const { return fCurrent ; }
		/** Get the current packet */
		const PP* operator->() const { return fCurrent ; }

		/** Get the current packet */
		const PP* current() const { return fCurrent ; }
		/** Get end of list */
		const PP* end() const { return fEnd ; }

	private:
		/** Initialize the iterator to the first valid packet */
		void Initialize()
		{
			if ( fSI )
			{
				fCurrent = fSI->GetElements( (Access*) nil ).begin() ;
				fEnd = fSI->GetElements( (Access*) nil ).end() ;
				IterateUntilValid() ;
			}
		}

		/** Advance the iterator to the next valid packet */
		void IterateUntilValid()
		{
			//Apply filter and skip duplicate elements
			while ( fCurrent != fEnd && SkipPacket() )
				++fCurrent ;

			//Cache elements we've seen
			if ( fCurrent != fEnd )
				fAlreadySeen.push_back( fCurrent ) ;

			//Skip elements that are not supported (no provider)
			if ( fCurrent != fEnd && fCurrent->GetProvider() == kInvalidClass )
			{
				++fCurrent ;
				IterateUntilValid() ;
			}

			//Iterate the elements on the base object, if any
			if ( fIterateBaseObjects && fCurrent == fEnd )
			{
				if ( fSI != nil )
					fSI = fSI->FindBaseObject() ;

				Initialize() ;
			}
		}

		/** Returns kTrue if the current packet should be skipped */
		bool16 SkipPacket() const
		{
			if ( fFilter.SkipPacket( fCurrent ) )
				return kTrue ;

			for ( const PP* const* iter = fAlreadySeen.begin() ; iter != fAlreadySeen.end() ; ++iter )
			{
				if ( fFilter.Matches( *iter, fCurrent ) )
					return kTrue ;
			}
			return kFalse ;
		}

	private:
		const SI*			fSI ;
		bool16				fIterateBaseObjects ;
		const PP*			fCurrent ;
		const PP*			fEnd ;
		K2Vector<const PP*>	fAlreadySeen ;
		Access				fFilter ;

	private:
		//hide
		ProviderPacketIterator operator++(int) ;	//{ ProviderPacketIterator tmp(*this) ; ++(*this) ; return tmp ; }
		ProviderPacketIterator& operator=( const ProviderPacketIterator& ) ;
		bool16 operator==( const ProviderPacketIterator& ) const ;
} ;

/** An iterator for parents */
typedef ProviderPacketIterator<ObjectScriptElement, ParentProviderPacket,		AccessParents>		ParentProviderIterator ;
/** An iterator for children */
typedef ProviderPacketIterator<ObjectScriptElement, ChildProviderPacket,		AccessChildren>		ChildProviderIterator ;
/** An iterator for methods */
typedef ProviderPacketIterator<ObjectScriptElement, MethodProviderPacket,		AccessMethods>		MethodProviderIterator ;
/** An iterator for collection methods */
typedef ProviderPacketIterator<ObjectScriptElement, CollectionMethodProviderPacket,	AccessCollectionMethods>	CollectionMethodProviderIterator ;
/** An iterator for properties */
typedef ProviderPacketIterator<ObjectScriptElement, PropertyProviderPacket,		AccessProperties>	PropertyProviderIterator ;
/** An iterator for events */
typedef ProviderPacketIterator<ObjectScriptElement, EventProviderPacket,		AccessEvents>		EventProviderIterator ;
//Note: ObjectScriptElement has to be specified as a template class argument because it hasn't been defined yet

/** Used for sorting children of an object */
typedef bool16 (*PacketComp)(const ChildProviderPacket left, const ChildProviderPacket right);

}	// End namespace ScriptInfo

#endif //__SCRIPTINFODEFS__
