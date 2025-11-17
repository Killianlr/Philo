## 🧠 Philosophers — Simulation en C

Projet d’école visant à implémenter des philosophes autour d’une table, en utilisant le multithreading et des mutex pour gérer la concurrence.

## 🎯 Objectif du projet

Simuler le comportement de plusieurs philosophes assis autour d’une table.
Chaque philosophe alterne entre penser, manger et dormir.
Pour manger, un philosophe doit obtenir deux fourchettes (une à sa gauche et une à sa droite).

## ⚙️ Fonctionnement

Le programme prend en arguments :

./philo <philo_number> <time_to_die> <time_to_eat> <time_to_sleep> [nb_times_each_philo_must_eat]

### exemple :
```
./philo 6 800 200 200 12
```
philo_number : nombre de philosopher 

time_to_die : temps en ms avant qu’un philosophe meure s’il ne mange pas

time_to_eat : durée d’un repas

time_to_sleep : durée de sommeil

nb_times_each_philo_must_eat (optionnel) : condition d’arrêt si tous les philosophes ont mangé un certain nombre de fois

Le programme crée un thread par philosophe, et utilise des mutex pour représenter les fourchettes.

## 🧵 Concurrence & Synchronisation

Un thread par philosophe

Une mutex par fourchette

Gestion fine de l’accès aux ressources partagées pour éviter les blocages

Option d’arrêt propre lorsque tous les philosophes ont atteint le quota de repas

## 📝 Ce que le projet démontre

Maîtrise du multithreading en C

Synchronisation via mutex

Prévention du deadlock

Gestion d’un cycle de vie complexe avec contraintes temporelles
