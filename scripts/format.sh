#!/bin/bash
# This script is used to format the code in the repository.

sources="find src test -type f -name *\.hpp -o -name *\.cpp"
$sources | xargs -I {} sh -c "clang-format -i {}; echo -n '.'"
