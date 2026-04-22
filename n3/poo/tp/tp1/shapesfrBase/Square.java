import java.awt.*;

/**
 * Un carré qui peut être manipulé et se dessine sur un fond.
 * 
 * @author  Michael Kolling et David J. Barnes
 * @version 1.0  (15 juillet 2000)
 */

public class Square
{
    private int size;
    private int xPosition;
    private int yPosition;
    private String color;
    private boolean isVisible;

    /**
     * Crée un nouveau carré à la position par défaut avec la couleur par défaut.
     */
    public Square()
    {
        size = 30;
        xPosition = 60;
        yPosition = 50;
        color = "red";
        isVisible = false;
    }

    /**
     * Affiche ce carré. S'il était déjà visible, ne fait rien.
     */
    public void makeVisible()
    {
        isVisible = true;
        draw();
    }
    
    /**
     * Masque ce carré. S'il était déjà masqué, ne fait rien.
     */
    public void makeInvisible()
    {
        erase();
        isVisible = false;
    }
    
    /**
     * Déplace le carré de quelques pixels à droite.
     */
    public void moveRight()
    {
        moveHorizontal(20);
    }

    /**
     * Déplace le carré de quelques pixels à gauche.
     */
    public void moveLeft()
    {
        moveHorizontal(-20);
    }

    /**
     * Déplace le carré de quelques pixels vers le haut.
     */
    public void moveUp()
    {
        moveVertical(-20);
    }

    /**
     * Déplace le carré de quelques pixels vers le bas.
     */
    public void moveDown()
    {
        moveVertical(20);
    }

    /**
     * Déplace le carré à l'horizontale de la valeur de 'distance'.
     */
    public void moveHorizontal(int distance)
    {
        erase();
        xPosition += distance;
        draw();
    }

    /**
     * Déplace le carré à la verticale de la valeur de 'distance'.
     */
    public void moveVertical(int distance)
    {
        erase();
        yPosition += distance;
        draw();
    }

    /**
     * Déplace lentement le carré à l'horizontale de la valeur de 'distance'.
     */
    public void slowMoveHorizontal(int distance)
    {
        int delta;

        if(distance < 0) 
        {
            delta = -1;
            distance = -distance;
        }
        else 
        {
            delta = 1;
        }

        for(int i = 0; i < distance; i++)
        {
            xPosition += delta;
            draw();
        }
    }

    /**
     * Déplace lentement le carré à la verticale de la valeur de 'distance'.
     */
    public void slowMoveVertical(int distance)
    {
        int delta;

        if(distance < 0) 
        {
            delta = -1;
            distance = -distance;
        }
        else 
        {
            delta = 1;
        }

        for(int i = 0; i < distance; i++)
        {
            yPosition += delta;
            draw();
        }
    }

    /**
     * Passe à la nouvelle taille (en pixels). Elle doit être >= 0.
     */
    public void changeSize(int newSize)
    {
        erase();
        size = newSize;
        draw();
    }

    /**
     * Modifie la couleur. Les couleurs valables sont "red", "yellow", "blue", "green",
     * "magenta" et "black".
     */
    public void changeColor(String newColor)
    {
        color = newColor;
        draw();
    }

    /*
     * Dessine le carré à l'écran avec les spécifications actuelles.
     */
    private void draw()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.draw(this, color,
                        new Rectangle(xPosition, yPosition, size, size));
            canvas.wait(10);
        }
    }

    /*
     * Efface le carré de l'écran.
     */
    private void erase()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.erase(this);
        }
    }
}
