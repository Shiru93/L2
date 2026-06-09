# Partiel Blanc n°2 — Programmation Orientée Objet
**Licence Informatique — Institut Galilée**  
*Durée : 3 heures.*  
*Documents autorisés : documentation des classes conteneur (livret distribué) et de l'interface JAVA Iterator*

---

## Ce qui est évalué

- Utiliser correctement le langage Java pour implémenter une classe
- Effectuer des choix corrects pour la visibilité des champs et des méthodes
- Respecter le contrat hérité des super-classes lors de la définition d'une nouvelle classe
- Donner l'implémentation d'une classe en conformité avec son interface et son contrat
- Utiliser correctement les exceptions pour détecter et gérer les violations de pré-conditions
- Utiliser correctement l'héritage et la généricité pour la définition de classes

---

# SUJET

---

## 1 — Définition de la classe `PairIterator`

**Exercice 1** La classe générique `PairIterator<E>` est une classe générique implémentant l'interface `Iterator` et représentant un itérateur sur **exactement deux éléments**. Cette classe peut par exemple être utilisée lorsque l'on a besoin d'un itérateur sur une collection contenant exactement deux éléments.

Un exemple typique d'utilisation d'un itérateur est présenté ci-après :

```java
ArrayList<String> als = new ArrayList<String>();
// ajout d'éléments à la liste als...
Iterator<String> iterAls = als.iterator();
// Suppression dans la liste als de toutes les chaînes "abc" présentes:
while (iterAls.hasNext()) {
    if (iterAls.next().equals("abc")) {
        iterAls.remove();
    }
}
```

Donnez le code source complet de la classe `PairIterator` décrite ci-dessus.  
Les commentaires et assertions ne sont pas demandés.

**IMPORTANT :** Cette classe pourra être utilisée pour implémenter la classe `FilteredContainer` du deuxième exercice.

---

## 2 — Définition de la classe `FilteredContainer`

**Exercice 2** Donnez une implémentation complète de la classe `FilteredContainer` conforme à son interface donnée en annexe.

**IMPORTANT :** Pour cette classe les commentaires et assertions ne sont pas demandés.

---

## 3 — Définition de la classe `Bibliotheque`

**Exercice 3** Dans le contexte du jeu Zork, on souhaite définir une classe `Bibliotheque` pouvant contenir des `ObjetZork`. Une `Bibliotheque` peut être ouverte ou fermée à l'aide d'une instance d'une nouvelle classe `Cadenas`. Elle a donc toutes les caractéristiques d'un `FilteredContainer`. Une `Bibliotheque` possède cependant deux caractéristiques supplémentaires par rapport à un `FilteredContainer` :
- une instance de la classe `String` qui permet de lui associer un titre
- un entier représentant le poids à vide de cette `Bibliotheque`

Compte tenu de ces caractéristiques supplémentaires, trois méthodes supplémentaires devront être définies :
- une méthode `String getTitre()` renvoyant le titre de la bibliothèque
- une méthode `int getEmptyWeight()` renvoyant le poids à vide de la bibliothèque
- une méthode `int getWeight()` renvoyant le poids total de la bibliothèque (i.e. le poids à vide + la somme des poids de tous les objets qu'elle contient)

La classe `Bibliotheque` devra disposer de deux constructeurs : un constructeur initialisant une `Bibliotheque` vide et un constructeur initialisant une `Bibliotheque` contenant les mêmes éléments qu'une collection donnée en paramètre.

Donnez une implémentation complète de la classe `Bibliotheque` définie par héritage de la classe `FilteredContainer`.

**IMPORTANT :** Les commentaires et assertions devront être donnés uniquement pour les deux constructeurs. La définition des classes `Cadenas` et `ObjetZork` n'est pas demandée. On supposera que la classe `ObjetZork` possède une méthode `int getWeight()` qui renvoie le poids de l'`ObjetZork`.

---

---

# ANNEXE — Interface de la classe `FilteredContainer`

---

## Présentation générale

```
public class FilteredContainer<K, E>
extends Object
implements Iterable<E>
```

Représentation d'une collection d'objets non ordonnée et de taille illimitée pouvant être ouverte ou fermée, dans laquelle **les doublons ne sont pas autorisés**. Chaque `FilteredContainer` possède sa propre clé fournie lors de sa création. Cette clé doit être fournie pour pouvoir l'ouvrir ou le fermer. Lorsque le `FilteredContainer` est fermé, il se comporte comme un `FilteredContainer` vide dont le contenu ne peut pas être modifié. Lorsque le `FilteredContainer` est fermé les opérations `add` et `remove` déclenchent une exception `IllegalStateException`.

**Type Parameters :**
- `K` - le type de la clé
- `E` - le type des éléments du `FilteredContainer`

**Invariant :**

```
!hasKey(null);
!contains(null);
!isOpen() ==> (size() == 0);
(\forall E x; contains(x); (\forall E y; contains(y); x.equals(y) ==> x == y));
```
*(ce dernier invariant signifie : pas de doublons)*

---

## Constructor Summary

| Constructeur | Description |
|---|---|
| `FilteredContainer(K cle)` | Initialise un nouveau `FilteredContainer` vide ayant pour clé la valeur spécifiée. |
| `FilteredContainer(K cle, Collection<? extends E> desObjets)` | Initialise un nouveau `FilteredContainer` ayant pour clé la valeur spécifiée et contenant les objets de la collection spécifiée. |

---

## Method Summary

| Type | Méthode | Description |
|---|---|---|
| `void` | `add(E elt)` | Ajoute l'objet spécifié s'il n'est pas déjà présent et si le conteneur est ouvert. |
| `boolean` | `close(K cle)` | Tente de fermer ce `FilteredContainer` avec la clé spécifiée. |
| `boolean` | `contains(Object obj)` | Renvoie true si ce `FilteredContainer` contient l'objet spécifié. |
| `int` | `frequencyOf(Object obj)` | Renvoie le nombre d'exemplaires de l'objet spécifié (0 ou 1 car pas de doublons). |
| `boolean` | `hasKey(K cle)` | Teste si l'objet spécifié est la clé de ce `FilteredContainer`. |
| `boolean` | `isOpen()` | Renvoie l'état actuel de ce `FilteredContainer` : ouvert ou fermé. |
| `Iterator<E>` | `iterator()` | Renvoie un itérateur sur les objets présents dans ce `FilteredContainer`. |
| `boolean` | `open(K cle)` | Tente d'ouvrir ce `FilteredContainer` avec la clé spécifiée. |
| `boolean` | `remove(Object obj)` | Retire l'objet spécifié si le conteneur est ouvert et que l'objet est présent. |
| `int` | `size()` | Renvoie le nombre d'objets présents dans ce `FilteredContainer`. |

---

## Constructor Details

### `FilteredContainer(K cle)`

```
public FilteredContainer(K cle)
```

Initialise un nouveau `FilteredContainer` vide ayant pour clé la valeur spécifiée.

**Requires :**
```
cle != null;
```

**Ensures :**
```
isOpen();
hasKey(cle);
size() == 0;
```

**Throws :**  
`NullPointerException` - si la clé est null

---

### `FilteredContainer(K cle, Collection<? extends E> desObjets)`

```
public FilteredContainer(K cle, Collection<? extends E> desObjets)
```

Initialise un nouveau `FilteredContainer` ayant pour clé la valeur spécifiée et contenant les objets de la collection spécifiée. Si la collection contient des doublons, un seul exemplaire est conservé.

**Requires :**
```
cle != null;
desObjets != null;
!desObjets.contains(null);
```

**Ensures :**
```
isOpen();
hasKey(cle);
(\forall E elt; desObjets.contains(elt); this.contains(elt));
```

**Throws :**  
`NullPointerException` - si la clé ou la collection spécifiée est null ou que la collection contient null

---

## Method Details

### `hasKey`

```
public boolean hasKey(K cle)
```

Teste si l'objet spécifié est equals à la clé de ce `FilteredContainer`.

**Ensures :**
```
(cle == null) ==> !\result;
```

**Pure (no side effect)**

---

### `open`

```
public boolean open(K cle)
```

Tente d'ouvrir ce `FilteredContainer` avec la clé spécifiée.

**Ensures :**
```
hasKey(cle) <==> \result;
hasKey(cle) ==> isOpen();
```

---

### `close`

```
public boolean close(K cle)
```

Tente de fermer ce `FilteredContainer` avec la clé spécifiée.

**Ensures :**
```
hasKey(cle) <==> \result;
hasKey(cle) ==> !isOpen();
```

---

### `isOpen`

```
public boolean isOpen()
```

Renvoie l'état actuel de ce `FilteredContainer` : ouvert ou fermé.

**Pure (no side effect)**

---

### `add`

```
public void add(E elt)
```

Ajoute l'objet spécifié aux objets présents dans ce `FilteredContainer` s'il est ouvert et si l'objet n'est pas déjà présent. Si l'objet est déjà présent, rien ne se passe.

**Requires :**
```
elt != null;
isOpen();
```

**Ensures :**
```
contains(elt);
(!\old(contains(elt))) ==> (frequencyOf(elt) == \old(frequencyOf(elt)) + 1);
(\old(contains(elt))) ==> (size() == \old(size()));
```

**Throws :**  
`NullPointerException` - si l'objet spécifié est null  
`IllegalStateException` - si ce `FilteredContainer` est fermé

---

### `remove`

```
public boolean remove(Object obj)
```

Retire l'objet spécifié si le conteneur est ouvert et que l'objet est présent.

**Requires :**
```
isOpen();
```

**Ensures :**
```
\old(contains(obj)) <==> \result;
\old(contains(obj)) ==> !contains(obj);
```

**Throws :**  
`IllegalStateException` - si ce `FilteredContainer` est fermé

---

### `contains`

```
public boolean contains(Object obj)
```

Renvoie true si ce `FilteredContainer` contient au moins un exemplaire de l'objet spécifié. Renvoie false si l'argument est null ou que ce `FilteredContainer` est fermé.

**Ensures :**
```
\result <==> (frequencyOf(obj) > 0);
!isOpen() ==> !\result;
```

**Pure (no side effect)**

---

### `size`

```
public int size()
```

Renvoie le nombre d'objets présents dans ce `FilteredContainer`.

**Ensures :**
```
\result >= 0;
!isOpen() ==> (\result == 0);
```

**Pure (no side effect)**

---

### `frequencyOf`

```
public int frequencyOf(Object obj)
```

Renvoie le nombre d'exemplaires de l'objet spécifié (0 ou 1 car pas de doublons). Renvoie 0 si ce `FilteredContainer` est fermé.

**Ensures :**
```
\result >= 0;
\result <= 1;
!isOpen() ==> (\result == 0);
```

**Pure (no side effect)**

---

### `iterator`

```
public Iterator<E> iterator()
```

Renvoie un itérateur sur les objets présents dans ce `FilteredContainer`. Si ce `FilteredContainer` est fermé, l'itérateur renvoyé se comporte comme un itérateur sur un `FilteredContainer` ne contenant aucun élément. Si ce `FilteredContainer` contient exactement deux éléments, l'itérateur renvoyé est un `PairIterator`.

**Ensures :**
```
\result != null;
```

**Pure (no side effect)**

---

---

# CORRECTION

---

## Exercice 1 — `PairIterator<E>`

Un itérateur sur **exactement deux éléments**. On a besoin de savoir lequel des deux on doit retourner → on utilise un compteur `index`.

```java
import java.util.Iterator;
import java.util.NoSuchElementException;

public class PairIterator<E> implements Iterator<E> {

    private final E premier;
    private final E second;
    private int index; // 0 = rien lu, 1 = premier lu, 2 = tout lu

    public PairIterator(E premier, E second) {
        this.premier = premier;
        this.second = second;
        this.index = 0;
    }

    @Override
    public boolean hasNext() {
        return index < 2;
    }

    @Override
    public E next() {
        if (index == 0) {
            index = 1;
            return premier;
        }
        if (index == 1) {
            index = 2;
            return second;
        }
        throw new NoSuchElementException();
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
```

**Comparaison des 3 itérateurs vus :**

| | `EmptyIterator` | `SingletonIterator` | `PairIterator` |
|---|---|---|---|
| Nb éléments | 0 | 1 | 2 |
| `hasNext()` | toujours `false` | `!dejaLu` | `index < 2` |
| Mémoire | aucune | `boolean dejaLu` | `int index` |

---

## Exercice 2 — `FilteredContainer<K, E>`

La différence clé avec `CloseableContainer` : **pas de doublons** (comme un `Set`).  
On utilise donc un `HashSet` en interne au lieu d'un `ArrayList`.

```java
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Objects;
import java.util.Set;

public class FilteredContainer<K, E> implements Iterable<E> {

    private final K key;
    private boolean ouvert;
    private final Set<E> elements;

    public FilteredContainer(K cle) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        this.key = cle;
        this.ouvert = true;
        this.elements = new HashSet<>();
    }

    public FilteredContainer(K cle, Collection<? extends E> desObjets) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        Objects.requireNonNull(desObjets, "La collection ne peut pas être null");
        if (desObjets.contains(null)) {
            throw new NullPointerException("La collection ne peut pas contenir null");
        }
        this.key = cle;
        this.ouvert = true;
        this.elements = new HashSet<>(desObjets); // HashSet élimine les doublons
    }

    public boolean hasKey(K cle) {
        if (cle == null) return false;
        return this.key.equals(cle);
    }

    public boolean isOpen() {
        return ouvert;
    }

    public boolean open(K cle) {
        if (hasKey(cle)) {
            ouvert = true;
            return true;
        }
        return false;
    }

    public boolean close(K cle) {
        if (hasKey(cle)) {
            ouvert = false;
            return true;
        }
        return false;
    }

    public void add(E elt) {
        Objects.requireNonNull(elt, "L'élément ne peut pas être null");
        if (!ouvert) {
            throw new IllegalStateException("Le FilteredContainer est fermé");
        }
        elements.add(elt); // HashSet ignore si déjà présent → pas de doublon
    }

    public boolean remove(Object obj) {
        if (!ouvert) {
            throw new IllegalStateException("Le FilteredContainer est fermé");
        }
        return elements.remove(obj);
    }

    public boolean contains(Object obj) {
        if (!ouvert || obj == null) return false;
        return elements.contains(obj);
    }

    public int size() {
        if (!ouvert) return 0;
        return elements.size();
    }

    public int frequencyOf(Object obj) {
        if (!ouvert) return 0;
        return elements.contains(obj) ? 1 : 0; // 0 ou 1, jamais plus
    }

    @Override
    public Iterator<E> iterator() {
        if (!ouvert) return new EmptyIterator<>();
        if (size() == 2) {
            // on récupère les deux éléments pour PairIterator
            Iterator<E> it = elements.iterator();
            E premier = it.next();
            E second = it.next();
            return new PairIterator<>(premier, second); // ← réutilisation Ex.1
        }
        return elements.iterator();
    }

    protected Iterator<E> iteratorInterne() {
        return elements.iterator();
    }
}
```

**Pourquoi `HashSet` et pas `ArrayList` ?**

| | `ArrayList` | `HashSet` |
|---|---|---|
| Doublons | autorisés | **interdits automatiquement** |
| Utilisé dans | `CloseableContainer` | `FilteredContainer` |

Le `HashSet` gère les doublons tout seul : si on `add()` un élément déjà présent, il ne se passe rien.

---

## Exercice 3 — `Bibliotheque`

Même structure que `Coffre` dans le vrai partiel, mais hérite de `FilteredContainer`.

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Bibliotheque extends FilteredContainer<Cadenas, ObjetZork> {

    private final String titre;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Bibliotheque vide.
     *
     * @requires cadenas != null
     * @requires titre != null
     * @requires emptyWeight >= 0
     * @ensures getTitre().equals(titre)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cadenas ou titre est null
     */
    public Bibliotheque(Cadenas cadenas, String titre, int emptyWeight) {
        super(cadenas);
        Objects.requireNonNull(titre, "Le titre ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.titre = titre;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Bibliotheque initialisée avec une collection d'ObjetZork.
     *
     * @requires cadenas != null
     * @requires titre != null
     * @requires emptyWeight >= 0
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getTitre().equals(titre)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cadenas, titre ou elements est null,
     *         ou si elements contient null
     */
    public Bibliotheque(Cadenas cadenas, String titre, int emptyWeight,
                        Collection<? extends ObjetZork> elements) {
        super(cadenas, elements);
        Objects.requireNonNull(titre, "Le titre ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.titre = titre;
        this.emptyWeight = emptyWeight;
    }

    public String getTitre() {
        return titre;
    }

    public int getEmptyWeight() {
        return emptyWeight;
    }

    /**
     * Renvoie le poids total = poids à vide + somme des poids des objets.
     * Fonctionne même si la bibliothèque est fermée (via iteratorInterne).
     */
    public int getWeight() {
        int total = emptyWeight;
        Iterator<ObjetZork> it = iteratorInterne();
        while (it.hasNext()) {
            total += it.next().getWeight();
        }
        return total;
    }
}
```

---

## Résumé de la hiérarchie

```
FilteredContainer<K, E>   (pas de doublons, HashSet)
        ↑ extends
   Bibliotheque            (titre, poids à vide, getWeight())
```

**Différence principale avec le vrai partiel :**

| | Vrai partiel | Partiel blanc n°2 |
|---|---|---|
| Itérateur 0 élément | `EmptyIterator` | `EmptyIterator` |
| Itérateur spécial | — | `PairIterator` (2 éléments) |
| Stockage interne | `ArrayList` (doublons ok) | `HashSet` (pas de doublons) |
| Classe fille | `Coffre` | `Bibliotheque` |
| Clé | `Cle` | `Cadenas` |
