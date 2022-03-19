# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_includes
    ${CMAKE_CURRENT_LIST_DIR}/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/ParticleEngine2D.h
	${CMAKE_CURRENT_LIST_DIR}/RenderEngine2D.h
	${CMAKE_CURRENT_LIST_DIR}/2DPlatformerGame.h
	${CMAKE_CURRENT_LIST_DIR}/2DPlatformerGameLevel.h
	${CMAKE_CURRENT_LIST_DIR}/Entity2D.h
	${CMAKE_CURRENT_LIST_DIR}/Player2D.h
	${CMAKE_CURRENT_LIST_DIR}/Enemy2D.h
	${CMAKE_CURRENT_LIST_DIR}/Weapon2D.h
)

# /CMakeLists.txt-------------------------------------------------------------