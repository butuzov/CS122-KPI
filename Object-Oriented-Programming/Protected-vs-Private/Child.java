public class Child extends Parent {

    Child(){
        this.text = "Hijo";
    }


    protected void protegido(){
        System.out.println("Soy hijo protegido");
    }

    private void privado(){
        System.out.println("Soy hijo privado");
    }
}
