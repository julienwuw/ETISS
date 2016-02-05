FILE(REMOVE_RECURSE
  "libLLVMJIT_make_genheader.pdb"
  "libLLVMJIT_make_genheader.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/LLVMJIT_make_genheader.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
