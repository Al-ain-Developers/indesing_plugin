//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/MOpenPanelDelegate.h $
//  
//  Owner: sanyam
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
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __MOpenPanelDelegate_H_
#define __MOpenPanelDelegate_H_

class MOpenFileDialogBase;
@interface MOpenPanelDelegate: NSObject <NSOpenSavePanelDelegate>
{
	MOpenFileDialogBase*	fOpenBaseRef;	
	NSInteger				fCustomMenuTypeAllIdx;
	NSMutableSet*			fAllowedExtensionsList;
}

@property(readwrite) NSInteger				fCustomMenuTypeAllIdx;
@property(readwrite) MOpenFileDialogBase*	fOpenBaseRef;

// Initialize/Constructor for constructing the object
- (id) init;

// Deallocator/Desctructor for the object
- (void) dealloc;

// Add the type into the list of types
-(void) AddType:(SysOSType) value;

// Add extension string into the list of extension, based on which file filtering is done.
-(void) AddExtensionString:(NSString*) fileExtensionString;

// Add the extension into the list of extensions
- (void) AddExtension:(const PMString&) newExtension;

// Callback/ delegate procedure of Cocoa, triggered on the file selection change
- (void)panelSelectionDidChange:(id)sender;

// Callback/delegate procedure of Cocoa to notify that the selected directory has changed
- (void)panel:(id)sender didChangeToDirectoryURL:(NSURL *)url;

// Update allowed file types list
- (void) UpdateAllowedFileTypesList:(NSOpenPanel*) panel allOrNoneFlag:(bool16) showAll;

@end
#endif