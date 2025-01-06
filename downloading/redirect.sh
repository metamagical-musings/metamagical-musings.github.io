#!/bin/bash
echo "Redirect URLs embedded in PDF files in the parent folder"
echo "which point to the server at https://metamagical-musings.github.io"
echo "so that they point to the parent folder instead."
echo ""
cd ..
./downloading/redirect https://metamagical-musings.github.io
echo ""
echo "Press the enter key to continue..."
read input
