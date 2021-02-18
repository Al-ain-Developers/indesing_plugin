//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSManager.h $
//  
//  Owner: fhaberma
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

#ifndef __ICMSMANAGER__
#define __ICMSMANAGER__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ICMSProfile.h"

#include "ColorMgmtID.h"
#include "BravoForwardDecl.h"

class PMString;
class IDocument;
class CMSAvailableProfileList;

const int32 kCMSMgrHonorProfileSpace = (1L<<0);
const int32 kCMSMgrHonorProfileClass = (1L<<1);
const int32 kCMSMgrHonorProfileCategory = (1L<<2);

const int32 kCMSMgrIncludeStandard	= (1L << 0L);
const int32 kCMSMgrIncludeOther		= (1L << 1L);
const int32 kCMSMgrIncludeInternal	= (1L << 2L);
const int32 kCMSMgrIncludeAll		= (kCMSMgrIncludeStandard | kCMSMgrIncludeOther | kCMSMgrIncludeInternal);

class CMSMgrProfileFilter {
public:
	// Note: this may expand in the future to allow additional criteria.
	// Do NOT store this class in a persistent manner!

	CMSMgrProfileFilter():
			fHonorFlags(0),
			fIncludeFlags(kCMSMgrIncludeAll),
			fProfileSpace(ICMSProfile::kSpaceUnknown),
			fProfileClass(ICMSProfile::kClassUnknown),
			fProfileCategory(ICMSProfile::kOther) {};

	CMSMgrProfileFilter(ICMSProfile::profileSpace theSpace):
			fHonorFlags(kCMSMgrHonorProfileSpace), 
			fIncludeFlags(kCMSMgrIncludeAll),
			fProfileSpace(theSpace),
			fProfileClass(ICMSProfile::kClassUnknown),
			fProfileCategory(ICMSProfile::kOther) {};

	CMSMgrProfileFilter(ICMSProfile::profileClass theClass):
			fHonorFlags(kCMSMgrHonorProfileClass), 
			fIncludeFlags(kCMSMgrIncludeAll),
			fProfileSpace(ICMSProfile::kSpaceUnknown),
			fProfileClass(theClass),
			fProfileCategory(ICMSProfile::kOther) {};

	CMSMgrProfileFilter(ICMSProfile::profileSpace theSpace, ICMSProfile::profileClass theClass):
			fHonorFlags(kCMSMgrHonorProfileSpace | kCMSMgrHonorProfileClass),
			fIncludeFlags(kCMSMgrIncludeAll),
			fProfileSpace(theSpace),
			fProfileClass(theClass),
			fProfileCategory(ICMSProfile::kOther) {};

	CMSMgrProfileFilter(ICMSProfile::profileCategory theCategory):
			fHonorFlags(kCMSMgrHonorProfileCategory), 
			fIncludeFlags(kCMSMgrIncludeAll),
			fProfileSpace(ICMSProfile::kSpaceUnknown),
			fProfileClass(ICMSProfile::kClassUnknown),
			fProfileCategory(theCategory) {};
	
	int operator== (const CMSMgrProfileFilter& x) {
			return (fHonorFlags == x.fHonorFlags
				&& (!(fHonorFlags & kCMSMgrHonorProfileSpace) || fProfileSpace == x.fProfileSpace)
				&& (!(fHonorFlags & kCMSMgrHonorProfileClass) || fProfileClass == x.fProfileClass)
				&& (!(fHonorFlags & kCMSMgrHonorProfileCategory) || fProfileCategory == x.fProfileCategory)
				&& fIncludeFlags == x.fIncludeFlags
			); 
		};
	int operator!= (const CMSMgrProfileFilter& x) { return !operator==(x); };
	
	int32 fHonorFlags;	// Collection of CMSMgrHonor* flags.  Be explicit; don't use 0xFFFFFFFF, for example.
	int32 fIncludeFlags;// Collection of CMSMgrInclude* glags.  Be explicit; don't use 0xFFFFFFFF, for example.
	ICMSProfile::profileSpace	fProfileSpace;
	ICMSProfile::profileClass	fProfileClass;
	ICMSProfile::profileCategory	fProfileCategory;
};

//========================================================================================
// Description:
//	ICMSManager is meant to provide a generic wrapper around a CMS system. Access to the CMS is typically done
//	by coordinating between this interface and a specific data interface for the specific CMS implementation. For
//	example, Rainbow Bridge is a CMS, and implements ICMSManager with RBCMSManager, and coordinates with
//	an IRBSpecificData interface on the same CMS boss. 
//
//	The following routines are broken up into four categories:
//		¥ CMS Manager startup/shutdown methods
//		¥ CMM manipulation
//		¥ Available profile methods. 
//				Available profiles are ones that are available from the system or a CMM.
//		¥ Used profile methods
//				Used profiles are meant to connote profiles that are used in a document by some object.
//
//	Coordinating with CMS data interface
//		Some routines below need coordinating with a data interface as mentioned above. For example, the routine
//		GenerateAvailableProfiles() needs to be called before getting or querying for the Nth profile or profile name.
//		Similarly, the concept of a "used" profile needs to be tracked by the CMS manager. This means that querying
//		and releasing needs to be done through this interface. When an object is assigned a profile, you should call
//		"UseProfile()" so that the CMS manager can clean up properly.
//
//	Simple example
//	Here are some basic steps that most apps will want to do:
//		- See if CMS is installed in the OS by calling IsAvailable()
//		- Call Startup to get the machine going
//		- Make a popup of available CMMs with consecutive calls to GetNthCMMName() and turn on the user choice
//			with UseNthCMM().
//		- Create popups for profile choices:
//				o Call GenerateAvailableProfiles() to generate a list of those types of profiles available
//				o Fill a popup of available profiles with consecutive calls to GetNthAvailableProfileName()
//		- When the user chooses from the popup, call UseProfile with the name of the profile. The CMS manager will create this profile (if
//			it doesn't already exist) and assign it to the element. You can also categorize it as one of the 5 std profiles (rgb source, cmyk source, etc) 
//		- If the user stops using the profile (e.g. deletes the last item using it, never used it, or changes to a different selection),
//			just release it, and the CMS Manager will remove it from the document.
//		- Call Shutdown() when all is said and done
//
//	Other notes
//		- The profileCategory is a helper enum which allows you to find the K2 standard profiles by id (see ICMSProfile.h)
//		- Use the GetNthAvailableProfileName() and GetNthAvailableProfileFile() routines for filling in popups, as
//			they don't actually create any objects (in the default implementation). 
//		- You should use the CMSUtils class instead of calls to this (for things like UseProfile), as they go through commands. 
//		- If you need to connect to AGM, the GetAGMProfileMethods will return you the correct structure to set up CMS.
//========================================================================================
class ICMSManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSMANAGER };
	
		enum CMSStatus {
					// Anything in this range means it is shut down.
					kCMSStatusShutDown = 0,
					
					// Anything in this range means it couldn't start up.
					kCMSStatusInitializationErrorBase = 100,
					kCMSStatusFailedToInitializeEngine,
					kCMSStatusFailedToInitializeCMMs,
					kCMSStatusFailedToInitializeProfiles,
					
					// Anything in this range means it's starting up.
					kCMSStatusInitializingBase = 200,
					kCMSStatusInitializedEngine,
					kCMSStatusInitializedCMMs,
					kCMSStatusInitializedProfiles,
					
					// Anything >= this value means it's running.  Might
					// later add status for ongoing operations.
					kCMSStatusRunning = 300
				};
		
		enum CMSPolicy
		{
			kCMSPolicyOff		= 'off ',
			kCMSPolicyPreserve	= 'pres',
			kCMSPolicyConvert	= 'conv',
			kCMSPolicyPDIL		= 'pdil', 	// Note: this is manufactured by a combination of preserve and safe-cmyk
											// (it does not occur as such in a CSF; it's inferred)
			kCMSPolicyUndefined = 'undf',	// This indicates a legacy document with no policy set up.
											// It doesn't occur in CSFs but occurs in legacy documents
			kCMSPolicyMaxEnum	= 0xFFFFFFFFL	// Force enum to be 32-bits wide.
		};
		
		// Basic status calls
		// ----------------------------------------------
			// Start/stop the cms manager.  Should be done only
			// at app init/deinit.
			virtual void 			Startup() = 0;
			virtual void 			Shutdown() = 0;

			// called when the application resumes
			virtual void 			AppResume() = 0;
			
			// Indicates how operational the CMS manager currently is.
			virtual CMSStatus		GetStatus() = 0;
			// Returns true if shut down or errored at startup.
			virtual bool32			IsShutDown() = 0; 
			// Returns true if currently starting up.
			virtual bool32			IsInitializing() = 0;
			// Returns true if started up successfully.
			virtual bool32			IsRunning() = 0;
			
		// CMM calls		
		// ----------------------------------------------
			// Get the number of CMMs available 	
			virtual uint32			GetNumOfCMMs() = 0;
			// Get the name of an available CMM
			virtual bool32			GetNthCMMName(int32 index, PMString& theName) = 0;		
			// Select a particular CMM
			virtual bool32			UseNthCMM(int32 index) = 0;
			// Get which one's selected; returns -1 if none is selected yet.
			virtual int32			GetActiveCMMIndex() = 0;
			
			virtual bool16 GetEngineInfo(uint32 engineIndex, PMString *engineName = nil, uint32 *engineCMS = nil, uint32 *engineCMM = nil) = 0;
			virtual bool16 GetEngineInfo(const PMString &engineName, uint32 *engineIndex = nil, uint32 *engineCMS = nil, uint32 *engineCMM = nil) = 0;
			virtual bool16 GetEngineInfo(uint32 engineCMS, uint32 engineCMM, uint32 *engineIndex = nil, PMString *engineName = nil) = 0;
			
		// Available Profile list methods		
		// ----------------------------------------------
			// These create CMSAvailableProfileList objects, which can be further
			// queried (e.g., count, profile names, etc).  Caller is responsible
			// for delete-ing the resulting list.
			// Caller may specify which CMM to use, or -1 to use the current CMM.
			// However, if the CMM is not the current one, only names may be obtained
			// from the resulting list; calls to the getfilename and getspace members
			// will not work.
			// ResetProfileListCache can be used to guarantee that the next call to
			// GenerateAllAvailableProfiles() will take a fresh look at the profiles out
			// on disk.  Otherwise it may used a cached version, which will not take any
			// changes to the external profiles into account.
			virtual void ResetProfileListCache(int32 whichCMM = -1) = 0;
			virtual CMSAvailableProfileList *GenerateAllAvailableProfiles(int32 whichCMM = -1) = 0;
			virtual CMSAvailableProfileList *GenerateAvailableProfiles(CMSMgrProfileFilter& filter, int32 whichCMM = -1) = 0;		// Generate a list of compatible profiles

		// System profiles		
		// ----------------------------------------------
			virtual bool32 		GetSystemProfileName(PMString& theName) = 0;		
			
			virtual bool16 GetDefaultProfileName(ICMSProfile::profileCategory category, PMString &name) = 0;
	
		// Methods for Using/Querying used Profiles
		// ----------------------------------------------
			// Item profiles.  These methods are used to assign profiles to items.
			
			// This method selects an external profile (by name) as the profile for the
			// specified item.  If the named profile is in the used profile list, its
			// refcount is simply increased by one.  If not, a new profile is created 
			// using data from the available profile list (if the profile isn't in that
			// list, the call fails).  In any case the UIDRef of the profile in the
			// used list is returned; its database is always the same as owningItem.
			// By passing a non-nil data and size, a profile will be created in the
			// document (i.e., kProfileSourceEmbeddedInDocument) and will be used as
			// the reference instead of failing when the name isn't found.
			virtual UIDRef			ItemUseExternalProfile(
														const UIDRef& owningItem, 
														const PMString& profileName,
														const void *pProfileData = nil,
														const int32 profileDataSize = 0) = 0;
			
			// Use the image's own embedded profile.  This call will fail on any item
			// that doesn't have embedded data.  The profile data is optional; if you 
			// already have it then it will be used; otherwise it will be pulled from
			// the image when it's needed.  However, if the image hasn't ever been set
			// up with a profile name (as might happen during the import process), 
			// you must either provide profile data, or the name of the profile.
			// The UIDRef of the new profile is returned, which is always from the 
			// same database as owningItem.
			virtual UIDRef			ItemUseEmbeddedProfile(
														const UIDRef& owningItem, 
														void *pProfileData = nil,
														int32 dataSize = 0,
														PMString *pEmbeddedName = nil) = 0; 

			// Have the item use the document default profile for its colorspace.
			// This is the default state for items without embedded profiles. 
			// No return value because the default profile is looked up as needed. 
			virtual bool32			ItemUseDocDefaultProfile(const UIDRef& owningItem) = 0;
			
			// Document profiles can only be external and are stored by their
			// category.  Returns the UIDRef of the selected profile.
			// By passing a non-nil data and size, a profile will be created in the
			// document (i.e., kProfileSourceEmbeddedInDocument) and will be used as
			// the reference instead of failing when the name isn't found.
			virtual UIDRef			DocUseProfile(
														IDocument *doc, 
														ICMSProfile::profileCategory which, 
														const PMString& profileName,
														const void *pProfileData = nil,
														const int32 profileDataSize = 0) = 0;
			virtual UIDRef			DocUseProfile(
														UIDRef docUIDRef, 
														ICMSProfile::profileCategory which, 
														const PMString& profileName,
														const void *pProfileData = nil,
														const int32 profileDataSize = 0) = 0;

			// Get used profile methods.
			virtual ICMSProfile 	*QueryUsedProfile(ICMSProfile::profileCategory which, IDocument *doc, bool32 forceSystemDefaultIfNone = kTrue) = 0;
			virtual ICMSProfile 	*QueryUsedProfile(int32 index, IDocument *doc) = 0;
			virtual ICMSProfile 	*QueryUsedProfile(const PMString &name, IDocument *doc) = 0;	
			virtual ICMSProfile 	*QueryUsedProfile(uint32 pmCsType, IPMUnknown* obj) = 0;	
			virtual int32 			FindUsedProfile(const PMString &name, IDocument *doc) = 0;
			virtual int32 			NumUsedProfiles(IDocument *doc) = 0;
			
			// Install the default profile for a category into a document. 'which' can be one of: 
			// ICMSProfile::kRGBSource; ICMSProfile::kCMYKSource; and ICMSProfile::kLABSource 
			// when 'doc' is non-nil and: ICMSProfile::kMonitorDestination; 
			// ICMSProfile::kCompositeDestination; and ICMSProfile::kSeparationDestination when 
			// 'doc' is nil.
			virtual bool16 InstallDefaultProfile(ICMSProfile::profileCategory which, IDocument *doc) = 0;
						
			virtual bool16 ProfilesEqual(ICMSProfile *iCMSProfileA, ICMSProfile *iCMSProfileB) const = 0;
			virtual bool16 ProfilesMatch(ICMSProfile *iCMSProfileA, ICMSProfile *iCMSProfileB) const = 0;
				
			// Create a virtual (memory-only, no DB) profile by asking ACE for the profile by its name.
			// Note that the profile by that name needs to be on the system, not embedded in a doc.
			virtual ICMSProfile *CreateVirtualProfileFromName(const PMString &name) = 0;

			// return true iff all the directories (profiles, csf, etc) required by color management
			// are present.
			virtual bool16 VerifyDirectories() = 0;
			
		// Methods for handling CMS during AGM-direct drawing (EPS, PDF)
		// ---------------------------------------------------------------
			// When libraries are drawing directly to AGM, you don't have the opportunity
			// to set up color spaces for that library.  So, during an EPS drawing, for example,
			// we want to assign profiles to the uncalibrated spaces so they draw on screen
			// properly.  These methods allow the ColorMgmt plug-in to properly handle this
			// sort of thing:  bracket the AGM calls with this begin/end pair and ColorMgmt
			// will automatically do the right thing based on whether CMS is on for the
			// specified document.
			// If pDestinationProfile is nil, CMS will use the current monitor profile as
			// the destination device.
			virtual bool32			BeginLibraryDraw(const UIDRef &pageItem, AGMColorProfile *pDestinationProfile = nil) = 0;
			virtual bool32			EndLibraryDraw() = 0;

		// Global parameters
		// -----------------
			// These affect global color behavior and are nonpersistent.
			typedef enum
			{
				kInvalidSelector = 0,
				
				kCMSOffMode, 		// redbook = 1, stock profiles = 2
				kAllowV4Export		// default is false (0)
			} CMSSelector;
			
			// returns true if the selector is recognized and set; otherwise false
			virtual bool32 SetGlobalParameter(CMSSelector selector, int32 value) = 0;
			// note: always returns zero for unrecognized selectors
			virtual int32 GetGlobalParameter(CMSSelector selector) = 0;


		#ifdef DEBUG
		virtual void DumpToDebugWindow(IDocument* document) = 0;
		#endif
};

#endif // __ICMSMANAGER__

// End, ICMSManager.h.
