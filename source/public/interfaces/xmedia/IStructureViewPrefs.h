//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IStructureViewPrefs.h $
//  
//  Owner: Matt Joss
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
#ifndef __IStructureViewPrefs__
#define __IStructureViewPrefs__

#include "XMediaUIID.h"
#include "IPMUnknown.h"

/** Preferences for the window displaying the logical structure, persisted on session workspace. */
class IStructureViewPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTRUCTUREVIEWPREFS };

	

	/**	Detemine if displaying attributes in the tree?
		
		@return  kTrue if the attributes should be shown, kFalse otherwise
	 */
	virtual	bool16						ShowAttributes() const = 0;

	/**	Specify whether to show attributes
		@param displayRoot specifies whether the attributes should be shown
	 */
	virtual	void						SetShowAttributes(bool16 displayRoot) = 0;

	/**	Detemine if displaying comments in the tree?
		
		@return  kTrue if the comments should be shown, kFalse otherwise
	 */
	virtual	bool16						ShowComments() const = 0;

	/**	Specify whether to show comments
		@param displayRoot specifies whether the comments should be shown
	 */
	virtual	void						SetShowComments(bool16 displayRoot) = 0;

	/**	Detemine if displaying processing instructions in the tree?
		
		@return  kTrue if the processing instructions should be shown, kFalse otherwise
	 */
	virtual	bool16						ShowPIs() const = 0;

	/**	Specify whether to show processing instructions
		@param displayRoot specifies whether the processing instructions should be shown
	 */
	virtual	void						SetShowPIs(bool16 displayRoot) = 0;

	/**	Determine if text snippets currently shown
		
		@return  kTrue if the snippets should be shown, kFalse otherwise
	 */
	virtual	bool16						ShowTextSnippets() const = 0;

	/**	Specify whether to show Text Snippets in the tree?
		@param showTextSnippets 
	 */
	virtual	void						SetShowTextSnippets(bool16 showTextSnippets) = 0;

	/**	Copy state from another IStructureViewPrefs interface
		@param other specifies other interface to copy state from
	 */
	virtual	void 						Copy(IStructureViewPrefs* other) = 0;
};


#endif
