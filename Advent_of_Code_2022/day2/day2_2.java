import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int ans=0;
        while(true){
            String[] words = br.readLine().split(" ");
            if(words[0].equals("end")) break;
            int s = words[0].charAt(0)-'A';
            int d = words[1].charAt(0)-'W';
            // ここでsとdを使った処理を行う
            ans+=(d-1)*3+(s+(d-2)+3)%3+1;
        }
        System.out.println(ans);
    }
}