using System;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

class BinaryDataRcvr
{
   public static void Main()
   {
      TcpListener server = new TcpListener(9050);
      server.Start();
      TcpClient client = server.AcceptTcpClient();
      NetworkStream strm = client.GetStream();
      IFormatter formatter = new BinaryFormatter();

      SerialEmployee emp1 = (SerialEmployee)formatter.Deserialize(strm);
      Console.WriteLine("emp1.EmployeeID = {0}", emp1.EmployeeID);
      Console.WriteLine("emp1.LastName = {0}", emp1.LastName);
      Console.WriteLine("emp1.FirstName = {0}", emp1.FirstName);
      Console.WriteLine("emp1.YearsService = {0}", emp1.YearsService);
      Console.WriteLine("emp1.Salary = {0}\n", emp1.Salary);

      SerialEmployee emp2 = (SerialEmployee)formatter.Deserialize(strm);
      Console.WriteLine("emp2.EmployeeID = {0}", emp2.EmployeeID);
      Console.WriteLine("emp2.LastName = {0}", emp2.LastName);
      Console.WriteLine("emp2.FirstName = {0}", emp2.FirstName);
      Console.WriteLine("emp2.YearsService = {0}", emp2.YearsService);
      Console.WriteLine("emp2.Salary = {0}", emp2.Salary);
      strm.Close();
      server.Stop();
   }
}