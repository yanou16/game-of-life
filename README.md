# Game of Life
Le Jeu de la Vie de Conway est une simulation basée sur des automates cellulaires, implémentée en C++ avec SFML pour une interface interactive et intuitive. Cette version permet une personnalisation avancée, une interaction en temps réel et une distinction visuelle entre les cellules créées par l'utilisateur et celles générées automatiquement.

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

## 🎨 Fonctionnalités

### Interface Graphique (SFML)
- ✨ Grille interactive avec cellules colorées
- 🖱️ Interaction souris pour activer/désactiver les cellules
- ⌨️ Contrôles clavier complets
- 📊 Affichage des statistiques en temps réel

### Patterns Prédéfinis
- 🛸 Planeur (Glider)
- ⬛ Bloc (Block)
- 💫 Clignotant (Blinker)

### Contrôles Détaillés
| Touche | Action |
|--------|--------|
| A | Pause/Reprise |
| +/- | Ajuster la vitesse |
| C | Effacer la grille |
| R | Remplissage aléatoire |
| G | Placer un planeur |
| B | Placer un bloc |
| L | Placer un clignotant |

### Fonctionnalités Avancées
- 🎨 Différenciation visuelle des cellules (utilisateur/automatique)
- ⚡ Contrôle de la vitesse de simulation
- 💾 Sauvegarde/Chargement d'états
- 📊 Statistiques en temps réel

## 🏗️ Architecture Technique

## Classes Principales

## 🎮 GameOfLife
- Gestion centrale de la simulation et des règles du jeu.
- Contrôle du cycle de vie : initialisation, mise à jour et rendu.
- Interface avec les renderers pour l'affichage (graphique ou console).

## 📐 Grid
- Gestion de la grille contenant les cellules du jeu.
- Implémentation des règles d'évolution pour chaque génération.
- Calcul des états futurs des cellules (vivantes ou mortes) et gestion des voisins.

## 🧩 Cell
- Représentation individuelle d'une cellule.
- Contient son état (vivante ou morte) et sa position sur la grille.
- Fournit des méthodes pour définir ou obtenir son état.

## 🖼️ Render (Interface)
- Interface abstraite définissant les fonctionnalités des modules de rendu.
- SFMLRender : Gestion du rendu graphique avec SFML pour une interface utilisateur interactive et visuelle.
- ConsoleRender : Rendu texte en mode console pour une visualisation simple.

## 📂 FileService
- Gestion des opérations liées aux fichiers et répertoires pour le jeu.
- Sauvegarde : Enregistre l'état de la grille dans un fichier texte.
- Chargement : Lit un état initial depuis un fichier pour configurer la grille.
- Exportation : Génération de fichiers pour enregistrer les états successifs de la simulation.
- Gestion des répertoires : Création et vérification des dossiers nécessaires pour les fichiers.

## 🧪 Tests

### Test Unitaire Principal
```cpp
TEST_METHOD(TestGridValidityAtIterationT)
```

Aspects Testés
✅ Validité de la grille à l'itération t
✅ Comportement des patterns
✅ Règles de transition
✅ Gestion des limites

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

```
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
```

## 🤝 Contribution

1. Forkez le projet.
2. Créez votre branche (`git checkout -b feature/AmazingFeature`).
3. Commitez vos modifications (`git commit -m 'Add some AmazingFeature'`).
4. Pushez vers votre branche (`git push origin feature/AmazingFeature`).
5. Ouvrez une Pull Request.

## 📝 Licence

Ce projet est sous licence MIT. Consultez le fichier `LICENSE` pour plus de détails.

## 👥 Auteurs
Les auteurs de ce guide et les reponsables du projet: @shenzhenyz @yannou16



# Version Finale
Version actuelle et stable du jeu :
- Pause avec touche 'A'
- Cellules bleues pour création utilisateur
- Cellules vertes pour génération automatique
- Contrôle de vitesse optimisé
- Interface utilisateur complète



![image](https://github.com/user-attachments/assets/7261aac5-a3c1-493b-98cd-4499aabf70ea)
