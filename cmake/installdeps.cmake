# Usage
#   installdeps(${PROJECT_NAME} ${install_directory} ${pdb_directory})
#
# This macro is used to copy dll of dll or exe from runtime directory to an install directory
# proj_name : ${PROJECT_NAME}
# install directory : ${CMAKE_INSTALL_PREFIX}/something
# pdb directory : where to put pdb
macro(installdeps proj_name install_directory pdb_directory)
		install(CODE
		"file(MAKE_DIRECTORY \"${install_directory}\")
		SET(MAIN_TGT \"$<TARGET_FILE:${proj_name}>\")
		 file(GET_RUNTIME_DEPENDENCIES
				RESOLVED_DEPENDENCIES_VAR resolved_deps
				UNRESOLVED_DEPENDENCIES_VAR unresolved_deps
				LIBRARIES \${MAIN_TGT}
				)        
		get_filename_component(MAIN_DIR \${MAIN_TGT} DIRECTORY)
		get_filename_component(MAIN_PDB \${MAIN_TGT} NAME_WLE)
		SET(MAIN_PDB \"\${MAIN_DIR}/\${MAIN_PDB}.pdb\")
		if(EXISTS \"\${MAIN_PDB}\")
			if(NOT EXISTS \"${pdb_directory}\")
				file(MAKE_DIRECTORY \"${pdb_directory}\")
			endif()
			MESSAGE(\"Copy \${MAIN_PDB} to ${pdb_directory}\")
			configure_file(\${MAIN_PDB} \"${pdb_directory}\" COPYONLY)
		endif()
		# get only files/dependencies in subfolder
		string(TOLOWER \${MAIN_DIR} LOWER_MAIN_DIR)        
		foreach(SINGLE_FILE \${resolved_deps})
		   string(TOLOWER \${SINGLE_FILE} SINGLE_FILE_OUT)
		   if (\${SINGLE_FILE_OUT} MATCHES \"^(\${LOWER_MAIN_DIR})\")
			MESSAGE(\"Copy \${SINGLE_FILE} to ${install_directory}\")
			configure_file(\${SINGLE_FILE} \"${install_directory}\" COPYONLY)                                  
			get_filename_component(SINGLE_PDB \${SINGLE_FILE} NAME_WLE)
			SET(SINGLE_PDB \"\${MAIN_DIR}/\${SINGLE_PDB}.pdb\")
			if(EXISTS \"\${SINGLE_PDB}\")
				MESSAGE(\"Copy \${SINGLE_PDB} to ${pdb_directory}\")
				configure_file(\${SINGLE_PDB} \"${pdb_directory}\" COPYONLY)
			endif()
		   endif()
		endforeach()
		"
		)
endmacro()