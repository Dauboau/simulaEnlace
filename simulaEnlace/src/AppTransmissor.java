import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;

public class AppTransmissor {

    public static void aplicacaoTransmissora(){

        Scanner scannerInput = new Scanner(System.in);

        System.out.println("Digite uma mensagem:");

        String mensagem = scannerInput.nextLine();

        // debug input
        System.out.println(mensagem);

        scannerInput.close();

        // chama a próxima camada
        camadaDeAplicacaoTransmissora(mensagem);

    }

    private static void camadaDeAplicacaoTransmissora(String mensagem){

        ArrayList<Integer> quadro = new ArrayList<>(Arrays.asList(
            new BigInteger(mensagem.getBytes())
            .toString(2)
            .split(""))
            .stream()
            .map(p->Integer.valueOf(p))
            .collect(Collectors.toList()))
        ;

        // debug quadro
        System.out.println(quadro);

        String text = new String(new BigInteger(String.join("",quadro.toString().replaceAll(", |\\[|\\]", "")), 2).toByteArray());
        System.out.println(text);
    }
    
}
