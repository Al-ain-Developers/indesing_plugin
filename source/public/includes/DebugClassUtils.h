//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DebugClassUtils.h $
//  
//  Owner: lance bushore
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
//  Provides some debug-only utilities to get a prefix name from an id.
//  
//  Third party prefixes are in DeveloperPrefix.h
//  
//========================================================================================

#pragma once
#ifndef _DebugClassUtils_H
#define _DebugClassUtils_H

#ifdef ID_ENABLE_DEBUGGING

#include "OMTypes.h"
#include "ShuksanID.h"

enum kDebugClassUtilsBufferSizeEnum {kDebugClassUtilsBufferSize = 512} ;
typedef char DebugClassUtilsBuffer[kDebugClassUtilsBufferSize];

class ModelThreadLocal_DebugClassUtilsBuffer
	{
	public:
		DebugClassUtilsBuffer* Get()
		{
			return &fThreadLocalBuffer.Get()->fBuffer;
		}
	private:
		struct DebugClassUtilsBufferWrapper
		{
			DebugClassUtilsBuffer fBuffer;
		};
		
		IDThreading::ThreadLocalManagedObject<DebugClassUtilsBufferWrapper> fThreadLocalBuffer;
	};

#pragma export on
/** This file contains a bunch of utilites to get symbolic names for various types of IDs. There's really just one function most developers are
	likely to use: GetIDName() The most typical usage for this is to dump out a nicely formatted assert or TRACE for debugging. Here's a usage example:

<pre>	
#ifdef DEBUG
	DebugClassUtilsBuffer classBuf,widgetBuf;
	ASSERT_FAIL(FORMAT_ARGS("Widget %s of boss %s is my very favorite",
							DebugClassUtils::GetIDName(&widgetBuf,myControlView->GetWidgetID()),
							DebugClassUtils::GetIDName(&classBuf,::GetClass(myControlView))));
#endif
</pre>	
	
*/

	class PUBLIC_DECL DebugClassUtils
	{
	public:

	/** Gets the name associated with this PluginID. For example, if you pass in an ID of 0x0301, this will return the string "Layers.RPLN".
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the PluginID you want a prefix name for
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char*	GetPluginName( DebugClassUtilsBuffer *pName, PluginID id );
	
	/** Gets the name associated with this ID range in the prefix file. For example, if you pass in an ID between 0x0300 and 0x03FF, this will return the
		string "LayerPrefix".
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a prefix name for. This could be a ClassID, WidgetID, InterfaceID, ImplementationID, ActionID, etc.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char*	GetPluginName( DebugClassUtilsBuffer *pName, int32 id );
		
		
	/** Gets the prefix part of this ID. For example, if you pass in an ID between 0x0300 and 0x03FF, this will return 0x0300.
		
		@param id the id you want a prefix for. This could be a ClassID, WidgetID, InterfaceID, ImplementationID, ActionID, etc.
		@return the prefix, masking off the offset.
	*/
		static int32 		GetPrefix(int32 id);

	/** Gets the offset part of this ID. For example, if you pass in an ID of 0x0309, this will return 9.
		
		@param id the id you want an offset for. This could be a ClassID, WidgetID, InterfaceID, ImplementationID, ActionID, etc.
		@return the offset within the prefix
	*/
		static int32		GetOffset(int32 id);
		
		
	/** This function will tell you whether or not this prefix is reserved by any plugin in your copy of the reserved prefix files.
		Mostly useful for internal development, since after we ship, new developer prefixes could be added which would not be part of the
		files in the SDK.
		
		@param prefix the prefix you would like to know about. Note that you have to pass just the prefix, not any id in the range, so you'll 
		likely want to call GetPrefix first.
		@return boolean indicating whether or not this prefix is reserved.

	*/
		static bool16 IsPrefixReserved(int32 prefix);
		
		
	/** Gets the name associated with this ID space. For example, if you pass in kClassIDSpace, this will return the string "ClassID".
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param idspace the idspace you want a name for. This could be a kClassIDSpace, kWidgetIDSpace, etc.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *	GetIDSpaceName( DebugClassUtilsBuffer *pName, int32 idspace );
			
	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. This could be a ClassID, WidgetID, ActionID, etc.
		@param idspace the idspace associated with the id you're asking about. This could be kClassIDSpace, kWidgetIDSpace, etc.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *	GetIDName( DebugClassUtilsBuffer *pName, int32 id, int32 idspace = kClassIDSpace, bool16 appendGetIDString = kFalse );
		
	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, ClassID id, bool16 appendGetIDString = kFalse ) ;
	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, PMIID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, ImplementationID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, WidgetID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, ActionID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, ServiceID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, PluginID id, bool16 appendGetIDString = kFalse );

	/** Gets the name associated with this ID. For example, if you pass in the constant kIconSuiteButtonWidgetBoss, this will return the string "kIconSuiteButtonWidgetBoss".
		If we don't have a symbolic name for the ID you requested, this function will still return a nicely formatted string, like  "kWidgetPrefix + 1 (601)". The way we get the nice 
		symbolic constants in thru use of the xxxID.cpp files. If your plugin's id's aren't showing up with nice symbolic names, make sure that you have an xxxID.cpp file in your
		project and that it's got the correct stuff in it. 
		
		@param pName specifies a buffer we can stuff the name into. This pointer is also returned from this function, for more convienient use.
		@param id the id you want a name for. There a versions of this function that take a ClassID, PMIID, ImplementationID, WidgetID, ActionID, ServiceID, PluginID, and ScriptElementID. 
				This means that you can just call GetIDName and pass your id and we'll figure out what ID space it's in to give back the correct string.
		@param appendGetIDString a boolean indicating if you'd like us to give back an extra long string like "kButtonWidgetBoss (kWidgetPrefix + 7 (607))" i.e. passing kTrue will
				make us append the id string even if we have a symbolic name.
		@return a pointer to the buffer you passed in, populated with the name you asked for
	*/
		static const char *GetIDName( DebugClassUtilsBuffer *pName, ScriptElementID id, bool16 appendGetIDString = kFalse );

	/** This function asserts if we don't have a symbolic name for this id in this idspace. 
		
		@param idspace the idspace you want to validate there's a symbolic constant for.
		@param id the id you want to validate there's a symbolic constant for.
	*/
		static void ValidateOMId(int32 idSpace, int32 id);
		
	/** In theory this function asserts if we don't have a symbolic name for all the ids registered with the object model. In practice it doesn't do anything
		because there are too many issues with this.
	*/
		static void ValidateAllClassIds();
	
	private:
	/** this will be removed soon, as we begin to enforce the usage of GetIDName. This builds a string like 'kShuksanPrefix + 41 (129)'
	*/
		static const char*	GetIDString( DebugClassUtilsBuffer *pName, int32 id);
	};

#pragma export off
#endif


#endif /* _DebugClassUtils_H */