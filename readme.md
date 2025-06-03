# README - Projet Tower Defense

## Introduction

Bienvenue dans le projet de Tower Defense ! 
Ce jeu de stratégie vous met au défi de défendre une zone contre des vagues incessantes d'ennemis en utilisant des tours stratégiquement placées. 
Ce document vous guidera à travers l'architecture du projet, les fonctionnalités, et les instructions pour le lancement du jeu.

## Architecture du Projet

### Modèle MVC

Le projet est structuré selon le modèle architectural MVC (Modèle-Vue-Contrôleur) :

- **Modèle (Model)** : Gère la logique, les données et les règles du jeu.
    - **Classes** :
        - `Tower` : Représente les tours de défense.
        - `Enemy` : Représente les ennemis qui attaquent.
        - `Wave` : Gère les vagues d'ennemis.
        - `Game` : Logique principale du jeu.
        - `ScoreManager` : Gère le score et les tableaux des scores.

- **Vue (View)** : Interface utilisateur.
    - **Composants** :
        - `MainMenu` : Menu principal du jeu.
        - `GameView` : Interface de jeu en cours.
        - `ScoreBoard` : Affichage des scores.
        - `Settings` : Options de jeu.

- **Contrôleur (Controller)** : Gère les interactions entre le modèle et la vue.
    - **Classes** :
        - `GameController` : Contrôle le flux du jeu.
        - `MenuController` : Gère les interactions du menu.
        - `SettingsController` : Gère les options de configuration.

### Design Patterns Utilisés

- **Singleton** : Pour le gestionnaire du son et la gestion du score, garantissant qu'il n'y a qu'une seule instance de ces classes.
- **Factory** : Pour créer dynamiquement des instances de tours et d'ennemis.

## Diagrammes UML

- **Diagramme de classes** : Illustre les relations entre les classes principales.
- **Diagramme utilisateur** : Montre les interactions de l'utilisateur avec le système.

## Fonctionnalités du Jeu

- **Vagues d'ennemis** : Gestion dynamique des vagues d'ennemis avec un timer.
- **Victoire/Défaite** : Conditions de victoire et de défaite basées sur l'arrivée des ennemis dans la zone protégée.
- **Gestion du score** : Calcul du score basé sur les ennemis éliminés et les vagues complétées, affiché dans un tableau des scores.
- **Gestion du son** : Options pour activer/désactiver la musique et les effets sonores.
- **Graphisme travaillé** : Interface attrayante avec des animations pour les tours et les ennemis.
- **Barres de vie des ennemis** : Barres de vie visibles pour chaque ennemi.
- **Évolutions des tours** : Système d'amélioration des tours.
- **Timer et compteur de vagues** : Affichage du temps restant pour la vague actuelle et le nombre de vagues restantes.
