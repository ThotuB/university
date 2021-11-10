import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

class RSA {
    Cipher cipher;

    Key publicKey;
    Key privateKey;

    public RSA(int keySize, String mode, String padding) throws Exception {
        cipher = Cipher.getInstance("RSA/" + mode + "/" + padding);
        
        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("RSA");
        keyGen.initialize(keySize, new SecureRandom());

        KeyPair keyPair = keyGen.generateKeyPair();
        publicKey = keyPair.getPublic();
        privateKey = keyPair.getPrivate();
    }

    public byte[] encrypt(byte[] data) throws Exception {
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        return cipher.doFinal(data);
    }

    public byte[] decrypt(byte[] data) throws Exception {
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        return cipher.doFinal(data);
    }
}

class AES {
    Cipher cipher;
    String mode;

    SecretKeySpec key;
    IvParameterSpec iv;

    private AES(byte[] key, String mode, String padding) {
        try {
            cipher = Cipher.getInstance("AES/" + mode + "/" + padding);
        } catch (Exception e) {
            e.printStackTrace();
        }
        this.mode = mode;
        this.key = new SecretKeySpec(key, "AES");
    }

    public AES(byte[] key, String padding) {
        this(key, "ECB", padding);
    }

    public AES(byte[] key, byte[] iv, String padding) {
        this(key, "CBC", padding);
        this.iv = new IvParameterSpec(iv);
    }

    public byte[] encrypt(byte[] data) throws Exception {
        switch (mode) {
            case "ECB":
                cipher.init(Cipher.ENCRYPT_MODE, key);
                break;
            case "CBC":
                cipher.init(Cipher.ENCRYPT_MODE, key, iv);
                break;
        }
        return cipher.doFinal(data);
    }

    public byte[] decrypt(byte[] data) throws Exception {
        switch (mode) {
            case "ECB":
                cipher.init(Cipher.DECRYPT_MODE, key);
                break;
            case "CBC":
                cipher.init(Cipher.DECRYPT_MODE, key, iv);
                break;
        }
        return cipher.doFinal(data);
    }
}

class HMac {
    SecretKeyFactory factory;

    public HMac(String algorithm) throws Exception {
        factory = SecretKeyFactory.getInstance(algorithm);
    }

    public HMac() {
        try {
            factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public byte[] generate(char[] pass, byte[] salt, int iter) throws Exception {
        PBEKeySpec spec = new PBEKeySpec(pass, salt, iter, 128);
        SecretKey key = new SecretKeySpec(factory.generateSecret(spec).getEncoded(), "AES");

        return key.getEncoded();
    }
}

class Main {
    class Convert {
        public static String toString(byte[] data) {
            return new String(data);
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

        public static byte[] toBytes(String text) {
            return text.getBytes();
        }
    }

    public static void main(String[] args) {
        try {
            byte[] key = Convert.toBytes("1234567890123456");
            AES aes = new AES(key, "PKCS5Padding");
    
            byte[] data = Convert.toBytes("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            byte[] encrypted = aes.encrypt(data);
            byte[] decrypted = aes.decrypt(encrypted);
    
            System.out.println(Convert.toString(data));
            System.out.println(Convert.toHex(encrypted, 16));
            System.out.println(Convert.toString(decrypted));
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}