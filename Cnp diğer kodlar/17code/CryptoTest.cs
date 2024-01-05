using System;
using System.IO;
using System.Security;
using System.Security.Cryptography;
using System.Text;

class CryptoTest
{
   public static void Main()
   {
      Console.Write("Enter phrase to encrypt: ");
      string phrase = Console.ReadLine();
      MemoryStream memstrm = new MemoryStream();

      byte[] Key = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
      byte[] IV = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                   0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

      TripleDESCryptoServiceProvider tdes = new TripleDESCryptoServiceProvider();
      CryptoStream csw = new CryptoStream(memstrm,
                     tdes.CreateEncryptor(Key, IV), CryptoStreamMode.Write);

      csw.Write(Encoding.ASCII.GetBytes(phrase), 0, phrase.Length);
      csw.FlushFinalBlock();
      byte[] cryptdata = memstrm.GetBuffer();
      Console.WriteLine("Encrypted: {0}",
              Encoding.ASCII.GetString(cryptdata, 0, (int)memstrm.Length));

      memstrm.Position = 0;
      byte[] data = new byte[1024];

      CryptoStream csr = new CryptoStream(memstrm,
                     tdes.CreateDecryptor(Key, IV), CryptoStreamMode.Read);
      int recv = csr.Read(data, 0, data.Length);
      string newphrase = Encoding.ASCII.GetString(data, 0, recv);
      Console.WriteLine("Decrypted: {0}", newphrase);
      csr.Close();
      csw.Close();
      memstrm.Close();
   }
}