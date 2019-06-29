build:
ifeq (${EXERCISE},)
	@echo "EXERCISE not set"
	@exit 1
endif
	echo "building ./bin/$(EXERCISE)"
	gcc ${EXERCISE}.cpp glad.c \
		-Wall -Wextra -Werror \
		-Iinclude \
		-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++ \
		-o ./bin/${EXERCISE}
