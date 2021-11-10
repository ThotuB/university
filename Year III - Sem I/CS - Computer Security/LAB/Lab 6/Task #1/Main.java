import java.security.*;
import javax.crypto.*;

class AsymEncryption {
    public static class Builder {
        private String name = "RSA";

        private Key[] keys = new Key[2];

        private String mode = "ECB";
        private String padding = "PKCS1Padding";
        
        public Builder (String encryption, int keySize) throws Exception {
            this.name = encryption;
            generateKeys(keySize);
        }

        public Builder (String encryption) throws Exception {
            this(encryption, 1024);
        }

        private void generateKeys(int size) throws Exception {
            KeyPairGenerator keyGen = KeyPairGenerator.getInstance(this.name);
            keyGen.initialize(size, new SecureRandom());

            KeyPair keyPair = keyGen.generateKeyPair();
            this.keys[0] = keyPair.getPublic();
            this.keys[1] = keyPair.getPrivate();
        }

        public Builder setMode(String mode) {
            this.mode = mode;
            return this;
        }

        public Builder setPadding(String padding) {
            this.padding = padding;
            return this;
        }

        public AsymEncryption build() throws Exception {
            AsymEncryption asymEncryption = new AsymEncryption();

            asymEncryption.publicKey = this.keys[0];
            asymEncryption.privateKey = this.keys[1];
            asymEncryption.cipher = Cipher.getInstance(this.name + "/" + this.mode + "/" + this.padding);

            return asymEncryption;
        }
    }

    private Key publicKey;
    private Key privateKey;

    private Cipher cipher;

    private AsymEncryption() {}

    public Key getPublicKey() {
        return this.publicKey;
    }

    public Key getPrivateKey() {
        return this.privateKey;
    }

    public byte[] encrypt(byte[] plainText) throws Exception {
        cipher.init(Cipher.ENCRYPT_MODE, publicKey, new SecureRandom());
        return cipher.doFinal(plainText);
    }

    public byte[] decrypt(byte[] cipherText) throws Exception {
        cipher.init(Cipher.DECRYPT_MODE, privateKey, new SecureRandom());
        return cipher.doFinal(cipherText);
    }
}

class Main {
    public static String bytesToHexString(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02X", b));
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        try {
            AsymEncryption asymEncryption = new AsymEncryption.Builder("RSA", 1024)
                .setMode("ECB")
                .setPadding("PKCS1Padding")
                .build();

            byte[] plainText = "Hello World!".getBytes();
            byte[] cipherText = asymEncryption.encrypt(plainText);
            byte[] decryptedText = asymEncryption.decrypt(cipherText);

            System.out.println("Plain Text: " + new String(plainText));
            System.out.println("Cipher Text: " + bytesToHexString(cipherText));
            System.out.println("Decrypted Text: " + new String(decryptedText));
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}