//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicsPort.h $
//  
//  Owner: Jack Kirstein
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
//  Purpose of interface
//  IGraphicsPort is THE drawing API for Shuksan. It is a shell around
//  the AGM API
//  
//  The methods behave exactly, or very much like the equivalent PostScript operators.
//  See the PostScript language reference manual for complete documentation
//  
//  IMPORTANT: if you expect something to print, this is the ONLY interface you can use
//  to do drawing
//  
//========================================================================================

#pragma once
#ifndef __IGRAPHICSPORT__
#define __IGRAPHICSPORT__

#include "GraphicsID.h"
//#include "GRConversions.h"
#include "PMMatrix.h"
#include "PMReal.h"
#include "PMRect.h"
#include "GraphicTypes.h"
#include "BravoForwardDecl.h"

class IFontInstance;
class IPMFont;
class IOPIInfo;
class IDrawMgr;
class PMRealGlyphPoint;

struct OneOTFeature;

#define __PORTSUPPORTSFIXED__				// The graphics port is moving from Fixed numbers to floats - this is here until we force it

/**
	The following is a class container, to pass on auxiliary information using
	BeginAuxInfoContext/EndAuxInfoContext.
	For future usage, we could add kText, and pass on text run information,
	so a GPort can mark the received text strings from the show() methods,
	and group them and mark them as paragraphs, or text links.
*/
class GPortAuxInfoParam
{
	public:
		enum AuxInfoObjectType
		{
			kNone,
			kImage,
			kTextFrame,
			kImageStream,	// tagging only (no data)
			kText,
			kColor,
			kTextRun
		};

		inline GPortAuxInfoParam(): fObjType( kNone ), fOPIInfo(nil), fTextStart(0), fTextSpan(0), fTint(0.0) {}
		inline GPortAuxInfoParam( AuxInfoObjectType objType ) :
				fObjType(objType), fOPIInfo(nil), fTextStart(0), fTextSpan(0), fTint(0.0) {}

		/**
			Set the type of information stored by this object.
			@param AuxInfoObjectType bObjType: object type.
		*/
		inline void SetObjectType(AuxInfoObjectType bObjType) {fObjType = bObjType;}
		/**
			Get the type of information stored by this object.
			@param AuxInfoObjectType* bObjType: Return the object type.
		*/
		inline void GetObjectType(AuxInfoObjectType* bObjType) {*bObjType = fObjType;}
		/**
			Get the type of information stored by this object.
			@return AuxInfoObjectType
		*/
		inline AuxInfoObjectType GetObjectType() { return fObjType ; }

		/**
			Store OPI information with this object.
			@param IOPIInfo* bOPIInfo: OPI object to store.
		*/
		inline void SetOPIInfo(IOPIInfo* bOPIInfo) {fOPIInfo = bOPIInfo;}
		/**
			Get the OPI information stored with this object.
			@param IOPIInfo** bOPIInfo: Returns the OPI object stored.
		*/
		inline void GetOPIInfo(IOPIInfo** bOPIInfo) {*bOPIInfo = fOPIInfo;}
		/**
			Get the OPI information stored with this object.
			@return IOPIInfo*: Returns the OPI object stored.
		*/
		inline IOPIInfo* GetOPIInfo() { return fOPIInfo ; }

		/**
			Store a UIDRef with this object.
			@param UIDRef& obj: UIDRef to store.
		*/
		inline void SetObjectRef( const UIDRef& obj ) { fObjRef = obj ; }
		/**
			Get the UIDRef stored with this object.
			@return UIDRef&: Returns the UIDRef object stored.
		*/
		inline const UIDRef& GetObjectRef() { return fObjRef ; }

		/**
			Store the starting text index with this object.
			@param TextIndex start: TextIndex to store.
		*/
		inline void SetTextStart( TextIndex start ) { fTextStart = start ; }
		/**
			Get the starting text index stored with this object.
			@return TextIndex Returns the TextIndex stored.
		*/
		inline TextIndex GetTextStart() { return fTextStart ; }

		/**
			Store the span with this object.
			@param int32: Return span stored.
		*/
		inline void SetTextSpan( int32 span ) { fTextSpan = span ; }
		/**
			Get the span stored with this object.
			@return int32: Returns the span stored.
		*/
		inline int32 GetTextSpan() { return fTextSpan ; }

		/**
			Store the tint with this object.
			@param const PMReal& tint: tint to store with this object.
		*/
		inline void SetTint( const PMReal& tint ) { fTint = tint ; }
		/**
			Get the tint stored with this object.
			@return PMReal&: Returns the tint stored.
		*/
		inline const PMReal& GetTint() { return fTint ; }

	private:
		AuxInfoObjectType fObjType;
		IOPIInfo* fOPIInfo;
		UIDRef fObjRef ;
		TextIndex fTextStart ;
		int32 fTextSpan ;
		PMReal fTint ;
};

/**
	IGraphicsPort is THE drawing API for InDesign. It is a shell around the AGM API.

	The methods behave exactly, or very much like the equivalent PostScript operators.
	See the PostScript language reference manual for complete documentation.

	IMPORTANT: if you expect something to print, this is the ONLY interface you can use
	to do drawing.
*/
class IGraphicsPort : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGRAPHICSPORT };

		// Call this to initialize or re-initialize the port
		virtual void Setup() = 0;

	/**
		Clears the port's current path (makes it empty).

		Equivalent to the PostScript 'newpath' operator.
	*/
		virtual void newpath() = 0;
	/**
		Begins a new subpath within the current path.
		It also sets the path's current point to the given point.

		<b>Note:</b> All valid paths must begin with a call to MoveTo,
		or HintedMoveTo.

		Equivalent to the PostScript 'moveto' operator.
	*/
		virtual void moveto(const PMReal& x, const PMReal& y) = 0;
	/**
		Begins a new subpath within the current path.
		It also sets the path's current point to the path's existing
		current point offset by the given coordinates.  The
		'R' stands for 'relative'.  The path cannot be empty
		when this call is made.

		Equivalent to PostScript's 'rmoveto' operator.
	*/
		virtual void rmoveto(const PMReal& x, const PMReal& y) = 0;
	/**
		Adds a line segment to the path.
		The segment is from the path's current point
		to the given point.  The given point becomes the
		path's new current point.  The path cannot be empty
		when this call is made.

		Equivalent to PostScript's 'lineto' operator.
	*/
		virtual void lineto(const PMReal& x, const PMReal& y) = 0;
	/**
		Adds a bezier curve segment to the path.  The curve
		is defined by the path's current point as the first
		anchor point, (x1,y1) as the first control point,
		(x2,y2) as the second control point, and (x3,y3)
		as the second anchor point.  (x3,y3) becomes the
		path's new current point.  The path cannot be empty
		when this call is made.

		Equivalent to PostScript's 'curveto' operator.
	*/
		virtual void curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3) = 0;
	/**
		Adds a bezier curve segment to the path.  This method
		is identical to the CurveTo method except that the path's
		current point is treated as both the first anchor point
		as well as the first control point.

		The method originated in the Adobe Illustrator file format
		which used a 'v' operator to represent this abbreviated
		form of curve.
	*/
		virtual void curvetov(const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3) = 0;
	/**
		Closes the current subpath.
		It appends a straight line segment connecting the current
		point to the subpath's starting point -- generally, the
		point most recently specified by MoveTo.

		Equivalent to PostScript's 'closepath' operator.
	*/
		virtual void closepath() = 0;
	/**
		Makes a copy of the port's current graphics state.
		The new copy becomes the port's new current state.
		The graphics state contains:
<pre>
* current clip
* current color
* current path
* current stroke settings
* current transformation matrix
</pre>
		Equivalent to PostScript's 'gsave' operator.

	*/
		virtual void gsave() = 0;
	/**
		Resets the port's current graphics state.
		It is set to the state that was saved in the previous
		call to GSave.

		Equivalent to PostScript's 'grestore' operator.
	*/
		virtual void grestore() = 0;
	/**
		Offsets the port's current transformation matrix.
		It uses the given values, which are first mapped
		by the current transformation matrix so that they
		are interpreted as being 'user space' values.

		Equivalent to PostScript's 'translate' operator.
	*/
		virtual void translate(const PMReal& x, const PMReal& y) = 0;
	/**
		Scales the port's current transformation matrix.
		It uses the given values, which are first mapped
		by the current transformation matrix so that they
		are interpreted as being 'user space' values.

		Equivalent to PostScript's 'scale' operator.
	*/
		virtual void scale(const PMReal& x, const PMReal& y) = 0;
	/**
		Rotates the port's current transformation matrix
		by the given number of degrees and replaces it.

		Equivalent to PostScript's 'rotate' operator.
	*/
		virtual void rotate(const PMReal& theta) = 0;
	/**
		Makes the port's current transformation matrix
		the product of the current matrix and the given one.

		Equivalent to PostScript's 'concat' operator.
	*/
		virtual void concat(const PMMatrix &m) = 0;	//this is a PreConcat in PMMatrix terms
	/**
		Sets the port's current line width.  This width
		is used in any later call to Stroke or StrokePathClip.

		A stroke adjusted linewidth can be incremented in steps of
		.25, giving better and smoother visual results for small
		linewidths when antialiasing is enabled.

		Equivalent to PostScript's 'setlinewidth' operator.

		@see IGraphicsPort#Stroke IGraphicsPort#StrokePathClip IGraphicsPort#StrokeAdjust
	*/
		virtual void setlinewidth(const PMReal& width) = 0;
	/**
		Sets the port's current dash pattern.  This pattern
		is used in any later call to Stroke or StrokePathClip.

		Equivalent to PostScript's 'setdash' operator.

		@see CAGMPort#Stroke CAGMPort#StrokePathClip
	*/
		virtual void setdash(int32 numDash, float* dashArray, float offset) = 0;

	/**
		Sets current blending mode in GState.

		Blending modes are defined in GraphicTypes.h
	*/
		virtual void setblendingmode (PMBlendingMode pmBlendingMode) = 0;

	/**
		Starts a new transparency group.
		'bounds' is in user space and defines the area of the
		transparency group.
		If 'isIsolated' is set, 'colorSpace' defines the colorspace
		of the group. If the group is defaulted or non-isolated,
		the parent's colorspace is used.

		StartTransparencyGroup does an automatic GSave.  It inherits
		all of the current GState except for 3 parameters that are
		reset:
<pre>
SetAlpha(1.0);
RemoveAlphaServer();
SetBlendingMode(kAGMBlendNormal);
</pre>
		@see IGraphicsPort#SetAlpha IGraphicsPort#RemoveAlphaServer IGraphicsPort#SetBlendingMode
	*/
		virtual void starttransparencygroup(const PMRect& bounds, AGMColorSpace *cs, bool16 isolationgroup = kTrue, bool16 knockoutgroup = kFalse) = 0;
	/**
		Ends a transparency group.
		EndTransparencyGroup does an automatic GRestore.
	*/
		virtual void endtransparencygroup() = 0;

	/**
		Starts a named group.
		Groups surround an arbitrary, and possibly empty,  set of drawing operations.  The may be nested.  Begin/End pairs must be matched
		within a given context which is identified by the name.

		'name' allows for protocols based nesting of multiple different group types
		'attrib' dictionary of attributes associated with the group itself rather than
		each of the enclosed elements.


		@see PMString const_CAIMDictionary
	*/
		virtual void BeginGroup( const PMString name, const_AIMDictionaryContainer* attrib ) = 0;

	/**
		Ends a named group.

		@see PMString
	*/
		virtual void EndGroup( const PMString name ) = 0;

	/**
		Sets a constant opacity value. opacity should be between
		0.0 (transparent) and (1.0) opaque.
		AlphaIsShape = true defines the alpha value as shape alpha.
		This value is in effect in addition to AlphaServer.
	*/
		virtual void setopacity (const PMReal& opacity, bool16 bIsAlphaShape) = 0; // from 0 to 1.0

	/**
		Sets the port's current line cap type.  This type
		is used in any later call to Stroke or StrokePathClip.
		These are the different types:
<pre>
* Butt cap
* Round cap
* Square cap
</pre>
		Equivalent to PostScript's 'setlinecap' operator.

		@see GraphicTypes.h for possible values of 'type'
	*/
		virtual void setlinecap(int32 type) = 0;
	/**
		Sets the port's current line join type.  This type
		is used in any later call to Stroke or StrokePathClip.
		Possible types are:
<pre>
* Miter join
* Round join
* Bevel join
</pre>
		Equivalent to PostScript's 'setlinejoin' operator.

		@see GraphicTypes.h for possible values of 'type'
		@see IGraphicsPort#Stroke IGraphicsPort#StrokePathClip
	*/
		virtual void setlinejoin(int32 type) = 0;

	/**
		Sets the port's current miter limit.  This limit is
		used iff the port's current join type is miter join
		in any later call to Stroke or StrokePathClip.

		Equivalent to PostScript's 'setmiterlimit' operator.

		@see CAGMPort#Stroke CAGMPort#StrokePathClip
	*/
		virtual void setmiterlimit(const PMReal& limit) = 0;
	/**
		Defines the StrokeAdjust state in the graphics state.

		Equivalent to PostScript's 'setstrokeadjust' operator.
	*/
		virtual void setstrokeadjust(bool16 strokeAdjust) = 0;
		virtual void setgray(const PMReal& gray) = 0;
		virtual void setrgbcolor(const PMReal& r, const PMReal& g, const PMReal& b) = 0;
		virtual void setcmykcolor(const PMReal& c, const PMReal& m, const PMReal& y, const PMReal& k) = 0;
		virtual void setlabcolor(const PMReal& l, const PMReal& a, const PMReal& b) = 0;
		virtual void setcolorspace(AGMColorSpace* colorSpace) = 0;
		virtual void setcolorvalues(const float* colorVals) = 0;

		virtual void setgradient(AGMGradient *agmGrad, const PMMatrix& grMatrix,
								const PMReal &xOrig, const PMReal &yOrig,
								const PMReal &len, const PMReal &ang,
								const PMReal &hiliteLen, const PMReal &hiliteAng) = 0;
	/**
		Installs a paint server as a color server.

		A subsequent port call to paint, such as Fill or Stroke, will call
		the paint servers to paint whatever graphic has been drawn with the
		color value(s).

		There may be both a color and an alpha paint server installed in
		the graphic state at the same time.

		alphaIsShape defines the alpha values as a shape (NOT opacity).

		Optional matrix will be concatenated with current CTM.

		TotalMatrix = paint server matrix * SetServer matrix * CTM.

		@see IGraphicsPort#SetAlphaServer
	*/
		virtual void SetColorServer(AGMPaint* agmPaint, bool16 bIsAlphaShape, const PMMatrix& m) = 0;
	/**
		Installs a paint server as an alpha server.

		A subsequent port call to paint, such as Fill or Stroke, will call
		the paint servers to paint whatever graphic has been drawn with the
		alpha value(s).

		There may be both a color and an alpha paint server installed in
		the graphic state at the same time.

		The alpha server must have a gray colorspace.
		'alphaIsShape' defines the alpha values as a shape (NOT opacity).

		This server is in effect in addition to fixed alpha.

		The optional 'matrix' will be concatenated with current CTM.

		TotalMatrix = paint server matrix * SetServer matrix * CTM.

		Clients may specify an invalid CAGMPaint.  In this case the alpha
		server is invalid, so none is defined.  This is the same as
		RemoveAlphaServer.

		@see IGraphicsPort#SetColorServer IGraphicsPort#RemoveAlphaServer
	*/
		virtual void SetAlphaServer(AGMPaint* agmPaint, bool16 bIsAlphaShape, const PMMatrix& m) = 0;

	/**
		Sets Overprint state in GState.
	*/
		virtual void setoverprint(bool32 overprint) = 0;
	/**
		Paints the inside of the current path.
		It uses the port's current color and opacity.  Insideness
		is determined by the winding fill rule.  Use EOFill for
		the even-odd fill rule.

		<b>Note:</b> This method clears the port's current path.

		Equivalent to PostScript's 'fill' operator.

		@see IGraphicsPort#EOFill
	*/
		virtual void fill() = 0;
	/**
		Paints the inside of the current path.
		It uses the port's current color and opacity.  Insideness
		is determined by the even-odd fill rule.  Use Fill for
		the winding fill rule.

		<b>Note:</b> This method clears the port's current path.

		Equivalent to PostScript's 'eofill' operator.

		@see IGraphicsPort#Fill
	*/
		virtual void eofill() = 0;
	/**
		Paints a line following the port's current path with
		the current color and opacity. The line thickness,
		dash pattern, joins, and caps are determined by the port's
		current settings for those (see SetLineWidth, SetLineDash,
		SetLineJoin, and SetLineCap).

		Equivalent to PostScript's 'stroke' operator.

		@see IGraphicsPort#SetLineWidth IGraphicsPort#SetLineDash
		     IGraphicsPort#SetLineJoin IGraphicsPort#SetLineCap
	*/
		virtual void stroke() = 0;
		virtual void image(_t_AGMImageRecord* imageRec, const PMMatrix& imMatrix, int32 flags) = 0;
		virtual void image(_t_AGMImageRecord* imageRec, AGMColorSpace* cs, const PMMatrix& m, int32 flags) = 0;
		// This replaces old version which took an IagmServer_Image
		virtual void image(AGMImage *image, const PMMatrix& imMatrix, int32 flags) = 0;

		// Use the following constants for show and xshow
		typedef enum
		{
			kFillText   = 1,
			kStrokeText = 2,
			kClipText	= 4
		} TextGraphicsFlags;

		virtual void show(const PMReal &x, const PMReal &y, uint32 numUTF16s, const textchar* text,
							TextGraphicsFlags graphicsflags = kFillText,
							bool16 verticalGlyphs = kFalse, bool16 wmodePositioning = kFalse) = 0;
#ifdef __PORTSUPPORTSFIXED__
		virtual void xshow(const PMReal &x, const PMReal &y, uint32 numGlyphs, const int32 *glyphArray,
							const Fixed* widths, const Fixed* yoffsets = nil,
							TextGraphicsFlags graphicsflags = kFillText,
							bool16 verticalGlyphs = kFalse, bool16 wmodePositioning = kFalse,
							uint32 numChars = 0, const textchar* text = nil,
							K2Vector<OneOTFeature>* otFeatureArray = nil) = 0;
#endif
		virtual void xshow(const PMReal &x, const PMReal &y, uint32 numGlyphs, const int32 *glyphArray,
							const float* widths, const float* yoffsets = nil,
							TextGraphicsFlags graphicsflags = kFillText,
							bool16 verticalGlyphs = kFalse, bool16 wmodePositioning = kFalse,
							uint32 numChars = 0, const textchar* text = nil,
							K2Vector<OneOTFeature>* otFeatureArray = nil) = 0;

		virtual void ctshow(IFontInstance *fontInstance,
							PMRealGlyphPoint *glyphPoints, uint32 numGlyphPoints,
							TextGraphicsFlags graphicsflags = kFillText,
							bool16 verticalGlyphs = kFalse) = 0;

		// xshow() and ctshow() take the optional parameters of numChars and text. These
			// are needed to include searchable text in Export PDF. They are ignored by most
			// other implementations.
			// verticalGlyphs = kTrue means to use the vertical variants even if the CMap is -H.
			// verticalGlyphs = kFalse means to use the horizontal variants.
			// wmodePositioning = kTrue means vertical text with the implication that the supplied character
				//positions are based on PostScript's vertical WMode; that is, vertical text with origin at
				//the top center of the glyph. Set this to kTrue if your text will be imaged vertically by
				//AGM or PostScript AND if the text positioning was determined by something other than
				//InDesign's composition engine. Examples of proper uses of wmodePosition = kTrue:
				//Vertical text in the UI or a placed EPS.
			// wmodePositioning = kFalse means that the supplied character positions are referred to the Roman
				//baseline. Set wmodePositioning to kFalse if InDesign's text composition engine layed out your
				//text, whether the text is intended to be vertical or horizontal.
		virtual void selectfont(IPMFont *font, const PMMatrix& m) = 0;
		virtual void selectfont(IPMFont *font, const PMReal& ptSize) = 0;
	/**
		Sets the clip to the intersection of the current clip
		and the inside of the current path.  Insideness is determined
		by the winding fill rule (see EOClip to use the even-odd
		fill rule).

		<b>Note:</b> This method does NOT modify the port's current path.

		Equivalent to PostScript's 'clip' operator.

		@see IGraphicsPort#EOClip
	*/
		virtual void clip() = 0;
	/**
		Sets the clip to the intersection of the current clip
		and the inside of the current path.  Insideness is determined
		by the even-odd fill rule (see Clip to use the winding
		fill rule).

		<b>Note:</b> This method does NOT modify the port's current path.

		Equivalent to PostScript's 'eoclip' operator.

		@see IGraphicsPort#Clip
	*/
		virtual void eoclip() = 0;
		virtual void strokepath_clip() = 0;
		virtual void rectclip(const PMReal& x, const PMReal& y, const PMReal& width, const PMReal& height) = 0;
		virtual void rectclip(const PMRect &r) = 0;
		virtual void rectfill(const PMReal& x, const PMReal& y, const PMReal& width, const PMReal& height) = 0;
		virtual void rectfill(const PMRect &r) = 0;
		virtual void rectstroke(const PMReal& x, const PMReal& y, const PMReal& width, const PMReal& height) = 0;
		virtual void rectstroke(const PMRect &r) = 0;
		virtual void rectpath(const PMReal& x, const PMReal& y, const PMReal& width, const PMReal& height) = 0;
		virtual void rectpath(const PMRect &r) = 0;
	/**
		This is similar to PostScript's shfill but using a shading
		paint server.

		This method is new for InDesign 3.0

		@see CAGMPaint
	*/
		virtual void shadingfill(AGMPaint* paint) = 0;

		virtual void AddComment(int32 comment, void *commentData, int32 length) = 0;

		// Return a reference to the port's draw manager instance.
		// Subclasses typically will have a draw manager concrete class as a data member, though details of
		// its construction and deployment are up to the class.
		virtual IDrawMgr *PortDrawMgr() = 0;

		// The following is only meant to pass auxiliary information, for a group of identical
		// graphical entities. It has a paired methods, for Begin/End context.
		// If a port does not support these methods, it should provide an empty stub.
		// A client of a port could take advantage of these methods to pass additional information
		// onto the port, where the port could simply punt the information, or use it to create
		// a more advanced representations of the graphical objects.
		virtual void BeginAuxInfoContext(GPortAuxInfoParam* auxInfoParam) = 0;
		virtual void EndAuxInfoContext(GPortAuxInfoParam* auxInfoParam) = 0;

		// Show method to match AGM. This is used to include searchable text in Export PDF.
		virtual void show( const CCTTextList& textList, int32 flags, const PMMatrix* matrix = 0 ) const = 0;

		/**
			Note that these values are defined the same as those in ICMSSettings; but ICMSSettings
			includes 'virtual' rendering intents that are not allowed in SetRenderingIntent.

			@see SetRenderingIntent
		*/
		typedef enum { kPerceptual, kSaturation, kRelative, kAbsolute } RenderingIntent;

		/**
			Sets the default rendering intent for any drawing that doesn't specify a particular
			rendering intent.  This default is part of gstate so is saved by gsave and restored
			by grestore.  By default the gstate intent is set to the document vector intent.

			@see IColorSpaceMgr
			@param intent: The new intent to use.
		*/
		virtual void SetRenderingIntent(RenderingIntent intent) = 0;

		/**
			Sets the overprint mode for the port.  This setting is part of gstate so is saved
			by gsave and restored by grestore.  By default the overprint mode is true (NZO).

			@param opm: True for non-zero overprint; false for full overprint.
		*/
		virtual void SetOverPrintMode(bool32 mode) = 0;
		
		/**
		 Fills the specified path using the current color server. Any path currently in the
		 gstate is ignored. In addition, the specified path is *not* added to the gstate. 
		 However, this will perform an implicit newpath.
		 
		 Note: The winding rule for the fill is taken from the path itself.
		 
		 @param path	The AGM path to fill
		 */
		virtual void FillPath(AGMPath *path) = 0;
		
		/**
		 Strokes the specified path using the current color server. Any path currently in the
		 gstate is ignored. In addition, the specified path is *not* added to the gstate. 
		 However, this will perform an implicit newpath.
		 
		 @param path	The AGM path to stroke
		 */
		virtual void StrokePath(AGMPath *path) = 0;

		/**
		 Adds the specified path to the clip in the gstate. Any path currently in the gstate 
		 is ignored. In addition, the specified path does *not* get added to the gstate. 
		 However, this will perform an implicit newpath.
		 
		 Note: The winding rule for the clip is taken from the path itself.

		 @param path	The AGM path to clip
		 */
		virtual void ClipPath(AGMPath *path) = 0;
};

#endif
