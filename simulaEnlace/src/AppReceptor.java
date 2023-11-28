import java.math.BigInteger;
import java.util.ArrayList;

public class AppReceptor {

    public static void camadaDeAplicacaoReceptora(ArrayList<Integer> quadro){

        // Conversão do ArrayList de Integers para a String mensagem
        String mensagem = new String(new BigInteger(String.join("",quadro.toString().replaceAll(", |\\[|\\]", "")), 2).toByteArray());

        AppReceptor.aplicacaoReceptora(mensagem);

    }

    private static void aplicacaoReceptora(String mensagem){

        System.out.println("A mensagem recebida foi: " + mensagem);

    }
    
}