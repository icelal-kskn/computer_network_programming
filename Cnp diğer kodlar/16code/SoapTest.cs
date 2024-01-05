using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Soap;

class SoapTest
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

      Stream str = new FileStream("soaptest.xml", FileMode.Create, FileAccess.ReadWrite);
      IFormatter formatter = new SoapFormatter();

      formatter.Serialize(str, emp1);
      formatter.Serialize(str, emp2);
      str.Close();
   }
}