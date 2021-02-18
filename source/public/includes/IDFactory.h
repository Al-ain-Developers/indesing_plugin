//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDFactory.h $
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

#ifndef __IDFactory_h__
#define __IDFactory_h__

// ---------------------------------------------------------------------------------------
// ----- Object model ids are registered in the debug build, but by default are not 
//		 registered in the release build. Localization can change the #undef to a
//		 #define in the non-debug case below to get ids registered in the release
//		 build. [amb]
//
#ifdef DEBUG
#define REGISTER_OM_IDS
#else
#undef REGISTER_OM_IDS
#endif
//
// ---------------------------------------------------------------------------------------

//#define ORIGINAL_ENUM_DECLARE_PMID
//#define NAMED_ENUM_DECLARE_PMID
#define CONST_INT_DECLARE_PMID

#ifdef REGISTER_OM_IDS

#ifdef ORIGINAL_ENUM_DECLARE_PMID
	#define DECLARE_PMID(space, name, id) enum { name = id };
#else
	#ifdef __ODFRC__
		#define DECLARE_PMID(space, name, id) enum { name = id };
	#elif defined CONST_INT_DECLARE_PMID
		#define DECLARE_PMID(space, name, id) constexpr uint32 name = id;
	#elif defined NAMED_ENUM_DECLARE_PMID
		#define DECLARE_PMID(space, name, id) enum space##name {name = id};
	#endif
#endif

#define START_IDS()
#define END_IDS()


#ifndef __ODFRC__


/** This is similar to an InterfaceFactory, but relates an ID to a name. This is
	used for debugging purposes, and works only in the Debug build. You should
	not need to access IDFactory directly, just declare your IDs with DECLARE_PMIID.
*/
class IDFactory
{
public:
	/** Construct a new IDFactory, relating a given ID to a C++ string.
		@param space	The ID space for the ID (e.g., kClassIDSpace, kImplemetationIDSpace, etc.)
		@param name		The C++ name of the ID
		@param id		The prefix + n of the ID, where n MUST NOT be greater than 255! or you'll overflow your prefix
	*/
    IDFactory(const int32& space, const char* name, const int32& id);
	
	/** For internal use only */
	static void InstallIDs(PluginID ownerComponent);

private:
	IDFactory*			fNextID;
	const char*			fName;
	int32				fSpace;
	int32				fId;
	
	static IDFactory*	fgFirstID;
};

#endif

#else  // REGISTER_OM_IDS

/** Use DECLARE_PMIID to declare the IDs used by your plug-in
		@param space	The ID space for the ID (e.g., kClassIDSpace, kImplemetationIDSpace, etc.)
		@param name		The C++ name of the ID
		@param id		The prefix + n of the ID, where n MUST NOT be greater than 255! or you'll overflow your prefix
*/
#ifdef ORIGINAL_ENUM_DECLARE_PMID
	#define DECLARE_PMID(space, name, id) enum { name = id };
#else
	#ifdef __ODFRC__
		#define DECLARE_PMID(space, name, id) enum { name = id };
	#elif defined CONST_INT_DECLARE_PMID
		#define DECLARE_PMID(space, name, id) constexpr uint32 name = id;
	#elif defined NAMED_ENUM_DECLARE_PMID
		#define DECLARE_PMID(space, name, id) enum space##name {name = id};
	#endif
#endif

/** These macros are used in ODFRC declarations of ID names. You put START_IDS before the 
	first DECLARE_PMID, and END_IDS after the last one, and then you can declare 
	your plug-ins IDs in the ODFRC way. This is better because the IDs will get 
	loaded on application startup, instead of the first time the plug-in is loaded.
*/
#define START_IDS()
#define END_IDS()

#endif // REGISTER_OM_IDS

#endif // __IDFactory_h__
