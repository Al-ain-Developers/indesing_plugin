//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/FileUtils.java $
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
//  Copyright 2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

package com.adobe.idml;

import java.io.*;
import java.util.Stack;


/** 
 * File specific utility methods used by other classes in the package.
 */
public abstract class FileUtils 
{
	/**
	 * Get the file extension for a file. 
	 * @param filePath	The path to the file.
	 * @return	The three character extension for the file.
	 */
	public static String getFileType(String filePath)
	{
		return filePath.substring(filePath.lastIndexOf(".") + 1);
	}
	
	/**
	 * Get the size of a file in Kilobytes.
	 * @param file	The file object to obtain the size of.
	 * @return	The size of the file in Kilobytes.
	 */
	public static String getFileSize(File file)
	{
		long size = (file.length() / 1024);
		return String.format("%s Kb", String.valueOf(size));
	}
		
	/**
	 * Returns a file object representing the path given.
	 * @param filePath	The path to the file.
	 * @return	A file object representing the file path given.
	 * @throws IOException
	 */
	public static File getFile(String filePath) throws IOException
	{		
		if (null != filePath)
		{
			File file = new File(filePath);
			if(file.exists())
			{
				return file;
			}
		}	
		throw new IllegalArgumentException(String.format("%s is not a valid file path", filePath));
	}
	
	/**
	 * Returns a file object representing the path given.
	 * @param filePath	The path to the file.
	 * @return	A file object representing the file path given.
	 * @throws PackageException 
	 */
	public static File getIdmlReferencedFile(String filePath) throws PackageException
	{		
		if (null != filePath)
		{
			//Remove the file prefix
			filePath = filePath.replace("file:", "");
			File file = new File(filePath);
			if(file.exists())
			{
				return file;
			}
		}	
		String err = 	"This idml package links to an external file which was not found." +
						"\nThis package package may have been created on a different computer or the file system structure has changed." +
						"\n\nMissing File: %s";
		throw new PackageException(String.format(err, filePath));
	}
	
	/**
	 * Creates a text file at the location specified.
	 * @param filePath	The location of the file to be created.
	 * @return	Returns true if the file was created and false if not.
	 * @throws IOException
	 */
	public static File createFile(String filePath) throws IOException
	{
		File txtFile = new File(filePath);
		if (txtFile.exists())
		{	
			String err = String.format("%s already exists: ", filePath);
			throw new IllegalArgumentException(err);
		}
		if (txtFile.createNewFile())
		{
			return txtFile;
		}
		return null;
	}
	
	/**
	 * Gets a buffered writer for a text file.
	 * @param txtFile	The file to obtain a buffered writer for.
	 * @return	A BufferedWriter object for the file specified.
	 * @throws IOException
	 */
	public static BufferedWriter getFileWriter(File txtFile) throws IOException
	{
		FileUtils.verifyFile(txtFile);
		if (!txtFile.canWrite())
		{
			String err = String.format("%s cannot be written to.", txtFile.getAbsolutePath());
			throw new IllegalArgumentException(err);
		}
		return new BufferedWriter(new FileWriter(txtFile));
	}
	
	/**
	 * Returns a file object representing the path given.
	 * @param dirPath	The path to the directory.
	 * @return	A file object representing the file path given.
	 * @throws IOException
	 */
	public static File getDirectory(String dirPath) throws IOException
	{		
		if (null != dirPath)
		{
			File dir = new File(dirPath);
			if(dir.exists())
			{
				return dir;
			}
		}	
		throw new IOException(String.format("%s is not a valid directory path", dirPath));
	}
	
	/**
	 * Throws an error if the file object is invalid.
	 * @param filePath The path to the file to be tested.
	 * @throws IOException
	 */
	public static void verifyFile(String filePath) throws IOException
	{
		verifyFile(new File(filePath)); 			
	}
	
	/**
	 * Throws an error if the file object is invalid.
	 * @param file	The file to be tested.
	 * @throws IOException
	 */
	public static void verifyFile(File file) throws IOException
	{
		if (null == file || !file.exists() || file.isDirectory())
		{
			String err = String.format("%s is not a valid file.", file.getAbsolutePath());
			throw new IllegalArgumentException(err);
		}			
	}
	
	/**
	 * Throws an error if the file object is invalid.
	 * @param dirPath	The path to the directory to be tested.
	 * @throws IOException
	 */
	public static void verifyDirectory(String dirPath) throws IOException
	{
		verifyDirectory(new File(dirPath));
	}
	
	/**
	 * Throws an error if the file object representing the directory is invalid.
	 * @param dir	The directory object to be tested.
	 * @throws IOException
	 */
	public static void verifyDirectory(File dir) throws IOException
	{
		if (null == dir || !dir.exists() || dir.isFile())
		{
			throw new IllegalArgumentException(String.format("%s is not a valid directory.", dir.getAbsolutePath()));
		}			
	}
	
	/**
	 * Ensures that the directory containing the file specified exists.
	 * If it does not, the directory will be created.
	 * @param filePath	The path the to a file.
	 * @throws IOException 
	 */
	public static void ensureParentDirectory(String filePath) throws IOException
	{
		String parentDir = getParentDirectoryPath(filePath);
		ensureDirectory(parentDir);
	}

	/** 
	 * Deletes the directory specified by dir.
	 * @param dir The directory to delete.
	 * @return Returns true if successful, otherwise false.
	 */
	public static boolean DeleteDirectory(File dir)
	{
		if (dir.isDirectory()) 
		{
			String[] children = dir.list();
			for (int c=0; c<children.length; c++) 
			{
				boolean success = DeleteDirectory(new File(dir, children[c]));
				if (!success) 
				{
					return false;
				}
			}
		}		
		return dir.delete();
	}
	
	/**
	 * Deletes a file.
	 * @param filePath	The location of the file to be deleted.
	 * @return	Returns true if the file was deleted and false if not.
	 */
	public static boolean deleteFile(String filePath)
	{
		File file = new File(filePath);
		if (file.exists())
		{
			return file.delete();
		}
		return false;
	}
	
	
	/** 
	 * Creates a temp file that is deleted on exit.
	 * @return a non-null File object reference on success.
	 */
	public static File CreateTempFile()
	{
		try
		{
			File cwdDir = new File(""); // need this for createTempFile
			File temp = File.createTempFile("_idmltools_temp_file_", "_", cwdDir.getAbsoluteFile());
			if( temp != null)
				temp.deleteOnExit();
			
			return temp;
		}
		catch(Exception e)
		{
			System.err.println("Error: Failed to create temp file.");
			return null;
		}
	}
		
	/** 
	 * Creates a temporary directory.  It's up to the caller to delete this
	 * directory when it's no longer needed.
	 * @return a non-null File object for the directory upon success.
	 */
	public static File CreateTempDir( )
	{
		try
		{
			File cwdDir = new File(""); // need this for createTempFile
			File temp = File.createTempFile("_idmltools_temp_dir_", "_", cwdDir.getAbsoluteFile());
			temp.delete();
			if(temp.mkdir())
				return temp;
		}
		catch(Exception e)
		{
			System.err.println("Error: Failed to create temp directory.");
			return null;
		}		
		return null;
	}
	
	/** 
	 * Copy a file
	 * @param src  The source file.
	 * @param dest The destination file.
	 * @throws Exception
	 */
	public static void CopyFile(File src, File dest) throws Exception
	{
		InputStream srcStream = new FileInputStream(src);
		OutputStream destStream =  new FileOutputStream(dest);
		
		int length;
		byte [] buffer = new byte[1024];
		
		while( (length = srcStream.read(buffer)) > 0)
		{
			destStream.write(buffer, 0, length);
		}
		
		srcStream.close();
		destStream.close();		
	}
	
	/** 
	 * Copies the contents of a source directory into a destination directory. 
	 * @param src	The directory to copy.
	 * @param dest	The destination directory to copy the files into.
	 * @throws Exception
	 */
	public static void CopyDir(File src, File dest) throws Exception
	{
		if(src.isDirectory())
		{
			if( !dest.exists())
			{
				dest.mkdir();
			}
			
			String [] fileNames = src.list();
			for(int i=0; i<fileNames.length; i++)
			{
				CopyDir(new File(src, fileNames[i]), new File(dest, fileNames[i]));
			}
		}
		else
		{
			CopyFile(src, dest);
		}
	}
	
	/**
	 * Returns a relative path from the directory provided to the file specified.
	 * @param fromDirPath 	The starting point of the relative path.  Note: it needs to be a directory not a file.
	 * @param toFilePath 	The target file of the relative path.
	 * @return			The relative path.
	 * @throws IOException 
	 */
	public static String getRelativePath(String fromDirPath, String toFilePath) throws IOException
	{
		File fromDir = FileUtils.getDirectory(fromDirPath);
		File toFile = FileUtils.getFile(toFilePath);
		return getRelativePath(fromDir, toFile);
	}
	
	/**
	 * Returns a relative path from the directory provided to the file specified.
	 * @param fromDir	The starting point of the relative path.  Note: it needs to be a directory not a file.
	 * @param toFile	The target file of the relative path.	
	 * @return			The relative path.
	 * @throws IOException 
	 */
	public static String getRelativePath(File fromDir, File toFile) throws IOException
	{
		FileUtils.verifyDirectory(fromDir);
		FileUtils.verifyFile(toFile);		
		Stack<String> fromStk = getFolderStack(fromDir);
		Stack<String> toStk = getFolderStack(toFile);
		return matchFolderStacks(fromStk,toStk);
	}
	
	/**
	 * Returns the parent directory for the file provided.
	 * @param file	A file object for the file.
	 * @return	A file object for the parent directory.
	 * @throws IOException 
	 */
	public static File getParentDirectory(File file) throws IOException
	{
		return getParentDirectory(file.getAbsolutePath());
	}
	
	/**
	 * Returns the parent directory for the file provided.
	 * @param filePath 	The path to a file.
	 * @return	A file object for the parent directory.
	 * @throws IOException 
	 */
	public static File getParentDirectory(String filePath) throws IOException
	{
		String dirPath = getParentDirectoryPath(filePath);
		return FileUtils.getDirectory(dirPath);
	}
	
	/**
	 * Given a file path this method returns the parent directory path.
	 * @param filePath	The absolute or relative path to a file
	 * @return	The path to the parent directory
	 */
	public static String getParentDirectoryPath(String filePath)
	{
		String dirPath = ".";
		int seperatorIndex = filePath.lastIndexOf(File.separator);
		if (seperatorIndex > -1)
		{
			dirPath = filePath.substring(0, seperatorIndex);
		}
		return dirPath;
	}
	
	/**
	 * Creates the directory if it does not already exist.
	 * @param dirPath	The location of the directory to ensure.
	 * @throws IOException
	 */
	public static void ensureDirectory(String dirPath) throws IOException
	{
		ensureDirectory(new File(dirPath));
	}

	/**
	 * Creates the directory if it does not already exist.
	 * @param dir	The file object representing the directory to ensure.
	 * @throws IOException
	 */
	public static void ensureDirectory(File dir) throws IOException
	{
		if(dir.equals(null))
		{
			throw new IOException("The directory object is null.");		
		}
		if (dir.isFile())
		{
			throw new IOException("This object is a file.  A directory is required.");	
		}
		if (dir.exists())
		{
			return;
		}
		dir.mkdirs();
	}
		
	/**
	 * Given a file, this method will return a stack containing the directories
	 * from file to root.
	 * @param file	The file to use when building the stack of directories.
	 * @return	A stack containing all directories in order start with the file and ending with the root directory.
	 * @throws IOException
	 */
	private static Stack<String> getFolderStack(File file) throws IOException 
	{
		Stack<String> folderStk = new Stack<String>();
		File current;
		current = file.getCanonicalFile();
		while(current != null) {
			folderStk.push(current.getName());
			current = current.getParentFile();
		}
		return folderStk;
	}
	

	/**
	 * Give two stacks of folders from branch to root, this method will return a relative path from 
	 * a directory to a file.
	 * @param fromDir	A stack containing all folders in the path from root to the start directory.
	 * @param toFile	A stack containing all folders in the path from root to the destination file.
	 * @return	A relative path from the start directory to the destination file.
	 */
	private static String matchFolderStacks(Stack<String> fromStk, Stack<String> toStk) {
		String relativePath = "";

		//Eliminate the common folders starting at the root and working towards the leafs.
		while((!toStk.empty()) && (!fromStk.empty()) && (toStk.peek().equals(fromStk.peek())))
		{
			toStk.pop();
			fromStk.pop();
		}

		//Add a "../" for each remaining folder in the from list.
		while(!fromStk.empty())
		{
			relativePath += "../";
			fromStk.pop();
		}

		//Join each remaining folder in the file list with a "/".
		while(toStk.size() > 1)
		{
			relativePath += toStk.pop() + "/";
		}

		//Adds the file name.
		relativePath += toStk.pop();
		return relativePath;
	}
}
