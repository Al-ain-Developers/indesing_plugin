#pragma once
#ifndef __Ext__
#define __Ext__

#ifndef kIDEnigmaCode
#define kIDEnigmaCode "IDSN"
#endif

#ifndef kICEnigmaCode
#define kICEnigmaCode "AICY"
#endif

class CExt {
public:
	static bool16 extInitialized;

	PUBLIC_DECL CExt();
	PUBLIC_DECL ~CExt();

	PUBLIC_DECL static bool16 isInitialized();
	PUBLIC_DECL static bool16 InitializeExtLib();
	PUBLIC_DECL static int32 LogEventForPluginList();
	PUBLIC_DECL static int32 LogCepExtension(const PMString& extensionID);
	PUBLIC_DECL static void DeinitializeExtlib();
};


#endif
