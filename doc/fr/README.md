# Ray-Tracing

## Installation

Le fichier input.cpp par défaut n'existe pas dans le dossier src. Il peut être copié depuis le fichier template input.cpp.template

```
cp src/input.template.cpp src/input.cpp
```

C'est ce fichier que sera améné à être remplacé s'il on souhaite utiliser le langage RayLang de description de scènes :
https://gitlab.data-ensta.fr/alabbe/ray_lang

## Instructions de compilation (testé sous Linux)

- make pour compiler
- make clean pour supprimer les exécutables

## Description des scènes
La description de la scène se fait via un fichier XML, le schéma est fourni dans le fichier scene.xsd
Pour connaître l'utilisation de ce format, un fichier example.xml est fourni et regroupe les objets disponibles (sphère, plan, polygone)

## Instructions pour l'exécution
- l'exécutable est le fichier main, il a besoin d'exactement 2 arguments :
  - le chemin d'accès du fichier xml d'entrée
  - le chemin d'accès de l'image de sortie
- l'image de sortie est au format tga
- RayLang : s'il on souhaite utiliser un fichier input.cpp généré par le compilateur de RayLang (adresse du repo plus haut), il suffit de l'ajouter au src et de lancer l'exécutable avec un seul argument :
  - le chemin d'accès de l'image de sortie

## Voici un exemple d'exécution

```
mkdir assets
./bin/main scenes/ReflexionSphere.xml assets/ReflexionSphere.tga
```

Avec un fichier input.cpp compilé en RayLang

```
mkdir assets
./bin/main assets/rtl.tga
```

## Mise en garde pour l'utilisation
- Les textures n'ont pas été implémentées pour les objets polygones (classe objet) et sphère
  Il faut cependant fournir le chemin d'une texture par défaut
- Les textures non carrées posent problème et ceci n'a pas été résolu. Il est recommandé d'utliser des    textures carrées.
- Les textures doient être au format ppm (+le fichier ne doit pas comporter de commentaire)
- Les polygones renseignés dans le XML sont triangulés. L'implémentation de cette triangulation n'a pas été menée à son terme. Seuls les polygons monotones sont compatibles.

Pour de plus amples informations sur les fonctionnalités, veuillez consulter le fichier doc.txt et pour
comprendre l'architecture des classes, veuillez vous référer à l'image architecture.png