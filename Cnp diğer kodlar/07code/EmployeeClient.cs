using System;
using System.Net;
using System.Net.Sockets;


class EmployeeClient
{
   public static void Main()
   {
      Employee emp1 = new Employee();
      Employee emp2 = new Employee();
      TcpClient client;

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

      try
      {
         client = new TcpClient("127.0.0.1", 9050);
      } catch (SocketException)
      {
         Console.WriteLine("Unable to connect to server");
         return;
      }
      NetworkStream ns = client.GetStream();

      byte[] data = emp1.GetBytes();
      int size = emp1.size;
      byte[] packsize = new byte[2];
      Console.WriteLine("packet size = {0}", size);
      packsize = BitConverter.GetBytes(size);
      ns.Write(packsize, 0, 2);
      ns.Write(data, 0, size);
      ns.Flush();

      data = emp2.GetBytes();
      size = emp2.size;
      packsize = new byte[2];
      Console.WriteLine("packet size = {0}", size);
      packsize = BitConverter.GetBytes(size);
      ns.Write(packsize, 0, 2);
      ns.Write(data, 0, size);
      ns.Flush();
   
      ns.Close();
      client.Close();    
   }
}