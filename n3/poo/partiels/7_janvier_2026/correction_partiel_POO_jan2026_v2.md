# Correction — Partiel POO, 7 janvier 2026
**Épreuve de Programmation Orientée Objet — Licence Informatique**  
*Institut Galilée — M. Champesme*

---

## Exercice 1 — `EmptyIterator<E>`

Un itérateur sur *aucun* élément.  
D'après la doc officielle de `Iterator` (annexe) :
- `next()` doit lever `NoSuchElementException` si plus d'éléments
- `remove()` peut lever `UnsupportedOperationException` si non supporté

```java
import java.util.Iterator;
import java.util.NoSuchElementException;

public class EmptyIterator<E> implements Iterator<E> {

    @Override
    public boolean hasNext() {
        return false;
    }

    @Override
    public E next() {
        throw new NoSuchElementException();
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
```

**Points clés :**
- Classe générique `<E>`, implémente `Iterator<E>`
- `hasNext()` → `false` systématiquement (aucun élément)
- `next()` → `NoSuchElementException` (contrat de l'interface, cf. annexe Iterator)
- `remove()` → `UnsupportedOperationException` (opération optionnelle non supportée, cf. annexe Iterator)

---

## Exercice 2 — `CloseableContainer<K, E>`

D'après l'annexe officielle, la classe est :
```
public class CloseableContainer<K, E>
extends Object
implements Iterable<E>
```

**Invariants importants à respecter :**
- `!hasKey(null)` → la clé null est interdite
- `!contains(null)` → null ne peut pas être dans le conteneur
- `!isOpen() ==> (size() == 0)` → **quand fermé, size() renvoie 0** (pas les vrais éléments !)

> Ce dernier invariant est crucial : `size()`, `contains()`, `frequencyOf()` renvoient tous 0/false quand fermé.

```java
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class CloseableContainer<K, E> implements Iterable<E> {

    private final K cle;
    private boolean ouvert;
    private final List<E> elements;

    /**
     * Constructeur 1 : CloseableContainer vide.
     * @requires cle != null
     * @ensures isOpen()
     * @ensures hasKey(cle)
     * @ensures size() == 0
     * @throws NullPointerException si cle est null
     */
    public CloseableContainer(K cle) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        this.cle = cle;
        this.ouvert = true;
        this.elements = new ArrayList<>();
    }

    /**
     * Constructeur 2 : CloseableContainer initialisé avec une collection.
     * @requires cle != null
     * @requires desObjets != null
     * @requires !desObjets.contains(null)
     * @ensures isOpen()
     * @ensures hasKey(cle)
     * @ensures this.size() == desObjets.size()
     * @throws NullPointerException si cle ou desObjets est null, ou si desObjets contient null
     */
    public CloseableContainer(K cle, Collection<? extends E> desObjets) {
        Objects.requireNonNull(cle, "La clé ne peut pas être null");
        Objects.requireNonNull(desObjets, "La collection ne peut pas être null");
        if (desObjets.contains(null)) {
            throw new NullPointerException("La collection ne peut pas contenir null");
        }
        this.cle = cle;
        this.ouvert = true;
        this.elements = new ArrayList<>(desObjets);
    }

    /**
     * Teste si l'objet spécifié est la clé de ce CloseableContainer.
     * @ensures (cle == null) ==> !\result
     * Pure (no side effect)
     */
    public boolean hasKey(K cle) {
        if (cle == null) return false;
        return this.cle.equals(cle);
    }

    /**
     * Renvoie l'état actuel : ouvert ou fermé.
     * Pure (no side effect)
     */
    public boolean isOpen() {
        return ouvert;
    }

    /**
     * Tente d'ouvrir avec la clé spécifiée.
     * @ensures hasKey(cle) <==> \result
     * @ensures hasKey(cle) ==> isOpen()
     */
    public boolean open(K cle) {
        if (hasKey(cle)) {
            this.ouvert = true;
            return true;
        }
        return false;
    }

    /**
     * Tente de fermer avec la clé spécifiée.
     * @ensures hasKey(cle) <==> \result
     * @ensures hasKey(cle) ==> !isOpen()
     */
    public boolean close(K cle) {
        if (hasKey(cle)) {
            this.ouvert = false;
            return true;
        }
        return false;
    }

    /**
     * Ajoute l'objet si le conteneur est ouvert.
     * @requires elt != null
     * @requires isOpen()
     * @throws NullPointerException si elt est null
     * @throws IllegalStateException si fermé
     */
    public void add(E elt) {
        Objects.requireNonNull(elt, "L'élément ne peut pas être null");
        if (!ouvert) {
            throw new IllegalStateException("Le CloseableContainer est fermé");
        }
        elements.add(elt);
    }

    /**
     * Retire un exemplaire de l'objet si ouvert et présent.
     * @requires isOpen()
     * @throws IllegalStateException si fermé
     */
    public boolean remove(Object obj) {
        if (!ouvert) {
            throw new IllegalStateException("Le CloseableContainer est fermé");
        }
        return elements.remove(obj);
    }

    /**
     * Renvoie true si ouvert ET contient au moins un exemplaire de obj.
     * Renvoie false si null ou si fermé.
     * @ensures \result <==> (frequencyOf(obj) > 0)
     * @ensures !isOpen() ==> !\result
     * Pure (no side effect)
     */
    public boolean contains(Object obj) {
        if (!ouvert || obj == null) return false;
        return elements.contains(obj);
    }

    /**
     * Renvoie le nombre d'objets présents.
     * Renvoie 0 si fermé (invariant : !isOpen() ==> result == 0).
     * @ensures \result >= 0
     * @ensures !isOpen() ==> (\result == 0)
     * Pure (no side effect)
     */
    public int size() {
        if (!ouvert) return 0;
        return elements.size();
    }

    /**
     * Renvoie le nombre d'exemplaires de obj présents.
     * Renvoie 0 si fermé.
     * @ensures \result >= 0
     * @ensures !isOpen() ==> (\result == 0)
     * Pure (no side effect)
     */
    public int frequencyOf(Object obj) {
        if (!ouvert) return 0;
        return Collections.frequency(elements, obj);
    }

    /**
     * Renvoie un itérateur sur les éléments.
     * Si fermé, se comporte comme un itérateur sur un conteneur vide.
     * → Utilisation de EmptyIterator (Exercice 1) !
     * @ensures \result != null
     * Pure (no side effect)
     */
    @Override
    public Iterator<E> iterator() {
        if (!ouvert) {
            return new EmptyIterator<>(); // ← Exercice 1 réutilisé ici
        }
        return elements.iterator();
    }

    /**
     * Renvoie true ssi la collection spécifiée contient les mêmes éléments.
     * Si fermé, se comporte comme un CloseableContainer vide.
     * @ensures \result <==> c != null && (\forall E elt; contains(elt);
     *          frequencyOf(elt) == Collections.frequency(c, elt))
     * @ensures \result && !isOpen() <==> (c != null && c.isEmpty())
     * Pure (no side effect)
     */
    public boolean hasSameContent(Collection<?> c) {
        if (c == null) return false;
        if (!ouvert) return c.isEmpty();
        if (elements.size() != c.size()) return false;
        for (E elt : elements) {
            if (Collections.frequency(elements, elt) != Collections.frequency(c, elt)) {
                return false;
            }
        }
        return true;
    }
}
```

---

## Exercice 3 — `Coffre`

`Coffre` hérite de `CloseableContainer<Cle, ObjetZork>` et ajoute :
- `String description`
- `int emptyWeight` (poids à vide)
- `getDescription()`, `getEmptyWeight()`, `getWeight()`

### Problème de `getWeight()` quand le coffre est fermé

`getWeight()` doit additionner le poids de **tous** les objets du coffre.  
Mais `iterator()` retourne `EmptyIterator` quand fermé → on ne peut pas itérer normalement.

**Solution :** accéder directement à la liste interne via une méthode `protected` dans `CloseableContainer` :

```java
// À ajouter dans CloseableContainer :
protected Iterator<E> iteratorInterne() {
    return elements.iterator(); // sans vérification isOpen
}
```

Puis dans `Coffre` :

```java
import java.util.Collection;
import java.util.Iterator;
import java.util.Objects;

public class Coffre extends CloseableContainer<Cle, ObjetZork> {

    private final String description;
    private final int emptyWeight;

    /**
     * Constructeur 1 : Coffre vide.
     *
     * @requires description != null
     * @requires emptyWeight >= 0
     * @requires cle != null
     * @ensures getDescription().equals(description)
     * @ensures getEmptyWeight() == emptyWeight
     */
    public Coffre(String description, int emptyWeight, Cle cle) {
        super(cle);
        Objects.requireNonNull(description, "La description ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.description = description;
        this.emptyWeight = emptyWeight;
    }

    /**
     * Constructeur 2 : Coffre initialisé avec une collection d'ObjetZork.
     *
     * @requires description != null
     * @requires emptyWeight >= 0
     * @requires cle != null
     * @requires elements != null
     * @requires !elements.contains(null)
     * @ensures getDescription().equals(description)
     * @ensures getEmptyWeight() == emptyWeight
     */
    public Coffre(String description, int emptyWeight, Cle cle,
                  Collection<? extends ObjetZork> elements) {
        super(cle, elements);
        Objects.requireNonNull(description, "La description ne peut pas être null");
        assert emptyWeight >= 0 : "Le poids à vide doit être positif ou nul";
        this.description = description;
        this.emptyWeight = emptyWeight;
    }

    public String getDescription() {
        return description;
    }

    public int getEmptyWeight() {
        return emptyWeight;
    }

    /**
     * Renvoie le poids total = poids à vide + somme des poids des objets contenus.
     * Fonctionne même si le coffre est fermé (via iteratorInterne).
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

## Résumé des points importants

| Concept | Exercice |
|---|---|
| Classe générique + `implements Iterator<E>` | Ex. 1 |
| `NoSuchElementException` dans `next()` | Ex. 1 |
| `UnsupportedOperationException` dans `remove()` | Ex. 1 |
| `CloseableContainer<K, E>` avec **deux paramètres** de type | Ex. 2 |
| `size()`, `contains()`, `frequencyOf()` → 0/false si fermé | Ex. 2 |
| `iterator()` → `EmptyIterator` si fermé (réutilisation Ex. 1) | Ex. 2 |
| `open()` et `close()` retournent un `boolean` | Ex. 2 |
| `hasSameContent()` → vrai ssi mêmes éléments avec mêmes fréquences | Ex. 2 |
| `super(cle)` ou `super(cle, elements)` dans `Coffre` | Ex. 3 |
| Assertions uniquement dans les constructeurs de `Coffre` | Ex. 3 |
| `iteratorInterne()` pour `getWeight()` quand coffre fermé | Ex. 3 |
| `getWeight()` = poids vide + somme `getWeight()` des objets | Ex. 3 |
