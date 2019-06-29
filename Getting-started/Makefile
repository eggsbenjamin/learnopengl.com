LIBS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++ -lm
INCLUDE := -Iinclude
FLAGS := -Wall -Wextra -Werror -Wno-type-limits 

build:
ifeq (${CHAPTER},)
	@echo "CHAPTER not set"
	@exit 1
endif
ifeq (${EXERCISE},)
	@echo "EXERCISE not set"
	@exit 1
endif
	@echo "building ./${CHAPTER}/bin/${EXERCISE}"
	@gcc ./${CHAPTER}/${EXERCISE}.cpp glad.c \
		${FLAGS} \
		${INCLUDE} \
		${LIBS} \
		-o ./${CHAPTER}/bin/${EXERCISE}

run:
	cd ./${CHAPTER} && ./bin/${EXERCISE}
