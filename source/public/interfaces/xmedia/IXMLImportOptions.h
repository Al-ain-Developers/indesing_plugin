//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportOptions.h $
//  
//  Owner: Bruce Linker
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
#ifndef __IXMLImportOptions__
#define __IXMLImportOptions__

#include "XMLID.h"
#include "IPMUnknown.h"

//========================================================================================
// CLASS IXMLImportOptions
//========================================================================================
/** Interface representing preferences for import. Use command of type kChangeXMLImportOptionsCmdBoss to change
	prefs rather than calling mutators on the interface on the session or doc workspaces.  
*/
class IXMLImportOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLIMPORTOPTIONS };

	/** Enumeration of ways that content can be imported.*/
	enum ImportStyle { /** */ kAppend = 0, /** */ kMerge, /** */ kPartial };


	/**	Determine whether importer should import into tree at selected node		
		@return bool16 kTrue if should import into selected item in structure
	 */
	virtual bool16 	GetImportIntoSelected() const = 0;

	/**	Mutator for property specifying whether to import into logical structure tree at selected node
		@param importIntoSelected 
	 */
	virtual void 	SetImportIntoSelected( bool16 importIntoSelected ) = 0;

	/**	Accessor for import style stored on this.
		@return  import style stored on this interface
	 */
	virtual ImportStyle	GetImportStyle() const = 0;

	/**	Mutator for import style stored on this interface
		@param importStyle new style to store
	 */
	virtual void 	SetImportStyle( ImportStyle importStyle ) = 0;

	/** Accessor for whether to import ruby with the W3C markup.
		If this is kTrue and the incoming XML with the W3C markup will be converted to 
		InDesign ruby. If this is kFalse, The ruby tag will remain as a normal tag.
		@return bool16 kTrue to import ruby
	*/
	virtual bool16	GetImportRuby(void) const = 0;

	/** Mutator for setting whether to import ruby with the W3C markup.
		@param importRuby kTrue if importing ruby.
	*/
	virtual void	SetImportRuby(bool16 importRuby) = 0;

	/**	Accessor indicating whether or not an import filter should be used.
		@return  import style stored on this interface
	 */
	virtual bool16	ShouldUseImportFilter() const = 0;

	/**	Mutator for setting whether of not to use an import filter.
		@param importStyle new style to store
	 */
	virtual void 	UseImportFilter( const bool16& useFilter = kTrue ) = 0;
	
	/**	Mutator, copy state from another preferences interface into this
		@param otherOptions interface to copy state from into this
	 */
	virtual void Copy( IXMLImportOptions* otherOptions ) = 0;
};


#endif
