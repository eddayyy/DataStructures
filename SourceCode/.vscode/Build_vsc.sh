#!/usr/bin/env bash
#
# Script file to compile all C++ source files in or under the
# current directory.  This has been used in the OpenSUSE and Ubuntu
# environments with the GCC and Clang compilers and linkers

clear
BuildTaskName="$1"
echo -e "$BuildTaskName\n"  # Build Title





### Vendors are releasing version of their C++ compilers and libraries with ever more C++20 compliant features, but
### they're not fully compliant yet.  And Linux vendors are slow to make these new versions available.  As a result,
### we see in practice various degrees of compliance which we can compensate for by providing the missing pieces in a
### header file that is added to each translation unit.  We search for such a header file first in the current working
### directory, then in the same directory as this build script, and if not found in either of those locations we create
### create it on the fly.  This search order allows such a (potentially updated) header file to be provided with each
### project.
complianceHelperFile_filename="Compliance_Workarounds.hpp"

complianceHelperFile_path="./${complianceHelperFile_filename}"
if [[ ! -f "${complianceHelperFile_path}" ]]; then                                   # Is the helper file in the current directory?
  complianceHelperFile_path="${0%/*}/${complianceHelperFile_filename}"
  if [[ ! -f "${complianceHelperFile_path}" ]]; then                                 # Is the helper file in the same directory as this script (Build.sh)
    complianceHelperFile_path=/dev/null                                              # No helper file is to be used
  fi
fi



# Find and display all the C++ source files to be compiled ...
# temporarily ignore spaces when globing words into file names
temp=$IFS
  IFS=$'\n'
  sourceFiles=( $(find ./ -path ./.\* -prune -o -name "*.cpp" -print) ) # create array of source files skipping hidden folders (folders that start with a dot)
IFS=$temp

echo "compiling in \"$PWD\" ..."
for fileName in "${sourceFiles[@]}"; do
  echo "  $fileName"
done
echo ""


#define options
GccOptions="  -Wall -Wextra -pedantic        \
              -Wdelete-non-virtual-dtor      \
              -Wduplicated-branches          \
              -Wduplicated-cond              \
              -Wextra-semi                   \
              -Wfloat-equal                  \
              -Winit-self                    \
              -Wlogical-op                   \
              -Wnoexcept                     \
              -Wshadow                       \
              -Wnon-virtual-dtor             \
              -Wold-style-cast               \
              -Wstrict-null-sentinel         \
              -Wsuggest-override             \
              -Wswitch-default               \
              -Wswitch-enum                  \
              -Woverloaded-virtual           \
              -Wuseless-cast                 "

#             -Wzero-as-null-pointer-constant"


ClangOptions=" -stdlib=libc++ -Weverything        \
               -Wno-comma                         \
               -Wno-unused-template               \
               -Wno-sign-conversion               \
               -Wno-exit-time-destructors         \
               -Wno-global-constructors           \
               -Wno-missing-prototypes            \
               -Wno-weak-vtables                  \
               -Wno-padded                        \
               -Wno-double-promotion              \
               -Wno-c++98-compat-pedantic         \
               -Wno-c++11-compat-pedantic         \
               -Wno-c++14-compat-pedantic         \
               -Wno-c++17-compat-pedantic         \
               -Wno-c++20-compat-pedantic         \
               -fdiagnostics-show-category=name   \
                                                  \
               -Wno-zero-as-null-pointer-constant \
               -Wno-ctad-maybe-unsupported        "

CommonOptions="-pthread -std=c++20 -I./ -DUSING_TOMS_SUGGESTIONS -D__func__=__PRETTY_FUNCTION__"




if [ $Compiler = 'clang++' ]; then
  options="$Options $CommonOptions $ClangOptions"

elif [ $Compiler = 'g++' ]; then
  options="$Options $CommonOptions $GccOptions"
fi

echo $Compiler $options -include \"${complianceHelperFile_path}\"
$Compiler --version
$Compiler $options -include "${complianceHelperFile_path}" -o "$Executable" "${sourceFiles[@]}" && echo -e "\nSuccessfully created  \"$Executable\""
