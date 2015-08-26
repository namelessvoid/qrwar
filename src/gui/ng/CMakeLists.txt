add_library(namelessgui
	button.cpp
	buttongroup.cpp
	label.cpp
	radiotogglebutton.cpp
	spritewidget.cpp
	widget.cpp
	window.cpp
)
target_link_libraries(namelessgui ${SFML_LIBRARIES})
