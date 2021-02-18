//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/examplefiles/TransparencyEffect.java $
//  
//  Owner: ???
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
//  TransparencyEffect.java
//  
//========================================================================================

package com.adobe.ids.sdk.document;

import com.adobe.ids.*;
import com.adobe.ids.basics.*;
import com.adobe.ids.enums.*;
import com.adobe.ids.layout.*;
import com.adobe.ids.sdk.utils.*;
import com.adobe.ids.preferences.*;

public class TransparencyEffect
{
	public static String getDescription()
	{
		return "Creates a rectangle and uses the transparency effect on it.";
	}

	public static String[] getArgumentList()
	{
		return new String[] { "iorFilePath", "outputFilepath" };
	}

	public static void main(String[] args) throws Exception
	{
		//This line below did work in previous releases
		//Application myApp = ApplicationUtils.getApplication(args[0]);
		//However, it has now been replaced with these two lines.		
		ApplicationUtils utils = new ApplicationUtils(args[0]);
		Application myApp = utils.getApplication();

		if (myApp != null){
			myApp.consoleout("TransparencyEffect started!");

			try{
				// @startCodeSnippet
				// Open a new document
				Document myDocument = myApp.addDocument(OptArg.noDocumentPreset());

				// Draw a rectangle on the first page of the document
				Rectangle rect = myDocument.getNthChildPage(0).addRectangle(OptArg.noLayer(), 
						OptArg.noLocationOptionsEnum(), OptArg.noVariableType());
				rect.setGeometricBounds(UnitUtils.createDouble(
						new double []{6, 6, 18, 18}));
				rect.setStrokeWeight(UnitUtils.createDouble(4));

				// set the transparency effect settings of the rectangle
				Transparencyeffectsettings s = rect.getTransparencyeffectsettingsproperty();
				s.setTransparencyeffectmode(true);
				s.setTransparencyeffectusealpha(true);
				s.setTransparencyeffectoffsetxdirection(10);
				s.setTransparencyeffectoffsetydirection(8);
				s.setTransparencyeffectuseblackasopaque(true);
				s.setTransparencyeffectuseblur(true);

				// save and close the file
				String myFilepath = "/TransparencyEffect_java.indd";
				if (args.length > 1) {
					myFilepath = args[1];
				}
				myDocument.close(OptArg.makeSaveOptionsEnum(kSaveOptionsYes.value), 
						OptArg.makeFile(myFilepath), 
						OptArg.noString(), OptArg.noBoolean());

				// @endCodeSnippet
			}
			catch(IdsException e) {
				System.err.println("Exception #" + e.errorCode + ":  " + e.errorMsg);
				e.printStackTrace();
			}
			myApp.consoleout("TransparencyEffect finished!");
		}
	}
}
