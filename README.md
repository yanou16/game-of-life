# Game of Life
Le Jeu de la Vie de Conway est une simulation basée sur des automates cellulaires, implémentée en C++ avec SFML pour une interface interactive et intuitive. Cette version permet une personnalisation avancée, une interaction en temps réel et une distinction visuelle entre les cellules créées par l'utilisateur et celles générées automatiquement grâce aux extensions de notre projet du bloc POO: Game of Life.

## 📋 Table des matières
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Configuration](#configuration)
- [Utilisation](#utilisation)
- [Fonctionnalités](#fonctionnalités)
- [Structure du projet](#structure-du-projet)
- [Contribution](#contribution)
- [Licence](#licence)

## 🔧 Prérequis
- Windows 10 ou plus récent
- Visual Studio 2019 ou plus récent
- SFML 2.5.1 ou plus récent
- C++17 ou plus récent

## 💻 Installation
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/yanou16/ssp.git
   ```
2. Ouvrez le projet dans Visual Studio.
3. Configurez les dépendances pour SFML.
4. Compilez et lancez le projet.

## ⚙️ Configuration
Le jeu peut être configuré de plusieurs façons :

- **Taille de la grille** : modifiez les dimensions dans le fichier `main.cpp`.
- **État initial** : personnalisez le fichier `initial_state.txt` pour définir les cellules vivantes au démarrage.
- **Vitesse de simulation** : ajustez directement en jeu à l'aide des commandes clavier.

### Format du fichier d'état initial (`initial_state.txt`) :
```
5 10  // Hauteur Largeur
0 1 0 0 0 1 1 0 0 0
0 0 1 0 0 1 1 0 0 0
1 1 1 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
```

## 🎮 Utilisation

### Contrôles

#### Souris :
- **Clic gauche** : Créer une cellule.
- **Clic droit** : Supprimer une cellule.

#### Clavier :
- **Espace** : Pause/Reprise de la simulation.
- **+/-** : Ajuster la vitesse.
- **C** : Effacer toute la grille.
- **R** : Remplissage aléatoire de cellules.
- **G** : Placer un *planeur*.
- **B** : Placer un *bloc*.
- **L** : Placer un *clignotant*.
- **H** : Afficher l'aide en jeu.

### Code couleur :
- 🟦 **Bleu** : Cellules créées par l'utilisateur.
- 🟩 **Vert** : Cellules générées automatiquement.
- ⬛ **Noir** : Cellules mortes.

## 🌟 Fonctionnalités

- **Interface graphique** : Utilisation de SFML pour un rendu visuel.
- **Contrôles interactifs** : Modification de la grille en temps réel.
- **Formes prédéfinies** : Ajout rapide de motifs comme planeur, bloc ou clignotant.
- **Chargement d'état initial** : Lecture d'un fichier texte pour la configuration initiale.
- **Simulation dynamique** : Contrôle de la vitesse et mise en pause.
- **Grille redimensionnable** : Ajustable via le code source.

## 📁 Structure du projet


ssp/
├── components/
│   ├── Cell.cpp        # Gestion des cellules individuelles
│   ├── Cell.hpp
│   ├── Grid.cpp        # Logique de la grille
│   ├── Grid.hpp
├── ihm/
│   ├── ConsoleRender.cpp # Rendu texte (console)
│   ├── ConsoleRender.hpp
│   ├── SFMLRender.cpp    # Rendu graphique SFML
│   ├── SFMLRender.hpp
├── services/
│   ├── GameOfLife.cpp    # Classe principale du jeu
│   ├── GameOfLife.hpp
│   └── initial_state.txt # État initial de la grille
├── tests/
│   ├── Cell.cpp           # Tests unitaires pour Cell
│   ├── Grid.cpp           # Tests unitaires pour Grid
│   └── GameOfLifeTests1.cpp # Fichier principal des tests
├── main.cpp              # Point d'entrée du programme


## 🤝 Contribution

1. Forkez le projet.
2. Créez votre branche (`git checkout -b feature/AmazingFeature`).
3. Commitez vos modifications (`git commit -m 'Add some AmazingFeature'`).
4. Pushez vers votre branche (`git push origin feature/AmazingFeature`).
5. Ouvrez une Pull Request.

## 📝 Licence

Ce projet est sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

