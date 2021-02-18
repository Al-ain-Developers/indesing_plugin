//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionPresetUtils.h $
//  
//  Owner: SusanCL
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#include "DynamicDocumentsID.h"
#include "InstStrokeFillID.h"

#include "WideString.h"
#include "Utils.h"
#include "PMPathPoint.h"

class IMotionPresetMgr;
class IMotionPresetData;
class IAnimationCore;
class ISubject;
class IScriptRequestData;
class IScript;
class GraphicsData;

const PMReal kMotionPathLineWeight = 1.0;
const PMReal kMotionPathDotsWeight = 1.5;
const ClassID kMotionPathArrowHeadBoss = kBarbedArrowHeadBoss;
const ClassID kMotionPathCircleBoss = kCircleSolidArrowHeadBoss;

class IMotionPresetUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOTIONPRESETUTILS };
		
		/** Returs the motion preset manager for the specified database.
			@param iDB is the data base 
			@return IMotionPresetMgr for the specified database.
		*/
		virtual IMotionPresetMgr* QueryMotionPresetManager (IDataBase* iDB = nil) const = 0;
		
		/** Copy motion preset data.
			@param iSrcPreset is the source preset data to copy from.
			@param iDstPreset is the preset to which the data is to be copied. If iDstPreset does not have
			edit privilege, then nothing is copied.
		*/
		virtual ErrorCode CopyMotionPresetData (const IMotionPresetData* iSrcPreset, IMotionPresetData* iDstPreset) const = 0;

		/** Returns the motion preset data for the given page item's which animation.
			@param pageItemRef is the page item.
			@param whichAnimation is the nth animation attached to the page item.
			@return the motion preset data interface for this page item.
		*/
		virtual IMotionPresetData* QueryPageItemPresetData (const UIDRef& pageItemRef, int32 whichAnimation) = 0;

		/** Returns the animation data for the given page item.
			@param pageItemRef is the page item.
			@param whichAnimation is the nth animation attached to the page item.
			@return the animation attribute data for this page item.
		*/
		virtual IPMUnknown* QueryPageItemAnimationData (const UIDRef& pageItemRef) = 0;

		/** Returns the motion preset UID for the specified pageitem's which animation.
			@param pageItemRef is the page item.
			@return the motion preset UID.
		*/
		virtual UID GetPageItemAnimationPresetUID (const UIDRef& pageItemRef) const = 0;

		/** Returs the animation object for the specified motion preset.
			@param presetRef is the motion preset. If it is null, then an empty animation object is created.
			@return the animation object for the specified motion preset.
		*/
		virtual IAnimationCore* CreateAnimationCore (const UIDRef& presetRef = UIDRef::gNull) = 0;

		/** Sets the motion preset's name and description
			@param presetRef is UIDRef of the preset to change.
			@param doSetName is true is setting a new name
			@param newName is new name for the preset.
			@param doSetDescription is true is setting a new description
			@param newDescription is new description for the preset.
			@return the error code.
		*/
		virtual ErrorCode SetMotionPresetSettings (const UIDRef& presetRef, bool doSetName, const PMString& newName, 
			bool doSetDescription, const PMString& newDescription) = 0;
		
		/** Construct the motion xml data from the specified motion preset data.
			@param rawString is the motion preset data. It's the preset's xml description.
			@param xmlBuffer is the shared buffer containing the motion xml data.
			@param size is the size of the buffer
			@return kSuccess or an error code.
		*/
		virtual ErrorCode ConstructMotionXMLDataFromMotionData (const WideString& rawString, boost::shared_ptr<uint8>& xmlBuffer, size_t& size) = 0;

		/** Validate the given preset name
			@param iPresetMgr is the motion preset manager to validate against.
			@param presetName is the preset name to validate.
			@return kSuccess otherwise an error code.
		*/
		virtual ErrorCode ValidatePresetName (IMotionPresetMgr* iPresetMgr, const PMString& presetName) const = 0;
		
		/**	Query the preset manager's workspace subject
			@param iDB is the workspace database.
			@return the pointer to ISubject for the preset manager subject
		*/
		virtual ISubject* QueryPresetWorkspaceSubject (IDataBase* iDB) const = 0;

		/**	Query for the preset manager from the specified IScript.
			@param data is the script reset data. This is need to establish the request context.
			@param script is the script interface interested.
			@return the pointer to IMotionPresetMgr.
		*/
		virtual IMotionPresetMgr* QueryMotionPresetManagerFromScript (const IScriptRequestData* data, IScript* script) const = 0;

		/** Given an item interface, fill in a list of PMPathPoints for its easing path and motion path.
			The points are returned in "flash" coordinate space. This means aligned with the spread, with the 0, 0
			point at the upper left of the page item, and 72dpi. The animation offset has not yet been applied.
			Will return empty lists of item doesn't have motion data associated with it.
			@param pageItemRef [IN] is the UIDRef of the page item with motion data.
			@param motionPath [OUT] A list of PMPathPoints representing the motion path
			@param easingPath [OUT] A list of PMPathPoints representing the easing path
			@see FlashToInnerMatrix to convert from "flash" coordinates to inner coordinates for the page item.
		 */
		virtual void GetMotionPathPoints(const UIDRef& pageItemRef, PMPathPointList& motionPath, PMPathPointList& easingPath) = 0;

		/** Given an item interface that has motion applied, return a matrix that will map to inner coordinates for the item.
			The offset point (GetPageItemAnimationTransformOffsetPoint) is taken into account.
			@param pageItemRef [IN] is the UIDRef of the page item with motion data.
			@return PMMatrix a matrix that will map to inner coordinates for the item.
			@see FlashToInnerMatrix to convert from "flash" coordinates to inner coordinates for the page item.
			@see GetMotionPathPoints, typically this matrix could be applied to the points in order to draw, hittest, etc.
		 */
		virtual PMMatrix FlashToInnerMatrix(const UIDRef& pageItemRef) = 0;

		/** Given an item interface, draw its motion paths for "motion" and "easing".
			@param gd [IN] The graphics data to draw to
			@param pageItemRef [IN] is the UIDRef of the page item with motion data.
		 */
		virtual void DrawMotionPaths(GraphicsData* gd, const UIDRef& pageItemRef) = 0;

		/** Given a list of path points for the motion path, create the path using the graphics data.
			Caller must still call gPort->stroke()
			@param gd [IN] The graphics data to draw to
			@param motionPath [IN] A list of PMPathPoints for the easing path
		 */
		virtual void CreateMotionPath(GraphicsData* gd, const PMPathPointList& motionPath) = 0;

		/** Given a list of path points for the easing path, create the path using the graphics data.
			Caller must still call gPort->stroke()
			@param gd [IN] The graphics data to draw to
			@param easingPath [IN] A list of PMPathPoints for the easing path
		 */
		virtual void CreateEasingPath(GraphicsData* gd, const PMPathPointList& easingPath) = 0;

		/** Given a preset name, return the group name that it resides. The group name may be empty
			indicating the preset does not belong to a group or that it was not found in the current
			list of presets.
			@param presetName [IN] is the preset name.
			@param presetGroupName [OUT] is the preset's group name.
			@return bool whether or not the preset name was found.
		*/
		virtual bool GetPresetGroupName(const PMString& presetName, PMString& presetGroupName) = 0;
};
