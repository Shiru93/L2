# Corrigé détaillé — Partiel POO2, Mai 2026

## Exercice 1 — Design patterns *Iterator* et *Decorator*

### Idée générale du pattern Decorator ici

Le but est de créer une classe `UnmodifiableCollection<T>` qui **enveloppe** (wrap) une `Collection<T>` existante : elle implémente la même interface (`Collection<T>`), et pour chaque méthode :

- si la méthode est une **lecture** (`size`, `isEmpty`, `contains`, `containsAll`, `toArray`, `iterator`...) → elle **délègue** à la collection sous-jacente ;
- si la méthode est une **modification** (`add`, `remove`, `addAll`, `removeAll`, `retainAll`, `clear`) → elle lance `UnsupportedOperationException` **sans rien faire d'autre**.

C'est exactement la structure d'un Decorator : on garde une référence vers l'objet décoré (`Collection<T> c`), on implémente la même interface que lui, et on redéfinit le comportement de certaines méthodes en s'appuyant sur l'objet décoré pour les autres.

Point important donné dans l'énoncé (souvent oublié) : *la collection renvoyée ne transmet pas `equals`/`hashCode`*. Concrètement, cela veut dire qu'**on ne redéfinit pas** `equals` et `hashCode` dans `UnmodifiableCollection` — on laisse l'implémentation par défaut héritée de `Object` (égalité par référence). Si on les avait délégués à `c`, on violerait ce qui est demandé.

### Question 1 — `UnmodifiableCollection<T>`

```java
public class UnmodifiableCollection<T> implements Collection<T> {

    private Collection<T> c;

    public UnmodifiableCollection(Collection<T> c) {
        this.c = c;
    }

    // ----- Méthodes de lecture : on délègue -----

    public int size() {
        return c.size();
    }

    public boolean isEmpty() {
        return c.isEmpty();
    }

    public boolean contains(Object o) {
        return c.contains(o);
    }

    public boolean containsAll(Collection<?> c2) {
        return c.containsAll(c2);
    }

    public Object[] toArray() {
        return c.toArray();
    }

    public <U> U[] toArray(U[] a) {
        return c.toArray(a);
    }

    public Iterator<T> iterator() {
        return new UnmodifiableIterator<T>(c.iterator());
    }

    // ----- Méthodes de modification : on refuse -----

    public boolean add(T e) {
        throw new UnsupportedOperationException();
    }

    public boolean remove(Object o) {
        throw new UnsupportedOperationException();
    }

    public boolean addAll(Collection<? extends T> c2) {
        throw new UnsupportedOperationException();
    }

    public boolean removeAll(Collection<?> c2) {
        throw new UnsupportedOperationException();
    }

    public boolean retainAll(Collection<?> c2) {
        throw new UnsupportedOperationException();
    }

    public void clear() {
        throw new UnsupportedOperationException();
    }

    // PAS de equals/hashCode redéfinis : on garde ceux d'Object (cf. énoncé)
}
```

Remarques :

- `toArray(U[] a)` : j'ai renommé le paramètre de type en `U` pour ne pas le confondre avec le `T` de la classe — ça reste un override valide de `<T> T[] toArray(T[] a)` puisque le nom du paramètre de type n'a aucune importance pour la compatibilité, seule la signature effacée compte.
- On n'a **pas besoin** de redéfinir `forEach`, `stream`, `spliterator`, `removeIf` (méthodes par défaut de `Collection` depuis Java 8) : elles s'appuient sur `iterator()`, qui renvoie déjà un itérateur protégé contre `remove()`. Les redéfinir n'était pas demandé et ce n'est pas nécessaire pour respecter le contrat.

### Question 2 — `UnmodifiableIterator<T>`

Même logique, appliquée à `Iterator<E>` : `hasNext()` et `next()` délèguent, `remove()` est interdit.

```java
public class UnmodifiableIterator<T> implements Iterator<T> {

    private Iterator<T> it;

    public UnmodifiableIterator(Iterator<T> it) {
        this.it = it;
    }

    public boolean hasNext() {
        return it.hasNext();
    }

    public T next() {
        return it.next();
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }
}
```

C'est volontairement le décorateur le plus simple possible : il n'a qu'un seul champ, qu'une seule méthode modifiée, et délègue tout le reste. C'est ce niveau de minimalisme qui est attendu pour un Decorator correctement appliqué (ne jamais réimplémenter la logique de l'objet décoré "à la main").

---

## Exercice 2 — Design pattern *Builder*

### Point 1 — Attributs de `Gamer`

D'après l'énoncé :

```java
private String nom;                  // obligatoire, pas de défaut
private String personnalite;          // défaut : ""
private List<ObjetZork> objets;       // défaut : aucun objet
private int poidsMax;                 // défaut : 100, strictement positif
private int pointsDeVie;              // défaut : 50, strictement positif
```

(`ObjetZork` est la classe donnée dans le sujet/livret, on suppose qu'elle expose au moins une méthode `getPoids()`.)

### Point 2 — Classe `GamerBuilder`

Le piège classique ici : si `GamerBuilder` est une classe **séparée** de `Gamer`, le constructeur de `Gamer` ne peut pas accéder directement aux champs `private` du builder (sauf à ajouter des getters, ce qui n'est pas demandé). La solution standard du pattern Builder (popularisée par Effective Java) est d'en faire une **classe imbriquée statique** (`static nested class`) de `Gamer` : les classes imbriquées dans une même classe top-level partagent l'accès à leurs membres privés respectifs, donc `Gamer` peut lire directement les champs privés de `GamerBuilder` sans accesseur.

```java
public static class GamerBuilder {

    private String nom;
    private String personnalite = "";
    private List<ObjetZork> objets = new ArrayList<ObjetZork>();
    private int poidsMax = 100;
    private int pointsDeVie = 50;

    private GamerBuilder(String nom) {
        this.nom = nom;
    }

    public GamerBuilder personnalite(String personnalite) {
        this.personnalite = personnalite;
        return this;
    }

    public GamerBuilder poidsMax(int poidsMax) {
        if (poidsMax <= 0) {
            throw new IllegalArgumentException("poidsMax doit etre strictement positif");
        }
        this.poidsMax = poidsMax;
        return this;
    }

    public GamerBuilder pointsDeVie(int pointsDeVie) {
        if (pointsDeVie <= 0) {
            throw new IllegalArgumentException("pointsDeVie doit etre strictement positif");
        }
        this.pointsDeVie = pointsDeVie;
        return this;
    }

    public GamerBuilder addObjet(ObjetZork o) {
        int poidsActuel = 0;
        for (ObjetZork obj : objets) {
            poidsActuel += obj.getPoids();
        }
        if (poidsActuel + o.getPoids() > poidsMax) {
            throw new IllegalArgumentException("Poids maximal depasse");
        }
        objets.add(o);
        return this;
    }

    public Gamer build() {
        return new Gamer(this);
    }
}
```

Chaque méthode de configuration retourne `this` : c'est la signature du Builder fluide (`builder.poidsMax(150).pointsDeVie(80).addObjet(epee).build()`).

J'ai ajouté les vérifications (`poidsMax <= 0`, dépassement de poids) parce que l'énoncé général de l'épreuve liste explicitement "utiliser correctement les exceptions pour détecter et gérer les violations de pré-conditions" parmi les compétences évaluées — même si la consigne de l'exercice 2 dit que les *assertions* ne sont pas demandées pour `Gamer`, ça ne dispense pas de gérer proprement les préconditions du builder lui-même via des exceptions.

### Point 3 — Constructeur de `Gamer`

```java
private Gamer(GamerBuilder builder) {
    this.nom = builder.nom;
    this.personnalite = builder.personnalite;
    this.objets = builder.objets;
    this.poidsMax = builder.poidsMax;
    this.pointsDeVie = builder.pointsDeVie;
}
```

Le constructeur est `private` : seule la classe imbriquée `GamerBuilder` (via `build()`) doit pouvoir créer un `Gamer`, c'est tout le sens du pattern (empêcher la construction directe par `new Gamer(...)` depuis l'extérieur).

### Point 4 — Méthode static `builder`

Comme `nom` est **obligatoire**, le moyen le plus simple de forcer sa présence est de l'exiger en paramètre de la méthode statique d'entrée :

```java
public static GamerBuilder builder(String nom) {
    return new GamerBuilder(nom);
}
```

Usage typique :

```java
Gamer g = Gamer.builder("Zork-Hero")
               .personnalite("Courageux")
               .poidsMax(150)
               .addObjet(epee)
               .build();
```

### Assemblage final de `Gamer`

```java
public class Gamer {

    private String nom;
    private String personnalite;
    private List<ObjetZork> objets;
    private int poidsMax;
    private int pointsDeVie;

    private Gamer(GamerBuilder builder) {
        this.nom = builder.nom;
        this.personnalite = builder.personnalite;
        this.objets = builder.objets;
        this.poidsMax = builder.poidsMax;
        this.pointsDeVie = builder.pointsDeVie;
    }

    public static GamerBuilder builder(String nom) {
        return new GamerBuilder(nom);
    }

    public static class GamerBuilder {
        // ... (voir Point 2 ci-dessus)
    }
}
```

---

## Pièges fréquents sur ce type d'épreuve

1. **Décorateur qui réimplémente au lieu de déléguer** : sur `UnmodifiableCollection`, toute méthode de lecture doit appeler la méthode correspondante sur `c`, jamais recoder la logique soi-même.
2. **Oublier que `equals`/`hashCode` ne doivent pas être redéfinis** dans `UnmodifiableCollection` — c'est explicitement précisé dans le commentaire fourni, et c'est un point qui rapporte/enlève des points facilement.
3. **Accès aux champs privés du Builder** : sans classe imbriquée statique, le constructeur de `Gamer` ne peut pas lire les champs de `GamerBuilder` sans getters — solution standard = nested static class.
4. **Constructeur de `Gamer` public** : il doit être `private`, sinon on contourne tout l'intérêt du Builder (on pourrait construire un `Gamer` sans passer par `GamerBuilder`, donc sans validations).
5. **Valeurs par défaut mal placées** : elles doivent être initialisées dans `GamerBuilder` (`personnalite = ""`, `objets = new ArrayList<>()`, `poidsMax = 100`, `pointsDeVie = 50`), pas dans `Gamer`.
