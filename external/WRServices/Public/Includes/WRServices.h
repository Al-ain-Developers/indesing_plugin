//========================================================================================
//  
//  File: WRServices.h
//  
//  Owner: Michel Hutinel
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRServices__
#define __WRServices__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRPath.h"
#include <set>

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

class IWRFontAccess;
class IWRFontInfo;
class IWRFontCache;
class IWRFontContext;
class IWRMultiProcessing;
class IWROptycaPool;
class IWRClientSettings;

/* 
WRGetVersion 
*/
WRSERVICES_DECL WRUInt32 WRGetVersion();
/* 

WRInitialize 
*/
WRSERVICES_DECL WRInt32 WRServicesPreInitialize(WRMemObj* memObj);

WRSERVICES_DECL WRInt32 WRServicesInitialize(WRPath* fontDBPathWinSoft, WRPath* fontDBPathUser,
										  WRClientArea area = kWRAreaCEEA, WRClientType clientType = kWRTextOriented);

WRSERVICES_DECL void WRServicesSetFontContext(IWRFontContext* cntxt);
WRSERVICES_DECL IWRFontContext* WRServicesFontContext();
WRSERVICES_DECL IWRFontAccess* WRServicesFontAccess();
WRSERVICES_DECL IWRFontInfo* WRServicesFontInfo();
WRSERVICES_DECL IWRMultiProcessing* WRServicesMultiProcessing();
WRSERVICES_DECL IWRClientSettings* WRServicesSettings();
WRSERVICES_DECL WRUInt32 WRServicesGetClientCount();
WRSERVICES_DECL WRUInt32 WRServicesGetPreInitializeCount();
WRSERVICES_DECL void WRServicesSetMultiProcessing(IWRMultiProcessing* multi);
WRSERVICES_DECL void WRServicesSetFontAccess(IWRFontAccess* access);
WRSERVICES_DECL void WRServicesScriptsUsed(std::set<const char *> scripts);
WRSERVICES_DECL void WRServicesFontsUsed(std::set<std::string> fonts);
WRSERVICES_DECL void HighbeamLogging();
// Client Product should provide the Highbeam information to WRServices through this API.
//  personGUID: GUID of logged in user,if not known to the client then pass an empty string
//  licenseStatus: license status of the application,if not known to the client then pass an empty string
//  state: Serialization state, same state as passed while initializing AdobePip, kPrerelease(0) or kNonPrerelease(-1), if not known, pass kPrerelease(0).
//	productName: Name of the client product e.g. Photoshop, Indesign etc
//	productVersion: Version of the client product e.g. 11.0, 12.0, CS6 etc
//  productLocale: Locale of the client product e.g. en_US, de_DE etc
WRSERVICES_DECL void SetHighbeamInfo(const char* personGUID, const char* licenseStatus, int state, const char* productName, const char* productVersion, const char* productLocale);

/* 
WRServicesTerminate 
*/
WRSERVICES_DECL WRInt32	WRServicesTerminate ();

/* 
WRServicesPostTerminate 
*/
WRSERVICES_DECL WRInt32 WRServicesPostTerminate();

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif /* WRServices */
