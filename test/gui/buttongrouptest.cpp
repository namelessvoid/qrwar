#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "gui/ng/buttongroup.hpp"
#include "gui/ng/button.hpp"

#define BUTTONCOUNT 3

class ButtonGroupTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ButtonGroupTest);
	CPPUNIT_TEST(activateTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			group = new namelessgui::ButtonGroup();
			for(int i = 0; i < BUTTONCOUNT; ++i)
			{
				buttons[i] = new namelessgui::Button();
				group->addButton(buttons[i]);
			}
		}

		void tearDown()
		{
			delete group;
			for(int i = 0; i < BUTTONCOUNT; ++i)
				delete buttons[i];
		}

		void activateTest()
		{
			for(int i = 0; i < BUTTONCOUNT; ++i)
				CPPUNIT_ASSERT(buttons[i]->getState() == namelessgui::Button::EWS_INACTIVE);
			group->activateButton(buttons[0]);
			CPPUNIT_ASSERT(buttons[0]->getState() == namelessgui::Button::EWS_ACTIVE);
			CPPUNIT_ASSERT(buttons[1]->getState() == namelessgui::Button::EWS_INACTIVE);
			group->activateButton(buttons[2]);
			CPPUNIT_ASSERT(buttons[0]->getState() == namelessgui::Button::EWS_INACTIVE);
			CPPUNIT_ASSERT(buttons[1]->getState() == namelessgui::Button::EWS_INACTIVE);
			CPPUNIT_ASSERT(buttons[2]->getState() == namelessgui::Button::EWS_ACTIVE);
		}


	private:
		namelessgui::ButtonGroup* group;
		namelessgui::Button* buttons[BUTTONCOUNT];
};

CPPUNIT_TEST_SUITE_REGISTRATION(ButtonGroupTest);
