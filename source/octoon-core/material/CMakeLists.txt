SET(LIB_OUTNAME material)

SET(HEADER_PATH ${OCTOON_PATH_HEADER}/${LIB_OUTNAME})
SET(SOURCE_PATH ${OCTOON_PATH_SOURCE}/octoon-core/${LIB_OUTNAME})

SET(MATERIAL_LIST
	${HEADER_PATH}/material.h
	${SOURCE_PATH}/material.cpp
	${HEADER_PATH}/points_material.h
	${SOURCE_PATH}/points_material.cpp
	${HEADER_PATH}/line_basic_material.h
	${SOURCE_PATH}/line_basic_material.cpp
	${HEADER_PATH}/mesh_basic_material.h
	${SOURCE_PATH}/mesh_basic_material.cpp
	${HEADER_PATH}/mesh_standard_material.h
	${SOURCE_PATH}/mesh_standard_material.cpp
	${HEADER_PATH}/mesh_depth_material.h
	${SOURCE_PATH}/mesh_depth_material.cpp
	${HEADER_PATH}/lambert_material.h
	${SOURCE_PATH}/lambert_material.cpp
)
SOURCE_GROUP(material  FILES ${MATERIAL_LIST})

LIST(APPEND MATERIAL_LIST ${MATERIAL_LIST})