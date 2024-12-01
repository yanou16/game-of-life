# Game of Life

Une implémentation du Jeu de la Vie de Conway en C++ avec SFML, permettant une interaction utilisateur avancée et une distinction visuelle entre les cellules créées par l'utilisateur et celles générées automatiquement.

## 📋 Table des matières
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Configuration](#configuration)
- [Utilisation](#utilisation)
- [Fonctionnalités](#fonctionnalités)
- [Structure du projet](#structure-du-projet)
- [Contribution](#contribution)

## 🔧 Prérequis

- Windows 10 ou plus récent
- Visual Studio 2019 ou plus récent
- SFML 2.5.1 ou plus récent
- C++17 ou plus récent

## 💻 Installation

1. Clonez le dépôt :
```bash
git clone https://github.com/yanou16/ssp.git

Ouvrez le projet dans Visual Studio :
Double-cliquez sur le fichier .sln
Ou ouvrez Visual Studio et sélectionnez "Ouvrir un projet"
Configurez SFML :
Les dépendances SFML sont incluses dans le projet
Vérifiez que les chemins dans les propriétés du projet sont corrects
Compilez le projet :
Sélectionnez la configuration "Debug" ou "Release"
Cliquez sur "Générer la solution" ou appuyez sur F7

⚙️ Configuration
Le jeu peut être configuré de plusieurs façons :

Modification de la taille de la grille dans le fichier principal
Personnalisation de l'état initial via un fichier texte
Ajustement de la vitesse de simulation en jeu


Format du fichier d'état initial (initial_state.txt) :


5 10  // Hauteur Largeur
0 1 0 0 0 1 1 0 0 0
0 0 1 0 0 1 1 0 0 0
1 1 1 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0




🎮 Utilisation
Contrôles
Souris :
Clic gauche : Créer une cellule
Clic droit : Supprimer une cellule
Clavier :
Espace : Pause/Reprise
+/- : Ajuster la vitesse
C : Effacer la grille
R : Remplissage aléatoire
G : Placer un planeur
B : Placer un bloc
L : Placer un clignotant
H : Afficher l'aide
Code Couleur
🟦 Bleu : Cellules créées par l'utilisateur
🟩 Vert : Cellules générées automatiquement
⬛ Noir : Cellules mortes
🌟 Fonctionnalités
Interface graphique avec SFML
Distinction visuelle des cellules selon leur origine
Formes prédéfinies (planeur, bloc, clignotant)
Chargement d'état initial depuis un fichier
Contrôle de la vitesse de simulation
Mode pause
Grille redimensionnable
📁 Structure du projet
Code
CopyInsert
ssp/
├── src/
│   ├── Cell.cpp        # Gestion des cellules individuelles
│   ├── Grid.cpp        # Logique de la grille
│   ├── GameOfLife.cpp  # Classe principale
│   └── SFMLRender.cpp  # Rendu graphique
├── include/
│   ├── Cell.hpp
│   ├── Grid.hpp
│   ├── GameOfLife.hpp
│   └── SFMLRender.hpp
└── resources/
    └── initial_state.txt
🤝 Contribution
Fork le projet
Créez votre branche (git checkout -b feature/AmazingFeature)
Committez vos changements (git commit -m 'Add some AmazingFeature')
Push vers la branche (git push origin feature/AmazingFeature)
Ouvrez une Pull Request
📝 License
Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

👥 Auteurs
@yanou16
🙏 Remerciements
Merci à John Conway pour l'invention du Jeu de la Vie
SFML pour la bibliothèque graphique

![image](https://github.com/user-attachments/assets/84b15316-e3fe-44db-9d3f-7d8f752f5ca7)
![image](https://github.com/user-attachments/assets/3bf718fa-fed3-40c3-ae9f-9b7da206e0ad)
Modifier 
