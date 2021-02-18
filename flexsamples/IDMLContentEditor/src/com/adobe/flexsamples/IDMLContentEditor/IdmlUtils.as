package com.adobe.flexsamples.IDMLContentEditor
{
	import mx.collections.ArrayCollection;
	
	/**
	 * Contains utility function making specific updates to 
	 * IDML files using E4X.
	 */
	public class IdmlUtils
	{
		import flash.filesystem.FileStream;
		import flash.filesystem.File;
		import flash.filesystem.FileMode;
		
		public static const SPREADS_DIR:String = "Spreads";		
		public static const STORIES_DIR:String = "Stories";
		
		/**
		 * Given an extracted IDML file, this function
		 * returns an ArrayCollection of BindableTextObjects
		 * referring to the TextFrames with ScriptLabels
		 * found in the IDML file.
		 */ 
		public static function getScriptLabelObjects(idmlDir:File):ArrayCollection
		{
			var objects:ArrayCollection = new ArrayCollection();
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.SPREADS_DIR).getDirectoryListing())
			{				
				var xml:XML = IdmlUtils.readXmlFromFile(xmlFile);
				for each (var node:XML in xml..TextFrame)
				{
					var scriptLabelNode:XMLList = node..Properties..KeyValuePair;
					if (scriptLabelNode.length() > 0)
					{
						var scriptLabel:String = node..Properties.Label.KeyValuePair.@Value;
						var storyId:String = getStoryID(idmlDir, scriptLabel);
						var storyContent:String = getStoryContent(idmlDir, storyId);
						
						var obj:BindableTextObject = new BindableTextObject();
						obj.scriptLabel = scriptLabel;
						obj.storyId = storyId;
						obj.storyContent = storyContent;
						
						objects.addItem(obj);
					}
				}
			}		
			return objects;
		}
		
		/**
		 * Given an extracted IDML file, this function
		 * returns an ArrayCollection of BindableImageObjects
		 * referring to the images with ScriptLabels
		 * found in the IDML file.
		 */ 
		public static function getSpreadImages(idmlDir:File):ArrayCollection
		{
			var images:ArrayCollection = new ArrayCollection()
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.SPREADS_DIR).getDirectoryListing())
			{
				var xml:XML = readXmlFromFile(xmlFile);				
				for each(var node:XML in xml..Rectangle)
				{
					var scriptLabelNode:XMLList = node..Properties..KeyValuePair;
					if (scriptLabelNode.length() > 0)
					{
						var imgScriptLabel:String = node..Properties.Label.KeyValuePair.@Value;
						var imgPath:String = node..Image.Link.@LinkResourceURI;
						var imgStoreState:String = node..Image.Link.@StoredState;
						var imgID:String = node..Image.@Self;
						
						var img:BindableImageObject = new BindableImageObject();
						img.scriptLabel = imgScriptLabel;							
						img.id = imgID;
						img.isEmbedded = (imgStoreState == "Embedded");
						img.nativePath = getNativePath(imgPath);
						img.fileName = getFileName(imgPath);
						images.addItem(img);
					}
				}
			}
			return images;			
		}
		
		/**
		 * StoryID's are needed to match scriptLabels with TextFrame
		 * content.  Given an extracted IDML file a script label string,
		 * this function will return the coresponding story ID.
		 */
		public static function getStoryID(idmlDir:File, scriptLabel:String):String
		{
			var storyID:String = null;
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.SPREADS_DIR).getDirectoryListing())
			{
				var xml:XML = IdmlUtils.readXmlFromFile(xmlFile);
				storyID = xml..TextFrame.(Properties.Label.KeyValuePair.@Value == scriptLabel).@ParentStory;
				if (storyID != "")
				{
					break;
				}
			}		
			return storyID;
		}
		
		/**
		 * Given an extracted IDML file and a StoryID,
		 * this function will return the corresponding story content..
		 */
		public static function getStoryContent(idmlDir:File, storyId:String):String
		{
			var content:String = null;
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.STORIES_DIR).getDirectoryListing())
			{
				var xml:XML = IdmlUtils.readXmlFromFile(xmlFile);
				if (xml..Story.@Self == storyId)
				{
					content = xml..Story.(@Self == storyId).ParagraphStyleRange.CharacterStyleRange.Content;
					break;
				}
			}	
			return content;		
		}
		
		/**
		 * Writes changes found in the provided BindableTextObject to the extracted
		 * IDML directory.
		 */ 
		public static function updateStory(idmlDir:File, obj:BindableTextObject):void
		{
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.STORIES_DIR).getDirectoryListing())
			{
				if (obj.hasChanged)
				{
					var xml:XML = IdmlUtils.readXmlFromFile(xmlFile);
					if (xml..Story.@Self == obj.storyId)
					{
						//Update the story content.
						xml..Story.(@Self == obj.storyId).ParagraphStyleRange.CharacterStyleRange.Content = obj.storyContent;
						IdmlUtils.writeXmlToFile(xmlFile, xml);
					}
				}
			}			
		}
		
		/**
		 * Writes changes found in the provided BindableImageObject to the extracted
		 * IDML directory.
		 */
		public static function updateSpread(idmlDir:File, imgRef:BindableImageObject):void
		{
			for each (var xmlFile:File in idmlDir.resolvePath(IdmlUtils.SPREADS_DIR).getDirectoryListing())
			{
				if (imgRef.hasChanged)
				{
					var xml:XML = IdmlUtils.readXmlFromFile(xmlFile);
					
					//Update Image Path
					xml..Image.(@Self == imgRef.id).Link.@LinkResourceURI = imgRef.idmlPath;
					
					if (imgRef.isEmbedded)
					{
						//Set StoreState to Normal instead of Embedded
						xml..Image.(@Self == imgRef.id).Link.@StoredState = "Normal";
						
						//Delete Embedded Image
						delete xml..Image.(@Self == imgRef.id).Properties.Contents;				
					}
					
					IdmlUtils.writeXmlToFile(xmlFile, xml);
				}
			}
		}
		
		/**
		 * Extracts the absolute path from the path found
		 * in the IDML.
		 */
		private static function getNativePath(path:String):String
		{			
			return path.substring(5, path.length);
		}
		
		/**
		 * Extracts the file name from the file path.
		 */
		private static function getFileName(path:String):String
		{			
			return path.substring(path.lastIndexOf("/") + 1, path.length);
		}
		
		/**
		 * Writes an XML document to file.
		 */
		private static function writeXmlToFile(xmlFile:File, xml:XML):void
		{
			var stream:FileStream = new FileStream();
 			stream.open(xmlFile, FileMode.WRITE)
 			stream.writeUTFBytes(xml.toXMLString());
 			stream.close();
 		}
		
		/**
		 * Reads an XML document from file.
		 */ 
		private static function readXmlFromFile(xmlFile:File):XML
		{
			var fs:FileStream = new FileStream();
			fs.open(xmlFile, FileMode.READ);
			var xml:XML = XML(fs.readUTFBytes(fs.bytesAvailable));
			fs.close();
			return xml;			
		}
	}
}