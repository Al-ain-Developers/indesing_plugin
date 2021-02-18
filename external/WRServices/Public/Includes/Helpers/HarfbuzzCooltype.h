#ifndef HARFBUZZCOOLTYPE_H
#define HARFBUZZCOOLTYPE_H


#include "IWRHarfbuzzFontAccess.h"
#include "hb.h"
#include "CT.h"
#include "hb-machinery.hh"

#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-prototypes"

//All friend functions here are callback functions and have to be implemented using the font engine's API
struct hb_ct_font_t
{
	CCTFontDict dict;
	CCTFontInstance font;
	char * lang;
	char * script;
};
struct hb_kern_client_context
{
	float h_kern_value;
	float v_kern_value;
	WRInt32 glyph_pair[2];
};
void
encode_utf16_pair(uint32_t character, uint16_t *units);
// Harfbuzz callbacks
hb_position_t hb_ct_get_glyph_h_kerning(hb_font_t *font,
                          void *font_data,
                          hb_codepoint_t left_glyph,
                          hb_codepoint_t right_glyph,
                          void *user_data HB_UNUSED);

hb_blob_t *reference_table(hb_face_t *face HB_UNUSED, hb_tag_t tag, void *user_data);
hb_bool_t hb_ct_get_nominal_glyph(hb_font_t *font HB_UNUSED, void * font_data, hb_codepoint_t unicode,
                                  hb_codepoint_t * glyph, void *user_data HB_UNUSED);


hb_position_t
hb_ct_get_glyph_h_advance(hb_font_t *font HB_UNUSED,
                          void *font_data,
                          hb_codepoint_t glyph,
                          void *user_data HB_UNUSED);
hb_position_t
hb_ct_get_glyph_v_advance(hb_font_t *font HB_UNUSED,
                          void *font_data,
                          hb_codepoint_t glyph,
                          void *user_data HB_UNUSED);

hb_bool_t
hb_ct_get_glyph_name(hb_font_t *font HB_UNUSED,
                     void *font_data,
                     hb_codepoint_t glyph,
                     char *name, unsigned int size,
                     void *user_data HB_UNUSED);

void WR_HB_ApplyFeatures(void *font_data, void* clientRunContext, WROTFeatureInfo *featureInfo, WRFloat* endPenPos);
CTGlyphID BIBEXPORT GetGlyphIDAt_HB(void* clientRunContext, size_t elementIndex);
void BIBEXPORT ReplaceOneByOne_HB(void* clientRunContext, size_t strikeIndex, CTGlyphID newGlyphID, BRVBool32 isTempReplacement);
void BIBEXPORT ReplaceOneByMany_HB(void* clientRunContext, size_t strikeIndex, const CTGlyphID* newGlyphIDs, size_t numGlyphIDs);
void BIBEXPORT ReplaceRangeByOne_HB(void* clientRunContext, size_t startIndex, size_t limitIndex, CTGlyphID newGlyphID);
void BIBEXPORT ReplaceManyByOne_HB(void* clientRunContext, const size_t* strikeIndices, size_t indexCount, CTGlyphID newGlyphID);
size_t BIBEXPORT GetLigatureComponentIndex_HB(void* clientRunContext, size_t strikeIndex);
void BIBEXPORT SetLigatureComponentIndex_HB(void* clientRunContext, size_t strikeIndex, size_t newCompIndex);
size_t BIBEXPORT GetComponentCount_HB(void *clientCtx, size_t strikeIndex);
void BIBEXPORT SetComponentCount_HB(void *clientCtx, size_t strikeIndex, size_t newCompCount);
void BIBEXPORT AdjustPlacementAndAdvance_HB(void *clientCtx, size_t strikeIndex, BRVRealCoord xPlacementDelta,
                                            BRVRealCoord yPlacementDelta,  BRVRealCoord xAdvanceDelta, BRVRealCoord yAdvanceDelta);

void BIBEXPORT MergeAnchors_HB(void *clientCtx, size_t elementIndex1, BRVRealCoord anchor1x, BRVRealCoord anchor1y,
                               size_t elementIndex2, BRVRealCoord anchor2x, BRVRealCoord anchor2y, BRVBool32 isCursiveAttachment, BRVBool32 lastOnBaseline);

size_t BIBEXPORT GetAlternateIndex_HB(void *clientCtx, size_t elementIndex, const size_t* featureTagIndices, size_t numFeatureTagIndices);
BRVBool32 BIBEXPORT FeatureSelectorProc_HB(void* clientRunContext, const size_t *positions, size_t nbPositions,
                                           const size_t* featureTagIndices, size_t numFeatureTagIndices);
static void _hb_ct_font_set_funcs(hb_font_t *font, CCTFontDict dict, CCTFontInstance fontInstance, char * lang, char * script);

// class HarfbuzzCooltype
class HarfbuzzCooltype :public IWRHarfbuzzFontAccess
{
public:
    
	HarfbuzzCooltype() {};
	virtual ~HarfbuzzCooltype() {};
public:

    	virtual hb_face_t *
		hb_ct_face_create(WRFontDict *dict, hb_destroy_func_t destroy);
	virtual hb_font_t *
		hb_ct_font_create(WRFontDict * dict, WRFontInstance * instance, char * lang, char * script, hb_destroy_func_t destroy);
	//callback functions start
	friend void
		WR_HB_ApplyFeatures(void *font_data, void* clientRunContext, WROTFeatureInfo *featureInfo, WRFloat* endPenPos);
	friend  void
		_hb_ct_font_set_funcs(hb_font_t *font, CCTFontDict dict, CCTFontInstance fontInstance);
	friend hb_blob_t *
		reference_table(hb_face_t *face HB_UNUSED, hb_tag_t tag, void *user_data);// This must be implemented 
	friend hb_bool_t hb_ct_get_nominal_glyph(hb_font_t *font HB_UNUSED,
		void *font_data,
		hb_codepoint_t unicode,
		hb_codepoint_t *glyph,
		void *user_data HB_UNUSED);
	friend hb_position_t
		hb_ct_get_glyph_h_advance(hb_font_t *font HB_UNUSED,
			void *font_data,
			hb_codepoint_t glyph,
			void *user_data HB_UNUSED);
	friend hb_position_t
		hb_ct_get_glyph_v_advance(hb_font_t *font HB_UNUSED,
			void *font_data,
			hb_codepoint_t glyph,
			void *user_data HB_UNUSED);
	friend hb_bool_t
		hb_ct_get_glyph_name(hb_font_t *font HB_UNUSED,
			void *font_data,
			hb_codepoint_t glyph,
			char *name, unsigned int size,
			void *user_data HB_UNUSED);
	/*friend hb_bool_t
	hb_ct_get_glyph_h_origin(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	hb_position_t *x,
	hb_position_t *y,
	void *user_data HB_UNUSED);

	friend hb_bool_t
	hb_ct_get_variation_glyph(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t unicode,
	hb_codepoint_t variation_selector,
	hb_codepoint_t *glyph,
	void *user_data HB_UNUSED);
	
	friend hb_bool_t
	hb_ct_get_glyph_v_origin(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	hb_position_t *x,
	hb_position_t *y,
	void *user_data HB_UNUSED);*/
	
	friend hb_position_t
	hb_ct_get_glyph_h_kerning(hb_font_t *font,
	void *font_data,
	hb_codepoint_t left_glyph,
	hb_codepoint_t right_glyph,
	void *user_data HB_UNUSED);
	
	/*friend hb_position_t
	hb_ct_get_glyph_v_kerning(hb_font_t *font,
	void *font_data,
	hb_codepoint_t left_glyph,
	hb_codepoint_t right_glyph,
	void *user_data HB_UNUSED);
	
	friend hb_bool_t
	hb_ct_get_glyph_extents(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	hb_glyph_extents_t *extents,
	void *user_data HB_UNUSED);
	
	friend hb_bool_t
	hb_ct_get_glyph_contour_point(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_codepoint_t glyph,
	unsigned int point_index,
	hb_position_t *x,
	hb_position_t *y,
	void *user_data HB_UNUSED)=0;

	friend hb_bool_t
	hb_ct_get_glyph_from_name(hb_font_t *font HB_UNUSED,
	void *font_data,
	const char *name, int len, // -1 means nul-terminated //
	hb_codepoint_t *glyph,
	void *user_data HB_UNUSED);
	
	friend hb_bool_t
	hb_ct_get_font_h_extents(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_font_extents_t *metrics,
	void *user_data HB_UNUSED);
	
	friend hb_bool_t
	hb_ct_get_font_v_extents(hb_font_t *font HB_UNUSED,
	void *font_data,
	hb_font_extents_t *metrics,
	void *user_data HB_UNUSED);

	*/

	//callback functions end
	
    };
typedef class HarfbuzzCooltype HarfbuzzCooltype;

#endif
