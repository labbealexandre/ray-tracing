Instructions de compilation (testé sur Linux)
- make pour compiler
- make clean pour supprimer les exécutables

Description des scènes
La description de la scène se fait via un fichier XML, le schéma est fourni dans le fichier scene.xsd
Pour connaître l'utilisation de ce format, un fichier example.xml est fourni et regroupe les objets disponibles (sphère, plan, polygone)

Instructions pour l'exécution
- l'exécutable est le fichier main, il a besoin d'exactement 2 arguments :
  - le chemin d'accès du fichier xml d'entrée
  - le chemin d'accès de l'image de sortie
- l'image de sortie est au format ppm

Mise en garde pour l'utilisation
- Les textures n'ont pas été implémentées pour les objets polygones (classe objet) et sphère
  Il faut cependant fournir le chemin d'une texture par défaut
- Les textures non carrées posent problème et ceci n'a pas été résolu. Il est recommandé d'utliser des    textures carrées.
- Les textures doient être au format ppm (+le fichier ne doit pas comporter de commentaire)
- Les polygones renseignés dans le XML sont triangulés. L'implémentation de cette triangulation n'a pas été menée à son terme. Seuls les polygons monotones sont compatibles.