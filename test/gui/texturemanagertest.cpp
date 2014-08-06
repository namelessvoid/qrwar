#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include <SFML/Graphics/Texture.hpp>

#include "gui/texturemanager.hpp"


class TextureManagertest : public CppUnit::TestFixture
{
    // Setup testsuit
    CPPUNIT_TEST_SUITE(TextureManagertest);
    CPPUNIT_TEST(testLoad);
    CPPUNIT_TEST(testLoadWithDimensions);
    CPPUNIT_TEST(testUnload);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp()
        {
            tm = qrw::TextureManager::getInstance();
        }

        void tearDown()
        {
        }

        void testLoad()
        {
            // First time load of texture, should succeed.
            tm->loadTexture("defaulttileset", "res/img/defaulttileset.png");
            const sf::Texture* text1 = tm->getTexture("defaulttileset");
            CPPUNIT_ASSERT(text1 != NULL);

            // Second time just return texture pointer, should be at same adress.
            tm->loadTexture("defaulttileset", "res/img/defaulttileset.png");
            const sf::Texture* text2 = tm->getTexture("defaulttileset");
            CPPUNIT_ASSERT(text1 == text2);

            // Try to load from file that does not exist.
            tm->loadTexture("INVALIDTEXTURE", "INVALIDTEXTURE");
            const sf::Texture* text3 = tm->getTexture("INVALIDTEXTURE");
            CPPUNIT_ASSERT(text3 == tm->getFallbackTexture());
        }

        void testLoadWithDimensions()
        {
            tm->unloadTexture("defaulttileset");
            tm->loadTexture("defaulttileset", "res/img/defaulttileset.png", sf::IntRect(1, 1, 3, 4));
            const sf::Texture* text = tm->getTexture("defaulttileset");
            CPPUNIT_ASSERT(text->getSize() == sf::Vector2u(3, 4));

            // Check if upper left corner was loaded correctly. ATTENTION: This test fails
            // if the used defaulttileset.png file changed!
            // (See separation of test data issue: https://github.com/namelessvoid/qrwar/issues/24 )
            sf::Image img = text->copyToImage();
            sf::Color expectedColor(49, 117, 49);
            CPPUNIT_ASSERT(img.getPixel(0, 0) == expectedColor);
        }

        void testUnload()
        {
            tm->loadTexture("defaulttileset", "res/img/defaulttileset.png");
            const sf::Texture* text1 = tm->getTexture("defaulttileset");
            CPPUNIT_ASSERT(text1 != NULL);
            tm->unloadTexture("defaulttileset");
            text1 = tm->getTexture("defaulttileset");
            CPPUNIT_ASSERT(text1 == tm->getFallbackTexture());
        }

    private:
        qrw::TextureManager* tm;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TextureManagertest);
