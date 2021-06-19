add_llvm_library( MakeDot MODULE BUILDTREE_ONLY
  MakeDot.cpp
  
  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
