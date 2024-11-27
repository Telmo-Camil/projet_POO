# Nom de l'exécutable
EXEC = main

# Compilateur
CXX = clang++

# Options du compilateur
CXXFLAGS = -g -Wall -Wextra -Werror

# Options de l'éditeur de liens (pour SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

# Recherche des fichiers source (.cpp) et headers (.h)
SRCS = $(shell find . -type f -name '*.cpp' ! -path './.ccls-cache/*')
HEADERS = $(shell find . -type f -name '*.h' ! -path './.ccls-cache/*')

# Générer les fichiers objets à partir des fichiers sources
OBJS = $(SRCS:.cpp=.o)

# Cible par défaut
all: $(EXEC)

# Cible pour l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Compilation de chaque fichier objet
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cible pour le mode débogage
debug: CXXFLAGS += -O0 -DDEBUG
debug: clean $(EXEC)

# Nettoyage des fichiers générés
clean:
	rm -f $(EXEC) $(OBJS)
