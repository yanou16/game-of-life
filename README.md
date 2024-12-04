


# 🎮 Jeu de la Vie (Game of Life)
> Une implémentation avancée de l'automate cellulaire de Conway en C++


## 📋 Table des matières
- [Prérequis](#prérequis)
- [Installation](#installation)
1. [Vue d'ensemble](#vue-densemble)
2. [Fonctionnalités](#fonctionnalités)
3. [Architecture Technique](#architecture-technique)
4. [Tests](#tests)
5. - [Structure du projet](#structure-du-projet)
6. [Installation](#installation)
7. [Guide d'Utilisation](#guide-dutilisation)
8. [Développement](#développement)

## 🌟 Vue d'ensemble
Ce projet est une implémentation du Jeu de la Vie de Conway avec deux modes de rendu :
- Interface graphique avec SFML
- Mode console pour une utilisation sans interface graphique

### 🎯 Objectifs du Projet
- Implémenter les règles classiques du Jeu de la Vie
- Fournir une interface utilisateur interactive
- Assurer la qualité du code via des tests unitaires
- Permettre la sauvegarde et le chargement d'états

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
| Espace | Pause/Reprise |
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

### Structure du Projet



### Classes Principales
#### 🎮 GameOfLife
- Gestion du jeu
- Contrôle de la simulation
- Interface avec les renderers

#### 📐 Grid
- Implémentation des règles
- Gestion des états des cellules
- Calcul des générations

#### 🖼️ Render (Interface)
- `SFMLRender`: Rendu graphique
- `ConsoleRender`: Rendu texte

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
💻 Installation
Prérequis
Visual Studio 2022
SFML 2.6.1
C++17 ou supérieur
{
    // Test sur grille 5x10
    Grid grid(10, 5);
    
    // Configuration et vérification du blinker
    // Validation à t=0 et t=1
}

Aspects Testés
✅ Validité de la grille à l'itération t
✅ Comportement des patterns
✅ Règles de transition
✅ Gestion des limites
💻 Installation
Prérequis
Visual Studio 2022
SFML 2.6.1
C++17 ou supérieur

Étapes d'Installation
Cloner le repository
git clone [url-du-repo]
cd ssp

Configuration SFML
Inclure les headers SFML
Lier les bibliothèques
Copier les DLLs
📖 Guide d'Utilisation
Mode Graphique
Lancer l'application
Utiliser la souris pour placer les cellules
Espace pour démarrer/pauser
Touches G/B/L pour les patterns
Mode Console
Lancer en mode console
Suivre les instructions à l'écran
Utiliser les commandes du menu
🛠️ Développement
Branches
master: Version stable
ol2: Développement actif
Contributions Récentes
✨ Refactoring architecture
🧪 Ajout tests unitaires
🎨 Amélioration interface
🐛 Corrections bugs
Standards de Code
Style C++ moderne
Principes SOLID
Documentation complète


📝 Notes
Projet en développement actif
Tests unitaires en expansion
Optimisations prévues











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
