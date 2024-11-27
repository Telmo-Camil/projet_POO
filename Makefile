# Nom de l'exécutable
EXEC = main

# Compilateur
CXX = g++ # Remplacez par clang++ si nécessaire

# Options du compilateur
CXXFLAGS = -g -Wall -Wextra -Werror

# Options de l'éditeur de liens (pour SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

# Recherche des fichiers source
SRCS = $(shell find . -type f -name '*.cpp' ! -path './.ccls-cache/*')
OBJS = $(SRCS:.cpp=.o)

# Cible par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(EXEC)
