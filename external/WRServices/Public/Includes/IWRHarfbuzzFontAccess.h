

#ifndef __IWRHarfbuzzFontAccess__
#define __IWRHarfbuzzFontAccess__

#include "hb.h"
#include "WRDefines.h"
class WRSERVICES_DECL IWRHarfbuzzFontAccess {
public:
    virtual ~IWRHarfbuzzFontAccess(){};
	virtual hb_face_t * hb_ct_face_create(WRFontDict *dict, hb_destroy_func_t destroy) = 0;
	virtual	hb_font_t * hb_ct_font_create(WRFontDict * dict, WRFontInstance * fontInstance, char * lang, char * script, hb_destroy_func_t destroy) = 0;
};

#endif
