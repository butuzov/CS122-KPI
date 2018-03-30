public class Parent {
    public String text;

    Parent(){
       this.text = "Padre";
    }

    public void test(){
        System.out.format("(s: %s)\n", this.text);
        privado();
        protegido();
        System.out.format("(e: %s):\n\n", this.text);
    }

    protected void protegido(){
        System.out.println("Soy protegido");
    }

    private void privado(){
        System.out.println("Soy privado");
    }
}
