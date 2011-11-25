OBJ = obj/UnixPong.o \
      obj/Paddle.o \
	  obj/Timer.o \
	  obj/Ball.o \
	  obj/Doodad.o \
	  obj/LocalController.o \
	  obj/ControllerBase.o \
	  obj/ComputerController.o \
	  obj/GameState.o \
	  obj/Connection.o

SDL_LDFLAGS = `pkg-config sdl --libs`
GL_LDFLAGS = `pkg-config gl --libs`
SDL_CXXFLAGS = `pkg-config sdl --cflags`
GL_CXXFLAGS = `pkg-config gl --cflags`

CXXFLAGS = -c -g3 -Wall -Iinclude $(SDL_CXXFLAGS) $(GL_CXXFLAGS)
LDFLAGS = $(SDL_LDFLAGS) $(GL_LDFLAGS)

TARGET = unixpong

$(TARGET): $(OBJ)
	@echo "Linking... $@"
	@$(CXX) $(LDFLAGS) -o $@ $(OBJ)

obj/%.o: src/%.cpp
	@[ -d "obj" ] || mkdir "obj"
	@echo "Compiling: $@"
	@$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	@rm -f $(TARGET)
	@rm -f obj/*.o
