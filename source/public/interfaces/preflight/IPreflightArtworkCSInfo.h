//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkCSInfo.h $
//  
//  Owner: Matt Phillips
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

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "GraphicTypes.h"
#include "BravoForwardDecl.h"

/** This interface is of use to preflight rule implementations; ie if you're writing a preflight 
	rule, you may need the data exposed in this interface. Otherwise you're not going to need this.

	Furthermore, this interface is related to rules that inspect artwork. Artwork is the term 
	used to refer to marking operations that are captured by the preflight engine and handed to
	rules for further inspection. To get to this information you ask to visit objects of preflight 
	class kPreflightOM_ArtworkMark in your IPreflightRuleVisitor::GetClassesToVisit() implementation.

	The group of artwork interfaces are nonpersistent interfaces that live on typically very short 
	lived bosses. The root object, kPreflightAtworkMarkBoss, is created by a call to 
	IPreflightObjectModel::QueryObject(), typically on your behalf via 
	IPreflightVisitInfo::QueryObject(), in your implementation of IPreflightRuleVisitor. From
	that root object you can query to get other kinds of objects.

	Here's the hierarchy of interfaces that live on an artwork marking boss, or are served up
	by those interfaces.

	kPreflightAtworkMarkBoss
		IPreflightObject
		IPreflightArtworkMarkInfo
			IPreflightArtworkPaintInfo (via QueryColorPaintInfo, QueryAlphaPaintInfo)
				IPreflightArtworkCSInfo (via QueryColorSpace)
					IPreflightArtworkCSInfo (via QueryBase, QueryProcess, etc)
			IPreflightArtworkImage (via Rasterize())
				IPreflightArtworkCSInfo (via QueryColorSpace)
		IPreflightArtworkShapeContext
		IPreflightArtworkTextContext
		IPreflightArtworkOPIContext
		IPreflightArtworkOPI
*/

class IPreflightArtworkCSInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKCSINFO };

	/** Basic Type. */
	typedef enum
	{
		kCS_Invalid,
		kCS_Other,

		kCS_Gray,
		kCS_RGB,
		kCS_CMYK,
		kCS_LAB,

		/** NChannel is a process space combined with spots. Use QueryBase to access the 
			base process space.
		*/
		kCS_NChannel,

		/** General DeviceN, meaning an arbitrary combination of spots and possibly 
			individual CMYK inks.
		*/
		kCS_DeviceN,

		/** An indexed (single channel) space which points to an array of values in
			another colorspace. Use QueryBase() to obtain information about the underlying space.
		*/
		kCS_Indexed,

		/** A pattern, which is a wrapped-up bit of artwork which itself may have different
			colorspaces and so on. This is generally opaque; none of the methods below will
			do much. However, patterns are auto-expanded into artwork so you can ignore this
			marking operation if you like and wait for the child artwork to arrive later.
		*/
		kCS_Pattern,
        kCS_HSB
	} Type;

	/** The categories in which a given channel corresponds. */
	typedef enum 
	{ 
		/** A process channel in a fully specified process space (or NChannel space). */
		kChannelTypeProcess,

		/** A spot channel (not process or CMYK individual channel). */
		kChannelTypeSpot,

		/** Registration (ie separation all) */
		kChannelTypeRegistration,

		/** An individual CMYK channel floating in a DeviceN space. */
		kChannelTypeCMYKInDeviceN,

		/** The alpha channel. */
		kChannelTypeAlpha,

		/** This can happen in some DeviceN cases such as [none] channels. */
		kChannelTypeInvalid
	} ChannelType;

public:

	/** This is used to initialize the interface. This takes an opaque type, so only 
		InDesign internal code can call or implement this method.

		@param cs IN The opaque colorspace object that this interface gives you information about.
	*/
	virtual void Initialize(CAGMColorSpace& cs) = 0;

	/** Return the colorspace type, if applicable.

		@return The colorspace type.
	*/
	virtual Type GetType() const = 0;

	/** For hierarchical types, return the underlying, or base, type. 
		For Indexed, returns the colorspace in which the index entries are stored (including NChannel).
		For NChannel, returns the process colorspace on which the NChannel is based.
		For all other types, returns nil.

		@return A refcounted CSInfo or nil if there is no base type.
	*/
	virtual IPreflightArtworkCSInfo* QueryBase() const = 0;

	/** If there's a process space in this or a child space, finds it and returns it.
		For simple process spaces, returns the same space. (But still refcounted.)
		For Indexed, recursively checks the base colorspace.
		For NChannel, returns the process colorspace on which the NChannel is based.
		If there is no base process space anywhere (for example, DeviceN), returns nil.

		@return A refcounted CSInfo or nil if there is no base process type.
	*/
	virtual IPreflightArtworkCSInfo* QueryProcess() const = 0;

	/** Returns a colorspace with specified alpha state. If the alpha state already matches
		the current alpha state, simply returns a refcounted pointer to this colorspace.
		Otherwise it creates a new colorspace with the specified alpha state and returns
		that.

		@param alpha The desired alpha state of the resulting colorspace.
		@return A refcounted CSInfo or nil if an error occurs.
	*/
	virtual IPreflightArtworkCSInfo* QueryCSWithAlphaState(bool alpha) const = 0;

	/** Returns a colorspace that's raster port safe. AGM doesn't support DeviceN or
		separation images, for example, so these are promoted to full NChannel. Indexed
		colorspaces use their base colorspace (which is then checked again for safe promotion).

		If the colorspace is already safe (and with the same alpha), returns a refcounted
		same-interface pointer.

		@param alpha The desired alpha state of the resulting colorspace.
		@return A refcounted CSInfo or nil if there is no way to make this colorspace raster safe.
			Examples of the latter are pattern, invalid, kOther.
	*/
	virtual IPreflightArtworkCSInfo* QueryCSRasterPortSafe(bool alpha) const = 0;

	/** Return the total number of channels (color + alpha). 
		For information regarding subsets, eg the channels, or spot channels:
		@see 

		@return The number of channels in the paint operation.
	*/
	virtual uint32 GetNumChannels() const = 0;

	/** Get the alpha channel index, if there is one.
		@return The index of the alpha channel, or -1 if there is no alpha channel.
	*/

	/** Get the map for the color channels -- that is all the channels *except* the alpha
		channel, if there is one.

		@return The vector containing channel indices of color channels.
	*/
	virtual const K2Vector<int32>& GetColorChannelsMap() const = 0;

	/** Get the map for the process channels. This works on process colorspaces and NChannel
		colorspaces. The map will have the same number of channels as the process (or base
		process, in the case of NChannel) space. Each entry in the map is the channel index of
		the corresponding process space. For example for RGB+Spot NChannel, map[0] gives you
		the channel number corresponding to the Red channel. If the colorspace is ARGB then
		this would be 1.

		@return The vector containing channel indices of process channels. Note that this 
			is a const reference for maximum performance. Be careful of the scope; if you
			need to hold onto it for a while, be sure to assign it to a properly scoped
			variable.
	*/
	virtual const K2Vector<int32>& GetProcessChannelsMap() const = 0;

	/** Get the map of the channel indices of the CMYK channels. The resulting array will
		have four color values corresponding to cyan, magenta, yellow, and black. A value of -1
		indicates that there is no corresponding channel; otherwise it is the index of the 
		corresponding channel for that colorant.

		@return The vector containing 4 channel indices of CMYK channels; some entries
			may be -1 if there is no mapping for that CMYK channel. Note that this 
			is a const reference for maximum performance. Be careful of the scope; if you
			need to hold onto it for a while, be sure to assign it to a properly scoped
			variable.
	*/
	virtual const K2Vector<int32>& GetCMYKChannelsMap() const = 0;

	/** Get the map for the spot channels -- that is, the channels in the colorspace that
		correspond to non-process channels. This does *not* include the CMYK channels if any;
		nor does it include a registration channel.

		@return The vector containing channel indices of spot channels. Note that this 
			is a const reference for maximum performance. Be careful of the scope; if you
			need to hold onto it for a while, be sure to assign it to a properly scoped
			variable.
	*/
	virtual const K2Vector<int32>& GetSpotChannelsMap() const = 0;

	/** Get the map for the registration channel. This will be of size zero if there is no
		registration channel, else of size 1 with the single element being the channel index
		of the registration data.

		@return The vector containing channel indices of spot channels. Note that this 
			is a const reference for maximum performance. Be careful of the scope; if you
			need to hold onto it for a while, be sure to assign it to a properly scoped
			variable.
	*/
	virtual const K2Vector<int32>& GetRegistrationChannelsMap() const = 0;

	/** Get information on a particular channel.

		@param n The (0 based) index of the channel you want to examine.
		@param index If not nil, receives the corresponding index based on the returned type.
			For kChannelTypeProcess, receives the index into the process space (eg for RGB,
			1 = Green). For kChannelTypeCMYKInDeviceN, the index is the CMYK index.
		@return The channel type.
	*/
	virtual ChannelType GetNthChannelInfo(uint32 n, int32* index = nil) const = 0;

	/** For DeviceN colorspaces, returns the name of the colorant.
		@note Applies only for GetColorSpaceType() == kPaintCS_DeviceN.
		@param n The (0 based) index of the channel you want to examine.
		@return The name of the colorant.
	*/
	virtual WideString GetNthChannelName(uint32 n) const = 0;

	/** Get the number of entries in an indexed color type space.
		@return The number of entries, or 0 if it's not an indexed space.
	*/
	virtual uint32 GetIndexedNumEntries() const = 0;

	/** Get the Nth index colors. Note that QueryBase() will give you the space you need to 
		interpret the array.

		@param n IN The index of the entry you want.
		@param vals OUT Receives the array of color values.
	*/
	virtual void GetIndexedNthEntry(int32 n, K2Vector<PMReal>& vals) const = 0;

	/** Get the internal/private CAGMColorSpace. This is for internal use only.
		@param spc OUT The smart pointer to fill with the colorspace.
	*/
	virtual void GetColorSpace(CAGMColorSpace& spc) const = 0;
};

