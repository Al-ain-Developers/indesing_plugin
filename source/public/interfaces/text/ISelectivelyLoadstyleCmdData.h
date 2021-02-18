//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISelectivelyLoadstyleCmdData.h $
//  
//  Owner: sasatte
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
#ifndef __ISelectivelyLoadStyleCmdData__
#define __ISelectivelyLoadStyleCmdData__

#include "IPMUnknown.h"
#include "IDocument.h"
#include "TextID.h"
#include "StyleClashResolutionTypes.h"

#include <map>
/******************************************************************************
 *                                   HEADER
 ******************************************************************************/

/**
	ISelectivelyLoadStyleCmdData is an interface for getting/setting/modifying the data needed for
	selectively loading styles.
*/

class ISelectivelyLoadStyleCmdData : public IPMUnknown
{
public:
	enum  { kDefaultIID = IID_ISELECTIVELYLOADSTYLECMDDATA };

	/**
		The choices for loading styles
	*/
	enum LoadChoice
    {
		/** Load Paragraph styles */
        kLoadParagraphStyles = 0,
		/** Load Character styles */
        kLoadCharacterStyles,
		/** Load both Paragraph and Character styles */
        kLoadParaCharStyles,
		/** Load Object styles */
		kLoadObjectStyles,
		/** Load Text Variables */
		kLoadTextVariableTable,
        
        /** Load Table styles */
        kLoadTableStyles,
		/** Load Cell styles */
        kLoadCellStyles,
		/** Load both Table and Cell styles */
        kLoadTableCellStyles,
        
	};

	/**	Sets the Load Style Command Data
		@param importStatusMap		map of "Style name" and import status of this style
		@param clashStatusMap		map of "Style name" and clash status of this style
		@param resolveClashStrategy map of "Style name" and strategy to resolve clash for this style
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		SetLoadStyleCmdInfo(const std::map<PMString, bool32>& importStatus, const std::map<PMString, bool32>& clashStatus, const std::map<PMString, StyleClashResolutionTypes::StyleClashResolutionStrategy>& resolveClashStrategy, PMIID styleProtocol/*bool32 IsParagraphStyle*/) = 0;

	/**	Gets the Load Style Command Data
		@param importStatusMap		OUT map of "Style name" and import status of this style
		@param clashStatusMap		OUT map of "Style name" and clash status of this style
		@param resolveClashStrategy OUT map of "Style name" and strategy to resolve clash for this style
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		GetLoadStyleCmdInfo(std::map<PMString,bool32>& importStatusMap, std::map<PMString,bool32>& clashStatusMap, std::map<PMString,StyleClashResolutionTypes::StyleClashResolutionStrategy>& resolveClashStrategy, PMIID styleProtocol) = 0;

	/**	Sets the Import Status of strStyleName to status
		@param strStyleName			"Style name"
		@param status				Import status of strStyleName
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		SetImportStatus(const PMString& strStyleName, const bool32 status, PMIID styleProtocol) = 0;

	/**	Gets the Import Status of strStyleName
		@param strStyleName			"Style name"
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
		@return						Import status of strStyleName
	 */
	virtual bool32  	GetImportStatus(const PMString& strStyleName, PMIID styleProtocol) const = 0;

	/**	Sets the Import Status of All Styles to status
		@param status				Import status
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		SetAllImportStatus(bool32 status, PMIID styleProtocol) = 0;

	/**	Sets the strategy to resolve clash of strStyleName to status
		@param strStyleName			"Style name"
		@param status				strategy to resolve clash of strStyleName
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		SetResolveClashStrategy(const PMString& strStyleName, const StyleClashResolutionTypes::StyleClashResolutionStrategy status, PMIID styleProtocol) = 0;

	/**	Gets the strategy to resolve clash of strStyleName
		@param strStyleName			"Style name"
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
		@return						strategy to resolve clash of strStyleName
	 */
	virtual StyleClashResolutionTypes::StyleClashResolutionStrategy		GetResolveClashStrategy(const PMString& strStyleName, PMIID styleProtocol) const = 0;

	/** Reset the Load Style Command Data
	*/
	virtual void		ResetLoadStyleCmdInfo() = 0;

	/**	Sets the Source Document
		@param doc		Source Document
	 */
	virtual void		SetSourceIDDoc(IDocument* doc) = 0;

	/**	Gets the Source Document
		@return 		Source Document
	 */
	virtual IDocument*  GetSourceIDDoc() const = 0;

	/**	Set if User Cancelled
		@param UserCancelled		user cancelled choice
	 */
	virtual void		SetUserCancelled(bool32 UserCancelled) = 0;

	/**	Get if User Cancelled
		@return 		whether user cancelled
	 */
	virtual bool32 		GetUserCancelled() const = 0;

	/**	Set Global Clash Resolution Strategy
		@param val		option for Global Clash Resolution Strategy
	 */
	virtual void	SetGlobalClashResolutionStrategy(const StyleClashResolutionTypes::GlobalClashResolutionStrategy val) = 0;

	/**	Get Global Clash Resolution Strategy
		@return 		current Global Clash Resolution Strategy
	 */
	virtual	StyleClashResolutionTypes::GlobalClashResolutionStrategy	GetGlobalClashResolutionStrategy() const = 0;

	/**	Gets the Clash Status of styleName
		@param styleName			"Style name"
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
		@return						Clash status of styleName
	 */
	virtual bool32		GetStyleClashStatus(const PMString styleName, PMIID styleProtocol) const = 0;

	/**	Sets the Auto styleName Map
		@param AutoStyleNameMap		map of stylename1 and stylename2 (where stylename1 in source document is
									mapped to stylename2 in destination document)
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		SetAutoStyleNameMap(const std::map<PMString,PMString>& AutoStyleNameMap, PMIID styleProtocol) = 0;

	/**	Gets the Auto styleName Map
		@param AutoStyleNameMap		OUT map of stylename1 and stylename2 (where stylename1 in source document is
									mapped to stylename2 in destination document)
		@param styleProtocol		protocol to use (for example : IID_IPARASTYLEGROUPMANAGER, IID_ICHARSTYLEGROUPMANAGER or IID_IOBJECTSTYLEGROUPMANAGER)
	 */
	virtual void		GetAutoStyleNameMap(std::map<PMString,PMString>& AutoStyleNameMap, PMIID styleProtocol) const = 0;

	/**	Sets the types of styles to load
		@param loadStyleTypes		vector of protocols to load
	 */
	virtual void            SetLoadStyleTypes(const K2Vector<PMIID>& loadStyleTypes) = 0;

	/**	Gets the types of styles to load
		@return loadStyleTypes		vector of protocols to load
	 */
	virtual K2Vector<PMIID> GetLoadStyleTypes() const = 0;


	/**	Sets the Style matching Strategy, This choice is not on per style type basis. If set then this will
		be used for all the style types for that load style command. 
		@note This value will be only used if the global clash resolution strategy is 
			StyleClashResolutionTypes::kLoadAllWithOverwrite or Individual styles resolve strategy is 
			StyleClashResolutionStrategy::kUseIncomingStyleDefinition. In all other cases style's full path 
			will be used for matching the styles in target.
		@param styleMatchingStrategy [IN] To find the clashing style in target, Uses full path of style if kMatchStyleFullPath is passed
									   if kMatchStyleName is passed then matches style with the same name at any location if the style
									   is unique in target. if same name style exist in more then one location then falls back to matching
									   styles path.
	 */
	virtual void	SetStyleMatchingStrategy(StyleClashResolutionTypes::StyleMatchingStrategyEnum styleMatchingStrategy) = 0;

	/** Return the style matching method. 
		@return the style matching method set via SetStyleMatchingMethod.
	*/
	virtual StyleClashResolutionTypes::StyleMatchingStrategyEnum		GetStyleMatchingStrategy () const = 0;

};

#endif
