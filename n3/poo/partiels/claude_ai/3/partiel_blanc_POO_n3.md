# Partiel Blanc n°3 — Programmation Orientée Objet
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

## 1 — Définition de la classe `ReverseIterator`

**Exercice 1** La classe générique `ReverseIterator<E>` est une classe générique implémentant l'interface `Iterator` et représentant un itérateur sur une **liste**, parcourant les éléments **du dernier au premier** (ordre inverse).

Un exemple typique d'utilisation est présenté ci-après :

```java
ArrayList<String> als = new ArrayList<>();
als.add("a");
als.add("b");
als.add("c");
Iterator<String> it = new ReverseIterator<>(als);
while (it.hasNext()) {
    System.out.println(it.next()); // affiche : c, puis b, puis a
}
```

Donnez le code source complet de la classe `ReverseIterator` décrite ci-dessus.  
Les commentaires et assertions ne sont pas demandés.

**IMPORTANT :** Cette classe pourra être utilisée pour implémenter la classe `StackContainer` du deuxième exercice.

---

## 2 — Définition de la classe `StackContainer`

**Exercice 2** Donnez une implémentation complète de la classe `StackContainer` conforme à son interface donnée en annexe.

**IMPORTANT :** Pour cette classe les commentaires et assertions ne sont pas demandés.

---

## 3 — Définition de la classe `Armoire`

**Exercice 3** Dans le contexte du jeu Zork, on souhaite définir une classe `Armoire` pouvant contenir des `ObjetZork`. Une `Armoire` peut être ouverte ou fermée à l'aide d'une instance d'une nouvelle classe `Serrure`. Elle a donc toutes les caractéristiques d'un `StackContainer`. Une `Armoire` possède cependant deux caractéristiques supplémentaires par rapport à un `StackContainer` :
- une instance de la classe `String` qui permet de lui associer une couleur
- un entier représentant le poids à vide de cette `Armoire`

Compte tenu de ces caractéristiques supplémentaires, trois méthodes supplémentaires devront être définies :
- une méthode `String getCouleur()` renvoyant la couleur de l'armoire
- une méthode `int getEmptyWeight()` renvoyant le poids à vide de l'armoire
- une méthode `int getWeight()` renvoyant le poids total de l'armoire (i.e. le poids à vide + la somme des poids de tous les objets qu'elle contient)

La classe `Armoire` devra disposer de deux constructeurs : un constructeur initialisant une `Armoire` vide et un constructeur initialisant une `Armoire` contenant les mêmes éléments qu'une collection donnée en paramètre.

Donnez une implémentation complète de la classe `Armoire` définie par héritage de la classe `StackContainer`.

**IMPORTANT :** Les commentaires et assertions devront être donnés uniquement pour les deux constructeurs. La définition des classes `Serrure` et `ObjetZork` n'est pas demandée. On supposera que la classe `ObjetZork` possède une méthode `int getWeight()` qui renvoie le poids de l'`ObjetZork`.

---

---

# ANNEXE A — Interface `Iterator` (Java Platform SE 7)

---

```
public interface Iterator<E>
```

Un itérateur sur une collection.

**Method Summary :**

| Type | Méthode | Description |
|---|---|---|
| `boolean` | `hasNext()` | Retourne `true` s'il reste des éléments à parcourir. |
| `E` | `next()` | Retourne le prochain élément. |
| `void` | `remove()` | Supprime de la collection le dernier élément retourné (opération optionnelle). |

---

### `hasNext`
```
boolean hasNext()
```
Returns `true` if the iteration has more elements. (In other words, returns `true` if `next()` would return an element rather than throwing an exception.)

**Returns :** `true` if the iteration has more elements.

---

### `next`
```
E next()
```
Returns the next element in the iteration.

**Returns :** the next element in the iteration.

**Throws :**  
`NoSuchElementException` - if the iteration has no more elements.

---

### `remove`
```
void remove()
```
Removes from the underlying collection the last element returned by this iterator (optional operation).

**Throws :**  
`UnsupportedOperationException` - if the remove operation is not supported by this iterator.  
`IllegalStateException` - if the next method has not yet been called.

---

---

# ANNEXE B — Interface de la classe `StackContainer`

---

## Présentation générale

```
public class StackContainer<K, E>
extends Object
implements Iterable<E>
```

Représentation d'une collection d'objets **ordonnée selon l'ordre d'insertion** (le dernier ajouté est le premier renvoyé par l'itérateur) et de taille illimitée, pouvant être ouverte ou fermée. Chaque `StackContainer` possède sa propre clé fournie lors de sa création. Cette clé doit être fournie pour pouvoir l'ouvrir ou le fermer. Lorsque le `StackContainer` est fermé, il se comporte comme un `StackContainer` vide dont le contenu ne peut pas être modifié. Lorsque le `StackContainer` est fermé les opérations `add` et `remove` déclenchent une exception `IllegalStateException`.

**Type Parameters :**
- `K` - le type de la clé
- `E` - le type des éléments du `StackContainer`

**Invariant :**
```
!hasKey(null);
!contains(null);
!isOpen() ==> (size() == 0);
```

---

## Constructor Summary

| Constructeur | Description |
|---|---|
| `StackContainer(K cle)` | Initialise un nouveau `StackContainer` vide ayant pour clé la valeur spécifiée. |
| `StackContainer(K cle, Collection<? extends E> desObjets)` | Initialise un nouveau `StackContainer` ayant pour clé la valeur spécifiée et contenant les objets de la collection spécifiée. |

---

## Method Summary

| Type | Méthode | Description |
|---|---|---|
| `void` | `add(E elt)` | Ajoute l'objet spécifié si le conteneur est ouvert. |
| `boolean` | `close(K cle)` | Tente de fermer ce `StackContainer` avec la clé spécifiée. |
| `boolean` | `contains(Object obj)` | Renvoie true si ce `StackContainer` contient l'objet spécifié. |
| `int` | `frequencyOf(Object obj)` | Renvoie le nombre d'exemplaires de l'objet spécifié présents dans ce `StackContainer`. |
| `boolean` | `hasKey(K cle)` | Teste si l'objet spécifié est la clé de ce `StackContainer`. |
| `boolean` | `isOpen()` | Renvoie l'état actuel de ce `StackContainer` : ouvert ou fermé. |
| `Iterator<E>` | `iterator()` | Renvoie un itérateur sur les objets dans l'ordre **inverse d'insertion**. |
| `boolean` | `open(K cle)` | Tente d'ouvrir ce `StackContainer` avec la clé spécifiée. |
| `boolean` | `remove(Object obj)` | Retire un exemplaire de l'objet spécifié si le conteneur est ouvert et que l'objet est présent. |
| `int` | `size()` | Renvoie le nombre d'objets présents dans ce `StackContainer`. |

---

## Constructor Details

### `StackContainer(K cle)`

```
public StackContainer(K cle)
```

Initialise un nouveau `StackContainer` vide ayant pour clé la valeur spécifiée.

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

### `StackContainer(K cle, Collection<? extends E> desObjets)`

```
public StackContainer(K cle, Collection<? extends E> desObjets)
```

Initialise un nouveau `StackContainer` ayant pour clé la valeur spécifiée et contenant les objets de la collection spécifiée.

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
this.size() == desObjets.size();
```

**Throws :**  
`NullPointerException` - si la clé ou la collection spécifiée est null ou que la collection contient null

---

## Method Details

### `hasKey`
```
public boolean hasKey(K cle)
```
Teste si l'objet spécifié est equals à la clé de ce `StackContainer`.

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
Tente d'ouvrir ce `StackContainer` avec la clé spécifiée.

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
Tente de fermer ce `StackContainer` avec la clé spécifiée.

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
Renvoie l'état actuel de ce `StackContainer` : ouvert ou fermé.

**Pure (no side effect)**

---

### `add`
```
public void add(E elt)
```
Ajoute l'objet spécifié aux objets présents dans ce `StackContainer` s'il est ouvert.

**Requires :**
```
elt != null;
isOpen();
```

**Ensures :**
```
contains(elt);
frequencyOf(elt) == \old(frequencyOf(elt)) + 1;
```

**Throws :**  
`NullPointerException` - si l'objet spécifié est null  
`IllegalStateException` - si ce `StackContainer` est fermé

---

### `remove`
```
public boolean remove(Object obj)
```
Retire un exemplaire de l'objet spécifié de ce `StackContainer` s'il est ouvert et que cet objet y est présent.

**Requires :**
```
isOpen();
```

**Ensures :**
```
\old(contains(obj)) <==> \result;
\old(contains(obj)) ==> (frequencyOf(obj) == \old(frequencyOf(obj)) - 1);
```

**Throws :**  
`IllegalStateException` - si ce `StackContainer` est fermé

---

### `contains`
```
public boolean contains(Object obj)
```
Renvoie true si ce `StackContainer` contient au moins un exemplaire de l'objet spécifié. Renvoie false si l'argument est null ou que ce `StackContainer` est fermé.

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
Renvoie le nombre d'objets présents dans ce `StackContainer`.

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
Renvoie le nombre d'exemplaires de l'objet spécifié présents dans ce `StackContainer`. Renvoie 0 si ce `StackContainer` est fermé.

**Ensures :**
```
\result >= 0;
!isOpen() ==> (\result == 0);
```
**Pure (no side effect)**

---

### `iterator`
```
public Iterator<E> iterator()
```
Renvoie un itérateur sur les objets présents dans ce `StackContainer`. Les éléments sont parcourus dans l'**ordre inverse d'insertion** (dernier ajouté = premier parcouru). Si ce `StackContainer` est fermé, l'itérateur renvoyé se comporte comme un itérateur sur un `StackContainer` ne contenant aucun élément.

**Ensures :**
```
\result != null;
```
**Pure (no side effect)**

---

---

# CORRECTION

---

## Exercice 1 — `ReverseIterator<E>`

**Idée :** on reçoit une `List<E>` et on la parcourt de la fin vers le début avec un index qui part de `size()-1` et descend jusqu'à `0`.

```java
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

public class ReverseIterator<E> implements Iterator<E> {

    private final List<E> liste;
    private int index;

    public ReverseIterator(List<E> liste) {
        this.liste = liste;
        this.index = liste.size() - 1; // on commence à la fin
    }

    @Override
    public boolean hasNext() {
        return index >= 0;
    }

    @Override
    public E next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        return liste.get(index--); // retourne l'élément puis décrémente
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
```

**Trace d'exécution avec `["a", "b", "c"]` :**

```
Départ : index = 2

hasNext() → index >= 0 → true
next()    → liste.get(2) → "c", index devient 1

hasNext() → index >= 0 → true
next()    → liste.get(1) → "b", index devient 0

hasNext() → index >= 0 → true
next()    → liste.get(0) → "a", index devient -1

hasNext() → index >= 0 → false  ✅
```

**Comparaison des itérateurs vus :**

| | `EmptyIterator` | `SingletonIterator` | `PairIterator` | `ReverseIterator` |
|---|---|---|---|---|
| Nb éléments | 0 | 1 | 2 | n |
| `hasNext()` | `false` | `!dejaLu` | `index < 2` | `index >= 0` |
| Mémoire | aucune | `boolean` | `int` | `int` + `List` |

---

## Exercice 2 — `StackContainer<K, E>`

La différence clé avec `CloseableContainer` : **`iterator()` parcourt en ordre inverse**.  
On utilise un `ArrayList` en interne et on passe la liste à `ReverseIterator`.

```java
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class StackContainer<K, E> implements Iterable<E> {

    private final K key;
    private boolean ouvert;
    private final List<E> elements;

    public StackContainer(K cle) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        this.key = cle;
        this.ouvert = true;
        this.elements = new ArrayList<>();
    }

    public StackContainer(K cle, Collection<? extends E> desObjets) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        Objects.requireNonNull(desObjets, "La collection ne peut pas être null");
        if (desObjets.contains(null)) {
            throw new NullPointerException("La collection ne peut pas contenir null");
        }
        this.key = cle;
        this.ouvert = true;
        this.elements = new ArrayList<>(desObjets);
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
            throw new IllegalStateException("Le StackContainer est fermé");
        }
        elements.add(elt);
    }

    public boolean remove(Object obj) {
        if (!ouvert) {
            throw new IllegalStateException("Le StackContainer est fermé");
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
        return Collections.frequency(elements, obj);
    }

    @Override
    public Iterator<E> iterator() {
        if (!ouvert) return new EmptyIterator<>();
        return new ReverseIterator<>(elements); // ← réutilisation Ex.1
    }

    protected Iterator<E> iteratorInterne() {
        return elements.iterator();
    }
}
```

**Pourquoi `ArrayList` et pas `HashSet` ?**

| | `ArrayList` | `HashSet` |
|---|---|---|
| Ordre d'insertion | ✅ conservé | ❌ non garanti |
| Doublons | autorisés | interdits |

On a besoin de l'ordre pour que `ReverseIterator` fonctionne correctement → `ArrayList`.

---

## Exercice 3 — `Armoire`

Même structure que `Coffre` du vrai partiel, hérite de `StackContainer`.

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Armoire extends StackContainer<Serrure, ObjetZork> {

    private final String couleur;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Armoire vide.
     *
     * @requires serrure != null
     * @requires couleur != null
     * @requires emptyWeight >= 0
     * @ensures getCouleur().equals(couleur)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si serrure ou couleur est null
     */
    public Armoire(Serrure serrure, String couleur, int emptyWeight) {
        super(serrure);
        Objects.requireNonNull(couleur, "La couleur ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.couleur = couleur;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Armoire initialisée avec une collection d'ObjetZork.
     *
     * @requires serrure != null
     * @requires couleur != null
     * @requires emptyWeight >= 0
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getCouleur().equals(couleur)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si serrure, couleur ou elements est null,
     *         ou si elements contient null
     */
    public Armoire(Serrure serrure, String couleur, int emptyWeight,
                   Collection<? extends ObjetZork> elements) {
        super(serrure, elements);
        Objects.requireNonNull(couleur, "La couleur ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.couleur = couleur;
        this.emptyWeight = emptyWeight;
    }

    public String getCouleur() {
        return couleur;
    }

    public int getEmptyWeight() {
        return emptyWeight;
    }

    /**
     * Renvoie le poids total = poids à vide + somme des poids des objets.
     * Fonctionne même si l'armoire est fermée (via iteratorInterne).
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
StackContainer<K, E>    (ordre inverse, ArrayList, ReverseIterator)
        ↑ extends
      Armoire            (couleur, poids à vide, getWeight())
```

**Comparaison des 3 sujets :**

| | Vrai partiel | Partiel n°2 | Partiel n°3 |
|---|---|---|---|
| Itérateur spécial | `EmptyIterator` | `PairIterator` (2 élts) | `ReverseIterator` (ordre inverse) |
| Stockage interne | `ArrayList` | `HashSet` | `ArrayList` |
| Particularité | doublons ok | pas de doublons | ordre inverse |
| Classe fille | `Coffre` | `Bibliotheque` | `Armoire` |
| Clé | `Cle` | `Cadenas` | `Serrure` |

---

## Points de vigilance récapitulatifs

| Erreur fréquente | Correct |
|---|---|
| `==` pour comparer des objets | `.equals()` |
| `Object.requireNonNull` | `Objects.requireNonNull` (avec s) |
| Attribut et méthode avec le même nom | Renommer l'attribut |
| `iterator()` qui s'appelle elle-même | `elements.iterator()` ou `new ReverseIterator<>()` |
| `remove()` qui retourne toujours `true` | `return elements.remove(obj)` |
| `contains()` sans vérif `isOpen()` | `if (!ouvert) return false` |
| `getWeight()` via `iterator()` | Utiliser `iteratorInterne()` |
