import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

class SymEncryption {
    public static class Builder {
        private String name = "AES";

        private SecretKeySpec key;
        private IvParameterSpec iv;

        private String mode = "ECB";
        private String padding = "NoPadding";
        
        public Builder (String encryption) throws Exception {
            this.name = encryption;
        }

        public Builder setKey(byte[] key) throws Exception {
            this.key = new SecretKeySpec(key, this.name);
            return this;
        }

        public Builder setIV(byte[] iv) throws Exception {
            this.iv = new IvParameterSpec(iv);
            return this;
        }

        public Builder setMode(String mode) {
            this.mode = mode;
            return this;
        }

        public Builder setPadding(String padding) {
            this.padding = padding;
            return this;
        }

        public SymEncryption build() throws Exception {
            SymEncryption symEncryption = new SymEncryption();

            symEncryption.key = this.key;
            symEncryption.iv = this.iv;
            symEncryption.mode = this.mode;
            symEncryption.cipher = Cipher.getInstance(this.name + "/" + this.mode + "/" + this.padding);

            return symEncryption;
        }
    }

    private SecretKeySpec key;
    private IvParameterSpec iv;

    private String mode;

    private Cipher cipher;

    private SymEncryption() {}

    public byte[] encrypt(byte[] plainText) throws Exception {
        switch ( mode ) {
            case "ECB":
                cipher.init(Cipher.ENCRYPT_MODE, key);
                break;
            case "CBC":
                cipher.init(Cipher.ENCRYPT_MODE, key, iv);
                break;
        }
        return cipher.doFinal(plainText);
    }

    public byte[] decrypt(byte[] cipherText) throws Exception {
        switch ( mode ) {
            case "ECB":
                cipher.init(Cipher.DECRYPT_MODE, key);
                break;
            case "CBC":
                cipher.init(Cipher.DECRYPT_MODE, key, iv);
                break;
        }
        return cipher.doFinal(cipherText);
    }
}

class Main {
    public static String bytesToString(byte[] bytes, int keySize) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < bytes.length; i++) {
            sb.append(String.format("%02x", bytes[i]));
            if (i % keySize == keySize - 1) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }

    private static void task(String inputPassword, String message){
        try {
            byte[] salt = new SecureRandom().generateSeed(16);
            int iterCount = 1000;
            int keySize = 128;
            PBEKeySpec spec = new PBEKeySpec(inputPassword.toCharArray(), salt, iterCount, keySize);
            SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
            byte[] key = factory.generateSecret(spec).getEncoded();

            SymEncryption symEncryption = new SymEncryption.Builder("AES")
                .setMode("CBC")
                .setPadding("PKCS5Padding")
                .setKey(key)
                .setIV(new byte[] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})
                .build();

            byte[] plainText = message.getBytes();
            byte[] cipherText = symEncryption.encrypt(plainText);
            byte[] decryptedText = symEncryption.decrypt(cipherText);

            System.out.println("Plain Text:\n" + new String(plainText));
            System.out.println("\nCipher Text:\n" + bytesToString(cipherText, 16));
            System.out.println("Decrypted Text:\n" + new String(decryptedText));
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        task("password12345", "hello...");
        task("password12345", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    }
}