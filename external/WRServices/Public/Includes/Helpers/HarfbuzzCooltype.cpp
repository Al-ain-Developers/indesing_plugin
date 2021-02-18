
#include "HarfbuzzCooltype.h"
#include "IWRHarfbuzzFontAccess.h"
#include "CT.h" 
#include "WRVector.h"
static void destroy_face(void * user_data)
{
	CCTFontDict fontDict((CTFontDict*)user_data, true);
}
hb_position_t
hb_ct_get_glyph_h_kerning(hb_font_t *font,
                          void *font_data,
                          hb_codepoint_t left_glyph,
                          hb_codepoint_t right_glyph,
                          void *user_data HB_UNUSED);

static hb_ct_font_t *
_hb_ct_font_create(CCTFontDict fontDict, CCTFontInstance fontInstance, char * lang, char * script)
{

	hb_ct_font_t * ct_font = new hb_ct_font_t();

	ct_font->font = fontInstance;
	ct_font->dict = fontDict;
	ct_font->lang = lang;
	ct_font->script = script;

	return ct_font;

};
static void
_hb_ct_font_destroy(void *ct_font)
{
	delete((hb_ct_font_t*)ct_font);
}

hb_blob_t *
reference_table(hb_face_t *face HB_UNUSED, hb_tag_t tag, void *user_data)
{
	unsigned char unsignedTag[] = { HB_UNTAG(tag) };


	char untagged[] = { static_cast<char>(unsignedTag[0]),static_cast<char>(unsignedTag[1]),static_cast<char>(unsignedTag[2]),static_cast<char>(unsignedTag[3]),'\0' };
	//BRVUns32 tableTag = HB_TAG(untagged[3],untagged[2], untagged[1], untagged[0]);

	CCTFontDict dict((CTFontDict*)user_data);
	CBIBSharedBuffer tableBuf;
	dict.GetFontTable(untagged, tableBuf);

	if (tableBuf.GetSize() == 0)
		return NULL;
	return hb_blob_create((const char *)tableBuf.GetBuffer(), static_cast<unsigned int> (tableBuf.GetSize()),
		HB_MEMORY_MODE_DUPLICATE,
		tableBuf.GetBuffer(), NULL);
};

//Wikipedia algo to convert character from utf32 to utf16: https://en.wikipedia.org/wiki/UTF-16
void
encode_utf16_pair(uint32_t character, uint16_t *units)
{
	unsigned int code;
	//assert(0x10000 <= character && character <= 0x10FFFF);
	if (character > 0x10000)
	{
		code = (character - 0x10000);
		units[0] = 0xD800 + (code >> 10);
		units[1] = 0xDC00 + (code & 0x3FF);
	}
	else
	{
		units[0] = character;
		units[1] = 0;
	}
}

hb_bool_t hb_ct_get_nominal_glyph(hb_font_t *font HB_UNUSED, void * font_data, hb_codepoint_t unicode, hb_codepoint_t * glyph, void *user_data HB_UNUSED)
{

	const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
	unsigned char bytes[5];
	CCTEncoding encoding;
	encoding = ct_font->font.GetEncoding();
	auto preDefEnc = encoding.GetWhichPreDefined();
	uint16_t u16_str[2];
	encode_utf16_pair(unicode, u16_str);
	if (preDefEnc == kCTLEUnicode3Encoding)
	{
		bytes[0] = (u16_str[0] >> 0) & 0xFF;
		bytes[1] = (u16_str[0] >> 8) & 0xFF;
		bytes[2] = (u16_str[1] >> 0) & 0xFF;
		bytes[3] = (u16_str[1] >> 8) & 0xFF;
		bytes[4] = '\0';
		//printf("Little endian");
	}
	else
	{
		bytes[0] = (u16_str[0] >> 8) & 0xFF;
		bytes[1] = (u16_str[0]) & 0xFF;
		bytes[2] = (u16_str[1] >> 8) & 0xFF;
		bytes[3] = (u16_str[1]) & 0xFF;
		bytes[4] = '\0';

		//printf("Big endian");
	}
	const unsigned char * string;
	string = &(bytes[0]);

	size_t 	bytesConsumed;
	size_t stringLen;
	stringLen = sizeof(bytes);

	CTGlyphID glyphId;
	glyphId = ct_font->font.GetGlyphID(string, stringLen, bytesConsumed);
	*glyph = (hb_codepoint_t)glyphId;


	return true;
}

//TODO: to be tested
hb_position_t
hb_ct_get_glyph_h_advance(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	void *user_data HB_UNUSED)
{
	const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
	BRVRealCoord h_advance;
	h_advance = ct_font->font.GetWidth(glyph);
	return (hb_position_t)h_advance;
};

hb_position_t
hb_ct_get_glyph_v_advance(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	void *user_data HB_UNUSED)
{
	const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
	BRVRealCoord v_advance;
	v_advance = ct_font->font.GetWidth(glyph);
	return (hb_position_t)(v_advance);
};

hb_bool_t
hb_ct_get_glyph_name(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	char *name, unsigned int size,
	void *user_data HB_UNUSED)
{
	const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
	CBIBStringAtom glyph_name;
	glyph_name = ct_font->dict.GetNthGlyphName((size_t)glyph);
	const char* temp;
	temp = glyph_name.c_str();
	int j = 0;

	while (*(temp + j) != '\0')
	{
		name[j] = temp[j];
		j++;
	}
	name[j] = '\0';

	return true;
};


// Forward declaration for callbacks
CTGlyphID BIBEXPORT GetGlyphIDAt_HB(void* clientRunContext, size_t elementIndex)
{
	hb_kern_client_context * ctx = (hb_kern_client_context*)clientRunContext;
	WRInt32 i = static_cast<WRInt32>(elementIndex);
	if (i < 2)
		return (ctx->glyph_pair)[i];
	return -1;
}
void BIBEXPORT ReplaceOneByOne_HB(void* clientRunContext, size_t strikeIndex, CTGlyphID newGlyphID, BRVBool32 isTempReplacement)
{

}
void BIBEXPORT ReplaceOneByMany_HB(void* clientRunContext, size_t strikeIndex, const CTGlyphID* newGlyphIDs, size_t numGlyphIDs)
{

}
void BIBEXPORT ReplaceRangeByOne_HB(void* clientRunContext, size_t startIndex, size_t limitIndex, CTGlyphID newGlyphID)
{

}
void BIBEXPORT ReplaceManyByOne_HB(void* clientRunContext, const size_t* strikeIndices, size_t indexCount, CTGlyphID newGlyphID)
{

}
size_t BIBEXPORT GetLigatureComponentIndex_HB(void* clientRunContext, size_t strikeIndex)
{
	return 1;
}
void BIBEXPORT SetLigatureComponentIndex_HB(void* clientRunContext, size_t strikeIndex, size_t newCompIndex)
{

}
size_t BIBEXPORT GetComponentCount_HB(void *clientCtx, size_t strikeIndex)
{
	return 1;
}
void BIBEXPORT SetComponentCount_HB(void *clientCtx, size_t strikeIndex, size_t newCompCount)
{

}
void BIBEXPORT AdjustPlacementAndAdvance_HB(void *clientCtx, size_t strikeIndex, BRVRealCoord xPlacementDelta, BRVRealCoord yPlacementDelta, BRVRealCoord xAdvanceDelta, BRVRealCoord yAdvanceDelta)
{
	hb_kern_client_context * ctx = (hb_kern_client_context*)clientCtx;
	ctx->h_kern_value = xAdvanceDelta;
}
void BIBEXPORT MergeAnchors_HB(void *clientCtx, size_t elementIndex1, BRVRealCoord anchor1x, BRVRealCoord anchor1y, size_t elementIndex2, BRVRealCoord anchor2x, BRVRealCoord anchor2y, BRVBool32 isCursiveAttachment, BRVBool32 lastOnBaseline)
{

}
size_t BIBEXPORT GetAlternateIndex_HB(void *clientCtx, size_t elementIndex, const size_t* featureTagIndices, size_t numFeatureTagIndices)
{
	return 1;
}
BRVBool32 BIBEXPORT FeatureSelectorProc_HB(void* clientRunContext, const size_t *positions, size_t nbPositions, const size_t* featureTagIndices, size_t numFeatureTagIndices)
{
	return 1;
}

void
WR_HB_ApplyFeatures(void * font_data, void* clientRunContext, WROTFeatureInfo *featureInfo, WRFloat* endPenPos)
{
	const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
	CCTFontInstance fontInstance = ct_font->font;
	CCTFontDict fontDict = ct_font->dict;

	CTTextRunProcs runProcs(GetGlyphIDAt_HB,
		ReplaceOneByOne_HB,
		ReplaceOneByMany_HB,
		ReplaceRangeByOne_HB,
		ReplaceManyByOne_HB,
		GetLigatureComponentIndex_HB,
		SetLigatureComponentIndex_HB,
		GetComponentCount_HB,
		SetComponentCount_HB,
		GetAlternateIndex_HB,
		AdjustPlacementAndAdvance_HB,
		MergeAnchors_HB);
	size_t startIndex = 0, limitIndex = 2;
	CTFeatureType flags = kCTGlyphPositioning;
	WRInt32 numStrikes = 2;
	fontInstance.ProcessFeatures(runProcs,
		clientRunContext,
		featureInfo->script,
		featureInfo->language,
		featureInfo->features,
		featureInfo->numFeatures,
		flags,
		0, numStrikes,
		startIndex, limitIndex,
		featureInfo->featureRanges ? FeatureSelectorProc_HB : NULL);
};

hb_position_t
hb_ct_get_glyph_h_kerning(hb_font_t *font,
                          void *font_data,
                          hb_codepoint_t left_glyph,
                          hb_codepoint_t right_glyph,
                          void *user_data HB_UNUSED)
{
    //const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
    const hb_ct_font_t *ct_font = (const hb_ct_font_t *)font_data;
    WRFloat endPenPos[2] = { 0,0 };
    WROTFeature_v3Info v3KernFeatureInfo = {
        NULL,
        NULL,
        NULL,
        NULL
    };
    unsigned short dir = 0;
    WRInt32 numFeatures = 1;
    WRVector<WRInt32> choiceIndexes;
    hb_kern_client_context ctx;
    (ctx.glyph_pair)[0] = left_glyph;
    (ctx.glyph_pair)[1] = right_glyph;
    ctx.h_kern_value = 0.0f;
    ctx.v_kern_value = 0.0f;
    choiceIndexes.Append(-1);
    WRVector<WRInt32> ranges;
    ranges.Append(0);
    ranges.Append(1);
    WRVector<WRInt32> tags;
    tags.Append(WRTag2Long("kern"));
    char *scriptTag = ct_font->script;
    char *langTag = ct_font->lang;
    WROTFeatureInfo kernFeatureInfo = {
        kWROTFeature_v3,
        static_cast<unsigned short>(kWRApplyGlyphPos | dir) ,
        (char*)tags.PeekArray(),
        numFeatures,
        choiceIndexes.PeekArray(), // no choice
        ranges.PeekArray(),
        scriptTag,
        langTag, // default
        &v3KernFeatureInfo
    };
    WR_HB_ApplyFeatures(font_data, &ctx, &kernFeatureInfo,endPenPos);
    return (hb_position_t)ctx.h_kern_value;
}


#ifdef HB_USE_ATEXIT
static void free_static_ft_funcs(void);
#endif

static struct hb_ct_font_funcs_lazy_loader_t : hb_font_funcs_lazy_loader_t<hb_ct_font_funcs_lazy_loader_t>
{
	static inline hb_font_funcs_t *create(void)
	{
		hb_font_funcs_t *funcs = hb_font_funcs_create();

		//hb_font_funcs_set_font_h_extents_func(funcs, hb_ct_get_font_h_extents, nullptr, nullptr);
		//hb_font_funcs_set_font_v_extents_func (funcs, hb_ct_get_font_v_extents, nullptr, nullptr);
		hb_font_funcs_set_nominal_glyph_func(funcs, hb_ct_get_nominal_glyph, nullptr, nullptr);
		//hb_font_funcs_set_variation_glyph_func(funcs, hb_ct_get_variation_glyph, nullptr, nullptr);
		hb_font_funcs_set_glyph_h_advance_func(funcs, hb_ct_get_glyph_h_advance, nullptr, nullptr);
		hb_font_funcs_set_glyph_v_advance_func(funcs, hb_ct_get_glyph_v_advance, nullptr, nullptr);
		//hb_font_funcs_set_glyph_h_origin_func (funcs, hb_ct_get_glyph_h_origin, nullptr, nullptr);
		//hb_font_funcs_set_glyph_v_origin_func(funcs, hb_ct_get_glyph_v_origin, nullptr, nullptr);
		hb_font_funcs_set_glyph_h_kerning_func(funcs, hb_ct_get_glyph_h_kerning, nullptr, nullptr);
		//hb_font_funcs_set_glyph_v_kerning_func (funcs, hb_ct_get_glyph_v_kerning, nullptr, nullptr);
		//hb_font_funcs_set_glyph_extents_func(funcs, hb_ct_get_glyph_extents, nullptr, nullptr);
		//hb_font_funcs_set_glyph_contour_point_func(funcs, hb_ct_get_glyph_contour_point, nullptr, nullptr);
		hb_font_funcs_set_glyph_name_func(funcs, hb_ct_get_glyph_name, nullptr, nullptr);
		//hb_font_funcs_set_glyph_from_name_func(funcs, hb_ct_get_glyph_from_name, nullptr, nullptr);

		hb_font_funcs_make_immutable(funcs);

#ifdef HB_USE_ATEXIT
		atexit(free_static_ft_funcs);
#endif

		return funcs;
	}
} static_ft_funcs;

#ifdef HB_USE_ATEXIT
static
void free_static_ft_funcs(void)
{
	static_ft_funcs.free_instance();
}
#endif

static hb_font_funcs_t *
_hb_ct_get_font_funcs(void)
{
	return static_ft_funcs.get_unconst();
}

static void
_hb_ct_font_set_funcs(hb_font_t *font, CCTFontDict dict,
	CCTFontInstance fontInstance,char * lang, char * script)
{
	hb_font_set_funcs(font,
		_hb_ct_get_font_funcs(),
		_hb_ct_font_create(dict,fontInstance,lang,script),
		_hb_ct_font_destroy);
}

hb_face_t * HarfbuzzCooltype::hb_ct_face_create(WRFontDict *dict, hb_destroy_func_t destroy)
{
    hb_face_t *face;
    CCTFontDict fontDict((CTFontDict*)dict);
    
    face = hb_face_create_for_tables(&reference_table, fontDict.GetPointerAndAddRef(), destroy_face);
    
    hb_face_set_glyph_count(face, static_cast<unsigned int>(fontDict.GetNumGlyphs()));
    BRVUns16 unitsPerEm;
    if (fontDict.GetUnitsPerEm(unitsPerEm))
    {
        hb_face_set_upem(face, unitsPerEm);
    }
    
    return face;
    
};
hb_font_t * HarfbuzzCooltype::
hb_ct_font_create(WRFontDict * dict, WRFontInstance * instance, char * lang, char * script, hb_destroy_func_t destroy)
{
    hb_font_t *font;
    hb_face_t *face;
    
    face = hb_ct_face_create(dict, destroy_face);
    font = hb_font_create(face);
    CCTFontDict fontDict((CTFontDict*)dict);
    CCTFontInstance fontInstance((CTFontInstance*)instance);
    
    _hb_ct_font_set_funcs(font, fontDict, fontInstance, lang, script);
    /*hb_font_set_scale(font,
     (int)(((uint64_t)dict.GetHorizontalMetrics * (uint64_t)face->upem + (1u << 15)) >> 16),
     (int)(((uint64_t)ct_face->size->metrics.y_scale * (uint64_t)face->upem + (1u << 15)) >> 16));
     */
    hb_face_destroy(face);
    return font;
};

