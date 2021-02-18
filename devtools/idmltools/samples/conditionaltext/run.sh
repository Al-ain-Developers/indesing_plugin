#!/bin/sh

sh conditionaltext.sh -off "Print Only" ConditionalText.idml  ConditionalText-PrintOnlyOff.idml
sh conditionaltext.sh -on "Print Only" ConditionalText-PrintOnlyOff.idml ConditionalText-PrintOnlyOn.idml