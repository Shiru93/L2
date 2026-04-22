
import java.util.ArrayList;

public class AbstractPureList<E> implements PureList<E>{
    public PureList <E > append(Collection <? extends E > l){
        if (l != null && !l.contains(null)){
            PureList<E> nv = new PureList<E>;
            
            nv.addAll(this);
            nv.addAll(l);
        }
    }
}