using System;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

class BinaryDataSender
{
   public static void Main()
   {
      SerialEmployee emp1 = new SerialEmployee();
      SerialEmployee emp2 = new SerialEmployee();

      emp1.EmployeeID = 1;
      emp1.LastName = "Blum";
      emp1.FirstName = "Katie Jane";
      emp1.YearsService = 12;
      emp1.Salary = 35000.50;

      emp2.EmployeeID = 2;
      emp2.LastName = "Blum";
      emp2.FirstName = "Jessica";
      emp2.YearsService = 9;
      emp2.Salary = 23700.30;

      TcpClient client = new TcpClient("127.0.0.1", 9050);
      IFormatter formatter = new BinaryFormatter();
      NetworkStream strm = client.GetStream();

      formatter.Serialize(strm, emp1);
      formatter.Serialize(strm, emp2);
      strm.Close();
      client.Close();
   }
}