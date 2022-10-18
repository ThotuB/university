using System;
using System.IO;

namespace Task_2
{
	class Program
	{
		static void Main(String[] args)
		{
			// Path to Images: ./resources/...

			// gets input image
			Image image = new Image(Path.GetFullPath(@"resources\\input.bmp"));

			// encrypts image data
			image.Data = Crypto.Encrypt(image.Data);

			// saves encrypted image
			image.Save(Path.GetFullPath(@"resources\\output.bmp"));
		}
	}
}