The libraries may be outdated.You may go to their website to get the latest.
These folders contain sources which were used in order to make the game.

Warcraft II HD 
Libraries

	WARNING: There may be compatibility issues with the latest versions.

	SFML 2.5.1 (32bit) SETUP:
				Link every library according to the setup tutorials found on internet.
				Small guide:
					Open to Warcraft II.sln
					Right Click -> Properties
					Set Configuration to All Configurations
					Find C/C++ -> General in the right-side menu
					In Additional Include Directories Open SFML-<version>\include and add it (ex.SFML-2.5.0\include)
					Find Linker in the right-side menu
					In Additional Library Directories Open SFML-<version>\lib and add it (ex.SFML-2.5.0\lib)
					Find Linker -> Input in the right-side menu
					Set Configuration to Release
					In Additional Dependencies add sfml-graphics.lib sfml-window.lib sfml-system.lib sfml-network.lib sfml-audio.lib
					Set Configuration to Debug
					In Additional Dependencies add sfml-graphics-d.lib sfml-window-d.lib sfml-system-d.lib sfml-network-d.lib sfml-audio-d.lib
					
				(as of version 0.5.0 the game does not use the SFML network library. Setup is optional, but probably needed in later versions)
				
	NLOHMANN NOTES:
				According to the developer this library NEEDS support for C++11.
				WARNING: I renamed the default namespace to io(instead of nlohmann) for simplicity.