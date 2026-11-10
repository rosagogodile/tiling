# Created 10/12/2026
# Last Edited 11/10/2026

TARGET := out

CPP_FILES := tile.cpp colorlut.cpp tiling.cpp stereographic_projection.cpp main.cpp 

LINKED_LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm
VERSION := -std=c++23
RAYLIB_PATH := C:\raylib\raylib\src

# compiles and then runs the program
run: $(TARGET).exe
	./$(TARGET).exe

# compiles the program
$(TARGET).exe: $(CPP_FILES)
	g++ -Wall $(CPP_FILES) -o $(TARGET).exe -I $(RAYLIB_PATH) -O1 $(VERSION) -Wno-missing-braces -L ./lib/ $(LINKED_LIBS)

# removes all compiled executables and libraries 
# also removes all compiled object files, in the event that compilation fails for something else
clean:
	rm -f $(TARGET).exe
	rm -f *.a
	rm -f *.o