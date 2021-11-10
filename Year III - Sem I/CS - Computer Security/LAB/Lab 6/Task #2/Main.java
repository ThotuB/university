import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

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

    public static void main(String[] args) {
        System.out.println("CBC MODE");
        try {
            SymEncryption symEncryption = new SymEncryption.Builder("AES")
                .setMode("CBC")
                .setPadding("PKCS5Padding")
                .setKey(new byte[] {0x02, 0x02, 0x03, 0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10})
                .setIV(new byte[] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})
                .build();

            byte[] plainText = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA".getBytes();
            byte[] cipherText = symEncryption.encrypt(plainText);
            byte[] decryptedText = symEncryption.decrypt(cipherText);

            System.out.println("Plain Text:\n" + new String(plainText));
            System.out.println("\nCipher Text:\n" + bytesToString(cipherText, 16));
            System.out.println("Decrypted Text:\n" + new String(decryptedText));
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("\nECB MODE");
        try {
            SymEncryption symEncryption = new SymEncryption.Builder("AES")
                .setMode("ECB")
                .setPadding("PKCS5Padding")
                .setKey(new byte[] {0x02, 0x02, 0x03, 0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10})
                .build();

            byte[] plainText = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA".getBytes();
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
}