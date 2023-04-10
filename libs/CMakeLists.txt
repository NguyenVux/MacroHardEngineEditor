macro(add_libs LIB_FOLDER)
	add_subdirectory(${LIB_FOLDER})
	list(APPEND LOCAL_LIBTARGETS ${LIB_FOLDER})
endmacro()

add_libs("MHTL")
set(LIB_TARGETS ${LOCAL_LIBTARGETS} ${parameter} PARENT_SCOPE)