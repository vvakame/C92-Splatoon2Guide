#!/bin/bash -eux

gs \
  -sOutputFile=articles/C92-Splatoon2Guide-gray.pdf \
  -sDEVICE=pdfwrite \
  -dPDFX \
  -dCompatibilityLevel=1.3 \
  -sColorConversionStrategy=Gray \
  -dProcessColorModel=/DeviceGray \
  -dNOPAUSE \
  -dBATCH \
  articles/C92-Splatoon2Guide.pdf
