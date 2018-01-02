add_library(namelessgui
        gui.cpp
	button.cpp
	buttongroup.cpp
        text.cpp
        label.cpp
        lineinput.cpp
        radiotogglebutton.cpp
	spritewidget.cpp
	widget.cpp
	window.cpp
        confirmationdialog.cpp
)
target_link_libraries(namelessgui ${SFML_LIBRARIES})
