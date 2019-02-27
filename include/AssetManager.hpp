#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace stickman
{
	/**@class AssetManager
	 * @brief      Class for asset manager.This class loads a texture and creates a map between textures and strings so that we don't have to load the same texture and sprite again and again.
	 */
	class AssetManager
	{
	public:
		/**
		 * @brief      Constructs the object.
		 */
		AssetManager() { }
		/**
		 * @brief      Destroys the object.
		 */
		~AssetManager() { }

		/**
		 * @brief      Loads a texture and maps it to a string.
		 *
		 * @param[in]  name      The string with which it will be mapped.
		 * @param[in]  fileName  The string which has the filepath to the texture.
		 */
		void LoadTexture(std::string name, std::string fileName);
		/**
		 * @brief      Gets a texture by its name as specified in the dictionary.
		 *
		 * @param[in]  name  The name of the texture to fetch
		 *
		 * @return     The texture.
		 */
		sf::Texture &GetTexture(std::string name);

		/**
		 * @brief      Loads a font and maps it to a string
		 *
		 * @param[in]  name      The string with which it will be mapped.
		 * @param[in]  fileName  The string which has the filepath to the font.
		 */
		void LoadFont(std::string name, std::string fileName);
		/**
		 * @brief      Gets a font by its name as specified in the dictionary
		 *
		 * @param[in]  name  The name of the font to fetch
		 *
		 * @return     The font.
		 */
		sf::Font &GetFont(std::string name);

	private:
		/**
		 * The map for the textures
		 */
		std::map<std::string, sf::Texture> _textures;
		/**
		 * The map for the fonts
		 */
		std::map<std::string, sf::Font> _fonts;
	};
}
