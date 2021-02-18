@echo off

cmd /C copystyles.bat -a -p FromParagraphStyles.idml ToParagraphStyles.idml CopyAllParagraphStylesResult.idml
cmd /C copystyles.bat -e -p FromParagraphStyles.idml ToParagraphStyles.idml CopyExistingParagraphStylesResult.idml
cmd /C copystyles.bat -n -p FromParagraphStyles.idml ToParagraphStyles.idml CopyNewlParagraphStylesResult.idml

cmd /C copystyles.bat -e -o FromObjectStyles.idml ToObjectStyles.idml CopyExistingObjectStylesResult.idml

