WARNINGS=-Wall -Wunused -Wfloat-equal -Wparentheses -Wundef -Wextra -Wwrite-strings -fdiagnostics-show-option -Wno-unused-parameter 
CFLAGS= ${WARNINGS} -Iinclude -fPIC -mtune=native -march=native 
RELEASE_CFLAGS= -Wuninitialized -DNDEBUG -finline-functions -funroll-loops -finline-limit=3000 -fomit-frame-pointer -fno-strict-aliasing 
DEBUG_CFLAGS= -g3 -ggdb3 -DDEBUG -fno-strict-aliasing
WX_CFLAGS=`wx-config --cxxflags`
WX_LIBS=`wx-config --libs`
LINK_FLAGS=-Wl,-O1


all: debug/tp release/tp

clean:
	rm -rf debug release debug-teacher release-teacher

all-teacher: debug-teacher/tp-teacher release-teacher/tp-teacher



