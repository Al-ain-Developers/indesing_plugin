//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpGraphicHelper.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __SnpGraphicHelper_H_DEFINED__
#define __SnpGraphicHelper_H_DEFINED__


class IApplyMultAttributesCmdData;
class UIDList;
class UIDRef;
class IImageDataAccess;
/** Helper methods to perform basics of manipulating graphics.

	Graphic attributes control how a path is drawn.

	Graphic attributes have a common parent boss class kGraphicsAttrBoss and have the signature
	interface IGraphicAttributeInfo. Check out the documentation page for interface IGraphicAttributeInfo
	for a list of all graphic attributes supported by the API.
			
	The attributes applied to a page item can be accessed via the item's IGraphicStyleDescriptor interface.

	IGraphicAttributeUtils is a facade that helps create, apply and detect graphic attributes.
	It provides helpers for the most common attributes like stroke weight, stroke and fill colour.
	If there is no wrapper method provided to create the graphic attribute you are interested in
	you need to use CreateObject a boss object of the necessary class and fill out its data 
	interfaces. The sample code that deals with kDashedAttributeValuesBoss below shows an example
	of this.

	kGfxApplyMultAttributesCmdBoss is a command that allows you to apply graphic attributes to
	a page item. You can apply as many attributes as you want by processing this command.

	@ingroup sdk_common
	@see IGraphicAttributeUtils
	@see kGfxApplyMultAttributesCmdBoss
	@see IApplyMultAttributesCmdData
	@see IGraphicAttributeInfo
	@see IGraphicStyleDescriptor
*/
class SnpGraphicHelper
{
	public:
		/** Constructor.
			@param itemList identifies the items the helper will target.
		*/
		SnpGraphicHelper(const UIDList& itemList);

		/** Constructor.
			@param itemRef identifies a single item the helper will target.
		*/
		SnpGraphicHelper(const UIDRef& itemRef);

		/** Destructor
		*/
		virtual ~SnpGraphicHelper();

	public:

		/**	Apply the graphic attributes. Use the method like this:

			SnpGraphicHelper graphicsHelper(itemList);
			graphicsHelper.AddStrokeWeight(4.0);
			UID swatchUID = graphicsHelper.GetNamedSwatch(PMString("Black"), itemList.GetDataBase());
			graphicsHelper.AddStrokeRendering(swatchUID);
			graphicsHelper.ApplyAttributes();

			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode	ApplyAttributes();

		/**	Reset the items the helper will target, call this when
			you want to use a single instance of SnpGraphicHelper to target 
			different items.
			@param itemList identifies the items the helper will target.
		 */
		void Reset(const UIDList& itemList);

		/**	Reset the item the helper will target, call this when
			you want to use a single instance of SnpGraphicHelper to target 
			a different item.
			@param itemRef identifies a single item the helper will target.
		 */
		void Reset(const UIDRef& itemRef);

		/** Controls stroke weight.
			@param strokeWeight desired stroke weight.
		 */
		void	AddStrokeWeight(const PMReal& strokeWeight);

		/**	Get the named swatch's UID from the specified database.
			@param swatchName the swatch name.
			@param iDataBase the database to check.
			@return swatch UID of the specified swatch name, kInvalidUID if not found.
			@see ISwatchUtils.
		*/
		virtual UID GetNamedSwatch(const PMString& swatchName, IDataBase* iDataBase);

		/**	Controls stroke colour. Note if the stroke has no colour it won't get rendered.
			@param swatchUID specifies the swatch (use ISwatchUtils or SnpGraphicHelper::GetNamedSwatch
				to locate the swatch you want to use).
		 */
		void	AddStrokeRendering(const UID& swatchUID);

		/**	Controls fill colour.
			@param swatchUID specifies the swatch (use ISwatchUtils or SnpGraphicHelper::GetNamedSwatch
				to locate the swatch you want to use).
		 */
		void	AddFillRendering(const UID& swatchUID);

		/**	Controls corner effect drawing (rounded, fancy, bevelled, etc.). Corner effects are drawn 
			by boss classes that aggregate an IPathCorner interface.
			@param pathCornerClassID type of corner effect (see IPathCorner).
		 */
		void	AddCornerImplementation(const ClassID& pathCornerClassID);

		/**	Controls radius of corner effect.
			@param cornerRadius radius in points the corner effect should draw with.
			@see SnpGraphicHelper::AddCornerImplementation
		 */
		void	AddCornerRadius(const PMReal& cornerRadius);

		/**	Controls whether path draws as a solid, dashed or dotted line or another custom line effect.
			Paths are drawn by boss classes that aggregate an IPathStroker interface.
			@param pathStrokerClassID type of stroker (see IPathStroker).
		 */
		void	AddLineImplementation(const ClassID& pathStrokerClassID);

		/**	Controls line end effects like arrowheads and circles. Path ends are drawn by boss classes 
			that aggregate an IPathEndStroker interface.
			@param pathEndStrokerClassID type of path end stroker.
		 */
		void	AddLineEndEndImplementation(const ClassID& pathEndStrokerClassID);

		/** Available line join types.
		 */
		enum	JoinType {kJTMiter, kJTRound, kJTBevel};

		/**	Controls how line joins draw.
			@param joinType 
		 */
		void	AddJoinType(const SnpGraphicHelper::JoinType joinType);

		/** Available line caps.
		 */
		enum	LineCap {kLCButt, kLCRound, kLCSquare};

		/**	Controls how the end of lines draws.
			@param lineCap 
		 */
		void	AddLineCap(const SnpGraphicHelper::LineCap lineCap);

		/**	Controls the lengths of dashes and gaps when drawing dashed lines.
			@param dashAndGapValues index 0 gives length of dash, index 1 gives length of gap.
		 */
		void	AddDashedValues(const K2Vector<PMReal>& dashAndGapValues);

		/** Query graphic page item of a single graphic frame or item.
			Note: if the helper is constructed with multiple items, only the first item is returned
			@return pointer to the graphic item.
		*/
		IImageDataAccess * QueryImageDataAccess();

		/** Get graphic frame of a single graphic frame or item.
			Note: if the helper is constructed with multiple items, only the first frame is returned

			@return UIDRef of the graphic frame.
		*/
		UIDRef GetGraphicFrame();



	private:

		/** Add an unknown graphic attribute.
			@param unknown graphic attribute.
		 */
		void	AddAnAttribute(IPMUnknown* attribute);
		
	private:
		UIDList fItemList;
		InterfacePtr<IApplyMultAttributesCmdData> fIApplyMultAttributesCmdData;

};

#endif //  __SnpGraphicHelper_H_DEFINED__

//End, SnpGraphicHelper.h
