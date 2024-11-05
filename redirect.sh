#!/bin/bash
echo "Redirect URLs embedded in PDF files in the current folder"
echo "which point to the server at https://metamagical-musings.github.io"
echo "so that they point to the current folder instead."
echo
./redirect https://metamagical-musings.github.io
echo
echo "Press entoer to continue..."
read input
