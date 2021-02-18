#!/bin/sh

sh copystyles.sh -a -p FromParagraphStyles.idml ToParagraphStyles.idml CopyAllParagraphStylesResult.idml
sh copystyles.sh -e -p FromParagraphStyles.idml ToParagraphStyles.idml CopyExistingParagraphStylesResult.idml
sh copystyles.sh -n -p FromParagraphStyles.idml ToParagraphStyles.idml CopyNewParagraphStylesResult.idml

sh copystyles.sh -e -o FromObjectStyles.idml ToObjectStyles.idml CopyExistingObjectStylesResult.idml

