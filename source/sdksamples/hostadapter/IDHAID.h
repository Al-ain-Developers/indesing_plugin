#ifndef __IDHAID_h__
#define __IDHAID_h__

#include "SDKDef.h"

// Company:
#define kIDHACompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kIDHACompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kIDHAPluginName	"IDHostAdapter"			// Name of this plug-in.
#define kIDHAPrefixNumber	0x168900 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kIDHAVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kIDHAAuthor		"Lea Savage"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kIDHAPrefixNumber above to modify the prefix.)
#define kIDHAPrefix		RezLong(kIDHAPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kIDHAStringPrefix	SDK_DEF_STRINGIZE(kIDHAPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kIDHAMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kIDHAMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kIDHAPluginID, kIDHAPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kIDHAScriptProviderBoss, kIDHAPrefix + 0)
DECLARE_PMID(kClassIDSpace, kIDHAScriptObserverBoss, kIDHAPrefix + 1)
DECLARE_PMID(kClassIDSpace, kIDHAApplyMasterResponderBoss,	kIDHAPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kIDHANewDocResponderBoss,	kIDHAPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kIDHACloseDocResponderBoss,	kIDHAPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kIDHAAfterPlaceResponderBoss,	kIDHAPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kIDHABoss, kIDHAPrefix + 3)

// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDHAINTERFACE, kIDHAPrefix + 5)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kIDHAScriptProviderImpl, kIDHAPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kIDHAObserverImpl, kIDHAPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kIDHAStartupShutdownImpl, kIDHAPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kIDHAResponderImpl, kIDHAPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kIDHAImpl, kIDHAPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kIDHAImpl, kIDHAPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kIDHAImpl, kIDHAPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kIDHAImpl, kIDHAPrefix + 6)



// ActionIDs:
DECLARE_PMID(kActionIDSpace, kIDHAAboutActionID, kIDHAPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kIDHAActionID, kIDHAPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kIDHAActionID, kIDHAPrefix + 6)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kIDHAWidgetID, kIDHAPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kIDHAWidgetID, kIDHAPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kIDHAWidgetID, kIDHAPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kIDHAWidgetID, kIDHAPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kIDHAWidgetID, kIDHAPrefix + 6)


//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kIDHAMethodScriptElement, kIDHAPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kIDHAPropertyScriptElement, kIDHAPrefix + 2)

// ScriptInfoIDs for Events:
DECLARE_PMID(kScriptInfoIDSpace, kContentChangedEventScriptElement, kIDHAPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kFormatChangedEventScriptElement, kIDHAPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kGeometryChangedEventScriptElement, kIDHAPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleListChangedEventScriptElement, kIDHAPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleListChangedEventScriptElement, kIDHAPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kCellStyleListChangedEventScriptElement, kIDHAPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kParaStyleListChangedEventScriptElement, kIDHAPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kCharStyleListChangedEventScriptElement, kIDHAPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kSpreadListChangedEventScriptElement, kIDHAPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kLayerCreatedEventScriptElement, kIDHAPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kLayerAddedEventScriptElement, kIDHAPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kLayerChangedEventScriptElement, kIDHAPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kLayerVisibleChangedEventScriptElement, kIDHAPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kLayerLockChangedEventScriptElement, kIDHAPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kLayerOrderChangedEventScriptElement, kIDHAPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kDropEventScriptElement, kIDHAPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kKeyDownEventScriptElement, kIDHAPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kKeyUpEventScriptElement, kIDHAPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kKeyPressedEventScriptElement, kIDHAPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kMasterPageAppliedEventScriptElement, kIDHAPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kOverrideMasterPageItemEventScriptElement, kIDHAPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemDetachFromMasterPageEventScriptElement, kIDHAPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kCreateObjectEventScriptElement, kIDHAPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kModifyObjectEventScriptElement, kIDHAPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kStyleListChangedEventScriptElement, kIDHAPrefix + 27)


// ErrorID
//DECLARE_PMID(kErrorIDSpace,	kIDHostAdapterFailureErrorCode,	kIDHAPrefix + 1)


// "About Plug-ins" sub-menu:
#define kIDHAAboutMenuKey			kIDHAStringPrefix "kIDHAAboutMenuKey"
#define kIDHAAboutMenuPath		kSDKDefStandardAboutMenuPath kIDHACompanyKey

// "Plug-ins" sub-menu:
#define kIDHAPluginsMenuKey 		kIDHAStringPrefix "kIDHAPluginsMenuKey"
#define kIDHAPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kIDHACompanyKey kSDKDefDelimitMenuPath kIDHAPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kIDHAAboutBoxStringKey	kIDHAStringPrefix "kIDHAAboutBoxStringKey"
#define kIDHATargetMenuPath kIDHAPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kIDHAFirstMajorFormatNumber  RezLong(1)
#define kIDHAFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kIDHACurrentMajorFormatNumber kIDHAFirstMajorFormatNumber
#define kIDHACurrentMinorFormatNumber kIDHAFirstMinorFormatNumber

#endif // __IDHAID_h__

//  Code generated by DollyXs code generator
