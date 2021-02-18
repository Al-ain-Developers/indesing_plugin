//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RequestContext.h $
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
#ifndef __REQUESTCONTEXT__
#define __REQUESTCONTEXT__

#include "FormatID.h"
#include "K2SmartPtr.h"
#include "k2VectorStreaming.h"
#include "PMLocaleId.h"	//see also FeatureSets.h and PMLocaleIds.h

class IScriptEngine ;
class IScriptManager ;

namespace ScriptInfo
{

/** A scripting client */
typedef ClassID ScriptClient ;
/**
	A scripting DOM version. To access the current scripting DOM version 
	(i.e., kMajorScriptVersionNumber, kMinorScriptVersionNumber), use
	Utils<IScriptUtils>()->GetCurrentScriptDOMVersion().
*/
typedef FormatID ScriptVersion ;
/** A list of scripting DOM versions */
typedef K2Vector<ScriptVersion> ScriptVersionList ;
/** The minimum scripting DOM version: 0,0 */
extern PUBLIC_DECL const ScriptVersion kMinimumScriptVersion ;
/** The maximum scripting DOM version: kMaxInt32, kMaxInt32 */
extern PUBLIC_DECL const ScriptVersion kMaximumScriptVersion ;
/** The CS scripting DOM version: kDragontailMajorScriptVersionNumber, kDragontailMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS1ScriptVersion ;
/** The CS2 scripting DOM version: kFiredrakeMajorScriptVersionNumber, kFiredrakeMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS2ScriptVersion ;
/** The CS3 scripting DOM version: kCobaltMajorScriptVersionNumber, kCobaltMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS3ScriptVersion ;
/** The CS4 scripting DOM version: kBasilMajorScriptVersionNumber, kBasilMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS4ScriptVersion ;
/** The CS5 scripting DOM version: kRocketMajorScriptVersionNumber, kRocketMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS5ScriptVersion ;
/** The CS5.5 scripting DOM version: kOdinMajorScriptVersionNumber, kOdinMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS5_5ScriptVersion ;
/** The CS6 scripting DOM version: kAthosMajorScriptVersionNumber, kAthosMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCS6ScriptVersion ;
/** The CC scripting DOM version: kCitiusMajorScriptVersionNumber, kCitiusMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCCScriptVersion ;
/** The CC 2014 (10.0) scripting DOM version: kSiriusMajorScriptVersionNumber, kSiriusMinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC10ScriptVersion ;
/** The CC 2014.1 (10.1) scripting DOM version: kSiriusR3MajorScriptVersionNumber, kSiriusR3MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC10_1ScriptVersion ;
/** The CC 2014.2 (10.2) scripting DOM version: kSiriusR4MajorScriptVersionNumber, kSiriusR4MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC10_2ScriptVersion ;
/** The CC (11.0) scripting DOM version: kR5MajorScriptVersionNumber, kR5MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC11ScriptVersion ;
/** The CC (11.2) scripting DOM version: kR7MajorScriptVersionNumber, kR7MinorScriptVersionNumber - no scripting changes in R6 */
extern PUBLIC_DECL const ScriptVersion kCC11_2ScriptVersion;
/** The CC (11.3) scripting DOM version: kR8MajorScriptVersionNumber, kR8MinorScriptVersionNumber*/
extern PUBLIC_DECL const ScriptVersion kCC11_3ScriptVersion;
/** The CC (11.4) scripting DOM version: kR9MajorScriptVersionNumber, kR9MinorScriptVersionNumber*/
extern PUBLIC_DECL const ScriptVersion kCC11_4ScriptVersion;
/** The CC (12.0) scripting DOM version: kR10MajorScriptVersionNumber, kR10MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC12ScriptVersion;
/** The CC (12.1) scripting DOM version: kR11MajorScriptVersionNumber, kR11MinorScriptVersionNumber*/
extern PUBLIC_DECL const ScriptVersion kCC12_1ScriptVersion;
/** The CC (13.0) scripting DOM version: kR12MajorScriptVersionNumber, kR12MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC13ScriptVersion;
/** The CC (13.1) scripting DOM version: kR13MajorScriptVersionNumber, kR13MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC13_1ScriptVersion;
/** The CC (14.0) scripting DOM version: kCC14MajorScriptVersionNumber, kCC14MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC14ScriptVersion;
/** The CC (15.0) scripting DOM version: kCC15MajorScriptVersionNumber, kCC15MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC15ScriptVersion;
/** The CC (15.1) scripting DOM version: kCC15_1MajorScriptVersionNumber, kCC15_1MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC15_1ScriptVersion;
/** The CC (16.0) scripting DOM version: kCC16MajorScriptVersionNumber, kCC16MinorScriptVersionNumber */
extern PUBLIC_DECL const ScriptVersion kCC16ScriptVersion;

#ifdef ID_DEPRECATED	//deprecated in CS5; remove in CS6
#define kDragontailScriptVersion	kCS1ScriptVersion
#define kFiredrakeScriptVersion		kCS2ScriptVersion
#define kCobaltScriptVersion		kCS3ScriptVersion
#define kBasilScriptVersion			kCS4ScriptVersion
#endif

//CONVERSION UTILITIES

/**	Convert a version number to a string */
extern PUBLIC_DECL PMString ToString( const ScriptVersion& version ) ;
/**	Convert a string to a version number */
extern PUBLIC_DECL ScriptVersion ToVersion( PMString s, PMString::ConversionError* pError = nil ) ;
/**	Convert a version number to a real */
extern PUBLIC_DECL PMReal ToReal( const ScriptVersion& version ) ;
/**	Convert a real to a version number */
extern PUBLIC_DECL ScriptVersion ToVersion( PMReal r ) ;


/**
	The context for a scripting DOM (document object model)
*/
class PUBLIC_DECL RequestContext
{
	public:
		typedef object_type data_type ;

		RequestContext() {}
		RequestContext( const IScriptManager* client, const ScriptVersion& version, const PMLocaleId& locale ) ;
		RequestContext( const RequestContext& other ) { *this = other ; }
		~RequestContext() {}

		/** Get product, feature set, and locale */
		const PMLocaleId&			GetLocale() const			{ return fLocale ; }
		/** Get the scripting DOM version */
		const ScriptVersion&		GetVersion() const			{ return fVersion ; }
		/** Get the client */
		const ScriptClient&			GetClient() const			{ return fClient ; }

		/** Query the script manager for the client */
		IScriptManager*				QueryScriptManager() const ;

		/** */
		RequestContext&					operator=( const RequestContext& ) ;
		/** */
		bool16						operator==( const RequestContext& other ) const { return ( fLocale == other.fLocale && fVersion == other.fVersion && fClient == other.fClient ) ; }
		/** */
		bool16						operator!=( const RequestContext& other ) const { return ( fLocale != other.fLocale || fVersion != other.fVersion || fClient != other.fClient ) ; }

		/** Persist this object */
		void						ReadWrite( IPMStream* s ) ;

	private:
		PMLocaleId					fLocale ;		//defined in PMLocaleId.h
		ScriptVersion				fVersion ;		//min version is 0.0; max version is kMaxInt32.kMaxInt32 (0x7FFFFFFF)
		ScriptClient				fClient ;		//ClassID of the client's script manager boss

#ifdef ID_ENABLE_DEBUGGING
	public:
		/** Get a string describing this object (debug-only) */
		ConstCString				WhoAmI() const ;
		mutable scoped_array<char>	fWhoAmI ;
#endif
} ;

/** A list of DOM contexts */
typedef K2Vector<RequestContext> RequestContextList ;
DEFINEK2READWRITE( RequestContext )

/**
	The context for a scripting request determines the content of the scripting 
	document object model (DOM) that is used to process the request. It also 
	determines how a request is handled based on preferences in the client's 
	implementation of IScriptManager and IScriptPreferences.
*/
class PUBLIC_DECL EngineContext : public RequestContext
{
	public:
		typedef object_type data_type ;

		EngineContext() : fEngine( nil ) {}
		EngineContext( const IScriptManager* client, const ScriptVersion& version, const PMLocaleId& locale, const IScriptEngine* engine = nil ) ;
		EngineContext( const EngineContext& other ) : fEngine( nil ) { *this = other ; }
		~EngineContext() ;

		/** Query the script engine for this context. If none is set, returns the script manager's default engine. */
		IScriptEngine*				QueryScriptEngine() const ;

		/** */
		EngineContext&				operator=( const EngineContext& ) ;
		/** */
		bool16						operator==( const EngineContext& other ) const ;
		/** */
		bool16						operator!=( const EngineContext& other ) const ;

	private:
		const IScriptEngine*		fEngine ;

#ifdef ID_ENABLE_DEBUGGING
	public:
		/** Get a string describing this object (debug-only) */
		ConstCString				WhoAmI() const ;
#endif
} ;

}	// End namespace ScriptInfo

#endif //__REQUESTCONTEXT__
