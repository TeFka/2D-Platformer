# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_sources
    ${CMAKE_CURRENT_LIST_DIR}/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/ParticleEngine2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/RenderEngine2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/2DPlatformerGame.cpp
	${CMAKE_CURRENT_LIST_DIR}/2DPlatformerGameLevel.cpp
	${CMAKE_CURRENT_LIST_DIR}/Entity2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Player2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Enemy2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Weapon2D.cpp
)

# /CMakeLists.txt-------------------------------------------------------------