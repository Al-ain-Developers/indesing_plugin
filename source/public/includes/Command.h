//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Command.h $
//  
//  Owner: EricM
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
#ifndef __COMMAND__
#define __COMMAND__

#include "ICommand.h"
#include "HelperInterface.h"

#include "UIDList.h"
class IResourceAccess;

#pragma export on
/**	Base class for implementing ICommand. If you are defining a new command, inherit
	from this class. To implement a new command:

	Define a boss in your plug-in that provides a command, for instance:

	<pre>
Class 
{
	kYourCmdBoss,
	kInvalidClass,
	{
		IID_ICOMMAND,	kYourCmdImpl,
		IID_IYOURDATA,	kYourDataImpl,
	}
},
	</pre>

	If you require to pass additional parameters to your command
	aggregate data interfaces on your command boss.
	For example, you could implement a custom data interface,
	IYourData as shown above. Or you could re-use a data interface
	provided by the API.

	Provide an implementation of the ICommand interface, for instance:

	<pre>
class YourCmd : public Command
{
public:
	YourCmd(IPMUnknown* boss);
	~YourCmd();

protected:
	void Do();
	void DoNotify();
	PMString* CreateName();
};

CREATE_PMINTERFACE(YourCmd, kYourCmdImpl)
// Define bodies for your methods.
	</pre>

	Add REGISTER_PMINTERFACE macro calls to your plug-in's FactoryInterface.h file and
	add IDs to your your ID.h file. For example:
<pre>
DECLARE_PMID(kClassIDSpace, kYourCmdBoss, kYourPrefix + xx)	
DECLARE_PMID(kInterfaceIDSpace, IID_IYOURATA, kYourPrefix + xx)
DECLARE_PMID(kImplementationIDSpace, kYourCmdImpl, kYourPrefix + xx)	
DECLARE_PMID(kImplementationIDSpace, kYourDataImpl, kYourPrefix + xx)
</pre>

	Once you've done all this, you can add code to your plug-in that
	processes your new command using CmdUtils.

	@see ICommand
	@see IIntData, IBoolData, IRealNumberData, IStringData, IStringListData,
		IUIDData, IUIDListData, IUIDRefListData
	@see IErrorStringService

	@ingroup arch_cmd
	@ingroup arch_db
*/
class PUBLIC_DECL Command : public ICommand {
public:
	enum CommandDummyArg { kItemList = 1 };

	Command(IPMUnknown *boss);
	virtual ~Command();
	
	virtual void GetName(PMString *name) const;
	virtual void SetName(const PMString& newName);
	virtual bool16 IsNameRequired() const;
			
	virtual const UIDList* GetItemList() const;
	virtual const UIDList &GetItemListReference() const;
	virtual void SetItemList(const UIDList &newItemList);
		
	virtual void DoImmediate(bool16 isDynamic = kFalse);
	virtual void LWDoImmediate();
 	

	/** DEPRICATED
		Avoid using this function if possible - this is legacy and is deprecated.
	*/
	virtual void DoDynamic();	

	virtual CommandState GetCommandState() const;
	virtual bool16 IsDone() const;
	virtual bool16 CanJoin( const ICommand *pNewCmd )const;

	virtual void SetCreatorID(int32 creatorID);
	virtual int32 GetCreatorID() const;
	
	virtual bool16 LowMemIsOK() const;
	
	virtual const Target &GetTarget() const;	
	
	virtual Undoability GetUndoability() const;
	virtual void SetUndoability(Undoability newUndoability);

	virtual void SetActive(bool16 isActive);
	virtual bool16 IsActive() const;
	
	virtual bool8 IsLWProcessed() const;

protected:
	// If you are considering making any of these methods public
	// instead of protected... please let me know.  - Zak
	
	/**	Changes the model and must be defined by all commands. 
		If you encounter an error condition within your Do method 
		you normally set the global error code and return.
		@see ErrorUtils::SetPMGlobalErrorCode
	 */
	virtual void Do() = 0;
		// Executes the command, causing changes to the model.
		//
		// This must be overridden by each command.  This method
		// is only called by ExecuteImmediate(), which also sets
		// the command state and calls DoNotify().

	/**	Initiates notification, commands that want to perform notification
		define this method. It is called after the Do method has been
		called.
		@see ISubject
	 */
	virtual void DoNotify();

	/**	Sets the command state.
		@param state 
	 */
	virtual void SetCommandState(CommandState state);

	/**	Returns the name that appears in undo or redo menu items to identify this command.
		@return the name of the command 
	 */
	virtual PMString *CreateName();
			
	/**	Sets up the target, the database that contains the objects
		changed by the command. Define if your command has a target 
		that is not known at construction time and is not equivalent
		to the database passed in the command's item list when the command
		is processed.
		@see Command::SetTarget
	 */
	virtual void SetUpTarget();

	/**	Verification is called from SetCommandState as the command changes state.  PreVerify
		is called as the command changes to kNotDone.  PostVerify
		is called as the state changes to kDone.  Verification
		routines should verify the particular  state of an object or document when a change
		is completed and assert if there is something wrong.  Possible additions to this
		mechanism is the ability to "turn off" verification under certain circumstances.
		Verification is only called for debug builds.  [LDM]
		@param state 
	 */
	virtual void PreVerify(CommandState state);

	/**	See Command::PreVerify.
		@param state 
	 */
	virtual void PostVerify(CommandState state);

	/**	Identifies a pre-defined target database that contains
		the objects to be changed by a command.
	 */
	typedef enum
	{
		/**	Changes objects that persist in application defaults (kWorkspaceBoss) */
		kSessionWorkspaceTarget,
		/**	Changes objects that persist in SavedData */
		kSessionTarget
	} PredefinedTarget;	

	/**	See Command::SetTarget(IDataBase*).
		@param newTarget 
	 */
	void SetTarget(const Target &newTarget);

	/**	See Command::SetTarget(IDataBase*).
		@param newTarget 
	 */
	void SetTarget(PredefinedTarget newTarget);

	/**	Call this method from your constructor or your SetUpTarget method
		if the target of your command is not equivalent to the command manager
		of the database of the command's item list at the time of processing.
		@param db 
	 */
	void SetTarget(IDataBase *db);

	/** The command's item list.
	*/
	UIDList fItemList;

#ifdef ID_ENABLE_DEBUGGING
	enum Action { kDoAbsolutelyNothing, kDo} ;
	void LogCommand( Action act ) ;
#endif

private:
	mutable PMString *fName;
	
	CommandState fCommandState;
	int32 fCreatorID;

	Undoability fUndoability;
	bool16 fIsActive;
	UIDRef fTarget;
	// will go away
	bool8 fIsLWProcessed;	
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif 	// __COMMAND__

