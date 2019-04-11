%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


$(SDL_BIN): $(SDL_OBJS)
	$(CC) -o $(SDL_BIN) $(SDL_OBJS) $(INCLUDE) $(SDL_LDFLAGS) $(SDL_LIBS) $(PLATFORM_FLAGS)

