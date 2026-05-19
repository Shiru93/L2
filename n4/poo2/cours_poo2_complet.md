# POO2 — Design Patterns en Java
> Cours complet • Université Paris XIII • Marc Champesme
> Tout ce qu'il faut savoir, expliqué depuis zéro.

---

## Table des matières

1. [C'est quoi un Design Pattern ?](#1-cest-quoi-un-design-pattern)
2. [Pattern Itérateur (Iterator)](#2-pattern-itérateur-iterator)
3. [Pattern Singleton & Enum](#3-pattern-singleton--enum)
4. [Pattern Strategy & Lambda](#4-pattern-strategy--lambda)
5. [Pattern Decorator](#5-pattern-decorator)
6. [Les Streams Java](#6-les-streams-java)
7. [Architecture MVC & Pattern Command](#7-architecture-mvc--pattern-command)
8. [Pattern Builder](#8-pattern-builder)
9. [Récapitulatif : les patterns en un coup d'œil](#9-récapitulatif--les-patterns-en-un-coup-dœil)
10. [Le projet Zork : contexte d'application](#10-le-projet-zork--contexte-dapplication)

---

## 1. C'est quoi un Design Pattern ?

### L'idée de base

Un **design pattern** (motif de conception) est une **solution réutilisable à un problème récurrent** de conception logicielle. Ce n'est pas du code à copier-coller, c'est une **recette** documentée que les développeurs expérimentés ont élaborée et transmise.

L'idée vient de l'architecte Christopher Alexander (fin des années 70) qui avait décrit des patterns pour construire des bâtiments. La communauté POO a repris ce concept, et en **1995** le livre "Design Patterns" des **Gang of Four** (Gamma, Helm, Johnson, Vlissides) est devenu la référence absolue.

### Pourquoi en a-t-on besoin ?

Tout logiciel évolue : nouvelles fonctionnalités, bibliothèques qui changent, bugs à corriger… Il faut donc concevoir du code **facile à modifier**. Les design patterns aident à respecter trois grands principes :

- **Séparer ce qui change** : isoler le code susceptible d'évoluer dans des classes dédiées, pour ne pas avoir à tout réécrire.
- **Programmer vers les interfaces**, pas vers les implémentations : ne pas dépendre des détails internes d'une classe.
- **Préférer la composition à l'héritage** : assembler des objets plutôt que créer des hiérarchies profondes de classes.

### Les trois catégories de patterns

| Catégorie | Rôle | Exemples vus en cours |
|---|---|---|
| **Création** | Comment créer des instances | Singleton, Builder |
| **Structurel** | Comment assembler/composer des classes | Decorator |
| **Comportemental** | Comment les classes communiquent et se comportent | Iterator, Strategy, Command |

### Anatomie d'un design pattern

Chaque pattern est décrit par :
- **Nom** et catégorie
- **Problème** à résoudre
- **Solution** proposée
- **Structure** : quelles classes définir, quels rôles
- **Exemple** en Java
- **Applicabilité** : quand l'utiliser (et quand ne pas l'utiliser)

---

## 2. Pattern Itérateur (Iterator)

### Le problème

Imaginons une `Piece` (salle du jeu Zork) qui contient des objets. On veut pouvoir parcourir tous ces objets. Mais comment ? Avec un tableau ? Une `ArrayList` ? Un autre stockage ?

Si on écrit `for (int i = 0; i < piece.size(); i++) { piece.get(i); }`, on est **lié à l'implémentation** : si demain on change de structure de données, tout le code de parcours doit changer. Et certaines structures (comme `Set`) n'ont même pas de méthode `get(i)` !

### La solution : l'interface `Iterator<E>`

Un **itérateur** est une abstraction qui permet de parcourir une collection **sans connaître son implémentation interne**. En Java, c'est l'interface :

```java
public interface Iterator<E> {
    boolean hasNext(); // Y a-t-il encore un élément à parcourir ?
    E next();          // Renvoie l'élément suivant et avance le curseur
    void remove();     // (optionnel) Supprime le dernier élément renvoyé
}
```

> ⚠️ Un itérateur ne peut être utilisé **qu'une seule fois** : il parcourt la collection du début à la fin, et c'est tout.

### L'interface `Iterable<E>`

Pour qu'une classe puisse être utilisée avec le `for` amélioré (foreach), elle doit implémenter `Iterable<E>` :

```java
public interface Iterable<E> {
    Iterator<E> iterator(); // renvoie un nouvel itérateur
}
```

Grâce à ça, si `Piece implements Iterable<ObjetZork>`, on peut écrire :
```java
Piece p = ...;
for (ObjetZork oz : p) {         // ← for amélioré
    System.out.println(oz);
}
```
Ce code est **équivalent** à :
```java
Iterator<ObjetZork> iter = p.iterator();
while (iter.hasNext()) {
    ObjetZork oz = iter.next();
    System.out.println(oz);
}
```

### Implémenter un itérateur sur tableau

Les tableaux Java n'implémentent pas `Iterable`. Pour itérer sur un tableau, on crée une classe dédiée :

```java
public class ArrayIterator<E> implements Iterator<E> {
    protected E[] tab;
    protected int size;
    protected int index;   // curseur, commence à 0

    public ArrayIterator(E[] tab, int size) {
        this.tab = tab;
        this.size = size;
        this.index = 0;
    }

    public boolean hasNext() {
        return this.index < size;
    }

    public E next() {
        return tab[index++]; // renvoie l'élément puis avance
    }
}
```

Et dans la classe `Piece` (ou `Array<E>`) :
```java
public class Array<E> implements Iterable<E> {
    private E[] elements;
    public final int length;

    public Iterator<E> iterator() {
        return new ArrayIterator<E>(elements, length);
    }
}
```

### L'interface `ListIterator<E>`

`ListIterator` est une extension de `Iterator` pour les listes ordonnées, qui ajoute la capacité de parcourir **dans les deux sens** :

```java
boolean hasPrevious();  // y a-t-il un élément précédent ?
E previous();           // renvoie l'élément précédent
int nextIndex();        // index de l'élément suivant
int previousIndex();    // index de l'élément précédent
```

Exemple d'implémentation (`ArrayListIterator`) héritant de `ArrayIterator` :
```java
public class ArrayListIterator<E> extends ArrayIterator<E> implements ListIterator<E> {
    public int nextIndex() { return this.index; }
    public boolean hasPrevious() { return this.index > 0; }
    public int previousIndex() { return hasPrevious() ? this.index - 1 : -1; }
    // ...
}
```

### La classe générique `Array<E>`

En TD, on a créé une classe `Array<E>` qui encapsule un tableau Java et lui ajoute `Iterable`. Son amélioration, `BetterArray<E>`, redéfinit correctement `equals()` et `toString()` (que les tableaux Java ne gèrent pas bien).

> 💡 Les tableaux Java ne respectent pas le contrat de `Object` : `tab1.equals(tab2)` compare les **références**, pas les contenus. `BetterArray` corrige ça.

---

## 3. Pattern Singleton & Enum

### Le problème Singleton

Parfois, une seule instance d'une classe doit exister dans tout le programme. Par exemple : une classe de configuration, un logger, ou un comparateur sans état.

**Le pattern Singleton** garantit qu'une classe n'a qu'**une seule instance** et fournit un point d'accès global à cette instance.

### Implémentation en Java

```java
public class Singleton {
    // 1. L'unique instance, créée une fois, non modifiable
    public static final Singleton theInstance = new Singleton(arg1, arg2);

    private Class1 att1;

    // 2. Constructeur PRIVÉ → personne d'autre ne peut créer d'instance
    private Singleton(Class1 arg1, Class2 arg2) {
        att1 = arg1;
    }

    // 3. Interdire explicitement le clonage
    protected final Singleton clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }
}
```

Variante avec initialisation paresseuse (lazy initialization) :
```java
private static final Singleton theInstance;

public static Singleton getInstance() {
    if (theInstance == null) {
        theInstance = new Singleton(arg1, arg2);
    }
    return theInstance;
}
```

### Extension aux Enum

Le Singleton peut être généralisé aux **valeurs d'un type énuméré**. On veut plusieurs "singletons" (RED, BLUE, GREEN) mais exactement un seul de chaque.

**Avant Java 5** (pattern manuel) :
```java
public class Color {
    public static final Color RED   = new Color("RED");
    public static final Color BLUE  = new Color("BLUE");
    public static final Color GREEN = new Color("GREEN");

    private String name;
    private Color(String name) { this.name = name; }

    public String name() { return name; }
}
```

**Avec Java** (type `enum`) :
```java
public enum Color {
    RED, GREEN, BLUE
}
```

C'est quasi-équivalent, mais bien plus simple ! Java gère tout automatiquement.

### Enum avec attributs et méthodes

Les enums Java peuvent avoir des attributs et des méthodes :

```java
public enum ColorRGB {
    RED(255, 0, 0), GREEN(0, 128, 0), BLUE(0, 0, 255);

    private final int redValue;
    private final int greenValue;
    private final int blueValue;

    // Constructeur privé (toujours)
    private ColorRGB(int red, int green, int blue) {
        redValue = red; greenValue = green; blueValue = blue;
    }

    public int getRed()   { return redValue; }
    public int getGreen() { return greenValue; }
    public int getBlue()  { return blueValue; }
}
```

> ⚠️ Un `enum` **doit être non modifiable** (immutable). Ne jamais ajouter de setters !

### Application en TD : `ObjetZork` comme enum

En TD/TP, la classe `ObjetZork` peut être redéfinie comme un `enum` car le nombre d'objets est connu d'avance et aucun nouvel objet ne sera créé en cours de partie.

---

## 4. Pattern Strategy & Lambda

### Le problème Strategy

Imaginons qu'on veuille trier une liste d'`ObjetZork`, tantôt par poids, tantôt par nom. L'algorithme de tri est le même, mais le **critère de comparaison** change.

**Mauvaise approche** : créer une sous-classe de `Gamer` pour chaque stratégie → explosion du nombre de classes, et la stratégie est figée à la création.

**Bonne approche (Strategy)** : encapsuler l'algorithme variable dans une interface, et le passer en paramètre.

### La solution : une interface de stratégie

```java
public interface Comparator<E> {
    int compare(E o1, E o2);
    // retourne < 0 si o1 < o2, 0 si égaux, > 0 si o1 > o2
}
```

On crée autant d'implémentations que de stratégies :
```java
public class CompareWeight implements Comparator<ObjetZork> {
    public int compare(ObjetZork o1, ObjetZork o2) {
        return o1.getPoids() - o2.getPoids();
    }
}

public class CompareName implements Comparator<ObjetZork> {
    public int compare(ObjetZork o1, ObjetZork o2) {
        return o1.getNom().compareTo(o2.getNom());
    }
}
```

Et la classe `Gamer` délègue le choix de stratégie :
```java
public class Gamer {
    private MovingStrategy myStrategy;  // l'attribut qui contient la stratégie

    public Gamer(MovingStrategy strategy) {
        this.myStrategy = strategy;
    }

    public Location getRecommandation() {
        return myStrategy.getLocation();  // délégation
    }

    // La stratégie peut changer pendant le jeu !
    public void eat() {
        if (!hasFood()) {
            myStrategy = new FoodStrategy(zorkMap, this);
        }
    }
}
```

### Les Functional Interfaces

En Java, une **functional interface** est une interface avec **une seule méthode abstraite**. C'est ce qui permet d'utiliser les lambda expressions.

Quelques functional interfaces importantes du package `java.util.function` :

| Interface | Méthode | Description |
|---|---|---|
| `Predicate<T>` | `boolean test(T t)` | Teste une condition sur un objet |
| `Function<T, R>` | `R apply(T t)` | Transforme un T en R |
| `UnaryOperator<T>` | `T apply(T t)` | Transforme un T en T |
| `Supplier<T>` | `T get()` | Fournit un T (sans paramètre) |
| `Comparator<E>` | `int compare(E o1, E o2)` | Compare deux éléments |

### Les Lambdas expressions

Créer une classe entière pour une seule méthode, c'est verbeux. Java 8 a introduit les **lambda expressions** pour écrire des functional interfaces en une ligne.

**Avant les lambdas** :
```java
Comparator<ObjetZork> cmp = new Comparator<ObjetZork>() {
    @Override
    public int compare(ObjetZork o1, ObjetZork o2) {
        return o1.getPoids() - o2.getPoids();
    }
};
```

**Avec une lambda** :
```java
Comparator<ObjetZork> cmp = (o1, o2) -> o1.getPoids() - o2.getPoids();
```

La syntaxe est : `(paramètres) -> expression`

> ⚠️ Les lambdas ne s'utilisent **qu'avec les functional interfaces** (une seule méthode abstraite). Et on ne les utilise que pour du code simple, tenant en une expression.

### L'interface `Predicate<E>` en TD

En TD, on a construit une classe `FilterArrayIterator` qui filtre les éléments d'un tableau grâce à un `Predicate` :

```java
// Deux implémentations de Predicate
public class TestNotNull<E> implements Predicate<E> {
    public boolean test(E t) { return t != null; }
}

public class TestTransportable implements Predicate<ObjetZork> {
    public boolean test(ObjetZork oz) { return oz.estTransportable(); }
}
```

Avec une lambda, plus besoin de ces classes :
```java
Iterator<ObjetZork> iter = new FilterArrayIterator<>(tabOz,
    oz -> oz != null && oz.estTransportable() && oz.getPoids() < 15);
```

---

## 5. Pattern Decorator

### Le problème

Imaginons une pizzeria. On veut représenter toutes les combinaisons possibles d'ingrédients. Avec l'héritage seul, il faudrait une classe par combinaison : `PizzaOlivesJambon`, `PizzaJambonOignons`, etc. → **explosion combinatoire** !

**Le pattern Decorator** permet d'ajouter dynamiquement des fonctionnalités à un objet **en l'enveloppant** dans un autre objet (le décorateur) qui implémente la même interface.

### La solution : enveloppement

```java
public interface Pizza {
    String getDesc();
    int getPrice();
}

// La pizza de base
public class SimplePizza implements Pizza {
    public String getDesc()  { return "Pizza de base"; }
    public int getPrice()    { return 10; }
}

// Un décorateur : enveloppe une Pizza et ajoute des olives
public class PizzaAvecOlives implements Pizza {
    private Pizza pizza;  // la pizza décorée

    public PizzaAvecOlives(Pizza p) { pizza = p; }

    public String getDesc()  { return pizza.getDesc() + " avec olives"; }
    public int getPrice()    { return pizza.getPrice() + 2; }
}
```

**Utilisation** (on peut empiler les décorateurs) :
```java
Pizza p = new SimplePizza();
p = new PizzaAvecOlives(p);
p = new PizzaAvecJambon(p);
p = new PizzaAvecOignons(p);
System.out.println(p.getDesc()); // "Pizza de base avec olives avec jambon avec oignons"
System.out.println(p.getPrice()); // 18
```

### Application aux itérateurs

On peut appliquer exactement le même principe aux itérateurs pour créer des **itérateurs décorateurs** qui transforment un itérateur existant, quel qu'il soit.

#### `FilterIterator<E>` : filtrer les éléments

```java
public class FilterIterator<E> implements Iterator<E> {
    private Iterator<? extends E> supportIter;
    private Predicate<? super E> predicate;
    private boolean nextFound;
    private E nextElt;

    public FilterIterator(Iterator<? extends E> iter, Predicate<? super E> p) {
        supportIter = iter;
        predicate = p;
        findNext(); // on cherche le premier élément valide
    }

    private void findNext() {
        nextFound = false;
        while (supportIter.hasNext()) {
            E elt = supportIter.next();
            if (predicate.test(elt)) {
                nextElt = elt;
                nextFound = true;
                return;
            }
        }
    }

    public boolean hasNext() { return nextFound; }

    public E next() {
        E result = nextElt;
        findNext(); // cherche le suivant
        return result;
    }
}
```

Avantage majeur : `FilterIterator` fonctionne avec **n'importe quel itérateur** (tableau, liste, set…), contrairement à un `FilterArrayIterator` spécifique aux tableaux.

#### `MappingIterator<T, R>` : transformer les éléments

```java
public class MappingIterator<T, R> implements Iterator<R> {
    private Iterator<? extends T> iter;
    private Function<? super T, ? extends R> func;

    public MappingIterator(Iterator<? extends T> it, Function<? super T, ? extends R> f) {
        iter = it;
        func = f;
    }

    public boolean hasNext() { return iter.hasNext(); }
    public R next()          { return func.apply(iter.next()); }
}
```

#### Combiner plusieurs décorateurs

On peut chaîner : d'abord filtrer, puis transformer.

```java
ObjetZork[] tabOz = {oz1, oz2, oz3, oz4, oz5, oz6};

// 1. Itérateur de base
Iterator<ObjetZork> it = new ArrayIterator<>(tabOz);
// 2. Filtrer : garder seulement ceux dont le nom commence par "Pi"
it = new FilterIterator<>(it, oz -> oz.getNom().startsWith("Pi"));
// 3. Transformer : extraire le nom
Iterator<String> names = new MappingIterator<>(it, oz -> oz.getNom());

while (names.hasNext()) {
    System.out.print(":" + names.next());
}
// Affichage : :Pizza:Pistolet
```

> 💡 On peut même appliquer un `FilterIterator` sur un `FilterIterator` !

---

## 6. Les Streams Java

### Qu'est-ce qu'un Stream ?

L'interface `Stream<E>` de Java (depuis Java 8) reprend les idées des `FilterIterator` et `MappingIterator`, mais en proposant une **API bien plus riche** et plus lisible.

Un Stream est un "flux" d'éléments sur lequel on peut enchaîner des opérations. On distingue :

- **Opérations intermédiaires** : produisent un nouveau Stream, **ne déclenchent aucun calcul** (paresseuses)
- **Opérations terminales** : déclenchent le calcul et produisent un résultat final (autre qu'un Stream)

> ⚠️ Après une opération terminale, le Stream est **consommé** et ne peut plus être réutilisé.

### Créer un Stream

```java
// Depuis un tableau ou des valeurs
Stream<Direction> s = Stream.of(Direction.values());

// Depuis une collection (List, Set...)
List<String> list = ...;
Stream<String> s = list.stream();
```

### Opérations intermédiaires

```java
// filter : garder seulement les éléments satisfaisant le prédicat
Stream<Piece> voisines = Stream.of(Direction.values())
    .map(d -> p.pieceSuivante(d))    // transformer : Direction → Piece
    .filter(v -> v != null);          // filtrer : enlever les null
```

| Méthode | Description |
|---|---|
| `filter(Predicate)` | Garde seulement les éléments vérifiant le prédicat |
| `map(Function)` | Transforme chaque élément (change le type si besoin) |
| `flatMap(Function)` | Aplatit des streams de streams en un seul stream |

#### `flatMap` : aplatir des collections imbriquées

Problème : si on veut tous les `ObjetZork` de toutes les pièces voisines, `map` donne un `Stream<Stream<ObjetZork>>`. `flatMap` "aplatit" ça :

```java
// MAUVAIS : Stream<Stream<ObjetZork>>
Stream<Stream<ObjetZork>> ss = voisines.map(piece -> piece.stream());

// BON : Stream<ObjetZork> (tous les objets à plat)
Stream<ObjetZork> tousObjets = voisines
    .flatMap(piece -> piece.stream());
```

### Opérations terminales

| Méthode | Description |
|---|---|
| `iterator()` | Renvoie un `Iterator` |
| `toList()` | Renvoie une `List` avec tous les éléments |
| `toArray()` | Renvoie un tableau |
| `count()` | Compte le nombre d'éléments (renvoie un `long`) |
| `max(Comparator)` | Renvoie le maximum (dans un `Optional`) |
| `anyMatch(Predicate)` | `true` si au moins un élément satisfait le prédicat |
| `allMatch(Predicate)` | `true` si tous les éléments satisfont le prédicat |
| `collect(Collector)` | Collecte dans n'importe quelle structure (très flexible) |

### La classe `Optional<T>`

`max()` (et d'autres méthodes) renvoient un `Optional<T>` pour gérer le cas où le Stream est vide (plutôt que de renvoyer `null`).

```java
Optional<Piece> bestRoom = voisines.max(Comparator.comparingInt(v -> countPred(v, pred)));

if (bestRoom.isPresent()) {
    Piece p = bestRoom.get();
}
// Ou plus simplement :
Piece p = bestRoom.orElse(null);
```

### Exemple complet : `StrategieMaxTresors`

Trouver la pièce voisine contenant le plus de trésors satisfaisant un critère :

**Version avec boucles classiques :**
```java
public Salle choisirSalle(Salle p, Predicate<? super Tresor> pred) {
    Salle res = null;
    int max = 0;
    for (Direction d : Direction.values()) {
        Salle voisine = p.salleSuivante(d);
        if (voisine != null) {
            int count = 0;
            for (Tresor t : voisine) {
                if (pred.test(t)) count++;
            }
            if (count > max) { max = count; res = voisine; }
        }
    }
    return res;
}
```

**Version avec Streams :**
```java
public Salle choisirSalle(Salle p, Predicate<? super Tresor> pred) {
    return Stream.of(Direction.values())
        .map(d -> p.salleSuivante(d))
        .filter(v -> v != null)
        .max(Comparator.comparingInt(v -> countPred(v, pred)))
        .orElse(null);
}
```

---

## 7. Architecture MVC & Pattern Command

### Le modèle MVC (Model-View-Controller)

MVC est un **principe architectural** qui consiste à séparer le code en trois catégories **indépendantes** :

#### Model (Modèle)
Gère les **données** de l'application. Aucun affichage, aucune interaction utilisateur. Les classes du Model ne connaissent ni la View ni le Controller.

Exemples dans Zork : `Room`, `Gamer`, `ObjetZork`, `ZorkMap`.

#### View (Vue)
Gère toutes les **interactions directes avec l'utilisateur** : affichage et saisie. Les classes de la View ne connaissent ni le Model ni le Controller.

Exemples : `ListView<E>` (affichage d'une liste numérotée), `MenuView`, `GUIView`.

#### Controller (Contrôleur)
Exécute les **commandes de l'utilisateur**. Fait le lien entre View et Model. Ne fait pas d'affichage directement : il demande à la View d'afficher, et au Model d'exécuter.

C'est ici qu'on applique le **design pattern Command**.

### Le Pattern Command

Chaque action possible (se déplacer, prendre un objet, etc.) est encapsulée dans une classe qui implémente l'interface `Command` :

```java
public interface Command {
    void execute();
}
```

#### Exemples de classes Command

**`RoomInventory`** — affiche les objets de la pièce courante :
```java
public class RoomInventory implements Command {
    private Room room;
    private View view;

    public void execute() {
        ListView<ObjetZork> menu = ListView.buildMenu(room); // iterable sur les objets
        menu.show();
        view.showMenu(); // réaffiche le menu principal
    }
}
```

**`TakeObject`** — le joueur prend un objet :
```java
public class TakeObject implements Command {
    private Room room;
    private Gamer gamer;
    private View view;

    public void execute() {
        ListView<ObjetZork> menu = ListView.buildMenu(room);
        menu.show();
        ObjetZork chosen = menu.readChoice(); // l'utilisateur choisit
        gamer.take(chosen);
        room.remove(chosen);
    }
}
```

**`GoCommand`** — le joueur se déplace :
```java
public class GoCommand implements Command {
    public void execute() {
        EnumMap<Direction, Room> voisines = map.nextValidLocation(currentLocation);
        ListView<Direction> menu = ListView.buildMenu(voisines.keySet());
        menu.show();
        Direction d = menu.readChoice();
        map.setLocation(gamer, voisines.get(d));
    }
}
```

### Pourquoi ce découpage ?

- On peut changer l'interface (console → graphique) **sans toucher au Model**.
- On peut ajouter des commandes (undo/redo) sans tout refaire.
- On peut tester le Model indépendamment de l'affichage.

---

## 8. Pattern Builder

### Le problème

Quand une classe a beaucoup de paramètres, son constructeur devient illisible :

```java
// Qu'est-ce que 4, 1, 2, 1, 4 signifient ? Facile de se tromper !
UniteEnseignement poo2 = new UniteEnseignement("POO2", "Design Patterns", 4, 1, 2, 1, 4);
```

### La solution : une classe Builder

Le **pattern Builder** sépare la **configuration** de la **construction** :

1. On crée une classe `Builder` dont le rôle unique est de préparer les paramètres.
2. Chaque paramètre optionnel a une méthode dédiée dans le Builder.
3. La méthode `build()` crée l'objet final.
4. Ces méthodes retournent `this` (le Builder) pour permettre le **chaînage**.

```java
public class UEBuilder {
    String name;         // obligatoire
    String description;  // obligatoire
    int ects = 4;        // optionnel, avec valeur par défaut
    int coefP1 = 1;
    int coefP2 = 2;
    int coefTP = 1;
    int numSemestre = 1;

    // Constructeur avec les paramètres obligatoires
    public UEBuilder(String name, String description) {
        if (name == null || description == null) throw new NullPointerException();
        this.name = name;
        this.description = description;
    }

    // Méthodes pour les paramètres optionnels, retournent this pour le chaînage
    public UEBuilder withEcts(int val)        { ects = val; return this; }
    public UEBuilder withCoefP1(int val)      { coefP1 = val; return this; }
    public UEBuilder withNumSemestre(int val) { numSemestre = val; return this; }

    // Construction de l'objet final
    public UniteEnseignement build() {
        return new UniteEnseignement(this);
    }
}
```

Dans `UniteEnseignement`, le constructeur est **package-private** (seul le Builder peut l'appeler) :
```java
public class UniteEnseignement {
    // tous les attributs...

    UniteEnseignement(UEBuilder builder) {  // package-private (pas de mot-clé public/private)
        name        = builder.name;
        description = builder.description;
        ects        = builder.ects;
        // etc.
    }
}
```

**Utilisation** (lisible et sans risque de confusion) :
```java
UniteEnseignement poo2 = new UEBuilder("POO2", "Design Patterns")
    .withNumSemestre(4)
    .build();
```

### Builder avec héritage : Abstract Builder

Quand plusieurs implémentations partagent des paramètres communs (ex: `MenuView` et `GUIView` implémentent toutes deux `ListView<E>`), on crée un Builder abstrait :

```java
public abstract class AbstractListViewBuilder<E> {
    protected String title  = "";
    protected String header = "";
    protected List<E> list; // obligatoire

    public AbstractListViewBuilder(List<E> list) { this.list = list; }

    public AbstractListViewBuilder<E> withTitle(String t)  { title = t;  return this; }
    public AbstractListViewBuilder<E> withHeader(String h) { header = h; return this; }

    public abstract ListView<E> build(); // chaque sous-builder crée sa propre classe
}

public class MenuViewBuilder<E> extends AbstractListViewBuilder<E> {
    public ListView<E> build() { return new MenuView<>(this); }
}

public class GUIViewBuilder<E> extends AbstractListViewBuilder<E> {
    private JFrame frame;
    public GUIViewBuilder<E> withFrame(JFrame f) { frame = f; return this; }
    public ListView<E> build() { return new GUIView<>(this); }
}
```

---

## 9. Récapitulatif : les patterns en un coup d'œil

| Pattern | Catégorie | Problème résolu | Mécanisme clé |
|---|---|---|---|
| **Iterator** | Comportemental | Parcourir une collection sans connaître son implémentation | Interface `Iterator<E>` + classe séparée |
| **Singleton** | Création | Garantir une seule instance | Constructeur `private`, attribut `static final` |
| **Enum** | Création | Ensemble fini d'instances uniques | Mot-clé `enum` en Java |
| **Strategy** | Comportemental | Changer d'algorithme à l'exécution | Interface de stratégie + attribut + injection |
| **Decorator** | Structurel | Ajouter dynamiquement des fonctionnalités | Même interface, enveloppement + délégation |
| **Command** | Comportemental | Encapsuler des actions, séparer demandeur et exécutant | Interface `Command` avec méthode `execute()` |
| **Builder** | Création | Construire des objets complexes lisiblement | Classe Builder, chaînage de méthodes, `build()` |

### Les trois grands principes (à retenir !)

1. **Séparer ce qui change** de ce qui reste stable.
2. **Programmer vers des interfaces**, pas vers des implémentations concrètes.
3. **Préférer la composition à l'héritage** (assembler des objets plutôt qu'en hériter).

---

## 10. Le projet Zork : contexte d'application

Tout au long du cours, les exemples s'appuient sur **Zork**, un jeu d'aventure textuel. Voici les classes principales :

### `ObjetZork`
Un objet du jeu avec un nom, un poids, et un booléen indiquant s'il est transportable.

```java
public class ObjetZork {
    private String nom;
    private int poids;
    private boolean estTransportable;

    public ObjetZork(String nom, int poids, boolean estTransportable) { ... }
    public String getNom()           { return nom; }
    public int getPoids()            { return poids; }
    public boolean estTransportable(){ return estTransportable; }
    // equals, hashCode, toString redéfinis
}
```

### Classes de la Map
- `Room` / `Piece` / `Salle` : une pièce qui contient des objets, avec des voisines dans chaque `Direction`.
- `Direction` : un `enum` (NORD, SUD, EST, OUEST).
- `ZorkMap` : la carte du jeu, gère les déplacements.
- `Gamer` / `Joueur` : le joueur, avec ses objets et sa position.

### Ce que chaque pattern apporte à Zork

| Pattern | Application dans Zork |
|---|---|
| **Iterator** | Parcourir les objets d'une `Piece` avec un `foreach` |
| **Singleton** | `ObjetZork` comme enum (nombre d'objets fixe) |
| **Strategy** | Stratégie de déplacement d'un monstre ou joueur (chercherNourriture, chercherTrésor…) |
| **Decorator** | `FilterIterator` pour filtrer les objets transportables d'une pièce |
| **Stream** | `StrategieMaxTresors` : trouver la pièce avec le plus de trésors |
| **MVC + Command** | Séparer l'affichage (console/GUI) des actions (Take, Drop, Go) |
| **Builder** | Créer un `ZorkMap` ou une `ListView` avec de nombreux paramètres |

---

## Annexe : Formulaire de notation

```
Note finale CC = max( (Devoir + PA1 + 2×PA2) / 4 ,  PA2 )
```

- **Devoir** : TP noté (pratique Java)
- **PA1** : partiel de mi-semestre
- **PA2** : partiel de fin de semestre (compte double)

---

*Document généré à partir des supports de cours POO2 de Marc Champesme, Université Paris XIII — Institut Galilée.*
