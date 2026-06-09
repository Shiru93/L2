# Partiel Blanc — Programmation Orientée Objet
**Licence Informatique — Institut Galilée**  
*Durée : 3 heures. Documents autorisés : documentation CloseableContainer et Iterator.*

---

## Ce qui est évalué

- Utiliser correctement le langage Java pour implémenter une classe
- Effectuer des choix corrects pour la visibilité des champs et méthodes
- Respecter le contrat hérité des super-classes
- Utiliser correctement les exceptions pour les violations de pré-conditions
- Utiliser correctement l'héritage et la généricité

---

# SUJET

---

## Exercice 1 — Classe `SingletonIterator<E>` (4 pts)

La classe générique `SingletonIterator<E>` est une classe implémentant l'interface `Iterator` et représentant un itérateur sur **un seul et unique élément**.

Exemple d'utilisation :

```java
Iterator<String> it = new SingletonIterator<>("bonjour");
while (it.hasNext()) {
    System.out.println(it.next()); // affiche "bonjour"
}
```

Donnez le code source complet de la classe `SingletonIterator`.  
Les commentaires et assertions ne sont pas demandés.

**IMPORTANT :** Cette classe pourra être utilisée dans l'exercice 2.

---

## Exercice 2 — Classe `BoundedContainer<K, E>` (8 pts)

On souhaite définir une classe `BoundedContainer<K, E>` qui fonctionne comme un `CloseableContainer` mais avec une **capacité maximale** : on ne peut pas ajouter plus de `capacity` éléments.

Par rapport à un `CloseableContainer`, un `BoundedContainer` possède deux caractéristiques supplémentaires :
- un entier `capacity` représentant le nombre maximum d'éléments
- une méthode `boolean isFull()` renvoyant `true` si le conteneur est plein

**Comportements supplémentaires :**
- `add()` lève une `IllegalStateException` si le conteneur est plein (en plus d'être fermé)
- `isFull()` renvoie `false` si le conteneur est fermé
- `iterator()` renvoie un `SingletonIterator` sur le premier élément si le conteneur contient exactement un élément et est ouvert  
  *(indice : réutilisation de l'exercice 1)*

**Pré-conditions du constructeur :**
- `cle != null`
- `capacity > 0`

Donnez une implémentation complète de `BoundedContainer` définie par héritage de `CloseableContainer`.  
Les commentaires et assertions ne sont pas demandés.

---

## Exercice 3 — Classe `Sac` (8 pts)

Dans le contexte du jeu Zork, on souhaite définir une classe `Sac` pouvant contenir des `ObjetZork`.  
Un `Sac` est un `BoundedContainer<Cle, ObjetZork>`.

Par rapport à un `BoundedContainer`, un `Sac` possède deux caractéristiques supplémentaires :
- une instance de la classe `String` représentant la matière du sac (ex: "cuir", "tissu")
- un entier représentant le poids à vide du sac

Compte tenu de ces caractéristiques, trois méthodes supplémentaires devront être définies :
- `String getMaterial()` renvoyant la matière du sac
- `int getEmptyWeight()` renvoyant le poids à vide du sac
- `int getWeight()` renvoyant le poids total (poids à vide + somme des poids de tous les objets)

La classe `Sac` devra disposer de deux constructeurs :
- un constructeur initialisant un `Sac` vide avec une capacité, une matière et un poids à vide
- un constructeur initialisant un `Sac` contenant les éléments d'une collection donnée

**IMPORTANT :** Les commentaires et assertions devront être donnés uniquement pour les deux constructeurs. On supposera que la classe `ObjetZork` possède une méthode `int getWeight()`.

Donnez une implémentation complète de la classe `Sac`.

---

---

# CORRECTION

---

## Exercice 1 — `SingletonIterator<E>` (4 pts)

**Idée :** on stocke l'élément unique et un booléen `dejaLu` pour savoir si `next()` a déjà été appelé.

```java
import java.util.Iterator;
import java.util.NoSuchElementException;

public class SingletonIterator<E> implements Iterator<E> {

    private final E element;
    private boolean dejaLu;

    public SingletonIterator(E element) {
        this.element = element;
        this.dejaLu = false;
    }

    @Override
    public boolean hasNext() {
        return !dejaLu;
    }

    @Override
    public E next() {
        if (dejaLu) {
            throw new NoSuchElementException();
        }
        dejaLu = true;
        return element;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
```

**Points clés :**
- Classe générique `<E>`, implémente `Iterator<E>`
- Attribut `dejaLu` pour suivre si l'élément a déjà été retourné
- `hasNext()` → `true` seulement si pas encore lu
- `next()` → lève `NoSuchElementException` si déjà appelé (contrat Iterator)
- `remove()` → `UnsupportedOperationException` (opération non supportée)

**Comparaison avec `EmptyIterator` :**

| | `EmptyIterator` | `SingletonIterator` |
|---|---|---|
| Nb éléments | 0 | 1 |
| `hasNext()` | toujours `false` | `false` après 1 appel à `next()` |
| Attribut extra | aucun | `dejaLu` |

---

## Exercice 2 — `BoundedContainer<K, E>` (8 pts)

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class BoundedContainer<K, E> extends CloseableContainer<K, E> {

    private final int capacity;

    public BoundedContainer(K cle, int capacity) {
        super(cle);
        assert capacity > 0 : "La capacité doit être strictement positive";
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        this.capacity = capacity;
    }

    public boolean isFull() {
        if (!isOpen()) return false;
        return size() >= capacity;
    }

    @Override
    public void add(E elt) {
        if (isFull()) {
            throw new IllegalStateException("Le BoundedContainer est plein");
        }
        super.add(elt); // délègue à CloseableContainer (gère fermé + null)
    }

    @Override
    public Iterator<E> iterator() {
        if (!isOpen()) return new EmptyIterator<>();
        if (size() == 1) {
            // on récupère le seul élément via l'itérateur interne
            E seulElement = iteratorInterne().next();
            return new SingletonIterator<>(seulElement); // ← réutilisation Ex.1
        }
        return iteratorInterne();
    }

    public int getCapacity() {
        return capacity;
    }
}
```

**Points clés :**
- `extends CloseableContainer<K, E>` → héritage, on réutilise tout
- `isFull()` → `false` si fermé (comportement demandé)
- `add()` → on vérifie `isFull()` AVANT de déléguer à `super.add()` qui vérifie fermé + null
- `iterator()` → `SingletonIterator` si exactement 1 élément (réutilisation Ex. 1)
- `capacity` en `final` car elle ne change jamais après construction

---

## Exercice 3 — `Sac` (8 pts)

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Sac extends BoundedContainer<Cle, ObjetZork> {

    private final String material;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Sac vide.
     *
     * @requires cle != null
     * @requires material != null
     * @requires capacity > 0
     * @requires emptyWeight >= 0
     * @ensures getMaterial().equals(material)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cle ou material est null
     */
    public Sac(Cle cle, int capacity, String material, int emptyWeight) {
        super(cle, capacity);
        Objects.requireNonNull(material, "La matière ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.material = material;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Sac initialisé avec une collection d'ObjetZork.
     *
     * @requires cle != null
     * @requires material != null
     * @requires capacity > 0
     * @requires emptyWeight >= 0
     * @requires elements != null
     * @requires !elements.contains(null)
     * @requires elements.size() <= capacity
     * @ensures getMaterial().equals(material)
     * @ensures getEmptyWeight() == emptyWeight
     * @throws NullPointerException si cle, material ou elements est null,
     *         ou si elements contient null
     */
    public Sac(Cle cle, int capacity, String material, int emptyWeight,
               Collection<? extends ObjetZork> elements) {
        super(cle, capacity);
        Objects.requireNonNull(material, "La matière ne peut pas être null");
        Objects.requireNonNull(elements, "La collection ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        assert elements.size() <= capacity : "La collection dépasse la capacité";
        this.material = material;
        this.emptyWeight = emptyWeight;
        // Ajout des éléments (le sac est ouvert par défaut après super())
        for (ObjetZork obj : elements) {
            add(obj);
        }
    }

    public String getMaterial() {
        return material;
    }

    public int getEmptyWeight() {
        return emptyWeight;
    }

    /**
     * Renvoie le poids total = poids à vide + somme des poids des objets.
     * Fonctionne même si le sac est fermé (via iteratorInterne).
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

**Points clés :**
- `extends BoundedContainer<Cle, ObjetZork>` → double héritage (Sac → BoundedContainer → CloseableContainer)
- `super(cle, capacity)` dans les deux constructeurs
- Assertions uniquement dans les constructeurs (comme demandé)
- `getWeight()` utilise `iteratorInterne()` pour fonctionner même coffre fermé
- `material` et `emptyWeight` en `final` car ils ne changent jamais

---

## Résumé de la hiérarchie

```
CloseableContainer<K, E>
        ↑ extends
BoundedContainer<K, E>
        ↑ extends
       Sac
```

| Classe | Apporte |
|---|---|
| `CloseableContainer` | Stockage, ouvert/fermé, clé |
| `BoundedContainer` | Capacité maximale, `isFull()` |
| `Sac` | Matière, poids à vide, `getWeight()` |

---

## Points de vigilance récapitulatifs

| Erreur fréquente | Correct |
|---|---|
| `Object.requireNonNull` | `Objects.requireNonNull` (avec s) |
| Attribut `open` + méthode `open()` | Renommer l'attribut en `ouvert` |
| `@Override` sur `add()` | Pas de `@Override` si méthode nouvelle |
| `extends Object` | Inutile, implicite en Java |
| Attributs en `public` | Toujours `private` |
| `ArrayList` comme type de déclaration | `List` (type le plus général) |
| `iterator()` sans vérif `isOpen` | Retourner `EmptyIterator` si fermé |
| `getWeight()` via `iterator()` | Utiliser `iteratorInterne()` |
