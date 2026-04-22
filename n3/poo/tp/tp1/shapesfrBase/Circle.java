import java.awt.*;
import java.awt.geom.*;

/**
 * Un cercle qui peut être manipulé et qui se dessine sur un fond.
 * 
 * @author  Michael Kolling et David J. Barnes
 * @version 1.0  (15 juillet 2000)
 */

public class Circle
{
    private int diameter;
    private int xPosition;
    private int yPosition;
    private String color;
    private boolean isVisible;
    
    /**
     * Crée un nouveau cercle à la position par défaut avec la couleur par défaut.
     */
    public Circle()
    {
        diameter = 30;
        xPosition = 20;
        yPosition = 60;
        color = "blue";
        isVisible = false;
    }

    /**
     * Affiche ce cercle. S'il était déjà visible, ne fait rien.
     */
    public void makeVisible()
    {
        isVisible = true;
        draw();
    }
    
    /**
     * Masque ce cercle. S'il était déjà invisible, ne fait rien.
     */
    public void makeInvisible()
    {
        erase();
        isVisible = false;
    }
    
    /**
     * Déplace le cercle de quelques pixels à droite.
     */
    public void moveRight()
    {
        moveHorizontal(20);
    }

    /**
     * Déplace le cercle de quelques pixels à gauche.
     */
    public void moveLeft()
    {
        moveHorizontal(-20);
    }

    /**
     * Déplace le cercle de quelques pixels vers le haut.
     */
    public void moveUp()
    {
        moveVertical(-20);
    }

    /**
     * Déplace le cercle de quelques pixels vers le bas.
     */
    public void moveDown()
    {
        moveVertical(20);
    }

    /**
     * Déplace le cercle horizontalement du nombre de pixels dans 'distance'.
     */
    public void moveHorizontal(int distance)
    {
        erase();
        xPosition += distance;
        draw();
    }

    /**
     * Déplace le cercle verticalement du nombre de pixels dans 'distance'.
     */
    public void moveVertical(int distance)
    {
        erase();
        yPosition += distance;
        draw();
    }

    /**
     * Déplace lentement le cercle horizontalement du nombre de pixels dans 'distance'.
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
     * Déplace lentement le cercle verticalement du nombre de pixels dans 'distance'.
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
     * Modifie la taille par la nouvelle valeur (en pixels). Elle doit être >= 0.
     */
    public void changeSize(int newDiameter)
    {
        erase();
        diameter = newDiameter;
        draw();
    }

    /**
     * Modifie la couleur. Les couleurs valides sont "red", "yellow", "blue", "green",
     * "magenta" et "black".
     */
    public void changeColor(String newColor)
    {
        color = newColor;
        draw();
    }

    /*
     * Dessine le cercle avec les spécifications actuelles.
     */
    private void draw()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.draw(this, color, new Ellipse2D.Double(xPosition, yPosition, 
                                                          diameter, diameter));
            canvas.wait(10);
        }
    }

    /*
     * Efface le cercle de l'écran.
     */
    private void erase()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.erase(this);
        }
    }
}
