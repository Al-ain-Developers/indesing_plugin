//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ReplaceStory.java $
//  
//  Owner: Heath Lynn
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
package com.adobe.idml.samples;

import com.adobe.idml.*;
import com.adobe.idml.Package;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

/** ReplaceStory can be used to extract and replace stories from IDML package files.
 *
 */
public class ReplaceStory 
{
	/** A ReplaceStory object is constructed with a path to an IDML file.  The
	 * IDML file is expanded to a temporary directory on construction.
	 * 
	 * @param idmlFile The path to the IDMLFile.
	 * @throws IOException
	 */
	public ReplaceStory(String idmlFile) throws IOException
	{
		fIDMLFile = idmlFile;
		fDeleteWorkingDir = false;
		
		File f = new File(fIDMLFile);
		
		if( f.isDirectory())
		{
			fWorkingDir = f;
			fDeleteWorkingDir = false;
		}
		else
		{
			fWorkingDir = Package.decompress(fIDMLFile);
			fDeleteWorkingDir = true;
		}
		
		fLocator = new PackageXmlLocator(fWorkingDir);
	}
	
	/** A temporary directory is maintained on disk until this
	 * function is called signaling that we are done with these
	 * resources.
	 * 
	 */
	public void release()
	{
		if( fDeleteWorkingDir)
			FileUtils.DeleteDirectory(fWorkingDir);
		
		fIDMLFile =  null;
		fWorkingDir = null;
	}
	
	/** Gets the path to a story file by it's Self ID
	 * @param storyID The ID to look for
	 * @return The path to the Story file.
	 */
	private String getStoryFileByID(String storyID)
	{
		String storyFile = null;
		
		try
		{
			String xPathExpression = "/idPkg:Story/Story[@Self='" + storyID + "']/@Self";
			storyFile = fLocator.getXMLFile(fLocator.getStoriesDirPath(), xPathExpression);
		}
		catch(Exception e)
		{
		}
		
		return storyFile;
	}

	/** Extracts a single story file.
	 * @param storyID The ID of the file to be extracted.
	 * @param outFile The path to the new file.
	 * @throws IOException
	 * @throws Exception
	 */
	public void extract(String storyID, String outFile) throws IOException, Exception
	{
		// Find the story file with the given ID and copy it to the output file
		//
		String storyFile = getStoryFileByID(storyID);
		
		// Copy the story file
		File src = new File(storyFile);
		File dest = new File(outFile);
		FileUtils.CopyFile(src, dest);
		
		if( storyFile == null )
		{
			throw new FileNotFoundException("No Stories with Self = " + storyID + " found.");
		}
	}
	
	/** Extracts all the stories in an IDML file.
	 * @param outDir The path to the directory where the files should be saved.
	 * 				If the directory does not exist it is created.
	 * @throws Exception
	 */
	public void extractAll(String outDir) throws Exception
	{
		// Make sure the output directory exists
		//
		File outDirFile = new File(outDir);
		if( !outDirFile.exists())
		{
			outDirFile.mkdirs();
		}
		
		// Copy all story files workingDir to outDir
		//
		File storiesDir = new File(fLocator.getStoriesDirPath());
		FileUtils.CopyDir( storiesDir, outDirFile);
	}
	
	/**Replaces a story in the working directory.   This replace assumes all resources, such as styles 
	 * and swatches are available in the destination document.  The file name and Self ID of the
	 * source story is changed to what the old file was.
	 * 
	 * @param storyID The Self ID of the story to replace.
	 * @param inFile The IDML file or expanded IDML directory.
	 * @throws Exception
	 */
	public void replace(String storyID, String inFile) throws Exception
	{
		// Copy the file into place
		String storyFile = getStoryFileByID(storyID);
		File dest = new File(storyFile);
		File src = new File(inFile);
		FileUtils.CopyFile(src, dest);
		
		// Make sure the new story has the right ID
		ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
		xslParamValues.add(new XslParam("story-id", storyID));
		
		File xslFile = new File("xsl/r/Stories/story.xsl");
		
		FileTransformer fileTransformer = new FileTransformer(xslFile, xslParamValues);
		fileTransformer.transformFile(dest, dest);
		
		
	}
	
	/** Writes the temporary working directory to an IDML package or 
	 * to another working directory (if a directory is specified).  
	 * @param output The path to the new IDML file or directory.
	 * @throws Exception
	 */
	public void writeTempFiles(String output) throws Exception
	{
		File outFile = new File(output);
		if( outFile.isDirectory() && outFile != fWorkingDir)
		{
			FileUtils.CopyDir(fWorkingDir, outFile);
		}
		else if(outFile != fWorkingDir)
		{
			Package.compress(fWorkingDir, output);
		}
	}
	
	String fIDMLFile;
	File fWorkingDir;
	boolean fDeleteWorkingDir;
	PackageXmlLocator fLocator;
	
	
	/** Usage message for main method.
	 * 
	 */
	private static void usage()
	{
		System.out.println("usage:");
		System.out.println("\tReplaceStory -e idmlPackage id outStoryFile"); // 3
		System.out.println("\tReplaceStory -ea idmlPackage outDir"); // 3
		System.out.println("\tReplaceStory -r idmlPackage id inStoryFile idmlOutput"); // 4
		System.out.println("\n\tReplaceStory can extract and replace story files within an IDML package.");
		System.out.println("\tThe IDML package can be either an IDML file or extracted directory.");
		System.out.println("\nOperations:");
		System.out.println("\t-e Extracts the story with the given ID to the specified file.");
		System.out.println("\t-ea Extracts all stories to the given directory.");
		System.out.println("\t-r Replace the story with the given id with the contents of inStoryFile and write to idmlOutput.");	
		System.out.println("\nExamples: ");
		System.out.println("\tReplaceStory -ea ReplaceStory2.idml tempdir");
		System.out.println("\tReplaceStory -r ReplaceStory.idml uf3 tempdir" + File.separator + "Story_ud4.xml ReplaceStory3.idml");
		System.exit(-1);
	}
	
	/** Program that allows you to replace stories from the command line.
	 * @param args
	 */
	public static void main(String[] args) 
	{
		ReplaceStory rs = null;
		
		try
		{
			if(args.length < 3 || args[0].equalsIgnoreCase("-h"))
			{
				usage();
			}
			
			String operation = args[0];
			String idmlFile = args[1];
			
			if(Package.isAPackage(idmlFile))
			{
				rs = new ReplaceStory(idmlFile);
				
				if(operation.equalsIgnoreCase("-e") && args.length == 4)
				{
					String id = args[2];
					String outFile = args[3];
					rs.extract(id, outFile);
				}
				else if(operation.equalsIgnoreCase("-ea") && args.length == 3)
				{
					String outDir = args[2];
					rs.extractAll(outDir);
				}
				else if(operation.equalsIgnoreCase("-r") && args.length == 5)
				{
					String id = args[2];
					String inFile = args[3];
					String output = args[4];
					rs.replace(id, inFile);
					rs.writeTempFiles(output);
				}
				else
				{
					rs.release();
					usage();
				}
				
				rs.release();

			}
			else
			{
				System.err.println("Error:  Non-package file or directory specified.");
			}
		}
		catch( Exception e)
		{
			if( rs != null)
				rs.release();
			
			String err = "Failed to replace Story.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
		
	}

}
