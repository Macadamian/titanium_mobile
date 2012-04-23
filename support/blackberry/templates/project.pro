TEMPLATE = app
TARGET = ${config['target']}

# TODO Mac: Template the config and libs section
CONFIG += qt warn_on debug_and_release cascades

INCLUDEPATH += ../src
SOURCES += ../src/*.cpp
HEADERS += ../src/*.hpp ../src/*.h

device {
	CONFIG(release, debug|release) {
		DESTDIR = o.le-v7
	 }
	CONFIG(debug, debug|release)  {
		DESTDIR = o.le-v7-g
	}
}

simulator {
	CONFIG(release, debug|release) {
		DESTDIR = o
	}
	CONFIG(debug, debug|release) {
		DESTDIR = o-g
	}
}

# Disables default filtering
OBJECTS_DIR = $$${"DESTDIR" | n}/.obj
MOC_DIR = $$${"DESTDIR" | n}/.moc
RCC_DIR = $$${"DESTDIR" | n}/.rcc
UI_DIR = $$${"DESTDIR" | n}/.ui


