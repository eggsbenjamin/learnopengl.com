build:
ifeq (${CHAPTER},)
	@echo "CHAPTER not set"
	@exit 1
endif
ifeq (${EXERCISE},)
	@echo "EXERCISE not set"
	@exit 1
endif
	echo "building ./${CHAPTER}/bin/${EXERCISE}"
	gcc ./${CHAPTER}/${EXERCISE}.cpp glad.c \
		-Wall -Wextra -Werror \
		-Iinclude \
		-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++ -lm \
		-o ./${CHAPTER}/bin/${EXERCISE}
