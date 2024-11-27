# Nom de l'exécutable
EXEC = main

# Compilateur
CXX = g++ # Ou clang++, si vous préférez

# Options de compilation
CXXFLAGS = -g -Wall -Wextra -Werror

# Options de liaison (pour SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Liste des fichiers source
SRCS = main.cpp Cellule.cpp

# Générer les fichiers objets correspondants
OBJS = $(SRCS:.cpp=.o)

# Cible par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Règle pour créer les fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(EXEC)
