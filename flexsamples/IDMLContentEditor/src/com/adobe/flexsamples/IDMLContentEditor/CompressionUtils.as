package com.adobe.flexsamples.IDMLContentEditor
{
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.utils.ByteArray;
	
	import nochump.util.zip.ZipEntry;
	import nochump.util.zip.ZipFile;
	import nochump.util.zip.ZipOutput;
	
	/**
	 * Contains utilities used to compress and decompress
	 * files.  Used to create and extract IDML files.
	 */
	public class CompressionUtils
	{
		/**
		 * Creates an idml file by compressing the directory
		 * provided.
		 */
		public static function compress(srcDir:File, destIdmlFile:File):void
		{
			var zipOut:ZipOutput = new ZipOutput();	
			var zipData:ByteArray = zipOut.byteArray		
			
			//recursively add files to the zip file.
			zipOut = CompressionUtils.addFileToArchive(zipOut, srcDir, srcDir);			
			zipOut.finish();
						
			//Save IDML file to disk.
			writeToFile(zipData, destIdmlFile);			
		}		
		
		/**
		 * Extracts the IDML file provided into the output
		 * directory provided.
		 */
		public static function decompress(src:File, output:File):void
		{
			var fileStream:FileStream = new FileStream();
			var srcBytes:ByteArray = new ByteArray();
			
			fileStream.open(src, FileMode.READ);
			fileStream.readBytes(srcBytes, 0, fileStream.bytesAvailable);

			var zipFile:ZipFile = new ZipFile(srcBytes); 
			for(var i:int = 0; i < zipFile.entries.length; i++) 
			{     
				var entry:ZipEntry = zipFile.entries[i];   
				var data:ByteArray = zipFile.getInput(entry); 
				CompressionUtils.outFile(entry.name, data, output); 
			}			
		}
		
		/**
		 * Recursively adds files to the zip archive.
		 */ 
		private static function addFileToArchive(zipOut:ZipOutput, currentFile:File, root:File):ZipOutput
		{
			if (currentFile.isDirectory)
			{
				var files:Array = currentFile.getDirectoryListing();
				for (var i:int = 0; i < files.length; i++) 
				{
					zipOut = addFileToArchive(zipOut, files[i], root);
				}
			}
			else 
			{			
				//Get relative path from IDML Package root to file.
				var name:String = root.getRelativePath(currentFile);
				
				//Get file byte data
				var fileStream:FileStream = new FileStream();
				var data:ByteArray = new ByteArray();
				fileStream.open(currentFile, FileMode.READ);				
				fileStream.readBytes(data, 0, fileStream.bytesAvailable);
				
				//Write Zip Entries
				var zipEntry:ZipEntry = new ZipEntry(name);
				zipOut.putNextEntry(zipEntry);				
				zipOut.write(data);
				zipOut.closeEntry();
			}			
			return zipOut;
		}	

		
		/**
		 * Extracts an IDML file to a temp directory
		 * and returns a file object for that temp 
		 * directory.
		 */ 
		public static function decompressToTempDir(src:File):File
		{
			var tempDir:File = File.createTempDirectory();
			CompressionUtils.decompress(src, tempDir);	
			return tempDir;		
		}	
		
		
		/**
		 * Writes the data byte array to the file path provided.
		 */ 
		private static function outFile(fileName:String, data:ByteArray, outDir:File):void
		{
		    var outFile:File = outDir.resolvePath(fileName); 
		    CompressionUtils.writeToFile(data, outFile);
		}
		
		/**
		 * Writes the data byte array to the file provided.
		 */ 
		private static function writeToFile(data:ByteArray, outFile:File):void
		{
		    var outStream:FileStream = new FileStream();
		    // open output file stream in WRITE mode
		    outStream.open(outFile, FileMode.WRITE);
		    // write out the file
		    outStream.writeBytes(data, 0, data.length);
		    // close it
		    outStream.close();
		}
	}	
}