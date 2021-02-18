//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelFactoryList.h $
//  
//  Owner: robin briggs
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
//  Plugin
//  
//========================================================================================

		REGISTER_PMINTERFACE(SpellMenuComponent, kSpellMenuComponent)			
		REGISTER_PMINTERFACE(SpellCheckWalkerClient, kSpellCheckClientImpl)

		// Button Observer		
		// REFERENCE_PMINTERFACE( SpellServiceObserver )
		// REFERENCE_PMINTERFACE( SpellCorrectObserver )
		// REFERENCE_PMINTERFACE( SpellAddRemoveObserver )
		REGISTER_PMINTERFACE(SpellIgnoreObserver, kSpellIgnoreObserver)
		// REFERENCE_PMINTERFACE( SpellCheckObserver )
		REGISTER_PMINTERFACE(SpellSkipObserver, kSpellSkipObserver)
		REGISTER_PMINTERFACE(SpellAddToListObserver, kSpellAddToListObserver)
		REGISTER_PMINTERFACE(SpellChangeObserver, kSpellChangeObserver)
		REGISTER_PMINTERFACE(SpellChangeAllObserver, kSpellChangeAllObserver)
		REGISTER_PMINTERFACE(SpellPreviousObserver, kSpellPreviousObserverImpl)

		// Editbox Observer		
		REGISTER_PMINTERFACE(SpellWordObserver, kSpellWordObserver)
		REGISTER_PMINTERFACE(SpellWordEventHandler, kSpellWordEventHandler)
		REGISTER_PMINTERFACE(SpellMisspelledObserver, kSpellMisspelledObserver)
		REGISTER_PMINTERFACE(SpellMisspelledEH, kSpellMisspelledEH)

		// Checkbox Observer
		// REFERENCE_PMINTERFACE( SpellBackgroundObserver )
		// REFERENCE_PMINTERFACE( SpellWrapObserver )	
		// REFERENCE_PMINTERFACE( SpellOversetObserver )	
		
		// Popup Observer
		REGISTER_PMINTERFACE(SpellScopeObserver, kSpellScopeObserver)	
	
		// Listbox Observer
		REGISTER_PMINTERFACE(SpellAlternativesObserver, kSpellAlternativesObserver)
		REGISTER_PMINTERFACE(SpellListBoxEH, kSpellListBoxEH)


		REGISTER_PMINTERFACE(DynamicSpellCheckAdornment, kDynamicSpellCheckAdornmentImpl)
		REGISTER_PMINTERFACE(GalleyDynamicSpellCheckAdornment, kGalleyDynamicSpellCheckAdornmentImpl)

		// Rest
		// REFERENCE_PMINTERFACE( SpellLightObserver )
		// REGISTER_PMINTERFACE(SpellDelayThread, kSpellDelayThread)
		
		// REFERENCE_PMINTERFACE( SpellProgressBarObserver )	
		REGISTER_PMINTERFACE(ApplySpellPanelOptionsCmd, kApplySpellPanelOptionsCmd)	
		REGISTER_PMINTERFACE(SpellPanelOptions, kSpellPanelOptionsImpl)	
		REGISTER_PMINTERFACE(SpellPanelOptions2, kSpellPanelOptionsImpl2)	
		REGISTER_PMINTERFACE(SpellStatusTextObserver, kSpellStatusTextObserverImpl)	
		REGISTER_PMINTERFACE(SpellTargetServer, kSpellTargetServer)	
		REGISTER_PMINTERFACE(SpellReplaceWalkerClient, kSpellReplaceClientImpl)	
		REGISTER_PMINTERFACE(SpellCheckWalkerData, kSpellCheckWalkerDataImpl)

		REGISTER_PMINTERFACE(SpellPrefsPanelCreator, kSpellPrefsPanelCreatorImpl)	
		REGISTER_PMINTERFACE(SpellPrefsDialogController, kSpellPrefsDialogControllerImpl)	
		
		REGISTER_PMINTERFACE(DynamicSpellCheckObserver, kDynamicSpellCheckObserverImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckTypingIdleTask, kDynamicSpellCheckTypingIdleTaskImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckKeyWatcher, kDynamicSpellCheckKeyEventWatcherImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckStartupShutdown, kDynamicSpellCheckStartupShutdownImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckServiceProvider, kDynamicSpellCheckServiceProviderImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckCache, kDynamicSpellCheckCacheImpl)
		REGISTER_PMINTERFACE(DocumentDynamicSpellCheckObserver, kDocumentDynamicSpellCheckObserverImpl)
		REGISTER_PMINTERFACE(DynamicSpellCheckDocResponder, kDynamicSpellCheckDocResponderImpl)
		
		REGISTER_PMINTERFACE(SpellPanelDialogController, kSpellPanelDialogControllerImpl)
		
		REGISTER_PMINTERFACE(SpellTargetListObserver, kSpellTargetListObserverImpl)
		REGISTER_PMINTERFACE(SpellCaseSensitiveObserver, kSpellCaseSensitiveObserverImpl)
				
#ifdef DEBUG
		REGISTER_PMINTERFACE(SpellPanelTestMenu, kSpellPanelTestMenu)	
		REGISTER_PMINTERFACE(LinguisticTestMenu, kLinguisticTestMenuImpl)
		REGISTER_PMINTERFACE(HyphenateStoryWalker, kHyphenateStoryWalkerImpl)
		REGISTER_PMINTERFACE(HyphenateStoryCmd, kHyphenateStoryCmdImpl)
		REGISTER_PMINTERFACE(SpellCheckStoryWalker, kSpellCheckStoryWalkerImpl)
		REGISTER_PMINTERFACE(SpellCheckStoryCmd, kSpellCheckStoryCmdImpl)
#endif

		REGISTER_PMINTERFACE(PrivateSpellingUtils, kPrivateSpellingUtilsImpl)

		REGISTER_PMINTERFACE(AutoCorrectPrefsPanelCreator, kAutoCorrectPrefsPanelCreatorImpl)
		REGISTER_PMINTERFACE(AutoCorrectPrefsDialogController, kAutoCorrectPrefsDialogControllerImpl)
		
		REGISTER_PMINTERFACE(AutoCorrectTypingIdleTask, kAutoCorrectTypingIdleTaskImpl)
		REGISTER_PMINTERFACE(AutoCorrectKeyWatcher, kAutoCorrectKeyEventWatcherImpl)
		REGISTER_PMINTERFACE(AutoCorrectObserver, kAutoCorrectObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectServiceProvider, kAutoCorrectServiceProviderImpl)
		REGISTER_PMINTERFACE(AutoCorrectStartupShutdown, kAutoCorrectStartupShutdownImpl)

		REGISTER_PMINTERFACE(AutoCorrectTreeViewWidgetMgr, kAutoCorrectTreeViewWidgetMgrImpl)
		REGISTER_PMINTERFACE(AutoCorrectTreeViewAdapter, kAutoCorrectTreeViewAdapterImpl)

		REGISTER_PMINTERFACE(AutoCorrectAddButtonObserver, kAutoCorrectAddButtonObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectAddButtonObserver, kAutoCorrectEditButtonObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectRemoveButtonObserver, kAutoCorrectRemoveButtonObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectCheckBoxObserver, kAutoCorrectCheckBoxObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectCapCheckBoxObserver, kAutoCorrectCapCheckBoxObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectAddPairDlgController, kAutoCorrectAddPairDialogControllerImpl)
		REGISTER_PMINTERFACE(AutoCorrectTreeViewObserver, kAutoCorrectTreeViewObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectLanguageObserver, kAutoCorrectLanguageObserverImpl)
		REGISTER_PMINTERFACE(AutoCorrectWorkspaceResponder, kAutoCorrectNewWSResponderImpl)
		REGISTER_PMINTERFACE(AutoCorrectFolderIdleTask, kAutoCorrectFolderIdleTaskImpl)

