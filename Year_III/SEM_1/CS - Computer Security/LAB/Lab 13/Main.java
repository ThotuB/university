import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

class Main {
    public static String toString(byte[] data) {
        StringBuilder sb = new StringBuilder();
        for (byte b : data) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    public static String toHex(byte[] data, int blockSize) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < data.length; i++) {
            sb.append(String.format("%02x", data[i]));
            if (i % blockSize == blockSize - 1) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                                 + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }

    public static void main(String[] args){
        String c = "1F2588D48FCFFDB2771719259342A814E04BFA6C4953AE56C38BCC951F928CD6";
        String iv = "AF82BDA52D4196C88FF7525BE24ED188";

        byte[] cBytes = hexStringToByteArray(c);
        byte[] ivBytes = hexStringToByteArray(iv);

        String pass = "crazy_monkey";
        String salt = "75384F7E36634ACBE44C4128C0566A75";

        try {
            PBEKeySpec spec = new PBEKeySpec(pass.toCharArray(), hexStringToByteArray(salt), 8000, 128);
            SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");

            SecretKey key = new SecretKeySpec(factory.generateSecret(spec).getEncoded(), "AES");

            byte[] keyBytes = key.getEncoded();
            System.out.println(toHex(keyBytes, 32));

            Cipher aes = Cipher.getInstance("AES/CBC/NoPadding");
            aes.init(Cipher.DECRYPT_MODE, key, new IvParameterSpec(ivBytes));

            byte[] message = aes.doFinal(cBytes);

            System.out.println(toHex(message, 32));
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
