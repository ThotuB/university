using System.IO;
using System;

namespace Task_2
{
    class Image
    {
        private const int HEADER_SIZE = 138;
        public byte[] Header { get; set; }
        public byte[] Data { get; set; }

        public Image(string path) {
            byte[] image = File.ReadAllBytes(path);
            Header = new byte[HEADER_SIZE];
            Data = new byte[image.Length - HEADER_SIZE];

            Array.Copy(image, Header, HEADER_SIZE);
            Array.Copy(image, HEADER_SIZE, Data, 0, image.Length - HEADER_SIZE);
        }

        public void Save(string path) {
            ResetAlpha();

            byte[] image = new byte[Header.Length + Data.Length];
            Array.Copy(Header, image, Header.Length);
            Array.Copy(Data, 0, image, Header.Length, Data.Length);

            File.WriteAllBytes(path, image);
        }

        private void ResetAlpha(){
            for (int i = 3; i < Data.Length; i += 4){
                Data[i] = 255;
            }
        }
    }
}
