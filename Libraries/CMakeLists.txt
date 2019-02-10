include_directories(../headers)
add_library(Libraries Game.cpp
		      AssetManager.cpp
		      InputManager.cpp
		      SplashState.cpp
		      StateMachine.cpp
			  MainMenuState.cpp
			)


