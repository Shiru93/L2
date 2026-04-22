import java.awt.*;

/**
 *  Un triangle qui peut être manipulé et se dessine sur un fond.
 * 
 * @author  Michael Kolling et David J. Barnes
 * @version 1.0  (15 juillet 2000)
 */

public class Triangle
{
    private int height;
    private int width;
    private int xPosition;
    private int yPosition;
    private String color;
    private boolean isVisible;

    /**
     *Crée un nouveau triangle à la position par défaut avec la couleur par défaut.
     */
    public Triangle()
    {
        height = 30;
        width = 40;
        xPosition = 50;
        yPosition = 15;
        color = "green";
        isVisible = false;
    }

    /**
     * Affiche ce triangle. S'il était déjà visible, ne fait rien.
     */
    public void makeVisible()
    {
        isVisible = true;
        draw();
    }
    
    /**
     * Masque ce triangle. S'il était déjà masqué, ne fait rien.
     */
    public void makeInvisible()
    {
        erase();
        isVisible = false;
    }
    
    /**
     * Déplace le triangle de quelques pixels à droite.
     */
    public void moveRight()
    {
        moveHorizontal(20);
    }

    /**
     * Déplace le triangle de quelques pixels à gauche.
     */
    public void moveLeft()
    {
        moveHorizontal(-20);
    }

    /**
     * Déplace le triangle de quelques pixels vers le haut.
     */
    public void moveUp()
    {
        moveVertical(-20);
    }

    /**
     * Déplace le triangle de quelques pixels vers le bas.
     */
    public void moveDown()
    {
        moveVertical(20);
    }

    /**
     * Déplace le triangle à l'horizontale de la valeur de 'distance'.
     */
    public void moveHorizontal(int distance)
    {
        erase();
        xPosition += distance;
        draw();
    }

    /**
     * Déplace le triangle à la verticale de la valeur de 'distance'.
     */
    public void moveVertical(int distance)
    {
        erase();
        yPosition += distance;
        draw();
    }

    /**
     * Déplace lentement le triangle à l'horizontale de la valeur de 'distance'.
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
     * Déplace lentement le triangle à la verticale de la valeur de 'distance'.
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
    public void changeSize(int newHeight, int newWidth)
    {
        erase();
        height = newHeight;
        width = newWidth;
        draw();
    }

    /**
     * Modifie la couleur. Les couleurs acceptées sont "red", "yellow", "blue", "green",
     * "magenta" et "black".
     */
    public void changeColor(String newColor)
    {
        color = newColor;
        draw();
    }

    /*
     * Dessine le triangle à l'écran avec les spécifications actuelles.
     */
    private void draw()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            int[] xpoints = { xPosition, xPosition + (width/2), xPosition - (width/2) };
            int[] ypoints = { yPosition, yPosition + height, yPosition + height };
            canvas.draw(this, color, new Polygon(xpoints, ypoints, 3));
            canvas.wait(10);
        }
    }

    /*
     * Efface le triangle de l'écran.
     */
    private void erase()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.erase(this);
        }
    }
}
