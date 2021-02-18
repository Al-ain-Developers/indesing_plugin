//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IDocStructurePrefs.h $
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
#ifndef __IDocStructurePrefs__
#define __IDocStructurePrefs__

#include "XMediaUIID.h"
#include "IPMUnknown.h"

/** Class to manipulate the structure-view preferences. Persisted on session and in each document workspace.
	Change by using a  command (kChangeDocStructurePrefsCmdBoss) which takes UID of boss object with this interface as first
	and only thing in its item list.
*/
class IDocStructurePrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCSTRUCTUREPREFS };

	/**	Copy fields from another instance of this interface
		@param other The other interface to copy data from
	 */
	virtual void						CopyFields(IDocStructurePrefs* other) = 0;
	
	/** Determine whether the structure pane is shown in layout window?
		@return kTrue if structure-view visible, kFalse otherwise.
	*/
	virtual	bool16						StructureIsShown() const = 0;

	/**	Mutator for structure view visibility property
		@param showStructure kTrue if structure should be set visible, kFalse otherwise
	 */
	virtual	void						SetShowStructure(bool16 showStructure) = 0;


	/**	Accessor for width of structure view
		@return  current width of structure view preference
	 */
	virtual	PMReal						GetStructureWidth() const = 0;

	/**	Mutator for width of structure view
		@param structureWidth specify pixel width of the structure view
	 */
	virtual	void						SetStructureWidth( PMReal structureWidth ) = 0;

	/** Determine whether the Validation pane is shown in structure pane?
		@return kTrue if Validation-view visible, kFalse otherwise.
	*/
	virtual	bool16						StructureValidationIsShown() const = 0;

	/**	Mutator for Validation pane visibility property
		@param showStructureValidation kTrue if validation should be set visible, kFalse otherwise
	 */
	virtual	void						SetShowStructureValidation(bool16 showStructureValidation) = 0;


	/**	Accessor for height of validation view
		@return  current height of validation view preference
	 */
	virtual	PMReal						GetStructureValidationHeight() const = 0;

	/**	Mutator for height of validation view
		@param structureValidationHeight specify pixel height of the validation view
	 */
	virtual	void						SetStructureValidationHeight( PMReal structureValidationHeight ) = 0;
};


#endif
