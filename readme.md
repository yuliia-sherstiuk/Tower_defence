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